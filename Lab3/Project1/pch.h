﻿// pch.h: это предварительно скомпилированный заголовочный файл.
// Перечисленные ниже файлы компилируются только один раз, что ускоряет последующие сборки.
// Это также влияет на работу IntelliSense, включая многие функции просмотра и завершения кода.
// Однако изменение любого из приведенных здесь файлов между операциями сборки приведет к повторной компиляции всех(!) этих файлов.
// Не добавляйте сюда файлы, которые планируете часто изменять, так как в этом случае выигрыша в производительности не будет.

#ifndef PCH_H
#define PCH_H
#define _CRT_SECURE_NO_WARNINGS
#include <typeinfo>
#include <windows.h>
#include <locale.h> 
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <tchar.h>
#include <vector>
#include <stdio.h>
#include <Windows.h>
#include <time.h>

#pragma comment(lib, "user32.lib")
// Добавьте сюда заголовочные файлы для предварительной компиляции

#endif //PCH_H