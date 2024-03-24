// miniprogram/pages/edit_userinfo/edit_userinfo.js
Page({
  /**
   * 页面的初始数据
   */
  data: {
    userInfo: '',
    avatarUrl: ''
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    var that = this
    wx.cloud.callFunction({
      name: 'fakeCode',
    }).then( res => {
      console.log('res', res.result.code)
      var fakeCode = res.result.code
      that.setData({
        fakeCode: fakeCode
      })
    })
    console.log('fakecode', this.data.fakeCode)
    this.setData({
      userInfo: getApp().globalData.userInfo
    })
  },
  bindFormSubmit(e) {
    const newUserInfo = e.detail.value
    
    console.log(e.detail)
    if (!checkFormData(newUserInfo)) {
      wx.showToast({
        title: "请填写所有字段",
        icon: 'error'
      })
      return
    }

    newUserInfo.avatarUrl = this.data.userInfo.avatarUrl
    newUserInfo.gender = parseInt(newUserInfo.gender)
    newUserInfo.title = this.data.userInfo.title

    wx.showLoading({
      title: '保存中',
    })
    // update user
    wx.cloud.callFunction({
      name: "updateUser",
      data: newUserInfo
    }).then(_ => {
      wx.hideLoading()
      getApp().globalData.userInfo = newUserInfo
      wx.navigateBack({
        delta: 1,
      })
    }).catch(e => {
      console.log(e)
      wx.showToast({
        title: '更新失败',
        icon: "error"
      })
    })
  }
})

function checkFormData(formUser) {
  if (formUser.name === "") return false
  if (formUser.gender === "") return false
  if (formUser.grade === "") return false
  if (formUser.professional === "") return false
  if (formUser.phone === "") return false
  if (formUser.introduction === "") return false
  return true
}
