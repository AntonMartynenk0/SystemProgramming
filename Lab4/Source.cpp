#include "pch.h"
#define bSize 1024
#define maxNumberOfFiles 10

using namespace std;

void ShowLastError()
{
	LPVOID lpMsgBuf;
	DWORD dw = GetLastError();
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);
	_tprintf("%s", lpMsgBuf);

	LocalFree(lpMsgBuf);
}

bool pack_files()
{
	bool result = true;
	LPSTR fileName = new CHAR[MAX_PATH];
	printf("������� ���� � ����� ��� ���������:");
	scanf("%s", fileName);
	LPSTR archiveName = new CHAR[MAX_PATH];
	printf("������� ���� ���� ������ ��������� �����: ");
	scanf("%s", archiveName);
	// �������� ���������� ������
	HANDLE hInReadPipe;
	HANDLE hInWritePipe;
	HANDLE hOutReadPipe;
	HANDLE hOutWritePipe;
	CreatePipe(
		&hInReadPipe,  //����� ����������, ���� ����� ������� ������������� ������ ��� ������ ������                             
		&hInWritePipe, //����� ����������, ���� ����� ������� ������������� ������ ��� ������ ������              
		NULL,	       //����� ���������� ��� ��������� ������ 
		0);	       //���������� ���� ������, ����������������� ��� ������ 
	CreatePipe(&hOutReadPipe, &hOutWritePipe, NULL, 0);
	if (hInReadPipe == INVALID_HANDLE_VALUE || hInWritePipe == INVALID_HANDLE_VALUE ||
		hOutReadPipe == INVALID_HANDLE_VALUE || hOutWritePipe == INVALID_HANDLE_VALUE) {
		ShowLastError();
		result = false;
	}
	// ���������� ������� ����, ������� ����, ����������� ����������� 
	// � ������� ��� �������� ���� ��� �������� �� ����� ��������.
	STARTUPINFOA startInfo;
	ZeroMemory(&startInfo, sizeof(startInfo));
	startInfo.cb = sizeof(startInfo);		// ������������� ������ ���������, � ������.
	startInfo.hStdInput = hInReadPipe;		// ���������� ���������� ����� ��� ��������
	startInfo.hStdOutput = hOutWritePipe;		// ���������� ���������� ����� ��� ��������
	startInfo.hStdError = hOutWritePipe;		// ���������� ���������� ������ ��� ��������
	startInfo.dwFlags |= STARTF_USESTDHANDLES;
	// ��������������� ����������� ���� ������, ����������� ����� � ����������� ��������� ������ 
	// ������������ ��������, ������������ � ������ hStdInput, hStdOutput � hStdError
	PROCESS_INFORMATION procInfo;
	ZeroMemory(&procInfo, sizeof(procInfo));
	// ������������ �������
	LPSTR cmdLine = new CHAR[MAX_PATH];
	ZeroMemory(cmdLine, MAX_PATH);
	// a (Add) command
	strncpy(cmdLine, "7z.exe a ", MAX_PATH - strlen(cmdLine));
	strncat(cmdLine, archiveName, MAX_PATH - strlen(cmdLine));
	strncat(cmdLine, " ", MAX_PATH - strlen(cmdLine));
	strncat(cmdLine, fileName, MAX_PATH - strlen(cmdLine));
	strncat(cmdLine, " ", MAX_PATH - strlen(cmdLine));
	// ��������� ����� ������� � ��� ��������� (�������) �����. ����� ������� ��������� 
	// �������� ����������� ���� � ��������� ������������ ����������� ��������.
	if (!CreateProcessA(NULL, cmdLine, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS, NULL, NULL, &startInfo, &procInfo)) {
		ShowLastError();
		result = false;
	}
	if (result) {
		WaitForSingleObject(procInfo.hProcess, INFINITE);
		DWORD readBytes = 0;
		LPSTR outBuffer = new CHAR[bSize];
		ZeroMemory(outBuffer, bSize);
		OVERLAPPED overlapped;
		ReadFile(hOutReadPipe, outBuffer, bSize, &readBytes, &overlapped);
		CloseHandle(procInfo.hProcess);
		CloseHandle(procInfo.hThread);
	}
	CloseHandle(hOutReadPipe);
	CloseHandle(hOutWritePipe);
	CloseHandle(hInReadPipe);
	CloseHandle(hInWritePipe);
	return result;
}

bool unpack_files()
{
	bool result = true;
	LPSTR inputFileName = new CHAR[MAX_PATH];
	LPSTR outputFileName = new CHAR[MAX_PATH];
	printf("������� ���� � ������: ");
	scanf("%s", inputFileName);
	printf("������� ���� �� ������ ������� �����: ");
	scanf("%s", outputFileName);
	LPSTR cmdLine = new CHAR[MAX_PATH];
	ZeroMemory(cmdLine, MAX_PATH);
	strncpy(cmdLine, "7z.exe x ", MAX_PATH - strlen(cmdLine));
	strncat(cmdLine, inputFileName, MAX_PATH - strlen(cmdLine));
	strncat(cmdLine, " -o", MAX_PATH - strlen(cmdLine));
	strncat(cmdLine, outputFileName, MAX_PATH - strlen(cmdLine));
	strncat(cmdLine, " -y", MAX_PATH - strlen(cmdLine));
	STARTUPINFOA startInfo;
	ZeroMemory(&startInfo, sizeof(startInfo));
	startInfo.cb = sizeof(startInfo);
	startInfo.dwFlags |= STARTF_USESTDHANDLES;
	PROCESS_INFORMATION procInfo;
	ZeroMemory(&procInfo, sizeof(procInfo));
	if (!CreateProcessA(NULL, cmdLine, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS, NULL, NULL, &startInfo, &procInfo)) {
		ShowLastError();
		result = false;
	}
	return result;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int choice = 0;
	for (;;)
	{
		printf("1. ���������� ������ � �����\n2. �������� ������ ����� � ����� �����\n�������� ��������: ");
		cin >> choice;
		switch (choice)
		{
		case 1:
			if (unpack_files())
			{
				printf("\n���� ��� ������� ��������������.");
			}
			else
			{
				printf("\n������!");
			}
			break;
		case 2:
			if (pack_files())
			{
				printf("\n���� ��� ������� �����������");
			}
			else
			{
				printf("\n������!");
			}
			break;
		default:
			printf("������ �������� �� ����������\n");
			choice = 0;
			break;
		}

		system("\npause");
		system("cls");
	}
}