#include "pch.h"
//
//using namespace std;
// 
//int main()
//{
//	HANDLE mutex = CreateMutexA(NULL, FALSE, "yMutex");
//
//	if (WaitForSingleObject(mutex, 0) == WAIT_OBJECT_0)
//	{
//		cout << "Program is running!" << endl;
//		system("pause");
//		ReleaseMutex(mutex);
//	}
//	else
//	{
//		cout << "Error!Program is already running!" << endl;
//		system("pause");
//	}
//
//	CloseHandle(mutex);
//	return 0;
//}