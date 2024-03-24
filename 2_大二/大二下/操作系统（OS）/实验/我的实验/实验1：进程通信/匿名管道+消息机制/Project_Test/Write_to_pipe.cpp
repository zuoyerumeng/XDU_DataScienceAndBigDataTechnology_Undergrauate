#include<stdio.h>
#include<afxwin.h>
#include<windows.h>


/*下面代码用于向管道写数据--*/
/*获取EDIT控件中的字符串*/
int main()
{
	HANDLE hPipeWrite;
	CString str;
	CEdit m_EDIT_Message;
	m_EDIT_Message.GetWindowText(str); //mEDIT_Message为CEdit对象,查看Vieu->Classwizard获得详情
									   //GetwindowText函数用于从EDIT控件中取得数据
	/*向管道中写入数据*/
	DWORD dwWritten;
	WriteFile(hPipeWrite,str,40,&dwWritten,NULL); //WriteFile为写管道函数,
												//各个参数信息详见MSDN
	/*----向管道写数据完----*/

	/*--下面代码用于向子进程发送消息----*/
	CString strWinName ="Process Child";//注意这里的值应当是子进程窗体的Title
	CWnd *pWnd = CWnd::FindWindow(NULL,strWinName);//得到子进程主窗体句柄
	if(pWnd) //如果子进程窗体存在
	{
		pWnd->SendMessage(WM_FATHER_SEND,0);//发送自定义消息WM FATHER SEND给该窗体
											//WM_FATHER_SEND定义见头文件
		/*向LISTBOx控件 (记录框) 中写数据*/
		str ="Father: "+ str;
		CListBox m_LISTBOX_Record;
		m_LISTBOX_Record.InsertString(-1,str);//m LISTBOX Record为CLISTBOX对象
												//查看uiew->classwizard获得详情
		/*清空Edit控件内容,以方便下次输入*/
		m_EDIT_Message.SetWindowText("");
	}
	else //如果子进程窗体不存在
		MessageBox(NULL,"没有发现子进程","错误",MB_OK);
	return 0;
}