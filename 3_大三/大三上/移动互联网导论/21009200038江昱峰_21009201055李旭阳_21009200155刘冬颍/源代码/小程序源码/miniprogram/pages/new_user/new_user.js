const defaultAvatarUrl = '../../images/defaultAvatar.png'

Page({
  data: {
    avatarUrl: defaultAvatarUrl,
    OPENID: '',
    nickname: '',
    //avatarUrl_tmp: ''
  },
  onChooseAvatar(e) {
    getApp().globalData.fakeInfo.fakeAvatarUrl = e.detail.avatarUrl

    var ee = e
    const { avatarUrl } = e.detail
    console.log(e)
    this.setData({
      avatarUrl,
      fakeInfo: getApp().globalData.fakeInfo.fakeAvatarUrl
    });
    console.log(this.data.fakeInfo)
  },
  submitFake() {
    getApp().globalData.fakeInfo.fakeNickname = this.data.nickname
    wx.navigateTo({
      url: `/pages/user/user`,
    })
  },
  onLoad: function (options) {
    var that = this
    this.setData({
      //avatarUrl: getApp().globalData.userinfo.avatarUrl,
      // Name:getApp().globalData.userinfo.name,
      OPENID: getApp().globalData.openId,
      fakeCode: getApp().globalData.fakeCode
      // title: getApp().globalData.userInfo.title
    });
    // console.log('code_new', getApp().globalData.fakeCode)
  },
  
  bindFormSubmit(e) {
    const userInfo = e.detail.value
    if (!checkFormData(userInfo)) {
      wx.showToast({
        title: "请填写所有字段",
        icon: 'error'
      })
      return
    }
    userInfo.avatarUrl = this.data.avatarUrl
    userInfo.gender = parseInt(userInfo.gender)
    userInfo.title = '华为创新俱乐部'

    const filename = Date.now() + userInfo.avatarUrl.replace("wxfile://tmp_","")
    console.log('文件名', filename)
    wx.showLoading({
      title: '保存中',
    })
    wx.cloud.uploadFile({
      cloudPath: `avatars/${filename}`, // 上传至云端的路径
      filePath: userInfo.avatarUrl, // 小程序临时文件路径
    }).then( res => {
      userInfo.avatarUrl=res.fileID
      getApp().globalData.userInfo = userInfo
      wx.cloud.callFunction({
        name: "createUser",
        data: userInfo
      }).then(res => {
        wx.hideLoading()
        wx.reLaunch({
          url: '/pages/user/user'
        })
      }).catch(res => {
        console.log(res)
        wx.hideLoading()
        wx.showToast({
          title: '创建用户失败',
          icon: "error"
        })
      })
    });
  }
})

function checkFormData(formUser) {
  if (formUser.name === "") return false
  if (formUser.gender === "") return false
  if (formUser.grade === "") return false
  if (formUser.professional === "") return false
  if (formUser.phone === "") return false
  if (formUser.email === "") return false
  if (formUser.introduction === "") return false
  return true
}
