//云函数入口文件
const cloud = require('wx-server-sdk')

cloud.init()
//云函数入口函数
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

  const toUserId = event.toUserId
  const comment = event.comment
  const adminGroupId = await getAdminGroupId(db, adminId)

  if (!isParamOk(toUserId, comment)) {
    return {
      code: 1001,
      msg: "param error"
    }
  }
  if (!isAdmin(adminGroupId)) {
    return {
      code: 1003,
      msg: "permission denied"
    }
  }

  return await db.collection("applicant")
    .where({
      groupId: adminGroupId,
      openId: toUserId,
    })
    .update({
      data: {
        comment: comment
      }
    })
    .then(_ => {
      return {
        code: 1000,
        msg: "saved"
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

async function getAdminGroupId(db, openId) {
  return await db.collection("user")
    .where({
      openId: openId
    })
    .limit(1)
    .get()
    .then(res => {
      if (!res.data.length > 0) {
        return "-1"
      }
      return res.data[0].adminFor
    })
    .catch(e => {
      console.log(e)
      return "-1"
    })
}

function isParamOk(toUserId, comment) {
  if (toUserId === undefined) return false
  if (comment === undefined) return false

  return true
}

function isAdmin(adminGroupId) {
  return parseInt(adminGroupId) >= 0
}
