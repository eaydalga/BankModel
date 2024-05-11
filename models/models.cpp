#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
//#include <windows.h>

#define GLOBAL

FILE *input;
FILE *output;

int fclass,
finit,
fpanel,
ftxtfunc,
flblfunc,
frbutton,
fbutton,
fchkbox,
fcombo,
fexit,
fquery,
fscroll,
ftable,
floader,
fbuttongrps;

int param = 0;

int panelno = -1;
int combono = 0;
int loadno = 0;
int qlistno = 0;
int txtno = 0;
int lblno = 0;
int buttonno = 0;
int buttongrpno = 0;
int checkno = 0;
int scrollno = 0;
int tableno = 0;

int Processed = 0;
char indent[200];
int  indents = 0;
int  hostyok = 0;

int nfiles = 0;

char buf[MAXCHAR + 1];
char symbol[MAXCHAR + 1];
char program[MAXCHAR + 1];
char areaName[200];

char currpanel[NPANEL][MAXCHAR + 1];
char labels[MAXLABELS][LBLMAX][LBLSIZE];
char txtfields[MAXTXT][TXTMAX][TXTSIZE];
char buttons[MAXBTN][TXTMAX][BTNSIZE];
char buttongrps[MAXBTN][TXTMAX][BTNSIZE];
char combobox[MAXBTN][TXTMAX][BTNSIZE];
char qlist[MAXBTN][TXTMAX][BTNSIZE];
char loads[MAXBTN][TXTMAX][BTNSIZE];
char chkBox[MAXBTN][TXTMAX][BTNSIZE];
char tscroll[MAXBTN][TXTMAX][BTNSIZE];
char table[MAXBTN][TXTMAX][BTNSIZE];
char trndir[200];

int  iglobalid = 0;
char *globalid[1000];

int  ihost;
char hostvar[MAXTXT][TXTSIZE];

int globalyazdi = 0;

void scmandaCondition(int);
void setmandaCondition(int);
void showmsgCondition(int);
void invisibleCondition(int);
void svalueCondition(int);
void datasplitCondition(int);
void datamergeCondition(int);
char *indentstr();
void enableCondition(int);
void disableCondition(int);
void lstsearchCondition(int);
void visibleCondition(int);
void mysignalCondition(int);

int buyukh(char s)
{
	if (s >= 'a' && s <= 'z') {
		return (s & 0xff) - 'a' + 'A';
	}
	return s;
}

char *buyukHarf(char *s)
{
	if (*s >= 'a' && *s <= 'z') {
		*s = (*s & 0xff) - 'a' + 'A';
	}
	return s;
}

int strcasecmp(char *p, char *s)
{
	char *p1, *s1;
	int  i;
	int  len = (int)strlen(p);

	p1 = (char *)calloc(1, strlen(p) + 1);

	if (p1) {
		for (i = 0; i < len; i++) {
			p1[i] = buyukh(p[i]);
			p1[i + 1] = 0;
		}
	}

	len = (int)strlen(s);
	s1 = (char *)calloc(1, strlen(s) + 1);
	if (s1) {
		for (i = 0; i < len; i++) {
			s1[i] = buyukh(s[i]);
			s1[i + 1] = 0;
		}
	}
	return (p1 && s1) ? strcmp(p1, s1) : 0;
}

int strncasecmp(char *s, char *t, int len)
{
	int  i;
	
	for (i = 0; i < len; i++) {
		if (buyukh(s[i]) > buyukh(t[i])) return 1;
		if (buyukh(s[i]) < buyukh(t[i])) return -1;
	}
	return 0;
}


char* myReplace(char* str, char s, char trg)
{
	int i, len;
	int k = 0;
	char t[500];
	len = (int)strlen(str);
	for (i = 0; i < len; i++) {
		if (str[i] == s) str[i] = trg;
	}
	for (i = 0; i < len; i++) {
		if (str[i] == 0xC3) {
			if (str[i + 1] == 0x87)
			{
				t[k] = 'C'; k++;
			}
			if (str[i + 1] == 0x9C)
			{
				t[k] = 'U'; k++;
			}
			if (str[i + 1] == 0x96)
			{
				t[k] = 'O'; k++;
			}
			if (str[i + 1] == 0xA7)
			{
				t[k] = 'C'; k++;
			}
			if (str[i + 1] == 0xBC)
			{
				t[k] = 'U'; k++;
			}
			if (str[i + 1] == 0xB6)
			{
				t[k] = 'O'; k++;
			}
		}
		else
			if (str[i] == 0xC4) {
				if (str[i + 1] == 0xB0)
				{
					t[k] = 'I'; k++;
				}
				if (str[i + 1] == 0x9E)
				{
					t[k] = 'G'; k++;
				}
				if (str[i + 1] == 0xB1)
				{
					t[k] = 'C'; k++;
				}
				if (str[i + 1] == 0x9F)
				{
					t[k] = 'G'; k++;
				}
			}
			else
				if (str[i] == 0xC5) {
					if (str[i + 1] == 0x9E)
					{
						t[k] = 'S'; k++;
					}
					if (str[i + 1] == 0x9F)
					{
						t[k] = 'S'; k++;
					}
				}
				else {
					int sint = str[i];
					switch (sint) {
					case -35:
						t[k] = 'I'; k++;
						break;
					case -57:
						t[k] = 'C'; k++;
						break;
					case -48:
						t[k] = 'G'; k++;
						break;
					case -34:
						t[k] = 'S'; k++;
						break;
					case -36:
						t[k] = 'U'; k++;
						break;
					case -42:
						t[k] = 'O'; k++;
						break;
					case -4:
						t[k] = 'u'; k++;
						break;
					default:
						t[k] = str[i]; k++;
					}
				}
	}
	t[k] = 0;
	if (strlen(str) <= strlen(t)) {
		str = (char*)calloc(1, strlen(t) + 1);
		strcpy(str, t);
	}
	else strcpy(str, t);
	return str;
}

char *indentstr()
{
	int i;
	indent[0] = 0;
	for (i = 0; i<indents; i++) {
		strcat_s(indent, "   ");
		// indent[i+1] = 0;
	}
	return indent;
}

void rmnl(char *bf)
{
	int len = (int) strlen(bf);
	if (bf[len - 1] == '\n') { bf[len - 1] = 0; len--; }
	if (bf[len - 1] == '\r') { bf[len - 1] = 0; len--; }
	if (bf[len - 1] == '\n') { bf[len - 1] = 0; len--; }
}

char *skipsome(char *p)
{
	int i, k, len = (int) strlen(p);
	char sbuf[200];
	char *p1;
	k = 0;
	for (i = 0; i < len; i++) {
		if ((p[i] >= '0' && p[i] <= '9') ||
			(p[i] >= 'a' && p[i] <= 'z') ||
			(p[i] >= 'A' && p[i] <= 'Z')) {
			sbuf[k] = p[i];
			k++;
			sbuf[k] = 0;
		}
	}
	p1 = (char *)calloc(1, strlen(sbuf) + 1);
	strcpy(p1, sbuf);
	return p1;
}
void searchGlobal(char *inp)
{
	int  i;
	char bf[MAXCHAR + 1];
	char *p, *p1;
	if (strstr(inp, "@return")) return;
	strcpy(bf, inp);
	p1 = bf;
	while (p1) {
		p = strstr(p1, "@");
		if (p) {
			p++;
			p1 = p;
			while (*p && *p != '\"' && *p != '.') p++;
			if (*p == '\"') {
				*p = 0;
				i = iglobalid;
				globalid[i] = (char *)calloc(1, strlen(p1) + 1);
				strcpy(globalid[i], p1);
				iglobalid++;
				break;
			}
			if (*p == '.') {
				*p = 0;
				p++;
				i = iglobalid;
				globalid[i] = (char *)calloc(1, strlen(p1) + 1);
				strcpy(globalid[i], p1);
				iglobalid++;
				p1 = strstr(p, "@");
			}
		}
		else break;
	}
}

int mygetline(char *ss)
{
	int ret = EOF;
	char *p1, *pt, *pbuf = buf;
	if (Processed == 0) {
		return ret;
	}
	Processed = 0;
	if (fgets(buf, MAXCHAR, input) != NULL) {
		rmnl(buf);
		searchGlobal(buf);
		if (strstr(buf, "import")) {
			Processed = 1;
			return ret;
		}
		p1 = pbuf;
		while (*p1 == ' ') p1++;
		if ((*p1 == '/' &&  *(p1 + 1) == '*')) {
			if (!strstr(buf, "*/")) {
				while (1) {
					fgets(buf, MXCHAR, input);
					if (strstr(buf, "*/")) break;
				}
			}
			return ret;
		}
		else {
			pt = strstr(pbuf, ss);
			if (pt != NULL) {
				ret = (int)(pt - buf) + (int) strlen(ss);
			}
		}
	}
	else 
		ret = -2;
	return ret;
}

int findval(char *inp)
{
	if (strcmp(inp, CCLASS) == 0) return PCLASS;
	if (strcmp(inp, CWIDGETS) == 0) return PWIDGETS;
	if (strcmp(inp, CPANEL) == 0) return PPANEL;
	if (strcmp(inp, CLABEL) == 0) return PLABEL;
	if (strcmp(inp, CTEXTFIELD) == 0) return PTEXTFIELD;
	if (strcmp(inp, CBUTTON) == 0) return PBUTTON;
	if (strcmp(inp, CBUTTONGRP) == 0) return PBUTTONGRP;
	if (strcmp(inp, CCOMBOBOX) == 0) return PCOMBOBOX;
	if (strcmp(inp, CCHECKBOX) == 0) return PCHECKBOX;
	if (strcmp(inp, CQUERYLSTFUNC) == 0) return PQUERYLSTFUNC;
	if (strcmp(inp, CLOADER) == 0) return PLOADER;
	if (strcmp(inp, CTABLE) == 0) return PTABLE;
	if (strcmp(inp, CTABLES) == 0) return PTABLES;
	if (strcmp(inp, CSCROLL) == 0) return PTSCROLL;
	return EOF;
}

int getsymbol(char *intext)
{
	int len;
	char *pbuf = buf;
	char *pt;
	len = (int) strlen(intext);
	pt = strstr(pbuf, intext);
	if (pt) {
		pt = pt + len;
		while (*pt == ' ') pt++;
		strcpy(symbol, pt);
		return findval(intext);
	}
	return EOF;
}

int detected(char *str)
{
	int ret;
	ret = getsymbol(str);
	if (ret != EOF) {
		char *pt = strstr(symbol, " ");
		if (pt && (strstr(symbol, "(") == NULL)) {
			*pt = 0;
			switch (ret) {
			case PPANEL:
				panelno++;
				strcpy(currpanel[panelno], symbol);
				lblno = 0;
				txtno = 0;
				buttonno = 0;
				buttongrpno = 0;
				Processed = 1;
				break;
			case PLABEL:
				/* save label to current panel */
				strcpy(labels[panelno][lblno], symbol);
				lblno++;
				labels[panelno][lblno][0] = 0;
				Processed = 1;
				break;
			case PTEXTFIELD:
				/* save textfield to current panel */
				strcpy(txtfields[panelno][txtno], symbol);
				txtno++;
				txtfields[panelno][txtno][0] = 0;
				Processed = 1;
				break;
			case PBUTTON:
				strcpy(buttons[panelno][buttonno], symbol);
				buttonno++;
				buttons[panelno][buttonno][0] = 0;
				Processed = 1;
				break;
			case PBUTTONGRP:
				strcpy(buttongrps[panelno][buttongrpno], symbol);
				buttongrpno++;
				buttongrps[panelno][buttongrpno][0] = 0;
				Processed = 1;
				break;
			case PCOMBOBOX:
				strcpy(combobox[panelno][combono], symbol);
				combono++;
				combobox[panelno][combono][0] = 0;
				Processed = 1;
				break;
			case PCHECKBOX:
				strcpy(chkBox[panelno][checkno], symbol);
				checkno++;
				chkBox[panelno][checkno][0] = 0;
				Processed = 1;
				break;
			case PQUERYLSTFUNC:
				strcpy(qlist[panelno][qlistno], symbol);
				qlistno++;
				qlist[panelno][qlistno][0] = 0;
				Processed = 1;
				break;
			case PTABLE:
			case PTABLES:
				strcpy(table[panelno][tableno], symbol);
				tableno++;
				table[panelno][tableno][0] = 0;
				Processed = 1;
				break;
			}
		}
	}
	return ret;
}

int findinval(char *inp)
{
	if (strcmp(inp, CINIT) == 0) return PINIT;
	if (strcmp(inp, CPAGE) == 0) return PPAGE;
	if (strcmp(inp, CTITLE) == 0) return PTITLE;
	if (strcmp(inp, CBOUND) == 0) return PBOUND;
	if (strcmp(inp, CADD) == 0) return PADD;
	if (strcmp(inp, CGETGRP) == 0) return PGETGRP;
	if (strcmp(inp, CLAYOUT) == 0) return PLAYOUT;

	if (strcmp(inp, CEXIT) == 0) return PEXIT;
	if (strcmp(inp, cexit) == 0) return pexit;
	if (strcasecmp(inp, CADDEXIT) == 0) return PADDEXIT;
	if (strcasecmp(inp, CSHOWMSG) == 0) return PSHOWMSG;
	if (strcasecmp(inp, CSETVALUE) == 0) return PSETVALUE;
	if (strcasecmp(inp, CDATAMERGE) == 0) return PDATAMERGE;
	if (strcasecmp(inp, CANDCONDITION) == 0) return PANDCONDITION;
	if (strcasecmp(inp, CDATASPLIT) == 0) return PDATASPLIT;
	if (strcasecmp(inp, CCLEAR) == 0) return PCLEAR;
	if (strcasecmp(inp, CSETCLEAR) == 0) return PSETCLEAR;
	if (strcasecmp(inp, CINVISIBLE) == 0) return PINVISIBLE;
	if (strcasecmp(inp, CADDCONDITION) == 0) return PADDCONDITION;
	if (strcasecmp(inp, CLOADER) == 0) return PLOADER;
	if (strcasecmp(inp, CQUERYLSTFUNC) == 0) return PQUERYLSTFUNC;
	return EOF;
}

int getinsym(char *intext)
{
	int len, ret = EOF;
	char pbuf[500];
	char *pt;
	strcpy(pbuf, buf);
	len = (int) strlen(intext);
	
	pt = strstr(pbuf, intext);
	if (pt) {
		while (*pt != ' ' && *pt != 0) pt++;
		*pt = 0;
		strcpy(symbol, pt);
		ret = findinval(intext);
	}
	return ret;
}

void mysplit(int x[], char *p, char c)
{
	char *p1, *p2;
	p1 = p2 = p;
	while (*p1 != 0 && *p1 != ',') p1++;
	*p1 = 0;
	p1++;
	x[0] = atoi(p2);
	p2 = p1;
	while (*p1 != 0 && *p1 != ',') p1++;
	*p1 = 0;
	p1++;
	x[1] = atoi(p2);
	p2 = p1;
	while (*p1 != 0 && *p1 != ',') p1++;
	*p1 = 0;
	p1++;
	x[2] = atoi(p2);
	p2 = p1;
	while (*p1 != 0 && *p1 != ',') p1++;
	*p1 = 0;
	x[3] = atoi(p2);
}

int findPanel(char *pname, char *pp)
{
	int i;
	char *p2, *p1 = pp;
	p2 = p1;
	while (*p1 != 0 && *p1 != '(') p1++;
	*p1 = 0;
	strcpy(pname, p2);
	for (i = 0; i <= panelno; i++)
		if (strcasecmp(p2, currpanel[i]) == 0) {
			return i;
		}
	return EOF;
}

int findButton(char *bname, char *pp)
{
	int i, j;
	char *p2, *p1 = pp;
	p2 = p1;
	while (*p1 != 0 && *p1 != '(') p1++;
	*p1 = 0;
	strcpy(bname, p2);
	for (i = 0; i <= panelno; i++) {
		for (j = 0; (int) strlen(buttons[i][j]) > 0; j++)
			if (strcasecmp(p2, buttons[i][j]) == 0) {
				return (i * 100 + j);
			}
	}
	return EOF;
}

int findGroup(char *instr, char *pp)
{
	int i, j;
	char grp[200];
	char btn[200];
	char *p2, *p1 = pp;
	p2 = p1;
	while (*p1 != 0 && *p1 != '(') p1++;
	*p1 = 0;
	p1++;
	strcpy(grp, p2);
	while (*p1 != 0 && *p1 != '.') p1++;
	p2 = p1 + 8; // .add(get
	p1 = p2;
	while (*p1 != 0 && *p1 != '(') p1++;
	*p1 = 0;
	strcpy(btn, p2);
	strcpy(instr, btn);
	for (i = 0; i <= panelno; i++) {
		for (j = 0; (int) strlen(buttongrps[i][j]) > 0; j++)
			if (strcasecmp(grp, buttongrps[i][j]) == 0) {
				strcpy(instr, btn);
				return i * 100 + j;
			}
	}
	return EOF;
}

int findScroll(char *bname, char *pp)
{
	int i, j;
	char *p2, *p1 = pp;
	p2 = p1;
	while (*p1 != 0 && *p1 != '(') p1++;
	*p1 = 0;
	strcpy(bname, p2);
	for (i = 0; i <= panelno; i++) {
		for (j = 0; (int) strlen(buttons[i][j]) > 0; j++)
			if (strcasecmp(p2, buttons[i][j]) == 0) {
				return (i * 100 + j);
			}
	}
	return EOF;
}

int initMi()
{
	int ret = EOF;
	//  CINIT "initialize() "
	if ((finit == 0) && (strstr(buf, CINIT) > 0)) {
		finit = 1;
		Processed = 1;
		// CENDINIT "}"
		while (1) {
			ret = mygetline(CENDINIT2);
			if (ret != EOF) { 
				Processed = 1; 
				break; 
			}
			if (strstr(buf, CENDINIT) && !strstr(buf, CBEGIN)) {
				Processed = 1;
				break;
			}
			Processed = 1;
			// CPAGE "this.setName("
			if (getinsym(CPAGE) == PPAGE) {
				char *p1, *p;
				p = strstr(buf, CPAGE);
				if (p) {
					p = p + strlen(CPAGE) + 1;
					p1 = p;
					while (*p != 0 && *p != '"') p++;
					*p = 0;
					slayout[nfiles].name = (char *)calloc(1, strlen(p1) + 1);
					strcpy(slayout[nfiles].name, p1);
				}
				else {
					slayout[nfiles].name = (char *)calloc(1, strlen("noname") + 1);
					strcpy(slayout[nfiles].name, "noname");
				}
				continue;
			}
			// CTITLE "this.setTitle("
			if (getinsym(CTITLE) == PTITLE) {
				char *p1, *p;
				p = strstr(buf, CTITLE);
				if (p) {
					p = p + strlen(CTITLE) + 1;
					p1 = p;
					while (*p != 0 && *p != '"') p++;
					*p = 0;
					slayout[nfiles].title = (char *)calloc(1, strlen(p1) + 1);
					strcpy(slayout[nfiles].title, p1);
				}
				else {
					slayout[nfiles].title = (char *)calloc(1, 3);
					strcpy(slayout[nfiles].title, "  ");
				}
				continue;
			}
			// CBOUND "this.setBounds("
			if (getinsym(CBOUND) == PBOUND) {
				int x[4];
				char *p1, *p;
				p = strstr(buf, CBOUND);
				if (p) {
					p = p + strlen(CBOUND);
					p1 = p;
					while (*p != 0 && *p != ')') p++;
					*p = 0;
					mysplit(x, p1, ',');
					slayout[nfiles].bound.x0 = x[0];
					slayout[nfiles].bound.y0 = x[1];
					slayout[nfiles].bound.x1 = x[2];
					slayout[nfiles].bound.y1 = x[3];
				}
				continue;
			}
			// CADD "this.add(get"
			if (getinsym(CADD) == PADD) {
				char *p = strstr(buf, CADD);
				int  curpanel;
				if (p) {
					p = p + strlen(CADD);
					if (strstr(buf, CADDPANEL)) {
						char pname[200];
						slayout[nfiles].added[slayout[nfiles].iadded].npanel = findPanel(pname, p);
						curpanel = slayout[nfiles].added[slayout[nfiles].iadded].npanel;
						slayout[nfiles].added[slayout[nfiles].iadded].nbutton = EOF;
						slayout[nfiles].added[slayout[nfiles].iadded].type = PADDPANEL;
						slayout[nfiles].added[slayout[nfiles].iadded].addb = 
							(char *)calloc(1, strlen(pname) + 1);
						strcpy(slayout[nfiles].added[slayout[nfiles].iadded].addb, pname);
						slayout[nfiles].iadded++;
						finit = 0;
					}
					if (strstr(buf, CTABLESP)) {
						char pname[200];
						char *p1;
						p = strstr(buf, CTABLESP);
						if (p) {
							p1 = strstr(p, "Scroll");
							if (p1) *p1 = 0;
							strcpy(pname, "A");
							strcat(pname, p);
							slayout[nfiles].added[slayout[nfiles].iadded].npanel = curpanel;
							slayout[nfiles].added[slayout[nfiles].iadded].nbutton = EOF;
							slayout[nfiles].added[slayout[nfiles].iadded].type = PADDSTABLE;
							slayout[nfiles].added[slayout[nfiles].iadded].addb = 
								(char *)calloc(1, strlen(pname) + 1);
							if(slayout[nfiles].added[slayout[nfiles].iadded].addb) strcpy(slayout[nfiles].added[slayout[nfiles].iadded].addb, pname);
							slayout[nfiles].iadded++;
							finit = 0;
						}
					}
				}
				else
					if (strstr(buf, CADDBUTTON)) {
						int x;
						char bname[200];
						char *p = strstr(buf, CADDBUTTON);
						if (p) {
							x = findButton(bname, p);
							slayout[nfiles].added[slayout[nfiles].iadded].npanel = x / 100;
							slayout[nfiles].added[slayout[nfiles].iadded].nbutton = x % 100;
							slayout[nfiles].added[slayout[nfiles].iadded].type = PADDBUTTON;
							slayout[nfiles].added[slayout[nfiles].iadded].addb = (char *)calloc(1, strlen(bname) + 1);
							strcpy(slayout[nfiles].added[slayout[nfiles].iadded].addb, bname);
							slayout[nfiles].iadded++;
						}
					}
				continue;
			}
			// CGETGRP " get"
			if (getinsym(CGETGRP) == PGETGRP) {
				int x;
				char addbtn[200];
				char *p = strstr(buf, CGETGRP);
				if (p) {
					p = p + strlen(CGETGRP);
					x = findGroup(addbtn, p);
					slayout[nfiles].added[slayout[nfiles].iadded].npanel = x / 100;
					slayout[nfiles].added[slayout[nfiles].iadded].nbutton = x % 100;
					slayout[nfiles].added[slayout[nfiles].iadded].type = PGETGRP;
					slayout[nfiles].added[slayout[nfiles].iadded].addb = (char *)calloc(1, strlen(addbtn) + 1);
					if(slayout[nfiles].added[slayout[nfiles].iadded].addb) strcpy(slayout[nfiles].added[slayout[nfiles].iadded].addb, addbtn);
					slayout[nfiles].iadded++;
					continue;
				}
			}
		}
	}
	return ret;
}


