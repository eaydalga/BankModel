#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSZ 300
#define NMAX  300
char tranid[6];
int  nproc;
char buf[BUFSZ];

int  ifields;
struct FIELDS {
	char *fname;
	int  fcount;
} fields[NMAX];

void saveName(char *p) {
	int  i;
	for (i = 0; i < ifields; i++) {
		if (strcmp(fields[i].fname, p) == 0) return;
	}
	i = ifields;
	ifields++;
	fields[i].fname = (char *)calloc(1, strlen(p) + 1);
	strcpy(fields[i].fname, p);
}

void params(int argc, char **argv)
{
	int i;
	for (i = 1; i < argc; i++) {
		printf("%d %s, ", i, argv[i]);
	}
	printf("\n");
}

int main(int argc, char* argv[])
{
	// ilk parametre tranId
	// Proc.xml sayisi
	// Proc.xml files
	// java files
	int  i, j;
	FILE *fp;
	char *p, *p1;
	if (argc > 2) {
		ifields = 0;
		strcpy(tranid, argv[1]);
		nproc = atoi(argv[2]);
		for (i = 0; i < nproc; i++) {
			fp = fopen(argv[i + 3], "r");
			if (fp) {
				while (fgets(buf, BUFSZ, fp)) {
					p = strstr(buf, "<fStringAk");
					if (p) {
						p1 = strstr(p, "dataName");
						if (p1) {
							while (*p1 != 0 && *p1 != '=') p1++;
							p1++;
							while (*p1 != 0 && *p1 != '"') p1++;
							p1++;
							p = p1;
							while (*p1 != 0 && *p1 != '"') p1++;
							*p1 = 0;
							saveName(p);
						}
					}
				}
				fclose(fp);
			}
			else {
				params(argc, argv);
				printf("proc file %s yok\n", argv[i + 3]);
				return 0;
			}
		}
		for (j = 0; j < ifields; j++) {
			for (i = nproc + 3; i < argc; i++) {
				fp = fopen(argv[i], "r");
				if (fp) {
					while (fgets(buf, BUFSZ, fp)) {
						if (strstr(buf, fields[j].fname)) {
							fields[j].fcount++;
							break;
						}
					}
					fclose(fp);
				}
				else {
					params(argc, argv);
					printf("java file %s yok\n", argv[i]);
					return 0;
				}
			}
		}
		for (i = 0; i < ifields; i++) {
			if (fields[i].fcount != 0)
				printf("%s=%d\n", fields[i].fname, fields[i].fcount);
		}
	}
	else {
		params(argc, argv);
		printf("usage modelServer <tranId> <procxmlNo> <procxmlfiles>... <javafiles>\n");
	}
	return 0;
}

