#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include <windows.h>

FILE *input;
FILE *output;

int fclass,
finit,
fpanel,
ftxtfunc,
flblfunc,
frbutton,
fbutton,
fcombo,
fchkbox,
fexit,
fquery,
fscroll,
ftable,
floader,
fbuttongrps;
int  unique;

int eprintid = 0;

int param = 0;

int panelno = -1;
int combono = 0;
int checkno = 0;
int scrollno = 0;
int tableno = 0;
int loadno = 0;
int qlistno = 0;
int txtno = 0;
int lblno = 0;
int buttonno = 0;
int buttongrpno = 0;

int Processed = 0;
char indent[200];
int  indents = 0;
int  scriptVar = 0;
int  onchange = 0;
int  hiddenk = 0;

int rdiv = 0;

char buf[MAXCHAR + 1];
char symbol[MAXCHAR + 1];
char program[MAXCHAR + 1];
char indexname[MAXCHAR + 1];

char xsplit[10][100];

char currpanel[NPANEL][MAXCHAR + 1];
char labels[MAXLABELS][LBLMAX][LBLSIZE];
char txtfields[MAXTXT][TXTMAX][TXTSIZE];
char buttons[MAXBTN][TXTMAX][BTNSIZE];
char buttongrps[MAXBTN][TXTMAX][BTNSIZE];
char combobox[MAXBTN][TXTMAX][BTNSIZE];
char chkBox[MAXBTN][TXTMAX][BTNSIZE];
char tscroll[MAXBTN][TXTMAX][BTNSIZE];
char table[MAXBTN][TXTMAX][BTNSIZE];
char qlist[MAXBTN][TXTMAX][BTNSIZE];
char loads[MAXBTN][TXTMAX][BTNSIZE];

void scmandaCondition(int);
void setmandaCondition(int);
void showmsgCondition(int);
void invisibleCondition(int);
void svalueCondition(int);
void datasplitCondition(int);
void datamergeCondition(int);
char *indentstr();

int iconstant;
struct CONSTANTS {
	char *vtype; // view, action, cond, oper, flow, final, java
	char *vname; // constant name R944.R944constants.<vname>
	char *vval;  // corresponding constant data
} constants[300];

char tranname[20];

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
	int  i, len;
	len = (int) strlen(p);
	p1 = (char *)calloc(1, (int) strlen(p) + 1);
	for (i = 0; i < len; i++) {
		p1[i] = buyukh(p[i]);
		p1[i + 1] = 0;
	}
	len = (int) strlen(s);
	s1 = (char *)calloc(1, (int) strlen(s) + 1);
	for (i = 0; i < len; i++) {
		s1[i] = buyukh(s[i]);
		s1[i + 1] = 0;
	}
	return (p1 && s1) ? strcmp(p1, s1) : 0;
}

int strncasecmp(char *s, char *t, int n)
{
	int  i, len;
	len = (int)strlen(s);
	
	for (i = 0; i < len; i++) {
		if (buyukh(s[i]) > buyukh(t[i])) return 1;
		if (buyukh(s[i]) < buyukh(t[i])) return -1;
	}
	return 0;
}

char *laststr(char *p, char *s)
{
	int  i, len = (int)strlen(p);
	for (i = len - 1; i >= 0; i--) {
		if (p[i] == s[0])
			return p + i;
	}
	return 0;
}

char *skipsome(char *p)
{
	int i, k, len = (int)strlen(p);
	char sbuf[200];
	char *p1;
	k = 0;
	sbuf[0] = 0;
	for (i = 0; i < len; i++) {
		if ((p[i] >= '0' && p[i] <= '9') ||
			(p[i] >= 'a' && p[i] <= 'z') ||
			(p[i] >= 'A' && p[i] <= 'Z')) {
			sbuf[k] = p[i];
			k++;
			sbuf[k] = 0;
		}
	}
	if (strlen(sbuf)) {
		p1 = (char*)calloc(1, strlen(sbuf) + 1);
		strcpy(p1, sbuf);
	}
	else p1 = 0;
	return p1;
}

void myprologue(char *program, char *tranid, char * area, char *title)
{
	int  ir, listno;
	fprintf(output, "@model AkbankFace.Web.%s.Models.%sViewModel\n", area, tranid);

	fprintf(output, "@{\n");
	indents++;
	indentstr();
	fprintf(output, "%s", indent);
	fprintf(output, "Layout = Html.AkbankFace().ChooseLayout(\n");
	fprintf(output, "%s", indent);
	fprintf(output, "        config => config.Layout(LayoutType.FacePlusLayout)\n");
	fprintf(output, "%s", indent);
	fprintf(output, "    );\n");
	fprintf(output, "%s", indent);
	// title modelde var
	fprintf(output, "ViewBag.Title = \"%s\";\n", program);
	//fprintf(output, "%s", indent);
	//fprintf(output, "Model.FunctionInfo.Name = \"%s\";\n", title); // burada program olabilir
	if (irbutton > 0) {
		fprintf(output, "%s", indentstr());
		listno = 0;
		for (ir = 0; ir < irbutton; ir++) {
			if(listno != rbutton[ir].rbutTab) {
				fprintf(output, "List<ListTypes> list%d = new List<ListTypes>();\n", 
					rbutton[ir].rbutTab);
				listno = rbutton[ir].rbutTab;
			}
			fprintf(output, "%s", indentstr());
			fprintf(output, "list.Add(new ListTypes(){ Text = \"%s\", Value = \"%s\" });\n", 
				rbutton[ir].rbutText, rbutton[ir].rbutVal);
		}
	}
	indents--;
	indentstr();
	fprintf(output, "%s", indent);
	fprintf(output, "}\n");
}

void myepilogue(int panel)
{

	//fprintf(output, "%s", indent);
	//fprintf(output, "</div>\n");

		indents--;
		indentstr();
		fprintf(output, "%s", indent);
		fprintf(output, "}\n");
		indents--;
		indentstr();
		fprintf(output, "%s", indent);
		fprintf(output, "</div>\n");
}

char *indentstr()
{
	int i;
	indent[0] = 0;
	for (i = 0; i<indents; i++) {
		strcat(indent, "   ");
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

void myReplace(char *str, char s, char t)
{
	int i, len;
	len = (int) strlen(str);
	for (i = 0; i<len; i++) {
		if (str[i] == s) str[i] = t;
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
	if (fgets(buf, MAXCHAR, input)) {
		rmnl(buf);
		if (strstr(buf, "import")) {
			Processed = 1;
			return EOF;
		}
		p1 = pbuf;
		while (*p1 == ' ') p1++;
		if ((*p1 == '/' && *(p1 + 1) == '*')) {
			if (!strstr(buf, "*/")) {
				while (1) {
					fgets(buf, MAXCHAR, input);
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
	else ret = -2;
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
	char *pt;
	ret = getsymbol(str);

	if (ret != EOF) {
		pt = strstr(symbol, " ");
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
			case PTABLES:
			case PTABLE:
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
	if (strcmp(inp, CADDEXIT) == 0) return PADDEXIT;
	if (strcmp(inp, CADDEXITS) == 0) return PADDEXIT;
	if (strcmp(inp, CSHOWMSG) == 0) return PSHOWMSG;
	if (strcmp(inp, CSETVALUE) == 0) return PSETVALUE;
	if (strcmp(inp, CDATAMERGE) == 0) return PDATAMERGE;
	if (strcmp(inp, CDATASPLIT) == 0) return PDATASPLIT;
	if (strcmp(inp, CCLEAR) == 0) return PCLEAR;
	if (strcasecmp(inp, CSETCLEAR) == 0) return PSETCLEAR;
	if (strcasecmp(inp, CENABLE) == 0) return PENABLE;
	if (strcasecmp(inp, CDISABLE) == 0) return PDISABLE;
	if (strcasecmp(inp, CVISIBLE) == 0) return PVISIBLE;
	if (strcasecmp(inp, CLSTSEARCH) == 0) return PLSTSEARCH;
	if (strcasecmp(inp, CSIGNAL) == 0) return PSIGNAL;
	if (strcmp(inp, CINVISIBLE) == 0) return PINVISIBLE;
	if (strcmp(inp, CADDCONDITION) == 0) return PADDCONDITION;
	if (strcmp(inp, CLOADER) == 0) return PLOADER;
	if (strcmp(inp, CQUERYLSTFUNC) == 0) return PQUERYLSTFUNC;
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
	while(*p1 == ' ') p1++;
	x[0] = atoi(p2);
	p2 = p1;
	while (*p1 != 0 && (*p1 != ',' && *p1 != ')')) p1++;
	if (*p1 == 0 || *p1 == ')') {
		x[1] = atoi(p2);
		return;
	}
	*p1 = 0;
	p1++;
	while (*p1 == ' ') p1++;
	x[1] = atoi(p2);
	p2 = p1;
	while (*p1 != 0 && *p1 != ',') p1++;
	*p1 = 0;
	p1++;
	while(*p1 == ' ') p1++;
	x[2] = atoi(p2);
	p2 = p1;
	while (*p1 != 0 && *p1 != ')') p1++;
	*p1 = 0;
	x[3] = atoi(p2);
}

int findPanelno(char *pname, char *pp)
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
			if (ret != EOF) { Processed = 1; break; }
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
					p = p + (int)strlen(CPAGE) + 1;
					// slayout.name <- "name"

					p1 = p;
					while (*p != 0 && *p != '"') p++;
					*p = 0;
					slayout.name = (char *) calloc(1, (int) strlen(p1) + 1);
					strcpy(slayout.name, p1);
				}
				else {
					slayout.name = (char *)calloc(1, (int)strlen("noname") + 1);
					strcpy(slayout.name, "noname");
					//p = buf;
				}
				continue;
			}
			// CTITLE "this.setTitle("
			if (getinsym(CTITLE) == PTITLE) {
				char *p1, *p;
				p = strstr(buf, CTITLE);
				if (p) {
					p = p + (int)strlen(CTITLE) + 1;
					p1 = p;
					while (*p != 0 && *p != '"') p++;
					*p = 0;
					slayout.title = (char *) calloc(1, (int) strlen(p1) + 1);
					strcpy(slayout.title, p1);
				}
				else {
					slayout.title = (char *)calloc(1, 3);
					strcpy(slayout.title, "  ");
				}
				continue;
			}
			// CBOUND "this.setBounds("
			if (getinsym(CBOUND) == PBOUND) {
				int x[4];
				char *p1, *p;
				p = strstr(buf, CBOUND);
				if (p) {
					p = p + (int)strlen(CBOUND);
					p1 = p;
					while (*p != 0 && *p != ')') p++;
					*p = 0;
					mysplit(x, p1, ',');
					slayout.bound.x0 = x[0];
					slayout.bound.y0 = x[1];
					slayout.bound.x1 = x[2];
					slayout.bound.y1 = x[3];
				}
				continue;
			}
			// CADD "this.add(get"
			if (getinsym(CADD) == PADD) {
				char *p = strstr(buf, CADD);
				int  curpanel = 0;
				if (p) {
					p = p + (int) strlen(CADD);
					if (strstr(buf, CADDPANEL)) {
						char pname[200];
						slayout.added[slayout.iadded].npanel = findPanelno(pname, p);
						if (slayout.added[slayout.iadded].npanel >= 0)
							curpanel = slayout.added[slayout.iadded].npanel;
						slayout.added[slayout.iadded].nbutton = EOF;
						slayout.added[slayout.iadded].type = PADDPANEL;
						slayout.added[slayout.iadded].addb =
							(char *)calloc(1, (int)strlen(pname) + 1);
						strcpy(slayout.added[slayout.iadded].addb, pname);
						slayout.iadded++;
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
							slayout.added[slayout.iadded].npanel = curpanel;
							slayout.added[slayout.iadded].nbutton = EOF;
							slayout.added[slayout.iadded].type = PADDSTABLE;
							slayout.added[slayout.iadded].addb =
								(char *)calloc(1, (int)strlen(pname) + 1);
							strcpy(slayout.added[slayout.iadded].addb, pname);
							slayout.iadded++;
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
							slayout.added[slayout.iadded].npanel = x / 100;
							slayout.added[slayout.iadded].nbutton = x % 100;
							slayout.added[slayout.iadded].type = PADDBUTTON;
							slayout.added[slayout.iadded].addb =
								(char *)calloc(1, strlen(bname) + 1);
							strcpy(slayout.added[slayout.iadded].addb, bname);
							slayout.iadded++;
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
					p = p + (int)strlen(CGETGRP);
					x = findGroup(addbtn, p);
					slayout.added[slayout.iadded].npanel = x / 100;
					slayout.added[slayout.iadded].nbutton = x % 100;
					slayout.added[slayout.iadded].type = PGETGRP;
					slayout.added[slayout.iadded].addb =
						(char *)calloc(1, (int)strlen(addbtn) + 1);
					strcpy(slayout.added[slayout.iadded].addb, addbtn);
					slayout.iadded++;
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
	case PENABLE:
		for (i = 0; i < sexit.ienable; i++) {
			if (strcasecmp(sexit.senable[i].sName, name) == 0)
				return i;
		}
		break;
	case PDISABLE:
		for (i = 0; i < sexit.idisable; i++) {
			if (strcasecmp(sexit.sdisable[i].sName, name) == 0)
				return i;
		}
		break;
	case PVISIBLE:
		for (i = 0; i < sexit.ivisible; i++) {
			if (strcasecmp(sexit.svisible[i].sName, name) == 0)
				return i;
		}
		break;
	case PLSTSEARCH:
		for (i = 0; i < sexit.ilstsearch; i++) {
			if (strcasecmp(sexit.slstsearch[i].sName, name) == 0)
				return i;
		}
		break;
	case PSIGNAL:
		for (i = 0; i < sexit.isignal; i++) {
			if (strcasecmp(sexit.signal[i].sName, name) == 0)
				return i;
		}
		break;
	case PCLEAR:
		for (i = 0; i < sexit.iscmanda; i++) {
			if (strcasecmp(sexit.scmanda[i].sName, name) == 0)
				return i;
		}
		break;
	case PSETCLEAR:
		for (i = 0; i < sexit.isetmanda; i++) {
			if (strcasecmp(sexit.setmanda[i].sName, name) == 0)
				return i;
		}
		break;
	case PSHOWMSG:
		for (i = 0; i < sexit.ishowmsg; i++) {
			if (strcasecmp(sexit.showMsg[i].sName, name) == 0)
				return i;
		}
		break;
	case PSETVALUE:
		for (i = 0; i < sexit.isvalue; i++) {
			if (strcasecmp(sexit.svalue[i].sName, name) == 0)
				return i;
		}
		break;
	case PDATAMERGE:
		for (i = 0; i < sexit.idatamerge; i++) {
			if (strcasecmp(sexit.datamerge[i].sName, name) == 0)
				return i;
		}
		break;
	case PDATASPLIT:
		for (i = 0; i < sexit.idatasplit; i++) {
			if (strcasecmp(sexit.datasplitfunc[i].sName, name) == 0)
				return i;
		}
		break;
	case PINVISIBLE:
		for (i = 0; i < sexit.iInvisible; i++) {
			if (strcasecmp(sexit.sinvisible[i].sName, name) == 0)
				return i;
		}
		break;
	case PQUERYLSTFUNC:
		for (i = 0; i < sexit.iqueryList; i++) {
			if (strcasecmp(sexit.squeryList[i].sName, name) == 0)
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
	if (!p) {
		p = strstr(buf, CADDEXITS);
		p1 = p + (int)strlen(CADDEXITS);
	}
	else {
		p1 = p + (int)strlen(CADDEXIT);
	}
	p = p1;
	for (i = 0; i < 3; i++) {
		while (*p != ',' && *p != 0) p++;
		*p = 0; p++;
		strcpy(a[i], p1);
		p1 = p;
		p1++;
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
		indx = sexit.iscmanda;
		sexit.iscmanda++;
		sexit.scmanda[indx].iaddexit = 0;
		sexit.scmanda[indx].iaddcon = 0;
		sexit.scmanda[indx].sName = (char *) calloc(1, (int) strlen(name) + 1);
		strcpy(sexit.scmanda[indx].sName, name);
	}
	if ((p = strstr(buf, CSETTAB))) {
		while (*p != '{' && *p != 0) p++;
		p++;
		p1 = p;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit.scmanda[indx].setTabnum = (char *)calloc(1, strlen(p1) + 1);
		strcpy(sexit.scmanda[indx].setTabnum, p1);
	}
	p = strstr(buf, CADDEXIT);
	if (!p) p = strstr(buf, CADDEXITS);
	if (p) {
		char a[3][100];
		char *pp;
		splitEvent(a);
		pp = a[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit.scmanda[indx].iaddexit;
		sexit.scmanda[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0]) + 1);
		strcpy(sexit.scmanda[indx].saddExit[j].fieldName, a[0]);
		sexit.scmanda[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit.scmanda[indx].saddExit[j].clearFunc, a[1]);
		sexit.scmanda[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit.scmanda[indx].saddExit[j].eventName, a[2]);
		sexit.scmanda[indx].iaddexit++;
	}
	scmandaCondition(indx);
	return indx;
}

void scmandaCondition(int indx)
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
		p1 = p + (int) strlen(CADDCONDITION) + 1;

		while (*p1 != ' ') p1++;
		if (*p1 == ' ') p1++;
		p = p1;
		while (*p != '(') p++;
		*p = 0;
		p++;
		// p1 de condition var
		p3 = p;

		while (*p != ')') p++;
		*p = 0;

		for (indx = 0; indx < sexit.iscmanda; indx++) {
			if (strcmp(sexit.scmanda[indx].sName, p2) == 0) {
				j = sexit.scmanda[indx].iaddcon;
				sexit.scmanda[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p1) + 1);
				strcpy(sexit.scmanda[indx].addCondition[j], p1);
				sexit.scmanda[indx].iaddcon++;
				j++;
				sexit.scmanda[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p2) + 1);
				strcpy(sexit.scmanda[indx].addCondition[j], p2);
				sexit.scmanda[indx].iaddcon++;
				j++;
				sexit.scmanda[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p3) + 1);
				strcpy(sexit.scmanda[indx].addCondition[j], p3);
				sexit.scmanda[indx].iaddcon++;

			}
		}
	}
}

int setMandatory(int current, char *name)
{
	int indx, j;
	char *p, *p1;
#ifdef DEBUGX
	fprintf(output, "====%d %s %s\n", current, name, CSETCLEAR);
#endif
	if (!strstr(name, CSETCLEAR)) return EOF;
	indx = adVarmi(current, name);
#ifdef DEBUGX
	fprintf(output, "====indx %d\n", indx);
#endif
	if (indx == EOF) {
		p = name;
		while (*p != 0 && *p != '(') p++;
		*p = 0;
		indx = sexit.isetmanda;
		sexit.isetmanda++;
		sexit.setmanda[indx].iaddexit = 0;
		sexit.setmanda[indx].iaddcon = 0;
		sexit.setmanda[indx].sName = (char *) calloc(1, (int) strlen(name) + 1);
		strcpy(sexit.setmanda[indx].sName, name);
	}
	if ((p = strstr(buf, CSETTAB))) {
		while (*p != '{' && *p != 0) p++;
		p++;
		p1 = p;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit.setmanda[indx].setTabnum = (char *)calloc(1, strlen(p1) + 1);
		strcpy(sexit.setmanda[indx].setTabnum, p1);
	}
	p = strstr(buf, CADDEXIT);
	if (!p) p = strstr(buf, CADDEXITS);
	if (p) {
		char a[3][100];
		char *pp;
		splitEvent(a);
		pp = a[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit.setmanda[indx].iaddexit;
		sexit.setmanda[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0]) + 1);
		strcpy(sexit.setmanda[indx].saddExit[j].fieldName, a[0]);
		sexit.setmanda[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit.setmanda[indx].saddExit[j].clearFunc, a[1]);
		sexit.setmanda[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit.setmanda[indx].saddExit[j].eventName, a[2]);
		sexit.setmanda[indx].iaddexit++;
	}
	setmandaCondition(indx);
	return indx;
}

void setmandaCondition(int indx)
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
		p1 = p + (int) strlen(CADDCONDITION) + 1;
		while (*p1 != ' ') p1++;
		if (*p1 == ' ') p1++;
		p = p1;
		while (*p != '(') p++;
		*p = 0;
		p++;
		// p1 de condition var
		p3 = p;
		while (*p != ')') p++;
		*p = 0;
		for (indx = 0; indx<sexit.isetmanda; indx++) {
			if (strcmp(sexit.setmanda[indx].sName, p2) == 0) {


				j = sexit.setmanda[indx].iaddcon;
				sexit.setmanda[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p1) + 1);
				strcpy(sexit.setmanda[indx].addCondition[j], p1);
				sexit.setmanda[indx].iaddcon++;
				j++;
				sexit.setmanda[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p2) + 1);
				strcpy(sexit.setmanda[indx].addCondition[j], p2);
				sexit.setmanda[indx].iaddcon++;
				j++;
				sexit.setmanda[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p3) + 1);
				strcpy(sexit.setmanda[indx].addCondition[j], p3);
				sexit.setmanda[indx].iaddcon++;

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
		indx = sexit.ishowmsg;
		sexit.ishowmsg++;
		sexit.showMsg[indx].iaddexit = 0;
		sexit.showMsg[indx].iaddcon = 0;
		sexit.showMsg[indx].sName = (char *) calloc(1, (int) strlen(name) + 1);
		strcpy(sexit.showMsg[indx].sName, name);
	}
	if ((p = strstr(buf, CSETTAB))) {
		while (*p != '{' && *p != 0) p++;
		p++;
		p1 = p;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit.showMsg[indx].setTabnum = (char *)calloc(1, strlen(p1) + 1);
		strcpy(sexit.showMsg[indx].setTabnum, p1);
	}
	if ((p = strstr(buf, CSETTITLE))) {
		p1 = p + (int) strlen(CSETTITLE) + 2;
		p = p1;
		while (*p != '"' && *p != 0) p++;
		*p = 0;
		sexit.showMsg[indx].title = (char *) calloc(1, (int) strlen(p1) + 1);
		strcpy(sexit.showMsg[indx].title, p1);
	}
	if ((p = strstr(buf, CSETMSG))) {
		p1 = p + (int) strlen(CSETMSG) + 1;
		p = p1;
		while (*p != '"' && *p != 0) p++;
		*p = 0;
		sexit.showMsg[indx].msg = (char *) calloc(1, (int) strlen(p1) + 1);
		strcpy(sexit.showMsg[indx].msg, p1);
	}
	if ((p = strstr(buf, CSETMSGTYPE))) {
		p1 = p + (int) strlen(CSETMSGTYPE);
		p = p1;
		while (*p != ')' && *p != 0) p++;
		*p = 0;
		sexit.showMsg[indx].msgType = atoi(p1);
	}
	if ((p = strstr(buf, CSETMSGOPTION))) {
		p1 = p + (int) strlen(CSETMSGOPTION);
		p = p1;
		while (*p != ')' && *p != 0) p++;
		*p = 0;
		sexit.showMsg[indx].optionType = atoi(p1);
	}
	p = strstr(buf, CADDEXIT);
	if (!p) p = strstr(buf, CADDEXITS);
	if (p) {
		char a[3][100];
		char *pp;
		splitEvent(a);
		pp = a[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit.showMsg[indx].iaddexit;
		sexit.showMsg[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0]) + 1);
		strcpy(sexit.showMsg[indx].saddExit[j].fieldName, a[0]);
		sexit.showMsg[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit.showMsg[indx].saddExit[j].clearFunc, a[1]);
		sexit.showMsg[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit.showMsg[indx].saddExit[j].eventName, a[2]);
		sexit.showMsg[indx].iaddexit++;
	}
	showmsgCondition(indx);
	return indx;
}

