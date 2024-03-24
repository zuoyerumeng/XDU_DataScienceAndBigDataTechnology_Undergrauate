// 云函数入口文件
const cloud = require('wx-server-sdk')

const emptySet = new Set()

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

  const info = await getUserRequiredInfo(db, openId)
  const existData = await getExistData(db, openId)
  // 过滤出没有报的
  const groups = event.groups.filter(e => !existData.has(e))

  if (info == null) {
    return {
      code: 1002,
      msg: "not sign in"
    }
  }
  if (!isParamOk(groups)) {
    return {
      code: 1001,
      msg: "param error"
    }
  }

  if (existData.size + groups.length > 2) {
    return {
      code: 1001,
      msg: "request to create too much"
    }
  }

  // fast path
  if (groups.length === 0) {
    return {
      code: 1000,
      msg: "created"
    }
  }

  const applicants = []
  for (let i = 0; i < groups.length; i++) {
    const applicant = {
      groupId: groups[i],
      openId: openId,
      name: info.name,
      avatarUrl: info.avatarUrl,
      status: 0,
      comment: ""
    }
    applicants.push(applicant)
  }

  return await db.collection("applicant").add({
    data: applicants
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

function getUserRequiredInfo(db, openId) {
  return db.collection("user")
    .where({
      openId: openId
    })
    .limit(1)
    .get()
    .then(res => {
      if (!res.data.length > 0) return null

      const data = res.data[0]
      return {
        name: data.name,
        avatarUrl: data.avatarUrl,
      }
    })
    .catch(e => {
      console.log(e)

      return null
    })
}

function isParamOk(groups) {
  if (groups === undefined) return false

  const length = groups.length
  for (let i = 0; i < length; i++) {
    if (groups[i] === undefined || isNaN(parseInt(groups[i]))) return false
  }
  return true
}

function getExistData(db, openId) {
  return db.collection("applicant")
    .where({
      openId: openId
    }).get()
    .then(res => {
      if (!res.data.length > 0) return emptySet

      const set = new Set()
      const data = res.data
      data.forEach(e => {
        set.add(e.groupId)
      })
      return set
    })
    .catch(e => {
      console.log(e)

      return emptySet
    })
}