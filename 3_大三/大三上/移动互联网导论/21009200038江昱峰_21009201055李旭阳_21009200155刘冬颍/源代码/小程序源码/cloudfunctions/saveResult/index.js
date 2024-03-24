// 云函数入口文件
const cloud = require('wx-server-sdk')

cloud.init()

const templateId = "7nG6mOLUBgkfmLbCP1GZaXXmcKqAcCvO-JJUCWDoeEw"
const qq = "670560395"
const time = "9月22日22:00"
const clubQQ = "378286068"

const groupQQMap = new Map()
{
  groupQQMap.set("0", "634472513")
  groupQQMap.set("1", "937822336")
  groupQQMap.set("2", "937715649")
  groupQQMap.set("3", "876461576")
  groupQQMap.set("4", "937235665")
  groupQQMap.set("5", "604271303")
  groupQQMap.set("6", "664670158")
  groupQQMap.set("7", "955061487")
  groupQQMap.set("8", "937807633")
}

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

  const toUserId = event.toUserId
  const result = event.result
  const adminGroupId = await getAdminGroupId(db, adminId)

  if (!isAdmin(adminGroupId)) {
    return {
      code: 1003,
      msg: "permission denied"
    }
  }
  if (!isParamOk(toUserId, result)) {
    return {
      code: 1001,
      msg: "param error"
    }
  }

  return await db.collection("applicant")
    .where({
      openId: toUserId,
      groupId: adminGroupId
    })
    .update({
      data: {
        status: result
      }
    })
    .then(_ => {
      let res = sendResultMsg(db, toUserId, adminGroupId, result)
      console.log(res)
      
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

function isParamOk(toUserId, result) {
  if (toUserId === undefined) return false
  return result === 1 || result === 2
}

function isAdmin(adminGroupId) {
  return parseInt(adminGroupId) >= 0
}

async function sendResultMsg(db, toUserId, groupId, result) {
  const namePromise = getUsername(db, toUserId)
  const groupNamePromise = getGroupName(db, groupId)

  const name = await namePromise
  const groupName = await groupNamePromise
  const groupQQ = groupQQMap.get(groupId)
  const resultStr = result === 1 ? "通过" : "未通过"

  const option = {
    touser: toUserId,
    templateId: templateId,
    miniprogram_state: 'formal',
    data: {
      thing1: {value: name},
      thing2: {value: '西电华为创新俱乐部'},
      thing3: {value: groupName},
      phrase5: {value: resultStr},
      phone_number6: {value: qq}
    }
  }
  if (result === 1) {
    option.page = `pages/result/result?group=${groupName}&qq=${qq}&time=${time}&groupQQ=${groupQQ}&clubQQ=${clubQQ}`
    option.data.phone_number6.value = groupQQ
  } else if (result === 2) {
    option.page = `pages/welcome/index`
    option.data.phone_number6.value = qq
  }
  return await cloud.openapi.subscribeMessage.send(option)
}

async function getUsername(db, toUserId) {
  const res = await db.collection("user")
    .where({
      openId: toUserId
    })
    .limit(1)
    .get()

  if (res.data.length === 0) {
    return null
  }
  return res.data[0].name
}

async function getGroupName(db, groupId) {
  const res = await db.collection("group")
    .where({
      _id: groupId
    })
    .limit(1)
    .get()

  if (res.data.length === 0) {
    return null
  }
  return res.data[0].name
}
