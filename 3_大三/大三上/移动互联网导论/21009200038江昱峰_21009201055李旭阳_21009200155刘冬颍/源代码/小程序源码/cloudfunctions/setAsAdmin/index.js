// 云函数入口文件
const cloud = require('wx-server-sdk')

cloud.init()

// 云函数入口函数
exports.main = async (event, _) => {
  if (!isParamOk(event)) {
    return {
      code: 1001,
      msg: "param error"
    }
  }

  const db = cloud.database()

  const studentNum = event.studentNum
  const groupId = event.groupId

  return await db.collection("user")
    .where({
      studentNum: studentNum
    }).update({
        data: {
          adminFor: groupId
        }
      }
    ).then(_ => {
      return {
        code: 1000,
        msg: "updated"
      }
    }).catch(e => {
      console.log(e)

      return {
        code: 1100,
        msg: "server internal error"
      }
    })
}

function isParamOk(event) {
  if (event.studentNum === undefined) return false
  if (event.groupId === undefined) return false
  return true
}
