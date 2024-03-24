#ifndef _MysqlClient_H
#define _MysqlClient_H
#pragma once
#include <mysql.h>
//用二维数组来存数据库中表里面的内容
#include <vector>
#include <string>
//定义一个客户端类
class MysqlClient
{
	//为了后续代码简洁，声明别名
	typedef const char* c_str;
private:
	MYSQL mysql_id;
public:
	MysqlClient();
	~MysqlClient();
	/*连接数据库需要传入
	username	用户名
	pwd			密码
	db			数据库
	host		ip地址
	port		端口号
	*/
	//连接数据库
	void connect(c_str username, c_str pwd, c_str db, c_str host, int port = 3306);
	//数据表用二维数组来接收
	typedef std::vector<std::vector<std::string>> table_content;
	//用于执行sql命令
	table_content execute(std::string sql);
	//退出连接
	void exit();
	//输出运算符重载
	friend std::ostream& operator<<(std::ostream& os, MysqlClient::table_content t);
};
std::ostream& operator<<(std::ostream& os, MysqlClient::table_content t);
#endif
