#ifndef _MysqlClient_H
#define _MysqlClient_H
#pragma once
#include <mysql.h>
//�ö�ά�����������ݿ��б����������
#include <vector>
#include <string>
//����һ���ͻ�����
class MysqlClient
{
	//Ϊ�˺��������࣬��������
	typedef const char* c_str;
private:
	MYSQL mysql_id;
public:
	MysqlClient();
	~MysqlClient();
	/*�������ݿ���Ҫ����
	username	�û���
	pwd			����
	db			���ݿ�
	host		ip��ַ
	port		�˿ں�
	*/
	//�������ݿ�
	void connect(c_str username, c_str pwd, c_str db, c_str host, int port = 3306);
	//���ݱ��ö�ά����������
	typedef std::vector<std::vector<std::string>> table_content;
	//����ִ��sql����
	table_content execute(std::string sql);
	//�˳�����
	void exit();
	//������������
	friend std::ostream& operator<<(std::ostream& os, MysqlClient::table_content t);
};
std::ostream& operator<<(std::ostream& os, MysqlClient::table_content t);
#endif
