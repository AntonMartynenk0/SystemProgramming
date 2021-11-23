#include <iostream>
#include <windows.h>


using namespace std;
int main()
{
	setlocale(LC_CTYPE, "rus");
	struct sample {
		int a;
		char b;
		long c;
		short d;
		char* e;
	};
	cout << sizeof(sample)<<endl;


	cout << "|  Тип данных\t|Размер |           Диапазон           |" << endl;
	cout << "|BOOL" << "\t\t|   " << sizeof(BOOL) << "   | 0 ... 1\t\t       |" << endl;
	cout << "|BOOLEAN" << "\t|   " << sizeof(BOOLEAN) << "   | 0 ... 1\t\t       |" << endl;
	cout << "|BYTE" << "\t\t|   " << sizeof(BYTE) << "   | " << 0 << "..." << MAXBYTE << "\t\t       |" << endl;
	cout << "|SHORT" << "\t\t|   " << sizeof(SHORT) << "   | " << -1 * (MINSHORT) << "..." << MAXSHORT << "\t       |" << endl;
	cout << "|USHORT" << "\t\t|   " << sizeof(USHORT) << "   | " << "0" << "..." << MAXSHORT << "\t\t       |" << endl;
	cout << "|INT" << "\t\t|   " << sizeof(INT) << "   | " << -1 * MININT << "..." << MAXINT << "     |" << endl;
	cout << "|DOUBLE" << "\t\t|   " << sizeof(DOUBLE) << "   | " << -DBL_MIN << "..." << DBL_MAX << " |" << endl;
	cout << "|FLOAT" << "\t\t|   " << sizeof(FLOAT) << "   | " << -FLT_MIN << "..." << FLT_MAX << "   |" << endl;
	cout << "|LONG" << "\t\t|   " << sizeof(LONG) << "   | -" << MINLONG << "..." << MAXLONG << "     |" << endl;
	cout << "|ULONG" << "\t\t|   " << sizeof(ULONG) << "   | " << 0 << "..." << ULLONG_MAX << "     |" << endl;
	cout << "|UINT" << "\t\t|   " << sizeof(UINT) << "   | " << "0" << "..." << MAXUINT << "\t       |" << endl;
	cout << "|UINT8" << "\t\t|   " << sizeof(UINT8) << "   | " << "0" << "..." << (int)MAXUINT8 << "\t\t       |" << endl;
	cout << "|UINT16" << "\t\t|   " << sizeof(UINT16) << "   | " << "0" << "..." << MAXUINT16 << "\t\t       |" << endl;
	cout << "|CHAR" << "\t\t|   " << sizeof(CHAR) << "   | " << -1 * (MINCHAR) << "..." << MAXCHAR << "\t\t       |" << endl;
	cout << "|WCHAR" << "\t\t|   " << sizeof(WCHAR) << "   | " << -1 * (WCHAR_MIN) << "..." << WCHAR_MAX << "\t\t       |" << endl;
	cout << "|TCHAR" << "\t\t|   " << sizeof(TCHAR) << "   | " << "..." << "\t\t\t       |" << endl;
	cout << "|WORD" << "\t\t|   " << sizeof(WORD) << "   | " << "..." << "\t\t\t       |" << endl;
	cout << "|DWORD" << "\t\t|   " << sizeof(DWORD) << "   | " << "..." << "\t\t\t       |" << endl;
	cout << "|HANDLE" << "\t\t|   " << sizeof(HANDLE) << "   | " << "..." << "\t\t\t       |" << endl;
	cout << "|HINSTANCE" << "\t|   " << sizeof(HINSTANCE) << "   | " << "..." << "\t\t\t       |" << endl;
	cout << "|HMODULE" << "\t|   " << sizeof(HMODULE) << "   | " << "..." << "\t\t\t       |" << endl;
	cout << "|LPSTR" << "\t\t|   " << sizeof(LPSTR) << "   | " << "..." << "\t\t\t       |" << endl;
	cout << "|LPCSTR" << "\t\t|   " << sizeof(LPCSTR) << "   | " << "..." "\t\t\t       |" << endl;
	cout << "|LPWSTR" << "\t\t|   " << sizeof(LPWSTR) << "   | " << "..." "\t\t\t       |" << endl;
	cout << "|LPCWSTR" << "\t|   " << sizeof(LPCWSTR) << "   | " << "..." "\t\t\t       |" << endl;
	cout << "|LPTSTR" << "\t\t|   " << sizeof(LPTSTR) << "   | " << "..." "\t\t\t       |" << endl;
	cout << "|LPCTSTR" << "\t|   " << sizeof(LPCTSTR) << "   | " << "..." "\t\t\t       |" << endl;
	return 0;
}