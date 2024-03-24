// pages/searchresult/searchresult.js

var app = getApp()

Page({

  /**
   * 页面的初始数据
   */
  data: {
    member: {
      passed: 0,
      failed: 0,
      pending: 0,
    },
    is_hidden: []
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    var stuinfo = JSON.parse(options.stuinfo)
    console.log("stuinfo", stuinfo)
    let that = this

    that.setData({
      stuinfo: stuinfo,
      group: stuinfo.groupId
    })
    console.log('信息', that.data.stuinfo)
    
    if (that.data.stuinfo.status == 1) {
      that.data.is_hidden.push(0)
      that.data.member.passed++
    } else if (that.data.stuinfo.status == 2) {
      that.data.is_hidden.push(2) //已通过为0，未通过为2，处理中为1
      that.data.member.failed++
    } else {
      that.data.is_hidden.push(1) // 0不显示，1显示
      that.data.member.pending++ 
    }
    console.log('隐藏状态', that.data.is_hidden)
    that.setData({
      is_hidden: that.data.is_hidden,
      member: that.data.member
    })
    wx.hideLoading()
    console.log('stuinfo', that.data.stuinfo)
  },
  goToUserInfo: function (e) {
    let idx = e.target.dataset.id
    const userId = this.data.stuinfo[idx].openId
    const comment = this.data.stuinfo[idx].comment
    wx.navigateTo({
      url: `../userinfo/userinfo?userId=${userId}&comment=${comment}`
    })
  },
  Agree: function (e) {
    console.log('测试', e)
    var that = this
    wx.showModal({
      cancelColor: 'cancelColor',
      content: "是否确认同意",
      success: (res) => {
        if (res.confirm) {
          console.log('用户点击确定-同意')
          var id = e.target.dataset.id
          console.log(id)
          console.log(that.data.stuinfo[id])
          var toUserId = that.data.stuinfo[id].openId
          //console.log('ishidden', that.data.is_hidden)
          var result = 1
          that.data.is_hidden[id] = 1
          that.setData({
            is_hidden: that.data.is_hidden
          })
          that.saveResult(toUserId, result, id)
        } else if (res.cancel) {
          console.log('用户点击取消')
        }
      }
    })
  },
  disAgree: function (e) {
    console.log('测试', e)
    var that = this
    wx.showModal({
      cancelColor: 'cancelColor',
      content: "是否确认拒绝",
      success: res => {
        if (res.confirm) {
          console.log('用户点击确定-拒绝')
          var id = e.target.dataset.id
          console.log('data-id', id)
          console.log(that.data.stuinfo[id])
          var toUserId = that.data.stuinfo[id].openId
          console.log('ishidden', that.data.is_hidden)
          var result = 2
          this.data.is_hidden[id] = 2
          this.setData({
            is_hidden: that.data.is_hidden
          })
          that.saveResult(toUserId, result, id)
        } else if (res.cancel) {
          console.log('用户点击取消')
        }
      }
    })

  },
  saveResult: function (openId, result, id) {
    const that = this
    console.log(openId)
    console.log(result)
    wx.showLoading({
      title: '操作中',
    })
    wx.cloud.callFunction({
      name: "saveResult",
      data: {
        toUserId: openId,
        result: result,
      }
    }).then(res => {
      console.log('saveResult', res)
      if (res.result.code === 1000) {
        if (result == 2) {
          that.data.is_hidden[id] = 2
          that.setData({
            is_hidden: that.data.is_hidden
          })
          console.log('拒绝')
          console.log(that.data.is_hidden)
          wx.hideLoading({
            success: res => {
              wx.showToast({
                title: '操作成功',
              })
              this.onShow()
            },
          })
        }
        else if(result == 1) {
          that.data.is_hidden[id] = 0
          that.setData({
            is_hidden: that.data.is_hidden
          })
          console.log('同意')
          console.log(that.data.is_hidden)
          wx.hideLoading({
            success: (res) => {
              wx.showToast({
                title: '操作成功',
              })
              this.onShow()
            },
          })
        }
      }
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

  }
})