int adVarmi(int cur, char *name)
{
	int i, ret = EOF;
	switch (cur) {
	case PCLEAR:
		for (i = 0; i < sexit[nfiles].iscmanda; i++) {
			if (strcasecmp(sexit[nfiles].scmanda[i].sName, name) == 0)
				return i;
		}
		break;
	case PSETCLEAR:
		for (i = 0; i < sexit[nfiles].isetmanda; i++) {
			if (strcasecmp(sexit[nfiles].setmanda[i].sName, name) == 0)
				return i;
		}
		break;
	case PSHOWMSG:
		for (i = 0; i < sexit[nfiles].ishowmsg; i++) {
			if (strcasecmp(sexit[nfiles].showMsg[i].sName, name) == 0)
				return i;
		}
		break;
	case PSETVALUE:
		for (i = 0; i < sexit[nfiles].isvalue; i++) {
			if (strcasecmp(sexit[nfiles].svalue[i].sName, name) == 0)
				return i;
		}
		break;
	case PDATAMERGE:
		for (i = 0; i < sexit[nfiles].idatamerge; i++) {
			if (strcasecmp(sexit[nfiles].datamerge[i].sName, name) == 0)
				return i;
		}
		break;
	case PDATASPLIT:
		for (i = 0; i < sexit[nfiles].idatasplit; i++) {
			if (strcasecmp(sexit[nfiles].datasplitfunc[i].sName, name) == 0)
				return i;
		}
		break;
	case PINVISIBLE:
		for (i = 0; i < sexit[nfiles].iInvisible; i++) {
			if (strcasecmp(sexit[nfiles].sinvisible[i].sName, name) == 0)
				return i;
		}
		break;
	case PQUERYLSTFUNC:
		for (i = 0; i < sexit[nfiles].iqueryList; i++) {
			if (strcasecmp(sexit[nfiles].squeryList[i].sName, name) == 0)
				return i;
		}
		break;
	}
	return ret;
}

void splitEvent(char a[3][100])
{
	int i;
	char *p, *p1;
	p = strstr(buf, CADDEXIT);
	if(p) {
		p1 = p + (int) strlen(CADDEXIT);
		if(p1) {
			p = p1;
			for (i = 0; i < 3; i++) {
				while (*p != ',' && *p != 0) p++;
				if(p) {
					*p = 0; 
					p++;
				}
				strcpy(a[i], p1);
				p1 = p;
				if(p1) p1++;
			}
		}
	}
}

int clearMandatory(int current, char *name)
{
	int indx, j;
	char *p, *p1;
	if (!strstr(name, CCLEAR)) return EOF;
	indx = adVarmi(current, name);
	if (indx == EOF) {
		p = name;
		while (*p != 0 && *p != '(') p++;
		*p = 0;
		indx = sexit[nfiles].iscmanda;
		sexit[nfiles].iscmanda++;
		sexit[nfiles].scmanda[indx].iaddexit = 0;
		sexit[nfiles].scmanda[indx].iaddcon = 0;
		sexit[nfiles].scmanda[indx].sName = (char *) calloc(1, (int) strlen(name) + 1);
		strcpy(sexit[nfiles].scmanda[indx].sName, name);
	}
	if ((p = strstr(buf, CSETTAB))) {
		while (*p != '{' && *p != 0) p++;
		p++;
		p1 = p;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit[nfiles].scmanda[indx].setTabnum = (char *) calloc(1, (int) strlen(p1) + 1);
		strcpy(sexit[nfiles].scmanda[indx].setTabnum, p1);
	}
	if ((p = strstr(buf, CADDEXIT))) {
		char a[3][100];
		char *pp;
		splitEvent(a);
		pp = a[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit[nfiles].scmanda[indx].iaddexit;
		sexit[nfiles].scmanda[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0]) + 1);
		strcpy(sexit[nfiles].scmanda[indx].saddExit[j].fieldName, a[0]);
		sexit[nfiles].scmanda[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit[nfiles].scmanda[indx].saddExit[j].clearFunc, a[1]);
		sexit[nfiles].scmanda[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit[nfiles].scmanda[indx].saddExit[j].eventName, a[2]);
		sexit[nfiles].scmanda[indx].iaddexit++;
	}
	scmandaCondition(indx);
	return indx;
}

void scmandaCondition(int indx)
{
	int j;
	char *p, *p1, *p2, *p3;
	if ((p = strstr(buf, CADDCONDITION))) {
		p2 = buf;
		while (*p2 != 0 && (*p2 == ' ' || *p2 == '\t')) p2++;
		*(p - 1) = 0;
		p1 = p + (int) strlen(CADDCONDITION) + 1;

		p = p1;
		while (*p != '(') p++;
		p++;
		p3 = p;
		while (*p != ')') p++;
		*p = 0;
		for (indx = 0; indx < sexit[nfiles].iscmanda; indx++) {
			if (strcmp(sexit[nfiles].scmanda[indx].sName, p2) == 0) {
				j = sexit[nfiles].scmanda[indx].iaddcon;
				sexit[nfiles].scmanda[indx].addCondition[j] =
					(char*)calloc(1, strlen(p1) + 1);
				strcpy(sexit[nfiles].scmanda[indx].addCondition[j], p1);
				sexit[nfiles].scmanda[indx].iaddcon++;
				j++;
				sexit[nfiles].scmanda[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p2) + 1);
				strcpy(sexit[nfiles].scmanda[indx].addCondition[j], p2);
				sexit[nfiles].scmanda[indx].iaddcon++;
				j++;
				sexit[nfiles].scmanda[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p3) + 1);
				strcpy(sexit[nfiles].scmanda[indx].addCondition[j], p3);
				sexit[nfiles].scmanda[indx].iaddcon++;
			}
		}
	}
}

int setMandatory(int current, char *name)
{
	int indx, j;
	char *p, *p1;

	if (!strstr(name, CSETCLEAR)) return EOF;
	indx = adVarmi(current, name);
	if (indx == EOF) {
		p = name;
		while (*p != 0 && *p != '(') p++;
		*p = 0;
		indx = sexit[nfiles].isetmanda;
		sexit[nfiles].isetmanda++;
		sexit[nfiles].setmanda[indx].iaddexit = 0;
		sexit[nfiles].setmanda[indx].iaddcon = 0;
		sexit[nfiles].setmanda[indx].sName = (char *) calloc(1, (int) strlen(name) + 1);
		strcpy(sexit[nfiles].setmanda[indx].sName, name);
	}
	if ((p = strstr(buf, CSETTAB))) {
		while (*p != '{' && *p != 0) p++;
		p++;
		p1 = p;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit[nfiles].setmanda[indx].setTabnum = (char *) calloc(1, (int) strlen(p1) + 1);
		strcpy(sexit[nfiles].setmanda[indx].setTabnum, p1);
	}
	if ((p = strstr(buf, CADDEXIT))) {
		char a[3][100];
		char *pp;
		splitEvent(a);
		pp = a[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit[nfiles].setmanda[indx].iaddexit;
		sexit[nfiles].setmanda[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0]) + 1);
		strcpy(sexit[nfiles].setmanda[indx].saddExit[j].fieldName, a[0]);
		sexit[nfiles].setmanda[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit[nfiles].setmanda[indx].saddExit[j].clearFunc, a[1]);
		sexit[nfiles].setmanda[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit[nfiles].setmanda[indx].saddExit[j].eventName, a[2]);
		sexit[nfiles].setmanda[indx].iaddexit++;
	}
	setmandaCondition(indx);
	return indx;
}

void setmandaCondition(int indx)
{
	int  j;
	char *p, *p1, *p2, *p3;
	if ((p = strstr(buf, CADDCONDITION))) {
		p2 = buf;
		while (*p2 != 0 && (*p2 == ' ' || *p2 == '\t')) p2++;
		*(p - 1) = 0;
		p1 = p + (int) strlen(CADDCONDITION) + 1;
		p = p1;
		while (*p != '(') p++;
		p++;
		p3 = p;
		while (*p != ')') p++;
		*p = 0;
		for (indx = 0; indx < sexit[nfiles].isetmanda; indx++) {
			if (strcmp(sexit[nfiles].setmanda[indx].sName, p2) == 0) {


				j = sexit[nfiles].setmanda[indx].iaddcon;
				sexit[nfiles].setmanda[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p1) + 1);
				strcpy(sexit[nfiles].setmanda[indx].addCondition[j], p1);
				sexit[nfiles].setmanda[indx].iaddcon++;
				j++;
				sexit[nfiles].setmanda[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p2) + 1);
				strcpy(sexit[nfiles].setmanda[indx].addCondition[j], p2);
				sexit[nfiles].setmanda[indx].iaddcon++;
				j++;
				sexit[nfiles].setmanda[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p3) + 1);
				strcpy(sexit[nfiles].setmanda[indx].addCondition[j], p3);
				sexit[nfiles].setmanda[indx].iaddcon++;
			}
		}
	}
}



int showMessage(int current, char *name)
{
	int indx, j;
	char *p, *p1;
	if (!strstr(name, CSHOWMSG)) return EOF;
	indx = adVarmi(current, name);
	if (indx == EOF) {
		indx = sexit[nfiles].ishowmsg;
		sexit[nfiles].ishowmsg++;
		sexit[nfiles].showMsg[indx].iaddexit = 0;
		sexit[nfiles].showMsg[indx].iaddcon = 0;
		sexit[nfiles].showMsg[indx].sName = (char *) calloc(1, (int) strlen(name) + 1);
		strcpy(sexit[nfiles].showMsg[indx].sName, name);
	}
	if ((p = strstr(buf, CSETTAB))) {
		while (*p != '{' && *p != 0) p++;
		p++;
		p1 = p;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit[nfiles].showMsg[indx].setTabnum = (char *)calloc(1, strlen(p1)+1);
		strcpy(sexit[nfiles].showMsg[indx].setTabnum, p1);
	}
	if ((p = strstr(buf, CSETTITLE))) {
		p1 = p + (int) strlen(CSETTITLE) + 2;
		p = p1;
		while (*p != '\"' && *p != 0) p++;
		*p = 0;
		sexit[nfiles].showMsg[indx].title = (char *) calloc(1, (int) strlen(p1) + 1);
		strcpy(sexit[nfiles].showMsg[indx].title, p1);
	}
	if ((p = strstr(buf, CSETMSG))) {
		p1 = p + (int) strlen(CSETMSG) + 1;
		p = p1;
		while (*p != '\"' && *p != 0) p++;
		*p = 0;
		sexit[nfiles].showMsg[indx].msg = (char *) calloc(1, (int) strlen(p1) + 1);
		strcpy(sexit[nfiles].showMsg[indx].msg, p1);
	}
	if ((p = strstr(buf, CSETMSGTYPE))) {
		p1 = p + (int) strlen(CSETMSGTYPE);
		p = p1;
		while (*p != ')' && *p != 0) p++;
		*p = 0;
		sexit[nfiles].showMsg[indx].msgType = atoi(p1);
	}
	if ((p = strstr(buf, CSETMSGOPTION))) {
		p1 = p + (int) strlen(CSETMSGOPTION);
		p = p1;
		while (*p != ')' && *p != 0) p++;
		*p = 0;
		sexit[nfiles].showMsg[indx].setTabnum = (char *) calloc(1, (int) strlen(p1) + 1);
		strcpy(sexit[nfiles].showMsg[indx].setTabnum, p1);
	}
	if ((p = strstr(buf, CADDEXIT))) {
		char a[3][100];
		char *pp;
		splitEvent(a);
		pp = a[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit[nfiles].showMsg[indx].iaddexit;
		sexit[nfiles].showMsg[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0]) + 1);
		strcpy(sexit[nfiles].showMsg[indx].saddExit[j].fieldName, a[0]);
		sexit[nfiles].showMsg[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit[nfiles].showMsg[indx].saddExit[j].clearFunc, a[1]);
		sexit[nfiles].showMsg[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit[nfiles].showMsg[indx].saddExit[j].eventName, a[2]);
		sexit[nfiles].showMsg[indx].iaddexit++;
	}
	showmsgCondition(indx);
	return indx;
}

void showmsgCondition(int indx)
{
	int  j;
	char *p, *p1, *p2, *p3;
	if ((p = strstr(buf, CADDCONDITION))) {
		p2 = buf;
		while (*p2 != 0 && (*p2 == ' ' || *p2 == '\t')) p2++;
		*(p - 1) = 0;
		p1 = p + (int) strlen(CADDCONDITION) + 1;
		p = p1;
		while (*p != '(') p++;
		p++;
		p3 = p;
		while (*p != ')') p++;
		*p = 0;
		for (indx = 0; indx < sexit[nfiles].ishowmsg; indx++) {
			if (strcmp(sexit[nfiles].showMsg[indx].sName, p2) == 0) {
				j = sexit[nfiles].showMsg[indx].iaddcon;
				sexit[nfiles].showMsg[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p1) + 1);
				strcpy(sexit[nfiles].showMsg[indx].addCondition[j], p1);
				sexit[nfiles].showMsg[indx].iaddcon++;
				j++;
				sexit[nfiles].showMsg[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p2) + 1);
				strcpy(sexit[nfiles].showMsg[indx].addCondition[j], p2);
				sexit[nfiles].showMsg[indx].iaddcon++;
				j++;
				sexit[nfiles].showMsg[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p3) + 1);
				strcpy(sexit[nfiles].showMsg[indx].addCondition[j], p3);
				sexit[nfiles].showMsg[indx].iaddcon++;
			}
		}
	}
}


int invisible(int current, char *name)
{
	int indx, j;
	char *p, *p1;
	if (!strstr(name, CINVISIBLE)) return EOF;
	indx = adVarmi(current, name);
	if (indx == EOF) {
		indx = sexit[nfiles].iInvisible;
		sexit[nfiles].iInvisible++;
		sexit[nfiles].sinvisible[indx].iaddexit = 0;
		sexit[nfiles].sinvisible[indx].iaddcon = 0;
		sexit[nfiles].sinvisible[indx].sName = (char *) calloc(1, (int) strlen(name) + 1);
		strcpy(sexit[nfiles].sinvisible[indx].sName, name);
	}
	if ((p = strstr(buf, CSETTAB))) {
		while (*p != '{' && *p != 0) p++;
		p++;
		p1 = p;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit[nfiles].sinvisible[indx].setTabnum = (char *) calloc(1, (int) strlen(p1) + 1);
		strcpy(sexit[nfiles].sinvisible[indx].setTabnum, p1);
	}
	if ((p = strstr(buf, CADDEXIT))) {
		char a[3][100];
		char *pp;
		splitEvent(a);
		pp = a[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit[nfiles].sinvisible[indx].iaddexit;
		sexit[nfiles].sinvisible[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0]) + 1);
		strcpy(sexit[nfiles].sinvisible[indx].saddExit[j].fieldName, a[0]);
		sexit[nfiles].sinvisible[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit[nfiles].sinvisible[indx].saddExit[j].clearFunc, a[1]);
		sexit[nfiles].sinvisible[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit[nfiles].sinvisible[indx].saddExit[j].eventName, a[2]);
		sexit[nfiles].sinvisible[indx].iaddexit++;
	}
	invisibleCondition(indx);
	return indx;
}

void invisibleCondition(int indx)
{
	int  j;
	char *p, *p1, *p2, *p3;
	if ((p = strstr(buf, CADDCONDITION))) {
		p2 = buf;
		while (*p2 != 0 && (*p2 == ' ' || *p2 == '\t')) p2++;
		*(p - 1) = 0;
		p1 = p + (int) strlen(CADDCONDITION) + 1;
		p = p1;
		while (*p != '(') p++;
		p++;
		p3 = p;
		while (*p != ')') p++;
		*p = 0;
		for (indx = 0; indx < sexit[nfiles].iInvisible; indx++) {
			if (strcmp(sexit[nfiles].sinvisible[indx].sName, p2) == 0) {
				j = sexit[nfiles].sinvisible[indx].iaddcon;
				sexit[nfiles].sinvisible[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p1) + 1);
				strcpy(sexit[nfiles].sinvisible[indx].addCondition[j], p1);
				sexit[nfiles].sinvisible[indx].iaddcon++;
				j++;
				sexit[nfiles].sinvisible[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p2) + 1);
				strcpy(sexit[nfiles].sinvisible[indx].addCondition[j], p2);
				sexit[nfiles].sinvisible[indx].iaddcon++;
				j++;
				sexit[nfiles].sinvisible[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p3) + 1);
				strcpy(sexit[nfiles].sinvisible[indx].addCondition[j], p3);
				sexit[nfiles].sinvisible[indx].iaddcon++;
			}
		}
	}
}


int setValue(int current, char *name)
{
	int indx, j;
	char *p, *p1;
	if (!strstr(name, CSETVALUE)) return EOF;
	indx = adVarmi(current, name);
	if (indx == EOF) {
		indx = sexit[nfiles].isvalue;
		sexit[nfiles].isvalue++;
		sexit[nfiles].svalue[indx].iaddexit = 0;
		sexit[nfiles].svalue[indx].iaddcon = 0;
		sexit[nfiles].svalue[indx].sName = (char *) calloc(1, (int) strlen(name) + 1);
		strcpy(sexit[nfiles].svalue[indx].sName, name);
	}
	sexit[nfiles].svalue[indx].setTabnum = 0;
	if ((p = strstr(buf, CSETTAB))) {
		while (*p != '{' && *p != 0) p++;
		p++;
		p1 = p;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit[nfiles].svalue[indx].setTabnum = (char *) calloc(1, (int) strlen(p1) + 1);
		strcpy(sexit[nfiles].svalue[indx].setTabnum, p1);
	}
	if ((p = strstr(buf, CSETDATAELM))) {
		p1 = p + (int) strlen(CSETDATAELM) + 1;
		while (*p1 != '{' && *p1 != 0) p1++;
		p1++;
		p = p1;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit[nfiles].svalue[indx].dataElement = (char *) calloc(1, (int) strlen(p1) + 1);
		strcpy(sexit[nfiles].svalue[indx].dataElement, p1);
	}
	// sexit[nfiles].svalue[indx].setValue = NULL;
	if ((p = strstr(buf, CSETVALUE1))) {
		p1 = p + (int) strlen(CSETVALUE1) + 1;
		p = p1;
		while (*p != '\"' && *p != 0) p++;
		*p = 0;
		sexit[nfiles].svalue[indx].setValue = (char *) calloc(1, (int) strlen(p1) + 1);
		strcpy(sexit[nfiles].svalue[indx].setValue, p1);
	}
	if ((p = strstr(buf, CADDEXIT))) {
		char a[3][100];
		char *pp;
		splitEvent(a);
		pp = a[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit[nfiles].svalue[indx].iaddexit;
		sexit[nfiles].svalue[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0]) + 1);
		strcpy(sexit[nfiles].svalue[indx].saddExit[j].fieldName, a[0]);
		sexit[nfiles].svalue[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit[nfiles].svalue[indx].saddExit[j].clearFunc, a[1]);
		sexit[nfiles].svalue[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit[nfiles].svalue[indx].saddExit[j].eventName, a[2]);
		sexit[nfiles].svalue[indx].iaddexit++;
	}
	svalueCondition(indx);
	return indx;
}

