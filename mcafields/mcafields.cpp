#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE   300
#define REQMAX    200
#define RESMAX    200

#define OPERATION    "operation id="
#define FMTDEF       "<fmtDef "
#define FSTRING      "<fStringAk"
#define FSTRINGARR   "<fString "
#define DATANAME     "dataName="
#define REQFMT       "RequestFmt"
#define REPLYFMT     "ReplyFmt"
#define ENDFMT       "/fmtDef"
#define SENDAND      "SendAnd"
#define ICOL         "<iCollF"
#define ICOLEND      "</iCollF"

// "hesapAcilisTrh"

char buf[MAXSIZE + 1];
struct MCADATA {
	char *name;
	int  ireq;
	int  reqtype[REQMAX];
	char *reqs[REQMAX];
	char rqdata[REQMAX];
	char *rqtype[REQMAX];
	int  rqlen[REQMAX];
	int  ires;
	int  resptype[RESMAX];
	char *resp[RESMAX];
	char rsdata[RESMAX];
	char *rstype[REQMAX];
	int  rslen[RESMAX];
} mca;

char* buyukHarf(char* s)
{
	if (*s >= 'a' && *s <= 'z')
		*s = (*s & 0xff) - 'a' + 'A';
	return s;
}

char *getname(char *s) 
{
	char *p1, *p = s;
	p1 = 0;
	while (*p != 0 && *p != '"') p++;
	if (p) {
		p++;
		p1 = p;
		while (*p != 0 && *p != '"') p++;
		*p = 0;
	}
	return p1;
}

void lookres(char *p, char *no)
{
	int i;
	for (i = 0; i < mca.ires; i++) {
		if (strcmp(mca.resp[i], p) == 0) {
			mca.resptype[i] = 0;
		}
	}
}
void savelen(char *p, int len)
{
	int i;
	for (i = 0; i < mca.ireq; i++) {
		if (strcmp(mca.reqs[i], p) == 0) {
			mca.rqlen[i] = len;
			break;
		}
	}
	for (i = 0; i < mca.ires; i++) {
		if (strcmp(mca.resp[i], p) == 0) {
			mca.rslen[i] = len;
			return;
		}
	}
}

void savetype(char *p, char *typ)
{
	int i;
	for (i = 0; i < mca.ireq; i++) {
		if (strcmp(mca.reqs[i], p) == 0) {
			mca.rqtype[i] = (char *)calloc(1, strlen(typ) + 1);
			strcpy(mca.rqtype[i],typ);
			break;
		}
	}
	for (i = 0; i < mca.ires; i++) {
		if (strcmp(mca.resp[i], p) == 0) {
			mca.rstype[i] = (char *)calloc(1, strlen(typ) + 1);
			strcpy(mca.rstype[i], typ);
			return;
		}
	}
}

