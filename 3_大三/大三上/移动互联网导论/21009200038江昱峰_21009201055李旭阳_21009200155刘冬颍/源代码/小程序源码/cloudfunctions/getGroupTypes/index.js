// 云函数入口文件
const cloud = require('wx-server-sdk')

cloud.init()

// 云函数入口函数
exports.main = async (event, _) => {
  const wxContext = cloud.getWXContext()
  const db = cloud.database()

  const openId = wxContext.OPENID
  if (openId === undefined) {
    return {
      code: 1001,
      msg: "openId not found"
    }
  }

  return await db.collection("groupType")
    .get()
    .then(res => {
      if (!res.data.length > 0) {
        return {
          code: 1004,
          msg: "not found"
        }
      }

      return {
        code: 1000,
        data: res.data
      }
    })
    .catch(e => {
      console.log(e)

      return {
        code: 1100,
        msg: "server internal error"
      }
    })
}
