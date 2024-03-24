// miniprogram/pages/detail_introduction/detail_introduction.js
Page({

  /**
   * 页面的初始数据
   */
  data: {
    is_add: false,
    order_src: "/images/order.png"
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    this.setData({
      fakeCode: getApp().globalData.fakeCode
    })
    console.log(this.data.fakeCode)
    getApp().globalData.is_add = false;
    console.log('onLoad options', options)
    var that = this
    const eventChannel = this.getOpenerEventChannel()
    // 监听acceptDataFromOpenerPage事件，获取上一页面通过eventChannel传送到当前页面的数据
    eventChannel.on('acceptDataFromOpenerPage', function(data) {
      console.log('data',data)
      that.setData({
        introImg: data.src,
        background_img_src: data.background_img_src,
        id: data.id
      })
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
    console.log("unload")
    if (this.data.is_add){
      getApp().globalData.is_add = true
    }
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
  back:function(){
    wx.navigateBack({
      delta: 1
    })
  },
  add:function(){
    var selectGroupId = getApp().globalData.selectGroupId
    console.log(selectGroupId)
    let flag =true;
    for (let i in selectGroupId){
      if (this.data.id == selectGroupId[i]){
        flag= false
      }
    }
    if (flag){
      selectGroupId.push(this.data.id)
      this.setData({
        is_add:true
      })
    }
    console.log(selectGroupId)
    console.log(getApp().globalData.selectGroupId)
    this.red_point()
    wx.showToast({
      title: '已加入我的意愿',
    })
  },
  red_point:function(){
      this.setData({
        order_src:"/images/order_unread.png"
      })
  },
  open_shopping_cart:function(){
    var that = this
    var id = getApp().globalData.selectGroupId
    wx.navigateTo({
      url: '/pages/Shopping_Cart/Shopping_Cart',
      success: function(res) {
        // 通过eventChannel向被打开页面传送数据
        res.eventChannel.emit('acceptDataFromOpenerPage', { data: id })
        console.log("emit data")
      }
    })
  }
})