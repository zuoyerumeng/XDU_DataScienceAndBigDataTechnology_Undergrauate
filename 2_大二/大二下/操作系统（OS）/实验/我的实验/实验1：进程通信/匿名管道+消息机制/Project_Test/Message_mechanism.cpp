#include<stdio.h>
#include<afxwin.h>
#include<afx.h>
#include<winuser.h>
//自定义消息
#define SM_FATHER_SEND WM_USER+100
#define WM_CHILD_SEND WM_USER+101

int main()
{
	//消息处理函数
		//Generated message map functions
		//{{AFX_MSG(CProcess_ChidDlg)
	virtual bool OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnReceiveMsg(WPARAM wParam,LPARAM lParam); //声明消息处理函数
	afx_msg void OnBUTTONSend();
		//}}AFX_MSG
	DECLARE_MESSAGE_MAP();

	//建立消息映射
	BEGIN_MESSAGE_MAP(CProcess_ChildDlg,CDialog)
	{
		//{{AFX_MSG_MAP(CProcess_ChildDlg)
		ON_WM_PAINT();
		ON_WM_QUERYDRAGICON();
		ON_BN_CLICKED(IDC_BUTTON_Send,OnBUTTONSend);
		//}}AFX_MSG_MAP
	}	
		ON_MESSAGE(WM_FATHER_SEND,OnReceiveMsg) //消息映射		
	END_MESSAGE_MAP()；

	//定义消息处理函数
	void CProcess_ChildDlg::OnReceiveMsg(WPARAM wParam,LPARAM lParam)
	{
		DWORD dwRead;
		char s[40];
		HANDLE hPipeRead; //声明读句柄	
		/*读句柄*/
		hPipeRead=GetStdHandle(STD_INPUT_HANDLE); //获得管道读句柄
		ReadFile(hPipeRead,s,40,&dwRead,NULL); //读数据		
		/*向记录框中写数据*/
		char str[60]="Father：";
		strcat(str,s);
		m_LISTBOX_Record.InsertString(-1,str);
	}
	return 0;
} 