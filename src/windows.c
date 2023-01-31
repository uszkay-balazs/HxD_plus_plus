#include <windows.h>
#include <stdio.h>



#define NONE		"\x1b[m"
#define ULINE		"\x1b[4m"
#define RED			"\x1b[31m"
#define GREEN		"\x1b[32m"
#define BLUE		"\x1b[34m"
#define YELLOW		"\x1b[33m"
#define ORANGE		"\x1b[38;5;208m"

#define UERROR 		"["RED"ERROR"NONE"]   "		/* 'ERROR' in red */
#define UWARNING 	"["ORANGE"WARNING"NONE"] "	/* 'WARNING' in orange */
#define UINFO 		"["BLUE"INFO"NONE"]    "	/* 'INFO' in blue */
#define USUCCESS	"["GREEN"SUCCESS"NONE"] "	/* 'SUCCESS' in green */

int main(int argc, char** argv) {
	if (argc < 2) {
		printf(UERROR"Not enough arguments provided\n");
		return 1;
	} else if (argc > 2) printf(UWARNING"Too many arguments provided, ignored %d\n", argc - 2);
	

	// Open this file for reading and writing (ie. editing)
	HANDLE FileHandle = CreateFileA(argv[1],
				GENERIC_READ | GENERIC_WRITE,
				0,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
	if (FileHandle == INVALID_HANDLE_VALUE){
		unsigned long error = GetLastError();
		printf_s(UERROR"File '%s' could not be opened (error code %lu/0x%lx)\n", argv[1], error);
		return 1;
	} else printf_s(UINFO"File '%s' has been opened\n", argv[1]);

	unsigned long FileSize;
	if (GetFileSize(FileHandle, &FileSize) == 0){
		unsigned long error = GetLastError();
		printf_s(UERROR"GetFileSize failed (error code %lu/0x%lx)\n", error, error);
		CloseHandle(FileHandle);
		return 1;
	}

	unsigned long BufferSize = FileSize + 1;
	char* FileBuffer = (char*) malloc(BufferSize * sizeof(char));
	unsigned long bytesRead = 0;
	if (ReadFile(FileHandle, FileBuffer, BufferSize-1, &bytesRead, NULL) == 0
		|| bytesRead != BufferSize - 1 ){
		unsigned long error = GetLastError();
		printf_s(UERROR"File read failed (error code %lu/0x%lx)\n", error, error);
		CloseHandle(FileHandle);
		return 1;
	} else printf_s(UINFO"File '%s' has been read successfully\n", argv[1]);

	

	unsigned long BytesWritten;
	if (WriteFile(FileHandle, FileBuffer, BufferSize - 1, &BytesWritten, NULL) == 0 
		|| BytesWritten != BufferSize - 1){
		unsigned long error = GetLastError();
		printf_s(UERROR"File '%s' could not be written (error code %lu/0x%lx)\n", argv[1], error, error);
		CloseHandle(FileHandle);
		return 1;
	} else printf_s(UINFO"File '%s' has been written successfully\n", argv[1]);
	CloseHandle(FileHandle);
	return 0;
}
