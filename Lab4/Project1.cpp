

#include "pch.h"

//#define DIV 1024
//#define WIDTH 7
//char divisor = 'K';
//
//using namespace std;
//
//void ShowLastError()
//{
//    LPVOID lpMsgBuf;
//    DWORD dw = GetLastError();
//    FormatMessage(
//        FORMAT_MESSAGE_ALLOCATE_BUFFER |
//        FORMAT_MESSAGE_FROM_SYSTEM |
//        FORMAT_MESSAGE_IGNORE_INSERTS,
//        NULL,
//        dw,
//        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//        (LPTSTR)&lpMsgBuf,
//        0, NULL);
//    _tprintf("%s", lpMsgBuf);
//
//    LocalFree(lpMsgBuf);
//}
//
//int _tmain(int args, char* argv[])
//{
//    setlocale(LC_CTYPE, "rus");
//    if (args == 2)
//    {
//        if (strcmp(argv[1], "-e")==0)
//        {
//            TCHAR str[100];
//            str[0] = '\0';
//            HANDLE hf = CreateFile(str, GENERIC_READ | GENERIC_WRITE,
//                FILE_SHARE_READ,
//                NULL,
//                OPEN_EXISTING,
//                FILE_ATTRIBUTE_NORMAL, NULL);
//            if (hf == INVALID_HANDLE_VALUE)
//            {
//                ShowLastError();
//            }
//        }
//        else if (strcmp(argv[1], "-s") == 0)
//        {
//            SYSTEM_INFO si;
//            MEMORYSTATUS sm;
//            GetSystemInfo(&si);
//            GlobalMemoryStatus(&sm);
//
//            cout << "Hardware information: \n" << endl;
//            printf("    OEM ID: %u\n", si.dwOemId);
//            printf("    Number of processors: %u\n", si.dwNumberOfProcessors);
//            printf("    Page size: %u\n", si.dwPageSize);
//            printf("    Processor type: %u\n", si.dwProcessorType);
//            printf("    Minimum application address: %lx\n", si.lpMinimumApplicationAddress);
//            printf("    Maximum application address: %lx\n", si.lpMaximumApplicationAddress);
//            printf("    Active processor mask: %u\n", si.dwActiveProcessorMask);
//            cout << endl;
//            printf("    The MemoryStatus structure is %ld bytes long.\n", sm.dwLength);
//            printf("    It should be %d.\n", sizeof(sm));
//            printf("    %ld percent of memory is in use.\n", sm.dwMemoryLoad);
//            printf("    There are %*ld total %sbytes of physical memory.\n", WIDTH, sm.dwTotalPhys / DIV, &divisor);
//            printf("    There are %*ld free %sbytes of physical memory.\n", WIDTH, sm.dwAvailPhys / DIV, &divisor);
//            printf("    There are %*ld total %sbytes of paging file.\n", WIDTH, sm.dwTotalPageFile / DIV, &divisor);
//            printf("    There are %*ld free %sbytes of paging file.\n", WIDTH, sm.dwAvailPageFile / DIV, &divisor);
//            printf("    There are %*lx total %sbytes of virtual memory.\n", WIDTH, sm.dwTotalVirtual / DIV, &divisor);
//            printf("    There are %*lx free %sbytes of virtual memory.\n", WIDTH, sm.dwAvailVirtual / DIV, &divisor);
//        }
//    }
//    system("pause");
//    return 0;
//}