void svalueCondition(int indx)
{
	int  j;
	char *p, *p1, *p2, *p3;
	if ((p = strstr(buf, CADDCONDITION))) {
		p2 = buf;
		while (*p2 != 0 && (*p2 == ' ' || *p2 == '\t')) p2++;
		*(p - 1) = 0;
		p1 = p + (int) strlen(CADDCONDITION) + 1;
		p = p1;
		while (*p != '(') p++;
		p++;
		p3 = p;
		while (*p != ')') p++;
		*p = 0;

		for (indx = 0; indx < sexit[nfiles].isvalue; indx++) {
			if (strcmp(sexit[nfiles].svalue[indx].sName, p2) == 0) {
				j = sexit[nfiles].svalue[indx].iaddcon;
				sexit[nfiles].svalue[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p1) + 1);
				strcpy(sexit[nfiles].svalue[indx].addCondition[j], p1);
				sexit[nfiles].svalue[indx].iaddcon++;
				j++;
				sexit[nfiles].svalue[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p2) + 1);
				strcpy(sexit[nfiles].svalue[indx].addCondition[j], p2);
				sexit[nfiles].svalue[indx].iaddcon++;
				j++;
				sexit[nfiles].svalue[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p3) + 1);
				strcpy(sexit[nfiles].svalue[indx].addCondition[j], p3);
				sexit[nfiles].svalue[indx].iaddcon++;
			}
		}
	}
}

int dataSplit(int current, char *name)
{
	int indx, j;
	char *p, *p1;
	if (!strstr(name, CDATASPLIT)) return EOF;
	indx = adVarmi(current, name);
	if (indx == EOF) {
		indx = sexit[nfiles].idatasplit;
		sexit[nfiles].idatasplit++;
		sexit[nfiles].datasplitfunc[indx].iaddexit = 0;
		sexit[nfiles].datasplitfunc[indx].iaddcon = 0;
		sexit[nfiles].datasplitfunc[indx].sName = (char *) calloc(1, (int) strlen(name) + 1);
		strcpy(sexit[nfiles].datasplitfunc[indx].sName, name);
	}
	if ((p = strstr(buf, CSETTAB))) {
		while (*p != '{' && *p != 0) p++;
		p++;
		p1 = p;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit[nfiles].datasplitfunc[indx].setTabnum = (char *) calloc(1, (int) strlen(p1) + 1);
		strcpy(sexit[nfiles].datasplitfunc[indx].setTabnum, p1);
	}
	if ((p = strstr(buf, CSETDATAELM))) {
		p1 = p + (int) strlen(CSETDATAELM) + 1;
		p = p1;
		while (*p != '\"' && *p != 0) p++;
		*p = 0;
		sexit[nfiles].datasplitfunc[indx].dataElement = (char *) calloc(1, (int) strlen(p1) + 1);
		strcpy(sexit[nfiles].datasplitfunc[indx].dataElement, p1);
	}
	if ((p = strstr(buf, CADDEXIT))) {
		char a[3][100];
		char *pp;
		splitEvent(a);
		pp = a[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit[nfiles].datasplitfunc[indx].iaddexit;
		sexit[nfiles].datasplitfunc[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0]) + 1);
		strcpy(sexit[nfiles].datasplitfunc[indx].saddExit[j].fieldName, a[0]);
		sexit[nfiles].datasplitfunc[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit[nfiles].datasplitfunc[indx].saddExit[j].clearFunc, a[1]);
		sexit[nfiles].datasplitfunc[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit[nfiles].datasplitfunc[indx].saddExit[j].eventName, a[2]);
		sexit[nfiles].datasplitfunc[indx].iaddexit++;
	}
	datasplitCondition(indx);
	return indx;
}

void datasplitCondition(int indx)
{
	int  j;
	char *p, *p1, *p2, *p3;
	if ((p = strstr(buf, CADDCONDITION))) {
		p2 = buf;
		while (*p2 != 0 && (*p2 == ' ' || *p2 == '\t')) p2++;
		*(p - 1) = 0;
		p1 = p + (int) strlen(CADDCONDITION) + 1;
		p = p1;
		while (*p != '(') p++;
		p++;
		p3 = p;
		while (*p != ')') p++;
		*p = 0;
		for (indx = 0; indx < sexit[nfiles].idatasplit; indx++) {
			if (strcmp(sexit[nfiles].datasplitfunc[indx].sName, p2) == 0) {
				j = sexit[nfiles].datasplitfunc[indx].iaddcon;
				sexit[nfiles].datasplitfunc[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p1) + 1);
				strcpy(sexit[nfiles].datasplitfunc[indx].addCondition[j], p1);
				sexit[nfiles].datasplitfunc[indx].iaddcon++;
				j++;
				sexit[nfiles].datasplitfunc[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p2) + 1);
				strcpy(sexit[nfiles].datasplitfunc[indx].addCondition[j], p2);
				sexit[nfiles].datasplitfunc[indx].iaddcon++;
				j++;
				sexit[nfiles].datasplitfunc[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p3) + 1);
				strcpy(sexit[nfiles].datasplitfunc[indx].addCondition[j], p3);
				sexit[nfiles].datasplitfunc[indx].iaddcon++;
			}
		}
	}
}


int dataMerge(int current, char *name)
{
	int indx, j;
	char *p, *p1;
	if (!strstr(name, CDATAMERGE)) return EOF;
	indx = adVarmi(current, name);
	if (indx == EOF) {
		indx = sexit[nfiles].idatamerge;
		sexit[nfiles].idatamerge++;
		sexit[nfiles].datamerge[indx].iaddexit = 0;
		sexit[nfiles].datamerge[indx].iaddcon = 0;
		sexit[nfiles].datamerge[indx].sName = (char *) calloc(1, (int) strlen(name) + 1);
		strcpy(sexit[nfiles].datamerge[indx].sName, name);
	}
	if ((p = strstr(buf, CSETTAB))) {
		while (*p != '{' && *p != 0) p++;
		p++;
		p1 = p;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit[nfiles].datamerge[indx].setTabnum = (char *) calloc(1, (int) strlen(p1) + 1);
		strcpy(sexit[nfiles].datamerge[indx].setTabnum, p1);
	}
	if ((p = strstr(buf, CSETMERGEELEMENTS))) {
		p1 = p + (int) strlen(CSETMERGEELEMENTS);
		while (*p1 != '{' && *p1 != 0) p1++;
		p1++;
		p = p1;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit[nfiles].datamerge[indx].setMergeElements = (char *) calloc(1, (int) strlen(p1) + 1);
		strcpy(sexit[nfiles].datamerge[indx].setMergeElements, p1);
	}
	if ((p = strstr(buf, CADDEXIT))) {
		char a[3][100];
		char *pp;
		splitEvent(a);
		pp = a[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit[nfiles].datamerge[indx].iaddexit;
		sexit[nfiles].datamerge[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0]) + 1);
		strcpy(sexit[nfiles].datamerge[indx].saddExit[j].fieldName, a[0]);
		sexit[nfiles].datamerge[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit[nfiles].datamerge[indx].saddExit[j].clearFunc, a[1]);
		sexit[nfiles].datamerge[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit[nfiles].datamerge[indx].saddExit[j].eventName, a[2]);
		sexit[nfiles].datamerge[indx].iaddexit++;
	}
	datamergeCondition(indx);
	return indx;
}

void datamergeCondition(int indx)
{
	int  j;
	char *p, *p1, *p2, *p3;
	if ((p = strstr(buf, CADDCONDITION))) {
		p2 = buf;
		while (*p2 != 0 && (*p2 == ' ' || *p2 == '\t')) p2++;
		*(p - 1) = 0;
		p1 = p + (int) strlen(CADDCONDITION) + 1;
		p = p1;
		while (*p != '(') p++;
		p++;
		p3 = p;
		while (*p != ')') p++;
		*p = 0;
		for (indx = 0; indx < sexit[nfiles].idatamerge; indx++) {
			if (strcmp(sexit[nfiles].datamerge[indx].sName, p2) == 0) {
				j = sexit[nfiles].datamerge[indx].iaddcon;
				sexit[nfiles].datamerge[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p1) + 1);
				strcpy(sexit[nfiles].datamerge[indx].addCondition[j], p1);
				sexit[nfiles].datamerge[indx].iaddcon++;
				j++;
				sexit[nfiles].datamerge[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p2) + 1);
				strcpy(sexit[nfiles].datamerge[indx].addCondition[j], p2);
				sexit[nfiles].datamerge[indx].iaddcon++;
				j++;
				sexit[nfiles].datamerge[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p3) + 1);
				strcpy(sexit[nfiles].datamerge[indx].addCondition[j], p3);
				sexit[nfiles].datamerge[indx].iaddcon++;
			}
		}
	}
}


int enable(int current, char *name)
{
	int indx, j;
	char *p, *p1;
	char asplit[3][100];
	if (!strstr(name, CENABLE)) return EOF;
	indx = adVarmi(current, name);
	if (indx == EOF) {
		indx = sexit[nfiles].ienable;
		sexit[nfiles].ienable++;
		sexit[nfiles].senable[indx].iaddexit = 0;
		sexit[nfiles].senable[indx].iaddcon = 0;
		sexit[nfiles].senable[indx].sName = (char *)calloc(1, strlen(name) + 1);
		strcpy(sexit[nfiles].senable[indx].sName, name);
	}
	if ((p = strstr(buf, CSETTABS))) {
		while (*p != '{' && *p != 0) p++;
		p++;
		p1 = p;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit[nfiles].senable[indx].setTabnums = (char *)calloc(1, strlen(p1) + 1);
		strcpy(sexit[nfiles].senable[indx].setTabnums, p1);
		// sexit[nfiles].senable[indx].setTabnum = atoi(p1);
	}
	p = strstr(buf, CADDEXIT);
	if (!p) p = strstr(buf, CADDEXITS);
	if (p) {
		char *pp;
		splitEvent(asplit);
		pp = asplit[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit[nfiles].senable[indx].iaddexit;
		sexit[nfiles].senable[indx].saddExit[j].fieldName =
			(char *)calloc(1, strlen(asplit[0]) + 1);
		strcpy(sexit[nfiles].senable[indx].saddExit[j].fieldName, asplit[0]);
		sexit[nfiles].senable[indx].saddExit[j].clearFunc =
			(char *)calloc(1, strlen(asplit[1]) + 1);
		if(sexit[nfiles].senable[indx].saddExit[j].clearFunc) strcpy(sexit[nfiles].senable[indx].saddExit[j].clearFunc, (char*)asplit[1]);
		sexit[nfiles].senable[indx].saddExit[j].eventName =
			(char *)calloc(1, strlen(asplit[2]) + 1);
		if(sexit[nfiles].senable[indx].saddExit[j].eventName) strcpy(sexit[nfiles].senable[indx].saddExit[j].eventName, (char*)asplit[2]);
		sexit[nfiles].senable[indx].iaddexit++;
	}
	enableCondition(indx);
	return indx;
}

void enableCondition(int indx)
{
	int  j;
	char *p, *p1, *p2, *p3, *pbuf;
	if ((p = strstr(buf, CADDCONDITION))) {
		pbuf = strstr(buf, CADDCONDITION);
		if (pbuf)
			pbuf = pbuf + 2;
		else pbuf = buf;
		p2 = pbuf;
		while (*p2 != 0 && (*p2 == ' ' || *p2 == '\t')) p2++;
		*(p - 1) = 0;
		p1 = p + strlen(CADDCONDITION) + 1;
		while (*p1 != ' ') p1++;
		if (*p1 == ' ') p1++;
		p = p1;
		while (*p != '(') p++;
		*p = 0;
		p++;
		p3 = p;
		while (*p != ')') p++;
		*p = 0;
		for (indx = 0; indx < sexit[nfiles].ienable; indx++) {
			if (strcmp(sexit[nfiles].senable[indx].sName, p2) == 0) {
				j = sexit[nfiles].senable[indx].iaddcon;
				sexit[nfiles].senable[indx].addCondition[j] =
					(char *)calloc(1, strlen(p1) + 1);
				strcpy(sexit[nfiles].senable[indx].addCondition[j], p1);
				j++;
				sexit[nfiles].senable[indx].addCondition[j] =
					(char *)calloc(1, strlen(p2) + 1);
				strcpy(sexit[nfiles].senable[indx].addCondition[j], p2);
				j++;
				sexit[nfiles].senable[indx].addCondition[j] =
					(char *)calloc(1, strlen(p3) + 1);
				strcpy(sexit[nfiles].senable[indx].addCondition[j], p3);
				sexit[nfiles].senable[indx].iaddcon++;
			}
		}
	}
}

int disable(int current, char *name)
{
	int  indx, j;
	char *p, *p1;
	char asplit[3][100];
	if (!strstr(name, CDISABLE)) return EOF;
	indx = adVarmi(current, name);
	if (indx == EOF) {
		indx = sexit[nfiles].idisable;
		sexit[nfiles].idisable++;
		sexit[nfiles].sdisable[indx].iaddexit = 0;
		sexit[nfiles].sdisable[indx].iaddcon = 0;
		sexit[nfiles].sdisable[indx].sName = (char *)calloc(1, strlen(name) + 1);
		strcpy(sexit[nfiles].sdisable[indx].sName, name);
	}
	if ((p = strstr(buf, CSETTAB))) {
		while (*p != '{' && *p != 0) p++;
		p++;
		p1 = p;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit[nfiles].sdisable[indx].setTabnum = (char *)calloc(1, strlen(p1) + 1);
		strcpy(sexit[nfiles].sdisable[indx].setTabnum, p1);
	}
	p = strstr(buf, CADDEXIT);
	if (!p) p = strstr(buf, CADDEXITS);
	if (p) {
		char *pp;
		splitEvent(asplit);
		pp = asplit[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit[nfiles].sdisable[indx].iaddexit;
		sexit[nfiles].sdisable[indx].saddExit[j].fieldName =
			(char *)calloc(1, strlen(asplit[0]) + 1);
		strcpy(sexit[nfiles].sdisable[indx].saddExit[j].fieldName, asplit[0]);
		sexit[nfiles].sdisable[indx].saddExit[j].clearFunc =
			(char *)calloc(1, strlen(asplit[1]) + 1);
		if (sexit[nfiles].sdisable[indx].saddExit[j].clearFunc) strcpy(sexit[nfiles].sdisable[indx].saddExit[j].clearFunc, (char*)asplit[1]);
		sexit[nfiles].sdisable[indx].saddExit[j].eventName =
			(char *)calloc(1, strlen(asplit[2]) + 1);
		if(sexit[nfiles].sdisable[indx].saddExit[j].eventName) strcpy(sexit[nfiles].sdisable[indx].saddExit[j].eventName, (char*)asplit[2]);
		sexit[nfiles].sdisable[indx].iaddexit++;
	}
	disableCondition(indx);
	return indx;
}

void disableCondition(int indx)
{
	int  j;
	char *p, *p1, *p2, *p3, *pbuf;
	if ((p = strstr(buf, CADDCONDITION))) {
		pbuf = strstr(buf, "*/");
		if (pbuf)
			pbuf = pbuf + 2;
		else pbuf = buf;
		p2 = pbuf;
		while (*p2 != 0 && (*p2 == ' ' || *p2 == '\t')) p2++;
		*(p - 1) = 0;
		p1 = p + strlen(CADDCONDITION) + 1;
		while (*p1 != ' ') p1++;
		p = p1;
		while (*p != '(') p++;
		*p = 0;
		p++;
		p3 = p;
		while (*p != ')') p++;
		*p = 0;
		for (indx = 0; indx < sexit[nfiles].idisable; indx++) {
			if (strcmp(sexit[nfiles].sdisable[indx].sName, p2) == 0) {
				j = sexit[nfiles].sdisable[indx].iaddcon;
				sexit[nfiles].sdisable[indx].addCondition[j] =
					(char *)calloc(1, strlen(p1) + 1);
				strcpy(sexit[nfiles].sdisable[indx].addCondition[j], p1);
				j++;
				sexit[nfiles].sdisable[indx].addCondition[j] =
					(char *)calloc(1, strlen(p2) + 1);
				strcpy(sexit[nfiles].sdisable[indx].addCondition[j], p2);
				j++;
				sexit[nfiles].sdisable[indx].addCondition[j] =
					(char *)calloc(1, strlen(p3) + 1);
				strcpy(sexit[nfiles].sdisable[indx].addCondition[j], p3);
				sexit[nfiles].sdisable[indx].iaddcon++;
			}
		}
	}
}
int visible(int current, char *name)
{
	int indx, j;
	char *p, *p1;
	char asplit[3][100];
	if (!strstr(name, CVISIBLE)) return EOF;
	indx = adVarmi(current, name);
	if (indx == EOF) {
		indx = sexit[nfiles].ivisible;
		sexit[nfiles].ivisible++;
		sexit[nfiles].svisible[indx].iaddexit = 0;
		sexit[nfiles].svisible[indx].iaddcon = 0;
		sexit[nfiles].svisible[indx].sName = (char *)calloc(1, strlen(name) + 1);
		strcpy(sexit[nfiles].svisible[indx].sName, name);
	}
	if ((p = strstr(buf, CSETTAB))) {
		while (*p != '{' && *p != 0) p++;
		p++;
		p1 = p;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit[nfiles].svisible[indx].setTabnum = (char *)calloc(1, strlen(p1) + 1);
		strcpy(sexit[nfiles].svisible[indx].setTabnum, p1);
	}
	p = strstr(buf, CADDEXIT);
	if (!p) p = strstr(buf, CADDEXITS);
	if (p) {
		char *pp;
		splitEvent(asplit);
		pp = asplit[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit[nfiles].svisible[indx].iaddexit;
		sexit[nfiles].svisible[indx].saddExit[j].fieldName =
			(char *)calloc(1, strlen(asplit[0]) + 1);
		strcpy(sexit[nfiles].svisible[indx].saddExit[j].fieldName, asplit[0]);
		sexit[nfiles].svisible[indx].saddExit[j].clearFunc =
			(char *)calloc(1, strlen(asplit[1]) + 1);
		if(sexit[nfiles].svisible[indx].saddExit[j].clearFunc) strcpy(sexit[nfiles].svisible[indx].saddExit[j].clearFunc, (char*)asplit[1]);
		sexit[nfiles].svisible[indx].saddExit[j].eventName =
			(char *)calloc(1, strlen(asplit[2]) + 1);
		if(sexit[nfiles].svisible[indx].saddExit[j].eventName) strcpy(sexit[nfiles].svisible[indx].saddExit[j].eventName, (char*)asplit[2]);
		sexit[nfiles].svisible[indx].iaddexit++;
	}
	visibleCondition(indx);
	return indx;
}


void visibleCondition(int indx)
{
	int  j;
	char *p, *p1, *p2, *p3, *pbuf;
	if ((p = strstr(buf, CADDCONDITION))) {
		pbuf = strstr(buf, "*/");
		if (pbuf)
			pbuf = pbuf + 2;
		else pbuf = buf;
		p2 = pbuf;
		while (*p2 != 0 && (*p2 == ' ' || *p2 == '\t')) p2++;
		*(p - 1) = 0;
		p1 = p + strlen(CADDCONDITION) + 1;
		while (*p1 != ' ') p1++;
		p = p1;
		while (*p != '(') p++;
		*p = 0;
		p++;
		p3 = p;
		while (*p != ')') p++;
		*p = 0;
		for (indx = 0; indx < sexit[nfiles].ivisible; indx++) {
			if (strcmp(sexit[nfiles].svisible[indx].sName, p2) == 0) {
				j = sexit[nfiles].svisible[indx].iaddcon;
				sexit[nfiles].svisible[indx].addCondition[j] =
					(char *)calloc(1, strlen(p1) + 1);
				strcpy(sexit[nfiles].svisible[indx].addCondition[j], p1);
				j++;
				sexit[nfiles].svisible[indx].addCondition[j] =
					(char *)calloc(1, strlen(p2) + 1);
				strcpy(sexit[nfiles].svisible[indx].addCondition[j], p2);
				j++;
				sexit[nfiles].svisible[indx].addCondition[j] =
					(char *)calloc(1, strlen(p3) + 1);
				strcpy(sexit[nfiles].svisible[indx].addCondition[j], p3);
				sexit[nfiles].svisible[indx].iaddcon++;
			}
		}
	}
}
int lstSearch(int current, char *name)
{
	int indx, j;
	char *p, *p1;
	char asplit[3][100];
	if (!strstr(name, CLSTSEARCH)) return EOF;
	indx = adVarmi(current, name);
	if (indx == EOF) {
		indx = sexit[nfiles].ilstsearch;
		sexit[nfiles].ilstsearch++;
		sexit[nfiles].slstsearch[indx].iaddexit = 0;
		sexit[nfiles].slstsearch[indx].iaddcon = 0;
		sexit[nfiles].slstsearch[indx].sName = (char *)calloc(1, strlen(name) + 1);
		strcpy(sexit[nfiles].slstsearch[indx].sName, name);
	}
	if ((p = strstr(buf, CSETTAB))) {
		while (*p != '{' && *p != 0) p++;
		p++;
		p1 = p;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit[nfiles].slstsearch[indx].setTabnum = (char *)calloc(1, strlen(p1) + 1);
		strcpy(sexit[nfiles].slstsearch[indx].setTabnum, p1);
	}
	p = strstr(buf, CADDEXIT);
	if (!p) p = strstr(buf, CADDEXITS);
	if (p) {
		char *pp;
		splitEvent(asplit);
		pp = asplit[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit[nfiles].slstsearch[indx].iaddexit;
		sexit[nfiles].slstsearch[indx].saddExit[j].fieldName =
			(char *)calloc(1, strlen(asplit[0]) + 1);
		strcpy(sexit[nfiles].slstsearch[indx].saddExit[j].fieldName, asplit[0]);
		sexit[nfiles].slstsearch[indx].saddExit[j].clearFunc =
			(char *)calloc(1, strlen(asplit[1]) + 1);
		if(sexit[nfiles].slstsearch[indx].saddExit[j].clearFunc) strcpy(sexit[nfiles].slstsearch[indx].saddExit[j].clearFunc, (char*)asplit[1]);
		sexit[nfiles].slstsearch[indx].saddExit[j].eventName =
			(char *)calloc(1, strlen(asplit[2]) + 1);
		if(sexit[nfiles].slstsearch[indx].saddExit[j].eventName) strcpy(sexit[nfiles].slstsearch[indx].saddExit[j].eventName, (char*)asplit[2]);
		sexit[nfiles].slstsearch[indx].iaddexit++;
	}
	lstsearchCondition(indx);
	return indx;
}

void lstsearchCondition(int indx)
{
	int  j;
	char *p, *p1, *p2, *p3, *pbuf;
	if ((p = strstr(buf, CADDCONDITION))) {
		pbuf = strstr(buf, "*/");
		if (pbuf)
			pbuf = pbuf + 2;
		else pbuf = buf;
		p2 = pbuf;
		while (*p2 != 0 && (*p2 == ' ' || *p2 == '\t')) p2++;
		*(p - 1) = 0;
		p1 = p + strlen(CADDCONDITION) + 1;
		while (*p1 != ' ') p1++;
		p = p1;
		while (*p != '(') p++;
		*p = 0;
		p++;
		p3 = p;
		while (*p != ')') p++;
		*p = 0;
		for (indx = 0; indx < sexit[nfiles].ilstsearch; indx++) {
			if (strcmp(sexit[nfiles].slstsearch[indx].sName, p2) == 0) {
				j = sexit[nfiles].slstsearch[indx].iaddcon;
				sexit[nfiles].slstsearch[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p1) + 1);
				strcpy(sexit[nfiles].slstsearch[indx].addCondition[j], p1);
				sexit[nfiles].slstsearch[indx].iaddcon++;
				j++;
				sexit[nfiles].slstsearch[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p2) + 1);
				strcpy(sexit[nfiles].slstsearch[indx].addCondition[j], p2);
				sexit[nfiles].slstsearch[indx].iaddcon++;
				j++;
				sexit[nfiles].slstsearch[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p3) + 1);
				strcpy(sexit[nfiles].slstsearch[indx].addCondition[j], p3);
				sexit[nfiles].slstsearch[indx].iaddcon++;
			}
		}
	}
}

void mysignalCondition(int indx)
{
	int  j;
	char* p, * p1, * p2, * p3, * pbuf;
	if ((p = strstr(buf, CADDCONDITION))) {
		pbuf = strstr(buf, "*/");
		if (pbuf)
			pbuf = pbuf + 2;
		else pbuf = buf;
		p2 = pbuf;
		while (*p2 != 0 && (*p2 == ' ' || *p2 == '\t')) p2++;
		*(p - 1) = 0;
		p1 = p + strlen(CADDCONDITION) + 1;
		while (*p1 != ' ') p1++;
		p = p1;
		while (*p != '(') p++;
		*p = 0;
		p++;
		p3 = p;
		while (*p != ')') p++;
		*p = 0;
		for (indx = 0; indx < sexit[nfiles].isignal; indx++) {
			if (strcmp(sexit[nfiles].signal[indx].sName, p2) == 0) {
				j = sexit[nfiles].signal[indx].iaddcon;
				sexit[nfiles].signal[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p1) + 1);
				strcpy(sexit[nfiles].signal[indx].addCondition[j], p1);
				sexit[nfiles].signal[indx].iaddcon++;
				j++;
				sexit[nfiles].signal[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p2) + 1);
				strcpy(sexit[nfiles].signal[indx].addCondition[j], p2);
				sexit[nfiles].signal[indx].iaddcon++;
				j++;
				sexit[nfiles].signal[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p3) + 1);
				strcpy(sexit[nfiles].signal[indx].addCondition[j], p3);
				sexit[nfiles].signal[indx].iaddcon++;
			}
		}
	}
}

