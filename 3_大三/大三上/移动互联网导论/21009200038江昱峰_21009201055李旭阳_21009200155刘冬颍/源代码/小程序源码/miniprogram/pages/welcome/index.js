// pages/welcome/index.js
const app = getApp()
let touchStartX = 0 //触摸时的原点
let touchStartY = 0 //触摸时的原点
let time = 0 // 时间记录，用于滑动时且时间小于1s则执行左右滑动
let interval = "" // 记录/清理时间记录
let touchMoveX = 0 // x轴方向移动的距离
let touchMoveY = 0 // y轴方向移动的距离

Page({
  data: {
    animation: {},
    isLogin: "请登陆",
    userInfo: {},
    hasUserInfo: false,
    canIUseGetUserProfile: false,
    headimg: '/images/hic-head.jpg'
  },
  onLoad: function() {
    var that = this
    wx.cloud.callFunction({
      name: 'fakeCode',
    }).then(res => {
      console.log(res.result.code)
      getApp().globalData.fakeCode = res.result.code
      // console.log(getApp().globalData.fakeCode)
    })
  },
  // ---------------------- slide gesture start -------------------------------
  touchStart: function (e) {
    touchStartX = e.touches[0].pageX // 获取触摸时的原点
    touchStartY = e.touches[0].pageY // 获取触摸时的原点
    // 使用js计时器记录时间
    interval = setInterval(function () {
      time++
    }, 100)
  },
  touchMove: function (e) {
    touchMoveX = e.touches[0].pageX
    touchMoveY = e.touches[0].pageY
  },
  touchEnd: function (e) {
    let moveX = touchMoveX - touchStartX
    let moveY = touchMoveY - touchStartY
    if (Math.sign(moveX) === -1) {
      moveX = moveX * -1
    }
    if (Math.sign(moveY) === -1) {
      moveY = moveY * -1
    }
    if (moveX <= moveY) { // 上下
      // 向上滑动
      if (touchMoveY - touchStartY <= -30 && time < 10) {
        this.login()
      }
      clearInterval(interval) // 清除setInterval
      time = 0
    }
  },
  // ---------------------- slide gesture end -------------------------------
  onShow: function () {
    this.setData({
      headimg: getApp().globalData.headimg,
    })
    // 1: 创建动画实例animation:
    var animation = wx.createAnimation({
      duration: 500,
      timingFunction: 'ease',
    })
    this.animation = animation
    let next = true
    //连续动画关键步骤
    setInterval(function () {
      //2: 调用动画实例方法来描述动画
      if (next) {
        //animation.scale(1.5,1.5).step();
        animation.translateY(12).step()
        //animation.rotate(19).step()
        next = !next
      } else {
        //animation.scale(1,1).step();
        animation.translateY(-12).step()
        //animation.rotate(-19).step()
        next = !next
      }
      //3: 将动画export导出，把动画数据传递组件animation的属性
      this.setData({
        animation: animation.export()
      })
    }.bind(this), 600)
  },
  login: function () {
    wx.cloud.callFunction({
      name: "login",
    }).then(res => {
      const resp = res.result
      const code = resp.code

      // 未注册
      if (code === 1002) {
        this.navigateToNewUser()
      } else {
        this.navigateToUserPage(resp.data)
      }
    }).catch(e => {
      console.log(e)

      wx.showToast({
        title: '登录失败',
        icon: 'error'
      })
    })
  },
  navigateToNewUser: function () {
    wx.reLaunch({
      url: '/pages/new_user/new_user'
    })
  },
  navigateToUserPage: function (user) {
    getApp().globalData.userInfo = user
    wx.reLaunch({
      url: '/pages/user/user',
    })
  }
})
