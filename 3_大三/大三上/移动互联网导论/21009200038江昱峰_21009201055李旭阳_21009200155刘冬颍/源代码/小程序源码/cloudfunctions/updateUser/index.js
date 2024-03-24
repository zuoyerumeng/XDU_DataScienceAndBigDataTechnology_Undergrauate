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
    }).update({
      data: {
        name: event.name,
        // 头像
        avatarUrl: event.avatarUrl,
        // 性别
        gender: event.gender,
        // 年级
        grade: event.grade,
        // 专业
        professional: event.professional,
        //手机号
        phone: event.phone,
        email: event.email,
        //个人简介
        introduction: event.introduction,
        title: event.title
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