int mysignal(int current, char* name)
{
	int indx, j;
	char* p, * p1;
	char asplit[3][100];
	if (!strstr(name, CSIGNAL)) return EOF;
	indx = adVarmi(current, name);
	if (indx == EOF) {
		indx = sexit[nfiles].isignal;
		sexit[nfiles].isignal++;
		sexit[nfiles].signal[indx].iaddexit = 0;
		sexit[nfiles].signal[indx].iaddcon = 0;
		sexit[nfiles].signal[indx].sName = (char*)calloc(1, strlen(name) + 1);
		strcpy(sexit[nfiles].signal[indx].sName, name);
	}
	if ((p = strstr(buf, CSETTAB))) {
		while (*p != '{' && *p != 0) p++;
		p++;
		p1 = p;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit[nfiles].signal[indx].setTabnum = (char*)calloc(1, strlen(p1) + 1);
		strcpy(sexit[nfiles].signal[indx].setTabnum, p1);
	}
	p = strstr(buf, CADDEXIT);
	if (!p) p = strstr(buf, CADDEXITS);
	if (p) {
		char* pp;
		splitEvent(asplit);
		pp = asplit[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit[nfiles].signal[indx].iaddexit;
		sexit[nfiles].signal[indx].saddExit[j].fieldName =
			(char*)calloc(1, strlen(asplit[0]) + 1);
		strcpy(sexit[nfiles].signal[indx].saddExit[j].fieldName, asplit[0]);
		sexit[nfiles].signal[indx].saddExit[j].clearFunc =
			(char*)calloc(1, strlen(asplit[1]) + 1);
		if (sexit[nfiles].signal[indx].saddExit[j].clearFunc) strcpy((char*)sexit[nfiles].signal[indx].saddExit[j].clearFunc, asplit[1]);
		sexit[nfiles].signal[indx].saddExit[j].eventName =
			(char*)calloc(1, strlen(asplit[2]) + 1);
		if (sexit[nfiles].signal[indx].saddExit[j].eventName) strcpy((char*)sexit[nfiles].signal[indx].saddExit[j].eventName, asplit[2]);
		sexit[nfiles].signal[indx].iaddexit++;
	}
	mysignalCondition(indx);
	return indx;
}

int addExit(int current, char *name)
{
	int indx, j;
	char *pp;
	char asplit[3][100];
	if (!strstr(name, CADDEXIT)) return EOF;
	indx = adVarmi(current, name);
	splitEvent(asplit);
	pp = asplit[0];
	while (*pp != 0 && *pp != '(') pp++;
	*pp = 0;
	switch (current) {
	case PDATASPLIT:
		j = sexit[nfiles].datasplitfunc[indx].iaddexit;
		sexit[nfiles].datasplitfunc[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(asplit[0]) + 1);
		strcpy(sexit[nfiles].datasplitfunc[indx].saddExit[j].fieldName, asplit[0]);
		sexit[nfiles].datasplitfunc[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(asplit[1]) + 1);
		strcpy(sexit[nfiles].datasplitfunc[indx].saddExit[j].clearFunc, asplit[1]);
		sexit[nfiles].datasplitfunc[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(asplit[2]) + 1);
		strcpy(sexit[nfiles].datasplitfunc[indx].saddExit[j].eventName, asplit[2]);
		sexit[nfiles].datasplitfunc[indx].iaddexit++;
		break;
	case PDATAMERGE:
		j = sexit[nfiles].datamerge[indx].iaddexit;
		sexit[nfiles].datamerge[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(asplit[0]) + 1);
		strcpy(sexit[nfiles].datamerge[indx].saddExit[j].fieldName, asplit[0]);
		sexit[nfiles].datamerge[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(asplit[1]) + 1);
		strcpy(sexit[nfiles].datamerge[indx].saddExit[j].clearFunc, asplit[1]);
		sexit[nfiles].datamerge[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(asplit[2]) + 1);
		strcpy(sexit[nfiles].datamerge[indx].saddExit[j].eventName, asplit[2]);
		sexit[nfiles].datamerge[indx].iaddexit++;
		break;
	case PSETVALUE:
		j = sexit[nfiles].svalue[indx].iaddexit;
		sexit[nfiles].svalue[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(asplit[0]) + 1);
		strcpy(sexit[nfiles].svalue[indx].saddExit[j].fieldName, asplit[0]);
		sexit[nfiles].svalue[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(asplit[1]) + 1);
		strcpy(sexit[nfiles].svalue[indx].saddExit[j].clearFunc, asplit[1]);
		sexit[nfiles].svalue[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(asplit[2]) + 1);
		strcpy(sexit[nfiles].svalue[indx].saddExit[j].eventName, asplit[2]);
		sexit[nfiles].svalue[indx].iaddexit++;
		break;
	case PSETCLEAR:
		j = sexit[nfiles].setmanda[indx].iaddexit;
		sexit[nfiles].setmanda[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(asplit[0]) + 1);
		strcpy(sexit[nfiles].setmanda[indx].saddExit[j].fieldName, asplit[0]);
		sexit[nfiles].setmanda[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(asplit[1]) + 1);
		strcpy(sexit[nfiles].setmanda[indx].saddExit[j].clearFunc, asplit[1]);
		sexit[nfiles].setmanda[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(asplit[2]) + 1);
		strcpy(sexit[nfiles].setmanda[indx].saddExit[j].eventName, asplit[2]);
		sexit[nfiles].setmanda[indx].iaddexit++;
		break;
	case PCLEAR:
		j = sexit[nfiles].scmanda[indx].iaddexit;
		sexit[nfiles].scmanda[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(asplit[0]) + 1);
		strcpy(sexit[nfiles].scmanda[indx].saddExit[j].fieldName, asplit[0]);
		sexit[nfiles].scmanda[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(asplit[1]) + 1);
		strcpy(sexit[nfiles].scmanda[indx].saddExit[j].clearFunc, asplit[1]);
		sexit[nfiles].scmanda[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(asplit[2]) + 1);
		strcpy(sexit[nfiles].scmanda[indx].saddExit[j].eventName, asplit[2]);
		sexit[nfiles].scmanda[indx].iaddexit++;
		break;
	case PINVISIBLE:
		j = sexit[nfiles].sinvisible[indx].iaddexit;
		sexit[nfiles].sinvisible[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(asplit[0]) + 1);
		strcpy(sexit[nfiles].sinvisible[indx].saddExit[j].fieldName, asplit[0]);
		sexit[nfiles].sinvisible[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(asplit[1]) + 1);
		strcpy(sexit[nfiles].sinvisible[indx].saddExit[j].clearFunc, asplit[1]);
		sexit[nfiles].sinvisible[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(asplit[2]) + 1);
		strcpy(sexit[nfiles].sinvisible[indx].saddExit[j].eventName, asplit[2]);
		sexit[nfiles].sinvisible[indx].iaddexit++;
		break;
	case PSHOWMSG:
		j = sexit[nfiles].showMsg[indx].iaddexit;
		sexit[nfiles].showMsg[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(asplit[0] + 1));
		strcpy(sexit[nfiles].showMsg[indx].saddExit[j].fieldName, asplit[0]);
		sexit[nfiles].showMsg[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(asplit[1]) + 1);
		strcpy(sexit[nfiles].showMsg[indx].saddExit[j].clearFunc, asplit[1]);
		sexit[nfiles].showMsg[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(asplit[2]) + 1);
		strcpy(sexit[nfiles].showMsg[indx].saddExit[j].eventName, asplit[2]);
		sexit[nfiles].showMsg[indx].iaddexit++;
		break;
	case PQUERYLSTFUNC:
		j = sexit[nfiles].squeryList[indx].iaddexit;
		sexit[nfiles].squeryList[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(asplit[0]) + 1);
		strcpy(sexit[nfiles].squeryList[indx].saddExit[j].fieldName, asplit[0]);
		sexit[nfiles].squeryList[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(asplit[1]) + 1);
		strcpy(sexit[nfiles].squeryList[indx].saddExit[j].clearFunc, asplit[1]);
		sexit[nfiles].squeryList[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(asplit[2]) + 1);
		strcpy(sexit[nfiles].squeryList[indx].saddExit[j].eventName, asplit[2]);
		sexit[nfiles].squeryList[indx].iaddexit++;
		break;
	case PENABLE:
		j = sexit[nfiles].senable[indx].iaddexit;
		sexit[nfiles].senable[indx].saddExit[j].fieldName =
			(char *)calloc(1, strlen(asplit[0]) + 1);
		strcpy(sexit[nfiles].senable[indx].saddExit[j].fieldName, asplit[0]);
		sexit[nfiles].senable[indx].saddExit[j].clearFunc =
			(char *)calloc(1, strlen(asplit[1]) + 1);
		strcpy(sexit[nfiles].senable[indx].saddExit[j].clearFunc, asplit[1]);
		sexit[nfiles].senable[indx].saddExit[j].eventName =
			(char *)calloc(1, strlen(asplit[2]) + 1);
		strcpy(sexit[nfiles].senable[indx].saddExit[j].eventName, asplit[2]);
		sexit[nfiles].senable[indx].iaddexit++;
		break;
	case PDISABLE:
		j = sexit[nfiles].sdisable[indx].iaddexit;
		sexit[nfiles].sdisable[indx].saddExit[j].fieldName =
			(char *)calloc(1, strlen(asplit[0]) + 1);
		strcpy(sexit[nfiles].sdisable[indx].saddExit[j].fieldName, asplit[0]);
		sexit[nfiles].senable[indx].saddExit[j].clearFunc =
			(char *)calloc(1, strlen(asplit[1]) + 1);
		strcpy(sexit[nfiles].sdisable[indx].saddExit[j].clearFunc, asplit[1]);
		sexit[nfiles].sdisable[indx].saddExit[j].eventName =
			(char *)calloc(1, strlen(asplit[2]) + 1);
		strcpy(sexit[nfiles].sdisable[indx].saddExit[j].eventName, asplit[2]);
		sexit[nfiles].sdisable[indx].iaddexit++;
		break;
	case PVISIBLE:
		j = sexit[nfiles].svisible[indx].iaddexit;
		sexit[nfiles].svisible[indx].saddExit[j].fieldName =
			(char *)calloc(1, strlen(asplit[0]) + 1);
		strcpy(sexit[nfiles].svisible[indx].saddExit[j].fieldName, asplit[0]);
		sexit[nfiles].svisible[indx].saddExit[j].clearFunc =
			(char *)calloc(1, strlen(asplit[1]) + 1);
		strcpy(sexit[nfiles].svisible[indx].saddExit[j].clearFunc, asplit[1]);
		sexit[nfiles].svisible[indx].saddExit[j].eventName =
			(char *)calloc(1, strlen(asplit[2]) + 1);
		strcpy(sexit[nfiles].svisible[indx].saddExit[j].eventName, asplit[2]);
		sexit[nfiles].svisible[indx].iaddexit++;
		break;
	case PLSTSEARCH:
		j = sexit[nfiles].slstsearch[indx].iaddexit;
		sexit[nfiles].slstsearch[indx].saddExit[j].fieldName =
			(char *)calloc(1, strlen(asplit[0]) + 1);
		strcpy(sexit[nfiles].slstsearch[indx].saddExit[j].fieldName, asplit[0]);
		sexit[nfiles].slstsearch[indx].saddExit[j].clearFunc =
			(char *)calloc(1, strlen(asplit[1]) + 1);
		strcpy(sexit[nfiles].slstsearch[indx].saddExit[j].clearFunc, asplit[1]);
		sexit[nfiles].slstsearch[indx].saddExit[j].eventName =
			(char *)calloc(1, strlen(asplit[2]) + 1);
		strcpy(sexit[nfiles].slstsearch[indx].saddExit[j].eventName, asplit[2]);
		sexit[nfiles].slstsearch[indx].iaddexit++;
		break;
	case PSIGNAL:
		j = sexit[nfiles].signal[indx].iaddexit;
		sexit[nfiles].signal[indx].saddExit[j].fieldName =
			(char *)calloc(1, strlen(asplit[0]) + 1);
		strcpy(sexit[nfiles].signal[indx].saddExit[j].fieldName, asplit[0]);
		sexit[nfiles].signal[indx].saddExit[j].clearFunc =
			(char *)calloc(1, strlen(asplit[1]) + 1);
		strcpy(sexit[nfiles].signal[indx].saddExit[j].clearFunc, asplit[1]);
		sexit[nfiles].signal[indx].saddExit[j].eventName =
			(char *)calloc(1, strlen(asplit[2]) + 1);
		strcpy(sexit[nfiles].signal[indx].saddExit[j].eventName, asplit[2]);
		sexit[nfiles].signal[indx].iaddexit++;
		break;
	}
	return indx;
}

int queryList(int current, char *name)
{
	int indx, j;
	char *p, *p1;
	char a[3][100];
	char *pp;

	if (!strstr(name, CQUERYLSTFUNC)) return EOF;
	indx = adVarmi(current, name);

	if (indx == EOF) {
		indx = sexit[nfiles].iqueryList;
		sexit[nfiles].iqueryList++;
		sexit[nfiles].squeryList[indx].iaddexit = 0;
		sexit[nfiles].squeryList[indx].sName = (char *) calloc(1, (int) strlen(name) + 1);
		strcpy(sexit[nfiles].squeryList[indx].sName, name);
	}
	if ((p = strstr(buf, CSETTAB))) {
		p1 = strstr(buf, CSETTAB);
		p = p1 + (int) strlen(CSETTAB);
		p1 = p;
		while (*p != ')' && *p != 0) p++;
		*p = 0;
		sexit[nfiles].squeryList[indx].setTabnum = (char *)calloc(1, strlen(p1)+1);
		strcpy(sexit[nfiles].squeryList[indx].setTabnum, p1);
	}
	if ((p = strstr(buf, CADDEXIT))) {
		splitEvent(a);
		pp = a[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit[nfiles].squeryList[indx].iaddexit;
		sexit[nfiles].squeryList[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0]) + 1);
		strcpy(sexit[nfiles].squeryList[indx].saddExit[j].fieldName, a[0]);
		sexit[nfiles].squeryList[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit[nfiles].squeryList[indx].saddExit[j].clearFunc, a[1]);
		sexit[nfiles].squeryList[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit[nfiles].squeryList[indx].saddExit[j].eventName, a[2]);
		sexit[nfiles].squeryList[indx].iaddexit++;
	}
	if ((p = strstr(buf, CSETQUERYLST))) {
		p1 = strstr(buf, CSETQUERYLST);
		p = p1 + (int) strlen(CSETQUERYLST) + 1;
		p1 = p;
		p = strstr(p, "\")");
		if (p) {
			p += 2;
			*p = 0;
		}
		// sexit[nfiles].squeryList[indx].sName = (char *) calloc(1, (int) strlen(name)+1);
		// strcpy(sexit[nfiles].squeryList[indx].sName, name);
		if(p1) {
			sexit[nfiles].squeryList[indx].sQuerylist = (char *) calloc(1, (int) strlen(p1) + 1);
			if (sexit[nfiles].squeryList[indx].sQuerylist)
				strcpy(sexit[nfiles].squeryList[indx].sQuerylist, p1);
		}
	}
	return indx;
}

int exitMi()
{
	int ret = EOF;

	if ((fexit == 0) &&
		(strstr(buf, CEXIT) || strstr(buf, cexit))) {
		int current = EOF;
		char *p, *p1;
		char name[200];
		fexit = 1;
		Processed = 1;

		// CENDINIT "}"
		while (1) {
			ret = mygetline(CENDINIT2);
			if (ret != EOF) { 
				Processed = 1; 
				break; 
			}
			if (strstr(buf, CENDINIT) && !strstr(buf, CBEGIN)) {
				Processed = 1;
				break;
			}
			Processed = 1;
			if (strstr(buf, cexit) || strstr(buf, "new") || (current != EOF)) {
				if ((strstr(buf, cexit) || strstr(buf, "new")) &&
					!strstr(buf, CCONDITION) || strstr(buf, CSETTABNUM) || strstr(buf, CSETTAB) ||
					strstr(buf, CSETTABD) || strstr(buf, CSETTABS) || strstr(buf, CADDEXIT) ||
					strstr(buf, CADDEXITS)) {
					p = strstr(buf, cexit);
					if (!p) {
						p1 = strstr(buf, "    ");
						if (p1) p = p1 + 5;
						else p = buf;
						p1 = strstr(p, " ");
					}
					else {
						p1 = strstr(p, " "); 
					} 
					if (p1) {
						p1++;
						p = strstr(p1, " ");
						if(p) *p = 0;
						strcpy(name, p1);
					}
				}
				ret = mygetline(CDUMMY);
				if (getinsym(CCLEAR) == PCLEAR) {
					current = PCLEAR;
					if (clearMandatory(current, name) != EOF) continue;
				}
				if (getinsym(CSETCLEAR) == PSETCLEAR) {
					current = PSETCLEAR;
					if (setMandatory(current, name) != EOF) continue;
				}
				if (getinsym(CSHOWMSG) == PSHOWMSG) {
					current = PSHOWMSG;
					if (showMessage(current, name) != EOF) continue;
				}
				if (getinsym(CINVISIBLE) == PINVISIBLE) {
					current = PINVISIBLE;
					if (invisible(current, name) != EOF) continue;
				}
				if (getinsym(CSETVALUE) == PSETVALUE) {
					current = PSETVALUE;
					if (setValue(current, name) != EOF) continue;
				}
				if (getinsym(CDATASPLIT) == PDATASPLIT) {
					current = PDATASPLIT;
					if (dataSplit(current, name) != EOF) continue;
				}
				if (getinsym(CDATAMERGE) == PDATAMERGE) {
					current = PDATAMERGE;
					if (dataMerge(current, name) != EOF) continue;
				}
				if (getinsym(CADDEXIT) == PADDEXIT) {
					current = PADDEXIT;
					if (addExit(current, name) != EOF) continue;
				}
				if (getinsym(CQUERYLSTFUNC) == PQUERYLSTFUNC) {
					current = PQUERYLSTFUNC;
					if (queryList(current, name) != EOF) continue;
				}
				if (getinsym((char *)CENABLE) == PENABLE) {
					current = PENABLE;
					if (enable(current, name) != EOF) continue;
				}
				if (getinsym((char *)CDISABLE) == PDISABLE) {
					current = PDISABLE;
					if (disable(current, name) != EOF) continue;
				}
				if (getinsym((char *)CVISIBLE) == PVISIBLE) {
					current = PVISIBLE;
					if (visible(current, name) != EOF) continue;
				}
				if (getinsym((char *)CSIGNAL) == PSIGNAL) {
					current = PSIGNAL;
					if (mysignal(current, name) != EOF) continue;
				}
				if (getinsym((char *)CLSTSEARCH) == PLSTSEARCH) {
					current = PLSTSEARCH;
					if (lstSearch(current, name) != EOF) continue;
				}
			}
		}
		// fexit = 0;
		Processed = 1;
	}
	return ret;
}

