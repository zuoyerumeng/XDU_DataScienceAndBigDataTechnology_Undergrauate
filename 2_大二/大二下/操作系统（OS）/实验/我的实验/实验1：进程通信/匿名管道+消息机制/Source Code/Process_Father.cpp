
//�Զ�����Ϣ	
#define WM_FATHER_SEND WM_USER+100
#define WM_CHILD_SEND WM_USER+101

#include<stdio.h> 
#include <afxwin.h> 

int main()
{
	/*----����Ĵ�����������һ���ܵ�,������Ҫ��CreatePipe�����е���ز������г�ʼ��----*/
		/*��ʼ��lpPipeAttributes��������������񶨷��صĹܵ�����Ƿ���Ա��ӽ��̼̳�*/
	HANDLE hPipeRead, hPipeWrite;
	SECURITY_ATTRIBUTES sa; //SECURITY_ATTRIBUTES��vc�ṩ��һ���ṹ����������
	sa.nLength=sizeof(SECURITY_ATTRIBUTES); //����ṹ���size
	sa.lpSecurityDescriptor=NULL; //���尲ȫ��������NULLΪĬ��ֵ
	sa.bInheritHandle=TRUE; //�������ؾ���Ƿ���Ա��ӽ��̼̳У�TRUEΪ����
	::CreatePipe(&hPipeRead,&hPipeWrite,&sa,0); //���������ܵ�

	/*----����Ĵ������ڴ����ӽ��̣�ͬ��������Ҫ��ʼ��createProcess�����е���ز���----*/
		/*��ʼ��StartupInfo��������Ҫ����ΪSTARTUPINFO����*/
	STARTUPINFO StartupInfo; //STARTUPINF0Ϊvc�����һ���ṹ����������
	int temp=sizeof(STARTUPINFO);
	memset(&StartupInfo,0,temp); //����6�д�������startupInfo�ĳ�ʼ��
	StartupInfo.cb=temp;
	StartupInfo.dwFlags=STARTF_USESTDHANDLES;
	StartupInfo.hStdInput=hPipeRead;
	StartupInfo.hStdOutput=hPipeWrite;
	StartupInfo.hStdError=GetStdHandle(STD_ERROR_HANDLE);
	PROCESS_INFORMATION ProcessInfo; //PROCESs_INFORNATIONΪUC�Ľṹ�����ͣ����ڱ������ɽ��̵���Ϣ
		/*�����ӽ��̣���1������Ϊ·������5��������Ҫ����ΪTRUE(�̳о��)����9��10�����������Ѿ����壬������ʹ��NULL*/
	::CreateProcess("Process_Child.exe",NULL,NULL,NULL,TRUE,0,NULL,NULL,&StartupInfo,&ProcessInfo);
	    /*�������ӽ��̰�ť��ң��Ա�ֻ�ܴ���һ���ӽ���*/
	CButton m_BT_CreateChildProcess;
	m_BT_CreateChildProcess.EnableWindow(FALSE);//m_BT_CreateChildProcessΪ��ť����



	/*----����Ĵ���������ܵ�д����----*/
		/*��ȡEDIT�ؼ��е��ַ���*/
	CString str;
	CEdit m_EDIT_Message;
	m_EDIT_Message.GetWindowText(str); //mEDIT_MessageΪCEdit����,�鿴Vieu->Classwizard�������
									   //GetwindowText�������ڴ�EDIT�ؼ���ȡ������
		/*��ܵ���д������*/
	DWORD dwWritten;
	WriteFile(hPipeWrite,str,40,&dwWritten,NULL); //WriteFileΪд�ܵ�����
	/*----��ܵ�д�������----*/

	/*--����Ĵ����������ӽ��̷�����Ϣ----*/
	CString strWinName ="Process_Child"; //ע�������ֵӦ�����ӽ��̴����Title
	CWnd *pWnd = CWnd::FindWindow(NULL,strWinName); //�õ��ӽ�����������
	if(pWnd) //����ӽ��̴������
	{
		pWnd->SendMessage(WM_FATHER_SEND,0);//�����Զ�����ϢWM FATHER SEND���ô���
		/*��LISTBOX�ؼ� (��¼��) ��д����*/
		str ="Father: "+ str;
		CListBox m_LISTBOX_Record;
		m_LISTBOX_Record.InsertString(-1,str); //m LISTBOX RecordΪCLISTBOX����
		/*���Edit�ؼ�����,�Է����´�����*/
		m_EDIT_Message.SetWindowText("");
	}
	else //����ӽ��̴��岻����
		MessageBox(NULL,"û�з����ӽ���","����",MB_OK);
	return 0;
}