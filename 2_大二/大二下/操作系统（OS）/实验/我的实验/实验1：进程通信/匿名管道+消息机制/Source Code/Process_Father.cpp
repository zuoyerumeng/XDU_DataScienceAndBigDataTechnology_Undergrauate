
//自定义消息	
#define WM_FATHER_SEND WM_USER+100
#define WM_CHILD_SEND WM_USER+101

#include<stdio.h> 
#include <afxwin.h> 

int main()
{
	/*----下面的代码用于生成一个管道,首先需要对CreatePipe函数中的相关参数进行初始化----*/
		/*初始化lpPipeAttributes参数，这个参数抉定返回的管道句柄是否可以被子进程继承*/
	HANDLE hPipeRead, hPipeWrite;
	SECURITY_ATTRIBUTES sa; //SECURITY_ATTRIBUTES是vc提供的一个结构体数据类型
	sa.nLength=sizeof(SECURITY_ATTRIBUTES); //定义结构体的size
	sa.lpSecurityDescriptor=NULL; //定义安全描述符，NULL为默认值
	sa.bInheritHandle=TRUE; //决定返回句柄是否可以被子进程继承，TRUE为可以
	::CreatePipe(&hPipeRead,&hPipeWrite,&sa,0); //创建匿名管道

	/*----下面的代码用于创建子进程，同样首先需要初始化createProcess函数中的相关参数----*/
		/*初始化StartupInfo参数，需要定义为STARTUPINFO类型*/
	STARTUPINFO StartupInfo; //STARTUPINF0为vc定义的一个结构体数据类型
	int temp=sizeof(STARTUPINFO);
	memset(&StartupInfo,0,temp); //下面6行代码用于startupInfo的初始化
	StartupInfo.cb=temp;
	StartupInfo.dwFlags=STARTF_USESTDHANDLES;
	StartupInfo.hStdInput=hPipeRead;
	StartupInfo.hStdOutput=hPipeWrite;
	StartupInfo.hStdError=GetStdHandle(STD_ERROR_HANDLE);
	PROCESS_INFORMATION ProcessInfo; //PROCESs_INFORNATION为UC的结构体类型，用于保存生成进程的信息
		/*生成子进程，第1个参数为路径，第5个参数需要设置为TRUE(继承句柄)，第9、10个参数上面已经定义，其他的使用NULL*/
	::CreateProcess("Process_Child.exe",NULL,NULL,NULL,TRUE,0,NULL,NULL,&StartupInfo,&ProcessInfo);
	    /*将创建子进程按钮变灰，以便只能创建一个子进程*/
	CButton m_BT_CreateChildProcess;
	m_BT_CreateChildProcess.EnableWindow(FALSE);//m_BT_CreateChildProcess为按钮对象



	/*----下面的代码用于向管道写数据----*/
		/*获取EDIT控件中的字符串*/
	CString str;
	CEdit m_EDIT_Message;
	m_EDIT_Message.GetWindowText(str); //mEDIT_Message为CEdit对象,查看Vieu->Classwizard获得详情
									   //GetwindowText函数用于从EDIT控件中取得数据
		/*向管道中写入数据*/
	DWORD dwWritten;
	WriteFile(hPipeWrite,str,40,&dwWritten,NULL); //WriteFile为写管道函数
	/*----向管道写数据完毕----*/

	/*--下面的代码用于向子进程发送消息----*/
	CString strWinName ="Process_Child"; //注意这里的值应当是子进程窗体的Title
	CWnd *pWnd = CWnd::FindWindow(NULL,strWinName); //得到子进程主窗体句柄
	if(pWnd) //如果子进程窗体存在
	{
		pWnd->SendMessage(WM_FATHER_SEND,0);//发送自定义消息WM FATHER SEND给该窗体
		/*向LISTBOX控件 (记录框) 中写数据*/
		str ="Father: "+ str;
		CListBox m_LISTBOX_Record;
		m_LISTBOX_Record.InsertString(-1,str); //m LISTBOX Record为CLISTBOX对象
		/*清空Edit控件内容,以方便下次输入*/
		m_EDIT_Message.SetWindowText("");
	}
	else //如果子进程窗体不存在
		MessageBox(NULL,"没有发现子进程","错误",MB_OK);
	return 0;
}