void getPanel(char *xname, char *txt)
{
	char *p, *p1;
	p = strstr(buf, txt);
	p1 = p + (int) strlen(txt);
	p = strstr(p1, "(");
	*p = 0;
	strcpy(xname, p1);
}

int getPanelno(char *xname)
{
	int len = (int) strlen(xname);
	char *p = xname;
	while (!(*p >= '0' && *p <= '9')) {
		p++;
		if (*p == 0) break;
	}
	if ((int) strlen(p) > 0) {
		return atoi(p);
	}
	return 0;
}

int fieldtype(char *p)
{
	if (strstr(p, "TextField")) return panelTEXT;
	if (strstr(p, "Label")) return panelLABEL;
	if (strstr(p, "Radio")) return panelRBUTTON;
	if (strstr(p, "Button")) return panelBUTTON;
	if (strstr(p, "ComboBox")) return panelCOMBOX;
	if (strstr(p, "CheckBox")) return panelCHKBOX;
	if (strstr(p, "ScrollPane")) return panelSCROLL;
	if (strstr(p, "Table")) return panelTABLE;
	return EOF;
}

#define panelTITLE ".setTitle("

int panelMi()
{
	int indx, ret, j;
	char *p, *p1;
	char xname[200];

	ret = EOF;
	if (buf[0] == '}') {
		mygetline(CDUMMY);
	}
	if ((fpanel == 0) && strstr(buf, CPANELDEC)) {
		fpanel = 1;
		getPanel(xname, CPANELDEC);
		Processed = 1;
		indx = ispanel[nfiles];
		spanel[nfiles][indx].panNo = getPanelno(xname);

		ispanel[nfiles]++;
		spanel[nfiles][indx].panelName = (char *) calloc(1, (int) strlen(xname) + 1);
		strcpy(spanel[nfiles][indx].panelName, xname);
		spanel[nfiles][indx].ifield = 0;
		while (1) {
			ret = mygetline(CENDINIT2);
			if (ret != EOF) { 
				Processed = 1; 
				break;
			}
			if (strstr(buf, CENDINIT) && !strstr(buf, CBEGIN)) {
				Processed = 1;
				break;
			}
			Processed = 1;
			if (strstr(buf, CPNLBOUNDS)) {
				// bounds
				boundVals(&spanel[nfiles][indx].spnlbound, CPNLBOUNDS);
				continue;
			}
			if (strstr(buf, CPNLADD)) {
				int ff;
				p1 = strstr(buf, CPNLADD);
				if(p1) {
					p = p1 + (int) strlen(CPNLADD);
					p1 = p;
					while (*p != 0 && *p != '(') p++;
					*p = 0;
					j = spanel[nfiles][indx].ifield;
					ff = fieldtype(p1);
					spanel[nfiles][indx].fields[j].fieldname = (char *) calloc(1, (int) strlen(p1) + 1);
					strcpy(spanel[nfiles][indx].fields[j].fieldname, p1);
					spanel[nfiles][indx].fields[j].ftype = ff;
					spanel[nfiles][indx].ifield++;
					continue;
				}
			}
			if (strstr(buf, panelTITLE)) {
				p1 = strstr(buf, panelTITLE);
				p = p1 + (int) strlen(panelTITLE) + 1;
				p1 = p;
				while (*p != 0 && *p != '"') p++;
				if(p) *p = 0;
				if(p1) {
					spanel[nfiles][indx].setTitle = (char *) calloc(1, (int) strlen(p1) + 1);
					strcpy(spanel[nfiles][indx].setTitle, p1);
					continue;
				}
			}
		}
		fpanel = 0;
	}
	return ret;
}


void boundVals(struct BOUNDS *s, char * txt)
{
	char *p, *p1;
	int x[4];
	
	p = strstr(buf, txt);
	p1 = p + (int) strlen(txt);
	mysplit(x, p1, ',');
	s->x0 = x[0];
	s->y0 = x[1];
	s->x1 = x[2];
	s->y1 = x[3];
}

void getName(char *xname, char *txt)
{
	char *p, *p1;
	p = strstr(buf, txt);
	p1 = p + (int) strlen(txt);
	if(p1) {
		p = strstr(p1, "(");
		if (p) *p = 0;
		p = strstr(p1, " =");
		if (p) *p = 0;
		strcpy(xname, p1);
	}
}

int getLabel(char *xname)
{
	int i, j;
	// label dizisi icinde karsit deger var mi
	for (i = 0; i <= panelno; i++) {
		for (j = 0; j <= lblno; j++)
			if ((int) strlen(labels[i][j]) > 0)
				if (strcasecmp(labels[i][j], xname) == 0)
					return i * 100 + j;
	}
	return EOF;
}

int getTextField(char *xname)
{
	int i, j;
	for (i = 0; i <= panelno; i++) {
		for (j = 0; j <= txtno; j++)
			if ((int) strlen(txtfields[i][j]) > 0)
				if (strcasecmp(txtfields[i][j], xname) == 0)
					return i * 100 + j;
	}
	return EOF;
}

int getRbutton(char *xname)
{
	int i, j;
	for (i = 0; i <= panelno; i++) {
		for (j = 0; j <= buttongrpno; j++)
			if ((int) strlen(buttongrps[i][j]) > 0)
				if (strcasecmp(buttongrps[i][j], xname) == 0)
					return i * 100 + j;
	}
	return EOF;
}

int getButton(char *xname)
{
	int i, j;
	for (i = 0; i <= panelno; i++) {
		for (j = 0; j <= buttonno; j++)
			if ((int) strlen(buttons[i][j]) > 0)
				if (strcasecmp(buttons[i][j], xname) == 0)
					return i * 100 + j;
	}
	return EOF;
}

int getCombo(char *xname)
{
	int i, j;
	for (i = 0; i <= panelno; i++) {
		for (j = 0; j <= combono; j++)
			if ((int) strlen(combobox[i][j]) > 0)
				if (strcasecmp(combobox[i][j], xname) == 0)
					return i * 100 + j;
	}
	return EOF;
}

int getLoader(char *xname)
{
	int i, j;
	for (i = 0; i <= panelno; i++) {
		for (j = 0; j <= loadno; j++)
			if ((int) strlen(loads[i][j]) > 0)
				if (strcasecmp(loads[i][j], xname) == 0)
					return i * 100 + j;
	}
	return EOF;
}

int getCheck(char *xname)
{
	int i, j;
	for (i = 0; i <= panelno; i++) {
		for (j = 0; j <= checkno; j++)
			if ((int) strlen(chkBox[i][j]) > 0)
				if (strcasecmp(chkBox[i][j], xname) == 0)
					return i * 100 + j;
	}
	return EOF;
}


int getScroll(char *xname)
{
	int i, j;
	for (i = 0; i <= panelno; i++) {
		for (j = 0; j <= scrollno; j++)
			if ((int) strlen(tscroll[i][j]) > 0)
				if (strcasecmp(tscroll[i][j], xname) == 0)
					return i * 100 + j;
	}
	return EOF;
}

int getTable(char *xname)
{
	int i, j;
	for (i = 0; i <= panelno; i++) {
		for (j = 0; j <= tableno; j++)
			if ((int) strlen(table[i][j]) > 0)
				if (strcasecmp(table[i][j], xname) == 0)
					return i * 100 + j;
	}
	return EOF;
}

int ColkDataName(char **kdataname, char *pkdataname)
{
	char *p, *p1;
	p = strstr(buf, pkdataname);
	if (p) {
		p = p + strlen(pkdataname) + 1;
		p1 = p;
		while (*p && *p != '\"') p++;
		*p = 0;
		*kdataname = (char *)calloc(1, strlen(p1) + 1);
		strcpy(*kdataname, p1);
	}
	return EOF;
}

int ColWidth(int *colw, char *psetcol)
{
	char *p, *p1;
	p = strstr(buf, psetcol);
	if (p) {
		p = p + strlen(psetcol) + 1;
		p1 = p;
		while (*p && *p != '\"') p++;
		*p = 0;
		*colw = atoi(p1);
	}
	return EOF;
}

int ColTitle(char **ptitle, char *psettitle)
{
	char *p, *p1;
	p = strstr(buf, psettitle);
	if (p) {
		p = p + strlen(psettitle) + 1;
		p1 = p;
		while (*p && *p != '\"') p++;
		*p = 0;
		*ptitle = (char *)calloc(1, strlen(p1) + 1);
		strcpy(*ptitle, p1);
	}
	return EOF;
}

int ColEditVal(int *editval, char *psetedit)
{
	char *p, *p1;
	p = strstr(buf, psetedit);
	if (p) {
		p = p + strlen(psetedit) + 1;
		p1 = p;
		while (*p && *p != '\"') p++;
		*p = 0;
		*editval = 0;
		if (strcmp(p1, "true") == 0)
		   *editval = 1;
	}
	return EOF;
}

int ColumnVals(struct COLUMN *c, char *addcol, int smart)
{
	char *p, *p1;
	if (strstr(buf, addcol)) {
		if (!smart) {
			p = strstr(buf, addcol);
			p1 = p + (int) strlen(addcol) + 1;
			p = p1;
			while (*p != 0 && *p != '\"') p++;
			*p = 0;
		}
		else {
			p = strstr(buf, addcol);
			p1 = p + (int) strlen(addcol);
			p = p1;
			while (*p != 0 && *p != ')') p++;
			*p = 0;
		}
		c->text = (char *) calloc(1, (int) strlen(p1));
		strcpy(c->text, p1);
		p1 = p + 2;
		p = p1;
		while (*p != 0 && *p != ',') p++;
		*p = 0;
		c->begincol = atoi(p1);
		p1 = p + 1;
		p = p1;
		while (*p != 0 && *p != ',') p++;
		*p = 0;
		c->endcol = atoi(p1);
		p1 = p + 4;
		p = p1;
		while (*p != 0 && *p != ',') p++;
		*p = 0;
		c->left = atoi(p1);
		p1 = p + 2;
		p = p1;
		while (*p != 0 && *p != '\"') p++;
		*p = 0;
		if (!smart) {
			c->dataname = (char *) calloc(1, (int) strlen(p1) + 1);
			strcpy(c->dataname, p1);
		}
		else {
			c->dataname = (char *) calloc(1, (int) strlen(c->text) + 1);
			strcpy(c->dataname, c->text);
		}
		p1 = p + 2;
		p = p1;
		while (*p != 0 && *p != ',') p++;
		*p = 0;
		c->dtype = (char *) calloc(1, (int) strlen(p1) + 1);
		strcpy(c->dtype, p1);
		p1 = p + 2;
		p = p1;
		while (*p != 0 && *p != '\"') p++;
		*p = 0;
		c->dpoint = atoi(p1);
		p1 = p + 5;
		p = p1;
		while (*p != 0 && *p != ',') p++;
		*p = 0;
		c->size = atoi(p1);
		return true;
	}
	return EOF;
}

