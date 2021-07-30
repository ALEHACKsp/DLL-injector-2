#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include "conio.h"

char yol[MAX_PATH];
DWORD exe = 0;
std::uint32_t find_process(const std::string& name);
int inject();
using namespace std;
