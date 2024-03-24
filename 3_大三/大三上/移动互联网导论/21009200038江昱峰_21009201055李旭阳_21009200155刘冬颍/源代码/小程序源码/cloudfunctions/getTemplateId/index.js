// 云函数入口文件
const cloud = require('wx-server-sdk')

cloud.init()

// 云函数入口函数
exports.main = async (event, context) => {
  const wxContext = cloud.getWXContext()

  return {
    code:1000,
    data:{
      templateId:"7nG6mOLUBgkfmLbCP1GZaXXmcKqAcCvO-JJUCWDoeEw"
    }
  }
}
