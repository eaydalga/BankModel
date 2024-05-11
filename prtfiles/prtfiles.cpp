// prtfields.cpp : Defines the entry point for the application.
//
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FDEF    "<fmtDef>"
#define FRECORD "<fRecordReport "
#define FNAME   "printMedia="
#define DNAME   "docName="

#define FROW    "<fReportRow "
#define RW      "rw="
#define RLABEL  "<fReportLabel "
#define LABEL   "label="
#define COL     "col="
#define RITEM   "<fReportItem "
#define DATANAME "dataName="
#define FMT		 "fmt="
#define LEN		 "len="
#define ALIGN	 "align="
#define PREC	 "precision="
#define ID       "id="
#define FILLCHAR "fillChar="
#define ENDLINE  "/>"
#define ENDFRECORD "</fRecordReport"
#define ENDFROW  "</fReportRow"
#define ENDDEF   "</fmtDef>"

#define RHEADER "<fRegionPageHeader>"
#define ERHEADER "</fRegionPageHeader>"
#define REGIONDATA "<fRegionData "
#define EREGIONDATA "</fRegionData>"
#define REGIONBREAK "<fRegionBreak "
#define EREGIONBREAK "</fRegionBreak>"

#define FRECEIPTLABEL "<fReceiptLabel "
#define FRECEIPTITEM "<fReceiptItem "

#define FRECEIPT "<fRecordReceipt "
#define FRROW    "<fRow "
#define FRECITEM  "<fReceiptItem "
#define FRECLABEL "<fReceiptLabel "
#define ERROW    "</fRow>"
#define FFILENAME  "fileName=\""
#define ENDFRECEIPT "</fRecordReceipt"

#define FUNCTION  "function="
#define ONCHANGE  "onChange="
#define PAGEBREAK "pageBreak="
#define USEBREAK  "useBreakPart="

#define ICOL      "iCol="

#define BMAX 2000
char  buf[BMAX + 1];

char tranname[200];

FILE* fx;

struct LINE {
	char* label;
	int labelcol;
	char* dataName;
	int datacol;
	char* fmt; // date IBAN normal KK gibi
	int len;
	int prec;
	int align;
};

struct PROW {
	int rw;
	int irline;
	struct LINE rline[20];
};

int iprt;
struct PRT {
	int  prttype;
	char* docName;
	char* fileName;
	int   iprow;
	struct PROW prow[200];
};
struct PRT prt[4];

int iregheaders;
struct REGHEADER {
	int iheader;
	int headers[100];
} regheaders[3];

int iregdata;
struct REGDATA {
	char* regdname;
	char* regchange;
	char* regusebrk;
	int regbreak;
	int regfunc;
	int iregdatas;
	int regdatas[5];
} regdata[3];

int iregbreak;
struct REGBREAK {
	int iregbrk;
	struct REGBRK {
		char* icol;
		char* id;
		int  ibrkrow;
		int  brkrow[30];
	} regbrk[2];
} regbreak[5];

char brkid[200];
char brkcol[200];

void rmnl(char* bf)
{
	int len = (int)strlen(bf);
	if (bf[len - 1] == '\n') { bf[len - 1] = 0; len--; }
	if (bf[len - 1] == '\r') { bf[len - 1] = 0; len--; }
	if (bf[len - 1] == '\n') { bf[len - 1] = 0; len--; }
}

char* params(char* pbf, char* retval, char* ss)
{
	char* p, * p1, * p2, sbuf[BMAX + 1];
	strcpy(sbuf, pbf);
	p = pbf;
	p1 = strstr(p, ss);
	if (p1) {
		p1 = p1 + strlen(ss);
		while (*p1 && *p1 == ' ') p1++;
		if (*p1 == '\"') {
			p1++;
			p2 = p1;
		}
		else p2 = p1;
		while (*p1 && *p1 != '\"') p1++;
		if (*p1 == '\"') {
			*p1 = 0;
		}
		strcpy(retval, p2);
	}
	else retval = 0;
	strcpy(pbf, sbuf);
	return pbf;
}
#define RECEIPT 2
#define REPORT  1

