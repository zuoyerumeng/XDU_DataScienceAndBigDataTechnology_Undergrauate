// 云函数入口文件
const cloud = require('wx-server-sdk')

cloud.init()

// 云函数入口函数
exports.main = async (event, _) => {
  const db = cloud.database()

  return await db.collection("group")
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