int elements()
{
	// select Text, label, button and radio button functions
	int  indx, ret = EOF;
	char *p, *p1;
	char xname[350];

    // if (buf[0] == '}') {
	if (strstr(buf, "}")) {
		Processed = 1;
		ret = mygetline(CDUMMY);
		return ret;
	}
	if ((flblfunc == 0) && strstr(buf, CLBLFUNC)) {
		flblfunc = 1;
		Processed = 1;
		getName(xname, CLBLFUNC);
		if (strlen(xname) > 0) {
			indx = islabel[nfiles];
			slabel[nfiles][indx].lblno = getLabel(xname);
			slabel[nfiles][indx].lbl = (char*)calloc(1, (int)strlen(xname) + 1);
			strcpy(slabel[nfiles][indx].lbl, xname);
			slabel[nfiles][indx].lbltext = 0;
			slabel[nfiles][indx].lblline = 0;
			islabel[nfiles]++;
		}
		else return ret;
		while (1) {
			ret = mygetline(CENDINIT2);
			if (ret != EOF) { 
				Processed = 1; 
				break;
			}
			if (strstr(buf, CENDINIT) && !strstr(buf, CBEGIN)) {
				Processed = 1;
				break;
			}
			Processed = 1;
			if (strstr(buf, LBLBOUND)) {
				// bounds
				boundVals(&slabel[nfiles][indx].slblbound, LBLBOUND);
				continue;
			}
			if (strstr(buf, LBLNAME)) {
				// LBLNAME setName found get name
				p1 = strstr(buf, LBLNAME) + (int) strlen(LBLNAME);
				p1++;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				slabel[nfiles][indx].name = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(slabel[nfiles][indx].name, p1);
				continue;
			}
			if (strstr(buf, LBLTXT)) {
				// LBLTEXT setText found get text
				p1 = strstr(buf, LBLTXT) + (int) strlen(LBLTXT);
				p1++;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				slabel[nfiles][indx].text = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(slabel[nfiles][indx].text, p1);
				continue;
			}
			if (strstr(buf, TXTDNAME)) {
				// LBLTEXT setText found get text
				p1 = strstr(buf, TXTDNAME) + (int)strlen(TXTDNAME);
				p1++;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				slabel[nfiles][indx].dname = (char*)calloc(1, (int)strlen(p1) + 1);
				strcpy(slabel[nfiles][indx].dname, p1);
				continue;
			}
			if (strstr(buf, CSETTABORDER)) {
				p1 = strstr(buf, CSETTABORDER) + strlen(CSETTABORDER);
				p1++;
				p = p1;
				while (*p != 0 && *p != '"') p++;
				*p = 0;
				slabel[nfiles][indx].tabOrder = atoi(p1);
			}
		}
		flblfunc = 0;
	}
	if ((ftxtfunc == 0) && strstr(buf, CTXTFUNC)) {
		ftxtfunc = 1;
		Processed = 1;
		getName(xname, CTXTFUNC);
		if (strlen(xname) > 0) {
			indx = istext[nfiles];
			stextfield[nfiles][indx].txtno = getTextField(xname);
			stextfield[nfiles][indx].text = (char*)calloc(1, (int)strlen(xname) + 1);
			strcpy(stextfield[nfiles][indx].text, xname);
			stextfield[nfiles][indx].txtline = 0;
			istext[nfiles]++;
		}
		else return ret;
		while (1) {
			ret = mygetline(CENDINIT2);
			if (ret != EOF) { 
				Processed = 1; 
				break;
			}
			if (strstr(buf, CENDINIT) && !strstr(buf, CBEGIN)) {
				Processed = 1;
				break;
			}
			Processed = 1;
			if (strstr(buf, TXTBOUND)) {
				// bounds
				boundVals(&stextfield[nfiles][indx].stxtbound, TXTBOUND);
				continue;
			}
			if (strstr(buf, TXTENABLED)) {
				// move enable value
				p1 = strstr(buf, TXTENABLED);
				p1 = p1 + (int) strlen(TXTENABLED);
				if (strncasecmp(p1, "false", 5) == 0)
					stextfield[nfiles][indx].enabled = false;
				else
					stextfield[nfiles][indx].enabled = true;
				continue;
			}
			if (strstr(buf, TXTREQ)) {
				p1 = strstr(buf, TXTREQ);
				p1 = p1 + (int) strlen(TXTREQ);
				if (strncasecmp(p1, "false", 5) == 0)
					stextfield[nfiles][indx].required = false;
				else
					stextfield[nfiles][indx].required = true;
			}
			if (strstr(buf, TXTFONT)) {
				// move font value
				p1 = strstr(buf, TXTFONT);
				p1 = p1 + (int) strlen(TXTFONT);
				while (*p1 != 0 && *p1 != '(') p1++;
				p1++;
				p = p1;
				while (*p != 0 && *p != ')') p++;
				*p = 0;
				stextfield[nfiles][indx].font = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(stextfield[nfiles][indx].font, p1);
				continue;
			}
			if (strstr(buf, TXTDNAME)) {
				// move data Name value
				p1 = strstr(buf, TXTDNAME);
				p1 = p1 + (int) strlen(TXTDNAME);
				p1++;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				stextfield[nfiles][indx].dataName = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(stextfield[nfiles][indx].dataName, p1);
				// label icin text sira no ekle
				// ======================> Bunu yapmamak gerekiyor....
				//if (islabel > 0) {
				//	if (slabel[nfiles][islabel - 1].lbltext == 0) {
				//		slabel[nfiles][islabel - 1].lbltext = (char *)calloc(1, (int)strlen(p1) + 1);
				//		strcpy(slabel[nfiles][islabel - 1].lbltext, p1);
				//	}
				//}
				continue;
			}
			if (strstr(buf, TXTNAME)) {
				// move Name value
				p1 = strstr(buf, TXTNAME);
				p1 = p1 + (int) strlen(TXTNAME);
				p1++;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				stextfield[nfiles][indx].name = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(stextfield[nfiles][indx].name, p1);
				continue;
			}
			if (strstr(buf, TXTFRMT)) {
				// move formatter value
				p1 = strstr(buf, TXTFRMT);
				p = p1 + (int) strlen(TXTFRMT);
				p1 = strstr(p, TXTCONVERTER);
				if (p1) {
					p1 = p1 + (int) strlen(TXTCONVERTER);
					p = p1;
					while (*p != 0 && *p != '(') p++;
					*p = 0;
				}
				else {
					p1 = strstr(p, TXTNUMERIC);
					if (p1) {
						p = p1;
						while (*p != 0 && *p != '(') p++;
						*p = 0;
					}
					else {
						p1 = strstr(p, TXTDATE);
						if (p1) {
							p = p1;
							while (*p != 0 && *p != '(') p++;
							*p = 0;
						}
					}
				}
				if (p1) {
					stextfield[nfiles][indx].formatter = (char *) calloc(1, (int) strlen(p1) + 1);
					strcpy(stextfield[nfiles][indx].formatter, p1);
				}
				else
					stextfield[nfiles][indx].formatter = 0;
				continue;
			}
		}
		ftxtfunc = 0;
	}
	if ((frbutton == 0) && strstr(buf, CRBUTTON)) {
		frbutton = 1;
		Processed = 1;
		getName(xname, CRBUTTON);
		if (strlen(xname) > 0) {
			indx = irbutton[nfiles];
			rbutton[nfiles][indx].rbutno = getRbutton(xname);
			irbutton[nfiles]++;
			rbutton[nfiles][indx].rbut = (char*)calloc(1, (int)strlen(xname) + 1);
			strcpy(rbutton[nfiles][indx].rbut, xname);
		}
		else return ret;
		while (1) {
			ret = mygetline(CENDINIT2);
			if (ret != EOF) { 
				Processed = 1; 
				break; 
			}
			if (strstr(buf, CENDINIT) && !strstr(buf, CBEGIN)) {
				Processed = 1;
				break;
			}
			Processed = 1;
			if (strstr(buf, RBUTBOUND)) {
				// bounds
				boundVals(&rbutton[nfiles][indx].rbutBound, TXTBOUND);
				continue;
			}
			if (strstr(buf, RBUTENABLED)) {
				// rbutton enabled
				p1 = strstr(buf, RBUTENABLED) + (int) strlen(RBUTENABLED);
				if (strncasecmp(p1, "false", 5) == 0)
					rbutton[nfiles][indx].rbutEnabled = false;
				else
					rbutton[nfiles][indx].rbutEnabled = true;
				continue;
			}
			if (strstr(buf, RBUTDISABLE)) {
				// rbutton enabled
				p1 = strstr(buf, RBUTDISABLE) + (int) strlen(RBUTDISABLE);
				if (strncasecmp(p1, "false", 5) == 0)
					rbutton[nfiles][indx].disable = false;
				else
					rbutton[nfiles][indx].disable = true;
				continue;
			}
			if (strstr(buf, RBUTTAB)) {
				// rbutton tab Order
				p1 = strstr(buf, RBUTTAB) + (int) strlen(RBUTTAB);
				p1++;
				p = p1;
				while (*p != 0 && *p != ')') p++;
				*p = 0;
				rbutton[nfiles][indx].rbutTab = atoi(p1);
				continue;
			}
			if (strstr(buf, RBUTTXT)) {
				// rbutton text
				p1 = strstr(buf, RBUTTXT) + (int) strlen(RBUTTXT);
				p1++;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				rbutton[nfiles][indx].rbutText = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(rbutton[nfiles][indx].rbutText, p1);
				continue;
			}
			if (strstr(buf, RBUTSVAL)) {
				// rbutton text
				p1 = strstr(buf, RBUTSVAL) + (int) strlen(RBUTSVAL);
				p1++;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				rbutton[nfiles][indx].rbutVal = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(rbutton[nfiles][indx].rbutVal, p1);
				continue;
			}
		}
		frbutton = 0;
	}
	if ((fbutton == 0) && strstr(buf, CGETBUTTON)) {
		fbutton = 1;
		Processed = 1;
		indx = ibutton[nfiles];
		getName(xname, CGETBUTTON);
		if (strlen(xname) > 0) {
			button[nfiles][indx].butNo = getButton(xname);
			button[nfiles][indx].but = (char*)calloc(1, (int)strlen(xname) + 1);
			strcpy(button[nfiles][indx].but, xname);
			ibutton[nfiles]++;
		}
		else return ret;
		while (1) {
			ret = mygetline(CENDINIT2);
			if (ret != EOF) { 
				Processed = 1; 
				break;
			}
			if (strstr(buf, CENDINIT) && !strstr(buf, CBEGIN)) {
				Processed = 1;
				break;
			}
			Processed = 1;
			if (strstr(buf, BUTBOUND)) {
				// bounds
				boundVals(&button[nfiles][indx].butBound, TXTBOUND);
				continue;
			}
			if (strstr(buf, BUTTXT)) {
				// button text
				p1 = strstr(buf, BUTTXT) + (int) strlen(BUTTXT);
				p1++;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				button[nfiles][indx].butText = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(button[nfiles][indx].butText, p1);
				continue;
			}
			if (strstr(buf, BUTNAME)) {
				// button text
				p1 = strstr(buf, BUTNAME) + (int) strlen(BUTNAME);
				p1++;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				button[nfiles][indx].butName = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(button[nfiles][indx].butName, p1);
				continue;
			}
			if (strstr(buf, BUTLOCATE)) {
				// button locater
				p1 = strstr(buf, BUTLOCATE) + (int) strlen(BUTLOCATE);
				if (strncasecmp(p1, "false", 5) == 0)
					button[nfiles][indx].butLocate = false;
				else
					button[nfiles][indx].butLocate = true;
				continue;
			}
			if (strstr(buf, BUTTAB)) {
				// button tab order
				p1 = strstr(buf, BUTTAB) + (int) strlen(BUTTAB);
				p = p1;
				while (*p != 0 && *p != ')') p++;
				*p = 0;
				button[nfiles][indx].butTabOrder = atoi(p1);
				continue;
			}
			if (strstr(buf, BUTTXTTYPE)) {
				p1 = strstr(buf, BUTTXTTYPE) + (int) strlen(BUTTXTTYPE);
				p1++;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				button[nfiles][indx].butTxttype = atoi(p1);
			}
		}
		fbutton = 0;
	}
	if ((fcombo == 0) && strstr(buf, CCOMBOBOX)) {
		fcombo = 1;
		Processed = 1;
		getName(xname, CCOMBOBOX);
		if (strlen(xname) > 0) {
			indx = icombox[nfiles];
			combox[nfiles][indx].comboNo = getCombo(xname);
			combox[nfiles][indx].comboxName = (char*)calloc(1, (int)strlen(xname) + 1);
			strcpy(combox[nfiles][indx].comboxName, xname);
			icombox[nfiles]++;
		}
		else return ret;

		while (1) {
			ret = mygetline(CENDINIT2);
			if (ret != EOF) { 
				Processed = 1; 
				break;
			}
			if (strstr(buf, CENDINIT) && !strstr(buf, CBEGIN)) {
				Processed = 1;
				break;
			}
			Processed = 1;
			if (strstr(buf, BUTBOUND)) {
				boundVals(&combox[nfiles][indx].comboBounds, TXTBOUND);
				continue;
			}
			if (strstr(buf, BUTTAB)) {
				// button tab order
				p1 = strstr(buf, BUTTAB) + (int) strlen(BUTTAB);
				p = p1;
				while (*p != 0 && *p != ')') p++;
				*p = 0;
				combox[nfiles][indx].comboTabOrder = atoi(p1);
				continue;
			}
			if (strstr(buf, BUTNAME)) {
				// button text
				p1 = strstr(buf, BUTNAME) + (int) strlen(BUTNAME);
				p1++;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				combox[nfiles][indx].comboxName = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(combox[nfiles][indx].comboxName, p1);
				continue;
			}
			if (strstr(buf, TXTDNAME)) {
				p1 = strstr(buf, TXTDNAME);
				p1 = p1 + (int) strlen(TXTDNAME);
				p1++;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				combox[nfiles][indx].dataName = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(combox[nfiles][indx].dataName, p1);
				continue;
			}
			if (strstr(buf, SETVALFNAME)) {
				p1 = strstr(buf, SETVALFNAME);
				p1 = p1 + (int) strlen(SETVALFNAME) + 1;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				combox[nfiles][indx].setvalfname = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(combox[nfiles][indx].setvalfname, p1);
				continue;
			}
			if (strstr(buf, SETVALIN)) {
				p1 = strstr(buf, SETVALIN);
				p1 = p1 + (int) strlen(SETVALIN) + 1;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				combox[nfiles][indx].setvalin = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(combox[nfiles][indx].setvalin, p1);
				continue;
			}
			if (strstr(buf, SETFNAME)) {
				p1 = strstr(buf, SETFNAME);
				p1 = p1 + (int) strlen(SETFNAME) + 1;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				combox[nfiles][indx].setfname = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(combox[nfiles][indx].setfname, p1);
				continue;
			}
			if (strstr(buf, SETDNAMELST)) {
				p1 = strstr(buf, SETDNAMELST);
				p1 = p1 + (int) strlen(SETDNAMELST) + 1;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				combox[nfiles][indx].setdnamelst = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(combox[nfiles][indx].setdnamelst, p1);
				continue;
			}
			if (strstr(buf, SETKEYVAL)) {
				p1 = strstr(buf, SETKEYVAL);
				p1 = p1 + (int) strlen(SETKEYVAL);
				if (strncasecmp(p1, "false", 5) == 0)
					combox[nfiles][indx].setkeyvals = 0;
				else
					combox[nfiles][indx].setkeyvals = 1;
				continue;
			}
			if (strstr(buf, SETREQ)) {
				p1 = strstr(buf, SETREQ);
				p1 = p1 + (int)strlen(SETREQ);
				if (strncasecmp(p1, "false", 5) == 0)
					combox[nfiles][indx].setreq = 0;
				else
					combox[nfiles][indx].setreq = 1;
				continue;
			}
		}
		fcombo = 0;
	}
	if ((fchkbox == 0) && strstr(buf, CCHECKBOX)) {
		fchkbox = 1;
		Processed = 1;
		getName(xname, CCHECKBOX);
		if (strlen(xname) > 0) {
			indx = ichkno[nfiles];
			checkBox[nfiles][indx].checkNo = getCheck(xname);
			checkBox[nfiles][indx].setName = (char*)calloc(1, (int)strlen(xname) + 1);
			strcpy(checkBox[nfiles][indx].setName, xname);
			ichkno[nfiles]++;
		}
		else return ret;

		while (1) {
			ret = mygetline(CENDINIT2);
			if (ret != EOF) { 
				Processed = 1; 
				break;
			}
			if (strstr(buf, CENDINIT) && !strstr(buf, CBEGIN)) {
				Processed = 1;
				break;
			}
			Processed = 1;
			if (strstr(buf, CHKBOUND)) {
				boundVals(&checkBox[nfiles][indx].checkBounds, CHKBOUND);
				continue;
			}
			if (strstr(buf, CHKSTAB)) {
				// check tab order
				p1 = strstr(buf, CHKSTAB) + (int) strlen(CHKSTAB);
				p = p1;
				while (*p != 0 && *p != ')') p++;
				*p = 0;
				checkBox[nfiles][indx].checkTabOrder = atoi(p1);
				continue;
			}
			if (strstr(buf, CHKNAME)) {
				// check text
				p1 = strstr(buf, CHKNAME) + (int) strlen(CHKNAME);
				p1++;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				checkBox[nfiles][indx].setName = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(checkBox[nfiles][indx].setName, p1);
				if (slabel[nfiles][islabel[nfiles] - 1].lbltext == 0) {
					slabel[nfiles][islabel[nfiles] - 1].lbltext = (char *) calloc(1, (int) strlen(p1) + 1);
					strcpy(slabel[nfiles][islabel[nfiles] - 1].lbltext, p1);
				}
				continue;
			}
			if (strstr(buf, CHKDNAME)) {
				p1 = strstr(buf, CHKDNAME);
				p1 = p1 + (int) strlen(CHKDNAME);
				p1++;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				checkBox[nfiles][indx].dataName = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(checkBox[nfiles][indx].dataName, p1);
				continue;
			}
			if (strstr(buf, CHKSVAL)) {
				p1 = strstr(buf, CHKSVAL);
				p1 = p1 + (int) strlen(CHKSVAL) + 1;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				checkBox[nfiles][indx].setval = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(checkBox[nfiles][indx].setval, p1);
				continue;
			}
			if (strstr(buf, CHKUVAL)) {
				p1 = strstr(buf, CHKUVAL);
				p1 = p1 + (int) strlen(CHKUVAL) + 1;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				checkBox[nfiles][indx].setuval = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(checkBox[nfiles][indx].setuval, p1);
				continue;
			}
			if (strstr(buf, CHKFONT)) {
				p1 = strstr(buf, CHKFONT);
				p1 = p1 + (int) strlen(CHKFONT) + 1;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				checkBox[nfiles][indx].font = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(checkBox[nfiles][indx].font, p1);
				continue;
			}
			if (strstr(buf, CHKTXT)) {
				p1 = strstr(buf, CHKTXT);
				p1 = p1 + (int) strlen(CHKTXT);
				if (strncasecmp(p1, "E", 1) == 0)
					checkBox[nfiles][indx].text = "E";
				else
					checkBox[nfiles][indx].text = "H";
				continue;
			}
		}
		fchkbox = 0;
	}
	if ((fbuttongrps == 0) && strstr(buf, CBUTTONGROUP)) {
		fbuttongrps = 1;
		Processed = 1;
		getName(xname, CBUTTONGROUP);
		if (strlen(xname) > 0) {
			indx = isgroup[nfiles];
			sgroup[nfiles][indx].dataName = (char*)calloc(1, (int)strlen(xname) + 1);
			strcpy(sgroup[nfiles][indx].dataName, xname);
			sgroup[nfiles][indx].txtno = 0;
			sgroup[nfiles][indx].txtlblno = 0;
			sgroup[nfiles][indx].text = 0;
			isgroup[nfiles]++;
		}
		else return ret;
		while (1) {
			ret = mygetline(CENDINIT2);
			if (ret != EOF) {
				Processed = 1;
				break;
			}
			if (strstr(buf, CENDINIT) && !strstr(buf, CBEGIN)) {
				Processed = 1;
				break;
			}
			Processed = 1;
			if (strstr(buf, CHKDNAME)) {
				p1 = strstr(buf, CHKDNAME);
				p1 = p1 + (int)strlen(CHKDNAME);
				p1++;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				sgroup[nfiles][indx].dataName = (char *)calloc(1, (int)strlen(p1) + 1);
				strcpy(sgroup[nfiles][indx].dataName, p1);
				continue;
			}
		}
		fbuttongrps = 0;
	}
	if ((fscroll == 0) && strstr(buf, CSCROLL)) {
		fscroll = 1;
		Processed = 1;
		getName(xname, CSCROLL);
		if (strlen(xname) > 0) {
			indx = iscroll[nfiles];
			sscrollfield[nfiles][indx].scrollno = getScroll(xname);
			sscrollfield[nfiles][indx].name = (char*)calloc(1, (int)strlen(xname) + 1);
			strcpy(sscrollfield[nfiles][indx].name, xname);
			iscroll[nfiles]++;
		}
		else return ret;

		while (1) {
			ret = mygetline(CENDINIT2);
			if (ret != EOF) { 
				Processed = 1; 
				break;
			}
			if (strstr(buf, CENDINIT) && !strstr(buf, CBEGIN)) {
				Processed = 1;
				break;
			}
			Processed = 1;
			if (strstr(buf, CHKBOUND)) {
				boundVals(&sscrollfield[nfiles][indx].scrollBounds, CHKBOUND);
				continue;
			}
			if (strstr(buf, TSCROLL)) {
				p1 = strstr(buf, TSCROLL);
				p1 = p1 + (int) strlen(TSCROLL) + 1;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				sscrollfield[nfiles][indx].tablename = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(sscrollfield[nfiles][indx].tablename, p1);
				continue;
			}
		}
		fscroll = 0;
	}
	if ((ftable == 0) && strstr(buf, CSTABLE)) {
		int j;
		ftable = 1;
		Processed = 1;
		getName(xname, CSTABLE);
		if (strlen(xname) > 0) {
			indx = istable[nfiles];
			stable[nfiles][indx].tableno = getTable(xname);
			stable[nfiles][indx].name = (char*)calloc(1, (int)strlen(xname) + 1);
			strcpy(stable[nfiles][indx].name, xname);
			istable[nfiles]++;
		}
		else return ret;

		while (1) {
			ret = mygetline(CENDINIT2);
			if (ret != EOF) { 
				Processed = 1; 
				break;
			}
			if (strstr(buf, CENDINIT) && !strstr(buf, CBEGIN)) {
				Processed = 1;
				break;
			}
			Processed = 1;
			if (strstr(buf, CHKBOUND)) {
				boundVals(&stable[nfiles][indx].tableBounds, CHKBOUND);
				continue;
			}
			if (strstr(buf, MCLICK)) {
				p1 = strstr(buf, MCLICK);
				p1 = p1 + (int) strlen(MCLICK) + 1;
				p = p1;
				while (*p != 0 && *p != ')') p++;
				*p = 0;
				stable[nfiles][indx].mclick = 0;
				if (strcmp(p1, "false") == 0)
					stable[nfiles][indx].mclick = 0;
				else
					stable[nfiles][indx].mclick = 1;
				continue;
			}
			if (strstr(buf, ADDCOLUMN)) {
				j = stable[nfiles][indx].icols;
				if (ColumnVals(&stable[nfiles][indx].cols[j], ADDCOLUMN, 0) != EOF)
					stable[nfiles][indx].icols++;
				continue;
			}
		}
		ftable = 0;
	}
	if ((ftable == 0) && strstr(buf, CSTABLES)) {
		int j;
		ftable = 1;
		Processed = 1;
		getName(xname, CSTABLES);
		if (strlen(xname) > 0) {
			indx = istable[nfiles];
			stable[nfiles][indx].tableno = getTable(xname);
			stable[nfiles][indx].name = (char*)calloc(1, (int)strlen(xname) + 1);
			strcpy(stable[nfiles][indx].name, xname);
			istable[nfiles]++;
		}
		else return ret;

		while (1) {
			ret = mygetline(CENDINIT2);
			if (ret != EOF) { 
				Processed = 1;
				break;
			}
			if (strstr(buf, CENDINIT) && !strstr(buf, CBEGIN)) {
				Processed = 1;
				break;
			}
			Processed = 1;
			if (strstr(buf, CHKBOUND)) {
				boundVals(&stable[nfiles][indx].tableBounds, CHKBOUND);
				continue;
			}
			if (strstr(buf, MCLICK)) {
				p1 = strstr(buf, MCLICK);
				p1 = p1 + (int) strlen(MCLICK) + 1;
				p = p1;
				while (*p != 0 && *p != ')') p++;
				*p = 0;
				stable[nfiles][indx].mclick = 0;
				if (strcmp(p1, "false") == 0)
					stable[nfiles][indx].mclick = 0;
				else
					stable[nfiles][indx].mclick = 1;
				continue;
			}
			if (strstr(buf, "setKeyDataName(")) {
				j = stable[nfiles][indx].icols;
				ColkDataName(&stable[nfiles][indx].cols[j].kdataname, "setKeyDataName(");
				continue;
			}
			if (strstr(buf, "setColumnWidth(")) {
				j = stable[nfiles][indx].icols;
				ColWidth(&stable[nfiles][indx].cols[j].colwidth, "setColumnWidth(");
				continue;
			}
			if (strstr(buf, "setTitle(")) {
				j = stable[nfiles][indx].icols;
				ColTitle(&stable[nfiles][indx].cols[j].title, "setTitle(");
				continue;
			}
			if (strstr(buf, "setEditable(")) {
				j = stable[nfiles][indx].icols;
				ColEditVal(&stable[nfiles][indx].cols[j].editval, "setEditable(");
				continue;
			}
			if (strstr(buf, ADDCOLUMN)) {
				j = stable[nfiles][indx].icols;
				if (ColumnVals(&stable[nfiles][indx].cols[j], ADDCOLUMN, 1) != EOF)
					stable[nfiles][indx].icols++;
				continue;
			}
		}
		ftable = 0;
	}
	if ((floader == 0) && strstr(buf, CLOADER)) {
		floader = 1;
		getName(xname, CLOADER);
		if (strlen(xname) > 0) {
			strcpy(loads[panelno][loadno], xname);
			loadno++;
			loads[panelno][loadno][0] = 0;
			indx = iloader[nfiles];
			loader[nfiles][indx].loadNo = loadno - 1;
			loader[nfiles][indx].name = (char*)calloc(1, (int)strlen(xname) + 1);
			strcpy(loader[nfiles][indx].name, xname);
			iloader[nfiles]++;
		}
		else return ret;
		while (1) {
			ret = mygetline(CENDINIT2);
			if (ret != EOF) { 
				Processed = 1; 
				break;
			}
			if (strstr(buf, CENDINIT) && !strstr(buf, CBEGIN)) {
				Processed = 1;
				break;
			}
			Processed = 1;
			if (strstr(buf, LOADSTR)) {
				// button tab order
				p1 = strstr(buf, LOADSTR) + (int) strlen(LOADSTR);
				p1++;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				loader[nfiles][indx].loadstr = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(loader[nfiles][indx].loadstr, p1);
			}
		}
		floader = 0;
	}

	//if (buf[0] == '}') {
	if (strstr(buf, "}")) {
		ret = EOF;
		return ret;
	}
	return ret;
}

int anyofThese()
{
	if (strstr(buf, cexit)) return true;
	if (strstr(buf, CEXIT)) return true;
	if (strstr(buf, CPANELDEC)) return true;
	if (strstr(buf, CLBLFUNC)) return true;
	if (strstr(buf, CTXTFUNC)) return true;
	if (strstr(buf, CRBUTTON)) return true;
	if (strstr(buf, CGETBUTTON)) return true;
	if (strstr(buf, CLOADER)) return true;
	return false;
}

int javaClass()
{
	/* public class className extends akbankPanel { inClass } */
	int ret = EOF;
	fclass = 0;
	Processed = 1;

	while ((ret = mygetline(CCLIENT)) > 0) {
		// if(anyofThese()) return EOF;
		if (fclass == 0) {
			ret = detected(CCLASS);
			if (ret != EOF) {
				char *pt = strstr(symbol, " ");
				if (pt) {
					*pt = 0;
					strcpy(program, symbol);
					fclass = 1;
					continue;
				}
			}
		}
		if (finit == 0 && fexit == 0) {
			ret = getsymbol(CWIDGETS);
			if (ret != EOF){
				if ((ret = detected(CPANEL)) != EOF) continue;
				if ((ret = detected(CLABEL)) != EOF) continue;
				if ((ret = detected(CTEXTFIELD)) != EOF) continue;
				if ((ret = detected(CBUTTON)) != EOF) continue;
				if ((ret = detected(CBUTTONGRP)) != EOF) continue;
				if ((ret = detected(CCOMBOBOX)) != EOF) continue;
				if ((ret = detected(CQUERYLSTFUNC)) != EOF) continue;
				if ((ret = detected(CTABLE)) != EOF) continue;
				if ((ret = detected(CTABLES)) != EOF) continue;
				Processed = 1;
			}
		}
	}
	return ret;
}

int hostvarmi(char *dname)
{
	int i, len;
	if (dname == NULL) return 0;
	len = (int) strlen(dname);
	for (i = 0; i<ihost; i++) {
		if (strncmp(hostvar[i], dname, len) == 0)
			return 1;
	}
	return 0;
}

int checkLabel(int nf, int lin, int col)
{
	int j, savei = -1;
	for (j = 0; j<islabel[nf]; j++) {
		if (slabel[nf][j].slblbound.x0 == lin && slabel[nf][j].slblbound.y0 < col)
			savei = j;
	}
	return savei;
}

int itext;
char *mytext[MAXTXT];
int onceki(char *s)
{
	int i;
	if (s == NULL) return 1;
	for (i = 0; i < itext; i++) {
		if (strcmp(mytext[i], s) == 0)
			return 1;
	}
	i = itext;
	itext++;
	mytext[i] = (char *)calloc(1, strlen(s) + 1);
	strcpy(mytext[i], s);
	return 0;
}

int rowcount = 0;

