#include<stdio.h>
#include<afxwin.h>
#include<afx.h>
#include<winuser.h>
//�Զ�����Ϣ
#define SM_FATHER_SEND WM_USER+100
#define WM_CHILD_SEND WM_USER+101

int main()
{
	//��Ϣ������
		//Generated message map functions
		//{{AFX_MSG(CProcess_ChidDlg)
	virtual bool OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnReceiveMsg(WPARAM wParam,LPARAM lParam); //������Ϣ������
	afx_msg void OnBUTTONSend();
		//}}AFX_MSG
	DECLARE_MESSAGE_MAP();

	//������Ϣӳ��
	BEGIN_MESSAGE_MAP(CProcess_ChildDlg,CDialog)
	{
		//{{AFX_MSG_MAP(CProcess_ChildDlg)
		ON_WM_PAINT();
		ON_WM_QUERYDRAGICON();
		ON_BN_CLICKED(IDC_BUTTON_Send,OnBUTTONSend);
		//}}AFX_MSG_MAP
	}	
		ON_MESSAGE(WM_FATHER_SEND,OnReceiveMsg) //��Ϣӳ��		
	END_MESSAGE_MAP()��

	//������Ϣ������
	void CProcess_ChildDlg::OnReceiveMsg(WPARAM wParam,LPARAM lParam)
	{
		DWORD dwRead;
		char s[40];
		HANDLE hPipeRead; //���������	
		/*�����*/
		hPipeRead=GetStdHandle(STD_INPUT_HANDLE); //��ùܵ������
		ReadFile(hPipeRead,s,40,&dwRead,NULL); //������		
		/*���¼����д����*/
		char str[60]="Father��";
		strcat(str,s);
		m_LISTBOX_Record.InsertString(-1,str);
	}
	return 0;
} 