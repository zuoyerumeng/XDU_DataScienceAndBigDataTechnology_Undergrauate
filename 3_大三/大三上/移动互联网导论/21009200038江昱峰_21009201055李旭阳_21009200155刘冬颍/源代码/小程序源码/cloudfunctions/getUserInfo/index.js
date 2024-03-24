// 云函数入口文件
const cloud = require('wx-server-sdk')

cloud.init()

// 云函数入口函数
exports.main = async (event, _) => {
  const wxContext = cloud.getWXContext()
  const db = cloud.database()

  const adminId = wxContext.OPENID
  if (adminId === undefined) {
    return {
      code: 1001,
      msg: "openId not found"
    }
  }
  if (!await isAdmin(db, adminId)) {
    return {
      code: 1003,
      msg: "permission denied"
    }
  }

  const userId = event.userId
  if (userId === undefined) {
    return {
      code: 1001,
      msg: "param error"
    }
  }

  return await db.collection("user")
    .where({
      openId: userId
    })
    .limit(1)
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
        data: res.data[0]
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

async function isAdmin(db, openId) {
  return await db.collection("user")
    .where({
      openId: openId
    })
    .limit(1)
    .get()
    .then(res => {
      if (!res.data.length > 0) {
        return false
      }
      return !isNaN(parseInt(res.data[0].adminFor))
    })
    .catch(e => {
      console.log(e)
      return false
    })
}
