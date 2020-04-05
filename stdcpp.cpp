#include "stdio.h"
#include <windows.h>
#include <iostream>
#include <string.h>
#include <cstring>
using namespace std;

#pragma warning(disable:4996)

int main() {
	string strMapName("ShareMemory");
	string strComData("This is common data!");
	LPVOID pBuffer;

	HANDLE hMap = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, (LPCSTR)strMapName.c_str());
	if (NULL == hMap) {
		hMap = ::CreateFileMapping(INVALID_HANDLE_VALUE,
			NULL,
			PAGE_READWRITE,
			0,
			strComData.length() + 1,
			(LPCSTR)strMapName.c_str());
		pBuffer = ::MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		strcpy((char*)pBuffer, strComData.c_str());
		cout << "写入共享内存数据:" << (char*)pBuffer << endl;
	}
	else {
		pBuffer = ::MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		cout << "读取共享内存数据: " << (char*)pBuffer << endl;
	}
	getchar();
	::UnmapViewOfFile(pBuffer);
	::CloseHandle(hMap);
	system("pause");
	return 0;
}

