#inlucde<windows.h>

void CClipDlg::OnBnClickedSendBtn()
{
	
	//打开剪切板
	if (OpenClipboard()) {
		//清空剪切板
		EmptyClipboard();
		
		char* szSendBuf;//要发送的数据
		
		//获取编辑框的内容
		CStringW strSendW;
		GetDlgItemText(IDC_SEND_EDIT, strSendW);
		
		CStringA  strSend = (CStringA)strSendW;
		//分配一个内存对象，内存对象的句柄就是hClip
		HANDLE hClip = GlobalAlloc(GMEM_MOVEABLE, strSend.GetLength() + 1);
		//句柄加锁
		szSendBuf = (char*)GlobalLock(hClip);
		
		
		//将指定字符串复制到目标字符串，若目标字符串大小小于指定字符串，则会溢出
		//第一个参数为目标字符串，第二个参数为指定字符串
		strcpy(szSendBuf, strSend);
		
		//TRACE("seSendBuf =%s", szSendBuf);
		//解锁
		GlobalUnlock(hClip);
		//将数据放在剪切板
		SetClipboardData(CF_TEXT, hClip);
		//关闭剪切板
		CloseClipboard();
	}
}

void CClipDlg::OnBnClickedButton1()
{
	if (OpenClipboard()) {
		//先确认剪切板是否可用
		if (IsClipboardFormatAvailable(CF_TEXT)) {
			HANDLE hClip;
			char* pBuf;
			//向剪切板要数据
			hClip = GetClipboardData(CF_TEXT);
			pBuf = (char*)GlobalLock(hClip);
			
			
			
			USES_CONVERSION;
			LPCWSTR strBuf = A2W(pBuf);
			GlobalUnlock(hClip);
			//显示
			SetDlgItemText(IDC_RECV_EDIT, strBuf);
			
		}
		CloseClipboard();
	}
}
