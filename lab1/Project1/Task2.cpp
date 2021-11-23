#include "pch.h"
#define BUF_SIZE 4096

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

int _tmain(int args, char* argv[])
{
    setlocale(LC_CTYPE, "rus");
    CHAR stra[BUF_SIZE] = {};
    WCHAR strw[BUF_SIZE] = {};
    BOOL bRes;
    DWORD dwRead, dwWrite;
    if (args == 2)
    {
        if (strcmp(argv[1], "-a") == 0)//ANSI файл в Юникод
        {
            HANDLE hf = CreateFile("ansi.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            if (hf == INVALID_HANDLE_VALUE)
            {
                ShowLastError();
            }
            else
            {
                HANDLE hf2 = CreateFile("unicode.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
                if (hf2 == INVALID_HANDLE_VALUE)
                {
                    ShowLastError();
                }
                else {
                    do {
                        if (ReadFile(hf, (LPVOID)stra, sizeof(CHAR) * BUF_SIZE, &dwRead, NULL))
                        {
                            int chum2 = MultiByteToWideChar(CP_ACP, 0, stra, dwRead / sizeof(CHAR), strw, BUF_SIZE);
                            cout << chum2 << endl;
                            cout << stra << endl;
                            WriteFile(hf2, (LPVOID)stra, chum2, &dwWrite, NULL);
                        }
                    } while (dwRead == BUF_SIZE);
                    CloseHandle(hf2);
                }
                CloseHandle(hf);
            }
        }
        else if (strcmp(argv[1], "-u") == 0)//Юникод файл в ANSI
        {
            HANDLE hf = CreateFile("unicode.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            if (hf == INVALID_HANDLE_VALUE)
            {
                ShowLastError();
            }
            else
            {
                HANDLE hf2 = CreateFile("ansi.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
                if (hf2 == INVALID_HANDLE_VALUE)
                {
                    ShowLastError();
                }
                else
                {
                    do {
                        if (ReadFile(hf, (LPVOID)strw, sizeof(WCHAR) * BUF_SIZE, &dwRead, NULL))
                        {
                            int chum2 = WideCharToMultiByte(GetACP(), 0, strw, dwRead / sizeof(WCHAR), stra, BUF_SIZE, "?", &bRes);
                            cout << chum2 << endl;
                            cout << stra << endl;
                            WriteFile(hf2, stra, chum2, &dwWrite, NULL);
                        }
                    } while (dwRead == BUF_SIZE);
                    FlushFileBuffers(hf2);
                    CloseHandle(hf2);
                }
                CloseHandle(hf);
            }
        }
    }
    system("pause");
    return 0;
}