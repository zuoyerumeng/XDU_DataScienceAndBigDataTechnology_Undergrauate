#include <process.h>
#include <windows.h>
#include <iostream>
int main( )
{
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(STARTUPINFO);
	PROCESS_INFORMATION pi;
	bool success = CreateProcess("子进程.exe", NULL, NULL, NULL, false, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	if(!success) /*创建子进程*/
	{
		printf("创建子进程失败!"); 
		return 0;
	}
	printf("Wait for event.\n");
	
	if(WAIT_FAILED == WaitForSingleObject(pi.hProcess, INFINITE))/*等待事件信号*/
	{
		printf("等待事件信号失败！");
		return 0;
	}
	printf("Get the event.");
	/*打印"Get the event"*/
	return 0;
}