int main(int argc, char *argv[])
{
	FILE *fp;
	char *p, *p1, *p2;
	int  i, param, end = 0, arr = 0;
	char *data;
	char fname[300];
	param = atoi(argv[1]);
	strcpy(fname, argv[2]);
	data = 0;
	if (param == 1) {
		fp = fopen(fname, "r");
		if (fp) {
			while (fgets(buf, MAXSIZE, fp)) {
				/*printf("buf (%s)\n", buf);*/
				if (strstr(buf, ENDFMT) && end == 1) {
					end = 0;
				}
				p = strstr(buf, OPERATION);
				if (p) {
					p = getname(p + strlen(OPERATION));
					p1 = strstr(p, "ServerOp");
					if (!p1) p1 = strstr(p, "ClientOp");
					*p1 = 0;
					mca.name = (char *)calloc(1, strlen(p) + 1);
					strcpy(mca.name, p);
					continue;
				}
				if (strstr(buf, FMTDEF)) {
					p = strstr(buf, REQFMT);
					if (p) data = "Q";
					p = strstr(buf, REPLYFMT);
					if (p) data = "A";
					p = strstr(buf, SENDAND);
					end = 1;
					if (p) {
						data = "S";
						end = 0;
					}
					continue;
				}
				if (strstr(buf, ICOL) && end == 1) {
					p = strstr(buf, DATANAME);
					if (p) {
						p1 = getname(p + strlen(DATANAME));
						if (*data == 'Q') {
							i = mca.ireq;
							mca.reqs[i] = (char *)calloc(1, strlen(p1) + 1);
							strcpy(mca.reqs[i], buyukHarf(p1));
							mca.rqdata[i] = 'I';
							mca.reqtype[i] = 3;
							mca.ireq++;
						}
						if (*data == 'A') {
							i = mca.ires;
							mca.resp[i] = (char *)calloc(1, strlen(p1) + 1);
							strcpy(mca.resp[i], buyukHarf(p1));
							mca.rsdata[i] = 'R';
							mca.resptype[i] = 3;
							mca.ires++;
						}
						arr = 1;
					}
				}
				if (end == 1 && arr == 1 && strstr(buf, FSTRING) || strstr(buf, FSTRINGARR)) {
					p = strstr(buf, DATANAME);
					if (p) {
						p1 = getname(p + strlen(DATANAME));
						if (*data == 'Q') {
							i = mca.ireq;
							mca.reqs[i] = (char *)calloc(1, strlen(p1) + 1);
							strcpy(mca.reqs[i], buyukHarf(p1));
							mca.rqdata[i] = 'I';
							mca.reqtype[i] = 4;
							mca.ireq++;
						}
						if (*data == 'A') {
							i = mca.ires;
							mca.resp[i] = (char *)calloc(1, strlen(p1) + 1);
							strcpy(mca.resp[i], buyukHarf(p1));
							mca.rsdata[i] = 'R';
							mca.resptype[i] = 4;
							mca.ires++;
						}
					}
				}
				if (end == 1 && arr == 0 && strstr(buf, FSTRING)) {
					p = strstr(buf, DATANAME);
					if (p) {
						p1 = getname(p + strlen(DATANAME));
						if (*data == 'Q'){
							i = mca.ireq;
							mca.reqs[i] = (char *)calloc(1, strlen(p1) + 1);
							strcpy(mca.reqs[i], buyukHarf(p1));
							mca.rqdata[i] = *data;
							mca.reqtype[i] = 2;
							mca.ireq++;
						}
						if (*data == 'A'){
							i = mca.ires;
							mca.resp[i] = (char *)calloc(1, strlen(p1) + 1);
							strcpy(mca.resp[i], buyukHarf(p1));
							mca.rsdata[i] = *data;
							mca.resptype[i] = 2;
							mca.ires++;
						}
					}
				}
				if (arr == 1 && strstr(buf, ICOLEND)) {
					arr = 0;
				}
				if (strstr(buf, "<fStringNonTTOHAk")) {
					p = strstr(buf, "dataName=");
					if (p) {
						p1 = p + 10;
						//p = strstr(p1, "\"");
						p = p1;
						while (*p != 0 && *p != '\"') p++;
						if (p) {
							*p = 0;
							p++;
						}
						else p = buf;
						// p1 element name
						if (strstr(p, "receive=\"No\"")) {
							lookres(p1, "No");
						}
						if (strstr(p, "format=")) {
							char ntype[20];
							int  ln;
							p2 = strstr(p, "format=");
							p2 = p2 + 8;
							p = p2;
							while (*p != 0 && *p != '\"') p++;
							ln = (int)(p - p2);
							strncpy(ntype, p2, ln);
							ntype[ln] = 0;
							savetype(p1, ntype);
						}
						if (strstr(p, "length=")) {
							char num[5];
							int  ln;
							p2 = strstr(p, "length=");
							p2 = p2 + 8;
							p = p2;
							while (*p != 0 && *p != '\"') p++;
							ln = (int)(p - p2);
							strncpy(num, p2, ln);
							num[ln] = 0;
							savelen(p1, atoi(num));
						}
					}
				}
			}
			fclose(fp);
			printf("1:Q:%sRequestFmt\n", mca.name);
			for (i = 0; i < mca.ireq; i++) {
				if (mca.rqtype[i] == 0) mca.rqtype[i] = "";
				if (mca.reqtype[i] == 3)
					printf("%d:%c:%s\n", mca.reqtype[i], mca.rqdata[i], mca.reqs[i]);
				if (mca.reqtype[i] > 0 && mca.rqlen[i] > 0)
					printf("%d:%c:%s:%d:%s\n", mca.reqtype[i], mca.rqdata[i], mca.reqs[i], mca.rqlen[i], mca.rqtype[i]);
			}
			printf("1:A:%sReplyFmt\n", mca.name);
			for (i = 0; i < mca.ires; i++) {
				if (mca.rstype[i] == 0) mca.rstype[i] = "";
				if (mca.resptype[i] == 3)
					printf("%d:%c:%s\n", mca.resptype[i], mca.rsdata[i], mca.resp[i]);
				if (mca.resptype[i] > 0 && mca.rslen[i] > 0)
					printf("%d:%c:%s:%d:%s\n", mca.resptype[i], mca.rsdata[i], mca.resp[i], mca.rslen[i], mca.rstype[i]);
			}
		}
		else printf("%s dosyasi bulunamadi\n", argv[2]);
	}
 else {
	 if (param == 2)
		 printf("MCA %s\n", argv[2]);
	 if (param == 3)
		 printf("VIEW %s\n", argv[2]);
 }
	return 0;
}

