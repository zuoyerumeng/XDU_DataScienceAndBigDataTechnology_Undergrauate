const http = require('http');

// 以命令行参数的方式获取URL
const url = process.argv[2];

// 输出等待提示信息
let dots = '';
const interval = setInterval(() => {
  dots += '.';
  process.stdout.write(`正在获取服务器端的数据，请等待${dots}\r`);
}, 500);

// 发送HTTP请求
http.get(url, (res) => {
  clearInterval(interval); // 停止输出等待提示信息
  process.stdout.write('\n'); // 换行

  // 接收响应数据
  let data = '';
  res.on('data', (chunk) => {
    data += chunk;
  });

  // 响应结束，显示结果
  res.on('end', () => {
    console.log(data);
  });
}).on('error', (err) => {
  clearInterval(interval); // 停止输出等待提示信息
  process.stdout.write('\n'); // 换行
  console.error(`请求发生错误：${err.message}`);
});
