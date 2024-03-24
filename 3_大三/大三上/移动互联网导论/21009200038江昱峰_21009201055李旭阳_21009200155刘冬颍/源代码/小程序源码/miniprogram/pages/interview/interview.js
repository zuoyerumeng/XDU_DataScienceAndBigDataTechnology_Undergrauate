// pages/interview/interview.js
let app = getApp()
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
    is_hidden: [],
    searchWord: {
      cond: ''
    },
    new_is_hidden: [],
    newMember: {
      passed: 0,
      failed: 0,
      pending: 0,
    },
  },

  search: function (e) {
    wx.showLoading({
      title: '搜索中',
    })
    let that = this
    console.log('输入值', e.detail.value)
    // getApp().globalData.searchWord.cond = e.detail.value
    that.data.searchWord.cond = e.detail.value.toString()
    // that.setData({
    //   searchWord: getApp().globalData.searchWord,
    // })
    console.log("searchWord", that.data.searchWord)
    wx.cloud.callFunction({
      name: 'searchApplicants',
      data: that.data.searchWord
    }).then(res => {
      console.log('云函数搜索返回值', res.result)
      if (res.result.code === 1000) { //搜索到
        const stuInfoTemp = res.result.data
        const stuInfo = []
        var i = 0
        for (i = 0; i < stuInfoTemp.length; i++) {
          if (app.globalData.userInfo.adminFor == stuInfoTemp[i].groupId) {
            stuInfo.push(stuInfoTemp[i])
          }
        }
        wx.hideLoading()
        wx.navigateTo({
          url: `../searchresult/searchresult?stuinfo=${JSON.stringify(stuInfo)}`,
        })
      }
      else if (res.result.code === 1004) {
        wx.hideLoading()
        wx.showToast({
          title: '未找到该同学',
          icon: 'error',
          // image: "../../images/叉.png",
          duration: 1500,
        })
        setTimeout(function () {}, 1200)
      }
    }).catch(res => {

    })
    // var i = 0
    // var flag = 0
    // // wx.cloud.callFunction("search")
    // for (i = 0; i < that.data.stuinfo.length; i++) {
    //   if (that.data.search_word == that.data.stuinfo[i].name) {
    //     flag++
    //     const stuInfo = that.data.stuinfo[i]
    //     console.log(stuInfo)
    //     getApp().globalData.search_word = that.data.stuinfo[i].name
    //     console.log('搜索词', app.globalData.search_word)
    //     wx.navigateTo({
    //       url: `../searchresult/searchresult?stuinfo=${JSON.stringify(stuInfo)}`,
    //     })
    //   }
    // }
    // if (flag == 0) {
    //   wx.showToast({
    //     title: '未找到该同学',
    //     icon: 'error',
    //     // image: "../../images/叉.png",
    //     duration: 1500,
    //   })
    //   setTimeout(
    //     function () {
    //     }, 1200
    //   )
    // }
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    let that = this;
    wx.showLoading({
      title: '加载中',
    })
    wx.cloud.callFunction({
      name: 'fakeCode',
    }).then(res => {
      console.log('res', res.result.code)
      var fakeCode = res.result.code
      that.setData({
        fakeCode: fakeCode
      })
    })
    console.log("触发onload")

    wx.cloud.callFunction({
      name: "getApplicants",
    }).then(res => {
      console.log('getApplicants的调用结果', res)
      if (res.result.code == 1004) {
        wx.hideLoading()
        wx.showToast({
          icon: 'none',
          title: '暂无申请',
        })
      } else {
        wx.hideLoading()
        this.setData({
          stuinfo: res.result.data,
          group: res.result.data[0].groupId
        })
        if (that.data.is_hidden.length != that.data.stuinfo.length) {
          for (let i in that.data.stuinfo) {
            if (that.data.stuinfo[i].status == 1) {
              that.data.is_hidden.push(0)
              that.data.member.passed++
            } else if (that.data.stuinfo[i].status == 2) {
              that.data.is_hidden.push(2) //已通过为0，未通过为2，处理中为1
              that.data.member.failed++
            } else {
              that.data.is_hidden.push(1) //0不显示，1显示
              that.data.member.pending++
            }
          }
        }
        console.log('隐藏状态', that.data.is_hidden)
        that.setData({
          is_hidden: that.data.is_hidden,
          member: that.data.member
        })
        wx.hideLoading()
        console.log('stuinfo', that.data.stuinfo)
      }
    })
    //异步 容易出bug:还没获取完信息就被点击，导致出错
  },

  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady: function () {
    //console.log("触发onready")
  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow: function () {
    console.log("触发onshow")
    let that = this;
    wx.cloud.callFunction({
      name: "getApplicants",
    }).then(res => {
      console.log('getApplicants的调用结果', res)
      if (res.result.code == 1004) {
        wx.showToast({
          icon: 'none',
          title: '暂无申请',
        })
      } else {
        wx.showLoading({
          title: '加载名单中',
        })
        this.setData({
          stuinfo: res.result.data,
          group: res.result.data[0].groupId
        })
        let newIsHidden = []
        let newMember = {
          passed: 0,
          failed: 0,
          pending: 0
        }
        for (let i in that.data.stuinfo) {
          if (that.data.stuinfo[i].status == 1) {
            newIsHidden.push(0)
            newMember.passed++
          } else if (that.data.stuinfo[i].status == 2) {
            newIsHidden.push(2) //已通过为0，未通过为2，处理中为1
            newMember.failed++
          } else {
            newIsHidden.push(1) //0不显示，1显示
            newMember.pending++
          }
        }
        that.setData({
          member: newMember,
          is_hidden: newIsHidden
        })
        console.log('隐藏状态', that.data.is_hidden, that.data.member)
        wx.hideLoading()
        console.log('stuinfo', that.data.stuinfo)
      }
    })
    //异步 容易出bug:还没获取完信息就被点击，导致出错
  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide: function () {
    // console.log("触发onhide")
  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload: function () {
    console.log("触发onUnload")

  },

  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh: function () {

  },

  bindKeyInput: function (e) {
    var input = e.detail.value
    console.log("检测输入：" + input)
    this.setData({
      search_word: input
    })
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
      content: "是否确认通过",
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
            }
          })
        } else if (result == 1) {
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
            }
          })
        }
      }
    })
  },

  /**
   * 页面上拉触底事件的处理函数
   */
  // onReachBottom: function () {

  // },

  /**
   * 用户点击右上角分享
   */
  onShareAppMessage: function () {

  }
})