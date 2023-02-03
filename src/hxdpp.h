#include <stdio.h>
#include <stdint.h>
#include <windows.h>
#include <fileapi.h>

typedef uint64_t u64;

typedef struct __Editor {
	u64 cursor_pos;
	u64 cursor_x, cursor_y;

	u64 lines_size, lines_cap;
	char** lines;

	u64 data_size, data_cap;
	char* data;
} Editor;

