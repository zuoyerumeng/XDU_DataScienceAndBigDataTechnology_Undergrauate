// miniprogram/pages/introduce_index/introduce_index.js
const app = getApp()
Page({

  /**
   * 页面的初始数据
   */
  data: {
    // 以下为新数据
    groups: [],
    groupTypes: [],
    selectGroupId: [],
    overflow: '',

    // 以下为旧数据
    order_src: "../../images/order.png",
    message_src: "../../images/message.png",
    group_touch_id: 0,
    select_department_id: [],
    show_message: false,
    animationData: {},
    g_introduction: [
      {
        id: 0,
        name: "俱乐部总介绍",
        src: "cloud://cloud1-4gnmnyk940a1a8bd.636c-cloud1-4gnmnyk940a1a8bd-1305879893/p_and_t/IMG_9402(20230905-123334).PNG"
      },
      {
        id: 1,
        name: "花粉部总介绍",
        src: "cloud://cloud1-4gnmnyk940a1a8bd.636c-cloud1-4gnmnyk940a1a8bd-1305879893/p_and_t/IMG_9401(20230905-123334).JPG"
      },
      {
        id: 2,
        name: "技术部总介绍",
        src: "cloud://cloud1-4gnmnyk940a1a8bd.636c-cloud1-4gnmnyk940a1a8bd-1305879893/p_and_t/IMG_9400.PNG"
      }
    ]
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    this.setData({
      fakeCode: getApp().globalData.fakeCode
    })
    console.log(this.data.fakeCode)
    let that = this
    wx.showLoading({
      title: '正在加载中',
    })
    // 获取全部小组
    wx.cloud.callFunction({
      name: 'getGroups'
    }).then( res => {
      console.log('getGroups的调用结果', res)
      getApp().globalData.groups = res.result.data
      that.setData({
        groups: res.result.data
      })
      wx.hideLoading()
    })
    // 获取小组分类
    wx.cloud.callFunction({
      name: 'getGroupTypes'
    }).then( res => {
      console.log('getGroupTypes的调用结果', res)
      getApp().globalData.groupTypes = res.result.data
      that.setData({
        groupTypes: res.result.data
      })
      wx.hideLoading();
    })

    // getApp().globalData.group = this.data.group
    // getApp().globalData.department = this.data.department
    let src = "groups[0].introImg"
    this.setData({
      [src]: app.globalData.d_image_path
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
  onShow: function (res) {
    if (getApp().globalData.is_add) {
      let len = getApp().globalData.selectGroupId.length
      let addId = getApp().globalData.selectGroupId[len - 1]
      console.log('addId', addId)
      let isClick = "groups[" + addId + "].isclick"
      this.setData({
        selectGroupId: getApp().globalData.selectGroupId,
        [isClick]: true
      })
      this.red_point()

    }
    wx.cloud.callFunction({
      name: "getCurApplicants"
    }).then(res => {
      console.log('getCurApplicants的调用结果', res)
      const code = res.result.code
      if (code === 1000) {
        const data = res.result.data
        console.log('data', data)
        const applicants = []
        // 为了兼容，做一些处理
        for (let i = 0; i < data.length; i++) {
          const cur = data[i]
          const idx = parseInt(cur.groupId)
          // console.log(idx)
          const img = this.data.groups[idx].coverImg
          // console.log('img', img)
          const name = this.data.groups[idx].name
          let result = ""
          if (cur.status == 0) {
            result = "待处理"
          } else if (cur.status == 1) {
            result = "已通过"
          } else if (cur.status == 2) {
            result = "未通过"
          }
          applicants.push({
            img: img,
            name: name,
            result: result
          })
        }

        this.setData({
          application_result: applicants
        })
      }
      console.log('application_result', this.data.application_result)
    })
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
  /*用户点击推荐栏中的某个类别*/
  tap_group: function (e) {
    var id = e.target.dataset.id
    this.setData({
      group_touch_id: id
    })
  },
  open_shopping_cart: function (e) {
    var that = this
    var id = this.data.selectGroupId
    wx.navigateTo({
      url: '/pages/Shopping_Cart/Shopping_Cart',
      success: function (res) {
        // 通过eventChannel向被打开页面传送数据
        res.eventChannel.emit('acceptDataFromOpenerPage', {data: id})
        console.log("emit data")
      }
    })
  },
  general_introduce: function (e) {
    var that = this
    var id = e.target.dataset.id
    var g_src = this.data.g_introduction[id].src
    var g_name = this.data.g_introduction[id].name
    console.log(g_src)
    wx.navigateTo({
      url: '/pages/general_introduction/general_introduction',
      success: function (res) {
        // 通过eventChannel向被打开页面传送数据
        res.eventChannel.emit('acceptDataFromOpenerPage', {
          src: g_src,
          name: g_name
        })
      }
    })
  },
  like: function (e) {
    console.log('like', e)
    var idd = this.data.groupTypes[this.data.group_touch_id].groupId[e.target.dataset.id]
    var id = parseInt(idd)
    console.log('id', id, typeof(id))
    this.add_to_cart(id)
    this.red_point()
    getApp().globalData.selectGroupId = this.data.selectGroupId
    console.log(getApp().globalData.selectGroupId)
  },
  red_point: function () {
    if (this.data.selectGroupId.length == 0) {
      //未知错误：全部取消like后判断 this.data.select_department_id == [] 也为false，随后改为判断length
      this.setData({
        order_src: "../../images/order.png"
      })
    } else {
      this.setData({
        order_src: "../../images/order_unread.png"
      })
    }
  },
  add_to_cart: function (id) {
    console.log("add_to_cart")
    var isclick = "groups[" + id + "].isclick"
    if (this.data.groups[id].isclick) {
      this.setData({
        [isclick]: false,
      })
      var new_select_id = []
      for (var i in this.data.selectGroupId) {
        if (id != this.data.selectGroupId[i])
          new_select_id.push(this.data.selectGroupId[i])
      }
      this.setData({
        selectGroupId: new_select_id
      })
      console.log(this.data.selectGroupId)
    } else {
      this.data.selectGroupId.push(id)
      this.setData({
        selectGroupId: this.data.selectGroupId,
        [isclick]: true
      })
      console.log(this.data.selectGroupId)
    }

  },
  detail_introduction: function (e) {
    var that = this
    var idd = this.data.groupTypes[this.data.group_touch_id].groupId[e.currentTarget.dataset.id]
    var id = parseInt(idd)
    console.log('id', id)
    var introImg = this.data.groups[id].introImg
    console.log('introImg', introImg)
    // if(id == 0) introImg = "cloud://cloud1-6grlmnp6a2096931.636c-cloud1-6grlmnp6a2096931-1305879893/images/宣传组.png"
    console.log('introImg', introImg)
    var t_group = this.data.groupTypes[1].groupId

    let f = false //f==false则代表点击的是花粉部的小组，否则为技术部的小组
    for (var i in t_group) {
      if (id == t_group[i]) {
        f = true
      }
    }
    var background_img_src = ""
    if (f) background_img_src = "https://i.loli.net/2021/08/24/pJxLBoZcmbXyQif.png"
    else background_img_src = "https://i.loli.net/2021/08/24/goNF8mWUPtZywMO.png"
    wx.navigateTo({
      url: '/pages/detail_introduction/detail_introduction',
      success: function (res) {
        // 通过eventChannel向被打开页面传送数据
        res.eventChannel.emit('acceptDataFromOpenerPage', {
          src: introImg,
          background_img_src: background_img_src,
          id: id
        })
      }
    })

  },
  message: function () {
    if (this.data.show_message == false) {
      this.showModal()
    } else {
      this.hideModal()
    }
  },
  showModal: function () {
    var that = this
    // 显示遮罩层
    var animation = wx.createAnimation({
      duration: 300,
      timingFunction: "linear",
      delay: 0
    })
    this.animation = animation
    animation.translateY(300).step()
    this.setData({
      animationData: animation.export(),
      show_message: true,
      
    })
    setTimeout(function () {
      animation.translateY(0).step()
      this.setData({
        animationData: animation.export(),
        overflow: 'hidden'
      })
    }.bind(this), 200)
  },
  // 隐藏弹框
  hideModal: function () {
    var that = this
    // 隐藏遮罩层
    var animation = wx.createAnimation({
      duration: 300,
      timingFunction: "linear",
      delay: 0
    })
    this.animation = animation
    animation.translateY(300).step()
    this.setData({
      animationData: animation.export(),
    })
    setTimeout(function () {
      animation.translateY(0).step()
      this.setData({
        animationData: animation.export(),
        show_message: false
      })
    }.bind(this), 200)
  }
})
