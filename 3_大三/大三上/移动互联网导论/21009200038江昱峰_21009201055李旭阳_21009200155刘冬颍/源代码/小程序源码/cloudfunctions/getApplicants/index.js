// 云函数入口文件
const cloud = require('wx-server-sdk')

cloud.init()

// 云函数服务端有一次只能最多取 100 条数据的限制
const MAX_LIMIT = 100

// 云函数入口函数
exports.main = async (event, _) => {
  const wxContext = cloud.getWXContext()
  const db = cloud.database()

  const openId = wxContext.OPENID
  const adminGroupId = await getAdminGroupId(db, openId)

  if (!isAdmin(adminGroupId)) {
    return {
      code: 1003,
      msg: "permission denied"
    }
  }

  // 分批取出所有数据
  const totalCnt = await getTotalCount(db, adminGroupId)
  if (totalCnt === 0) {
    return {
      code: 1004,
      msg: "not found"
    }
  }

  const batchTimes = Math.ceil(totalCnt / MAX_LIMIT)
  const tasks = []

  for (let i = 0; i < batchTimes; i++) {
    const promise = db.collection("applicant")
      .where({
        groupId: adminGroupId
      }).skip(i * MAX_LIMIT)
      .limit(MAX_LIMIT)
      .get()
    tasks.push(promise)
  }

  return await Promise.all(tasks)
    .then(res => {
      const allData = res.flatMap(e => e.data)

      return {
        code: 1000,
        data: allData
      }
    }).catch(e => {
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

function isAdmin(adminGroupId) {
  return parseInt(adminGroupId) >= 0
}

async function getTotalCount(db, groupId) {
  return await db.collection("applicant")
    .where({
      groupId: groupId
    }).count()
    .then(res => {
      return res.total
    }).catch(e => {
      console.log(e)

      return -1
    })
}