void showmsgCondition(int indx)
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
		p1 = p + (int) strlen(CADDCONDITION) + 1;
		while (*p1 != ' ') p1++;
		if (*p1 == ' ') p1++;
		p = p1;
		while (*p != '(') p++;
		*p = 0;
		p++;
		// p1 de condition var
		p3 = p;
		while (*p != ')') p++;
		*p = 0;
		for (indx = 0; indx<sexit.ishowmsg; indx++) {
			if (strcmp(sexit.showMsg[indx].sName, p2) == 0) {


				j = sexit.showMsg[indx].iaddcon;
				sexit.showMsg[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p1) + 1);
				strcpy(sexit.showMsg[indx].addCondition[j], p1);
				sexit.showMsg[indx].iaddcon++;
				j++;
				sexit.showMsg[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p2) + 1);
				strcpy(sexit.showMsg[indx].addCondition[j], p2);
				sexit.showMsg[indx].iaddcon++;
				j++;
				sexit.showMsg[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p3) + 1);
				strcpy(sexit.showMsg[indx].addCondition[j], p3);
				sexit.showMsg[indx].iaddcon++;

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
		indx = sexit.iInvisible;
		sexit.iInvisible++;
		sexit.sinvisible[indx].iaddexit = 0;
		sexit.sinvisible[indx].iaddcon = 0;
		sexit.sinvisible[indx].sName = (char *) calloc(1, (int) strlen(name) + 1);
		strcpy(sexit.sinvisible[indx].sName, name);
	}
	//if ((p = strstr(buf, CSETTAB))) {
	//	while (*p != '{' && *p != 0) p++;
	//	p++;
	//	p1 = p;
	//	while (*p != '}' && *p != 0) p++;
	//	*p = 0;
	//	sexit.sinvisible[indx].setTabnum = atoi(p1);
	//}
	p = strstr(buf, CADDEXIT);
	if (!p) p = strstr(buf, CADDEXITS);
	if (p) {
		char a[3][100];
		char *pp;
		splitEvent(a);
		pp = a[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit.sinvisible[indx].iaddexit;
		sexit.sinvisible[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0]) + 1);
		strcpy(sexit.sinvisible[indx].saddExit[j].fieldName, a[0]);
		sexit.sinvisible[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit.sinvisible[indx].saddExit[j].clearFunc, a[1]);
		sexit.sinvisible[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit.sinvisible[indx].saddExit[j].eventName, a[2]);
		sexit.sinvisible[indx].iaddexit++;
	}
	if ((p = strstr(buf, CSETTAB))) {
		while (*p != '{' && *p != 0) p++;
		p++;
		p1 = p;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit.sinvisible[indx].setTabnum = (char *)calloc(1, strlen(p1) + 1);
		strcpy(sexit.sinvisible[indx].setTabnum, p1);
	}
	invisibleCondition(indx);
	return indx;
}

void invisibleCondition(int indx)
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
		p1 = p + (int) strlen(CADDCONDITION) + 1;
		while (*p1 != ' ') p1++;
		if (*p1 == ' ') p1++;
		p = p1;
		while (*p != '(') p++;
		*p = 0;
		p++;
		// p1 de condition var
		p3 = p;
		while (*p != ')') p++;
		*p = 0;
		for (indx = 0; indx<sexit.iInvisible; indx++) {
			if (strcmp(sexit.sinvisible[indx].sName, p2) == 0) {

				j = sexit.sinvisible[indx].iaddcon;
				sexit.sinvisible[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p1) + 1);
				strcpy(sexit.sinvisible[indx].addCondition[j], p1);
				sexit.sinvisible[indx].iaddcon++;
				j++;
				sexit.sinvisible[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p2) + 1);
				strcpy(sexit.sinvisible[indx].addCondition[j], p2);
				sexit.sinvisible[indx].iaddcon++;
				j++;
				sexit.sinvisible[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p3) + 1);
				strcpy(sexit.sinvisible[indx].addCondition[j], p3);
				sexit.sinvisible[indx].iaddcon++;
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
		indx = sexit.isvalue;
		sexit.isvalue++;
		sexit.svalue[indx].iaddexit = 0;
		sexit.svalue[indx].iaddcon = 0;
		sexit.svalue[indx].sName = (char *) calloc(1, (int) strlen(name) + 1);
		strcpy(sexit.svalue[indx].sName, name);
	}
	sexit.svalue[indx].setTabnum = 0;
	if ((p = strstr(buf, CSETTAB))) {
		while (*p != '{' && *p != 0) p++;
		p++;
		p1 = p;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit.svalue[indx].setTabnum = (char *)calloc(1, strlen(p1) + 1);
		strcpy(sexit.svalue[indx].setTabnum, p1);
	}
	if ((p = strstr(buf, CSETDATAELM))) {
		p1 = p + (int) strlen(CSETDATAELM);
		while (*p1 != '"' && *p1 != 0) p1++;
		p1++;
		p = p1;
		while (*p != '"' && *p != 0) p++;
		*p = 0;
		sexit.svalue[indx].dataElement = (char *) calloc(1, (int) strlen(p1) + 1);
		strcpy(sexit.svalue[indx].dataElement, p1);
	}
	// sexit.svalue[indx].setValue = NULL;
	if ((p = strstr(buf, CSETVALUE1))) {
		p1 = p + (int) strlen(CSETVALUE1) + 1;
		p = p1;
		while (*p != '"' && *p != 0) p++;
		*p = 0;
		sexit.svalue[indx].setValue = (char *) calloc(1, (int) strlen(p1) + 1);
		strcpy(sexit.svalue[indx].setValue, p1);
	}
	p = strstr(buf, CADDEXIT);
	if (!p) p = strstr(buf, CADDEXITS);
	if (p) {
		char a[3][100];
		char *pp;
		splitEvent(a);
		pp = a[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit.svalue[indx].iaddexit;
		sexit.svalue[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0]) + 1);
		strcpy(sexit.svalue[indx].saddExit[j].fieldName, a[0]);
		sexit.svalue[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit.svalue[indx].saddExit[j].clearFunc, a[1]);
		sexit.svalue[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit.svalue[indx].saddExit[j].eventName, a[2]);
		sexit.svalue[indx].iaddexit++;
	}
	svalueCondition(indx);
	return indx;
}

void svalueCondition(int indx)
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
		p1 = p + (int) strlen(CADDCONDITION) + 1;
		while (*p1 != ' ') p1++;
		if (*p1 == ' ') p1++;
		p = p1;
		while (*p != '(') p++;
		*p = 0;
		p++;
		// p1 de condition var
		p3 = p;

		while (*p != ')') p++;
		*p = 0;
		for (indx = 0; indx<sexit.isvalue; indx++) {
			if (strcmp(sexit.svalue[indx].sName, p2) == 0) {
				j = sexit.svalue[indx].iaddcon;
				sexit.svalue[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p1) + 1);
				strcpy(sexit.svalue[indx].addCondition[j], p1);
				sexit.svalue[indx].iaddcon++;
				j++;
				sexit.svalue[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p2) + 1);
				strcpy(sexit.svalue[indx].addCondition[j], p2);
				sexit.svalue[indx].iaddcon++;
				j++;
				sexit.svalue[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p3) + 1);
				strcpy(sexit.svalue[indx].addCondition[j], p3);
				sexit.svalue[indx].iaddcon++;

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
		indx = sexit.idatasplit;
		sexit.idatasplit++;
		sexit.datasplitfunc[indx].iaddexit = 0;
		sexit.datasplitfunc[indx].iaddcon = 0;
		sexit.datasplitfunc[indx].sName = (char *) calloc(1, (int) strlen(name) + 1);
		strcpy(sexit.datasplitfunc[indx].sName, name);
	}
	if ((p = strstr(buf, CSETTAB))) {
		while (*p != '{' && *p != 0) p++;
		p++;
		p1 = p;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit.datasplitfunc[indx].setTabnum = (char *)calloc(1, strlen(p1) + 1);
		strcpy(sexit.datasplitfunc[indx].setTabnum, p1);
	}
	if ((p = strstr(buf, CSETDATAELM))) {
		p1 = p + (int) strlen(CSETDATAELM) + 1;
		p = p1;
		while (*p != '"' && *p != 0) p++;
		*p = 0;
		sexit.datasplitfunc[indx].dataElement = (char *) calloc(1, (int) strlen(p1) + 1);
		strcpy(sexit.datasplitfunc[indx].dataElement, p1);
	}
	p = strstr(buf, CADDEXIT);
	if (!p) p = strstr(buf, CADDEXITS);
	if (p) {
		char a[3][100];
		char *pp;
		splitEvent(a);
		pp = a[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit.datasplitfunc[indx].iaddexit;
		sexit.datasplitfunc[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0]) + 1);
		strcpy(sexit.datasplitfunc[indx].saddExit[j].fieldName, a[0]);
		sexit.datasplitfunc[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit.datasplitfunc[indx].saddExit[j].clearFunc, a[1]);
		sexit.datasplitfunc[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit.datasplitfunc[indx].saddExit[j].eventName, a[2]);
		sexit.datasplitfunc[indx].iaddexit++;
	}
	datasplitCondition(indx);
	return indx;
}

void datasplitCondition(int indx)
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
		p1 = p + (int) strlen(CADDCONDITION) + 1;
		while (*p1 != ' ') p1++;
		if (*p1 == ' ') p1++;
		p = p1;
		while (*p != '(') p++;
		*p = 0;
		p++;
		// p1 de condition var
		p3 = p;
		while (*p != ')') p++;
		*p = 0;
		for (indx = 0; indx<sexit.idatasplit; indx++) {
			if (strcmp(sexit.datasplitfunc[indx].sName, p2) == 0) {
				j = sexit.datasplitfunc[indx].iaddcon;
				sexit.datasplitfunc[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p1) + 1);
				strcpy(sexit.datasplitfunc[indx].addCondition[j], p1);
				sexit.datasplitfunc[indx].iaddcon++;
				j++;
				sexit.datasplitfunc[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p2) + 1);
				strcpy(sexit.datasplitfunc[indx].addCondition[j], p2);
				sexit.datasplitfunc[indx].iaddcon++;
				j++;
				sexit.datasplitfunc[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p3) + 1);
				strcpy(sexit.datasplitfunc[indx].addCondition[j], p3);
				sexit.datasplitfunc[indx].iaddcon++;
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
		indx = sexit.idatamerge;
		sexit.idatamerge++;
		sexit.datamerge[indx].iaddexit = 0;
		sexit.datamerge[indx].iaddcon = 0;
		sexit.datamerge[indx].sName = (char *) calloc(1, (int) strlen(name) + 1);
		strcpy(sexit.datamerge[indx].sName, name);
	}
	if ((p = strstr(buf, CSETTAB))) {
		while (*p != '{' && *p != 0) p++;
		p++;
		p1 = p;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit.datamerge[indx].setTabnum = (char *)calloc(1, strlen(p1) + 1);
		strcpy(sexit.datamerge[indx].setTabnum, p1);
	}
	if ((p = strstr(buf, CSETMERGEELEMENTS))) {
		p1 = p + (int) strlen(CSETMERGEELEMENTS);
		while (*p1 != '{' && *p1 != 0) p1++;
		p1++;
		p = p1;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit.datamerge[indx].setMergeElements = (char *) calloc(1, (int) strlen(p1) + 1);
		strcpy(sexit.datamerge[indx].setMergeElements, p1);
	}
	p = strstr(buf, CADDEXIT);
	if (!p) p = strstr(buf, CADDEXITS);
	if (p) {
		char a[3][100];
		char *pp;
		splitEvent(a);
		pp = a[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit.datamerge[indx].iaddexit;
		sexit.datamerge[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0]) + 1);
		strcpy(sexit.datamerge[indx].saddExit[j].fieldName, a[0]);
		sexit.datamerge[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit.datamerge[indx].saddExit[j].clearFunc, a[1]);
		sexit.datamerge[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit.datamerge[indx].saddExit[j].eventName, a[2]);
		sexit.datamerge[indx].iaddexit++;
	}
	datamergeCondition(indx);
	return indx;
}

void datamergeCondition(int indx)
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
		p1 = p + (int) strlen(CADDCONDITION) + 1;
		while (*p1 != ' ') p1++;
		if (*p1 == ' ') p1++;
		p = p1;
		while (*p != '(') p++;
		*p = 0;
		p++;
		// p1 de condition var
		p3 = p;

		while (*p != ')') p++;
		*p = 0;
		for (indx = 0; indx<sexit.idatamerge; indx++) {
			if (strcmp(sexit.datamerge[indx].sName, p2) == 0) {

				j = sexit.datamerge[indx].iaddcon;
				sexit.datamerge[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p1) + 1);
				strcpy(sexit.datamerge[indx].addCondition[j], p1);
				sexit.datamerge[indx].iaddcon++;
				j++;
				sexit.datamerge[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p2) + 1);
				strcpy(sexit.datamerge[indx].addCondition[j], p2);
				sexit.datamerge[indx].iaddcon++;
				j++;
				sexit.datamerge[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p3) + 1);
				strcpy(sexit.datamerge[indx].addCondition[j], p3);
				sexit.datamerge[indx].iaddcon++;
			}
		}
	}
}
void enableCondition(int);
void disableCondition(int);
void visibleCondition(int);
void lstsearchCondition(int);
void mysignalCondition(int);

int enable(int current, char *name)
{
	int indx, j;
	char *p, *p1;
	if (!strstr(name, CENABLE)) return EOF;
	indx = adVarmi(current, name);
	if (indx == EOF) {
		indx = sexit.ienable;
		sexit.ienable++;
		sexit.senable[indx].iaddexit = 0;
		sexit.senable[indx].iaddcon = 0;
		sexit.senable[indx].sName = (char *) calloc(1, (int) strlen(name) + 1);
		strcpy(sexit.senable[indx].sName, name);
	}
	if ((p = strstr(buf, CSETTABS))) {
		while (*p != '{' && *p != 0) p++;
		p++;
		p1 = p;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		// mysplit(sexit.senable[indx].setTabnums, p1, ',');
		sexit.senable[indx].setTabnums = (char *)calloc(1, strlen(p1) + 1);
		strcpy(sexit.senable[indx].setTabnums, p1);
		//sexit.senable[indx].setTabnum = atoi(p1);
	}
	p = strstr(buf, CADDEXIT);
	if (!p) p = strstr(buf, CADDEXITS);
	if (p) {
		char a[3][100];
		char *pp;
		splitEvent(a);
		pp = a[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit.senable[indx].iaddexit;
		sexit.senable[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0]) + 1);
		strcpy(sexit.senable[indx].saddExit[j].fieldName, a[0]);
		sexit.senable[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit.senable[indx].saddExit[j].clearFunc, a[1]);
		sexit.senable[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit.senable[indx].saddExit[j].eventName, a[2]);
		sexit.senable[indx].iaddexit++;
	}
	enableCondition(indx);
	return indx;
}

void enableCondition(int indx)
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
		p1 = p + (int) strlen(CADDCONDITION) + 1;
		while (*p1 != ' ') p1++;
		if (*p1 == ' ') p1++;
		p = p1;
		while (*p != '(') p++;
		*p = 0;
		p++;
		// p1 de condition var
		p3 = p;
		while (*p != ')') p++;
		*p = 0;
		for (indx = 0; indx<sexit.ienable; indx++) {
			if (strcmp(sexit.senable[indx].sName, p2) == 0) {
				j = sexit.senable[indx].iaddcon;
				sexit.senable[indx].addCondition[j] =
					(char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(sexit.senable[indx].addCondition[j], p1);
				sexit.senable[indx].iaddcon++;
				j++;
				sexit.senable[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p2) + 1);
				strcpy(sexit.senable[indx].addCondition[j], p2);
				sexit.senable[indx].iaddcon++;
				j++;
				sexit.senable[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p3) + 1);
				strcpy(sexit.senable[indx].addCondition[j], p3);
				sexit.senable[indx].iaddcon++;
			}
		}
	}
}

int disable(int current, char *name)
{
	int indx, j;
	char *p, *p1;
	if (!strstr(name, CDISABLE)) return EOF;
	indx = adVarmi(current, name);
	if (indx == EOF) {
		indx = sexit.idisable;
		sexit.idisable++;
		sexit.sdisable[indx].iaddexit = 0;
		sexit.sdisable[indx].iaddcon = 0;
		sexit.sdisable[indx].sName = (char *) calloc(1, (int) strlen(name) + 1);
		strcpy(sexit.sdisable[indx].sName, name);
	}
	if ((p = strstr(buf, CSETTABD))) {
		while (*p != '{' && *p != 0) p++;
		p++;
		p1 = p;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit.sdisable[indx].setTabnum = (char *)calloc(1, strlen(p1) + 1);
		strcpy(sexit.sdisable[indx].setTabnum, p1);
	}
	p = strstr(buf, CADDEXIT);
	if (!p) p = strstr(buf, CADDEXITS);
	if (p) {
		char a[3][100];
		char *pp;
		splitEvent(a);
		pp = a[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit.sdisable[indx].iaddexit;
		sexit.sdisable[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0]) + 1);
		strcpy(sexit.sdisable[indx].saddExit[j].fieldName, a[0]);
		sexit.sdisable[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit.sdisable[indx].saddExit[j].clearFunc, a[1]);
		sexit.sdisable[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit.sdisable[indx].saddExit[j].eventName, a[2]);
		sexit.sdisable[indx].iaddexit++;
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
		p1 = p + (int) strlen(CADDCONDITION) + 1;

		while (*p1 != ' ') p1++;
		if (*p1 == ' ') p1++;
		p = p1;
		while (*p != '(') p++;
		*p = 0;
		p++;
		// p1 de condition var
		p3 = p;

		while (*p != ')') p++;
		*p = 0;
		for (indx = 0; indx<sexit.idisable; indx++) {
			if (strcmp(sexit.sdisable[indx].sName, p2) == 0) {
				j = sexit.sdisable[indx].iaddcon;
				sexit.sdisable[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p1) + 1);
				strcpy(sexit.sdisable[indx].addCondition[j], p1);
				sexit.sdisable[indx].iaddcon++;
				j++;
				sexit.sdisable[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p2) + 1);
				strcpy(sexit.sdisable[indx].addCondition[j], p2);
				sexit.sdisable[indx].iaddcon++;
				j++;
				sexit.sdisable[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p3) + 1);
				strcpy(sexit.sdisable[indx].addCondition[j], p3);
				sexit.sdisable[indx].iaddcon++;
			}
		}
	}
}

int visible(int current, char *name)
{
	int indx, j;
	char *p, *p1;
	if (!strstr(name, CVISIBLE)) return EOF;
	indx = adVarmi(current, name);
	if (indx == EOF) {
		indx = sexit.ivisible;
		sexit.ivisible++;
		sexit.svisible[indx].iaddexit = 0;
		sexit.svisible[indx].iaddcon = 0;
		sexit.svisible[indx].sName = (char *) calloc(1, (int) strlen(name) + 1);
		strcpy(sexit.svisible[indx].sName, name);
	}
	if ((p = strstr(buf, CSETTAB))) {
		while (*p != '{' && *p != 0) p++;
		p++;
		p1 = p;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit.svisible[indx].setTabnum = (char *)calloc(1, strlen(p1) + 1);
		strcpy(sexit.svisible[indx].setTabnum, p1);
	}
	p = strstr(buf, CADDEXIT);
	if (!p) p = strstr(buf, CADDEXITS);
	if (p) {
		char a[3][100];
		char *pp;
		splitEvent(a);
		pp = a[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit.svisible[indx].iaddexit;
		sexit.svisible[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0]) + 1);
		strcpy(sexit.svisible[indx].saddExit[j].fieldName, a[0]);
		sexit.svisible[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit.svisible[indx].saddExit[j].clearFunc, a[1]);
		sexit.svisible[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit.svisible[indx].saddExit[j].eventName, a[2]);
		sexit.svisible[indx].iaddexit++;
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
		p1 = p + (int) strlen(CADDCONDITION) + 1;

		while (*p1 != ' ') p1++;
		if (*p1 == ' ') p1++;
		p = p1;
		while (*p != '(') p++;
		*p = 0;
		p++;
		// p1 de condition var
		p3 = p;

		while (*p != ')') p++;
		*p = 0;
		for (indx = 0; indx<sexit.ivisible; indx++) {
			if (strcmp(sexit.svisible[indx].sName, p2) == 0) {
				j = sexit.svisible[indx].iaddcon;
				sexit.svisible[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p1) + 1);
				strcpy(sexit.svisible[indx].addCondition[j], p1);
				sexit.svisible[indx].iaddcon++;
				j++;
				sexit.svisible[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p2) + 1);
				strcpy(sexit.svisible[indx].addCondition[j], p2);
				sexit.svisible[indx].iaddcon++;
				j++;
				sexit.svisible[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p3) + 1);
				strcpy(sexit.svisible[indx].addCondition[j], p3);
				sexit.svisible[indx].iaddcon++;
			}
		}
	}
}

int lstSearch(int current, char *name)
{
	int indx, j;
	char *p, *p1;
	if (!strstr(name, CLSTSEARCH)) return EOF;
	indx = adVarmi(current, name);
	if (indx == EOF) {
		indx = sexit.ilstsearch;
		sexit.ilstsearch++;
		sexit.slstsearch[indx].iaddexit = 0;
		sexit.slstsearch[indx].iaddcon = 0;
		sexit.slstsearch[indx].sName = (char *) calloc(1, (int) strlen(name) + 1);
		strcpy(sexit.slstsearch[indx].sName, name);
	}
	if ((p = strstr(buf, CSETTAB))) {
		while (*p != '{' && *p != 0) p++;
		p++;
		p1 = p;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit.slstsearch[indx].setTabnum = (char *)calloc(1, strlen(p1) + 1);
		strcpy(sexit.slstsearch[indx].setTabnum, p1);
	}
	p = strstr(buf, CADDEXIT);
	if (!p) p = strstr(buf, CADDEXITS);
	if (p) {
		char a[3][100];
		char *pp;
		splitEvent(a);
		pp = a[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit.slstsearch[indx].iaddexit;
		sexit.slstsearch[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0]) + 1);
		strcpy(sexit.slstsearch[indx].saddExit[j].fieldName, a[0]);
		sexit.slstsearch[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit.slstsearch[indx].saddExit[j].clearFunc, a[1]);
		sexit.slstsearch[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit.slstsearch[indx].saddExit[j].eventName, a[2]);
		sexit.slstsearch[indx].iaddexit++;
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
		p1 = p + (int) strlen(CADDCONDITION) + 1;
		while (*p1 != ' ') p1++;
		if (*p1 == ' ') p1++;
		p = p1;
		while (*p != '(') p++;
		*p = 0;
		p++;
		// p1 de condition var
		p3 = p;

		while (*p != ')') p++;
		*p = 0;
		for (indx = 0; indx<sexit.ilstsearch; indx++) {
			if (strcmp(sexit.slstsearch[indx].sName, p2) == 0) {
				j = sexit.slstsearch[indx].iaddcon;
				sexit.slstsearch[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p1) + 1);
				strcpy(sexit.slstsearch[indx].addCondition[j], p1);
				sexit.slstsearch[indx].iaddcon++;
				j++;
				sexit.slstsearch[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p2) + 1);
				strcpy(sexit.slstsearch[indx].addCondition[j], p2);
				sexit.slstsearch[indx].iaddcon++;
				j++;
				sexit.slstsearch[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p3) + 1);
				strcpy(sexit.slstsearch[indx].addCondition[j], p3);
				sexit.slstsearch[indx].iaddcon++;
			}
		}
	}
}

int mysignal(int current, char *name)
{
	int indx, j;
	char *p, *p1;
	if (!strstr(name, CSIGNAL)) return EOF;
	indx = adVarmi(current, name);
	if (indx == EOF) {
		indx = sexit.isignal;
		sexit.isignal++;
		sexit.signal[indx].iaddexit = 0;
		sexit.signal[indx].iaddcon = 0;
		sexit.signal[indx].sName = (char *) calloc(1, (int) strlen(name) + 1);
		strcpy(sexit.signal[indx].sName, name);
	}
	if ((p = strstr(buf, CSETTAB))) {
		while (*p != '{' && *p != 0) p++;
		p++;
		p1 = p;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit.signal[indx].setTabnum = (char *)calloc(1, strlen(p1) + 1);
		strcpy(sexit.signal[indx].setTabnum, p1);
	}
	p = strstr(buf, CADDEXIT);
	if (!p) p = strstr(buf, CADDEXITS);
	if (p) {
		char a[3][100];
		char *pp;
		splitEvent(a);
		pp = a[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit.signal[indx].iaddexit;
		sexit.signal[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0]) + 1);
		strcpy(sexit.signal[indx].saddExit[j].fieldName, a[0]);
		sexit.signal[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit.signal[indx].saddExit[j].clearFunc, a[1]);
		sexit.signal[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit.signal[indx].saddExit[j].eventName, a[2]);
		sexit.signal[indx].iaddexit++;
	}
	mysignalCondition(indx);
	return indx;
}

