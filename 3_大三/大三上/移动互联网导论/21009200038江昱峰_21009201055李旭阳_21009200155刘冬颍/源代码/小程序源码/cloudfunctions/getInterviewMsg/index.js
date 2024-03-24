// 云函数入口文件
const cloud = require('wx-server-sdk')

cloud.init()

const title = "面试通知"
const content = "报名时间为17-22号。面试时间暂定为23-25号，19：00-22：00（参考校园防疫政策可能会顺延，具体时间在QQ招新群另行通知，招新群号：670560395）。面试地点：竹园一号楼二区121活动室。若由于疫情原因，您无法线下参与面试，可联系招新群管理或意向组组长进行线上面试。2022年华为创新俱乐部欢迎你们的到来！！！"

// 云函数入口函数
exports.main = async (event, _) => {
  const wxContext = cloud.getWXContext()

  const openId = wxContext.OPENID
  if (openId === undefined) {
    return {
      code: 1001,
      msg: "openId not found"
    }
  }

  return {
    code: 1000,
    data: {
      title: title,
      content: content
    }
  }
}
