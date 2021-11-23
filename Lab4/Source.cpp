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
	printf("Введите путь к файлу для архивации:");
	scanf("%s", fileName);
	LPSTR archiveName = new CHAR[MAX_PATH];
	printf("Введите путь куда хотите поместить архив: ");
	scanf("%s", archiveName);
	// Создание анонимного канала
	HANDLE hInReadPipe;
	HANDLE hInWritePipe;
	HANDLE hOutReadPipe;
	HANDLE hOutWritePipe;
	CreatePipe(
		&hInReadPipe,  //адрес переменной, куда будет записан идентификатор канала для чтения данных                             
		&hInWritePipe, //адрес переменной, куда будет записан идентификатор канала для записи данных              
		NULL,	       //адрес переменной для атрибутов защиты 
		0);	       //количество байт памяти, зарезервированной для канала 
	CreatePipe(&hOutReadPipe, &hOutWritePipe, NULL, 0);
	if (hInReadPipe == INVALID_HANDLE_VALUE || hInWritePipe == INVALID_HANDLE_VALUE ||
		hOutReadPipe == INVALID_HANDLE_VALUE || hOutWritePipe == INVALID_HANDLE_VALUE) {
		ShowLastError();
		result = false;
	}
	// Определяет станцию окна, рабочий стол, стандартные дескрипторы 
	// и внешний вид главного окна для процесса во время создания.
	STARTUPINFOA startInfo;
	ZeroMemory(&startInfo, sizeof(startInfo));
	startInfo.cb = sizeof(startInfo);		// Устанавливает размер структуры, в байтах.
	startInfo.hStdInput = hInReadPipe;		// определяет дескриптор ввода для процесса
	startInfo.hStdOutput = hOutWritePipe;		// определяет дескриптор ввода для процесса
	startInfo.hStdError = hOutWritePipe;		// определяет дескриптор ошибки для процесса
	startInfo.dwFlags |= STARTF_USESTDHANDLES;
	// Устанавливается стандартный ввод данных, стандартный вывод и стандартная обработка ошибок 
	// дескрипторов процесса, определенных в членах hStdInput, hStdOutput и hStdError
	PROCESS_INFORMATION procInfo;
	ZeroMemory(&procInfo, sizeof(procInfo));
	// Формирование команды
	LPSTR cmdLine = new CHAR[MAX_PATH];
	ZeroMemory(cmdLine, MAX_PATH);
	// a (Add) command
	strncpy(cmdLine, "7z.exe a ", MAX_PATH - strlen(cmdLine));
	strncat(cmdLine, archiveName, MAX_PATH - strlen(cmdLine));
	strncat(cmdLine, " ", MAX_PATH - strlen(cmdLine));
	strncat(cmdLine, fileName, MAX_PATH - strlen(cmdLine));
	strncat(cmdLine, " ", MAX_PATH - strlen(cmdLine));
	// Создается новый процесс и его первичный (главный) поток. Новый процесс запускает 
	// заданный исполняемый файл в контексте безопасности вызывающего процесса.
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
	printf("Введите путь к архиву: ");
	scanf("%s", inputFileName);
	printf("Введите куда вы хотите извлечь файлы: ");
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
		printf("1. Распаковка архива в папку\n2. Упаковка одного файла в новый архив\nВыберите действие: ");
		cin >> choice;
		switch (choice)
		{
		case 1:
			if (unpack_files())
			{
				printf("\nФайл был успешло разархивирован.");
			}
			else
			{
				printf("\nОшибка!");
			}
			break;
		case 2:
			if (pack_files())
			{
				printf("\nФайл был успешло архивирован");
			}
			else
			{
				printf("\nОшибка!");
			}
			break;
		default:
			printf("Такого действия не существует\n");
			choice = 0;
			break;
		}

		system("\npause");
		system("cls");
	}
}