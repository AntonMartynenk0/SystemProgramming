#include "pch.h"
//
//using namespace std;
//
//HANDLE semaphore;
//
//DWORD WINAPI thread_function(LPVOID param)
//{
//	int* params = (int*)param;
//	clock_t start = clock();
//	int thread_number = params[0];
//	LPSTR str = new CHAR[128];
//
//	DWORD result = WaitForSingleObject(semaphore, 500);
//	while (result != WAIT_OBJECT_0)
//	{
//		result = WaitForSingleObject(semaphore, 1000);
//		printf("Thread number %i waiting for semaphore\n", thread_number);
//	}
//
//	printf("Thread number %i decrement semaphore. Going to sleep\n", thread_number);
//
//	Sleep(params[1] * 1000);
//
//	HANDLE file = CreateFileA("work_result.txt", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
//	if (file == INVALID_HANDLE_VALUE)
//	{
//		ReleaseSemaphore(semaphore, 1, NULL);
//		return 0;
//	}
//	SetFilePointer(file, 0, NULL, FILE_END);
//
//	clock_t finish = clock();
//	float time_elapsed = (finish - start) / CLK_TCK;
//
//	sprintf(str, "Thread number %i: %f sec\n\0", thread_number, time_elapsed);
//	WriteFile(file, str, strlen(str), NULL, NULL);
//	CloseHandle(file);
//
//	printf("Thread number %i released semaphore.\n", thread_number);
//	ReleaseSemaphore(semaphore, 1, NULL);
//	return 0;
//}
//
//int getRandValue(int min, int max)
//{
//	return min + rand() % (max + 1 - min);
//}
//
//int main()
//{
//	int max_handles;
//	int max_threads;
//	srand(time(NULL));
//	printf("Input max number of handles : ");
//	scanf("%i", &max_handles);
//
//	printf("Input max number of threads : ");
//	scanf("%i", &max_threads);
//
//	//Создание семафора
//	HANDLE* threads = new HANDLE[max_threads];
//	semaphore = CreateSemaphoreA(NULL, max_handles, max_handles, "MySemaphore");
//	if (semaphore == NULL) {
//		printf("Error of creating the semaphore");
//		system("pause");
//		return 0;
//	}
//
//	//Создание файла
//	HANDLE file = CreateFileA("work_result.txt", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
//	if (file == INVALID_HANDLE_VALUE)
//	{
//		CloseHandle(file);
//		return 0;
//	}
//	CloseHandle(file);
//
//	for (int i = 0; i < max_threads; i++)
//	{
//		int* params = new int[2];
//		params[0] = i; //Количество потоков
//		params[1] = getRandValue(1, 5); //Время сна.
//
//		threads[i] = CreateThread(
//			NULL, // дескриптор защиты
//			0, // начальный размер стека
//			thread_function, // функция потока
//			(LPVOID)params, // параметры потока
//			NULL, // опции создания
//			NULL);// идентификатор потока
//	}
//	WaitForMultipleObjects(max_threads, threads, TRUE, INFINITE);
//	return 0;
//}