void prtline(FILE* fx, int i, int j)
{
	int line;
	for (line = 0; line < prt[i].prow[j].irline; line++) {
		if (prt[i].prow[j].rline[line].label) {
			fprintf(fx, " :row=%d:type=%s:label=%s:col=%d\n", 
				prt[i].prow[j].rw, "LABEL",
				prt[i].prow[j].rline[line].label,
				prt[i].prow[j].rline[line].labelcol);
		}
		if (prt[i].prow[j].rline[line].dataName) {
			fprintf(fx, " :row=%d:type=%s:name=%s:col=%d ", 
				prt[i].prow[j].rw, "DATA",
				prt[i].prow[j].rline[line].dataName,
				prt[i].prow[j].rline[line].datacol);
			if (prt[i].prow[j].rline[line].fmt)
				fprintf(fx, ":fmt=%s", prt[i].prow[j].rline[line].fmt);
			if (prt[i].prow[j].rline[line].align)
				fprintf(fx, ":align=%d", prt[i].prow[j].rline[line].align);
			if (prt[i].prow[j].rline[line].len)
				fprintf(fx, ":len=%d", prt[i].prow[j].rline[line].len);
			if (prt[i].prow[j].rline[line].prec)
				fprintf(fx, ":prec=%d", prt[i].prow[j].rline[line].prec);
			fprintf(fx, "\n");
		}
	}
}

