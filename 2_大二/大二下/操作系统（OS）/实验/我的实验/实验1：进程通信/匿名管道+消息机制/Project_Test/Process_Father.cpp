#include<stdio.h> 
//#include<windows.h>
#include <afxwin.h> 
/***函数功能:下面的代码用于生成一个子进程，为了使得子进程能够继承管道的相关信息，
  首先生成管道，然后再生成子进程。***/
/*----下面代码用于生成一个管道
但是首先需要对CreatePipe函数中的相关参数进行初始化，详见MSDN帮助----*/
/*初始化lpPipeAttributes参数，这个参数抉定返回的管道句柄是否可以被子进程继承*/

int main()
{
	HANDLE hPipeRead, hPipeWrite;
	SECURITY_ATTRIBUTES sa;//SECURITY_ATTRIBUTES是vc提供的一个结构体数据类型
	sa.nLength=sizeof(SECURITY_ATTRIBUTES);//定义结构体的size
	sa.lpSecurityDescriptor=NULL;//定义安全描述符，NULL为默认值
	sa.bInheritHandle=TRUE; //决定返回句柄是否可以被子进程继承，TRUE为可?
	/*创建匿名管道*/
	
	::CreatePipe(&hPipeRead,&hPipeWrite,&sa,0);
	/*---管道创建完毕---*/

	/*---下面的代码用于创建子进程，
	同样首先需要初始化createProcess函数中的相关参数----*/
	/*初始化StartupInfo参数，需要定义为STARTUPINFO类型*/
	STARTUPINFO StartupInfo; //STARTUPINF0为vc定义的一个结构体数据类型
	int temp=sizeof(STARTUPINFO);
	memset(&StartupInfo,0,temp); //下面6行代码用于startupInfo的初始化
												//各个fie1d的功能详见MSDN
	StartupInfo.cb=temp;
	StartupInfo.dwFlags=STARTF_USESTDHANDLES;
	StartupInfo.hStdInput=hPipeRead;
	StartupInfo.hStdOutput=hPipeWrite;
	StartupInfo.hStdError=GetStdHandle(STD_ERROR_HANDLE);

	/*定义lpProcessInfornation参数，需要定义为PROCESS_INFORMATION类型*/
	PROCESS_INFORMATION ProcessInfo;//PROCESs_INFORNATION为UC的结构体类型，用于保存生成进程的信息

	/*生成子进程，第1个参数为路径，第5个参数需要设置为TRUE(继承句柄)，第9，10个参数上面已经定义，其他的使用NuLL*/
	::CreateProcess("Process_Child.exe",NULL,NULL,NULL,TRUE,0,NULL,NULL,&StartupInfo,&ProcessInfo);
		//注意路径现在给的是相对路径，你自己进行编译时?要修改路?
	  /*---子进程仓建完毕---*/
  
	  /*将创建子进程按钮变灰，以便只能创建一个子进程*/
	CButton m_BT_CreateChildProcess;
	m_BT_CreateChildProcess.EnableWindow(FALSE);//m_BT_CreateChildProcess为按钮对象，
	//查看View->Classwizard获得详情
	return 0;
}