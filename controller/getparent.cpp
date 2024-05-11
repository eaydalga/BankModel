#include <Windows.h>
#include <stdio.h>
#include <tlHelp32.h>
// #include <Psapi.h>
#include <stdlib.h>


DWORD getParentPID(DWORD pid)
{
	HANDLE h = NULL;
	PROCESSENTRY32 pe = { 0 };
	DWORD ppid = 0;
	pe.dwSize = sizeof(PROCESSENTRY32);
	h = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (Process32First(h, &pe)) {
		do {
			if (pe.th32ProcessID == pid) {
				ppid = pe.th32ParentProcessID;
				break;
			}
		} while (Process32Next(h, &pe));
	}
	// CloseHandle(h);
	return (ppid);
}

int bakBakalim(char *p, int procId)
{
	DWORD pid, ppid;
	pid = GetCurrentProcessId();
	ppid = getParentPID(pid);
	// e = getProcessName(ppid, (PUCHAR)fname, MAX_PATH);
	if (procId == ppid || procId == 12)
		return 1;
	fprintf(stderr, "Error*** hmm yetki sorunu %s\n", p);
	return 0;
}