int main(int argc, char** argv)
{
	FILE* fp;
	int   i, j, param, setcomment;
	int  setflag, setheader, setdata, setbreak;
	int   line;
	char* pbuf, * p;
	char fname[300];
	char hdir[300], fbuf[200];
	char dname[200], dfunc[20], dchange[20], dpage[20], duse[50];
	param = atoi(argv[1]);
	if (param >= 1 && param <= 3) {
		iprt = 0;
		// fx = stdout;
		strcpy(tranname, argv[2]);
		strcpy(hdir, argv[3]);
		fp = fopen(argv[4], "r");
		if (fp) {
			setcomment = 0;
			while (fgets(buf, BMAX, fp)) {
				rmnl(buf);
				pbuf = buf;
				if (strstr(pbuf, "/*")) {
					setcomment = 1;
					if (strstr(pbuf, "*/")) {
						setcomment = 0;
						pbuf = strstr(pbuf, "*/");
						pbuf += 2;
					}
					else continue;
				}
				if (strstr(pbuf, "*/") && setcomment) {
					setcomment = 0;
					pbuf = strstr(pbuf, "*/");
					pbuf += 2;
				}
				if (strstr(pbuf, RHEADER)) {
					setheader = 1;
					setdata = 0;
					setbreak = 0;
				}
				if (strstr(pbuf, ERHEADER))
					setheader = 0;
				if (strstr(pbuf, REGIONDATA)) {
					setheader = 0;
					setdata = 1;
					setbreak = 0;
					p = strstr(pbuf, REGIONDATA);
					if (p) {
						p = p + strlen(REGIONDATA);
						p = params(p, dname, (char*)DATANAME);
						p = params(p, dfunc, (char*)FUNCTION);
						p = params(p, dchange, (char*)ONCHANGE);
						p = params(p, dpage, (char*)PAGEBREAK);
						p = params(p, duse, (char*)USEBREAK);
					}
					else {
						dname[0] = 0;
						duse[0] = 0;
						strcpy(dfunc, "False");
						strcpy(dchange, "XXX");
						strcpy(dpage, "False");
					}
				}
				if (strstr(pbuf, EREGIONDATA))
					setdata = 0;
				if (strstr(pbuf, REGIONBREAK)) {
					setheader = 0;
					setdata = 0;
					setbreak = 1;
					p = strstr(pbuf, REGIONBREAK);
					if (p) p = p + strlen(REGIONBREAK);
					p = params(p, brkcol, (char*)ICOL);
					p = params(p, brkid, (char*)ID);
				}
				if (strstr(pbuf, EREGIONBREAK))
					setbreak = 0;
				if (strstr(pbuf, FRECEIPT) || strstr(pbuf, FRECORD)) {
					char  fname[200], dname[200];
					p = strstr(pbuf, FRECEIPT);
					if (p) {
						p = p + strlen(FRECEIPT);
						p = params(p, fname, (char*)FFILENAME);
						p = params(p, dname, (char*)DNAME);
						setflag = RECEIPT;
					}
					else {
						p = strstr(pbuf, FRECORD);
						if (p) {
							p = p + strlen(FRECORD);
							p = params(p, fname, (char*)FNAME);
							p = params(p, dname, (char*)DNAME);
							setflag = REPORT;
						}
					}
					i = iprt;
					prt[i].prttype = setflag;
					param = setflag;
					prt[i].fileName = (char*)calloc(1, strlen(fname) + 1);
					prt[i].docName = (char*)calloc(1, strlen(dname) + 1);
					prt[i].iprow = 0;
					strcpy(prt[i].fileName, fname);
					strcpy(prt[i].docName, dname);
				}
				if (strstr(pbuf, ENDFRECEIPT) || strstr(pbuf, ENDFRECORD)) {
					iprt++;
					if (setflag == REPORT) {
						iregheaders++;
						iregdata++;
						iregbreak++;
					}
				}
				if (strstr(pbuf, FROW) || strstr(pbuf, FRROW)) {
					char row[10];
					i = iprt;
					j = prt[i].iprow;
					p = strstr(pbuf, FROW);
					if (p) {
						p = p + strlen(FROW);
					}
					else {
						p = strstr(pbuf, FRROW);
						p = p + strlen(FRROW);
					}
					p = params(p, row, (char*)RW);
					prt[i].prow[j].rw = atoi(row);
					prt[i].prow[j].irline = 0;
				}
				if (strstr(pbuf, ENDFROW) || strstr(pbuf, ERROW)) {
					i = iprt;
					j = prt[i].iprow;
					if (setflag == REPORT) {
						int ii, ij, ik;
						if (setheader) {
							ii = iregheaders;
							ij = regheaders[ii].iheader;
							regheaders[ii].headers[ij] = j;
							regheaders[ii].iheader++;
						}
						if (setdata) {
							ii = iregdata;
							if (dname[0]) {
								regdata[ii].regdname = (char*)calloc(1, strlen(dname) + 1);
								strcpy(regdata[ii].regdname, dname);
							}
							else regdata[ii].regdname = 0;
							regdata[ii].regchange= (char*)calloc(1, strlen(dchange) + 1);
							strcpy(regdata[ii].regdname, dchange);
							if (strcmp(dfunc, "False") == 0)
								regdata[ii].regfunc = 0;
							else regdata[ii].regfunc = 1;
							if (strcmp(dpage, "False") == 0)
								regdata[ii].regbreak = 0;
							else regdata[ii].regbreak = 1;
							if (duse[0]) {
								regdata[ii].regusebrk = (char*)calloc(1, strlen(duse) + 1);
								strcpy(regdata[ii].regusebrk, duse);
							}
							else regdata[ii].regusebrk = 0;
							ij = regdata[ii].iregdatas;
							regdata[ii].regdatas[ij] = j;
							regdata[ii].iregdatas++;
						}
						if (setbreak) {
							ii = iregbreak;
							ij = regbreak[ii].iregbrk;
							if (brkcol) {
								regbreak[ii].regbrk[ij].icol = (char*)calloc(1, strlen(brkcol) + 1);
								strcpy(regbreak[ii].regbrk[ij].icol, brkcol);
							}
							if (brkid) {
								regbreak[ii].regbrk[ij].id = (char*)calloc(1, strlen(brkid) + 1);
								strcpy(regbreak[ii].regbrk[ij].id, brkid);
							}
							ik = regbreak[ii].regbrk[ij].ibrkrow;
							regbreak[ii].regbrk[ij].brkrow[ik] = j;
							regbreak[ii].regbrk[ij].ibrkrow++;
							regbreak[ii].iregbrk++;
						}
					}
					prt[i].iprow++;
				}
				if (strstr(pbuf, RLABEL) || strstr(pbuf, FRECLABEL)) {
					char col[100], lab[200];
					i = iprt;
					j = prt[i].iprow;
					p = strstr(pbuf, RLABEL);
					if (p) p = p + strlen(RLABEL);
					else {
						p = strstr(pbuf, FRECLABEL);
						p = p + strlen(FRECLABEL);
					}
					p = params(p, lab, (char*)LABEL);
					p = params(p, col, (char*)COL);
					line = prt[i].prow[j].irline;
					prt[i].prow[j].rline[line].label = (char*)calloc(1, strlen(lab) + 1);
					strcpy(prt[i].prow[j].rline[line].label, lab);
					prt[i].prow[j].rline[line].labelcol = atoi(col);
					prt[i].prow[j].irline++;
				}
				if (strstr(pbuf, RITEM) || strstr(pbuf, FRECITEM)) {
					char data[200], col[100], fmt[200];
					char lenstr[200], align[100], prec[200];
					i = iprt;
					j = prt[i].iprow;
					p = strstr(pbuf, RITEM);
					if (p) p = p + strlen(RITEM);
					else {
						p = strstr(pbuf, FRECITEM);
						p = p + strlen(FRECITEM);
					}
					p = params(p, data, (char*)DATANAME);
					p = params(p, col, (char*)COL);
					p = params(p, fmt, (char*)FMT);
					p = params(p, lenstr, (char*)LEN);
					p = params(p, align, (char*)ALIGN);
					p = params(p, prec, (char*)PREC);
					line = prt[i].prow[j].irline;
					prt[i].prow[j].rline[line].dataName = (char*)calloc(1, strlen(data) + 1);
					if (prt[i].prow[j].rline[line].dataName)
						strcpy(prt[i].prow[j].rline[line].dataName, data);
					prt[i].prow[j].rline[line].datacol = atoi(col);
					prt[i].prow[j].rline[line].fmt = (char*)calloc(1, strlen(fmt) + 1);
					if (prt[i].prow[j].rline[line].fmt)
						strcpy(prt[i].prow[j].rline[line].fmt, fmt);
					if (lenstr) {
						prt[i].prow[j].rline[line].len = atoi(lenstr);
					}
					if (align) {
						prt[i].prow[j].rline[line].align = atoi(align);
					}
					if (prec) {
						prt[i].prow[j].rline[line].prec = atoi(prec);
					}
					prt[i].prow[j].irline++;
				}
			}
			fclose(fp);
			iprt++;
		}
		strcpy(fname, hdir);
		strcat(fname, "\\prefs\\");
		strcat(fname, tranname);
		strcat(fname, "\\");
		strcat(fname, tranname);
		sprintf(fbuf, "%sprinter%d.pref", fname, param);
		fx = fopen(fbuf, "w");
		if (fx) {
			for (i = 0; i < iprt; i++) {
				fprintf(fx, "%d:\"%s\":%s\n", prt[i].prttype, prt[i].fileName, prt[i].docName);
				if (setflag == REPORT) {
					int  ii, ij, ik;
					fprintf(fx, "0:regheader\n");
					for (ii = 0; ii < iregheaders; ii++) {
						i = 0;
						for (ij = 0; ij < regheaders[ii].iheader; ij++) {
							j = regheaders[ii].headers[ij];
							prtline(fx, i, j);
						}
					}
					for (ii = 0; ii < iregdata; ii++) {
						if (ii == 0) {
							fprintf(fx, "0:regdata:dname=%s:func=%d:page=%d:change=%s:usebrk=%s\n",
								(regdata[ii].regdname == 0) ? "" : regdata[ii].regdname, regdata[ii].regfunc, 
								regdata[ii].regbreak, (regdata[ii].regchange == 0) ? "" : regdata[ii].regchange,
								(regdata[ii].regusebrk == 0) ? "" : regdata[ii].regusebrk);
						}
						i = 0;
						for (ij = 0; ij < regdata[ii].iregdatas; ij++) {
							j = regdata[ii].regdatas[ij];
							prtline(fx, i, j);
						}
					}
					for (ii = 0; ii < iregbreak; ii++) {
						i = 0;
						for (ij = 0; ij < regbreak[ii].iregbrk; ij++) {
							fprintf(fx, "0:regbreak:icol=%s:id=%s\n", regbreak[ii].regbrk[ij].icol, 
								(regbreak[ii].regbrk[ij].id == 0) ? "" : regbreak[ii].regbrk[ij].id);
							for(ik = 0; ik < regbreak[ii].regbrk[ij].ibrkrow; ik++) {
								j = regbreak[ii].regbrk[ij].brkrow[ik];
								prtline(fx, i, j);
							}
						}
					}
				}
				else {
					for (j = 0; j < prt[i].iprow; j++) {
						prtline(fx, i, j);
					}
				}
			}
			fclose(fx);
		}
	}
	return 0;
}