void tableVarmi(int nf, int i, char *ff, char *uniq)
{
	int  j, end = 0;
	char mylst[200];

	rowcount++;
	end = stable[nfiles][i].icols;
	sprintf(mylst, "%s%02d", ff, end);
	if (onceki(mylst) == 1) return;
	if (rowcount > 1)
		 fprintf(output, "        public string SelectedRow%d { get; set; }\n", rowcount);
	else fprintf(output, "        public string SelectedRow { get; set; }\n");
	fprintf(output, "        [ExcludeGenerateView]\n");

	for (j = 0; j< stable[nf][i].icols; j++) {
		if (j == 0) {
			fprintf(output, "        public List<%s%s> %s%sList { get; set; }\n",
				buyukHarf(ff), uniq, buyukHarf(ff), uniq);
			fprintf(output, "        public %s%s %s%sProp { get; set; }\n",
				buyukHarf(ff), uniq, buyukHarf(ff), uniq);
			fprintf(output, "        [Serializable]\n");
			fprintf(output, "        public sealed class %s%s\n", buyukHarf(ff), uniq);
			fprintf(output, "        {\n");
		}
		if (hostvarmi(stable[nf][i].cols[j].dataname)) {
			fprintf(output, "            [ScriptIgnore]\n");
		}
		if (stable[nf][i].cols[j].left == 0) {
			if (strstr(stable[nf][i].cols[j].dtype, "NUMERIC"))
				fprintf(output, "            [Numeric]\n");
		}
		//if ((int) strlen(stable[i].cols[j].dataname) > 0)
		//	fprintf(output, "            public string %s { get; set; }\n",
		//		stable[i].cols[j].dataname);
		//else
		//	fprintf(output, "            public string column%d { get; set; }\n", j);

		if (stable[nf][i].cols[j].title && (int)strlen(stable[nf][i].cols[j].title) > 0) {
			fprintf(output, "            [Display(Name=\"%s\")]\n", stable[nf][i].cols[j].title);
		}
		if ((int)strlen(stable[nf][i].cols[j].dataname) > 0) {
			if (stable[nf][i].cols[j].kdataname && strlen(stable[nf][i].cols[j].kdataname) > 0)
				fprintf(output, "            public string %s { get; set; }\n", buyukHarf(stable[nf][i].cols[j].kdataname));
			else
				if(strstr(stable[nf][i].cols[j].dataname, ","))
					fprintf(output, "            public string %s { get; set; }\n", buyukHarf(skipsome(stable[nf][i].cols[j].text)));
				else fprintf(output, "            public string %s { get; set; }\n", buyukHarf(stable[nf][i].cols[j].dataname));
		}
		else
			fprintf(output, "            public string Column%d { get; set; }\n", j);
	}
	if (end > 0) fprintf(output, "        }\n");
}

void GlobalEkle(char *p, char *ek)
{
	int  i;
	i = iglobalid;
	globalid[i] = (char *)calloc(1, strlen(p) + 3);
	if (ek[0]) {
		strcpy(globalid[i], ek);
		strcat(globalid[i], p);
	}
	else strcpy(globalid[i], p);
	iglobalid++;
}

int isorted[NFILES] = { 0 };
struct SORTED {
	int  sj;
	int  sline;
	char *stype;
	char *sf;
	char *stxt;
} sorted[NFILES][200];

void insertline(int nf, int j, int line, char *sfname, char *typ, char *txt)
{
	int  i, ii;
	for (i = 0; i < isorted[nf]; i++) {
		if (sorted[nf][i].sline > line) {
			for (ii = isorted[nf]; ii > i; ii--) {
				sorted[nf][ii].sj = sorted[nf][ii - 1].sj;
				sorted[nf][ii].sline = sorted[nf][ii - 1].sline;
				sorted[nf][ii].sf = sorted[nf][ii - 1].sf;
				sorted[nf][ii].stxt = sorted[nf][ii - 1].stxt;
				sorted[nf][ii].stype = sorted[nf][ii - 1].stype;
			}
			sorted[nf][i].sj = j;
			sorted[nf][i].sline = line;
			sorted[nf][i].sf = sfname;
			sorted[nf][i].stxt = txt;
			sorted[nf][ii].stype = typ;
			isorted[nf]++;
			return;
		}
	}
	i = isorted[nf];
	sorted[nf][i].sj = j;
	sorted[nf][i].sline = line;
	sorted[nf][i].sf = sfname;
	sorted[nf][i].stxt = txt;
	sorted[nf][i].stype = typ;
	isorted[nf]++;
}

int checklbl(int nf, char *s)
{
	int  i;
	for (i = 0; i < isorted[nf]; i++) {
		if (sorted[nf][i].stxt && strcmp(sorted[nf][i].stxt, s) == 0 && strcmp(sorted[nf][i].stype, "L") == 0)
			return sorted[nf][i].sj;
	}
	return -1;
}

void asciTasi(char *t, char *s)
{
	int i, len, k;
	len = (int)strlen(s);
	k = 0;
	for (i = 0; i < len; i++)
	{
		if ((s[i] >= 'a' && s[i] <= 'z') ||
			(s[i] >= 'A' && s[i] <= 'Z') ||
			(s[i] >= '0' && s[i] <= '9')) {
			if (s[i] >= 'a' && s[i] <= 'z') {
				t[k] = s[i] - 'a' + 'A';
			}
			else {
				t[k] = s[i];
			}
			k++;
			t[k] = 0;
		}
		else {
			if (s[i] == -36) { t[k] = 'U'; k++; }
			if (s[i] == -48) { t[k] = 'G'; k++; }
			if (s[i] == -35) { t[k] = 'I'; k++; }
			if (s[i] == -34) { t[k] = 'S'; k++; }
			if (s[i] == -57) { t[k] = 'C'; k++; }
			if (s[i] == -42) { t[k] = 'O'; k++; }
			if (s[i] == -4) { t[k] = 'U'; k++; }
			if (s[i] == -16) { t[k] = 'G'; k++; }
			if (s[i] == -3) { t[k] = 'I'; k++; }
			if (s[i] == -2) { t[k] = 'S'; k++; }
			if (s[i] == -25) { t[k] = 'C'; k++; }
			if (s[i] == -10) { t[k] = 'O'; k++; }
		}
	}
}

int v[100][50];

char letters(char s)
{
	if (s == 'B' || s == 'F' || s == 'P' || s == 'V')
		return '1';
	if (s == 'C' || s == 'G' || s == 'J' || s == 'K' ||
		s == 'Q' || s == 'S' || s == 'X' || s == 'Z')
		return '2';
	if (s == 'D' || s == 'T')
		return '3';
	if (s == 'L')
			return '4';
	if (s == 'M' || s == 'N')
		return '5';
	if (s == 'R')
		return '6';
	return '0';
}
char *soundex(char *p)
{
	char s[200];
	int i = 0;
	char letter;
	char *pps;

	s[0] = 0;
	while (*p && i < 4) {
		if (*p >= 'A' && *p <= 'Z') {
			if (*p == 'A' || *p == 'E' || *p == 'U' ||
				*p == 'O' || *p == 'I' || *p == 'W' || *p == 'H' || *p == 'Y') {
				p++;
				continue;
			}
			letter = letters(*p);
			if (i >= 1 && s[i - 1] == letter) {
				p++;
				continue;
			}
			s[i] = letter;
			s[i + 1] = 0;
			i++;
		}
		p++;
	}
	if (i <= 3) {
		while (i <= 3) {
			s[i] = '0';
			s[i + 1] = 0;
			i++;
		}
	}
	pps = (char *)calloc(1, strlen(s) + 1);
	strcpy(pps, s);
	return pps;
}

int matches(char *s, char *t)
{
	int  iss = 0;
	int  erc;
	int  i = 0, j = 0;
	char ps[200], pt[200];
	char *p1, *p2;

	if (t == 0) t = "null";
	if (s == 0) s = "null";
	asciTasi(pt, t);
	asciTasi(ps, s);


	p1 = soundex(pt);
	p2 = soundex(ps);
	for (i = 0; i < 4; i++) {
		if (p1[i] == p2[i]) iss++;
		else break;
	}
	// fprintf(output, "p1 %s p2 %s\n", p1, p2);
	erc = (strcmp(p1, p2) == 0 ? 1 : (iss >= 2 ? 1 : 0));
	return erc;
}

#define OZELX

void mytextWrite(int prm, int nf,  char *prog, char *area, char *uniq, char *nodisp, int son)
{
	int i, ilbl, j;
	int ii, ij, ik;
	int ji, jj, jk;
	int jjj, iii;
	char *str, *p, *p1;
	char saved[200];
	
	param = (prm == 5) ? 2 : prm;
	if (nf == 0) {
		p = strrchr(prog, '\\');
		if (p)
			 p++;
		else p = prog;
		p1 = strstr(p, ".java");
		if (p1) {
			*p1 = 0;
		}
		fprintf(output, "using System;\n");
		fprintf(output, "using System.Collections.Generic;\n");
		fprintf(output, "using System.ComponentModel.DataAnnotations;\n");
		fprintf(output, "using System.Linq;\n");
		fprintf(output, "using System.Text;\n");
		fprintf(output, "using System.Threading.Tasks;\n");
		fprintf(output, "using AkbankFace.Web.Common.Interfaces;\n");
		fprintf(output, "using AkbankFace.Web.Common;\n");
		//fprintf(output, "using System.Web.Mvc;\n");
		//fprintf(output, "using Newtonsoft.Json;\n");
		fprintf(output, "using AkbankFace.BranchBanking.Common;\n");
		fprintf(output, "namespace AkbankFace.Web.%s.Models\n", area);
		fprintf(output, "{\n");
		fprintf(output, "    [Serializable]\n");
		fprintf(output, "    public class %sViewModel : ModelBase\n", prog);
		fprintf(output, "    {\n");
	}


	for (i = 0; i < istext[nf]; i++) {
		char *sfname;
		int  line;
		sfname = stextfield[nf][i].dataName;
		if (stextfield[nf][i].txtline == 0) {
			// line = i * 100000000 + slabel[nfiles][i].slblbound.x1 * 1000000 + stextfield[nfiles][i].stxtbound.y1 * 1000 + stextfield[nfiles][i].stxtbound.x0;
			line = stextfield[nf][i].stxtbound.x0 * 1000000 + stextfield[nf][i].stxtbound.y0 * 1000 + stextfield[nf][i].stxtbound.y1;
			stextfield[nf][i].txtline = line;
		}
		if(stextfield[nfiles][i].dataName)
			insertline(nf, i, stextfield[nf][i].txtline, stextfield[nf][i].dataName, "T", 0);
		else insertline(nf, i, stextfield[nf][i].txtline, stextfield[nf][i].text, "T", 0);
	}

	for (i = 0; i < isgroup[nf]; i++) {
		char *sfname;
		int  line;
		sfname = sgroup[nf][i].dataName;
		if (sgroup[nf][i].txtline == 0) {
			line = i * 100000000;
			sgroup[nf][i].txtline = line;
		}
		insertline(nf, i, sgroup[nf][i].txtline, sgroup[nf][i].dataName, "T", 0);
	}

	for (i = 0; i < islabel[nf]; i++) {
		char *sfname;
		int  line;
		sfname = slabel[nf][i].name;
		if (slabel[nf][i].lblline == 0) {
			// line = i * 100000000 + slabel[nf][i].slblbound.x1 * 1000000 + slabel[nf][i].slblbound.y1 * 1000 + slabel[nf][i].slblbound.x0;
			if(slabel[nf][i].text)
				line = slabel[nf][i].slblbound.x0 * 1000000 + (slabel[nf][i].slblbound.y0 + strlen(slabel[nf][i].text)) * 1000 + slabel[nf][i].slblbound.y1;
			else 
				if (slabel[nf][i].dname)
					line = slabel[nf][i].slblbound.x0 * 1000000 + (slabel[nf][i].slblbound.y0 + strlen(slabel[nf][i].dname)) * 1000 + slabel[nf][i].slblbound.y1;
				else line = slabel[nf][i].slblbound.x0 * 1000000 + (slabel[nf][i].slblbound.y0 + strlen(slabel[nf][i].name)) * 1000 + slabel[nf][i].slblbound.y1;
			slabel[nf][i].lblline = line;
		}
		if(slabel[nf][i].text)
			insertline(nf, i, slabel[nf][i].lblline, slabel[nf][i].text, "L", 0);
		else
			if(slabel[nf][i].dname)
				insertline(nf, i, slabel[nf][i].lblline, slabel[nf][i].dname, "L", 0);
	}
	for (i = 0; i < isorted[nf]; i++) {
		ii = sorted[nf][i].sline / 1000000;
		ij = (sorted[nf][i].sline - ii * 1000000) / 1000;
		ik = sorted[nf][i].sline % 1000;
		for (j = i + 1; j < isorted[nf]; j++) {
			ji = sorted[nf][j].sline / 1000000;
			jj = (sorted[nf][j].sline - ii * 1000000) / 1000;
			jk = sorted[nf][j].sline % 1000;
			if (ii == ji && ij == jj) {
				jjj = sorted[nf][i].sj;
				iii = sorted[nf][j].sj;
				if ((strcmp(sorted[nf][i].stype, "T") == 0) &&
					(strcmp(sorted[nf][j].stype, "L") == 0)) {
					slabel[nf][iii].lbltext = sorted[nf][i].sf;
					sorted[nf][j].stxt = sorted[nf][i].sf;
					sorted[nf][i].stxt = sorted[nf][j].sf;
					break;
				}
				if ((strcmp(sorted[nf][j].stype, "T") == 0) &&
					(strcmp(sorted[nf][i].stype, "L") == 0)) {
					slabel[nf][jjj].lbltext = sorted[nf][j].sf;
					sorted[nf][j].stxt = sorted[nf][i].sf;
					sorted[nf][i].stxt = sorted[nf][j].sf;
					break;
				}
			}
		}
	}
	for (i = 0; i < isorted[nf]; i++) {
		int jj, jkal = 0;
		if (strcmp(sorted[nf][i].stype, "L") == 0 && sorted[nf][i].stxt == 0) {
			for (j = jkal; j < isorted[nf]; j++) {
 				if (strcmp(sorted[nf][j].stype, "T") == 0 && sorted[nf][j].stxt == 0) {
					if (matches(sorted[nf][i].sf, stextfield[nf][sorted[nf][j].sj].dataName)) {
						sorted[nf][i].stxt = sorted[nf][j].sf;
						jj = sorted[nf][i].sj;
						slabel[nf][jj].lbltext = sorted[nf][j].sf;
						sorted[nf][j].stxt = sorted[nf][i].sf;
						jkal = j;
						break;
					}
				}
			}
		}
	}

	for (i = 0; i < istext[nf]; i++) {
		if (stextfield[nf][i].dataName) {
			ilbl = checklbl(nf, stextfield[nf][i].dataName);
			if (ilbl >= 0) {
				if (strcmp(nodisp, "yes") == 0 && slabel[nf][ilbl].lbltext)
					if (slabel[nf][ilbl].text) {
						fprintf(output, "        [Display(Name=\"%s\")]\n", slabel[nf][ilbl].text);
						strcpy(saved, slabel[nf][ilbl].text);
					}
					else {
						fprintf(output, "        [Display(Name=\"%s\")]\n", slabel[nf][ilbl].lbl);
						strcpy(saved, slabel[nf][ilbl].lbl);
					}
			}
		}
		else
		if (stextfield[nf][i].text) {
			ilbl = checklbl(nf, stextfield[nf][i].text);
			if (ilbl >= 0) {
				if (strcmp(nodisp, "yes") == 0 && slabel[nf][ilbl].lbltext)
					if (slabel[nf][ilbl].text) {
						fprintf(output, "        [Display(Name=\"%s\")]\n", slabel[nf][ilbl].text);
						strcpy(saved, slabel[nf][ilbl].text);
					}
					else {
						fprintf(output, "        [Display(Name=\"%s\")]\n", slabel[nf][ilbl].lbl);
						strcpy(saved, slabel[nf][ilbl].lbl);
					}
			}
		}
		if (stextfield[nf][i].enabled)
			fprintf(output, "        [Enabled]\n");
		if (stextfield[nf][i].required)
			fprintf(output, "        [Required]\n");
		str = "string";
		if (stextfield[nf][i].formatter) {
			if (strstr(stextfield[nf][i].formatter, "Numeric")) {
				// fprintf(output,"    [Numeric]\n");
				str = "decimal";
			}
			//if (strstr(stextfield[nf][i].formatter, "Date"))
			//	str = "DateTime?";
			if (strstr(stextfield[nf][i].formatter, "Date"))
				str = "Date";
		}
		else {
			if (stextfield[nf][i].dataName && strstr(stextfield[nf][i].dataName, "Tarih")) {
				str = "Date";
			}
		}

		if (stextfield[nf][i].dataName) {
			if (strcmp(str, "Date") == 0) {
				fprintf(output, "        public string %s { get; set; }\n",
					buyukHarf(stextfield[nf][i].dataName));
				fprintf(output, "        public DateTime? %sDt { get; set; }\n",
					buyukHarf(stextfield[nf][i].dataName));
			}
			else
			if (strcmp(stextfield[nf][i].dataName, "paraBirimiAlfa") == 0)
				fprintf(output, "        public %s %s%d { get; set; }\n",
				str,
				buyukHarf(stextfield[nf][i].dataName), i);
			else
				fprintf(output, "        public %s %s { get; set; }\n",
				str, buyukHarf(stextfield[nf][i].dataName));
		}
	}
	for (i = 0; i < isgroup[nf]; i++) {
		if (onceki(sgroup[nf][i].dataName) == 1) continue;
		ilbl = checklbl(nf, sgroup[nf][i].dataName);
		if (ilbl >= 0) {
			if (strcmp(nodisp, "yes") == 0 && slabel[nf][ilbl].lbltext)
				fprintf(output, "        [Display(Name=\"%s\")]\n", slabel[nf][ilbl].text);
			strcpy(saved, slabel[nf][ilbl].text);
		}
		fprintf(output, "        public string %s { get; set; }\n", buyukHarf(sgroup[nf][i].dataName));
	}
	for (i = 0; i < ichkno[nf]; i++) {
		if (checkBox[nf][i].dataName) {
			if (onceki(checkBox[nf][i].dataName) == 1) continue;
			fprintf(output, "        public bool  %s { get; set; }\n",
				buyukHarf(checkBox[nf][i].dataName));
		} else {
			if (onceki(checkBox[nf][i].setName) == 1) continue;
			fprintf(output, "        public bool  %s { get; set; }\n",
				buyukHarf(checkBox[nf][i].setName));
		}
	}
	for (i = 0; i < icombox[nf]; i++) {
		if (onceki(combox[nf][i].setdnamelst) == 1) continue;
		// list type
		combox[nf][i].setdnamelst = myReplace(combox[nf][i].setdnamelst, ' ', '_');
		p = strstr(combox[nf][i].setdnamelst, ".");
		if (p) {
			p++;
			ilbl = checkLabel(nf, combox[nf][i].comboBounds.x0,
				combox[nf][i].comboBounds.y0);
			if (ilbl >= 0) {
				if (strcmp(nodisp, "yes") == 0)
					fprintf(output, "        [Display(Name=\"%s\")]\n", slabel[nf][ilbl].text);
			}
			//[ExcludeGenerateView]
			//public List<ListTypes> islemSubeList{ get; set; }
			if (combox[nf][i].dataName) {
				fprintf(output, "        public string %s { get; set; }\n", buyukHarf(combox[nf][i].dataName));
				if (combox[nf][i].setdnamelst) {
					p = strstr(combox[nf][i].setdnamelst, ".");
					if (p) {
						p1 = p + 1;
						/*GlobalEkle(p1, "*");*/
						if (strstr(p1, "List"))
							fprintf(output, "        public List<ListTypes> %s { get; set; }\n", buyukHarf(p1));
						else fprintf(output, "        public List<ListTypes> %sList { get; set; }\n", buyukHarf(p1));
					}
				}
				else {
					if (strstr(combox[nf][i].dataName, "List"))
						fprintf(output, "        public List<ListTypes> %s { get; set; }\n", buyukHarf(combox[nf][i].dataName));
					else fprintf(output, "        public List<ListTypes> %sList { get; set; }\n", buyukHarf(combox[nf][i].dataName));
				}
			}
			else {
					fprintf(output, "        public string %-10.10s { get; set; }\n", buyukHarf(p));
				fprintf(output, "        public List<ListTypes> %sList { get; set; }\n", buyukHarf(p));
				/*GlobalEkle(p, "*");*/
			}
		}
	}
	for (i = 0; i < irbutton[nf]; i++) {
		if (onceki(rbutton[nf][i].rbut) == 1) continue;
		// if(rbutton[i].rbutText)
		if (strcmp(nodisp, "yes") == 0) {
			fprintf(output, "        [Display(Name=\"%s\")]\n", rbutton[nf][i].rbutText);
		}
		// fprintf(output, "        [ExcludeGenerateView]\n");
		if (i == 0)
			fprintf(output, "        public string %s { get; set; }\n", buyukHarf(rbutton[nf][i].rbut));
		else fprintf(output, "        public bool %s { get; set; }\n", buyukHarf(rbutton[nf][i].rbut));
	}
	for (i = 0; i < ibutton[nf]; i++) {
		if (onceki(button[nf][i].but) == 1) continue;
		fprintf(output, "        [ExcludeGenerateView]\n");
		fprintf(output, "        public bool %s { get; set; }\n", buyukHarf(button[nf][i].but));
	}
	for (i = 0; i < istable[nf]; i++) {
		tableVarmi(nf, i, stable[nf][i].name, uniq);
	}
	//if (son) {
	//	fprintf(output, "        public string CommandTag { get; set; }\n");
	//	fprintf(output, "    }\n");
	//	fprintf(output, "}\n");
	//}
}


void getGlobals(int param, int nf, char* prog, char* area, char* uniq, char* nodisp, int son)
{
	int i, ilbl, j;
	int ii, ij, ik;
	int ji, jj, jk;
	int jjj, iii;
	char * p, * p1;

	for (i = 0; i < icombox[nf]; i++) {
		if (onceki(combox[nf][i].setdnamelst) == 1) continue;
		// list type
		combox[nf][i].setdnamelst = myReplace(combox[nf][i].setdnamelst, ' ', '_');
		p = strstr(combox[nf][i].setdnamelst, ".");
		if (p) {
			p++;
			if (combox[nf][i].dataName) {
				if (combox[nf][i].setdnamelst) {
					p = strstr(combox[nf][i].setdnamelst, ".");
					if (p) {
						p1 = p + 1;
						GlobalEkle(p1, "*");
					}
				}
			}
			else {
				GlobalEkle(p, "*");
			}
		}
	}
}

