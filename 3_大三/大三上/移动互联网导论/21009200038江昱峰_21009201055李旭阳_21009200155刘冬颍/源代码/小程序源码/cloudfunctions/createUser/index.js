// 云函数入口文件
const cloud = require('wx-server-sdk')

cloud.init()

// 云函数入口函数
exports.main = async (event, context) => {
  const wxContext = cloud.getWXContext()
  const db = cloud.database()

  if (wxContext.OPENID === undefined) {
    return {
      code: 1001,
      msg: "openId not found"
    }
  }

  if (!isParamOk(event)) {
    return {
      code: 1001,
      msg: "param error"
    }
  }

  return await db.collection("user")
    .add({
      data: {
        openId: wxContext.OPENID,
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
        // 是哪个组的管理员
        adminFor: "-1",
        title: "华为创新俱乐部"
      },
    }).then(_ => {
      return {
        code: 1000,
        msg: "created"
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
  if (event.name === undefined) return false
  if (event.avatarUrl === undefined) return false
  if (event.gender === undefined) return false
  if (event.grade === undefined) return false
  if (event.professional === undefined) return false
  if (event.phone === undefined) return false
  if (event.email === undefined) return false
  if (event.introduction === undefined) return false

  return true
}