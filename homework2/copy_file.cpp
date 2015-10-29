#include "stdafx.h"
#include "iostream"
#include "fstream"
#include "time.h"
#include "time.h"
#include "windows.h"
#include "winbase.h"

using namespace std;

void __cdecl _tmain(int argc, TCHAR *argv[])
{
	clock_t start, end;
	int pause;
	
	DWORD totalBytes = 0;
	DWORD actualBytesRead;
	long buffSize;
	buffSize = _tcstol(argv[1], NULL, 10);

	char   * readBuffer = new char[buffSize];
	HANDLE hFile, hFile2;
	hFile = CreateFile(argv[2],
		GENERIC_READ, 
		FILE_SHARE_READ,    
		NULL,                  
		OPEN_EXISTING,         
		FILE_ATTRIBUTE_NORMAL, 
		NULL);                 

	hFile2 = CreateFile(argv[3],            
		GENERIC_WRITE,          
		FILE_SHARE_WRITE,       
		NULL,                 
		OPEN_ALWAYS,         
		FILE_ATTRIBUTE_NORMAL, 
		NULL);

	BOOL endOfFile = TRUE;
	start = clock();
	while (endOfFile != FALSE)
	{
		ReadFile(hFile, readBuffer, buffSize, &actualBytesRead, NULL);
		totalBytes += actualBytesRead;
		endOfFile = (actualBytesRead > 0);
			if (endOfFile == TRUE) {
			WriteFile(hFile2, readBuffer, actualBytesRead, NULL, NULL);
		}
	}
	end = clock();
	double totalTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	cout << "Copied " << totalBytes << " bytes in " << totalTime << " seconds " <<
		" at the rate of " << static_cast<double>(totalBytes) / totalTime << " bytes per second." << " Buffer size is: " << buffSize << std::endl;
	
	CloseHandle(hFile);
	CloseHandle(hFile2);
	delete[] readBuffer;
}