void mysignalCondition(int indx)
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
		p1 = p + (int) strlen(CADDCONDITION) + 1;
		p = p1;
		while (*p != '(') p++;
		p++;
		p3 = p;
		while (*p != ')') p++;
		*p = 0;
		for (indx = 0; indx<sexit.isignal; indx++) {
			if (strcmp(sexit.signal[indx].sName, p2) == 0) {				
				j = sexit.signal[indx].iaddcon;
				sexit.signal[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p1) + 1);
				strcpy(sexit.signal[indx].addCondition[j], p1);
				sexit.signal[indx].iaddcon++;
				j++;
				sexit.signal[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p2) + 1);
				strcpy(sexit.signal[indx].addCondition[j], p2);
				sexit.signal[indx].iaddcon++;
				j++;
				sexit.signal[indx].addCondition[j] =
					(char *)calloc(1, (int)strlen(p3) + 1);
				strcpy(sexit.signal[indx].addCondition[j], p3);
				sexit.signal[indx].iaddcon++;
			}
		}
	}
}

int addExit(int current, char *name)
{
	int indx, j;
	char *pp;
	char a[3][100];
	if (!strstr(name, CADDEXIT) && !strstr(name, CADDEXITS)) return EOF;
	indx = adVarmi(current, name);
	splitEvent(a);
	pp = a[0];
	while (*pp != 0 && *pp != '(') pp++;
	*pp = 0;
	switch (current) {
	case PDATASPLIT:
		j = sexit.datasplitfunc[indx].iaddexit;
		sexit.datasplitfunc[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0]) + 1);
		strcpy(sexit.datasplitfunc[indx].saddExit[j].fieldName, a[0]);
		sexit.datasplitfunc[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit.datasplitfunc[indx].saddExit[j].clearFunc, a[1]);
		sexit.datasplitfunc[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit.datasplitfunc[indx].saddExit[j].eventName, a[2]);
		sexit.datasplitfunc[indx].iaddexit++;
		break;
	case PDATAMERGE:
		j = sexit.datamerge[indx].iaddexit;
		sexit.datamerge[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0]) + 1);
		strcpy(sexit.datamerge[indx].saddExit[j].fieldName, a[0]);
		sexit.datamerge[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit.datamerge[indx].saddExit[j].clearFunc, a[1]);
		sexit.datamerge[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit.datamerge[indx].saddExit[j].eventName, a[2]);
		sexit.datamerge[indx].iaddexit++;
		break;
	case PSETVALUE:
		j = sexit.svalue[indx].iaddexit;
		sexit.svalue[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0]) + 1);
		strcpy(sexit.svalue[indx].saddExit[j].fieldName, a[0]);
		sexit.svalue[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit.svalue[indx].saddExit[j].clearFunc, a[1]);
		sexit.svalue[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit.svalue[indx].saddExit[j].eventName, a[2]);
		sexit.svalue[indx].iaddexit++;
		break;
	case PSETCLEAR:
		j = sexit.setmanda[indx].iaddexit;
		sexit.setmanda[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0]) + 1);
		strcpy(sexit.setmanda[indx].saddExit[j].fieldName, a[0]);
		sexit.setmanda[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit.setmanda[indx].saddExit[j].clearFunc, a[1]);
		sexit.setmanda[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit.setmanda[indx].saddExit[j].eventName, a[2]);
		sexit.setmanda[indx].iaddexit++;
		break;
	case PCLEAR:
		j = sexit.scmanda[indx].iaddexit;
		sexit.scmanda[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0]) + 1);
		strcpy(sexit.scmanda[indx].saddExit[j].fieldName, a[0]);
		sexit.scmanda[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit.scmanda[indx].saddExit[j].clearFunc, a[1]);
		sexit.scmanda[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit.scmanda[indx].saddExit[j].eventName, a[2]);
		sexit.scmanda[indx].iaddexit++;
		break;
	case PINVISIBLE:
		j = sexit.sinvisible[indx].iaddexit;
		sexit.sinvisible[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0]) + 1);
		strcpy(sexit.sinvisible[indx].saddExit[j].fieldName, a[0]);
		sexit.sinvisible[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit.sinvisible[indx].saddExit[j].clearFunc, a[1]);
		sexit.sinvisible[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit.sinvisible[indx].saddExit[j].eventName, a[2]);
		sexit.sinvisible[indx].iaddexit++;
		break;
	case PSHOWMSG:
		j = sexit.showMsg[indx].iaddexit;
		sexit.showMsg[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0] + 1));
		strcpy(sexit.showMsg[indx].saddExit[j].fieldName, a[0]);
		sexit.showMsg[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit.showMsg[indx].saddExit[j].clearFunc, a[1]);
		sexit.showMsg[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit.showMsg[indx].saddExit[j].eventName, a[2]);
		sexit.showMsg[indx].iaddexit++;
		break;
	case PQUERYLSTFUNC:
		j = sexit.squeryList[indx].iaddexit;
		sexit.squeryList[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0]) + 1);
		strcpy(sexit.squeryList[indx].saddExit[j].fieldName, a[0]);
		sexit.squeryList[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit.squeryList[indx].saddExit[j].clearFunc, a[1]);
		sexit.squeryList[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit.squeryList[indx].saddExit[j].eventName, a[2]);
		sexit.squeryList[indx].iaddexit++;
		break;
	case PENABLE:
		j = sexit.senable[indx].iaddexit;
		sexit.senable[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0]) + 1);
		strcpy(sexit.senable[indx].saddExit[j].fieldName, a[0]);
		sexit.senable[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit.senable[indx].saddExit[j].clearFunc, a[1]);
		sexit.senable[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit.senable[indx].saddExit[j].eventName, a[2]);
		sexit.senable[indx].iaddexit++;
		break;
	case PDISABLE:
		j = sexit.sdisable[indx].iaddexit;
		sexit.sdisable[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0]) + 1);
		strcpy(sexit.sdisable[indx].saddExit[j].fieldName, a[0]);
		sexit.senable[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit.sdisable[indx].saddExit[j].clearFunc, a[1]);
		sexit.sdisable[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit.sdisable[indx].saddExit[j].eventName, a[2]);
		sexit.sdisable[indx].iaddexit++;
		break;
	case PVISIBLE:
		j = sexit.svisible[indx].iaddexit;
		sexit.svisible[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0]) + 1);
		strcpy(sexit.svisible[indx].saddExit[j].fieldName, a[0]);
		sexit.svisible[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit.svisible[indx].saddExit[j].clearFunc, a[1]);
		sexit.svisible[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit.svisible[indx].saddExit[j].eventName, a[2]);
		sexit.svisible[indx].iaddexit++;
		break;
	case PLSTSEARCH:
		j = sexit.slstsearch[indx].iaddexit;
		sexit.slstsearch[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0]) + 1);
		strcpy(sexit.slstsearch[indx].saddExit[j].fieldName, a[0]);
		sexit.slstsearch[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit.slstsearch[indx].saddExit[j].clearFunc, a[1]);
		sexit.slstsearch[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit.slstsearch[indx].saddExit[j].eventName, a[2]);
		sexit.slstsearch[indx].iaddexit++;
		break;
	case PSIGNAL:
		j = sexit.signal[indx].iaddexit;
		sexit.signal[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0]) + 1);
		strcpy(sexit.signal[indx].saddExit[j].fieldName, a[0]);
		sexit.signal[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit.signal[indx].saddExit[j].clearFunc, a[1]);
		sexit.signal[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit.signal[indx].saddExit[j].eventName, a[2]);
		sexit.signal[indx].iaddexit++;
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
		indx = sexit.iqueryList;
		sexit.iqueryList++;
		sexit.squeryList[indx].iaddexit = 0;
		sexit.squeryList[indx].sName = (char *) calloc(1, (int) strlen(name) + 1);
		strcpy(sexit.squeryList[indx].sName, name);
	}
	if ((p = strstr(buf, CSETTAB))) {
		p1 = strstr(buf, CSETTAB);
		p = p1 + (int) strlen(CSETTAB);
		p1 = p;
		while (*p != ')' && *p != 0) p++;
		*p = 0;
		sexit.squeryList[indx].setTabnum = (char *)calloc(1, strlen(p1) + 1);
		strcpy(sexit.squeryList[indx].setTabnum, p1);
	}
	p = strstr(buf, CADDEXIT);
	if (!p) p = p = strstr(buf, CADDEXITS);
	if (p) {
		splitEvent(a);
		pp = a[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit.squeryList[indx].iaddexit;
		sexit.squeryList[indx].saddExit[j].fieldName =
			(char *) calloc(1, (int) strlen(a[0]) + 1);
		strcpy(sexit.squeryList[indx].saddExit[j].fieldName, a[0]);
		sexit.squeryList[indx].saddExit[j].clearFunc =
			(char *) calloc(1, (int) strlen(a[1]) + 1);
		strcpy(sexit.squeryList[indx].saddExit[j].clearFunc, a[1]);
		sexit.squeryList[indx].saddExit[j].eventName =
			(char *) calloc(1, (int) strlen(a[2]) + 1);
		strcpy(sexit.squeryList[indx].saddExit[j].eventName, a[2]);
		sexit.squeryList[indx].iaddexit++;
	}
	if ((p = strstr(buf, CSETQUERYLST))) {
		p1 = strstr(buf, CSETQUERYLST);
		p = p1 + (int) strlen(CSETQUERYLST) + 1;
		p1 = p;
		if (p) {
			p = strstr((char*)p, "\")");
			if (p) {
				p += 2;
				if(p) *p = NULL;
			}
		}
		// sexit.squeryList[indx].sName = (char *) calloc(1, (int) strlen(name)+1);
		// strcpy(sexit.squeryList[indx].sName, name);
		if (p1) {
			sexit.squeryList[indx].sQuerylist = (char *) calloc(1, (int) strlen(p1) + 1);
			strcpy(sexit.squeryList[indx].sQuerylist, p1);
		}
	}
	return indx;
}

