#include<stdio.h>
#include<afxwin.h>
#include<windows.h>


/*�������������ܵ�д����--*/
/*��ȡEDIT�ؼ��е��ַ���*/
int main()
{
	HANDLE hPipeWrite;
	CString str;
	CEdit m_EDIT_Message;
	m_EDIT_Message.GetWindowText(str); //mEDIT_MessageΪCEdit����,�鿴Vieu->Classwizard�������
									   //GetwindowText�������ڴ�EDIT�ؼ���ȡ������
	/*��ܵ���д������*/
	DWORD dwWritten;
	WriteFile(hPipeWrite,str,40,&dwWritten,NULL); //WriteFileΪд�ܵ�����,
												//����������Ϣ���MSDN
	/*----��ܵ�д������----*/

	/*--��������������ӽ��̷�����Ϣ----*/
	CString strWinName ="Process Child";//ע�������ֵӦ�����ӽ��̴����Title
	CWnd *pWnd = CWnd::FindWindow(NULL,strWinName);//�õ��ӽ�����������
	if(pWnd) //����ӽ��̴������
	{
		pWnd->SendMessage(WM_FATHER_SEND,0);//�����Զ�����ϢWM FATHER SEND���ô���
											//WM_FATHER_SEND�����ͷ�ļ�
		/*��LISTBOx�ؼ� (��¼��) ��д����*/
		str ="Father: "+ str;
		CListBox m_LISTBOX_Record;
		m_LISTBOX_Record.InsertString(-1,str);//m LISTBOX RecordΪCLISTBOX����
												//�鿴uiew->classwizard�������
		/*���Edit�ؼ�����,�Է����´�����*/
		m_EDIT_Message.SetWindowText("");
	}
	else //����ӽ��̴��岻����
		MessageBox(NULL,"û�з����ӽ���","����",MB_OK);
	return 0;
}