void mytableWrite(int nf, char *ff, char *odir, char *area, char *uniq)
{
	int i, j;
	char fname[300];

	for (i = 0; i < istable[nf]; i++) {
		sprintf(fname, "%s/%s%s.cs", odir, stable[nf][i].name, uniq);
		output = fopen(fname, "w");
		if (output) {
			fprintf(output, "using System;\n");
			fprintf(output, "using System.Collections.Generic;\n");
			fprintf(output, "using System.ComponentModel.DataAnnotations;\n");
			fprintf(output, "using System.Linq;\n");
			fprintf(output, "using System.Text;\n");
			fprintf(output, "using System.Threading.Tasks;\n");
			fprintf(output, "using AkbankFace.Web.Common.Interfaces;\n");
			fprintf(output, "using AkbankFace.Web.Common;\n");
			fprintf(output, "using System.Web.Mvc;\n");
			fprintf(output, "using NewtonSoft.Json;\n");
			fprintf(output, "using AkbankFace.BranchBanking.Common;\n");
			fprintf(output, "namespace AkbankFace.Web.%s.Models\n", area);
			fprintf(output, "{\n");
			fprintf(output, "    public class %s : ModelBase\n", buyukHarf(stable[nf][i].name));
			fprintf(output, "    {\n");

			for (j = 0; j< stable[nf][i].icols; j++) {
				//if (hostvarmi(stable[i].cols[j].dataname)) {
				//	fprintf(output, "        [ScriptIgnore]\n");
				//}
				if (stable[nf][i].cols[j].left == 0) {
					if (strstr(stable[nf][i].cols[j].dtype, "NUMERIC"))
						fprintf(output, "        [Numeric]\n");
				}
				if ((int) strlen(stable[nf][i].cols[j].dataname) > 0)
					fprintf(output, "        public string %s { get; set; }\n",
					buyukHarf(stable[nf][i].cols[j].dataname));
				else
					fprintf(output, "        public string Column%d { get; set; }\n", j);
			}
		}
		fprintf(output, "    }\n");
		fprintf(output, "}\n");
		fclose(output);
	}
}

void getHost(char *fname, char *trnid)
{
	FILE *fx;
	char fbuf[MAXCHAR + 1];
	char *p;
	fx = fopen(fname, "r");
	if (fx) {
		ihost = 0;
		while (fgets(fbuf, MAXCHAR, fx)) {
			p = strstr(fbuf, "=");
			if (p) {
				*p = 0;
				strcpy(hostvar[ihost], fbuf);
				ihost++;
			}
		}
		fclose(fx);
	}
}

#define RSON 3

#define PXCMANDA    11
#define PXSMANDA    22
#define PXSVALUE    33
#define PXSHOWMSG    44
#define PXINVISIBLE    55
#define PXDATASPLIT    66
#define PXDATAMERGE    77
#define PXQUERYLST    88



void tableVarsa(int nf, int i, char *ff, char *uniq)
{
	int j;

	for (j = 0; j< stable[nf][i].icols; j++) {
		if (j == 0 && stable[nf][i].mclick == 0) {
			fprintf(output, "3:C:%s%s\n", ff, uniq);
		}
		if (j == 0 && stable[nf][i].mclick == 1) {
			fprintf(output, "3:L:%s%s\n", ff, uniq);
		}
		if (hostvarmi(stable[nf][i].cols[j].dataname) == 0) {
			hostyok = 1;
		}
		if ((int)strlen(stable[nf][i].cols[j].dataname) > 0) {
			if (stable[nf][i].cols[j].kdataname && strlen(stable[nf][i].cols[j].kdataname) > 0)
				fprintf(output, "4:I:%s", stable[nf][i].cols[j].kdataname);
			else 
				if (strstr(stable[nf][i].cols[j].dataname, ","))
					fprintf(output, "4:I:%s", skipsome(stable[nf][i].cols[j].text));
				else fprintf(output, "4:I:%s", stable[nf][i].cols[j].dataname);
		}
		else {
			if (stable[nf][i].cols[j].kdataname && strlen(stable[nf][i].cols[j].kdataname) > 0)
				fprintf(output, "4:I:%s", stable[nf][i].cols[j].kdataname);
			else fprintf(output, "4:I:column%d", j);
		}
		if (stable[nf][i].cols[j].title && strlen(stable[nf][i].cols[j].title) > 0)
			fprintf(output, ":%s", stable[nf][i].cols[j].title);
		fprintf(output, "\n");
	}
}

void writeViews(int nf, char *fname, char *uniq)
{
	int i, ilbl, len;
	char *str, *p;
	int  hostyok = 0;
	char buffer[500], ffname[200];

	p = strrchr(fname, '\\');
	if (p) p++;
	else p = fname;
	strcpy(ffname, p + 4);
	fprintf(output, "1:H:");
	fprintf(output, "%s\n", ffname);
	for (i = 0; i < istext[nf]; i++) {
		// burada server xml de olanlar yazılır.
		if (hostvarmi(stextfield[nf][i].dataName) == 0) {
			hostyok = 1;
		}
		ilbl = checkLabel(nf, stextfield[nf][i].stxtbound.x0,
			stextfield[nf][i].stxtbound.y0);
		str = "S";
		len = stextfield[nf][i].stxtbound.y1 / 5;
		if (stextfield[nf][i].formatter) {
			if (strstr(stextfield[nf][i].formatter, "Numeric")) {
				// fprintf(output,"    [Numeric]\n");
				str = "N";
			}
			if (strstr(stextfield[nf][i].formatter, "Date"))
				str = "D";
		}
		if (stextfield[nf][i].dataName) {
			if (strstr(stextfield[nf][i].dataName, "Tarih"))
				str = "S";

			if (strcmp(stextfield[nf][i].dataName, "paraBirimiAlfa") == 0)
				sprintf(buffer, "%s%d", stextfield[nf][i].dataName, i);
			else
				sprintf(buffer, "%s", stextfield[nf][i].dataName);
			fprintf(output, "2:%s:%s:%d\n", str, buffer, len);
		}
		else str = "S";
	}
	for (i = 0; i < isgroup[nf]; i++) {
		fprintf(output, "2:S:%s:2\n", sgroup[nf][i].dataName);
	}
	for (i = 0; i < ichkno[nf]; i++) {
		sprintf(buffer, "%s", checkBox[nf][i].dataName);
		fprintf(output, "2:C:%s\n", buffer);
	}
	for (i = 0; i < icombox[nf]; i++) {
		// list type
		if (combox[nf][i].setdnamelst == NULL)
			p = 0;
		else
			p = strstr(combox[nf][i].setdnamelst, ".");
		if (p) {
			p++;
			if (combox[nf][i].dataName)
				sprintf(buffer, "%s", combox[nf][i].dataName);
			else
				sprintf(buffer, "%s", p);
			len = combox[nf][i].comboBounds.y1 /5;
		}
		else {
			if (combox[nf][i].dataName)
				sprintf(buffer, "%s", combox[nf][i].dataName);
			else
				buffer[0] = 0;

		}
		if(buffer[0]) 
			fprintf(output, "2:L:%s:%d\n", buffer, len);
	}
	for (i = 0; i < irbutton[nf]; i++) {
		sprintf(buffer, "%s", rbutton[nf][i].rbut);
		len = rbutton[nf][i].rbutBound.y1 / 5;
		fprintf(output, "2:R:%s:%d\n", buffer, len);
	}
	for (i = 0; i < ibutton[nf]; i++) {
		sprintf(buffer, "%s", button[nf][i].but);
		len = button[nf][i].butBound.y1 / 5;
		fprintf(output, "2:B:%s:%d\n", buffer, len);
	}
	for (i = 0; i < istable[nf]; i++) {
		tableVarsa(nf, i, stable[nf][i].name, uniq);
	}
}

void globalHeader(char *trn, char *area)
{
	
	indents = 1;
	fprintf(output, "using System;\n");
	fprintf(output, "using System.Collections.Generic;\n");
	fprintf(output, "using System.ComponentModel.DataAnnotations;\n");
	fprintf(output, "using System.Linq;\n");
	fprintf(output, "using System.Text;\n");
	fprintf(output, "using System.Threading.Tasks;\n");
	fprintf(output, "using AkbankFace.Web.Common.Interfaces;\n");
	fprintf(output, "using AkbankFace.Web.Common;\n");
	fprintf(output, "using AkbankFace.BranchBanking.Common;\n");
	fprintf(output, "namespace AkbankFace.Web.%s.Models\n", area);
	fprintf(output, "{\n");
	fprintf(output, "    [Serializable]\n");
	fprintf(output, "    public sealed class %sViewModel : ModelBase\n", trn);
	fprintf(output, "    {\n");
}

char gname[300];
void globalLine(int i)
{
	if (!strstr(globalid[i], "ICol.0.")) {
		gname[0] = 0;
		if (globalid[i][0] == '*') {
			if (strlen(globalid[i]) > 1) {
				fprintf(output, "        public List<ListTypes> %s { get; set; }\n", buyukHarf(globalid[i] + 1));
				globalyazdi = 1;
			}
		}
		else
			if (globalid[i][0] == '-') {
				fprintf(output, "        public bool %s { get; set; }\n", buyukHarf(globalid[i] + 1));
				globalyazdi = 1;
			}
			else
				if(strlen(globalid[i]) > 0)
					fprintf(output, "        public string %s { get; set; }\n", globalid[i]);
	}
}

void globalOthers(int i)
{
	char* p;
	if (strstr(globalid[i], "ICol.0.")) {
		p = strstr(globalid[i], "ICol.0.");
		if (p) {
			*p = 0;
			p = p + 7;
			if (gname[0] == 0 || (gname[0] && strcmp(gname, globalid[i]))) {
				if (gname[0] && strcmp(gname, globalid[i])) {
					fprintf(output, "        }\n");
					strcpy(gname, globalid[i]);
					fprintf(output, "        public List<%sICol> %sIColList { get; set; }\n", buyukHarf(gname), buyukHarf(gname));
					fprintf(output, "        public %sICol %sIColProp { get; set; }\n", buyukHarf(gname), buyukHarf(gname));
					fprintf(output, "        [Serializable]\n");
					fprintf(output, "        public sealed class %sICol\n", buyukHarf(gname));
					fprintf(output, "        {\n");
					globalyazdi = 1;
				}
				else 
				if(gname[0] == 0) {
					strcpy(gname, globalid[i]);
					fprintf(output, "        public List<%sICol> %sIColList { get; set; }\n", buyukHarf(gname), buyukHarf(gname));
					fprintf(output, "        public %sICol %sIColProp { get; set; }\n", buyukHarf(gname), buyukHarf(gname));
					fprintf(output, "        [Serializable]\n");
					fprintf(output, "        public sealed class %sICol\n", buyukHarf(gname));
					fprintf(output, "        {\n");
					globalyazdi = 1;
				}
			}
			if(strlen(p) > 0)
				fprintf(output, "            public string %s { get; set;}\n", buyukHarf(p));
		}
	}
}

void globalEnd()
{
	fprintf(output, "        public string Actiontag{ get; set; }\n");
	fprintf(output, "        public string Fcall{ get; set; }\n");
	fprintf(output, "        public string Func{ get; set; }\n");
	fprintf(output, "    }\n");
	fprintf(output, "}\n");
	// fprintf(output, "// bu modelde kullanilacak tanim yapilmamistir. Silinebilir.\n");
}

void globOku(char *gf)
{
	FILE *g;
	char* p;
	char gbuf[300];
	g = fopen(gf, "r");
	if (g) {
		fprintf(output, "\n");
		while (fgets(gbuf, 200, g)) {
			rmnl(gbuf);
			p = gbuf;
			if (gbuf[0] == '@') p = gbuf + 1;
			globalid[iglobalid] = (char *)calloc(1, strlen(p) + 1);
			strcpy(globalid[iglobalid], buyukHarf(p));
			iglobalid++;
		}
		fclose(g);
	}
	/*else fprintf(output, "glob okunamadi %s\n", gf);*/
}

extern int bakBakalim(char *, int);


#define DEBUGX
#define NDEBUGX

int readExtras(char* area, char* hdir)
{
	int  erc = 1003;
	FILE* fx;
	char bfx[300];
	char filename[300];
	strcpy(filename, hdir);;
	strcat(filename, SEPERATOR);
	strcat(filename, area);
	strcat(filename, SEPERATOR);
	strcat(filename, area);
	strcat(filename, "extras.txt");
	fx = fopen(filename, "r");
	if (fx) {
		while (fgets(bfx, 200, fx)) {
			rmnl(bfx);
			GlobalEkle(buyukHarf(bfx), (char*)"*");
		}
		fclose(fx);
		erc = 0;
	}
	return erc;
}

int readGetList(char* area, char* hdir)
{
	int  erc = 1003;
	FILE* fx;
	char* p, bfx[300], glob[300];
	char filename[300];
	strcpy(filename, hdir);;
	strcat(filename, SEPERATOR);
	strcat(filename, area);
	strcat(filename, SEPERATOR);
	strcat(filename, area);
	strcat(filename, "GetList.txt");
	fx = fopen(filename, "r");
	if (fx) {
		while (fgets(bfx, 200, fx)) {
			rmnl(bfx);
			if (strstr(bfx, "No")) continue;
			p = strstr(bfx, "=");
			if (p) {
				p++;
				while (*p && *p == ' ') p++;
				strcpy(glob, buyukHarf(p));
				GlobalEkle(glob, (char*)"*");
			}
		}
		fclose(fx);
		erc = 0;
	}
	return erc;
}
void globalYaz(char* gfile)
{
	FILE* fx;
	int  i;
	if (iglobalid > 0) {
		fx = fopen(gfile, "w");
		if (fx) {
			for (i = 0; i < iglobalid; i++) {
				if (globalid[i][0] == '-' || globalid[i][0] == '*')
					if(strlen(globalid[i]) > 1)
						fprintf(fx, "%c%s\n", globalid[i][0], globalid[i] + 1);
				else fprintf(fx, "%s\n", globalid[i]);
			}
			fclose(fx);
		}
	}
}
void eksikEkle(int nf, char *fname, char *areaName, char *unique)
{
	int i, j;
	for (i = 0; i < istext[nf]; i++) {
		if (stextfield[nf][i].dataName)
			GlobalEkle(stextfield[nf][i].dataName, "");
		else
			if (stextfield[nf][i].name)
				GlobalEkle(stextfield[nf][i].name, "");
	}
	for (i = 0; i < icombox[nf]; i++) {
		if (combox[nf][i].comboxName)
			GlobalEkle(combox[nf][i].comboxName, "-");
	}
	for (i = 0; i < ibutton[nf]; i++) {
		if (button[nf][i].butName)
			GlobalEkle(button[nf][i].but, "");
	}
	for (i = 0; i < istable[nf]; i++) {
		if (stable[nf][i].name) {
			GlobalEkle(stable[nf][i].name, "+");
			for (j = 0; j < stable[nf][i].icols; j++) {
				// giris bilgisi olmali
				if (stable[nf][i].cols[j].dataname)
					GlobalEkle(stable[nf][i].cols[j].dataname, "0");
				else
					if (stable[nf][i].cols[j].kdataname)
						GlobalEkle(stable[nf][i].cols[j].kdataname, "0");
			}
			GlobalEkle(stable[nf][i].name, ":");
		}
	}
	for (i = 0; i < irbutton[nf]; i++) {
		if (rbutton[nf][i].rbutText)
			GlobalEkle(rbutton[nf][i].rbutText, "");
	}
}

int main(int argc, char **argv)
{
	FILE *fp;
	int  i, ret, ilk, son, iarg, procId;
	char filename[300];
	char modelname[300];
	char viewname[300];
	char outdir[200];
	char mfile[200];


	char unique[5];
	char nodisplay[10];
	char fglobal[300];
	char gfile[300], gfile1[300];
	char *p;

	/* get tables and coulmns of connected database */
	output = stdout;

	// SetConsoleOutputCP(CP_UTF8);
	param = 0;
	if (argc > 9) {
		param = atoi(argv[1]);
		if (param == 0) {
			fprintf(output, "kullanım: models [1/2/4] <ofile> <dir> <areaName> <unique> <modelname> <java_file>\n");
			return(0);
		}
		strcpy(outdir, argv[2]);
		strcpy(trndir, argv[3]);
		strcpy(areaName, argv[4]);
		strcpy(unique, argv[5]);
		strcpy(nodisplay, "no");
		strcpy(viewname, argv[7]);
		procId = atoi(argv[8]);
		iarg = argc;
		sprintf(fglobal, "%s%s\\Models\\%sGlobalModel.cs", outdir, trndir, trndir);
		// strcat(fglobal, "\\");
		//strcat(fglobal, trndir);
		//strcat(fglobal, "\\");
		//strcat(fglobal, "Models");
		//strcat(fglobal, "\\");
		//strcat(fglobal, trndir);
		//strcat(fglobal, "GlobalModel.cs");
		strcpy(gfile, argv[9]);
		p = strstr(gfile, "INDIRS");
		if (p) *p = 0;
		strcat(gfile, PREFS);
		strcat(gfile, trndir);
		strcat(gfile, "\\");
		strcat(gfile, trndir);
		strcpy(gfile1, gfile);
		strcat(gfile, "global.preference");

		if (bakBakalim("be1converter", procId) == 0)
			exit(0);

		for (i = 9; i < argc; i++) {
			strcpy(mfile, argv[i]);
			fp = fopen(mfile, "r");
			if (!fp) {
				fprintf(output, "java file %s bulunamadi\n", argv[i]);
				return(0);
			}


			strcpy(modelname, outdir);
			//strcat(modelname, "\\");
			//strcat(modelname, trndir);
			//strcat(modelname, viewname);
			//strcat(modelname, ".cs");

			strcpy(filename, outdir);
			strcat(filename, trndir);
			strcat(modelname, "\\");
			strcat(modelname, trndir);
			strcat(modelname, viewname);
			strcat(filename, "model.preference");
			getHost(filename, trndir);

			// strcat(modelname, ".cs");
			// output    = fopen(modelname,"w");
			ibutton[nfiles] = 0;
			if (fp) {
				input = fp;
				fclass = 0;
				finit = 0;
				fexit = 0;
				fpanel = 0;
				ftxtfunc = 0;
				flblfunc = 0;
				frbutton = 0;
				fbutton = 0;
				fcombo = 0;
				floader = 0;
				fquery = 0;
				fbuttongrps = 0;
				do {
					ret = javaClass();
					if (ret == EOF) ret = initMi();
					if (ret == EOF) ret = exitMi();
					if (ret == EOF) ret = panelMi();
					if (ret == EOF) ret = elements();
					/*
					com.akbank.client.staticdata.DataLoader
					sdl = (com.akbank.client.staticdata.DataLoader)
					getContext().getService("DataLoader");
					sdl.load("tefasFonKurucuList" ,getContext());
					*/
					Processed = 1;
				} while (ret != -2);
				fclose(fp);
				nfiles++;

				if (param == 2) {
					char xname[300];
					ilk = 0;
					if (i == 9) {
						ilk = 1;
						itext = 0;
					}
					son = 0;
					if (i + 1 == argc) son = 1;
					// mytextWrite(param, argv[i], areaName, unique, nodisplay, ilk, son);
					getGlobals(param, 0, trndir, areaName, unique, nodisplay, son);
					strcpy(xname, gfile1);
					strcat(xname, unique);
					strcat(xname, "mglobal.preference");
					globalYaz(xname);
				}
				// if(param == 3) mytableWrite(modelname, outdir, areaName, unique);
				if (param == 4) {
					writeViews(nfiles, modelname, unique);
				}
				if (param == 4) {
					writeViews(nfiles-1, modelname, unique);
					break; // bir file olmali
				}
			}
			*unique = *unique + 1;
		}
		if (param == 5) {
			int  j, varmis = 0;
			iglobalid = 0;
			for (i = 0; i < nfiles; i++) {
				son = i + 1;
				mytextWrite(param, i, trndir, areaName, unique, nodisplay, son);
			}
			readGetList(trndir, outdir);
			readExtras(trndir, outdir);
			globOku(gfile);
			//for (j = 0; j < i - 8; j++) {
			//	strcpy(xname, gfile1);
			//	sprintf(mysay, "%d", j);
			//	strcat(xname, mysay);
			//	strcat(xname, "mglobal.preference");
			//	globOku(xname);
			//}
			for (i = 0; i < iglobalid || globalid[i]; i++) {
				//if (i == 0)
				//	globalHeader(trndir, areaName);
				if (globalid[i] == 0) break; // globOku ile okuyamadiginda...
				for (j = 0; j < i; j++) {
					if (strcmp(globalid[i], globalid[j]) == 0) {
						varmis = 1;
						break;
					}
					if (strcmp(globalid[i], "value") == 0) {
						varmis = 1;
						break;
					}
				}
				if (varmis) {
					varmis = 0;
					continue;
				}
				globalLine(i);
			}
			for (i = 0; i < iglobalid || globalid[i]; i++) {
				globalOthers(i);
			}
			if (gname[0]) {
				fprintf(output, "        }\n");
			}
			globalEnd();
		}
	}
	else {
		fprintf(output, "kullanım: models [1/2/3/4] <java_file> <ofile> <odir>\n");
		fprintf(output, "   1 <ofile> <odir> debug info\n");
		fprintf(output, "   2 <ofile> <odir> <areaName> <unique> <modelname> <java_files> creates <viewname>model.cs\n");
		fprintf(output, "   4 <ofile> <odir> <areaName> <unique> <modelname> <java_files> creates View Variable\n");
	}
	return 0;
}
