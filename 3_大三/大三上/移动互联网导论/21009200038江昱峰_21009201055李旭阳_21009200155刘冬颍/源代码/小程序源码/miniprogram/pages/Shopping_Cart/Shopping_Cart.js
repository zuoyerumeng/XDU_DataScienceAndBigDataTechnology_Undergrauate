// miniprogram/pages/Shopping_Cart/Shopping_Cart.js
const app = getApp()
Page({
  /**
   * 页面的初始数据
   */
  data: {
    group_t: [0, 1, 3, 4, 7], // 哪些是技术部
    selectedTech: [], // 技术部
    selectedFans: [], // 花粉部
    final_selected: [],
    select_all_color: "gray",
    final_selected_group_id: [],
    back: 0 //back为2时返回到我们界面

  },
  deal_data: function () {
    var groupTypes = app.globalData.groupTypes
    var groups = app.globalData.groups
    this.setData({
      groupTypes: groupTypes,
      groups: groups
    })
    var selected = this.data.department_selected_id
    console.log(selected)
    for (var i in selected) {
      let bool = false
      for (var j in this.data.group_t) {
        if (selected[i] == this.data.group_t[j]) {
          this.data.selectedTech.push(selected[i])
          bool = true
          break
        }
      }
      if (bool == false) {
        this.data.selectedFans.push(selected[i])
      }
    }
    console.log(this.data.selectedTech)
    console.log(this.data.selectedFans)
    this.setData({
      selected_g_t: this.data.selectedTech,
      selected_g_p: this.data.selectedFans
    })
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    var that = this
    const eventChannel = this.getOpenerEventChannel()
    eventChannel.emit('acceptDataFromOpenedPage', {
      data: 'test'
    })
    // 监听acceptDataFromOpenerPage事件，获取上一页面通过eventChannel传送到当前页面的数据
    eventChannel.on('acceptDataFromOpenerPage', function (data) {
      console.log("accept data")
      console.log('data', data)
      that.setData({
        department_selected_id: data.data
      })
      that.deal_data()
    }) /* 回调函数需要时间执行，会导致data还没出来就执行下面的代码，导致数据错乱*/
    wx.cloud.callFunction({
      name: "getTemplateId"
    }).then(res => {
      console.log(res)
      that.data.templateID = res.result.data.templateId
      console.log(that.data.templateID)
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
      console.log(res)
      const data = res.result.data
      that.setData({
        message_title: data.title,
        message_content: data.content
      })

    })
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

  checkboxChange: function (e) {
    console.log(e)
    var f_selected = e.detail.value
    this.setData({
      final_selected: f_selected
    })
  },
  select_all: function (e) {
    if (this.data.select_all_color == "gray") {
      this.setData({
        select_all_color: "green",
        final_selected: this.data.department_selected_id
      })
    } else {
      this.setData({
        select_all_color: "gray",
        final_selected: []
      })
    }

  },
  submit: function () {
    /*for (var i in this.data.final_selected)
    console.log("提交"+this.data.department[this.data.final_selected[i]].name)*/
    var that = this
    if (this.data.final_selected.length > 0) {
      wx.showModal({
        content: "请再次确认您的意向",
        cancelColor: 'cancelColor',
        success(res) {
          if (res.confirm) {
            console.log("已确认")
            for (let i in that.data.final_selected) {
              //console.log(that.data.groups[that.data.final_selected[i]].table)
              console.log(that.data.groups[that.data.final_selected[i]]._id)
              that.data.final_selected_group_id.push(that.data.groups[that.data.final_selected[i]]._id.toString())
            }
            console.log('id:', that.data.final_selected_group_id)

            wx.showLoading({
              title: '正在提交中',
              success: res => {
                //提交意愿
                wx.cloud.callFunction({
                  data: {
                    groups: that.data.final_selected_group_id
                  },
                  name: 'createApplicants',
                  success: res => {
                    console.log('res', res)
                    if (res.result.code === 1000 ) {
                      wx.hideLoading()
                      wx.showToast({
                        title: '报名成功',
                        icon: 'success'
                      })
                    } else {
                      wx.showToast({
                        title: '已经提交了两个了，不能再交啦！',
                        icon: 'error'
                      })
                    }
                  },
                  fail: res => {
                    wx.hideLoading()
                    wx.showToast({
                      title: '报名失败',
                      icon: 'error'
                    })
                  }
                })
              }
            })

            var templateID = that.data.templateID
            wx.requestSubscribeMessage({
              tmplIds: [templateID],
              success: (result) => {
                console.log("获取订阅消息的用户权限")
              },
              fail: (result) => {
                console.log(result)
              },
              complete: (res) => {
                wx.navigateBack({
                  delta: 1,
                })
              },
            })

            // // 面试通知
            // wx.showModal({
            //   title: that.data.message_title,
            //   content: that.data.message_content,
            //   success(res) {
            //     that.data.back++
            //     if (that.data.back >= 2) wx.navigateBack({
            //       delta: 1,
            //     })
            //   }
            // })
          }
        }
      })
    }
    if (this.data.final_selected.length > 2) {
      wx.showToast({
        title: '最多选择两个意向组~',
        icon: 'none'
      })
    }
    if (this.data.final_selected.length === 0) {
      wx.showToast({
        title: '不能为空哟~',
        icon: 'none'
      })
    }
  }
})