#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <locale.h>
#define ARRAY_MAX 200000

CRITICAL_SECTION section;
int* array;

DWORD WINAPI thread_get_min(LPVOID use_critical_section);
DWORD WINAPI thread_get_max(LPVOID use_critical_section);
DWORD WINAPI thread_get_avg(LPVOID use_critical_section);

int getRandValue(int min, int max)
{
    return min + rand() % (max + 1 - min);
}

void arrayFilling(int* array)
{
    for (int i = 0; i < ARRAY_MAX; i++)
    {
        array[i] = getRandValue(0, 100);
    }
}


int main()
{
    setlocale(LC_CTYPE, "rus");
    HANDLE* threads;
    clock_t start;
    float elapsed_time;
    srand(time(NULL));
    InitializeCriticalSection(&section);

    array = new int[ARRAY_MAX];
    arrayFilling(array);

    start = clock();
    threads = new HANDLE[3];
    threads[0] = CreateThread(NULL, 0, thread_get_min, (LPVOID)TRUE, NULL, NULL);
    threads[1] = CreateThread(NULL, 0, thread_get_avg, (LPVOID)TRUE, NULL, NULL);
    threads[2] = CreateThread(NULL, 0, thread_get_max, (LPVOID)TRUE, NULL, NULL);
    WaitForMultipleObjects(3, threads, TRUE, INFINITE);

    for (int i = 0; i < 3; i++)
    {
        CloseHandle(threads[i]);
    }
    elapsed_time = ((float)(clock() - start)) / CLK_TCK;
    printf("Runtime with critical section is %f sec\n\n", elapsed_time);

    start = clock();
    threads = new HANDLE[3];
    threads[0] = CreateThread(NULL, 0, thread_get_min, (LPVOID)FALSE, NULL, NULL);
    threads[1] = CreateThread(NULL, 0, thread_get_avg, (LPVOID)FALSE, NULL, NULL);
    threads[2] = CreateThread(NULL, 0, thread_get_max, (LPVOID)FALSE, NULL, NULL);
    WaitForMultipleObjects(3, threads, TRUE, INFINITE);
    for (int i = 0; i < 3; i++)
    {
        CloseHandle(threads[i]);
    }
    elapsed_time = ((float)(clock() - start)) / CLK_TCK;
    printf("Runtime without critical section is %f sec\n\n", elapsed_time);

    DeleteCriticalSection(&section);
}

DWORD WINAPI thread_get_min(LPVOID use_critical_section)
{
    if ((bool)use_critical_section)
    {
        while (!TryEnterCriticalSection(&section))
        {
        }
    }

    int min = array[0];
    for (int i = 0; i < ARRAY_MAX; i++)
    {
        if (min > array[i])
            min = array[i];
    }
    printf("Minimum: %i\n", min);

    if ((bool)use_critical_section)
    {
        LeaveCriticalSection(&section);
    }

    return 0;
}

DWORD WINAPI thread_get_max(LPVOID use_critical_section)
{
    if ((bool)use_critical_section)
    {
        while (!TryEnterCriticalSection(&section))
        {
        }
    }

    int max = array[0];
    for (int i = 0; i < ARRAY_MAX; i++)
    {
        if (max < array[i])
            max = array[i];
    }
    printf("Maximum: %i\n", max);

    if ((bool)use_critical_section)
    {
        LeaveCriticalSection(&section);
    }

    return 0;
}

DWORD WINAPI thread_get_avg(LPVOID use_critical_section)
{
    if ((bool)use_critical_section)
    {
        while (!TryEnterCriticalSection(&section))
        {
        }
    }

    float avg = 0;
    for (int i = 0; i < ARRAY_MAX; i++)
    {
        avg += array[i];
    }
    printf("Average: %f\n", avg / ARRAY_MAX);

    if ((bool)use_critical_section)
    {
        LeaveCriticalSection(&section);
    }

    return 0;
}