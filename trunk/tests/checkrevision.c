#include <stdio.h>
#include <windows.h>

typedef unsigned int uint32_t;

typedef int (__stdcall *check_revision_t)(const char*, const char**, int, int, unsigned long*);
typedef int (__stdcall *exe_info_t)(const char*, char*, size_t, uint32_t*, int);
typedef int (__stdcall *ver_info_t)(char*);
typedef int (__stdcall *set_debug_t)(int);

int main(int argc, char* argv[])
{
	HMODULE lib;
	check_revision_t check_revision;
	exe_info_t exe_info;
	ver_info_t ver_info;
	set_debug_t set_debug;
	const char* paths[] = {
		"BNCSutil.dll",
		"BNCSutil_1.1.dll"
	};
	int has_debug[] = { 1, 0 };
	unsigned long checksum = 0;
	uint32_t version = 0;
	char exeInfo[1024];
	const unsigned long expectedChecksum = 0x98214637;
	int i;
	char lib_version[12];

	const char formula[] =
		"A=767237111 B=654373374 C=621868803 4 A=A+S B=B-C C=C-A A=A+B";

	for (i = 0; i < 2; i++) {
		lib = LoadLibrary(paths[i]);
		if (!lib) {
			printf("Failed to load \"%s\"\n", paths[i]);
			continue;
		}

		if (has_debug[i]) {
			set_debug = (set_debug_t) GetProcAddress(lib, "bncsutil_set_debug_status");
			set_debug(0);
		}
		
		ver_info = (ver_info_t) GetProcAddress(lib, "bncsutil_getVersionString");
		check_revision = (check_revision_t) GetProcAddress(lib, "checkRevision");
		exe_info = (exe_info_t) GetProcAddress(lib, "getExeInfo");

		ver_info(lib_version);
		printf("Using BNCSutil %s:\n", lib_version);

		if (!check_revision(formula, (argv + 1), (argc - 1), 7, &checksum)) {
			printf("\tCheckRevision call failed.\n");
			continue;
		}
		printf("\tChecksum:  0x%08X\n", checksum);

		if (!exe_info(argv[1], exeInfo, 1024, &version, 1)) {
			printf("\tGetExeInfo call failed.\n");
			continue;
		}
		printf("\tVersion:   0x%08X\n", version);
		printf("\t%s\n", exeInfo);

		FreeLibrary(lib);
	}
	
	return 0;
}
