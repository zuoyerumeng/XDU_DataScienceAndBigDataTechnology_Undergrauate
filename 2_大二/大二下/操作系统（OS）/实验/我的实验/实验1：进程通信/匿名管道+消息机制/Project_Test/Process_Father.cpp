#include<stdio.h> 
//#include<windows.h>
#include <afxwin.h> 
/***��������:����Ĵ�����������һ���ӽ��̣�Ϊ��ʹ���ӽ����ܹ��̳йܵ��������Ϣ��
  �������ɹܵ���Ȼ���������ӽ��̡�***/
/*----���������������һ���ܵ�
����������Ҫ��CreatePipe�����е���ز������г�ʼ�������MSDN����----*/
/*��ʼ��lpPipeAttributes��������������񶨷��صĹܵ�����Ƿ���Ա��ӽ��̼̳�*/

int main()
{
	HANDLE hPipeRead, hPipeWrite;
	SECURITY_ATTRIBUTES sa;//SECURITY_ATTRIBUTES��vc�ṩ��һ���ṹ����������
	sa.nLength=sizeof(SECURITY_ATTRIBUTES);//����ṹ���size
	sa.lpSecurityDescriptor=NULL;//���尲ȫ��������NULLΪĬ��ֵ
	sa.bInheritHandle=TRUE; //�������ؾ���Ƿ���Ա��ӽ��̼̳У�TRUEΪ��?
	/*���������ܵ�*/
	
	::CreatePipe(&hPipeRead,&hPipeWrite,&sa,0);
	/*---�ܵ��������---*/

	/*---����Ĵ������ڴ����ӽ��̣�
	ͬ��������Ҫ��ʼ��createProcess�����е���ز���----*/
	/*��ʼ��StartupInfo��������Ҫ����ΪSTARTUPINFO����*/
	STARTUPINFO StartupInfo; //STARTUPINF0Ϊvc�����һ���ṹ����������
	int temp=sizeof(STARTUPINFO);
	memset(&StartupInfo,0,temp); //����6�д�������startupInfo�ĳ�ʼ��
												//����fie1d�Ĺ������MSDN
	StartupInfo.cb=temp;
	StartupInfo.dwFlags=STARTF_USESTDHANDLES;
	StartupInfo.hStdInput=hPipeRead;
	StartupInfo.hStdOutput=hPipeWrite;
	StartupInfo.hStdError=GetStdHandle(STD_ERROR_HANDLE);

	/*����lpProcessInfornation��������Ҫ����ΪPROCESS_INFORMATION����*/
	PROCESS_INFORMATION ProcessInfo;//PROCESs_INFORNATIONΪUC�Ľṹ�����ͣ����ڱ������ɽ��̵���Ϣ

	/*�����ӽ��̣���1������Ϊ·������5��������Ҫ����ΪTRUE(�̳о��)����9��10�����������Ѿ����壬������ʹ��NuLL*/
	::CreateProcess("Process_Child.exe",NULL,NULL,NULL,TRUE,0,NULL,NULL,&StartupInfo,&ProcessInfo);
		//ע��·�����ڸ��������·�������Լ����б���ʱ?Ҫ�޸�·?
	  /*---�ӽ��ֽ̲����---*/
  
	  /*�������ӽ��̰�ť��ң��Ա�ֻ�ܴ���һ���ӽ���*/
	CButton m_BT_CreateChildProcess;
	m_BT_CreateChildProcess.EnableWindow(FALSE);//m_BT_CreateChildProcessΪ��ť����
	//�鿴View->Classwizard�������
	return 0;
}