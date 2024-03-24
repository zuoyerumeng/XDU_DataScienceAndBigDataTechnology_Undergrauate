// miniprogram/pages/general_introduction/general_introduction.js
Page({

  /**
   * 页面的初始数据
   */
  data: {
    load_code:true
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    console.log(options)
    var that = this
    const eventChannel = this.getOpenerEventChannel()
    // 监听acceptDataFromOpenerPage事件，获取上一页面通过eventChannel传送到当前页面的数据
    eventChannel.on('acceptDataFromOpenerPage', function(data) {
      console.log(data)
      that.setData({
        g_src: data.src,
        g_name: data.name
      })
    })
    console.log(this.data.g_src)
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
  g_back:function(){
    wx.navigateBack({
      delta: 1
    })
  },
  load_image:function(e){
    console.log(e)
    var that = this
    setTimeout(() => {
      that.setData({
        image_height:e.detail.height,
        load_code:false
      })
    }, 1000);
    
  }
})