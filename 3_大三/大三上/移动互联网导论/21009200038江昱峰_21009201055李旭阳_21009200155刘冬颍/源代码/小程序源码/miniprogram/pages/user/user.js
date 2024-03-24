// miniprogram/pages/user/user.js
Page({
  /**
   * 页面的初始数据
   */
  data: {
    isAdmin: false,
    is_member: false,
    avatarUrl: '',
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    this.setData({
      fakeInfo: getApp().globalData.fakeInfo,
      fakeCode: getApp().globalData.fakeCode
    })
    console.log(this.data.fakeCode, this.data.fakeInfo)
    const userInfo = getApp().globalData.userInfo
    console.log(userInfo)
    console.log('options', options)
    this.setData({
      userInfo: userInfo,
      avatarUrl: userInfo.avatarUrl,
      isAdmin: parseInt(userInfo.adminFor) >= 0,
    })
  },
  onShow: function(){
    console.log("onShow")
    const userInfo = getApp().globalData.userInfo
    console.log(userInfo)
    this.setData({
      userInfo: userInfo,
      avatarUrl: userInfo.avatarUrl,
      isAdmin: parseInt(userInfo.adminFor) >= 0,
    })
  },
  goToUserInfoFake() {
    wx.navigateTo({
      url: `/pages/userinfo/userinfo`,
    })
  },
  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady: function () {
    var that = this
    wx.cloud.callFunction({
      name: "getInterviewMsg"
    }).then(res => {
      const resp = res.result.data
      that.setData({
        message_title: resp.title,
        message_content: resp.content
      })
    })
  },
  look: function () {
    wx.navigateTo({
      url: '/pages/introduce_index/introduce_index',
    })
  },
  not_open: function () {
    wx.showToast({
      title: '敬请期待~',
      icon: 'none'
    })
  },
  interview: function () {
    wx.navigateTo({
      url: '/pages/interview/interview',
    })
  },
  editUserinfo: function () {
    wx.navigateTo({
      url: '/pages/edit_userinfo/edit_userinfo?',
    })
  },
  showMessage: function () {
    wx.showModal({
      title: this.data.message_title,
      content: this.data.message_content
    })
  },
  editTitle: function () {
    var that = this
    wx.showModal({
      editable: true,
      showCancel: true,
      placeholderText: "请修改你的头衔~",
      content: that.data.userInfo.title,
      success(res) {
        if (res.confirm) {
          const newTitle = res.content
          wx.showLoading({
            title: '修改中',
          })
          wx.cloud.callFunction({
            name: 'updateTitle',
            data: {
              title: newTitle
            }
          }).then(res => {
            getApp().globalData.userInfo.title = newTitle
            wx.hideLoading();
            that.setData({
              userInfo: getApp().globalData.userInfo
            })

            wx.showToast({
              title: '修改成功',
            })
          })
        }
      }
    })
  }
})
