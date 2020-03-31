#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <time.h>
#include <windows.h>
#include <tlhelp32.h>
using namespace std;
#pragma comment(linker,"/subsystem:windows /entry:mainCRTStartup")
typedef struct letter {
	int a = -1;
	struct letter* letters[26];
}letr;
HMODULE GetCurrentModule();
LRESULT CALLBACK KeyboardProc(int nCode,WPARAM wParam,LPARAM lParam);
void initial(letr *a,letr *b);
void circle(string word);
bool programState(char* name);

HHOOK mHook;
MSG mMsg;
HWND mHWND;
letr o, *mark = &o;
string source[200];
letr a[888];

int ordinal = 0;
int why = 0;

int main(int argc, char *argv[]) {
	if (programState(argv[0]))
		return 0;

	ifstream mFile("C:\\ProgramData\\上帝之手.txt");
	if (!mFile)
		MessageBox(GetForegroundWindow(), "您的根文件有误", "错误", MB_OK);
	mFile.close();
}

bool programState(char* name) {
	char* exeName = NULL;
	char* p = strtok(name, "\\");
	while (p != NULL) {
		exeName = p;
		p = strtok(NULL, "\\");
	}

	PROCESSENTRY32 pe32;
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pe32.dwSize = sizeof(pe32);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		MessageBox(GetForegroundWindow(),"CreateToolhelp32Snapshot failed!\n","Error!",MB_OK);
		return false;
	}
	BOOL bMore = ::Process32First(hProcessSnap, &pe32);
	int num = -1;
	while (bMore)
		if (!_tcscmp(exeName, pe32.szExeFile))
		{
			num++;
			if (num == 1) {
				MessageBox(GetForegroundWindow(), "Already Running!", "Error!", MB_OK);
				return false;
			}
		}
		else
			bMore = ::Process32Next(hProcessSnap, &pe32);
	return true;
}
