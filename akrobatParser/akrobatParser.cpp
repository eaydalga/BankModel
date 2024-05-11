#pragma warning(suppress : 4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#define INMAX 300
#define MAXBTN 400

char bfx[MAXBTN + 1];

void rmnl(char* bf)
{
	int len = strlen(bf);
	if (bf[len - 1] == '\n') { bf[len - 1] = 0; len--; }
	if (bf[len - 1] == '\r') { bf[len - 1] = 0; len--; }
	if (bf[len - 1] == '\n') { bf[len - 1] = 0; len--; }
}

int turkce(char* p)
{
	int i, len, var = 0;
	len = strlen(p);
	if (strstr(p, "ç")) var = 1;
	if (strstr(p, "ö")) var = 1;
	if (strstr(p, "þ")) var = 1;
	if (strstr(p, "ý")) var = 1;
	if (strstr(p, "ð")) var = 1;
	if (strstr(p, "ü")) var = 1;
	if (strstr(p, "Ç")) var = 1;
	if (strstr(p, "Ö")) var = 1;
	if (strstr(p, "Þ")) var = 1;
	if (strstr(p, "Ý")) var = 1;
	if (strstr(p, "Ð")) var = 1;
	if (strstr(p, "Ü")) var = 1;
	if (var == 0) {
		for (i = 0; i < len; i++) {
			if (i == 0 && (p[i] >= 'a' && p[i] <= 'z') ||
				(p[i] >= 'A' && p[i] <= 'Z')) continue;
			else var = 1;
			if(i && (p[i] >= 'a' && p[i] <= 'z') || 
			   (p[i] >= '0' && p[i] <= '9') ||
			   (p[i] >= 'A' && p[i] <= 'Z') ||
			   (p[i] >= '_')) continue;
			else var = 1;
		}
	}
	if (var == 1)
		wprintf((wchar_t*)"Türkçe Karakter, yalnýþ symbol var: state id %hs\n", p);
	return var;
}



void checkId(FILE *fp, char *bfx)
{
	char *p, *p1;
	char bufx[400];
	int  err;
	strcpy(bufx, bfx);
	p = strstr(bfx, "id=");
	if (p) {
		p = p + 3;
		if (*p == '"')
			p++;
		p1 = strstr(p, "\"");
		if (p1) {
			*p1 = 0;
		}
		err = turkce(p);
	}
}

void checkEntry(FILE *fp, char *bfx)
{
	char* p, * p1;
	char bufx[401];
	int  err, buttonList = 0, condAction = 0;
	while (fgets(bufx, 400, fp)) {
		if (strstr(bufx, "</entryActions>"))
			break;
		if (strstr(bufx, "<setValue")) {

		}
		if (strstr(bufx, "<openViewAk")) {

		}
		if (strstr(bufx, "<executeOperationActAk ")) {

		}	
		if (strstr(bufx, "<buttonList>")) {
			buttonList = 1;
		}
		if (strstr(bufx, "<footerButton") && buttonList) {
			if (strstr(bufx, "</footerButton"))
				buttonList = 0;
		}
		if (strstr(bufx, "<initColl")) {
		}
		if (strstr(bufx, "<conditionAction>")) {
			condAction = 1;
		}
		if (strstr(bufx, "<conditions") && condAction) {
			if (strstr(bufx, "</conditions"))
				condAction = 0;
		}
		if (strstr(bufx, "<compositeCondition")) {
		}
		
		if (strstr(bufx, "changeState(") && condAction) {
		}
		if (strstr(bufx, "onTrue") && condAction) {
		}
		if (strstr(bufx, "onFalse") && condAction) {
		}
	}
}

void checkTrans(FILE *fp, char *bfx)
{
	char* p, * p1;
	char bufx[400];
	int  err;
	while (fgets(bufx, 400, fp)) {
		if (strstr(bufx, "</transitions>"))
			break;
		if (strstr(bufx, "<transition")) {
		}
		if (strstr(bufx, "<actions")) {
		}
		if (strstr(bufx, "<closeViewA")) {
		}
		if (strstr(bufx, "targetState=\"")) {
		}
		
	}
}

int readProc(int param, char *tranname, char* area, char* hdir)
{
	char prefs[INMAX], prefsfile[INMAX], prefsfile1[INMAX];
	FILE* fp;
	char* ProcFiles, *err;
	WIN32_FIND_DATAA ffd;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	ProcFiles = (char*)"Proc.xml";
	sprintf(prefsfile, "%s\\INDIRS\\%s\\*", hdir, tranname);
	sprintf(prefsfile1, "%s\\INDIRS\\%s\\", hdir, tranname);
	hFind = FindFirstFileA(prefsfile, &ffd);
	if (hFind == INVALID_HANDLE_VALUE) {
		fprintf(stderr, "%s directory read error\n", prefsfile);
		return 1003;
	}
	do {
		if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
			if (strstr((char*)ffd.cFileName, ProcFiles)) {
				strcpy(prefs, prefsfile1);
				strcat(prefs, (char*)ffd.cFileName);
				fp = fopen(prefs, "r");
				if (fp) {
					while (fgets(bfx, MAXBTN, fp)) {
						rmnl(bfx);
						if (strlen(bfx) < 2) continue;
						if (strstr(bfx, "<!")) continue;
						if (strstr(bfx, "<state ")) {
							checkId(fp, bfx);
						}
						if (strstr(bfx, "<entryActions>")) {
							checkEntry(fp, bfx);
						}
		  			    if (strstr(bfx, "<transitions>")) {
							checkTrans(fp, bfx);
						}
					}
					fclose(fp);
				}
			}
		}
	} while(FindNextFileA(hFind, &ffd) != 0);
}

int readJava(int param, char* tranname, char* area, char* hdir)
{
	char prefs[INMAX], prefsfile[INMAX], prefsfile1[INMAX];
	int  ret, i, uniq = 0, xx;
	char tsmodel[INMAX], filename[INMAX];

	char pbuf[INMAX];
	FILE* fp;
	WIN32_FIND_DATAA ffd;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	char* ViewFields, * p;

	ViewFields = (char*)".java";

	// C:\Users\Caydalga\Desktop\Bankalar\converter\INDIRS
	sprintf(prefsfile1, "%s\\INDIRS\\%s\\", hdir, tranname);
	sprintf(prefsfile, "%s\\INDIRS\\%s\\*", hdir, tranname);
	hFind = FindFirstFileA(prefsfile, &ffd);
	if (hFind == INVALID_HANDLE_VALUE) {
		fprintf(stderr, "%s directory read error\n", prefsfile);
		return 1003;
	}
	do {
		if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
			if (strstr((char*)ffd.cFileName, ViewFields)) {
				strcpy(prefs, prefsfile1);
				strcat(prefs, (char*)ffd.cFileName);
				fp = fopen(prefs, "r");
				if (fp) {
					while (fgets(bfx, MAXBTN, fp)) {
					}
					fclose(fp);
				}
			}
		}
	} while (FindNextFileA(hFind, &ffd) != 0);
}