int exitMi()
{
	int ret = EOF;

	if ((fexit == 0) &&
		(strstr(buf, CEXIT) || (strstr(buf, cexit) && !strstr(buf, "import")))) {
		int current = EOF;
		char *p, *p1;
		char name[200];
		fexit = 1;
		Processed = 1;

		// CENDINIT "}"
		while (1) {
			ret = mygetline(CENDINIT);
			if (ret != EOF) { Processed = 1; break; }
			if (strstr(buf, CENDINIT) && !strstr(buf, CBEGIN)) {
				Processed = 1;
				break;
			}
			Processed = 1;
			if (strstr(buf, cexit) || strstr(buf, "new ") || (current != EOF)) {
				if ((strstr(buf, cexit) || strstr(buf, "new ")) && 
					!(strstr(buf, CCONDITION) || strstr(buf, CSETTABNUM) || strstr(buf, CSETTAB) ||
					  strstr(buf, CSETTABD) || strstr(buf, CSETTABS) || strstr(buf, CADDEXIT) ||
					  strstr(buf, CADDEXITS))) {
					p = strstr(buf, cexit);
					if (!p) {
						p1 = strstr(buf, "     ");
						if(p1) p1 = p1 + 5;
						else p1 = buf;
						p1 = strstr(p1, " ");
					}
					else {
						p1 = strstr(p, " ");
					}
					if (p1) {
						p1++;
						p = strstr(p1, " ");
						*p = 0;
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
				if (getinsym(CADDEXIT) == PADDEXIT || getinsym(CADDEXITS) == PADDEXIT) {
					current = PADDEXIT;
					if (addExit(current, name) != EOF) continue;
				}
				if (getinsym(CQUERYLSTFUNC) == PQUERYLSTFUNC) {
					current = PQUERYLSTFUNC;
					if (queryList(current, name) != EOF) continue;
				}
				if (getinsym(CLSTSEARCH) == PLSTSEARCH) {
					current = PLSTSEARCH;
					if (lstSearch(current, name) != EOF) continue;
				}
				if (getinsym(CENABLE) == PENABLE) {
					current = PENABLE;
					if (enable(current, name) != EOF) continue;
				}
				if (getinsym(CDISABLE) == PDISABLE) {
					current = PDISABLE;
					if (disable(current, name) != EOF) continue;
				}
				if (getinsym(CVISIBLE) == PVISIBLE) {
					current = PVISIBLE;
					if (visible(current, name) != EOF) continue;
				}
				if (getinsym(CSIGNAL) == PSIGNAL) {
					current = PSIGNAL;
					if (mysignal(current, name) != EOF) continue;
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

#define panelTITLE "setTitle("

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
		indx = ispanel;
		spanel[indx].panNo = getPanelno(xname);
		ispanel++;
		spanel[indx].panelName = (char *) calloc(1, (int) strlen(xname) + 1);
		strcpy(spanel[indx].panelName, xname);
		spanel[indx].ifield = 0;
		while (1) {
			ret = mygetline(CENDINIT2);
			if (ret != EOF) { Processed = 1; break; }
			if (strstr(buf, CENDINIT) && !strstr(buf, CBEGIN)) {
				Processed = 1;
				break;
			}
			Processed = 1;
			if (strstr(buf, CPNLBOUNDS)) {
				// bounds
				boundVals(&spanel[indx].spnlbound, CPNLBOUNDS);
				continue;
			}
			if (strstr(buf, CPNLADD)) {
				int ff;
				p1 = strstr(buf, CPNLADD);
				p = p1 + (int) strlen(CPNLADD);
				p1 = p;
				while (*p != 0 && *p != '(') p++;
				*p = 0;
				ff = fieldtype(p1);
				j = spanel[indx].ifield;
				spanel[indx].fields[j].fieldname = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(spanel[indx].fields[j].fieldname, p1);
				spanel[indx].fields[j].ftype = ff;
				spanel[indx].ifield++;
				continue;
			}
			if (strstr(buf, panelTITLE)) {
				p1 = strstr(buf, panelTITLE);
				p = p1 + (int) strlen(panelTITLE) + 1;
				p1 = p;
				while (*p != 0 && *p != '"') p++;
				*p = 0;
				spanel[indx].setTitle = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(spanel[indx].setTitle, p1);
				continue;
			}
		}
		fpanel = 0;
	}
	return ret;
}

#define CLBLFUNC "AkbankLabel get"
#define CTXTFUNC "AkbankTextField get"
#define CRBUTTON "AkbankRadioButton get"
#define CGETBUTTON "AkbankButton get"
#define COMBOBOX  "AkbankComboBox get"
#define CHECKBOX  "AkbankCheckBox get"
#define SCROLL    "AkbankTableScrollPane get"

#define TSCROLL  "setViewportView(get"

#define CSETTABORDER "setTabOrder("

/* label attributes */
#define LBLBOUND "setBounds("
#define LBLNAME "setName("
#define LBLTXT "setText("

/* text field attributes */
#define TXTBOUND "setBounds("
#define TXTENABLED "setEnabled("
#define TXTREQ "setRequired("
#define TXTDNAME "setDataName("
#define TXTNAME "setName("
#define TXTFONT "setFont("
#define TXTFRMT "setFormatter(new "
#define TXTCONVERTER "com.akbank.client.converters."
#define TXTNUMERIC "Numeric"
#define TXTDATE    "Date"

#define CHKBOUND "setBounds("
#define CHKFONT  "setFont("
#define CHKDNAME "setDataName("
#define CHKNAME "setName("
#define CHKTXT  "setText("
#define CHKSVAL  "setSelectedValue("
#define CHKUVAL  "setUnSelectedValue("
#define CHKSTAB  "setTabOrder("

/* radio button attributes */
#define RBUTBOUND "setBounds("
#define RBUTENABLED "setEnabled("
#define RBUTTAB "setTabOrder("
#define RBUTTXT "setText("
#define RBUTSVAL "setValue("
#define RBUTDISABLE "setDisableOnError("

/* button attributes */
#define BUTBOUND "setBounds("
#define BUTTXT "setText("
#define BUTTXTTYPE "setType("
#define BUTNAME "setName("
#define BUTLOCATE "setToBeLocatedAtFooter("
#define BUTTAB "setTabOrder("

/* combobox attributes */
#define COMBOBOUND "setBounds("
#define COMBOFLDNAME "setValueFieldName("
#define COMBOINCONTEXT "setValueInContext("
#define COMBOKEYVALS   "setUseKeyValues("
#define COMBOIDFLDNAME "setIdFieldName("
#define COMBOTABORDER  "setTabOrder("
#define COMBODATANAME  "setDataName("
#define COMBONAME  "setName("
#define COMBOFORLST "setDataNameForList("
#define COMBOSETREQ "setRequired("

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
	if (p) {
		p1 = p + (int)strlen(txt);
		p = strstr(p1, "(");
		if (p) {
			*p = 0;
			p = strstr(p1, " =");
			if (p)
				*p = 0;
		}
		strcpy(xname, p1);
	} else xname[0] = 0;
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

#define SETVALFNAME "setValueFieldName("
#define SETVALIN "setValueInContext("
#define SETKEYVAL "setUseKeyValues("
#define SETFNAME "setIdFieldName("
#define SETDNAMELST "setDataNameForList("

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
			while (*p != 0 && *p != '"') p++;
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
		while (*p != 0 && *p != '"') p++;
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
		while (*p != 0 && *p != '"') p++;
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
	char xname[200];

	if (buf[0] == '}') {
		Processed = 1;
		ret = mygetline(CDUMMY);
		return ret;
	}
	if ((flblfunc == 0) && strstr(buf, CLBLFUNC)) {
		flblfunc = 1;
		Processed = 1;
		getName(xname, CLBLFUNC);
		if (strlen(xname) < 1) return ret;
		indx = islabel;
		slabel[indx].lblno = getLabel(xname);
		slabel[indx].lbl = (char *) calloc(1, (int) strlen(xname) + 1);
		strcpy(slabel[indx].lbl, xname);
		slabel[indx].lbltext = 0;
		islabel++;
		while (1) {
			ret = mygetline(CENDINIT2);
			if (ret != EOF) { Processed = 1; break; }
			if (strstr(buf, CENDINIT) && !strstr(buf, CBEGIN)) {
				Processed = 1;
				break;
			}
			Processed = 1;
			if (strstr(buf, LBLBOUND)) {
				// bounds
				boundVals(&slabel[indx].slblbound, LBLBOUND);
				continue;
			}
			if (strstr(buf, LBLNAME)) {
				// LBLNAME setName found get name
				p1 = strstr(buf, LBLNAME) + (int) strlen(LBLNAME);
				p1++;
				p = p1;
				while (*p != 0 && *p != '"') p++;
				*p = 0;
				slabel[indx].name = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(slabel[indx].name, p1);
				continue;
			}
			if (strstr(buf, LBLTXT)) {
				// LBLTEXT setText found get text
				p1 = strstr(buf, LBLTXT) + (int) strlen(LBLTXT);
				p1++;
				p = p1;
				while (*p != 0 && *p != '"') p++;
				*p = 0;
				slabel[indx].text = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(slabel[indx].text, p1);
				continue;
			}
			if (strstr(buf, CSETTABORDER)) {
				p1 = strstr(buf, CSETTABORDER) + (int)strlen(CSETTABORDER);
				p1++;
				p = p1;
				while (*p != 0 && *p != '"') p++;
				*p = 0;
				slabel[indx].tabOrder = atoi(p1);
				continue;
			}
		}
		flblfunc = 0;
	}
	if ((ftxtfunc == 0) && strstr(buf, CTXTFUNC)) {
		ftxtfunc = 1;
		Processed = 1;
		getName(xname, CTXTFUNC);
		indx = istext;
		if (strlen(xname) < 1) return ret;
		stextfield[indx].txtno = getTextField(xname);
		stextfield[indx].text = (char *) calloc(1, (int) strlen(xname) + 1);
		strcpy(stextfield[indx].text, xname);
		istext++;
		while (1) {
			ret = mygetline(CENDINIT2);
			if (ret != EOF) { Processed = 1; break; }
			if (strstr(buf, CENDINIT) && !strstr(buf, CBEGIN)) {
				Processed = 1;
				break;
			}
			Processed = 1;
			if (strstr(buf, TXTBOUND)) {
				// bounds
				boundVals(&stextfield[indx].stxtbound, TXTBOUND);
				continue;
			}
			if (strstr(buf, TXTENABLED)) {
				// move enable value
				p1 = strstr(buf, TXTENABLED);
				p1 = p1 + (int) strlen(TXTENABLED);
				if (strncasecmp(p1, "false", 5) == 0)
					stextfield[indx].enabled = false;
				else
					stextfield[indx].enabled = true;
				continue;
			}
			if (strstr(buf, TXTREQ)) {
				p1 = strstr(buf, TXTREQ);
				p1 = p1 + (int) strlen(TXTREQ);
				if (strncasecmp(p1, "false", 5) == 0)
					stextfield[indx].required = false;
				else
					stextfield[indx].required = true;
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
				stextfield[indx].font = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(stextfield[indx].font, p1);
				continue;
			}
			if (strstr(buf, TXTDNAME)) {
				// move data Name value
				p1 = strstr(buf, TXTDNAME);
				p1 = p1 + (int) strlen(TXTDNAME);
				p1++;
				p = p1;
				while (*p != 0 && *p != '"') p++;
				*p = 0;
				stextfield[indx].dataName = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(stextfield[indx].dataName, p1);
				// label icin text sira no ekle
				if (islabel > 0) {
					if (slabel[islabel - 1].lbltext == 0) {
						slabel[islabel - 1].lbltext = (char *)calloc(1, (int)strlen(p1) + 1);
						strcpy(slabel[islabel - 1].lbltext, p1);
					}
				}
				else {
					slabel[0].lbltext = (char *)calloc(1, 1);
					slabel[0].lbltext[0] = 0;
				}
				continue;
			}
			if (strstr(buf, TXTNAME)) {
				// move Name value
				p1 = strstr(buf, TXTNAME);
				p1 = p1 + (int) strlen(TXTNAME);
				p1++;
				p = p1;
				while (*p != 0 && *p != '"') p++;
				*p = 0;
				stextfield[indx].name = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(stextfield[indx].name, p1);
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
					stextfield[indx].formatter = (char *) calloc(1, (int) strlen(p1) + 1);
					strcpy(stextfield[indx].formatter, p1);
				}
				else
					stextfield[indx].formatter = 0;
				continue;
			}
			if (strstr(buf, CSETTABORDER)) {
				p1 = strstr(buf, CSETTABORDER) + (int)strlen(CSETTABORDER);
				p1++;
				p = p1;
				while (*p != 0 && *p != '"') p++;
				*p = 0;
				stextfield[indx].tabOrder = atoi(p1);
				continue;
			}

		}
		ftxtfunc = 0;
	}
	if ((frbutton == 0) && strstr(buf, CRBUTTON)) {
		frbutton = 1;
		Processed = 1;
		getName(xname, CRBUTTON);
		if (strlen(xname) < 1) return ret;
		indx = irbutton;
		rbutton[indx].rbutno = getRbutton(xname);
		irbutton++;
		rbutton[indx].rbut = (char *) calloc(1, (int) strlen(xname) + 1);
		strcpy(rbutton[indx].rbut, xname);
		while (1) {
			ret = mygetline(CENDINIT2);
			if (ret != EOF) { Processed = 1; break; }
			if (strstr(buf, CENDINIT) && !strstr(buf, CBEGIN)) {
				Processed = 1;
				break;
			}
			Processed = 1;
			if (strstr(buf, RBUTBOUND)) {
				// bounds
				boundVals(&rbutton[indx].rbutBound, TXTBOUND);
				continue;
			}
			if (strstr(buf, RBUTENABLED)) {
				// rbutton enabled
				p1 = strstr(buf, RBUTENABLED) + (int) strlen(RBUTENABLED);
				if (strncasecmp(p1, "false", 5) == 0)
					rbutton[indx].rbutEnabled = false;
				else
					rbutton[indx].rbutEnabled = true;
				continue;
			}
			if (strstr(buf, RBUTDISABLE)) {
				// rbutton enabled
				p1 = strstr(buf, RBUTDISABLE) + (int) strlen(RBUTDISABLE);
				if (strncasecmp(p1, "false", 5) == 0)
					rbutton[indx].disable = false;
				else
					rbutton[indx].disable = true;
				continue;
			}
			if (strstr(buf, RBUTTAB)) {
				// rbutton tab Order
				p1 = strstr(buf, RBUTTAB) + (int) strlen(RBUTTAB);
				// p1++;
				p = p1;
				while (*p != 0 && *p != ')') p++;
				*p = 0;
				rbutton[indx].rbutTab = atoi(p1) / 10;
				continue;
			}
			if (strstr(buf, RBUTTXT)) {
				// rbutton text
				p1 = strstr(buf, RBUTTXT) + (int) strlen(RBUTTXT);
				p1++;
				p = p1;
				while (*p != 0 && *p != '"') p++;
				*p = 0;
				rbutton[indx].rbutText = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(rbutton[indx].rbutText, p1);
				continue;
			}
			if (strstr(buf, RBUTSVAL)) {
				// rbutton text
				p1 = strstr(buf, RBUTSVAL) + (int) strlen(RBUTSVAL);
				p1++;
				p = p1;
				while (*p != 0 && *p != '"') p++;
				*p = 0;
				rbutton[indx].rbutVal = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(rbutton[indx].rbutVal, p1);
				continue;
			}
		}
		frbutton = 0;
	}
	if ((fbutton == 0) && strstr(buf, CGETBUTTON)) {
		fbutton = 1;
		Processed = 1;
		getName(xname, CGETBUTTON);
		if (strlen(xname) < 1) return ret;
		indx = igetbutton;
		button[indx].butNo = getButton(xname);
		button[indx].but = (char *) calloc(1, (int) strlen(xname) + 1);
		strcpy(button[indx].but, xname);
		igetbutton++;
		while (1) {
			ret = mygetline(CENDINIT2);
			if (ret != EOF) { Processed = 1; break; }
			if (strstr(buf, CENDINIT) && !strstr(buf, CBEGIN)) {
				Processed = 1;
				break;
			}
			Processed = 1;
			if (strstr(buf, BUTBOUND)) {
				// bounds
				boundVals(&button[indx].butBound, TXTBOUND);
				continue;
			}
			if (strstr(buf, BUTTXT)) {
				// button text
				p1 = strstr(buf, BUTTXT) + (int) strlen(BUTTXT);
				p1++;
				p = p1;
				while (*p != 0 && *p != '"') p++;
				*p = 0;
				button[indx].butText = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(button[indx].butText, p1);
				continue;
			}
			if (strstr(buf, BUTNAME)) {
				// button text
				p1 = strstr(buf, BUTNAME) + (int) strlen(BUTNAME);
				p1++;
				p = p1;
				while (*p != 0 && *p != '"') p++;
				*p = 0;
				button[indx].butName = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(button[indx].butName, p1);
				continue;
			}
			if (strstr(buf, BUTLOCATE)) {
				// button locater
				p1 = strstr(buf, BUTLOCATE) + (int) strlen(BUTLOCATE);
				if (strncasecmp(p1, "false", 5) == 0)
					button[indx].butLocate = false;
				else
					button[indx].butLocate = true;
				continue;
			}
			if (strstr(buf, BUTTAB)) {
				// button tab order
				p1 = strstr(buf, BUTTAB) + (int) strlen(BUTTAB);
				p = p1;
				while (*p != 0 && *p != ')') p++;
				*p = 0;
				button[indx].butTabOrder = atoi(p1);
				continue;
			}
			if (strstr(buf, BUTTXTTYPE)) {
				p1 = strstr(buf, BUTTXTTYPE) + (int) strlen(BUTTXTTYPE);
				p1++;
				p = p1;
				while (*p != 0 && *p != '"') p++;
				*p = 0;
				button[indx].butTxttype = atoi(p1);
			}
		}
		fbutton = 0;
	}
	if ((fcombo == 0) && strstr(buf, CCOMBOBOX)) {
		fcombo = 1;
		Processed = 1;
		getName(xname, CCOMBOBOX);
		if (strlen(xname) < 1) return ret;
		indx = icombox;
		combox[indx].comboNo = getCombo(xname);
		combox[indx].fcomboxName = (char *) calloc(1, (int) strlen(xname) + 1);
		strcpy(combox[indx].fcomboxName, xname);
		icombox++;

		while (1) {
			ret = mygetline(CENDINIT2);
			if (ret != EOF) { Processed = 1; break; }
			if (strstr(buf, CENDINIT) && !strstr(buf, CBEGIN)) {
				Processed = 1;
				break;
			}
			Processed = 1;
			if (strstr(buf, BUTBOUND)) {
				boundVals(&combox[indx].comboBounds, TXTBOUND);
				continue;
			}
			if (strstr(buf, BUTTAB)) {
				// button tab order
				p1 = strstr(buf, BUTTAB) + (int) strlen(BUTTAB);
				p = p1;
				while (*p != 0 && *p != ')') p++;
				*p = 0;
				combox[indx].comboTabOrder = atoi(p1);
				continue;
			}
			if (strstr(buf, BUTNAME)) {
				// button text
				p1 = strstr(buf, BUTNAME) + (int) strlen(BUTNAME);
				p1++;
				p = p1;
				while (*p != 0 && *p != '"') p++;
				*p = 0;
				combox[indx].comboxName = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(combox[indx].comboxName, p1);
				continue;
			}
			if (strstr(buf, TXTDNAME)) {
				p1 = strstr(buf, TXTDNAME);
				p1 = p1 + (int) strlen(TXTDNAME);
				p1++;
				p = p1;
				while (*p != 0 && *p != '"') p++;
				*p = 0;
				combox[indx].dataName = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(combox[indx].dataName, p1);
				continue;
			}
			if (strstr(buf, SETVALFNAME)) {
				p1 = strstr(buf, SETVALFNAME);
				p1 = p1 + (int) strlen(SETVALFNAME) + 1;
				p = p1;
				while (*p != 0 && *p != '"') p++;
				*p = 0;
				combox[indx].setvalfname = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(combox[indx].setvalfname, p1);
				continue;
			}
			if (strstr(buf, SETVALIN)) {
				p1 = strstr(buf, SETVALIN);
				p1 = p1 + (int) strlen(SETVALIN) + 1;
				p = p1;
				while (*p != 0 && *p != '"') p++;
				*p = 0;
				combox[indx].setvalin = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(combox[indx].setvalin, p1);
				continue;
			}
			if (strstr(buf, SETFNAME)) {
				p1 = strstr(buf, SETFNAME);
				p1 = p1 + (int) strlen(SETFNAME) + 1;
				p = p1;
				while (*p != 0 && *p != '"') p++;
				*p = 0;
				combox[indx].setfname = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(combox[indx].setfname, p1);
				continue;
			}
			if (strstr(buf, SETDNAMELST)) {
				p1 = strstr(buf, SETDNAMELST);
				p1 = p1 + (int) strlen(SETDNAMELST) + 1;
				p = p1;
				while (*p != 0 && *p != '"') p++;
				*p = 0;
				combox[indx].setdnamelst = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(combox[indx].setdnamelst, p1);
				continue;
			}
			if (strstr(buf, SETKEYVAL)) {
				p1 = strstr(buf, SETKEYVAL);
				p1 = p1 + (int) strlen(SETKEYVAL);
				if (strncasecmp(p1, "false", 5) == 0)
					combox[indx].setkeyvals = 0;
				else
					combox[indx].setkeyvals = 1;
				continue;
			}
			if (strstr(buf, COMBOSETREQ)) {
				p1 = strstr(buf, COMBOSETREQ);
				p1 = p1 + (int)strlen(COMBOSETREQ);
				if (strncasecmp(p1, "false", 5) == 0)
					combox[indx].setreq = 0;
				else
					combox[indx].setreq = 1;
				continue;
			}
		}
		fcombo = 0;
	}
	if ((fchkbox == 0) && strstr(buf, CCHECKBOX)) {
		fchkbox = 1;
		Processed = 1;
		getName(xname, CCHECKBOX);
		if (strlen(xname) < 1) return ret;
		indx = ichkno;
		checkBox[indx].checkNo = getCheck(xname);
		checkBox[indx].setName = (char *) calloc(1, (int) strlen(xname) + 1);
		strcpy(checkBox[indx].setName, xname);
		ichkno++;

		while (1) {
			ret = mygetline(CENDINIT2);
			if (ret != EOF) { Processed = 1; break; }
			if (strstr(buf, CENDINIT) && !strstr(buf, CBEGIN)) {
				Processed = 1;
				break;
			}
			Processed = 1;
			if (strstr(buf, CHKBOUND)) {
				boundVals(&checkBox[indx].checkBounds, CHKBOUND);
				continue;
			}
			if (strstr(buf, CHKSTAB)) {
				// check tab order
				p1 = strstr(buf, CHKSTAB) + (int) strlen(CHKSTAB);
				p = p1;
				while (*p != 0 && *p != ')') p++;
				*p = 0;
				checkBox[indx].checkTabOrder = atoi(p1);
				continue;
			}
			if (strstr(buf, CHKNAME)) {
				// check text
				p1 = strstr(buf, CHKNAME) + (int) strlen(CHKNAME);
				p1++;
				p = p1;
				while (*p != 0 && *p != '"') p++;
				*p = 0;
				checkBox[indx].setName = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(checkBox[indx].setName, p1);
				if (slabel[islabel - 1].lbltext == 0) {
					slabel[islabel - 1].lbltext = (char *) calloc(1, (int) strlen(p1) + 1);
					strcpy(slabel[islabel - 1].lbltext, p1);
				}
				continue;
			}
			if (strstr(buf, CHKDNAME)) {
				p1 = strstr(buf, CHKDNAME);
				p1 = p1 + (int) strlen(CHKDNAME);
				p1++;
				p = p1;
				while (*p != 0 && *p != '"') p++;
				*p = 0;
				checkBox[indx].dataName = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(checkBox[indx].dataName, p1);
				continue;
			}
			if (strstr(buf, CHKSVAL)) {
				p1 = strstr(buf, CHKSVAL);
				p1 = p1 + (int) strlen(CHKSVAL) + 1;
				p = p1;
				while (*p != 0 && *p != '"') p++;
				*p = 0;
				checkBox[indx].setval = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(checkBox[indx].setval, p1);
				continue;
			}
			if (strstr(buf, CHKUVAL)) {
				p1 = strstr(buf, CHKUVAL);
				p1 = p1 + (int) strlen(CHKUVAL) + 1;
				p = p1;
				while (*p != 0 && *p != '"') p++;
				*p = 0;
				checkBox[indx].setuval = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(checkBox[indx].setuval, p1);
				continue;
			}
			if (strstr(buf, CHKFONT)) {
				p1 = strstr(buf, CHKFONT);
				p1 = p1 + (int) strlen(CHKFONT) + 1;
				p = p1;
				while (*p != 0 && *p != '"') p++;
				*p = 0;
				checkBox[indx].font = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(checkBox[indx].font, p1);
				continue;
			}
			if (strstr(buf, CHKTXT)) {
				p1 = strstr(buf, CHKTXT);
				p1 = p1 + (int) strlen(CHKTXT);
				if (strncasecmp(p1, "E", 1) == 0)
					checkBox[indx].text = "E";
				else
					checkBox[indx].text = "H";
				continue;
			}
		}
		fchkbox = 0;
	}
	if ((fbuttongrps == 0) && strstr(buf, CBUTTONGROUP)) {
		fbuttongrps = 1;
		Processed = 1;
		getName(xname, CBUTTONGROUP);
		if (strlen(xname) < 1) return ret;
		indx = isgroup;
		sgroup[indx].dataName = (char *)calloc(1, (int)strlen(xname) + 1);
		strcpy(sgroup[indx].dataName, xname);
		sgroup[indx].txtno = 0;
		sgroup[indx].txtlblno = 0;
		sgroup[indx].text = 0;
		isgroup++;
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
				sgroup[indx].dataName = (char *)calloc(1, (int)strlen(p1) + 1);
				strcpy(sgroup[indx].dataName, p1);
				continue;
			}
		}
		fbuttongrps = 0;
	}
	if ((fscroll == 0) && strstr(buf, CSCROLL)) {
		fscroll = 1;
		Processed = 1;
		getName(xname, CSCROLL);
		if (strlen(xname) < 1) return ret;
		indx = iscroll;
		scrollfield[indx].scrollno = getScroll(xname);
		scrollfield[indx].name = (char *) calloc(1, (int) strlen(xname) + 1);
		strcpy(scrollfield[indx].name, xname);
		iscroll++;
		while (1) {
			ret = mygetline(CENDINIT2);
			if (ret != EOF) { Processed = 1; break; }
			if (strstr(buf, CENDINIT) && !strstr(buf, CBEGIN)) {
				Processed = 1;
				break;
			}
			Processed = 1;
			if (strstr(buf, CHKBOUND)) {
				boundVals(&scrollfield[indx].scrollBounds, CHKBOUND);
				continue;
			}
			if (strstr(buf, TSCROLL)) {
				p1 = strstr(buf, TSCROLL);
				p1 = p1 + (int) strlen(TSCROLL) + 1;
				p = p1;
				while (*p != 0 && *p != '"') p++;
				*p = 0;
				scrollfield[indx].tablename = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(scrollfield[indx].tablename, p1);
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
		if (strlen(xname) < 1) return ret;
		indx = istable;
		stable[indx].tableno = getTable(xname);
		stable[indx].name = (char *) calloc(1, (int) strlen(xname) + 1);
		strcpy(stable[indx].name, xname);
		istable++;

		while (1) {
			ret = mygetline(CENDINIT2);
			if (ret != EOF) { Processed = 1; break; }
			if (strstr(buf, CENDINIT) && !strstr(buf, CBEGIN)) {
				Processed = 1;
				break;
			}
			Processed = 1;
			if (strstr(buf, CHKBOUND)) {
				boundVals(&stable[indx].tableBounds, CHKBOUND);
				continue;
			}
			if (strstr(buf, MCLICK)) {
				p1 = strstr(buf, MCLICK);
				p1 = p1 + (int) strlen(MCLICK) + 1;
				p = p1;
				while (*p != 0 && *p != ')') p++;
				*p = 0;
				if (strcmp(p1, "false") == 0)
					stable[indx].mclick = 0;
				else
					stable[indx].mclick = 1;
				continue;
			}
			if (strstr(buf, ADDCOLUMN)) {
				j = stable[indx].icols;
				if (ColumnVals(&stable[indx].cols[j], ADDCOLUMN, 0) != EOF)
					stable[indx].icols++;
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
		if (strlen(xname) < 1) return ret;
		indx = istable;
		stable[indx].tableno = getTable(xname);
		stable[indx].name = (char *) calloc(1, (int) strlen(xname) + 1);
		strcpy(stable[indx].name, xname);
		istable++;

		while (1) {
			ret = mygetline(CENDINIT2);
			if (ret != EOF) { Processed = 1; break; }
			if (strstr(buf, CENDINIT) && !strstr(buf, CBEGIN)) {
				Processed = 1;
				break;
			}
			Processed = 1;
			if (strstr(buf, CHKBOUND)) {
				boundVals(&stable[indx].tableBounds, CHKBOUND);
				continue;
			}
			if (strstr(buf, MCLICK)) {
				p1 = strstr(buf, MCLICK);
				p1 = p1 + (int) strlen(MCLICK) + 1;
				p = p1;
				while (*p != 0 && *p != ')') p++;
				*p = 0;
				if (strcmp(p1, "false") == 0)
					stable[indx].mclick = 0;
				else
					stable[indx].mclick = 1;
				continue;
			}
			if (strstr(buf, "setKeyDataName(")) {
				j = stable[indx].icols;
				ColkDataName(&stable[indx].cols[j].kdataname, "setKeyDataName(");
				continue;
			}
			if (strstr(buf, "setColumnWidth(")) {
				j = stable[indx].icols;
				ColWidth(&stable[indx].cols[j].colwidth, "setColumnWidth(");
				continue;
			}
			if (strstr(buf, "setTitle(")) {
				j = stable[indx].icols;
				ColTitle(&stable[indx].cols[j].title, "setTitle(");
				continue;
			}
			if (strstr(buf, "setEditable(")) {
				j = stable[indx].icols;
				ColEditVal(&stable[indx].cols[j].editval, "setEditable(");
				continue;
			}
			if (strstr(buf, ADDCOLUMN)) {
				j = stable[indx].icols;
				if (ColumnVals(&stable[indx].cols[j], ADDCOLUMN, 1) != EOF)
					stable[indx].icols++;
				continue;
			}
		}
		ftable = 0;
	}

	if ((floader == 0) && strstr(buf, CLOADER)) {
		floader = 1;
		getName(xname, CLOADER);
		if (strlen(xname) < 1) return ret;
		strcpy(loads[panelno][loadno], xname);

		loadno++;
		loads[panelno][loadno][0] = 0;

		indx = iloader;
		loader[indx].loadNo = loadno - 1;
		loader[indx].name = (char *) calloc(1, (int) strlen(xname) + 1);
		strcpy(loader[indx].name, xname);
		iloader++;
		while (1) {
			ret = mygetline(CENDINIT2);
			if (ret != EOF) { Processed = 1; break; }
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
				while (*p != 0 && *p != '"') p++;
				*p = 0;
				loader[indx].loadstr = (char *) calloc(1, (int) strlen(p1) + 1);
				strcpy(loader[indx].loadstr, p1);
			}
		}
		floader = 0;
	}
	if (buf[0] == '}') {
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

	while ((ret=mygetline(CCLIENT)) > 0) {
		// if(anyofThese()) return EOF;
		if (fclass == 0) {
			ret = detected(CCLASS);
			if (ret != EOF) {
				char *pt = strstr(symbol, " ");
				if (pt != NULL) {
					*pt = 0;
					strcpy(program, symbol);
					//myprologue(slayout.name, slayout.title);
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
				if ((ret = detected(CCHECKBOX)) != EOF) continue;
				if ((ret = detected(CQUERYLSTFUNC)) != EOF) continue;
				if ((ret = detected(CTABLE)) != EOF) continue;
				if ((ret = detected((char *)CTABLES)) != EOF) continue;
				Processed = 1;
			}
		}
	}
	return ret;
}

void mywriteLayout()
{
	int i;
	fprintf(output, "LAYOUT\n");
	fprintf(output, "\tName %s\n", slayout.name);
	fprintf(output, "\tTitle %s\n", slayout.title);
	// border-width: 2px 10px 4px 20px
	fprintf(output, "\tborder-width: %dpx %dpx %dpx %dpx;\n",
		slayout.bound.x0,
		slayout.bound.y0,
		slayout.bound.y1,
		slayout.bound.x1);
	for (i = 0; i< slayout.iadded; i++) {
		fprintf(output, "\tnpanel %d nbutton %d type %d added %s\n",
			slayout.added[i].npanel,
			slayout.added[i].nbutton,
			slayout.added[i].type,
			slayout.added[i].addb);
	}
}

void myExitWrite()
{
	int i, j;
	for (i = 0; i < sexit.iscmanda; i++) {
		fprintf(output, "clearManda Name %s setTabnum %s\n",
			sexit.scmanda[i].sName,
			sexit.scmanda[i].setTabnum);
		for (j = 0; j < sexit.scmanda[i].iaddexit; j++) {
			fprintf(output, "\tfieldName %s\n\tclearFunc %s\n\teventName %s\n",
				sexit.scmanda[i].saddExit[j].fieldName,
				sexit.scmanda[i].saddExit[j].clearFunc,
				sexit.scmanda[i].saddExit[j].eventName);
		}
		for (j = 0; j < sexit.scmanda[i].iaddcon; j++) {
			fprintf(output, "\tcondition %s\n",
				sexit.scmanda[i].addCondition[j]);
		}
	}

	for (i = 0; i < sexit.isetmanda; i++) {
		fprintf(output, "setManda Name %s setTabnum %s\n",
			sexit.setmanda[i].sName,
			sexit.setmanda[i].setTabnum);
		for (j = 0; j < sexit.setmanda[i].iaddexit; j++) {
			fprintf(output, "\tfieldName %s\n\tclearFunc %s\n\teventName %s\n",
				sexit.setmanda[i].saddExit[j].fieldName,
				sexit.setmanda[i].saddExit[j].clearFunc,
				sexit.setmanda[i].saddExit[j].eventName);
		}
		for (j = 0; j < sexit.setmanda[i].iaddcon; j++) {
			fprintf(output, "\tcondition %s\n",
				sexit.setmanda[i].addCondition[j]);
		}
	}

	for (i = 0; i < sexit.iInvisible; i++) {
		fprintf(output, "Invisible Name %s setTabnum %s\n",
			sexit.sinvisible[i].sName,
			sexit.sinvisible[i].setTabnum);
		for (j = 0; j < sexit.sinvisible[i].iaddexit; j++) {
			fprintf(output, "\tfieldName %s\n\tclearFunc %s\n\teventName %s\n",
				sexit.sinvisible[i].saddExit[j].fieldName,
				sexit.sinvisible[i].saddExit[j].clearFunc,
				sexit.sinvisible[i].saddExit[j].eventName);
		}
		for (j = 0; j < sexit.sinvisible[i].iaddcon; j++) {
			fprintf(output, "\tcondition %s\n",
				sexit.sinvisible[i].addCondition[j]);
		}
	}

	for (i = 0; i < sexit.isvalue; i++) {
		fprintf(output, "setValue Name %s setTabnum %s\n",
			sexit.svalue[i].sName,
			sexit.svalue[i].setTabnum);
		fprintf(output, "\tdataElement %s\n\tsetValue %s\n",
			sexit.svalue[i].dataElement,
			sexit.svalue[i].setValue);
		for (j = 0; j < sexit.svalue[i].iaddexit; j++) {
			fprintf(output, "\tfieldName %s\n\tclearFunc %s\n\teventName %s\n",
				sexit.svalue[i].saddExit[j].fieldName,
				sexit.svalue[i].saddExit[j].clearFunc,
				sexit.svalue[i].saddExit[j].eventName);
		}
		for (j = 0; j < sexit.svalue[i].iaddcon; j++) {
			fprintf(output, "\tcondition %s\n",
				sexit.svalue[i].addCondition[j]);
		}
	}

	for (i = 0; i < sexit.ishowmsg; i++) {
		fprintf(output, "showMsg Name %s setTabnum %s\n",
			sexit.showMsg[i].sName,
			sexit.showMsg[i].setTabnum);
		fprintf(output, "\ttitle %s\n\tmsg %s\n\tmsgtype %d optiontype %d\n",
			sexit.showMsg[i].title,
			sexit.showMsg[i].msg,
			sexit.showMsg[i].msgType,
			sexit.showMsg[i].optionType);
		for (j = 0; j < sexit.showMsg[i].iaddexit; j++) {
			fprintf(output, "\tfieldName %s\n\tclearFunc %s\n\teventName %s\n",
				sexit.showMsg[i].saddExit[j].fieldName,
				sexit.showMsg[i].saddExit[j].clearFunc,
				sexit.showMsg[i].saddExit[j].eventName);
		}
		for (j = 0; j < sexit.showMsg[i].iaddcon; j++) {
			fprintf(output, "\tcondition %s\n",
				sexit.showMsg[i].addCondition[j]);
		}
	}
	for (i = 0; i < sexit.idatasplit; i++) {
		fprintf(output, "dataSplit Name %s setTabnum %s\n",
			sexit.datasplitfunc[i].sName,
			sexit.datasplitfunc[i].setTabnum);
		fprintf(output, "\tdataElement %s\n",
			sexit.datasplitfunc[i].dataElement);
		for (j = 0; j < sexit.datasplitfunc[i].iaddexit; j++) {
			fprintf(output, "\tfieldName %s\n\tclearFunc %s\n\teventName %s\n",
				sexit.datasplitfunc[i].saddExit[j].fieldName,
				sexit.datasplitfunc[i].saddExit[j].clearFunc,
				sexit.datasplitfunc[i].saddExit[j].eventName);
		}
		for (j = 0; j < sexit.datasplitfunc[i].iaddcon; j++) {
			fprintf(output, "\tcondition %s\n",
				sexit.datasplitfunc[i].addCondition[j]);
		}
	}
	for (i = 0; i < sexit.idatamerge; i++) {
		fprintf(output, "dataMerge Name %s setTabnum %s\n",
			sexit.datamerge[i].sName,
			sexit.datamerge[i].setTabnum);
		fprintf(output, "setMergeElements %s\n",
			sexit.datamerge[i].setMergeElements);
		for (j = 0; j < sexit.datamerge[i].iaddexit; j++) {
			fprintf(output, "\tfieldName %s\n\tclearFunc %s\n\teventName %s\n",
				sexit.datamerge[i].saddExit[j].fieldName,
				sexit.datamerge[i].saddExit[j].clearFunc,
				sexit.datamerge[i].saddExit[j].eventName);
		}
		for (j = 0; j < sexit.datamerge[i].iaddcon; j++) {
			fprintf(output, "\tcondition %s\n",
				sexit.datamerge[i].addCondition[j]);
		}
	}
	for (i = 0; i < sexit.iqueryList; i++) {
		fprintf(output, "queryList Name %s\n\tsetTabnum %s\n",
			sexit.squeryList[i].sName,
			sexit.squeryList[i].setTabnum);
		fprintf(output, "\tsQueryList %s\n", sexit.squeryList[i].sQuerylist);
		for (j = 0; j < sexit.squeryList[i].iaddexit; j++) {
			fprintf(output, "\tfieldName %s\n\tclearFunc %s\n\teventName %s\n",
				sexit.squeryList[i].saddExit[j].fieldName,
				sexit.squeryList[i].saddExit[j].clearFunc,
				sexit.squeryList[i].saddExit[j].eventName);
		}
	}
	for (i = 0; i < sexit.ivisible; i++) {
		fprintf(output, "Visible Name %s setTabnum %s\n",
			sexit.svisible[i].sName,
			sexit.svisible[i].setTabnum);
		for (j = 0; j < sexit.svisible[i].iaddexit; j++) {
			fprintf(output, "\tfieldName %s\n\tclearFunc %s\n\teventName %s\n",
				sexit.svisible[i].saddExit[j].fieldName,
				sexit.svisible[i].saddExit[j].clearFunc,
				sexit.svisible[i].saddExit[j].eventName);
		}
		for (j = 0; j < sexit.svisible[i].iaddcon; j++) {
			fprintf(output, "\tcondition %s\n",
				sexit.svisible[i].addCondition[j]);
		}
	}
	for (i = 0; i < sexit.ienable; i++) {
		fprintf(output, "Enable Name %s ",
			sexit.senable[i].sName); 
		for (j = 0; j < 4; j++) {
			fprintf(output, " %d ", sexit.senable[i].setTabnums[j]);
		}
		fprintf(output, "\n");
		for (j = 0; j < sexit.senable[i].iaddexit; j++) {
			fprintf(output, "\tfieldName %s\n\tclearFunc %s\n\teventName %s\n",
				sexit.senable[i].saddExit[j].fieldName,
				sexit.senable[i].saddExit[j].clearFunc,
				sexit.senable[i].saddExit[j].eventName);
		}
		for (j = 0; j < sexit.senable[i].iaddcon; j++) {
			fprintf(output, "\tcondition %s\n",
				sexit.senable[i].addCondition[j]);
		}
	}
	for (i = 0; i < sexit.idisable; i++) {
		fprintf(output, "Disable Name %s setTabnum %s\n",
			sexit.sdisable[i].sName,
			sexit.sdisable[i].setTabnum);
		for (j = 0; j < sexit.sdisable[i].iaddexit; j++) {
			fprintf(output, "\tfieldName %s\n\tclearFunc %s\n\teventName %s\n",
				sexit.sdisable[i].saddExit[j].fieldName,
				sexit.sdisable[i].saddExit[j].clearFunc,
				sexit.sdisable[i].saddExit[j].eventName);
		}
		for (j = 0; j < sexit.sdisable[i].iaddcon; j++) {
			fprintf(output, "\tcondition %s\n",
				sexit.sdisable[i].addCondition[j]);
		}
	}
	for (i = 0; i < sexit
		.ilstsearch; i++) {
		fprintf(output, "LstSearch Name %s setTabnum %s\n",
			sexit.slstsearch[i].sName,
			sexit.slstsearch[i].setTabnum);
		for (j = 0; j < sexit.slstsearch[i].iaddexit; j++) {
			fprintf(output, "\tfieldName %s\n\tclearFunc %s\n\teventName %s\n",
				sexit.slstsearch[i].saddExit[j].fieldName,
				sexit.slstsearch[i].saddExit[j].clearFunc,
				sexit.slstsearch[i].saddExit[j].eventName);
		}
		for (j = 0; j < sexit.slstsearch[i].iaddcon; j++) {
			fprintf(output, "\tcondition %s\n",
				sexit.slstsearch[i].addCondition[j]);
		}
	}
	for (i = 0; i < sexit.isignal; i++) {
		fprintf(output, "Signal Name %s setTabnum %s\n",
			sexit.signal[i].sName,
			sexit.signal[i].setTabnum);
		for (j = 0; j < sexit.signal[i].iaddexit; j++) {
			fprintf(output, "\tfieldName %s\n\tclearFunc %s\n\teventName %s\n",
				sexit.signal[i].saddExit[j].fieldName,
				sexit.signal[i].saddExit[j].clearFunc,
				sexit.signal[i].saddExit[j].eventName);
		}
		for (j = 0; j < sexit.signal[i].iaddcon; j++) {
			fprintf(output, "\tcondition %s\n",
				sexit.signal[i].addCondition[j]);
		}
	}
}

void mylabelWrite()
{
	int i;
	for (i = 0; i < islabel; i++) {
		fprintf(output, "labelname %s\n", slabel[i].lbl);
		fprintf(output, "\tlblno %d setborder %d %d %d %d\n",
			slabel[i].lblno,
			slabel[i].slblbound.x0,
			slabel[i].slblbound.y0,
			slabel[i].slblbound.x1,
			slabel[i].slblbound.y1);
		fprintf(output, "\tname %s\n", slabel[i].name);
		fprintf(output, "\ttext %s\n", slabel[i].text);
		fprintf(output, "\tassociated text %s\n", slabel[i].lbltext);
	}
}

void mytextWrite()
{
	int i;
	for (i = 0; i < istext; i++) {
		fprintf(output, "textname %s\n", stextfield[i].text);
		fprintf(output, "\ttxtno %d setborder %d %d %d %d\n",
			stextfield[i].txtno,
			stextfield[i].stxtbound.x0,
			stextfield[i].stxtbound.y0,
			stextfield[i].stxtbound.x1,
			stextfield[i].stxtbound.y1);
		fprintf(output, "\tenabled %d required %d\n",
			stextfield[i].enabled,
			stextfield[i].required);
		fprintf(output, "\tfont %s\n", stextfield[i].font);
		fprintf(output, "\tdataName %s\n", stextfield[i].dataName);
		fprintf(output, "\tname %s\n", stextfield[i].name);
		fprintf(output, "\tformatter %s\n", stextfield[i].formatter);
	}
}

void mybuttonWrite()
{
	int i;
	for (i = 0; i < igetbutton; i++) {
		fprintf(output, "button %s\n",
			button[i].but);
		fprintf(output, "\tbutNo %d setborder %d %d %d %d\n",
			button[i].butNo,
			button[i].butBound.x0,
			button[i].butBound.y0,
			button[i].butBound.x1,
			button[i].butBound.y1);
		fprintf(output, "\ttxtType %d butText %s\n",
			button[i].butTxttype,
			button[i].butText);
		fprintf(output, "\tbutName %s\n",
			button[i].butName);
		fprintf(output, "\tLocater %d tabOrder %d\n",
			button[i].butLocate,
			button[i].butTabOrder);
	}
}

void myrbuttonWrite()
{
	int i;
	for (i = 0; i < irbutton; i++) {
		fprintf(output, "rbutton %s\n", rbutton[i].rbut);
		fprintf(output, "\trbutNo %d setborder %d %d %d %d\n",
			rbutton[i].rbutno,
			rbutton[i].rbutBound.x0,
			rbutton[i].rbutBound.y0,
			rbutton[i].rbutBound.x1,
			rbutton[i].rbutBound.y1);
		fprintf(output, "\tEnabled %d disable %d tabOrder %d\n",
			rbutton[i].rbutEnabled,
			rbutton[i].disable,
			rbutton[i].rbutTab);
		fprintf(output, "\trbutText %s\n\trbutVal %s\n",
			rbutton[i].rbutText,
			rbutton[i].rbutVal);
	}
}

void mycomboWrite()
{
	int i;
	for (i = 0; i < icombox; i++) {
		fprintf(output, "combox %s\n", combox[i].comboxName);
		fprintf(output, "\tcomboNo %d TabOrder %d setborder %d %d %d %d\n",
			combox[i].comboNo,
			combox[i].comboTabOrder,
			combox[i].comboBounds.x0,
			combox[i].comboBounds.y0,
			combox[i].comboBounds.x1,
			combox[i].comboBounds.y1);
		fprintf(output, "\tdataName %s\n", combox[i].dataName);
		fprintf(output, "\tsetValfname %s\n", combox[i].setvalfname);
		fprintf(output, "\tsetValin %s\n", combox[i].setvalin);
		fprintf(output, "\tsetkeyvals %d\n", combox[i].setkeyvals);
		fprintf(output, "\tsetfname %s\n", combox[i].setfname);
		fprintf(output, "\tsetdnamelst %s\n", combox[i].setdnamelst);
	}
}

void myloaderWrite()
{
	int i;
	for (i = 0; i < iloader; i++) {
		fprintf(output, "Loader= no:%d\n", loader[i].loadNo);
		fprintf(output, "\t Loader Name:%s\n", loader[i].name);
		fprintf(output, "\t Loader String:%s\n", loader[i].loadstr);
	}
}

void mytableWrite()
{
	int i, k;
	for (i = 0; i < istable; i++) {
		fprintf(output, "Table= no:%d\n", stable[i].tableno);
		fprintf(output, "\t Table Name:%s\n", stable[i].name);
		fprintf(output, "\t Table mclick %d\n", stable[i].mclick);
		fprintf(output, "\t Table cols %d\n", stable[i].icols);
		for (k = 0; k < stable[i].icols; k++) {
			fprintf(output, "\t\t Col %d text %s\n", k, stable[i].cols[k].text);
			fprintf(output, "\t\t Begin %d End %d left %d\n",
				stable[i].cols[k].begincol, stable[i].cols[k].endcol,
				stable[i].cols[k].left);
			fprintf(output, "\t\t dname %s dtype %s point %d size %d\n",
				stable[i].cols[k].dataname,
				stable[i].cols[k].dtype,
				stable[i].cols[k].dpoint,
				stable[i].cols[k].size);
		}
	}
}

void myWrite()
{
	int i, j;
	fprintf(output, "finished\n");
	for (i = 0; i <= panelno; i++) {
		fprintf(output, "%d %s\n", i, currpanel[i]);
		for (j = 0; j <= lblno; j++)
			if ((int) strlen(labels[i][j]) > 0)
				fprintf(output, "\t%d %d label: %s\n", i, j, labels[i][j]);
		for (j = 0; j <= txtno; j++)
			if ((int) strlen(txtfields[i][j]) > 0)
				fprintf(output, "\t%d %d txtfields: %s\n", i, j, txtfields[i][j]);
		for (j = 0; j <= buttonno; j++)
			if ((int) strlen(buttons[i][j]) > 0)
				fprintf(output, "\t%d %d buttons: %s\n", i, j, buttons[i][j]);
		for (j = 0; j <= buttongrpno; j++)
			if ((int) strlen(buttongrps[i][j]) > 0)
				fprintf(output, "\t%d %d buttongrp: %s\n", i, j, buttongrps[i][j]);
		for (j = 0; j <= combono; j++)
			if ((int) strlen(combobox[i][j]) > 0)
				fprintf(output, "\t%d %d combobox: %s\n", i, j, combobox[i][j]);
		for (j = 0; j <= qlistno; j++)
			if ((int) strlen(qlist[i][j]) > 0)
				fprintf(output, "\t%d %d combobox: %s\n", i, j, combobox[i][j]);
		for (j = 0; j <= checkno; j++)
			if ((int) strlen(chkBox[i][j]) > 0)
				fprintf(output, "\t%d %d checkBox: %s\n", i, j, chkBox[i][j]);
		for (j = 0; j <= loadno; j++)
			if ((int) strlen(loads[i][j]) > 0)
				fprintf(output, "\t%d %d loads: %s\n", i, j, loads[i][j]);
		for (j = 0; j <= tableno; j++)
			if ((int) strlen(table[i][j]) > 0)
				fprintf(output, "\t%d %d table: %s\n", i, j, table[i][j]);
	}
}

void mywritePanel()
{
	int i, j;
	for (i = 0; i<ispanel; i++) {
		fprintf(output, "panel %s\n", spanel[i].panelName);
		fprintf(output, "\tpanel No %d\n", spanel[i].panNo);
		fprintf(output, "\tborder-width: %d %d %d %d\n",
			spanel[i].spnlbound.x0,
			spanel[i].spnlbound.y0,
			spanel[i].spnlbound.y1,
			spanel[i].spnlbound.x1);
		fprintf(output, "\tTitle %s\n", spanel[i].setTitle);
		fprintf(output, "\tNo of fields %d\n", spanel[i].ifield);
		for (j = 0; j < spanel[i].ifield; j++) {
			fprintf(output, "\ttype %d name %s\n",
				spanel[i].fields[j].ftype,
				spanel[i].fields[j].fieldname);
		}
	}
}

#define RSON 6

#ifdef DEBUGX
char *renkler[] = { "red", "blue", "black", "green" };
#else
char *renkler[] = { "white", "white", "white", "white" };
#endif
int r = 0;

char *constVariables(char *p)
{
	int  i;
	char bufp[200], *p1;
	myReplace(p, '-', '_');
	for (i = 0; i < iconstant; i++) {
		myReplace(constants[i].vval, ' ', '_');
		if (strcmp(constants[i].vval, p) == 0) {
			if (strcmp(constants[i].vtype, "view") == 0)
				sprintf(bufp, "%sConstants.FlowView.%s", tranname, constants[i].vname);
			else
				sprintf(bufp, "%sConstants.%s", tranname, constants[i].vname);
			p1 = (char *)calloc(1, strlen(bufp) + 1);
			strcpy(p1, bufp);
			return p1;
		}
	}
	for (i = 0; i < iconstant; i++) {
		if (strcmp(constants[i].vname, p) == 0) {
			if (strcmp(constants[i].vtype, "view") == 0)
				sprintf(bufp, "%sConstants.FlowView.%s", tranname, constants[i].vname);
			else {
				if (unique) {
					// xx = constVarmi(constants[i].vname, unique, constants[i].vname);
					sprintf(bufp, "%sConstants.%s%d", tranname, constants[i].vname, unique);
				}
				else sprintf(bufp, "%sConstants.%s", tranname, constants[i].vname);
			}
			p1 = (char *)calloc(1, strlen(bufp) + 1);
			strcpy(p1, bufp);
			return p1;
		}
	}
	if (strstr(p, "View")) 
		sprintf(bufp, "%sConstants.FlowView.%s", tranname, p);
	else sprintf(bufp, "%sConstants.%s", tranname, p);
	p1 = (char *)calloc(1, strlen(bufp) + 1);
	strcpy(p1, bufp);
	return p1;
}

void new_form(char *name, char *arrname, int mc, char *area)
{
	char pname[200], *p;
	strcpy(pname, name);
	p = strstr(pname, "Model");
	if (p) *p = 0;
	indents++;
	indentstr();
	fprintf(output, "%s", indent);
	fprintf(output, "<div class=\"form-group\">\n");
	indents++;
	indentstr();
	fprintf(output, "%s", indent);
	fprintf(output, "@(Html.AkbankFacePlus().Grid<AkbankFace.Web.%s.Models.%sViewModel.%s%d>().Name(\"grid\")\n", area, tranname, arrname, mc);
	indents++;
	indentstr();
	fprintf(output, "%s", indent);
	fprintf(output, ".HeaderTitle(\"%s\")\n", arrname);
	fprintf(output, "%s", indent);
	fprintf(output, ".Filterable(f => f.Mode(GridFilterMode.Row))\n");
	fprintf(output, "%s", indent);
	fprintf(output, ".Pageable(p => p.Numeric(false).PreviousNext(false))\n");
	fprintf(output, "%s", indent);
	fprintf(output, ".Editable(e => e.Mode(GridEditMode.InLine))\n");
	fprintf(output, "%s", indent);
	fprintf(output, ".Scrollable(sc => sc.Endless(true))\n");
	//fprintf(output, "%s", indent);
	//fprintf(output, ".Resizeable(r => r.Columns(true))\n");
	if (mc) {
		fprintf(output, "%s", indent);
		fprintf(output, ".Selectable(s => s.Mode(GridSelectionMode.Single).Type(GridSelectionType.Row))\n");
	}
	fprintf(output, "%s", indent);
	fprintf(output, ".Columns(columns =>\n");

	indents++;
	indentstr();
	fprintf(output, "%s", indent);
	fprintf(output, "{\n");
}

void newformend(char* name, int uniq)
{
	indents--;
	indentstr();
	fprintf(output, "%s", indent);
	fprintf(output, "})\n");
	fprintf(output, "%s", indent);
	//fprintf(output, "%s", indent);
	//fprintf(output, ".DataSource(ds => ds.Ajax().Total(15)\n");
	//fprintf(output, "%s", indent);
	//fprintf(output, ".ServerOperation(false))\n");
	if (onchange > 0) 
		fprintf(output, ".BindTo(Model.%s%dList)", name, uniq - 1);
	else fprintf(output, ".BindTo(Model.%sList)", name);
	fprintf(output, "%s", indent);
	fprintf(output, ".DataSource(a => a.Ajax().PageSize(15)\n");
	fprintf(output, "%s", indent);
	fprintf(output, ".ServerOperation(false))\n");
	fprintf(output, "%s", indent);
	fprintf(output, ".Scrollable(s => s.Height(\"500px\"))\n");
	fprintf(output, "%s", indent);
	fprintf(output, ".Resizable(resize => resize.Columns(true))\n");

	onchange++;
	indents--;
	indentstr();
	indents--;
	indentstr();
	indents--;
	indentstr();
	fprintf(output, "%s", indent);
	fprintf(output, "</div>\n");
	rdiv--;
}

int splits(char *p, char c)
{
	int  i = 0;
	char *p1, *p2;
	char dummy[400];

	strcpy(dummy, p);
	p2 = dummy;
	p1 = p2;
	while (p2 && *p2) {
		if (*p2 != 0 && (*p2 == '\"' || *p2 == ' ' || *p2 == ','))
			p2++;
		p1 = p2;
		while (*p1 != 0 && (*p1 != '\"' && *p1 != ',')) p1++;
		if (*p1 == '\"' || *p1 == ',') {
			*p1 = 0;
			p1++;
		}
		else
			*p1 = 0;
		if (*p1 != 0 && (*p1 == '\"' || *p1 == ' ' || *p1 == ','))
			p1++;
		strcpy(xsplit[i], p2);
		p2 = p1;
		i++;
	}
	return i;
}

char *conopBul(char *p)
{
	char *sp = 0;
	if (p) {
		if (strstr(p, "AndCondition")) sp = "&&";
		if (strstr(p, "OrCondition")) sp = "||";
		if (strstr(p, "NOTEQUAL")) sp = "!=";
		if (strstr(p, "EQUAL")) sp = "==";
		if (strstr(p, "GREATERTHAN")) sp = ">";
		if (strstr(p, "GREATEREQUAL")) sp = ">=";
		if (strstr(p, "LESSTHAN")) sp = "<";
		if (strstr(p, "LESSEQUAL")) sp = ">=";
	}
	if (sp == 0)
		sp = "==";
		// fprintf(output, "operation not found %s\n", p);
	return sp;
}
#define STRING  "1"
#define NUMERIC "3"

void valuecheck(int i, int type)
{ 
	char *conop;
	switch (type) {
		case PXCMANDA:
			splits(sexit.scmanda[i].addCondition[2], ',');
			break;
		case PXDATAMERGE:
			splits(sexit.datamerge[i].addCondition[2], ',');
			break;
		case PXDATASPLIT:
			splits(sexit.datasplitfunc[i].addCondition[2], ',');
			break;
		case PXINVISIBLE:
			splits(sexit.sinvisible[i].addCondition[2], ',');
			break;
		case PXQUERYLST:
			splits(sexit.slstsearch[i].addCondition[2], ',');
			break;
		case PXSHOWMSG:
			splits(sexit.showMsg[i].addCondition[2], ',');
			break;
		case PXSMANDA:
			splits(sexit.setmanda[i].addCondition[2], ',');
			break;
		case PXSVALUE:
			splits(sexit.svalue[i].addCondition[2], ',');
			break;
		case PXDISABLE:
			splits(sexit.sdisable[i].addCondition[2], ',');
			break;
		case PXENABLE:
			splits(sexit.senable[i].addCondition[2], ',');
			break;
		case PXSIGNAL:
			splits(sexit.signal[i].addCondition[2], ',');
			break;
		case PXVISIBLE:
			splits(sexit.svisible[i].addCondition[2], ',');
			break;
	}
	conop = conopBul(xsplit[1]);
	if (strstr(xsplit[2], STRING))
		fprintf(output, " %s '%s'", conop, xsplit[1]);
	if (strstr(xsplit[2], NUMERIC))
		fprintf(output, " %s %s", conop, xsplit[1]);
}

void checkExit(int type, char *sname, char *name)
{
	int  i, yaz;
	yaz = 0;
	if (type != 1) {
		for (i = 0; i<sexit.iscmanda; i++) {
			if (sexit.scmanda[i].iaddexit > 0) {
				if (strcmp(sname, sexit.scmanda[i].saddExit[0].fieldName) == 0) {
					fprintf(output,
						".HtmlAttribute(\"data-bind\",\"clearmanda : clearcheck(Model.%s", name);
					if (sexit.scmanda[i].iaddcon > 0) {
						if (strstr(sexit.scmanda[i].addCondition[0], "AndCondition") || strstr(sexit.scmanda[i].addCondition[0], "OrCondition")) {
							valuecheck(i, PXCMANDA);
						}
					}
					else
						if (strstr(sexit.scmanda[i].saddExit[0].eventName, "FOCUS_LOST"))
							fprintf(output, "== ''");
					fprintf(output, ")\")");
					yaz = 1;
					break;
				}
			}
		}
		for (i = 0; i<sexit.isetmanda; i++) {
			if (sexit.setmanda[i].iaddexit > 0) {
				if (strcmp(sname, sexit.setmanda[i].saddExit[0].fieldName) == 0) {
					fprintf(output,
						".HtmlAttribute(\"data-bind\",\"setmanda : setmancheck(Model.%s", name);
					if (sexit.setmanda[i].iaddcon > 0) {
						if (strstr(sexit.setmanda[i].addCondition[0], "AndCondition") || strstr(sexit.setmanda[i].addCondition[0], "OrCondition"))
							valuecheck(i, PXSMANDA);
					}
					if (strstr(sexit.setmanda[i].saddExit[0].eventName, "ACTION_PERFORMED"))
						fprintf(output, "== ''");
					fprintf(output, ")\")");
					yaz = 1;
					break;
				}
			}
		}
		for (i = 0; i<sexit.iInvisible; i++) {
			if (sexit.sinvisible[i].iaddexit > 0) {
				if (strcmp(sname, sexit.sinvisible[i].saddExit[0].fieldName) == 0) {
					fprintf(output,
						".HtmlAttribute(\"data-bind\",\"invisible : invisiblecheck(Model.%s", name);
					if (sexit.sinvisible[i].iaddcon > 0) {
						if (strstr(sexit.sinvisible[i].addCondition[0], "AndCondition") || strstr(sexit.sinvisible[i].addCondition[0], "OrCondition"))
							valuecheck(i, PXINVISIBLE);
					}
					fprintf(output, ")\")");
					yaz = 1;
					break;
				}
			}
		}
		for (i = 0; i<sexit.isvalue; i++) {
			if (sexit.svalue[i].iaddexit > 0) {
				if (strcmp(name, sexit.svalue[i].dataElement) == 0) {
					fprintf(output,
						".HtmlAttribute(\"data-bind\",\"setvalue : valuecheck(Model.%s", name);
					if (sexit.svalue[i].iaddcon > 0) {
						if (strstr(sexit.svalue[i].addCondition[0], "AndCondition") || strstr(sexit.svalue[i].addCondition[0], "OrCondition"))
							valuecheck(i, PXSVALUE);
					}
					if (sexit.svalue[i].setValue[0] == '@')
						 fprintf(output, "),value: Model.%s", sexit.svalue[i].setValue+1);
					else fprintf(output, "),value: '%s'", sexit.svalue[i].setValue);
					fprintf(output, "\")");
					yaz = 1;
					break;
				}
			}
		}
		for (i = 0; i<sexit.ishowmsg; i++) {
			if (sexit.showMsg[i].iaddexit > 0) {
				if (strcmp(sname, sexit.showMsg[i].saddExit[0].fieldName) == 0) {
					// char *title;
					// char *msg;
					// int msgType;
					// int optionType;
					fprintf(output,
						".HtmlAttribute(\"data-bind\",\"showmsg : msgcheck(Model.%s", name);
					if (sexit.showMsg[i].iaddcon > 0) {
						if (strstr(sexit.showMsg[i].addCondition[0], "AndCondition") || strstr(sexit.showMsg[i].addCondition[0], "OrCondition"))
							valuecheck(i, PXSHOWMSG);
					}
					fprintf(output, ")\")");
					yaz = 1;
					break;
				}
			}
		}
		for (i = 0; i<sexit.idatasplit; i++) {
			if (sexit.datasplitfunc[i].iaddexit > 0) {
				if (strcmp(sname, sexit.datasplitfunc[i].saddExit[0].fieldName) == 0) {
					// char *dataElement;
					fprintf(output,
						".HtmlAttribute(\"data-bind\",\"datasplit : splitcheck(Model.%s, ", name);
					splits( sexit.datasplitfunc[i].dataElement, ',');
					fprintf(output, ",%s, %s, %s, %s", xsplit[0], xsplit[1], xsplit[2], xsplit[3]);
					if (sexit.datasplitfunc[i].iaddcon > 0) {
						if (strstr(sexit.datasplitfunc[i].addCondition[0], "AndCondition") || strstr(sexit.datasplitfunc[i].addCondition[0], "OrCondition"))
							valuecheck(i, PXDATASPLIT);
					}
					fprintf(output, ")\")");
					yaz = 1;
					break;
				}
			}
		}
		for (i = 0; i<sexit.idatamerge; i++) {
			if (sexit.datamerge[i].iaddexit > 0) {
				if (strcmp(sname, sexit.datamerge[i].sName) == 0) {
					// char *setMergeElements;
					fprintf(output,
						".HtmlAttribute(\"data-bind\",\"datamerge : mergecheck(Model.%s, ", name);
					splits( sexit.datamerge[i].setMergeElements, ',');
					fprintf(output, ", %s, %s, %s, %s", xsplit[0], xsplit[1], xsplit[2], xsplit[3]);
					if (sexit.datamerge[i].iaddcon > 0) {
						if (strstr(sexit.datamerge[i].addCondition[0], "AndCondition") || strstr(sexit.datamerge[i].addCondition[0], "OrCondition"))
							valuecheck(i, PXDATAMERGE);
					}
					fprintf(output, ")\")");
					yaz = 1;
					break;
				}
			}
		}
		for (i = 0; i<sexit.iqueryList; i++) {
			if (sexit.squeryList[i].iaddexit > 0) {
				if (strcmp(sname, sexit.squeryList[i].saddExit[0].fieldName) == 0) {
					// char *sQuerylist;
					fprintf(output,
						".HtmlAttribute(\"data-bind\",\"querylist : %s\")", name);
					yaz = 1;
					break;
				}
			}
		}
		for (i = 0; i<sexit.idisable; i++) {
			if (sexit.sdisable[i].iaddexit > 0) {
				if (strcmp(name, sexit.sdisable[i].sName) == 0) {
					fprintf(output,
						".HtmlAttribute(\"data-bind\",\"disable : discheck(Model.%s, ", name);
					if (sexit.sdisable[i].iaddcon > 0) {
						 if (strstr(sexit.sdisable[i].addCondition[0], "AndCondition") || strstr(sexit.sdisable[i].addCondition[0], "OrCondition"))
							valuecheck(i, PXDISABLE);
					}
					fprintf(output, ")\")");
					yaz = 1;
					break;
				}
			}
		}
		for (i = 0; i<sexit.ienable; i++) {
			if (sexit.senable[i].iaddexit > 0) {
				if (strcmp(sname, sexit.senable[i].saddExit[0].fieldName) == 0) {
					fprintf(output,
						".HtmlAttribute(\"data-bind\",\"enable : encheck(Model.%s, ", name);
					if (sexit.senable[i].iaddcon > 0) {
						if (sexit.senable[i].iaddcon > 0) {
							if (strstr(sexit.senable[i].addCondition[0], "AndCondition") ||
								strstr(sexit.senable[i].addCondition[0], "OrCondition"))
								valuecheck(i, PXENABLE);
						}
					}
					fprintf(output, ")\")");
					yaz = 1;
					break;
				}
			}
		}
		for (i = 0; i<sexit.ivisible; i++) {
			if (sexit.svisible[i].iaddexit > 0) {
				if (strcmp(name, sexit.svisible[i].sName) == 0) {
					fprintf(output,
						".HtmlAttribute(\"data-bind\",\"visible : visiblecheck(Model.%s, ", name);
					if (sexit.svisible[i].iaddcon > 0) {
						if (strstr(sexit.svisible[i].addCondition[0], "AndCondition") || strstr(sexit.svisible[i].addCondition[0], "OrCondition"))
							valuecheck(i,PXVISIBLE);
					}
					fprintf(output, ")\")");
					yaz = 1;
					break;
				}
			}
		}
		for (i = 0; i<sexit.ilstsearch; i++) {
			if (sexit.slstsearch[i].iaddexit > 0) {
				if (strcmp(sname, sexit.slstsearch[i].saddExit[0].fieldName) == 0) {
					fprintf(output,
						".HtmlAttribute(\"data-bind\",\"lstsearch : lstcheck(Model.%s, ", name);
					if (sexit.slstsearch[i].iaddcon > 0) {
						if (strstr(sexit.slstsearch[i].addCondition[0], "AndCondition") || strstr(sexit.slstsearch[i].addCondition[0], "OrCondition"))
							valuecheck(i, PXQUERYLST);
					}
					fprintf(output, ")\")");
					yaz = 1;
					break;
				}
			}
		}
		for (i = 0; i<sexit.isignal; i++) {
			if (sexit.signal[i].iaddexit > 0) {
				if (strcmp(sname, sexit.signal[i].saddExit[0].fieldName) == 0) {
					fprintf(output,
						".HtmlAttribute(\"data-bind\",\"signal : signalcheck(Model.%s, ", name);
					if (sexit.signal[i].iaddcon > 0) {
						if (strstr(sexit.signal[i].addCondition[0], "AndCondition") || strstr(sexit.signal[i].addCondition[0], "OrCondition"))
							valuecheck(i, PXSIGNAL);
					}
					fprintf(output, ")\")");
					yaz = 1;
					break;
				}
			}
		}
		if (yaz == 1) fprintf(output, ";\n");
	}
}

int  ionchange;
char *onchangestr[20];

int  onchangeYazdi(char *p)
{
	int  i;
	for (i = 0; i < ionchange; i++) {
		if (strcmp(onchangestr[i], p) == 0)
			return i;
	}
	i = ionchange;
	onchangestr[i] = (char *)calloc(1, strlen(p) + 1);
	strcpy(onchangestr[i], p);
	ionchange++;
	return -1;
}

void onchangeYaz(int icount)
{
	fprintf(output, "%s", indentstr());
	if (icount > 1)
		fprintf(output, "function onChange%d(event: Event) {\n", icount);
	else fprintf(output, "function onChange(event: Event) {\n");
	fprintf(output, "    event.preventDefault();\n");
	fprintf(output, "    var grid = $(event.srcElement).closest('div[data-role=\"akgrid\"]'.data(\"kendoAkbGrid\");\n");
	fprintf(output, "    var dataItem = grid.dataItem($(event.currentTarget).closest(\"tr\"));\n");
	fprintf(output, "    var strSelected = JSON.stringify(dataItem);\n");
	if (icount > 1)
		fprintf(output, "    	modelSelf.SelectedRow(strSelected);\n");
	else fprintf(output, "    	modelSelf.SelectedRow%d(strSelected);\n", icount);
	fprintf(output, "    }\n");
}

void onchangeSatir(int kk, int k, char *dname, char *kdname, char *dtext) {
	char pname[200];
	if (dname) {
		if (strstr(dname, ", "))
			sprintf(pname, "%s", skipsome(dtext));
		else
			strcpy(pname, dname);
	}
	else
		if (kdname)
			strcpy(pname, kdname);
		else
			if (!kdname)
				sprintf(pname, "column%d", kk);
	if (kk + 1 == stable[k].icols)
		fprintf(output, "    	     item.%s;\n", pname);
	else fprintf(output, "    	     item.%s + \" - \" +\n", pname);
}

int onchanged(char *pname)
{
	int  i;
	for (i = 0; i < ionchange; i++) {
		if(strcmp(onchangestr[i], pname) == 0)
			return 1;
	}
	return 0;
}

void scripts()
{
	int  i, j, k, kk;
	char *sfname;
	int icount = 0;
	// char pname[100];
	fprintf(output, "<script>\n");
	for (i = 0; i < ispanel; i++) {
		for (j = 0; j < spanel[i].ifield; j++) {
			sfname = spanel[i].fields[j].fieldname;
			if (spanel[i].fields[j].ftype == panelTEXT) {
				/* *****************  text field char *fieldname; *************************/
				for (k = 0; k < istext; k++) {
					if (strcasecmp(sfname, stextfield[k].text) == 0) {
						if (stextfield[k].formatter && strstr(stextfield[k].formatter, "Date")) {
							fprintf(output, "%s", indentstr());
							fprintf(output, "function %sSec(event) {\n", stextfield[k].dataName);
							fprintf(output, "%s", indentstr());
							fprintf(output, "   var sdata = document.getElementById(\"%sDt\").value;\n", stextfield[k].dataName);
							fprintf(output, "%s", indentstr());
							fprintf(output, "   document.getElementById(\"%s\").value = sdata;\n", stextfield[k].dataName);
							fprintf(output, "}\n");
						}
					}
				}
			}
			if (spanel[i].fields[j].ftype == panelCOMBOX) {
				for (k = 0; k < icombox; k++) {
					if (strcasecmp(sfname, combox[k].fcomboxName + 3) == 0) {
						char comb[100], *p;
						
						p = strstr(combox[k].comboxName, "Comb");
						if (p) {
							strcpy(comb, p);
						}
						else strcpy(comb, combox[k].comboxName);
						fprintf(output, "%s", indentstr());
						fprintf(output, "function %sSec(e) {\n", comb);
						fprintf(output, "	var sdata = this.dataItem(e.item.index());\n");
						fprintf(output, "	var str = sdata.Text;\n");
						fprintf(output, "   /* eger goruntulenecek bilgi -- oncesindeyse substr(0,i)\n");
						fprintf(output, "      yoksa -- sonrası icin substr(i) kullanin */\n");
						fprintf(output, "	var i = str.indexOf(\"--\");\n");
						fprintf(output, "	var a = str.substr(0, i);\n");
						fprintf(output, "	document.getElementById(\"%s\").value = a;\n", comb);
						fprintf(output, "}\n");
					}
				}
			}
		}
	}
	for (i = 0; i < ispanel; i++) {
		for (j = 0; j < spanel[i].ifield; j++) {
			if (spanel[i].fields[j].ftype == panelTABLE) {
				for (k = 0; k < istable; k++) {
					if (strcmp(stable[k].name, spanel[i].fields[j].fieldname) == 0) {
						icount++;
						onchangeYazdi(stable[k].name);
						onchangeYaz(icount);
						for (kk = 0; kk < stable[k].icols; kk++) {
							onchangeSatir(kk, k, stable[k].cols[kk].dataname, stable[k].cols[kk].dataname, stable[k].cols[kk].text);
						}
						if (icount > 1)
							fprintf(output, "    	     alert(document.getElementById(\"SelectedRow%d\").value);\n", icount);
						else fprintf(output, "    	     alert(document.getElementById(\"SelectedRow\").value);\n");
						fprintf(output, "    	    //  document.getElementById(\"CommandTag\").value = \"TABLECLICK\";\n");
						// document.getElementById("mainForm").submit();
						fprintf(output, "}\n");
					}
				}
			}
		}
	}
	for (k = 0; k < istable; k++) {	
		if (onchanged(stable[k].name) == 0) {
			icount++;
			onchangeYazdi(stable[k].name);
			onchangeYaz(icount);
			for (kk = 0; kk < stable[k].icols; kk++) {
				onchangeSatir(kk, k, stable[k].cols[kk].dataname, stable[k].cols[kk].dataname, stable[k].cols[kk].text);
			}
			if (icount > 1)
				fprintf(output, "    	     alert(document.getElementById(\"SelectedRow%d\").value);\n", icount);
			else fprintf(output, "    	     alert(document.getElementById(\"SelectedRow\").value);\n");
			fprintf(output, "    	    //  document.getElementById(\"CommandTag\").value = \"TABLECLICK\";\n");
			// document.getElementById("mainForm").submit();
			fprintf(output, "}\n");
		}		
	}	
	fprintf(output, "</script>\n");
}

void tabloYazdir(char *mname, char *area)
{
	int k, kk;
	/*int ii, ix;*/
	indents++;
	indentstr();
	for (k = 0; k < istable; k++) {
		fprintf(output, "%s", indent);
		fprintf(output, "<div class=\"row\">\n");
		indents++;
		indentstr();
		fprintf(output, "%s", indent);
		fprintf(output, "<div class=\"col-12\">\n");
		//ix = stable[k].icols / 6;
		//if (stable[k].icols > ix * 6) ix++;
		//for (ii = 0; ii<ix; ii++) {
		fprintf(output, "%s", indent);
		if (k > 0)
			fprintf(output, "@Html.AkbankFacePlus().HiddenFor(m => m.SelectedRow%d)\n", k);
		else fprintf(output, "@Html.AkbankFacePlus().HiddenFor(m => m.SelectedRow)\n");
		new_form(mname, stable[k].name, stable[k].mclick + 1, area);
		indents++;
		indentstr();
		for (kk = 0; kk<stable[k].icols; kk++) {
			if (stable[k].cols[kk].kdataname && strstr(stable[k].cols[kk].kdataname, ",")) {
				fprintf(output, "%s", indent);
				fprintf(output, "columns.Bound(c => c.%s).Title(\"%s\");\n", 
					skipsome(stable[k].cols[kk].text), stable[k].cols[kk].title);
			}
			else
			if (stable[k].cols[kk].kdataname) {
				fprintf(output, "%s", indent);
				fprintf(output, "columns.Bound(c => c.%s).Title(\"%s\");\n", 
					stable[k].cols[kk].kdataname, stable[k].cols[kk].title);
			}
			else {
				fprintf(output, "%s", indent);
				if (stable[k].cols[kk].text)
					fprintf(output, "columns.Bound(c => c.%s).Title(\"%s\");\n", 
						stable[k].cols[kk].text, stable[k].cols[kk].title);
				else fprintf(output, "columns.Bound(c => c.column%d).Title(\"coulmn%d\");\n", kk, kk);
			}
		}
		newformend(stable[k].name, k+1);
		/*}*/
		indents--;
		indentstr();
		fprintf(output, "%s", indent);
		fprintf(output, "</div>\n");
		indents--;
		indentstr();
		fprintf(output, "%s", indent);
		fprintf(output, "</div>\n");
	}
	indents--;
	indentstr();
}

int findLine(int ftype, char *fname)
{
	int  i, ii;
	if (ftype == panelTABLE) {
		for (i = 0; i < istable; i++) {
			if (strcmp(stable[i].name, fname) == 0) {
				return stable[i].tableBounds.x0;
			}
		}
		return -1;
	}
	if (ftype == panelTEXT) {
		for (i = 0; i < istext; i++) {
			if (strcmp(stextfield[i].text, fname) == 0) {
				return stextfield[i].stxtbound.x0 + slabel[i].slblbound.y0 * 1000;
			}
		}
		return -1;
	}
	if (ftype == panelLABEL) {
		for (i = 0; i < islabel; i++) {
			if (strcmp(slabel[i].lbl, fname) == 0) {
				for (ii = 0; ii < istext; ii++) {
					// burada kaldi...
					if (!(slabel[i].lbltext && stextfield[ii].dataName)) continue;
					if (strcmp(slabel[i].lbltext, stextfield[ii].dataName) == 0)
						return stextfield[ii].stxtbound.x0 + (slabel[i].slblbound.y0 + strlen(slabel[i].text)) * 1000;
				}
				return slabel[i].slblbound.y0 * 1000 + slabel[i].slblbound.x0;
			}
		}
		return -1;
	}
	if (ftype == panelRBUTTON) {
		for (i = 0; i < irbutton; i++) {
			if (strcmp(rbutton[i].rbut, fname) == 0) {
				return rbutton[i].rbutBound.y0 * 1000 + rbutton[i].rbutBound.x0;
			}
		}
		return -1;
	}
	if (ftype == panelCOMBOX) {
		for (i = 0; i < icombox; i++) {
			if (strstr(combox[i].fcomboxName, fname)) {
				return combox[i].comboBounds.y0 * 1000 + combox[i].comboBounds.x0;
			}
		}
		return -1;
	}
	
	if (ftype == panelCHKBOX) {
		for (i = 0; i < ichkno; i++) {
			if (strcasecmp(checkBox[i].setName, fname) == 0) {
				return checkBox[i].checkBounds.y0 * 1000 + checkBox[i].checkBounds.x0;
			}
		}
		return -1;
	}
	return -1;
}


int checkLine(int r, int line)
{
	if (line == EOF) return line;
	if (r == 0 || (r <= line-5 || r >= line+5)) {
		if (r != 0) {
			indents--;
			indentstr();
			fprintf(output, "%s", indent);
			fprintf(output, "</div>\n");
		}
		indentstr();
		fprintf(output, "%s", indent);
		fprintf(output, "<div class=\"row\">\n");
		indents++;
		indentstr();
	}
	return line;
}

/**********************************/
int isorted = 0;
struct SORTED {
	int  sj;
	int  sline;
	char *sf;
	int  styp;
	char *stxt;
} sorted[200];

void insertline(int j, int line, char *sfname, int typ, char *txt)
{
	int  i,ii;
	for (i = 0; i < isorted; i++) {
		if (sorted[i].sline > line) {
			for (ii = isorted; ii > i; ii--) {
				sorted[ii].sj = sorted[ii - 1].sj;
				sorted[ii].sline = sorted[ii - 1].sline;
				sorted[ii].sf = sorted[ii - 1].sf;
				sorted[ii].stxt = sorted[ii - 1].stxt;
				sorted[ii].styp = sorted[ii - 1].styp;
			}
			sorted[i].sj = j;
			sorted[i].sline = line;
			sorted[i].sf = sfname;
			sorted[i].stxt = txt;
			sorted[i].styp = typ;
			isorted++;
			return;
		}
	}
	i = isorted;
	sorted[i].sj = j;
	sorted[i].sline = line;
	sorted[i].sf = sfname;
	sorted[i].stxt = txt;
	sorted[i].styp = typ;
	isorted++;
}

// char *nextBak(char *ss, int ii, int is)
// {
// 	int  i, j, k, line, bak;
// 
// 	for (i = is; i < isorted; i++) {
// 		j = sorted[i].sj;
// 		line = sorted[i].sline;
// 		if (spanel[ii].fields[j].ftype == panelTEXT) {
// 			if (ss[0]) {
// 				for (k = 0; k < istext - 1; k++) {
// 					if (strcmp(stextfield[k].dataName, ss) == 0) {
// 						bak = ii * 1000000 + stextfield[k + 1].stxtbound.y0 * 1000 + stextfield[k + 1].stxtbound.x0;
// 						if (line == bak)
// 							return stextfield[k + 1].dataName;
// 					}
// 				}
// 			}
// 			else {
// 				for (k = 0; k < istext - 1; k++) {
// 					bak = ii * 1000000 + stextfield[k + 1].stxtbound.y0 * 1000 + stextfield[k + 1].stxtbound.x0;
// 					if (line == bak)
// 						return stextfield[k + 1].dataName;
// 				}
// 			}
// 		}
// 	}
// 	return 0;
// }
/*********************************************************/


char *calsize(int sz)
{
	if (sz / 5 <= 1)
		return "col-md-1";
	if (sz / 5 <= 2)
		return "col-md-2";
	if (sz / 5 <= 4)
		return "col-md-4";
	if (sz / 5 <= 6)
		return "col-md-6";
	return "col-md-8";
}

int  ilistnos = 0;
int  listnos[10];

int labelvarmi(int isort, int i, int k, int onceki, int outvar)
{
	char* ptext;
	if (onceki >= 0) {
		if (abs(sorted[isort].sline - sorted[onceki].sline) < 10) {
			if (outvar) {
				if (sorted[isort].styp == panelTEXT) {
					if (stextfield[k].name && strstr(stextfield[k].name, "null") == 0)
						ptext = stextfield[k].name;
					else 
						if (stextfield[k].dataName)
							ptext = stextfield[k].dataName;
						else ptext = stextfield[k].text;
					if (stextfield[k].formatter) {
						if (strstr(stextfield[k].formatter, "Date"))
							fprintf(output, "<label class=\"form-control-placeholder\" for=\"%sDt\">%s</label>\n",
								ptext, sorted[onceki].stxt);
						else
							if (strstr(stextfield[k].formatter, "Numeric"))
								fprintf(output, "<label class=\"form-control-placeholder\" for=\"%s\">%s</label>\n",
									ptext, sorted[onceki].stxt);
						fprintf(output, "%s", indent);
					}
					else {
						fprintf(output, "<label class=\"form-control-placeholder\" for=\"%s\">%s</label>\n",
							ptext, sorted[onceki].stxt);
						fprintf(output, "%s", indent);
					}
				}
				if (sorted[isort].styp == panelTABLE) {
					fprintf(output, "<label class=\"form-control-placeholder\" for=\"%s\">%s</label>\n",
						stable[k].name, sorted[onceki].stxt);
					fprintf(output, "%s", indent);
				}
				if (sorted[isort].styp == panelRBUTTON) {
					fprintf(output, "<label class=\"form-control-placeholder\">%s</label>\n",
						sorted[onceki].stxt);
					fprintf(output, "%s", indent);
				}
			}
			sorted[onceki].sline = 0;
			return onceki;
		}
	}
	return -1;
}

void writeTable(char* sfname, int isort, int i, int oncekij, int sonrakij, char* modelname, char* area, int uniq, int *icount)
{
	int  k, kk, lvar;
	char* psize;
	for (k = 0; k < istable; k++) {
		if (strcasecmp(sfname, stable[k].name) == 0) {
			int ii, son;
			fprintf(output, "%s", indent);
			fprintf(output, "<div class=\"row form-group\">\n");
			rdiv++;
			indents++;
			indentstr();
			fprintf(output, "%s", indent);
			psize = calsize(stable[k].tableBounds.y1);
			fprintf(output, "<div class=\"col-12\">\n");
			rdiv++;
			lvar = labelvarmi(isort, i, k, oncekij, 1);
			ii = 0;
			fprintf(output, "%s", indent);
			if (*icount > 0)
				fprintf(output, "@Httml.AkbankFace().HiddenFor(m=>m.SelectedRow%d).KO(\"value:SelectedRow%d\")\n", *icount, *icount);
			else fprintf(output, "@Httml.AkbankFace().HiddenFor(m=>m.SelectedRow).KO(\"value:SelectedRow\")\n");
			while (ii < stable[k].icols) {
				son = ii + CPERPAGE > stable[k].icols ? stable[k].icols : ii + CPERPAGE;
				new_form(modelname, stable[k].name, uniq, area);
				indents++;
				indentstr();

				for (kk = ii; kk < son; kk++) {
					if (kk == ii) {
						fprintf(output, "%s", indent);
						fprintf(output, "columns.Select().Title(\"\").Width(\"70px\")\n");
						fprintf(output, "%s", indent);
						fprintf(output, ".HtmlAttributes(new { @class=\"grid-detail-icon\", onclick=\"pageSelf.onChange(event)\"}))\n");
					}
					if (stable[k].cols[kk].dataname && (int)strlen(stable[k].cols[kk].dataname) > 0) {
						fprintf(output, "%s", indent);
						if (stable[k].cols[kk].kdataname && (int)strlen(stable[k].cols[kk].kdataname) > 0) {
							if (strstr(stable[k].cols[kk].kdataname, ","))
								fprintf(output, "columns.Bound(c => c.%s).Title(\"%s\");\n", skipsome(stable[k].cols[kk].text), stable[k].cols[kk].title);
							else fprintf(output, "columns.Bound(c => c.%s).Title(\"%s\");\n", stable[k].cols[kk].kdataname, stable[k].cols[kk].title);
						}
						else
							if (strstr(stable[k].cols[kk].dataname, ","))
								fprintf(output, "columns.Bound(c => c.%s).Title(\"%s\");\n", skipsome(stable[k].cols[kk].text), stable[k].cols[kk].title);
							else fprintf(output, "columns.Bound(c => c.%s).Title(\"%s\");\n", stable[k].cols[kk].dataname, stable[k].cols[kk].title);
					}
					else {
						fprintf(output, "%s", indent);
						if (stable[k].cols[kk].kdataname && (int)strlen(stable[k].cols[kk].kdataname) > 0)
							if (strstr(stable[k].cols[kk].kdataname, ","))
								fprintf(output, "columns.Bound(c => c.%s).Title(\"%s\");\n", skipsome(stable[k].cols[kk].text), stable[k].cols[kk].title);
							else fprintf(output, "columns.Bound(c => c.%s).Title(\"%s\");\n", skipsome(stable[k].cols[kk].kdataname), stable[k].cols[kk].title);
						else
							fprintf(output, "columns.Bound(c => c.column%d).Title(\"%s\");\n", kk, stable[k].cols[kk].title);
					}
				}
				indents--;
				newformend(stable[k].name, uniq);
				ii = son;
				scriptVar = 1;
			}
			*icount = *icount + 1;
			indents--;
			indentstr();
			fprintf(output, "%s", indent);
			fprintf(output, "</div>\n");
			rdiv--;
			indents--;
			indentstr();
			fprintf(output, "%s", indent);
			fprintf(output, "</div>\n");
			rdiv--;
			r++;
			break;
		}
	}
}

void writeText(char* sfname, int isort, int i, int j, int line, int oncekij)
{
	int  k, lvar;
	char* psize, * enableptr, * reqptr;
	for (k = 0; k < istext; k++) {
		if (strcasecmp(sfname, stextfield[k].text) == 0) {
			// textfield do something for required;
			r = checkLine(r, line);
			fprintf(output, "%s", indent);
			psize = calsize(stextfield[k].stxtbound.y1);
			fprintf(output, "<div class=\"%s\">\n", psize);
			rdiv++;
			indents++;
			indentstr();
			fprintf(output, "%s", indent);
			enableptr = "";
			if (!stextfield[k].enabled) {
				// disabled
				enableptr = ".Enable(false)";
			}
			reqptr = "";
			// if(stextfield[k].required)
			//     reqptr=".Required(true)";
			if (stextfield[k].formatter) {
				if (strstr(stextfield[k].formatter, "Numeric")) {
					lvar = labelvarmi(isort, i, k, oncekij, 1);
					fprintf(output,
						"@Html.AkbankFacePlus().NumericTextBoxFor(m => m.%s)%s%s",
						buyukHarf(stextfield[k].dataName),
						enableptr, reqptr);

					checkExit(spanel[i].fields[j].ftype, sfname, stextfield[k].dataName);
				}
				if (strstr(stextfield[k].formatter, "Date")) {
					fprintf(output, "@Html.AkbankFacePlus().HiddenFor(m => m.%s)\n",
						buyukHarf(stextfield[k].dataName));
					fprintf(output, "%s", indentstr());
					//fprintf(output,
					//"@Html.AkbankFacePlus().Tablet().DatePickerFor(m => m.%sDt).Events(e => { e.Change(\"%sSec\"); }).%s\n",
					//	stextfield[k].dataName, stextfield[k].dataName,
					//	reqptr);
					lvar = labelvarmi(isort, i, k, oncekij, 1);
					//fprintf(output, "<label class=\"form-control-placehlder\" for=\"%sDt\">%s</label>\n",
					//	stextfield[k].dataName, stextfield[oncekij].text);
					fprintf(output, "@(Html.AkbankFacePlus().DateRangePicker(\"StratDate\", \"EndDate\").Name(\"%sDt\").MaxDate(DateTime.Now.AddDays(1500)))\n",
						buyukHarf(stextfield[k].dataName));
					fprintf(output, ".HtmlAttributes(onselect=\"pageSelf.onSelect(event, '%sSec')\")%s\n",
						buyukHarf(stextfield[k].dataName), reqptr);
					checkExit(spanel[i].fields[j].ftype, sfname, stextfield[k].dataName);
					scriptVar = 1;
				}
			}
			else {
				lvar = labelvarmi(isort, i, k, oncekij, 1);
				if (stextfield[k].dataName == NULL) {
					stextfield[k].dataName = stextfield[k].text;
				}
				if (strncmp(stextfield[k].dataName, "paraBirimAlfa", 13) == 0) {
					fprintf(output,
						"@Html.AkbankFacePlus().AmountTextBoxFor(m => m.%s%d).KO(\"numeric:%s\").Min(0).Max(999999999999999).Decimals(2).%s%s",
						buyukHarf(stextfield[k].dataName), k, stextfield[k].dataName, enableptr, reqptr);
					checkExit(spanel[i].fields[j].ftype, sfname, stextfield[k].dataName);
				}
				else {
					fprintf(output,
						"@Html.AkbankFacePlus().TextBoxFor(m => m.%s)%s%s",
						buyukHarf(stextfield[k].dataName), enableptr, reqptr);
					checkExit(spanel[i].fields[j].ftype, sfname, stextfield[k].dataName);
				}
			}

			fprintf(output, "\n");
			// check exit struct and find conditions
			indents--;
			indentstr();
			fprintf(output, "%s", indent);
			fprintf(output, "</div>\n");
			rdiv--;
			break;
		}
	}
}

void writeLabel(int k)
{
	char* psize;
	char sonuncu[200];

	if (slabel[k].lbltext) {
		fprintf(output, "%s", indent);
		psize = calsize(slabel[k].slblbound.y1);
		fprintf(output, "<div class=\"%s\">\n", psize);
		rdiv++;
		indents++;
		fprintf(output, "%s", indentstr());
		fprintf(output, "    <label class=\"form-control-placeholder\">%s</label>\n", buyukHarf(slabel[k].lbltext));
		if (hiddenk == 0) {
			fprintf(output, "%s", indent);
			fprintf(output, "    @Html.AkbankFacePlus().HiddenFor(m => m.CommandTag)\n");
			hiddenk = 1;
		}
		indents--;
		indentstr();
		fprintf(output, "%s", indent);
		fprintf(output, "</div>\n");
		rdiv--;
		strcpy(sonuncu, slabel[k].lbltext);
	}
	else
		if (slabel[k].text) {
			// sonraki ilk degiskeni bul, daha oncesi de sonuncu adli alanda...
			fprintf(output, "%s", indent);
			psize = calsize((int)strlen(slabel[k].text) * 5);
			fprintf(output, "<div class=\"%s\">\n", psize);
			rdiv++;
			indents++;
			if (hiddenk == 0) {
				fprintf(output, "%s", indent);
				fprintf(output, "@Html.AkbankFacePlus().HiddenFor(m => m.CommandTag)\n");
				hiddenk = 1;
			}
			fprintf(output, "%s", indent);
			fprintf(output, "    <Label class=\"form-control-placeholder\">%s</label>\n", buyukHarf(slabel[k].text));
			indents--;
			indentstr();
			fprintf(output, "%s", indent);
			fprintf(output, "</div>\n");
			rdiv--;
		}
}

void writeRbutton(char* sfname, int isort, int i, int oncekij, int rbYazdi)
{
	int  k, kk, lvar, isize;
	int  listvar = 0, listno = 0;
	char* psize;
	fprintf(output, "%s", indentstr());
	for (k = 0; k < irbutton; k++) {
		for (kk = 0; kk < ilistnos; kk++) {
			if (listnos[kk] == rbutton[k].rbutTab && strcasecmp(sfname, rbutton[k].rbut) == 0)
				listvar = 1;
		}
		if (listvar == 0 && strcasecmp(sfname, rbutton[k].rbut) == 0 && rbYazdi == 0) {
			// rbutton[k].rbutVal, rbutton[k].rbut);
			if (listno != rbutton[k].rbutTab) {
				psize = calsize(rbutton[k].rbutBound.y1);
				fprintf(output, "<div class=\"%s\">\n", psize);
				rdiv++;
				lvar = labelvarmi(isort, i, k, oncekij, 1);
				indents++;
				isize = rbutton[k].rbutBound.y1;
				fprintf(output, "%s", indentstr());
				fprintf(output, "@Html.AkbankFacePlus().RadioButtonListFor(m => m.%s, list%d).ColSize(%d).Required(true)\n",
					buyukHarf(rbutton[k].rbut), rbutton[k].rbutTab, isize * 2);
				// rbutton[k].rbutVal
				//fprintf(output, ".KO(ComponentValueBindingType.RadioButtonList, \"%s\")",
				//	rbutton[k].rbut);

				/*fprintf(output, ".ColSize(%d).FirstCharToUpper(true)", isize);*/
				/*fprintf(output, ".FirstCharToUpper(true)");*/
				/*fprintf(output, ".Required(true)");*/
				if (!rbutton[k].rbutEnabled) {
					fprintf(output, ".Enabled(true)");
				}
				fprintf(output, "\n");
				listno = rbutton[k].rbutTab;
				// checkExit(spanel[i].fields[j].ftype, sfname, rbutton[k].rbut);
				indents--;
				indentstr();
				fprintf(output, "%s", indent);
				fprintf(output, "</div>\n");
				rdiv--;
				rbYazdi = 1;
				listnos[ilistnos] = listno;
				ilistnos++;
			}
			/* r++;*/
			// break;
		}
	}
}

void writeCombox(char* sfname, int k)
{
	char saveId[100], comb[200];
	char* p1, *psize, *p, *px, *pp;

	fprintf(output, "%s", indentstr());
	if (combox[k].comboBounds.y1)
		psize = calsize(combox[k].comboBounds.y1);
	else psize = "col-12";
	fprintf(output, "<div class=\"%s\">\n", psize);
	rdiv++;

	indents++;
	indentstr();
	if (combox[k].setvalfname) {
		p = strstr(combox[k].setvalfname + 1, ".--");
		if (p) *p = 0;
	}
	if (combox[k].comboxName == NULL) {
		combox[k].comboxName = combox[k].fcomboxName + 3;
	}
	p1 = strstr(combox[k].comboxName, "Comb");
	if (p1) {
		strcpy(saveId, p1);
	}
	else strcpy(saveId, combox[k].comboxName);
	fprintf(output, "%s", indent);
	p = strstr(combox[k].comboxName, "Comb");
	if (p) {
		strcpy(comb, p);
	}
	else strcpy(comb, combox[k].comboxName);
	fprintf(output, "<label class=\"form-control-placeholder\" for=\"%s\">%s</label>\n",
		comb, combox[k].comboxName);
	fprintf(output, "%s", indent);
	px = "";
	if (combox[k].setdnamelst) {
		pp = strstr(combox[k].setdnamelst, ".");
		if (pp) {
			pp = pp + 1;
			if (!strstr(pp, "List"))
				px = "";
			else px = "List";
		}
		else pp = combox[k].comboxName;
	}
	else  pp = combox[k].comboxName;

	fprintf(output, "@Html.AkbankFacePlus().ComboBoxFor(m => m.%s).Name(\"%s\")\n",
		buyukHarf(combox[k].comboxName), buyukHarf(comb));
	fprintf(output, ".BindTo(Model.%s%s).DataValueField(\"Value\").DataTextField(\"Text\")\n", pp, px);

	fprintf(output, ".HtmlAttributes(\"Id\", \"%s\").KO(\"selectedValue: %s\")\n",
		buyukHarf(combox[k].comboxName), buyukHarf(combox[k].comboxName));
	indents--;
	indentstr();
	rdiv--;
	fprintf(output, "%s", indent);
	fprintf(output, "</div>\n");
}

void writeChkBox(int k, int isort, int i, int oncekij, int line)
{
	char* psize;
	int lvar;
	if (k == 0) {
		r = checkLine(r, line);

		fprintf(output, "%s", indent);
		psize = calsize(checkBox[k].checkBounds.y1);
		fprintf(output, "<div class=\"%s\">\n", psize);
		rdiv++;
		lvar = labelvarmi(isort, i, k, oncekij, 0);
		indents++;
		indentstr();
	}
	fprintf(output, "%s", indent);
	if (checkBox[k].text)
		fprintf(output,
			"<label class=\"form-control-placeholder\" for=\"%s\">%s</label>\n",
			buyukHarf(checkBox[k].setName), checkBox[k].text);
	else
		fprintf(output,
			"<label class=\"form-control-placeholder\" for=\"%s\">%s</label>\n",
			buyukHarf(checkBox[k].setName), checkBox[k].dataName);

	//fprintf(output, "%s", indent);
	//psize = calsize(checkBox[k].checkBounds.y1);
	//fprintf(output, "<div class=\"%s\">\n", psize);
	//lvar = labelvarmi(isort, i, k, oncekij, 1);
	//indents++;
	//indentstr();
	fprintf(output, "%s", indent);
	fprintf(output,
		"@Html.AkbankFacePlus().CheckBoxFor(m => m.%s).KO(\"checked: %s\")\n",
		buyukHarf(checkBox[k].dataName), checkBox[k].dataName);
}

void panelContent(char *modelname, int ilkpanel, int uniq, char *panNam, char *pan, char *tranid, char *area, char *odir)
{
	int  i, j, k;
	int  isort = 0;
	int   line;
	char  *odirp;
	char *sfname;
	char sonuncu[200];
	char *styp;
	int  oncekij, sonrakij;
	int  listvar = 0;
	int  rbYazdi = 0, icount;
	styp = 0;
	ilistnos = 0;
	if (ilkpanel == 0) {
		// indents++;
		indentstr();
		fprintf(output, "%s", indent);
		fprintf(output, "<div class=\"container-fluid\">\n");
		rdiv++;

		indents++;
		indentstr();
		fprintf(output, "%s", indent);
		fprintf(output, "@using (Html.AkbankFacePlus().BeginForm())\n");
		fprintf(output, "%s", indent);
		fprintf(output, "{\n");
	}
	indents++;
	indentstr();
	odirp = strrchr(odir, '\\');
	if (odirp)
		 odirp++;
	else odirp = odir;
	for (i = 0; i < ispanel; i++) {
		// select panel
		if ((spanel[i].setTitle && strcmp(panNam, spanel[i].setTitle) == 0) || 
			(spanel[i].panelName && strcmp(panNam, spanel[i].panelName) == 0)) {
			isorted = 0;
			fprintf(output, "%s", indent);
			fprintf(output, "<div class=\"col-12\">\n");
			rdiv++;
			fprintf(output, "%s", indent);
			if (spanel[i].panelName)
				fprintf(output, "    @using (Html.AkbankFacePlus().BeginPanel(\"panel%d\", builder => builder.Header(AkbankFace.Web.%s.Common.Constants.%s)))\n",
					i, area, constVariables(spanel[i].panelName));
			else 
				fprintf(output, "    @using (Html.AkbankFacePlus().BeginPanel(\"panel%d\", builder => builder.Header(AkbankFace.Web.%s.Common.Constants.%s)))\n",
					i, area, constVariables("AkbankPanel"));
			indents++;
			fprintf(output, "%s", indent);
			fprintf(output, "    {\n");
			indents++;
			for (j = 0; j < spanel[i].ifield; j++) {
				if ((spanel[i].fields[j].ftype == panelTABLE) ||
					(spanel[i].fields[j].ftype == panelTEXT) ||
					(spanel[i].fields[j].ftype == panelLABEL) ||
					(spanel[i].fields[j].ftype == panelRBUTTON) ||
					(spanel[i].fields[j].ftype == panelCOMBOX) ||
					(spanel[i].fields[j].ftype == panelCHKBOX)) {
					    char *txt = " ";
						sfname = spanel[i].fields[j].fieldname;
						//if (j == 13) {
						//	fprintf(output, "burada\n");
						//}
						line = i * 1000000 + findLine(spanel[i].fields[j].ftype, sfname);
						if (spanel[i].fields[j].ftype == panelLABEL) {
							for (k = 0; k < islabel; k++) {
								// text field char *fieldname;
								if (strcasecmp(sfname, slabel[k].lbl) == 0) {
									txt = slabel[k].text;
									break;
								}
							}
						}
						else txt = " ";
						if (spanel[i].fields[j].ftype == panelLABEL)  styp = (char *)"L";
						if (spanel[i].fields[j].ftype == panelTEXT)   styp = (char*) "T";
						if (spanel[i].fields[j].ftype == panelTABLE)  styp = (char*) "B";
						if (spanel[i].fields[j].ftype == panelCOMBOX) styp = (char*) "C";
						if (spanel[i].fields[j].ftype == panelRBUTTON)styp = (char*) "R";
						if (spanel[i].fields[j].ftype == panelCHKBOX) styp = (char*) "H";

						insertline(j, line, sfname, spanel[i].fields[j].ftype, txt);
				}
			}

			r = 0;
			sonuncu[0] = 0;
			icount = 0;
			for (isort = 0; isort < isorted; isort++) {
				j = sorted[isort].sj;
				if (sorted[isort].sline < 1) continue;
				line = (sorted[isort].sline % 1000000) / 1000;
				if (isort > 0)
					oncekij = isort - 1;
				else oncekij = -1;
				if (isort - 1 < isorted)
					sonrakij = isort + 1;
				else sonrakij = -1;
				sfname = spanel[i].fields[j].fieldname;
				//line = i * 1000 + findLine(spanel[i].fields[j].ftype, sfname) / 1000;
				if (spanel[i].fields[j].ftype != panelRBUTTON)
					rbYazdi = 0;
				if (spanel[i].fields[j].ftype == panelTABLE) {
						// tables or grid
						writeTable(sfname, isort, i, oncekij, sonrakij, modelname, area, uniq, &icount);
						r = checkLine(r, line);
				}
				if (spanel[i].fields[j].ftype == panelTEXT) {
						/* *****************  text field char *fieldname; *************************/
						indents++;
						indentstr();
						writeText(sfname, isort, i, j, line, oncekij);
						indents--;
						indentstr();
				}
				if (spanel[i].fields[j].ftype == panelLABEL) {
						/* ***************** label ****************************************/
						// label attributes char *fieldname;
						indents++;
						indentstr();
						for (k = 0; k < islabel; k++) {
							// text field char *fieldname;
							if (strcasecmp(sfname, slabel[k].lbl) == 0) {
								if (sorted[sonrakij].styp != panelLABEL) break;
								writeLabel(k);
								break;
							}
							// slabel[k].text);
							// name yazılmadı...
							// break;
						}
						indents--;
						indentstr();
				}
				if (spanel[i].fields[j].ftype == panelRBUTTON ) {
						/* ***************** radio button ****************************************/
						// label attributes char *fieldname;
						int  listno;
						indents=2;
						if (rbYazdi == 0)
							r = checkLine(r, line);
						listno = 0;
						listvar = 0;
						writeRbutton(sfname, isort, i, oncekij, rbYazdi);
						indents--;
						indentstr();
				}
				if (spanel[i].fields[j].ftype == panelCOMBOX) {
						/********************* comboBox  queryList ********************************/
						indents = 2;
						r = checkLine(r, line);
						// combox[k].comboxName);
						for (k = 0; k<icombox; k++) {
							if (strcasecmp(sfname, combox[k].fcomboxName + 3) == 0) {
								writeCombox(sfname, k);
								scriptVar = 1;
							}
						}
						if (scriptVar) {
							indents--;
							indentstr();
							fprintf(output, "%s", indent);
							fprintf(output, "</div>\n");
							rdiv--;
							r++;
							indents--;
							indentstr();
						}
				}
				if (spanel[i].fields[j].ftype == panelCHKBOX) {
						/********************* checkBox ********************************/
						int chkboxvar = 0;
						indents++;
						indentstr();

						for (k = 0; k < ichkno; k++) {
							if(checkBox[k].setName == NULL || strcasecmp(spanel[i].fields[j].fieldname, checkBox[k].setName)) continue;
							writeChkBox(k, isort, i, oncekij, line);
							chkboxvar = 1;
						}
						if (chkboxvar) {
							indents--;
							indentstr();
							fprintf(output, "%s", indent);
							fprintf(output, "</div>\n");
							rdiv--;
							// r++;
							indents--;
							indentstr();
						}

				}

				if (spanel[i].fields[j].ftype != panelLABEL) {
					if (rdiv > 0) {
							indents--;
							indentstr();
							fprintf(output, "%s", indent);
							fprintf(output, "</div>\n");
							rdiv--;
					}
					r = checkLine(r, line);
				}
			}
			if (rdiv > 0) {
				indents--;
				indentstr();
				fprintf(output, "%s", indent);
				fprintf(output, "</div>\n");
				rdiv--;
			}
			indents--;
			indentstr();
			fprintf(output, "%s", indent);
			fprintf(output, "}\n");
			fprintf(output, "%s", indent);
			fprintf(output, "</div>\n");
			indents--;
			indentstr();
		}
	}
 }


void buttongrpContent(char *grp)
{
	int k;
	indents++;
	indentstr();
	for (k = 0; k < isgroup; k++) {
		if (strcasecmp(sgroup[k].dataName, grp) == 0) {
			/* bunlar baska yerde kullanilmali */
			fprintf(output, "%s", indent);
			fprintf(output, "@(Html.AkbankFacePlus().RadioButtonListFor(m => m.%s, %sList))\n", 
				buyukHarf(rbutton[k].rbut), buyukHarf(rbutton[k].rbut));
		}
	}
	indents--;
	indentstr();
}

void getfont(char *targ, char *pfont)
{
	char *p, *p1;
	char ff[200];
	strcpy(ff, pfont);
	p1 = strstr(ff, "\"");
	if(p1) {
		p1++;
		p = p1;
		while (*p != 0 && *p != '"') p++;
		if(p) {
			*p = 0;
			strcpy(targ, p1);
		}
	}
}

int getfontsz(char *pfont)
{
	char *p, *p1;
	char ff[200];
	strcpy(ff, pfont);
	p = strchr(ff, ',');
	if (p) {
		p++;
		p = strchr(ff, ',');
		while (*p <= '0' || *p >= '9') p++;
		p1 = p;
	}
	else p1 = 0;
	return(p1 ? atoi(p1) : 0);
}

char defineYaz[200][50];
int  idefineYaz;
int  defineYazFunc(char *p)
{
	int  i;
	for (i = 0; i < idefineYaz; i++) {
		if (strcmp(p, defineYaz[i]) == 0)
			return 1;
	}
	i = idefineYaz;
	strcpy(defineYaz[i], p);
	idefineYaz++;
	return 0;
}

char *findpanel(char *pname)
{
	int i;
	for (i = 0; i<ispanel; i++) {
		if (strcasecmp(pname, spanel[i].panelName) == 0)
			return spanel[i].setTitle;
	}
	return NULL;
}

int defines(int cnt, int tnum, char *sname)
{
	int i, j, var;
	char xtnum[100];

	sprintf(xtnum, "%d", tnum);
	var = 0;
	switch (cnt) {
	case TSSCMANDA:
		for (i = 0; i < sexit.iscmanda; i++) {
			if (sexit.scmanda[i].iaddexit > 0) {
				if (strstr(sexit.scmanda[i].setTabnum, xtnum)) {
					if (defineYazFunc("clearmanda")) continue;
					fprintf(output, "    public clearmanda: KnockoutComputed<string>;\n");
					var = 1;
					break;
				}
			}
		}
		break;
	case TSSETMANDA:
		for (i = 0; i < sexit.isetmanda; i++) {
			if (sexit.setmanda[i].iaddexit > 0) {
				if (strstr(sexit.setmanda[i].setTabnum, xtnum)) {
					if (defineYazFunc("setmanda")) continue;
					fprintf(output, "    public setmanda: KnockoutObservable<string>;\n");
					var = 1;
					break;
				}
			}
		}
		break;
	case TSINVISIBLE:
		for (i = 0; i < sexit.iInvisible; i++) {
			if (sexit.sinvisible[i].iaddexit > 0) {
				if (strstr(sexit.sinvisible[i].setTabnum, xtnum)) {
					if (defineYazFunc("sinvisible")) continue;
					fprintf(output, "    public sinvisible: KnockoutObservable<boolean>;\n");
					var = 1;
					break;
				}
			}
		}
		break;
	case TSSVALUE:
		for (i = 0; i < sexit.isvalue; i++) {
			if (sexit.svalue[i].iaddexit > 0) {
				if (sexit.svalue[i].setTabnum && strstr(sexit.svalue[i].setTabnum, xtnum)) {
					if (defineYazFunc(sexit.svalue[i].dataElement)) continue;
					// fprintf(output, "    public svalue: KnockoutObservable<boolean>;\n");
					fprintf(output, "    public %s: KnockoutObservable<string>;\n", sexit.svalue[i].dataElement);
					var = 1;
					break;
				}
			}
		}
		break;
	case TSSHOWMSG:
		for (i = 0; i < sexit.ishowmsg; i++) {
			if (sexit.showMsg[i].iaddexit > 0) {
				if (sexit.showMsg[i].setTabnum && strstr(sexit.showMsg[i].setTabnum, xtnum)) {
					if (defineYazFunc("showmsg")) continue;
					fprintf(output, "    public showmsg: KnockoutObservable<string>;\n");
					var = 1;
					break;
				}
			}
		}
		break;
	case TSSPLIT:
		for (i = 0; i < sexit.idatasplit; i++) {
			if (sexit.datasplitfunc[i].iaddexit > 0) {
				if (sexit.datasplitfunc[i].setTabnum && strstr(sexit.datasplitfunc[i].setTabnum, xtnum)) {
					if (defineYazFunc("datasplit")) continue;
					fprintf(output, "    public datasplit: KnockoutObservable<boolean>;\n");
					var = 1;
					break;
				}
			}
		}
		break;
	case TSMERGE:
		for (i = 0; i < sexit.idatamerge; i++) {
			if (sexit.datamerge[i].iaddexit > 0) {
				if (sexit.datamerge[i].setTabnum && strstr(sexit.datamerge[i].setTabnum, xtnum)) {
					if (defineYazFunc("datamerge")) continue;
					fprintf(output, "    public datamerge: KnockoutObservable<boolean>;\n");
					var = 1;
					break;
				}
			}
		}
		break;
	case TSQUERY:
		for (i = 0; i < sexit.iqueryList; i++) {
			if (sexit.squeryList[i].iaddexit > 0) {
				if (sexit.squeryList[i].setTabnum && strstr(sexit.squeryList[i].setTabnum, xtnum)) {
					if (defineYazFunc("querylist")) continue;
					fprintf(output, "    public querylist: KnockoutObservable<boolean>;\n");
					var = 1;
					break;
				}
			}
		}
		break;
	case TSDISABLE:
		for (i = 0; i < sexit.idisable; i++) {
			if (sexit.sdisable[i].iaddexit > 0) {
				if (sexit.sdisable[i].setTabnum && strstr(sexit.sdisable[i].setTabnum, xtnum)) {
					if (defineYazFunc(sexit.sdisable[i].sName)) continue;
					fprintf(output, "    public %s: KnockoutObservable<boolean>;\n", buyukHarf(sexit.sdisable[i].sName));
					var = 1;
					break;
				}
			}
		}
		break;
	case TSENABLE:
		for (i = 0; i < sexit.ienable; i++) {
			if (sexit.senable[i].iaddexit > 0) {
				for (j = 0; j < 4; j++) {
					if (tnum == sexit.senable[i].setTabnums[j] && sexit.senable[i].setTabnums[j] > 0) {
						if (defineYazFunc(sexit.senable[i].sName)) continue;
						fprintf(output, "    public %s: KnockoutObservable<boolean>;\n", buyukHarf(sexit.senable[i].sName));
						var = 1;
						break;
					}
				}
			}
		}
		break;
	case TSVISIBLE:
		for (i = 0; i < sexit.ivisible; i++) {
			if (sexit.svisible[i].iaddexit > 0) {
				if (strcmp(sname, sexit.svisible[i].saddExit[0].fieldName) == 0) {
					if (defineYazFunc(sexit.svisible[i].sName)) continue;
					fprintf(output, "    public %s: KnockoutObservable<boolean>;\n", buyukHarf(sexit.svisible[i].sName));
					var = 1;
					break;
				}
			}
		}
		break;
	case TSLSTSEARCH:
		for (i = 0; i < sexit.ilstsearch; i++) {
			if (sexit.slstsearch[i].iaddexit > 0) {
				if (strcmp(sname, sexit.slstsearch[i].saddExit[0].fieldName) == 0) {
					if (defineYazFunc("lstsearch")) continue;
					fprintf(output, "    public lstsearch: KnockoutObservable<boolean>;\n");
					var = 1;
					break;
				}
			}
		}
		break;
	case TSSIGNAL:
		for (i = 0; i < sexit.isignal; i++) {
			if (sexit.signal[i].iaddexit > 0) {
				if (strcmp(sname, sexit.signal[i].saddExit[0].fieldName) == 0) {
					if (defineYazFunc("signal")) continue;
					fprintf(output, "    public signal: KnockoutObservable<boolean>;\n");
					var = 1;
					break;
				}
			}
		}
		break;
	}
	return var;
}

char onbutton[50][50];
int  ionbutton = 0;

int  onbuttonVarmi(char *p)
{
	int  i;
	for (i = 0; i < ionbutton; i++) {
		if (strcmp(onbutton[i], p) == 0) return 1;
	}
	strcpy(onbutton[ionbutton], p);
	ionbutton++;
	return 0;
}

void tsProlog(char *trname, char *tsmodel, char *odir, char *area)
{
	char model[200];
	char *p1;
	int  i, k, icount=0;
	if (strcmp(trname, "Index") == 0) {
		strcpy(model, tsmodel);
	}
	else {
		strcpy(model, trname);
		strcat(model, "ViewModel");
	}
	if (strstr(model, "ViewModel") == 0)
		strcat(model, "ViewModel");

	p1 = strrchr(odir, '\\');
	fprintf(output, "import base = require(\"AkbankFaceBase\");\n");
	// fprintf(output, "import constants = require(\"constants\")\n");

	if (strstr(model,"KriterView")) {
		fprintf(output, "declare var pageSelf: %s;\n", trname);
		fprintf(output, "declare var modelSelf: %s%s;\n", tranname, model); // model);
		fprintf(output, "export class %s extends base.AkbankFacePageBase<%s> {\n", trname, trname);

		fprintf(output, "   public viewModel: base.AkbankFaceModelBase<%s%s>;\n", tranname, model);
		fprintf(output, "   constructor(data: any) {\n");
		fprintf(output, "    	super(pageSelf.viewModel);\n");
		fprintf(output, "    	pageSelf = this;\n");
		fprintf(output, "    	var viewModel = new %s%s();\n", tranname, model);
	}
	 else {
		 strcat(tsmodel, "Model");
		 fprintf(output, "declare var pageSelf: %s;\n", trname);
		 fprintf(output, "declare var modelSelf: %s;\n", model); // model);
		 fprintf(output, "export class %s extends base.AkbankFacePageBase<%s> {\n", trname, trname);

		 fprintf(output, "   public viewModel: base.AkbankFaceModelBase<%s>;\n", model);
		 fprintf(output, "   constructor(data: any) {\n");
		 fprintf(output, "    	super(pageSelf.viewModel);\n");
		 fprintf(output, "    	pageSelf = this;\n");
		 fprintf(output, "    	var viewModel = new %s();\n", model);
	 }
	fprintf(output, "    	viewModel.View = pageSelf;\n");
	fprintf(output, "    	pageSelf.viewModel = viewModel;\n");
	fprintf(output, "    	viewModel.Load(data);\n");
	fprintf(output, "   }\n\n");

	fprintf(output, "	public Init() : %s {\n", trname);
	fprintf(output, "		return super.Init();\n");
	fprintf(output, "	}\n\n");

	fprintf(output, "	public InitComplete() : %s {\n", trname);
	fprintf(output, "       return super.InitComplete(); \n");
	fprintf(output, "	}\n\n");

	fprintf(output, "	public PreLoad() : %s {\n", trname);
	fprintf(output, "		return super.PreLoad();\n");
	fprintf(output, "	}\n\n");

	fprintf(output, "	public Load(): %s {\n", trname);
	fprintf(output, "		return super.Load();\n");
	fprintf(output, "	}\n\n");

	fprintf(output, "	public LoadComplete(): %s {\n", trname);
	if (eprintid == 1 || eprintid == 3) {
		fprintf(output, "		super.Print(\"%s\", \"%s\", \"PrintSlip\", null);\n", area, tranname);
	}
	fprintf(output, "		return super.LoadComplete();\n");
	fprintf(output, "	}\n\n");

	fprintf(output, "	public Unload(): %s {\n", trname);
	fprintf(output, "		return super.Unload();\n");
	fprintf(output, "	}\n\n");

	fprintf(output, "	public OnButtonCommand(button: base.ActionButton): %s {\n", trname);
	fprintf(output, "		var command = button.CommandTag();\n");
	for (i = 0; i < iconstant; i++) {
		if (strcmp(constants[i].vtype, "flowtag") == 0) {
			if (onbuttonVarmi(constants[i].vname)) continue;
			fprintf(output, "		if (command === \"%s\") {\n", constants[i].vname);
			fprintf(output, "			$(\"#CommandTag\").val(\"%s\");\n", constants[i].vname);
			fprintf(output, "		}\n");
		}
	}
	fprintf(output, "		return super.OnButtonCommand(button);\n");
	fprintf(output, "	}\n");
	for (k = 0; k < istable; k++) {
		if (onchanged(stable[k].name) == 0) {
			icount++;
			onchangeYazdi(stable[k].name);
			onchangeYaz(icount);
		}
	}
	/* burada printer varsa ilgili typescript eklenecek */
	fprintf(output, "}\n");
}

int tsYazdirma(char *trname, int tnum, char *sname, char *odir, char *areaname)
{
	int var = 0;
	if (tnum == 0) return var;
	// fprintf(output, "//#region Model Properties\n");
	var = defines(TSSCMANDA, tnum, sname);
	if (var == 0) var = defines(TSSETMANDA, tnum, sname);
	if (var == 0) var = defines(TSINVISIBLE, tnum, sname);
	if (var == 0) var = defines(TSSVALUE, tnum, sname);
	if (var == 0) var = defines(TSSHOWMSG, tnum, sname);
	if (var == 0) var = defines(TSSPLIT, tnum, sname);
	if (var == 0) var = defines(TSMERGE, tnum, sname);
	if (var == 0) var = defines(TSQUERY, tnum, sname);
	if (var == 0) var = defines(TSDISABLE, tnum, sname);
	if (var == 0) var = defines(TSENABLE, tnum, sname);
	if (var == 0) var = defines(TSVISIBLE, tnum, sname);
	if (var == 0) var = defines(TSLSTSEARCH, tnum, sname);
	if (var == 0) var = defines(TSSIGNAL, tnum, sname);
	// fprintf(output, "//#endregion\n");
	return var;
}

void checks(char *fname, char *tsmodel, char *odir, char *areaname, int tnode)
{
	int  i, j, k;
	int  var7 = 0, var0 = 0, var1 = 0;
	int  var2 = 0, var4 = 0, var5 = 0;
	int  var;
	int  fvar;
	char *sfname, *p;
	char sva[200], tabnum[100];
	sprintf(tabnum, "%d", tnode);
	p = strrchr(fname, '\\');
	if (p) {
		p = p + 1;
	}
	else p = fname;
	strcpy(sva, tsmodel);
	tsProlog(p, tsmodel, odir, areaname);
	strcpy(tsmodel, sva);
	if (strstr(tsmodel, "ViewModel") == 0)
		strcat(tsmodel, "ViewModel");
	if (strstr(tsmodel, "KriterView"))
		fprintf(output, "export class %s%s extends base.AkbankFaceModelBase<%s%s> {\n", tranname, buyukHarf(tsmodel), tranname, buyukHarf(tsmodel));
	else fprintf(output, "export class %s extends base.AkbankFaceModelBase<%s> {\n", buyukHarf(tsmodel), buyukHarf(tsmodel));
	// view daki degiskenler icin bu tanimlar yapilir.
	var = 0;
	idefineYaz = 0;
	for (i = 0; i < ispanel; i++) {
		for (j = 0; j < spanel[i].ifield; j++) {
			sfname = spanel[i].fields[j].fieldname;
			for (k = 0; k < istext; k++) {
				if (stextfield[k].dataName && strcmp(sfname, stextfield[k].text) == 0 ||
					(stextfield[k].tabOrder && strstr(tabnum, stextfield[k].tabOrder)) {
					if (defineYazFunc(stextfield[k].dataName)) continue;
					fprintf(output, "    public %s: KnockoutObservable<string>;\n", buyukHarf(stextfield[k].dataName));
					var = 1;
				}
			}
		}
	}
	if (var) {
		fprintf(output, "    public CommandTag: any;\n");
		for (i = 0; i < isgroup; i++) {
			fprintf(output, "        public %s: KnockoutObservable<string>;\n", buyukHarf(sgroup[i].dataName));
		}
		// fprintf(output, "    }\n");
	}
	for (i = 0; i < ispanel; i++) {
		for (j = 0; j < spanel[i].ifield; j++) {
			sfname = spanel[i].fields[j].fieldname;
			switch (spanel[i].fields[j].ftype) {
			case panelTABLE: /* 7 */
				for (k = 0; k < istable; k++) {
					if (stable[k].name && strcmp(sfname, stable[k].name) == 0) {
						var = tsYazdirma(fname, stable[k].tabOrder, sfname, odir, areaname);
						if (var7 == 0) var7 = var;
						break;
					}
				}
				break;
			case panelTEXT:  /* 0 */
				for (k = 0; k < istext; k++) {
					if (stextfield[k].text && strcmp(sfname, stextfield[k].text) == 0) {
						var = tsYazdirma(fname, stextfield[k].tabOrder, sfname, odir, areaname);
						if (var0 == 0) var0 = var;
						break;
					}
				}
				break;
			case panelLABEL: /* 1 */
				for (k = 0; k < islabel; k++) {
					if (slabel[k].lbl && strcmp(sfname, slabel[k].lbl) == 0) {
						var = tsYazdirma(fname, slabel[k].tabOrder, sfname, odir, areaname);
						if (var1 == 0) var1 = var;
						break;
					}
				}
				break;
			case panelRBUTTON: /* 2 */
				for (k = 0; k < irbutton; k++) {
					if (rbutton[k].rbut && strcmp(sfname, rbutton[k].rbut) == 0) {
						var = tsYazdirma(fname, rbutton[k].rbutTab, sfname, odir, areaname);
						if (var2 == 0) var2 = var;
						break;
					}
				}
				break;
			case panelCOMBOX: /* 4 */
				for (k = 0; k < icombox; k++) {
					if (combox[k].fcomboxName && strstr(combox[k].fcomboxName, sfname)) {
						var = tsYazdirma(fname, combox[k].comboTabOrder, sfname, odir, areaname);
						if (var4 == 0) var4 = var;
						break;
					}
				}
				break;
			case panelCHKBOX: /* 5 */
				for (k = 0; k < ichkno; k++) {
					if (checkBox[k].dataName && strcmp(sfname, checkBox[k].dataName) == 0) {
						var = tsYazdirma(fname, checkBox[k].checkTabOrder, sfname, odir, areaname);
						if (var5 == 0) var5 = var;
						break;
					}
				}
			}
		}
	}
	// if (var) 
	fprintf(output, "    }\n");
	fvar = 0;
	// fprintf(output, "%d %d %d %d %d %d\n", var0, var1, var2, var4, var5, var7);
}

void params(int argc, char **argv)
{
	int i;
	for (i = 0; i < argc; i++){
		fprintf(output, "%d %s, ", i, argv[i]);
	}
	fprintf(output, "\n");
}

int constVarmi(char *p)
{
	int i;
	for (i = 0; i < iconstant; i++) {
		if (strcmp(constants[i].vname, p) == 0) {
			return 1;
		}
	}
	return 0;
}

void readconst(char *ffile, char *cfile)
{
	int  i;
	FILE *fp;
	char *p, *p1;
	char mybuf[200];
	iconstant = 0;
	fp = fopen(ffile, "r");
	if (fp) {
		while (fgets(buf, MAXCHAR, fp)) {
			rmnl(buf);
			p = strstr(buf, ".");
			if (p) {
				*p = 0;
				p++;
				strcpy(mybuf, buf);
				
				p1 = strstr(p, "=");
				if (p1) {
					if (constVarmi(p)) continue;
					i = iconstant;
					constants[i].vtype = (char *)calloc(1, strlen(mybuf) + 1);
					strcpy(constants[i].vtype, buyukHarf(mybuf));
					*p1 = 0; p1++;
					constants[i].vval = (char *)calloc(1, strlen(p) + 1);
					strcpy(constants[i].vval, buyukHarf(p));
					constants[i].vname = (char *)calloc(1, strlen(p1) + 1);
					strcpy(constants[i].vname, buyukHarf(p1));
					iconstant++;
				}
			}
		}
		fclose(fp);
	}
	else {
		printf("file yok %s\n", ffile);
		return;
	}
	fp = fopen(cfile, "r");
	if (fp) {
		while (fgets(buf, MAXCHAR, fp)) {
			rmnl(buf);
			p = strstr(buf, ".");
			if (p) {
				*p = 0;
				p++;
				strcpy(mybuf, buf);
				p1 = strstr(p, "=");
				if (p1) {
					*p1 = 0; p1++;
					if (constVarmi(p)) continue;
					i = iconstant;
					constants[i].vtype = (char *)calloc(1, strlen(buf) + 1);
					strcpy(constants[i].vtype, buyukHarf(mybuf));
					constants[i].vname = (char *)calloc(1, strlen(p) + 1);
					strcpy(constants[i].vname, buyukHarf(p));
					p = p1;
					constants[i].vval = (char *)calloc(1, strlen(p) + 1);
					strcpy(constants[i].vval, buyukHarf(p));
					iconstant++;
				}
			}
		}
		fclose(fp);
		i = iconstant;
		constants[i].vtype = "view";
		constants[i].vname = "ViewIndex";
		constants[i].vval = "Index";
		iconstant++;
	}
	else {
		printf("file yok %s\n", cfile);
		return;
	}
#ifdef DEBUG
	fprintf(output, "okuma tamam\n");
#endif
}


extern int bakBakalim(char *, int);

int main(int argc, char **argv)
{
	FILE *fp;
	int ret, procId;
	int  i, mypanel;
	char *ptitle;
	char *p, filename[300];
	char htmlname[300];
	char tsmodel[300];
	char modelname[300];
	char outdir[300];
	char area[300];
	char tranid[300];
	char flowfile[200];
	char constfile[200];
	char prog[200];

	/* get tables and coulmns of connected database */
	SetConsoleOutputCP(CP_UTF8);
	output = stdout;
	param = 0;
	if (argc >= 10) {
		param = atoi(argv[1]);
		strcpy(tranid, argv[2]);
		strcpy(outdir, argv[3]);
		strcpy(area, argv[4]);
		strcpy(modelname, argv[5]);
		strcpy(prog, argv[6]);
		unique = atoi(argv[7]);
		eprintid = atoi(argv[8]);
		procId = atoi(argv[9]);
		fp = fopen(argv[10], "r");
		if (argc == 12)
			strcpy(filename, argv[11]);
		else strcpy(filename, argv[10]);
		strcpy(indexname, filename);
		p = strrchr(indexname, '\\');
		if (p) {
			char temp[200];
			*p = 0;
			strcpy(temp, p+1);
			strcpy(indexname, temp);
			p = strstr(indexname, ".java");
			if (p) *p = 0;
		}
	}
	else {
		params(argc, argv);
		fprintf(output, "kullanım: cshtml 1/2 <tranid> <dir> <area> <model> <prog> <printer> <unique> <java_file> [<csName>]\n");
		return(0);
	}
	if (bakBakalim("", procId) == 0)
		exit(0);
	strcpy(flowfile, argv[10]);
	p = strstr(flowfile, "\\INDIRS");
	if (p) {
		*p = 0;
		strcat(flowfile, "\\");
		strcat(flowfile, PREFS);
		strcat(flowfile, tranid);
		strcat(flowfile, "\\");
		strcat(flowfile, tranid);
		strcat(flowfile, prog);
		strcpy(constfile, flowfile);
		strcat(flowfile, "flow.preference");
		strcat(constfile, ".constants");
	}
	strcpy(tranname, tranid);
	strcpy(tsmodel, modelname);
	strcat(modelname, "Model");
	p = strstr(filename, ".");
	if (p) *p = 0;
	strcpy(htmlname, outdir);
	strcat(htmlname, "\\");
	p = strrchr(filename, '\\');
	if (p) p++;
	else p = filename;
	strcat(htmlname, p); // htmlname  = p + ".cshtml"
	//strcpy(modelname, p);
	//strcat(modelname, "Model");
	if (param == 2) {
		strcat(htmlname, ".cshtml");
	}
	else {
		strcat(htmlname, ".ts");
	}

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
		fchkbox = 0;
		floader = 0;
		fquery = 0;
		ftable = 0;
		fscroll = 0;
		fbuttongrps = 0;
		do {
			// printf("buf (%s)\n", buf);
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
		fclose(input);
		if (param == 2) {
			char myfont[100];
			int myfontsz;
			if (stextfield[0].font) {
				getfont(myfont, stextfield[0].font);
				myfontsz = getfontsz(stextfield[0].font);
			}
			else {
				strcpy(myfont, "Verdana");
				myfontsz = 12;
			}
			readconst(flowfile, constfile);

			if (slayout.name)
				myprologue(slayout.name, tranid, area, slayout.title);
			else
			if (slayout.title)
				myprologue(modelname, tranid, area, slayout.title);
			else myprologue(modelname, tranid, area, modelname);
			// fprintf(output,"<form>\n");
			scriptVar = 0;
			if (slayout.iadded) {
				mypanel = 0;
				for (i = 0; i< slayout.iadded; i++) {
					if (slayout.added[i].type == PADDPANEL) {
						ptitle = findpanel(slayout.added[i].addb);
						panelContent(modelname, i, unique, slayout.added[i].addb, ptitle, tranid, area, outdir);
						mypanel++;
					}
					if (slayout.added[i].type == PGETGRP) {
						buttongrpContent(slayout.added[i].addb);
					}
					if (slayout.added[i].type == PADDSTABLE) {
						tabloYazdir(modelname, area);
					}
				}
			}
			//if (istable > 0) {
			//	tabloYazdir(area);
			//}
			myepilogue(mypanel);
			/*
			if (scriptVar) {
				scripts();
			}
			*/
			// buraya javascript eklenecek mi?
		}
		if (param == 3) {
			readconst(flowfile, constfile);
			checks(filename, tsmodel, outdir, area);
		}
		fclose(output);
	}
	else
		fprintf(output, "java_file %s bulunamadı\n", argv[5]);
	return 0;
}
