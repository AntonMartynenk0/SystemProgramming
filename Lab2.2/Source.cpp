#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <locale.h>
#include <iostream>
using namespace std;

void changeCurrDir()//������� ������� ����������
{
    printf("������� ���� � ����� ����������: \n");
    char path[MAX_PATH];
    scanf_s("%s", path, MAX_PATH);
    if (SetCurrentDirectoryA((LPCSTR)path))
    {
        if (GetCurrentDirectoryA(MAX_PATH, path) != 0)
        {
            printf("���������� ������� ��������!\n");
            system("pause");
        }
        else
        {
            printf("������! \n");
            system("pause");
            exit(1);
        }
    }
    else
    {
        printf("������! \n");
        system("pause");
    }
}
void printCurrDir()//���������� ������� ����������
{
    WIN32_FIND_DATAA file;
    HANDLE hf;
    char path[MAX_PATH];

    if (GetCurrentDirectoryA(MAX_PATH, path) != 0)
    {
        system("cls");
        strcat(path, "//*");
        hf = FindFirstFileA(path, &file);//����� ������� �����
        if (hf == INVALID_HANDLE_VALUE)
        {
            printf("������!\n");
            system("Pause");
            return;
        }
        else {
            do
            {
                if (file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                    printf("�����: ");
                else
                    printf("����: ");
                printf("  %s\n", file.cFileName);
                SYSTEMTIME time;
                FileTimeToSystemTime(&file.ftCreationTime, &time);
                printf("\t�������: %02d-%02d-%d %02d:%02d:%02d \n", time.wMonth, time.wDay, time.wYear, time.wHour, time.wMinute, time.wSecond);
                printf("\t������: %dB\n", file.nFileSizeLow);
                printf("\n");

            } while (FindNextFileA(hf, &file));
            system("Pause");
            FindClose(hf);
        }
    }
    else
    {
        printf("Error! \n");
        system("pause");
        exit(1);
    }


}
void copyFile()
{
    char old_path[MAX_PATH];
    char new_path[MAX_PATH];
    system("cls");
    printf("������� ���� � �����:\n");
    scanf_s("%s", old_path, MAX_PATH);
    printf("������� ����� ��� ����� � ���� ��� ����������:\n");
    scanf_s("%s", new_path, MAX_PATH);
    if (CopyFileA((LPCSTR)old_path, (LPCSTR)new_path, FALSE))
    {
        printf("���� ������� ����������!\n");
    }
    else
    {
        printf("�� ������� ����������� ����!\n");
    }
    system("Pause");
}
void createNewDir()//������� ����� ����������
{
    char path[MAX_PATH];
    system("cls");
    printf("������� ���� ��� �������� ����� ����������:\n");
    scanf_s("%s", path, MAX_PATH);
    if (CreateDirectoryA((LPCSTR)path, NULL))
    {
        printf("���������� �������!\n");
    }
    else
    {
        printf("�� ������� ������� ����� ����������!\n");
    }
    system("pause");
}
void deleteFile()
{
    char path[MAX_PATH];
    system("cls");
    printf("������� ���� � �����:\n");
    scanf_s("%s", path, MAX_PATH);
    if (DeleteFileA(path))
    {
        printf("���� ������� �����!\n");
    }
    else
    {
        printf("�� ������� ������� ����!\n");
    }
    system("pause");
}
void deleteDirectory()
{
    char path[MAX_PATH];
    system("cls");
    printf("������� ���� � ����������:\n");
    scanf_s("%s", path, MAX_PATH);
    if (RemoveDirectoryA(path))
    {
        printf("���������� ������� �������!\n");
    }
    else
    {
        printf("�� ������� ������� ����������!\n");
    }
    system("pause");
}
void fileInfo()
{
    char path[MAX_PATH];
    system("cls");
    printf("������� ���� � �����:\n");
    scanf_s("%s", path, MAX_PATH);
    BY_HANDLE_FILE_INFORMATION fileInfo;
    SYSTEMTIME time;
    HANDLE file = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, NULL,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        if (GetFileInformationByHandle(file, &fileInfo))
        {
            SYSTEMTIME time;
            FileTimeToSystemTime(&fileInfo.ftCreationTime, &time);
            printf("\t������: %dB\n", fileInfo.nFileSizeLow);
            FileTimeToSystemTime(&(fileInfo.ftCreationTime), &time);
            printf("\t������: %02d-%02d-%d %02d:%02d:%02d\n", time.wMonth, time.wDay, time.wYear, time.wHour, time.wMinute, time.wSecond);
            FileTimeToSystemTime(&(fileInfo.ftLastAccessTime), &time);
            printf("\t��������� �������������: %02d-%02d-%d %02d:%02d:%02d\n",time.wMonth, time.wDay, time.wYear, time.wHour, time.wMinute, time.wSecond);
            FileTimeToSystemTime(&(fileInfo.ftLastWriteTime), &time);
            printf("\t��������� ���������: %02d-%02d-%d %02d:%02d:%02d\n", time.wMonth, time.wDay, time.wYear, time.wHour, time.wMinute, time.wSecond);
            printf("\t����� ������: %d\n", fileInfo.nNumberOfLinks);
        }
        else
        {
            printf("�� ������� �������� ���������� � �����!\n");
        }
    system("pause");
    CloseHandle(file);
}

int main(void)
{
    setlocale(LC_ALL, "Russian");
    char path[MAX_PATH];
    strcpy(path, "C://");
    while (true)
    {
        system("cls");//������� �������
        if (GetCurrentDirectoryA(MAX_PATH, path) != 0)
        {
            printf("������� ����������: %s\n", path);
        }
        else
        {
            printf("������!\n");
            exit(1);
        }
        printf("\n");
        printf("1. ������� ����������\n");
        printf("2. ����������� ����������\n");
        printf("3. ����������� ����\n");
        printf("4. ������� ����������\n");
        printf("5. ������� ����\n");
        printf("6. ������� ���������� (������ ����������)\n");
        printf("7. ���������� � �����\n");
        printf("8. �����\n");

        int key = 0;
        cin >> key;
        switch (key)
        {
        case 1:
            changeCurrDir(); break;
        case 2:
            printCurrDir(); break;
        case 3:
            copyFile(); break;
        case 4:
            createNewDir(); break;
        case 5:
            deleteFile(); break;
        case 6:
            deleteDirectory(); break;
        case 7:
            fileInfo(); break;
        case 8:
            return 0;
        default:
            printf("������ �����!\n");
            break;
        }
    }
}