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

  if (event.title === undefined) {
    return {
      code: 1001,
      msg: "param error"
    }
  }

  return await db.collection('user')
    .where({
      openId: openId
    })
    .update({
      data: {
        title: event.title,
      }
    })
    .then(_ => {
      return {
        code: 1000,
        msg: "updated"
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
