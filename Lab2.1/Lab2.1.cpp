// Records.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
using namespace std;

const char FILE_NAME[] = "records.txt";

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
		printf("%s", lpMsgBuf);

	LocalFree(lpMsgBuf);
}

struct RECORD {
	int record_number;
	FILETIME creation;
	char text[81];
	int counter;
};

struct HEADER {
	int not_empty_record_count;
	int file_size;
};

void init_records(int init_num) {
	if (init_num > 0) {
		HANDLE hFile = CreateFileA(FILE_NAME, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		RECORD r;
		SYSTEMTIME system_time, system_time2;
		FILETIME file_time;
		HEADER header_information;
		header_information.not_empty_record_count = 0;
		header_information.file_size = sizeof(RECORD) * init_num + sizeof(header_information);
		GetLocalTime(&system_time);
		SystemTimeToFileTime(&system_time, &file_time);
		FileTimeToSystemTime(&file_time, &system_time2);
		r.counter = 0; r.creation = file_time; strcpy(r.text, "");
		if (hFile != INVALID_HANDLE_VALUE) {
			SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
			WriteFile(hFile, &header_information, sizeof(HEADER), NULL, NULL);
			SetFilePointer(hFile, NULL, NULL, FILE_END);
			for (int i = 0; i < init_num; i++) {
				r.record_number = i;
				WriteFile(hFile, &r, sizeof(RECORD), NULL, NULL);
			}
			CloseHandle(hFile);
		}
		else {
			ShowLastError();
		}
	}
}

HEADER get_header_info() {
	HEADER header_information;
	DWORD bytes;
	HANDLE hFile = CreateFileA(FILE_NAME, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE) {
		SetFilePointer(hFile, NULL, NULL, FILE_BEGIN);
		ReadFile(hFile, &header_information, sizeof(HEADER), &bytes, NULL);
		CloseHandle(hFile);
		printf("Header information\n");
		printf("Размер файла в байтах: %d\nКол-во ненулевых записей: %d\n", header_information.file_size, header_information.not_empty_record_count);
		return header_information;
	}
	else {
		ShowLastError();
	}
}

vector<RECORD> get_records_info(int count) {
	vector<RECORD> records(0);
	RECORD r; 
	DWORD bytes;
	HANDLE hFile = CreateFileA(FILE_NAME, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE) {
		SetFilePointer(hFile, sizeof(HEADER), NULL, FILE_BEGIN);
		do {
			ReadFile(hFile, &r, sizeof(RECORD), &bytes, NULL);
			records.push_back(r);
		} while (bytes != 0);
		SYSTEMTIME systemTime;
		printf("\t|  №  |\tДата и время создания |\tКол-во измений\t| Текст\n");
		for (int i = 0; i < count; i++) {
			printf("\t|  %d  |\t", records[i].record_number);
			FileTimeToSystemTime(&records[i].creation, &systemTime);
			printf("%d.%02d.%02d  %02d.%02d.%02d  |\t", systemTime.wYear, systemTime.wMonth, systemTime.wDay, systemTime.wHour, systemTime.wMinute, systemTime.wSecond);
			printf("%d \t\t| ", records[i].counter);
			printf("%s\n", records[i].text);
		}
		CloseHandle(hFile);
	}
	else {
		ShowLastError();
	}
	return records;
}

void deleteRecord(int count) {
	HEADER h = get_header_info();
	vector <RECORD> records = get_records_info(count);
	SYSTEMTIME systemTime;
	int id;
	printf("Введите индекс записи для удаления:");
	scanf("%d", &id);
	if (id >= 0 && id < count) {
		strcpy(records[id].text, "");
		h.not_empty_record_count--;
		records[id].counter = 0;
		FileTimeToSystemTime(&records[id].creation, &systemTime);
		HANDLE hFile = CreateFileA(FILE_NAME, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		SetFilePointer(hFile, NULL, NULL, FILE_BEGIN);
		WriteFile(hFile, &h, sizeof(HEADER), NULL, NULL);
		SetFilePointer(hFile, NULL, NULL, FILE_END);
		for (int i = 0; i < count; i++)
			WriteFile(hFile, &records[i], sizeof(RECORD), NULL, NULL);
		CloseHandle(hFile);
	}
	else {
		printf("Такой записи не существует");
	}
}

void editRecord(int count) {
	vector <RECORD> records = get_records_info(count);
	HEADER h = get_header_info();
	SYSTEMTIME systemTime;
	int id;
	printf("Input id to modify :");
	scanf("%d", &id);
	if (id >= 0 && id < count) {
		printf("Введите 80 символов без пробелов");
		scanf("%s", records[id].text);
		h.not_empty_record_count++;
		records[id].counter++;
		FileTimeToSystemTime(&records[id].creation, &systemTime);
		HANDLE hFile = CreateFileA(FILE_NAME, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		SetFilePointer(hFile, NULL, NULL, FILE_BEGIN);
		WriteFile(hFile, &h, sizeof(HEADER), NULL, NULL);
		SetFilePointer(hFile, NULL, NULL, FILE_END);
		for (int i = 0; i < count; i++)
			WriteFile(hFile, &records[i], sizeof(RECORD), NULL, NULL);
		CloseHandle(hFile);
	}
	else {
		printf("Такой записи не существует");
	}
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	if (argc != 2) {
		printf("Неверный аргумент!\n");
	}
	else {
		int key = 0;
			int num = atoi(argv[1]);
			init_records(num);
		while (true)
		{
			system("cls");
			printf("1. Удалить запись\n2. Изменить запись\n3. Показать все записи\n4. Выход\nВыберите действие:");
			cin>> key;
			switch (key)
			{
			case 1:
				system("cls");
				deleteRecord(num);
				system("pause");
				break;
			case 2:
				system("cls");
				editRecord(num);
				system("pause");
				break;
			case 3:
				system("cls");
				get_header_info();
				get_records_info(num);
				system("pause");
				break;
			case 4:
				return 0;
			default:
				printf("Неизвестное действие!");
				system("pause");
				break;
			}
		}
	}
	return 0;
}