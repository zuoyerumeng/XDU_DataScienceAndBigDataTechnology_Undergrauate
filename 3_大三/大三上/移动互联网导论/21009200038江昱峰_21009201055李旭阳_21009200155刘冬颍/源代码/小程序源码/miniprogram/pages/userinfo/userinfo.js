// pages/userinfo/userinfo.js
Page({

  /**
   * 页面的初始数据
   */
  data: {
    
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
    // console.log('options', options)
    this.setData({
      userId: options.userId,
      comment: options.comment,
    })
    wx.showLoading({
      title: '加载用户信息中',
    })
    console.log(typeof options.userId)
    wx.cloud.callFunction({
      name: "getUserInfo",
      data: {
        userId: options.userId
      }
    }).then(res => {
      console.log(res)
      this.setData({
        info: res.result.data,
      })
      if (that.data.info.gender === 0) {
        this.setData({
          genderStr: "男"
        })
      } else if (that.data.info.gender === 1) {
        this.setData({
          genderStr: "女"
        })
      } else {
        this.setData({
          genderStr: "未知"
        })
      }

      console.log(this.data.info)
      wx.hideLoading()
    })

  },

  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady: function () {

  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow: function () {

  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide: function () {

  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload: function () {

  },

  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh: function () {

  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom: function () {

  },

  /**
   * 用户点击右上角分享
   */
  onShareAppMessage: function () {

  },
  bindFormSubmit: function (e) {
    const that = this
    const comment = e.detail.value.textarea

    wx.cloud.callFunction({
      name: 'saveComment',
      data: {
        comment: comment,
        toUserId: that.data.userId
      }
    }).then(res => {
      wx.showToast({
        title: '已保存',
        icon: 'success',
        duration: 1500,
      })
      setTimeout(
        function () {
          wx.navigateBack({
            delta: 1
          })
        }, 1200
      )
    })
  }

})
