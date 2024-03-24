// 云函数入口文件
const cloud = require('wx-server-sdk')

cloud.init()

// 云函数入口函数
exports.main = async (event, _) => {
  const wxContext = cloud.getWXContext()
  const db = cloud.database()

  if (wxContext.OPENID === undefined) {
    return {
      code: 1001,
      msg: "openId not found"
    }
  }

  return await db.collection("user")
    .where({
      openId: wxContext.OPENID
    })
    .limit(1)
    .get()
    .then(res => {
      // not found
      if (!res.data.length > 0) {
        return {
          code: 1002,
          msg: "not sign in"
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
