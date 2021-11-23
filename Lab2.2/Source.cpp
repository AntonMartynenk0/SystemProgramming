#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <locale.h>
#include <iostream>
using namespace std;

void changeCurrDir()//сменить текущую директорию
{
    printf("введите путь к новой директории: \n");
    char path[MAX_PATH];
    scanf_s("%s", path, MAX_PATH);
    if (SetCurrentDirectoryA((LPCSTR)path))
    {
        if (GetCurrentDirectoryA(MAX_PATH, path) != 0)
        {
            printf("Директория успешно изменена!\n");
            system("pause");
        }
        else
        {
            printf("Ошибка! \n");
            system("pause");
            exit(1);
        }
    }
    else
    {
        printf("Ошибка! \n");
        system("pause");
    }
}
void printCurrDir()//распечатка текущей директории
{
    WIN32_FIND_DATAA file;
    HANDLE hf;
    char path[MAX_PATH];

    if (GetCurrentDirectoryA(MAX_PATH, path) != 0)
    {
        system("cls");
        strcat(path, "//*");
        hf = FindFirstFileA(path, &file);//поиск первого файла
        if (hf == INVALID_HANDLE_VALUE)
        {
            printf("Ошибка!\n");
            system("Pause");
            return;
        }
        else {
            do
            {
                if (file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                    printf("Папка: ");
                else
                    printf("Файл: ");
                printf("  %s\n", file.cFileName);
                SYSTEMTIME time;
                FileTimeToSystemTime(&file.ftCreationTime, &time);
                printf("\tСоздано: %02d-%02d-%d %02d:%02d:%02d \n", time.wMonth, time.wDay, time.wYear, time.wHour, time.wMinute, time.wSecond);
                printf("\tРазмер: %dB\n", file.nFileSizeLow);
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
    printf("Введите путь к файлу:\n");
    scanf_s("%s", old_path, MAX_PATH);
    printf("Введите новое имя файла и путь его размещения:\n");
    scanf_s("%s", new_path, MAX_PATH);
    if (CopyFileA((LPCSTR)old_path, (LPCSTR)new_path, FALSE))
    {
        printf("Файл успешно скопирован!\n");
    }
    else
    {
        printf("Не удалось скопировать файл!\n");
    }
    system("Pause");
}
void createNewDir()//Создать новую директорию
{
    char path[MAX_PATH];
    system("cls");
    printf("Введите путь для создания новой директории:\n");
    scanf_s("%s", path, MAX_PATH);
    if (CreateDirectoryA((LPCSTR)path, NULL))
    {
        printf("Директория создана!\n");
    }
    else
    {
        printf("Не удалось создать новую директорию!\n");
    }
    system("pause");
}
void deleteFile()
{
    char path[MAX_PATH];
    system("cls");
    printf("Укажите путь к файлу:\n");
    scanf_s("%s", path, MAX_PATH);
    if (DeleteFileA(path))
    {
        printf("Файл успешно удалён!\n");
    }
    else
    {
        printf("Не удалось удалить файл!\n");
    }
    system("pause");
}
void deleteDirectory()
{
    char path[MAX_PATH];
    system("cls");
    printf("Укажите путь к директории:\n");
    scanf_s("%s", path, MAX_PATH);
    if (RemoveDirectoryA(path))
    {
        printf("Директория удалена успешно!\n");
    }
    else
    {
        printf("Не удалось удалить директорию!\n");
    }
    system("pause");
}
void fileInfo()
{
    char path[MAX_PATH];
    system("cls");
    printf("Укажите путь к файлу:\n");
    scanf_s("%s", path, MAX_PATH);
    BY_HANDLE_FILE_INFORMATION fileInfo;
    SYSTEMTIME time;
    HANDLE file = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, NULL,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        if (GetFileInformationByHandle(file, &fileInfo))
        {
            SYSTEMTIME time;
            FileTimeToSystemTime(&fileInfo.ftCreationTime, &time);
            printf("\tРазмер: %dB\n", fileInfo.nFileSizeLow);
            FileTimeToSystemTime(&(fileInfo.ftCreationTime), &time);
            printf("\tСоздан: %02d-%02d-%d %02d:%02d:%02d\n", time.wMonth, time.wDay, time.wYear, time.wHour, time.wMinute, time.wSecond);
            FileTimeToSystemTime(&(fileInfo.ftLastAccessTime), &time);
            printf("\tПоследнее использование: %02d-%02d-%d %02d:%02d:%02d\n",time.wMonth, time.wDay, time.wYear, time.wHour, time.wMinute, time.wSecond);
            FileTimeToSystemTime(&(fileInfo.ftLastWriteTime), &time);
            printf("\tПоследнее изменение: %02d-%02d-%d %02d:%02d:%02d\n", time.wMonth, time.wDay, time.wYear, time.wHour, time.wMinute, time.wSecond);
            printf("\tЧисло связей: %d\n", fileInfo.nNumberOfLinks);
        }
        else
        {
            printf("Не удалось получить информацию о файле!\n");
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
        system("cls");//очистка консоли
        if (GetCurrentDirectoryA(MAX_PATH, path) != 0)
        {
            printf("Текущая директория: %s\n", path);
        }
        else
        {
            printf("Ошибка!\n");
            exit(1);
        }
        printf("\n");
        printf("1. Сменить директорию\n");
        printf("2. Распечатать директорию\n");
        printf("3. Скопировать файл\n");
        printf("4. Создать директорию\n");
        printf("5. Удалить файл\n");
        printf("6. Удалить директорию (пустую директорию)\n");
        printf("7. Информация о файле\n");
        printf("8. Выход\n");

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
            printf("Ошибка ввода!\n");
            break;
        }
    }
}