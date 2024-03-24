//app.js
App({
  globalData: {
    groups: [],
    groupTypes: [],
    selectGroupId: [],
    fakeCode: 0,
    fakeInfo: {
      fakeAvatarUrl: '',
      fakeNickname: ''
    },

    // 以下为旧数据
    group: [],
    department: [],
    select_department_id: [],
    is_add: false,
    nm: "HIC", //nickname
    code: '',
    haveGetOpenId: false,
    openId: '',
    avatarUrl: "./images/defaultAvatar.png",
    Name: "HIC",
    userInfo: {
      avatarUrl: "", //头像
      Name: "HIC",
      avatarUrl_tmp: '',
      title: '华为创新俱乐部'
    },
    d_image_path: []
  },
  imageLoader: function (imgSrc) {
    let that = this
    wx.getImageInfo({
      src: imgSrc,
      success(res) {
        console.log(res)
        that.globalData.d_image_path = res.path
        console.log(that.globalData.d_image_path)
      }
    })
  },
  onLaunch: function () {
    if (!wx.cloud) {
      console.error('请使用 2.2.3 或以上的基础库以使用云能力')
    } else {
      wx.cloud.init({
        env: 'cloud1-4gnmnyk940a1a8bd',
        traceUser: true,
      })
    }
  }
})
