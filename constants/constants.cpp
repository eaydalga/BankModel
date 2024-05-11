#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define DEBG

#define true  1
#define false 0

#define  TSSCMANDA    1
#define  TSSETMANDA   2
#define  TSINVISIBLE  3
#define  TSSVALUE     4
#define  TSSHOWMSG    5
#define  TSSPLIT      6
#define  TSMERGE      7
#define  TSQUERY      8
#define  TSDISABLE    9
#define  TSENABLE    10
#define  TSVISIBLE   11
#define  TSLSTSEARCH 12
#define  TSSIGNAL    13

#define PCLASS      1
#define PWIDGETS    2
#define PPANEL      3
#define PLABEL      4
#define PTEXTFIELD  5
#define PBUTTON     6
#define PBUTTONGRP  7
#define PCOMBOBOX   8
#define PLOADSTR    9
#define PCHECKBOX   10
#define PTSCROLL    11
#define PTABLE      12
#define PTABLES      13
#define PTSCROLLS    14
#define PQUERYLSTFUNC 83
#define PLOADER    86

#define CDUMMY ""

#define CCLIENT "com.akbank.client"
#define CWIDGETS "widgets."
#define CCLASS "class "
#define CPANEL "Panel "
#define CLABEL "Label "
#define CTEXTFIELD "TextField "
#define CBUTTON "Button "
#define CBUTTONGRP "ButtonGroup "
#define CCOMBOBOX  "AkbankComboBox "
#define CCHECKBOX  "AkbankCheckBox "
#define CLOADER "com.akbank.client.staticdata.DataLoader "
#define LOADSTR "load("
#define CQUERYLSTFUNC "queryListFunction"
#define CSETQUERYLST  "setQueryString("

#define MAXCHAR   200
#define MAXLABELS 200
#define LBLMAX    20
#define LBLSIZE   40
#define MAXTXT    200
#define TXTMAX    20
#define TXTSIZE   100
#define NPANEL    10
#define MAXBTN    200
#define BTNSIZE   100

#define CINIT "initialize()"
#define CENDINIT "}"
#define CENDINIT2 "    }"
#define CBEGIN "{"
// setName("name"); --> <h1> name </h1>
#define CPAGE "setName("
// setTitle("YatirimFonuAlim_MuVMeVDview");
#define CTITLE "setTitle("
// setBounds(0, 0, 739, 599); css -> border()
#define CBOUND "setBounds("
// add(get{panelname}(), null);  <div name=panelname> ... </div>
#define CADD "add(get"
// add(get{buttonname}(), null);  <div name=buttonname> ... </div>
#define CADDPANEL "Pane"
#define CADDBUTTON "Button"
// get{buttongrp}().add(get{AkbankRadioButton}());
#define CSCROLL   "ScrollPane"
#define CSTABLE   "kbankTable get"
#define CSTABLES   "kbankSmartTable get"
#define CTABLE   "kbankTable "
#define CTABLES   "kbankSmartTable "
#define CTABLESP  "kbankSmartTableScroll"
#define CGETGRP "getAn"
#define CLAYOUT "setLayout("

#define PINIT       51
#define PPAGE       52
#define PTITLE      53
#define PBOUND      54
#define PADD        55
#define PADDPANEL   56
#define PADDBUTTON  57
#define PGETGRP     58
#define PLAYOUT     59
#define PADDSTABLE  7

#define CEXIT "Exit"
#define cexit "com.akbank.client.exit"
#define CADDEXIT "addExitEvent(get"
#define CADDEXITS "addExitEvent(this"
#define CSHOWMSG "showMessageFunction"
#define CSETVALUE "setValueFunction"
#define CDATAMERGE "dataMergeFunction"
#define CDATASPLIT "dataSplitFunction"
#define CCLEAR "clearMandatoryFunction"
#define CSETCLEAR "setMandatorysFunction"
#define CINVISIBLE "invisibleFunction"
#define CENABLE "enableFunction"
#define CDISABLE "disableFunction"
#define CVISIBLE "visibleFunction"
#define CLSTSEARCH "listSearchFunction"
#define CSIGNAL "signalFunction"
#define CADDCONDITION "addCondition("
#define CCONDITION ".Condition."
#define CSETTABNUM    "setTabNumber("
#define CSETTAB "setTabNumbers("
#define CSETTABD "setTabNumbersToDisable("
#define CSETTABS "setTabNumbersToEnable("
#define CSETMERGEELEMENTS "setMergeElements("
#define CANDCONDITION "ndCondition"

#define CSETTITLE "setTitle("
#define CSETMSG "setMessage("
#define CSETMSGTYPE "setMessageType("
#define CSETMSGOPTION "setOptionType("

#define CSETDATAELM "setDataElements("
#define CSETVALUE1 "setValue("

#define MCLICK     "setMouseClickEnabled("
#define ADDCOLUMN  ".addColumn("

#define PEXIT       71
#define pexit       72
#define PADDEXIT    73
#define PSHOWMSG    74
#define PSETVALUE   75
#define PDATAMERGE  76
#define PDATASPLIT  77
#define PCLEAR      78
#define PSETCLEAR     79
#define PINVISIBLE    90
#define PADDCONDITION 91
#define PQUERYLST     92
#define PSETTABNUM    94
#define PSETQUERYLST  95
#define PENABLE       96
#define PDISABLE      97
#define PVISIBLE      98
#define PLSTSEARCH    99
#define PSIGNAL       100
#define PANDCONDITION  101

#define CPANELDEC "AkbankTitledEmbeddedPanel get"
#define CPNLBOUNDS ".setBounds("
#define CPNLADD ".add(get"

#define panelTEXT    0
#define panelLABEL   1
#define panelRBUTTON 2
#define panelBUTTON  3
#define panelCOMBOX  4
#define panelCHKBOX  5
#define panelSCROLL  6
#define panelTABLE   7

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
fscroll,
ftable,
fexit,
fquery,
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

char buf[MAXCHAR + 1];
char symbol[MAXCHAR + 1];
char program[MAXCHAR + 1];

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

char areaName[100];
char indexname[200];

void scmandaCondition(int);
void setmandaCondition(int);
void showmsgCondition(int);
void invisibleCondition(int);
void svalueCondition(int);
void datasplitCondition(int);
void datamergeCondition(int);
void enableCondition(int);
void disableCondition(int);
void visibleCondition(int);
void lstsearchCondition(int);
void mysignalCondition(int);

struct BOUNDS {
	int x0, y0, x1, y1;
};

void boundVals(struct BOUNDS *, char *);

struct SLAYOUT {
	char *name;
	struct BOUNDS bound;
	int iadded;
	struct ADDED {
		int npanel;
		int nbutton;
		int type;
		char *addb;
	} added[30];
	char *title;
} slayout;

int ispanel;
struct SPANEL {
	int panNo;
	struct BOUNDS spnlbound;
	char *panelName;
	int ifield;
	char *setTitle;
	struct FIELDS {
		int ftype;
		char *fieldname;
	} fields[50];
} spanel[50];

struct SADDEXIT {
	char *fieldName;
	char *clearFunc;
	char *eventName;
};

struct SEXIT {
	int iscmanda;
	struct SCMANDA {
		char *sName;
		int setTabnum;
		int iaddexit;
		struct SADDEXIT saddExit[10];
		int iaddcon;
		char *addCondition[10];
	} scmanda[50];
	int isetmanda;
	struct SETMANDA {
		char *sName;
		int setTabnum;
		int iaddexit;
		struct SADDEXIT saddExit[10];
		int iaddcon;
		char *addCondition[10];
	} setmanda[50];
	int iInvisible;
	struct SINVISIBLE {
		char *sName;
		int setTabnum;
		int iaddexit;
		struct SADDEXIT saddExit[10];
		int iaddcon;
		char *addCondition[10];
	} sinvisible[50];
	int isvalue;
	struct SVALUE {
		char *sName;
		int setTabnum;
		char *dataElement;
		char *setValue;
		int iaddexit;
		struct SADDEXIT saddExit[10];
		int iaddcon;
		char *addCondition[10];
	} svalue[50];
	int ishowmsg;
	struct SHOWMSG {
		char *sName;
		int setTabnum;
		char *title;
		char *msg;
		int msgType;
		int optionType;
		int iaddexit;
		struct SADDEXIT saddExit[10];
		int iaddcon;
		char *addCondition[10];
	} showMsg[50];
	int idatasplit;
	struct DATASPLIT {
		char *sName;
		int setTabnum;
		char *dataElement;
		int iaddexit;
		struct SADDEXIT saddExit[10];
		int iaddcon;
		char *addCondition[10];
	} datasplitfunc[50];
	int idatamerge;
	struct DATAMERGE {
		char *sName;
		int setTabnum;
		char *setMergeElements;
		int iaddexit;
		struct SADDEXIT saddExit[10];
		int iaddcon;
		char *addCondition[10];
	} datamerge[50];
	int iqueryList;
	struct QUERYLST {
		char *sName;
		int setTabnum;
		char *sQuerylist;
		int iaddexit;
		struct SADDEXIT saddExit[10];
	} squeryList[50];
	int idisable;
	struct DISABLE {
		char* sName;
		char* setTabnum;
		int iaddexit;
		struct SADDEXIT saddExit[10];
		int iaddcon;
		char* addCondition[10];
	} sdisable[50];
	int ienable;
	struct ENABLE {
		char* sName;
		char* setTabnums;
		int iaddexit;
		struct SADDEXIT saddExit[10];
		int iaddcon;
		char* addCondition[10];
	} senable[50];
	int ivisible;
	struct VISIBLE {
		char* sName;
		char* setTabnum;
		int iaddexit;
		struct SADDEXIT saddExit[10];
		int iaddcon;
		char* addCondition[10];
	} svisible[50];
	int ilstsearch;
	struct LSTSEARCH {
		char* sName;
		char* setTabnum;
		int iaddexit;
		struct SADDEXIT saddExit[10];
		int iaddcon;
		char* addCondition[10];
	} slstsearch[50];
	int isignal;
	struct SIGNAL {
		char* sName;
		char* setTabnum;
		int iaddexit;
		struct SADDEXIT saddExit[10];
		int iaddcon;
		char* addCondition[10];
	} signal[50];
} sexit;

struct COLUMN {
	char* text;
	int  begincol;
	int  endcol;
	int  left;
	char* dataname;
	char* dtype;
	int  dpoint;
	int  size;
	int  colwidth;
	char* title;
	char* kdataname;
	int	 editval;
};

int istable;
struct STABLE {
	int  tableno;
	char *name;
	int  mclick;
	struct BOUNDS tableBounds;
	int  icols;
	struct COLUMN cols[20];
} stable[50];

int iscroll;
struct SSCROLL {
	int  scrollno;
	struct BOUNDS scrollBounds;
	char *name;
	char *tablename;
} scrollfield[50];

int istext;
struct STEXTFIELD {
	int txtno;
	int tabOrder;
	int txtlblno;
	char *text;
	struct BOUNDS stxtbound;
	int  enabled;
	int  required;
	char *font;
	char *dataName;
	char *name;
	char *formatter;
} stextfield[200];

int islabel;
struct SLABEL {
	int  lblno;
	int tabOrder;
	char *lbl;
	struct BOUNDS slblbound;
	char *name;
	char *text;
	char *lbltext;
} slabel[200];

int irbutton;
struct RBUTTON {
	int  rbutno;
	char *rbut;
	struct BOUNDS rbutBound;
	int  rbutEnabled;
	int  disable;
	int  rbutTab;
	char * rbutText;
	char * rbutVal;
} rbutton[50];

int igetbutton;
struct BUTTON {
	int  butNo;
	char *but;
	struct BOUNDS butBound;
	int  butTxttype;
	char *butText;
	char *butName;
	int  butLocate;
	int  butTabOrder;
} button[50];

int icombox;
struct COMBOX {
	int comboNo;
	int comboTabOrder;
	struct BOUNDS comboBounds;
	char *comboxName;
	char *dataName;
	char *setvalfname;
	char *setvalin;
	int  setkeyvals;
	char *setfname;
	char *setdnamelst;
} combox[50];

int ichkno;
struct CHECKBOX {
	int checkNo;
	int checkTabOrder;
	struct BOUNDS checkBounds;
	char *setName;
	char *dataName;
	char *setval;
	char *setuval;
	char *text;
	char *font;
} checkBox[50];

int iloader;
struct LOADER {
	int  loadNo;
	char *name;
	char *loadstr;
} loader[50];

int  isgroup;
struct SGROUP {
	int  txtno;
	int  txtlblno;
	char* text;
	char* dataName;
	char* name;
	int  txtline;
};
struct SGROUP sgroup[50];

char *buyukHarf(char *s)
{
	if (*s >= 'a' && *s <= 'z') {
		*s = (*s & 0xff) - 'a' + 'A';
	}
	return s;
}

int buyukh(char s)
{
	if(s >= 'a' && s <= 'z') {
		return (s & 0xff) - 'a' + 'A';
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

void myReplace(char *str, char s, char trg)
{
	int i, len;
	int k = 0;
	char t[200];
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
					default:
						t[k] = str[i]; k++;
					}
				}
	}
	t[k] = 0;
	strcpy(str, t);
}

void myprologue(char *program, char *title)
{
	printf("@model AkbankFace.Web.Stock.Models.%s\n", program);

	printf("@{\n");
	printf("\tLayout = Html.AkbankFace().ChooseLayout();\n");
	printf("\tViewBag.Title = \"%s\";\n", title);
	printf("\tModel.FunctionInfo.Name = \"%s\";\n", title);
	printf("}\n");

}

void myepilogue()
{
	printf("\t\t\t\t\t\t\t</div>\n");

	printf("\t\t\t\t\t\t</div>\n");
	printf("\t\t\t\t\t</div>\n");
	printf("\t\t\t\t</div>\n");
	printf("\t\t\t</div>\n");
	printf("\t\t}\n");
	printf("\t<div>\n");
}
char *indentstr()
{
	int i;
	indent[0] = 0;
	for (i = 0; i<indents; i++) {
		strcat(indent, "   ");
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
	len = (int)strlen(intext);
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
#ifdef DEBUGX
	printf("Detected %d %s\n", ret, str);
#endif
	if (ret != EOF) {
		char *pt = strstr(symbol, " ");
		if (pt && (strstr(symbol, "(") == NULL)) {
			*pt = 0;
			switch (ret) {
			case PPANEL:
				panelno++;
				strcpy(currpanel[panelno], symbol);
#ifdef DEBUGX
				printf("%d PANEL detected %s\n", panelno, currpanel[panelno]);
#endif
				lblno = 0;
				txtno = 0;
				buttonno = 0;
				buttongrpno = 0;
				Processed = 1;
				break;
			case PLABEL:
				/* save label to current panel */
				strcpy(labels[panelno][lblno], symbol);
#ifdef DEBUGX
				printf("%d %d %s LABEL detected %s\n", panelno, lblno, currpanel[panelno], labels[panelno][lblno]);
#endif
				lblno++;
				labels[panelno][lblno][0] = 0;
				Processed = 1;
				break;
			case PTEXTFIELD:
				/* save textfield to current panel */
				strcpy(txtfields[panelno][txtno], symbol);
#ifdef DEBUGX
				printf("%d %d %s TEXTFIELD detected %s\n", panelno, txtno, currpanel[panelno], txtfields[panelno][txtno]);
#endif
				txtno++;
				txtfields[panelno][txtno][0] = 0;
				Processed = 1;
				break;
			case PBUTTON:
				strcpy(buttons[panelno][buttonno], symbol);
#ifdef DEBUGX
				printf("%d %d %s BUTTON detected %s\n", panelno, buttonno, currpanel[panelno], buttons[panelno][buttonno]);
#endif
				buttonno++;
				buttons[panelno][buttonno][0] = 0;
				Processed = 1;
				break;
			case PBUTTONGRP:
				strcpy(buttongrps[panelno][buttongrpno], symbol);
#ifdef DEBUGX
				printf("%d %d %s BUTTON detected %s\n", panelno, buttongrpno, currpanel[panelno], buttongrps[panelno][buttongrpno]);
#endif
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
#ifdef DEBUGX
				printf("%d %d %s QUERYLST detected %s\n", panelno, qlistno, currpanel[panelno], qlist[panelno][qlistno]);
#endif
				qlistno++;
				qlist[panelno][qlistno][0] = 0;
				Processed = 1;
				break;
			case PTABLE:
				strcpy(table[panelno][tableno], symbol);
#ifdef DEBUGX
				printf("%d %d %s TABLE detected %s\n", panelno, tableno, currpanel[panelno], table[panelno][tableno]);
#endif
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
	if (strcmp(inp, CSHOWMSG) == 0) return PSHOWMSG;
	if (strcmp(inp, CSETVALUE) == 0) return PSETVALUE;
	if (strcmp(inp, CDATAMERGE) == 0) return PDATAMERGE;
	if (strcmp(inp, CDATASPLIT) == 0) return PDATASPLIT;
	if (strcmp(inp, CCLEAR) == 0) return PCLEAR;
	if (strcasecmp(inp, CSETCLEAR) == 0) return PSETCLEAR;
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
	len = (int)strlen(intext);
#ifdef DEBUGX
	printf("intext %s len %d\n", intext, len);
#endif
	pt = strstr(pbuf, intext);
	if (pt) {
		while (*pt != ' ' && *pt != 0) pt++;
		*pt = 0;
		strcpy(symbol, pt);
		ret = findinval(intext);
#ifdef DEBUGX
		printf("symbol %s intext %s ret %d\n", symbol, intext, ret);
#endif
	}
	return ret;
}

void mysplit(int x[], char *p, char c)
{
	char *p1, *p2;
#ifdef DEBUGX
	printf("mysplit %s\n", p);
#endif
	p1 = p2 = p;
	while (*p1 != 0 && *p1 != ',') p1++;
	*p1 = 0;
	p1++;
	x[0] = atoi(p2);
#ifdef DEBUGX
	printf("mysplit-1 %s %d\n", p2, x[0]);
#endif
	p2 = p1;
	while (*p1 != 0 && *p1 != ',') p1++;
	*p1 = 0;
	p1++;
	x[1] = atoi(p2);
#ifdef DEBUGX
	printf("mysplit-2 %s %d\n", p2, x[1]);
#endif
	p2 = p1;
	while (*p1 != 0 && *p1 != ',') p1++;
	*p1 = 0;
	p1++;
	x[2] = atoi(p2);
#ifdef DEBUGX
	printf("mysplit-3 %s %d\n", p2, x[2]);
#endif
	p2 = p1;
	while (*p1 != 0 && *p1 != ',') p1++;
	*p1 = 0;
	x[3] = atoi(p2);
#ifdef DEBUGX
	printf("mysplit-4 %s %d\n", p2, x[3]);
#endif
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
		for (j = 0; strlen(buttons[i][j]) > 0; j++)
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
		for (j = 0; strlen(buttongrps[i][j]) > 0; j++)
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
		for (j = 0; strlen(buttons[i][j]) > 0; j++)
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
				if(p) {
					p = p + strlen(CPAGE) + 1;
					// slayout.name <- "name"

					p1 = p;
					while (*p != 0 && *p != '\"') p++;
					*p = 0;
					slayout.name = (char *)(char *) calloc(1, strlen(p1) + 1);
					strcpy(slayout.name, p1);

				}
				else {
					slayout.name = (char *)calloc(1, strlen("noname") + 1);
					strcpy(slayout.name, "noname");
				}
				continue;
			}
			// CTITLE "this.setTitle("
			if (getinsym(CTITLE) == PTITLE) {
				char *p1, *p;
				p = strstr(buf, CTITLE);
				if(p) {
					p = p + strlen(CTITLE) + 1;
					p1 = p;
					while (*p != 0 && *p != '\"') p++;
					*p = 0;
					slayout.title = (char *)(char *) calloc(1, strlen(p1) + 1);
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
				p = p + strlen(CBOUND);
				if(p) {
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
				if(p) {
					p = p + strlen(CADD);
					if (strstr(buf, CADDPANEL)) {
						char pname[200];
						slayout.added[slayout.iadded].npanel = findPanel(pname, p);
						slayout.added[slayout.iadded].nbutton = EOF;
						slayout.added[slayout.iadded].type = PADDPANEL;
						slayout.added[slayout.iadded].addb =
							(char *) (char *) calloc(1, strlen(pname) + 1);
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
								(char *)calloc(1, strlen(pname) + 1);
							if(slayout.added[slayout.iadded].addb) strcpy(slayout.added[slayout.iadded].addb, pname);
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
						if(p) {
							x = findButton(bname, p);
							slayout.added[slayout.iadded].npanel = x / 100;
							slayout.added[slayout.iadded].nbutton = x % 100;
							slayout.added[slayout.iadded].type = PADDBUTTON;
							slayout.added[slayout.iadded].addb =
								(char *) (char *) calloc(1, strlen(bname) + 1);
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
				if(p) {
					p = p + strlen(CGETGRP);
					x = findGroup(addbtn, p);
					slayout.added[slayout.iadded].npanel = x / 100;
					slayout.added[slayout.iadded].nbutton = x % 100;
					slayout.added[slayout.iadded].type = PGETGRP;
					slayout.added[slayout.iadded].addb =
						(char *)(char *) (char *) calloc(1, strlen(addbtn) + 1);
					strcpy(slayout.added[slayout.iadded].addb, addbtn);
					slayout.iadded++;
					continue;
				}
			}
		}
		finit = 1;
	}
	return ret;
}


int adVarmi(int cur, char *name)
{
	int i, ret = EOF;
	switch (cur) {
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
	if(p) {
		p1 = p + strlen(CADDEXIT);
		if(p1) {
			p = p1;
			for (i = 0; i < 3; i++) {
				while (*p != ',' && *p != 0) p++;
				if(p) {*p = 0; p++;}
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
		indx = sexit.iscmanda;
		sexit.iscmanda++;
		sexit.scmanda[indx].iaddexit = 0;
		sexit.scmanda[indx].iaddcon = 0;
		sexit.scmanda[indx].sName = (char *) (char *) calloc(1, strlen(name) + 1);
		strcpy(sexit.scmanda[indx].sName, name);
	}
	if ((p = strstr(buf, CSETTAB))) {
		while (*p != '{' && *p != 0) p++;
		p++;
		p1 = p;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit.scmanda[indx].setTabnum = atoi(p1);
	}
	if ((p = strstr(buf, CADDEXIT))) {
		char a[3][100];
		char *pp;
		splitEvent(a);
		pp = a[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit.scmanda[indx].iaddexit;
		sexit.scmanda[indx].saddExit[j].fieldName =
			(char *) (char *) calloc(1, strlen(a[0]) + 1);
		strcpy(sexit.scmanda[indx].saddExit[j].fieldName, a[0]);
		sexit.scmanda[indx].saddExit[j].clearFunc =
			(char *) (char *) calloc(1, strlen(a[1]) + 1);
		strcpy(sexit.scmanda[indx].saddExit[j].clearFunc, a[1]);
		sexit.scmanda[indx].saddExit[j].eventName =
			(char *) (char *) calloc(1, strlen(a[2]) + 1);
		strcpy(sexit.scmanda[indx].saddExit[j].eventName, a[2]);
		sexit.scmanda[indx].iaddexit++;
	}
	scmandaCondition(indx);
	return indx;
}

void scmandaCondition(int indx)
{
	int  j;
	char *p, *p1, *p2, *p3;
	if ((p = strstr(buf, CADDCONDITION))) {
		p2 = buf;
		while (*p2 != 0 && (*p2 == ' ' || *p2 == '\t')) p2++;
		*(p - 1) = 0;
		p1 = p + strlen(CADDCONDITION) + 1;

		p = p1;
		while (*p != '(') p++;
		p++;
		p3 = p;
		while (*p != ')') p++;
		*p = 0;
		for (indx = 0; indx < sexit.iscmanda; indx++) {
			if (strcmp(sexit.scmanda[indx].sName, p2) == 0) {
				j = sexit.scmanda[indx].iaddcon;
				sexit.scmanda[indx].addCondition[j] =
					(char*)calloc(1, strlen(p1) + 1);
				strcpy(sexit.scmanda[indx].addCondition[j], p1);
				sexit.scmanda[indx].iaddcon++;
				j++;
				sexit.scmanda[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p2) + 1);
				strcpy(sexit.scmanda[indx].addCondition[j], p2);
				sexit.scmanda[indx].iaddcon++;
				j++;
				sexit.scmanda[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p3) + 1);
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
	if (!strstr(name, CSETCLEAR)) return EOF;
	indx = adVarmi(current, name);
	if (indx == EOF) {
		p = name;
		while (*p != 0 && *p != '(') p++;
		*p = 0;
		indx = sexit.isetmanda;
		sexit.isetmanda++;
		sexit.setmanda[indx].iaddexit = 0;
		sexit.setmanda[indx].iaddcon = 0;
		sexit.setmanda[indx].sName = (char *) (char *) calloc(1, strlen(name) + 1);
		strcpy(sexit.setmanda[indx].sName, name);
	}
	if ((p = strstr(buf, CSETTAB))) {
		while (*p != '{' && *p != 0) p++;
		p++;
		p1 = p;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit.setmanda[indx].setTabnum = atoi(p1);
	}
	if ((p = strstr(buf, CADDEXIT))) {
		char a[3][100];
		char *pp;
		splitEvent(a);
		pp = a[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit.setmanda[indx].iaddexit;
		sexit.setmanda[indx].saddExit[j].fieldName =
			(char *) (char *) calloc(1, strlen(a[0]) + 1);
		strcpy(sexit.setmanda[indx].saddExit[j].fieldName, a[0]);
		sexit.setmanda[indx].saddExit[j].clearFunc =
			(char *) calloc(1, strlen(a[1]) + 1);
		strcpy(sexit.setmanda[indx].saddExit[j].clearFunc, a[1]);
		sexit.setmanda[indx].saddExit[j].eventName =
			(char *) calloc(1, strlen(a[2]) + 1);
		strcpy(sexit.setmanda[indx].saddExit[j].eventName, a[2]);
		sexit.setmanda[indx].iaddexit++;
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
		p1 = p + strlen(CADDCONDITION) + 1;
		p = p1;
		while (*p != '(') p++;
		p++;
		p3 = p;
		while (*p != ')') p++;
		*p = 0;
		for (indx = 0; indx < sexit.isetmanda; indx++) {
			if (strcmp(sexit.setmanda[indx].sName, p2) == 0) {


				j = sexit.setmanda[indx].iaddcon;
				sexit.setmanda[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p1) + 1);
				strcpy(sexit.setmanda[indx].addCondition[j], p1);
				sexit.setmanda[indx].iaddcon++;
				j++;
				sexit.setmanda[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p2) + 1);
				strcpy(sexit.setmanda[indx].addCondition[j], p2);
				sexit.setmanda[indx].iaddcon++;
				j++;
				sexit.setmanda[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p3) + 1);
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
		sexit.showMsg[indx].sName = (char *) calloc(1, strlen(name) + 1);
		strcpy(sexit.showMsg[indx].sName, name);
	}
	if ((p = strstr(buf, CSETTAB))) {
		while (*p != '{' && *p != 0) p++;
		p++;
		p1 = p;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit.showMsg[indx].setTabnum = atoi(p1);
	}
	if ((p = strstr(buf, CSETTITLE))) {
		p1 = p + strlen(CSETTITLE) + 2;
		p = p1;
		while (*p != '\"' && *p != 0) p++;
		*p = 0;
		sexit.showMsg[indx].title = (char *) calloc(1, strlen(p1) + 1);
		strcpy(sexit.showMsg[indx].title, p1);
	}
	if ((p = strstr(buf, CSETMSG))) {
		p1 = p + strlen(CSETMSG) + 1;
		p = p1;
		while (*p != '\"' && *p != 0) p++;
		*p = 0;
		sexit.showMsg[indx].msg = (char *) calloc(1, strlen(p1) + 1);
		strcpy(sexit.showMsg[indx].msg, p1);
	}
	if ((p = strstr(buf, CSETMSGTYPE))) {
		p1 = p + strlen(CSETMSGTYPE);
		p = p1;
		while (*p != ')' && *p != 0) p++;
		*p = 0;
		sexit.showMsg[indx].msgType = atoi(p1);
	}
	if ((p = strstr(buf, CSETMSGOPTION))) {
		p1 = p + strlen(CSETMSGOPTION);
		p = p1;
		while (*p != ')' && *p != 0) p++;
		*p = 0;
		sexit.showMsg[indx].optionType = atoi(p1);
	}
	if ((p = strstr(buf, CADDEXIT))) {
		char a[3][100];
		char *pp;
		splitEvent(a);
		pp = a[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit.showMsg[indx].iaddexit;
		sexit.showMsg[indx].saddExit[j].fieldName =
			(char *) calloc(1, strlen(a[0]) + 1);
		strcpy(sexit.showMsg[indx].saddExit[j].fieldName, a[0]);
		sexit.showMsg[indx].saddExit[j].clearFunc =
			(char *) calloc(1, strlen(a[1]) + 1);
		strcpy(sexit.showMsg[indx].saddExit[j].clearFunc, a[1]);
		sexit.showMsg[indx].saddExit[j].eventName =
			(char *) calloc(1, strlen(a[2]) + 1);
		strcpy(sexit.showMsg[indx].saddExit[j].eventName, a[2]);
		sexit.showMsg[indx].iaddexit++;
	}
	showmsgCondition(indx);
	return indx;
}

void showmsgCondition(int indx)
{
	int  j;
	char *p, *p1, *p2;
	if ((p = strstr(buf, CADDCONDITION))) {
		p2 = buf;
		while (*p2 != 0 && (*p2 == ' ' || *p2 == '\t')) p2++;
		*(p - 1) = 0;
		p1 = p + strlen(CADDCONDITION) + 1;
		p = p1;
		while (*p != '(') p++;
		p++;
		p1 = p;
		while (*p != ')') p++;
		*p = 0;
#ifdef DEBUGX
		printf("SHOWMSG addcondition %s %s\n", p2, p1);
#endif
		for (indx = 0; indx<sexit.ishowmsg; indx++) {
			if (strcmp(sexit.showMsg[indx].sName, p2) == 0) {
				j = sexit.showMsg[indx].iaddcon;
				sexit.showMsg[indx].addCondition[j] =
					(char *) calloc(1, strlen(p1) + 1);
				strcpy(sexit.showMsg[indx].addCondition[j], p1);
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
		sexit.sinvisible[indx].sName = (char *) calloc(1, strlen(name) + 1);
		strcpy(sexit.sinvisible[indx].sName, name);
	}
	if ((p = strstr(buf, CSETTAB))) {
		while (*p != '{' && *p != 0) p++;
		p++;
		p1 = p;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit.sinvisible[indx].setTabnum = atoi(p1);
	}
	if ((p = strstr(buf, CADDEXIT))) {
		char a[3][100];
		char *pp;
		splitEvent(a);
		pp = a[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit.sinvisible[indx].iaddexit;
		sexit.sinvisible[indx].saddExit[j].fieldName =
			(char *) calloc(1, strlen(a[0]) + 1);
		strcpy(sexit.sinvisible[indx].saddExit[j].fieldName, a[0]);
		sexit.sinvisible[indx].saddExit[j].clearFunc =
			(char *) calloc(1, strlen(a[1]) + 1);
		strcpy(sexit.sinvisible[indx].saddExit[j].clearFunc, a[1]);
		sexit.sinvisible[indx].saddExit[j].eventName =
			(char *) calloc(1, strlen(a[2]) + 1);
		strcpy(sexit.sinvisible[indx].saddExit[j].eventName, a[2]);
		sexit.sinvisible[indx].iaddexit++;
	}
	invisibleCondition(indx);
	return indx;
}

void invisibleCondition(int indx)
{
	int  j;
	char *p, *p1, *p2, * p3;
	if ((p = strstr(buf, CADDCONDITION))) {
		p2 = buf;
		while (*p2 != 0 && (*p2 == ' ' || *p2 == '\t')) p2++;
		*(p - 1) = 0;
		p1 = p + strlen(CADDCONDITION) + 1;
		p = p1;
		while (*p != '(') p++;
		p++;
		p3 = p;
		while (*p != ')') p++;
		*p = 0;
		for (indx = 0; indx < sexit.iInvisible; indx++) {
			if (strcmp(sexit.sinvisible[indx].sName, p2) == 0) {
				j = sexit.sinvisible[indx].iaddcon;
				sexit.sinvisible[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p1) + 1);
				strcpy(sexit.sinvisible[indx].addCondition[j], p1);
				sexit.sinvisible[indx].iaddcon++;
				j++;
				sexit.sinvisible[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p2) + 1);
				strcpy(sexit.sinvisible[indx].addCondition[j], p2);
				sexit.sinvisible[indx].iaddcon++;
				j++;
				sexit.sinvisible[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p3) + 1);
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
		sexit.svalue[indx].sName = (char *) calloc(1, strlen(name) + 1);
		strcpy(sexit.svalue[indx].sName, name);
	}
	sexit.svalue[indx].setTabnum = 0;
	if ((p = strstr(buf, CSETTAB))) {
		while (*p != '{' && *p != 0) p++;
		p++;
		p1 = p;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit.svalue[indx].setTabnum = atoi(p1);
	}
	if ((p = strstr(buf, CSETDATAELM))) {
		p1 = p + strlen(CSETDATAELM) + 1;
		while (*p1 != '{' && *p1 != 0) p1++;
		p1++;
		p = p1;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit.svalue[indx].dataElement = (char *) calloc(1, strlen(p1) + 1);
		strcpy(sexit.svalue[indx].dataElement, p1);
	}
	// sexit.svalue[indx].setValue = NULL;
	if ((p = strstr(buf, CSETVALUE1))) {
		p1 = p + strlen(CSETVALUE1) + 1;
		p = p1;
		while (*p != '\"' && *p != 0) p++;
		*p = 0;
		sexit.svalue[indx].setValue = (char *) calloc(1, strlen(p1) + 1);
		strcpy(sexit.svalue[indx].setValue, p1);
	}
	if ((p = strstr(buf, CADDEXIT))) {
		char a[3][100];
		char *pp;
		splitEvent(a);
		pp = a[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit.svalue[indx].iaddexit;
		sexit.svalue[indx].saddExit[j].fieldName =
			(char *) calloc(1, strlen(a[0]) + 1);
		strcpy(sexit.svalue[indx].saddExit[j].fieldName, a[0]);
		sexit.svalue[indx].saddExit[j].clearFunc =
			(char *) calloc(1, strlen(a[1]) + 1);
		strcpy(sexit.svalue[indx].saddExit[j].clearFunc, a[1]);
		sexit.svalue[indx].saddExit[j].eventName =
			(char *) calloc(1, strlen(a[2]) + 1);
		strcpy(sexit.svalue[indx].saddExit[j].eventName, a[2]);
		sexit.svalue[indx].iaddexit++;
	}
	svalueCondition(indx);
	return indx;
}

void svalueCondition(int indx)
{
	int  j;
	char *p, *p1, *p2, * p3;
	if ((p = strstr(buf, CADDCONDITION))) {
		p2 = buf;
		while (*p2 != 0 && (*p2 == ' ' || *p2 == '\t')) p2++;
		*(p - 1) = 0;
		p1 = p + strlen(CADDCONDITION) + 1;
		p = p1;
		while (*p != '(') p++;
		p++;
		p3 = p;
		while (*p != ')') p++;
		*p = 0;

		for (indx = 0; indx < sexit.isvalue; indx++) {
			if (strcmp(sexit.svalue[indx].sName, p2) == 0) {
				j = sexit.svalue[indx].iaddcon;
				sexit.svalue[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p1) + 1);
				strcpy(sexit.svalue[indx].addCondition[j], p1);
				sexit.svalue[indx].iaddcon++;
				j++;
				sexit.svalue[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p2) + 1);
				strcpy(sexit.svalue[indx].addCondition[j], p2);
				sexit.svalue[indx].iaddcon++;
				j++;
				sexit.svalue[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p3) + 1);
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
		sexit.datasplitfunc[indx].sName = (char *) calloc(1, strlen(name) + 1);
		strcpy(sexit.datasplitfunc[indx].sName, name);
	}
	if ((p = strstr(buf, CSETTAB))) {
		while (*p != '{' && *p != 0) p++;
		p++;
		p1 = p;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit.datasplitfunc[indx].setTabnum = atoi(p1);
	}
	if ((p = strstr(buf, CSETDATAELM))) {
		p1 = p + strlen(CSETDATAELM) + 1;
		p = p1;
		while (*p != '\"' && *p != 0) p++;
		*p = 0;
		sexit.datasplitfunc[indx].dataElement = (char *) calloc(1, strlen(p1) + 1);
		strcpy(sexit.datasplitfunc[indx].dataElement, p1);
	}
	if ((p = strstr(buf, CADDEXIT))) {
		char a[3][100];
		char *pp;
		splitEvent(a);
		pp = a[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit.datasplitfunc[indx].iaddexit;
		sexit.datasplitfunc[indx].saddExit[j].fieldName =
			(char *) calloc(1, strlen(a[0]) + 1);
		strcpy(sexit.datasplitfunc[indx].saddExit[j].fieldName, a[0]);
		sexit.datasplitfunc[indx].saddExit[j].clearFunc =
			(char *) calloc(1, strlen(a[1]) + 1);
		strcpy(sexit.datasplitfunc[indx].saddExit[j].clearFunc, a[1]);
		sexit.datasplitfunc[indx].saddExit[j].eventName =
			(char *) calloc(1, strlen(a[2]) + 1);
		strcpy(sexit.datasplitfunc[indx].saddExit[j].eventName, a[2]);
		sexit.datasplitfunc[indx].iaddexit++;
	}
	datasplitCondition(indx);
	return indx;
}

void datasplitCondition(int indx)
{
	int  j;
	char *p, *p1, *p2, * p3;
	if ((p = strstr(buf, CADDCONDITION))) {
		p2 = buf;
		while (*p2 != 0 && (*p2 == ' ' || *p2 == '\t')) p2++;
		*(p - 1) = 0;
		p1 = p + strlen(CADDCONDITION) + 1;
		p = p1;
		while (*p != '(') p++;
		p++;
		p3 = p;
		while (*p != ')') p++;
		*p = 0;
		for (indx = 0; indx < sexit.idatasplit; indx++) {
			if (strcmp(sexit.datasplitfunc[indx].sName, p2) == 0) {
				j = sexit.datasplitfunc[indx].iaddcon;
				sexit.datasplitfunc[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p1) + 1);
				strcpy(sexit.datasplitfunc[indx].addCondition[j], p1);
				sexit.datasplitfunc[indx].iaddcon++;
				j++;
				sexit.datasplitfunc[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p2) + 1);
				strcpy(sexit.datasplitfunc[indx].addCondition[j], p2);
				sexit.datasplitfunc[indx].iaddcon++;
				j++;
				sexit.datasplitfunc[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p3) + 1);
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
		sexit.datamerge[indx].sName = (char *) calloc(1, strlen(name) + 1);
		strcpy(sexit.datamerge[indx].sName, name);
	}
	if ((p = strstr(buf, CSETTAB))) {
		while (*p != '{' && *p != 0) p++;
		p++;
		p1 = p;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit.datamerge[indx].setTabnum = atoi(p1);
	}
	if ((p = strstr(buf, CSETMERGEELEMENTS))) {
		p1 = p + strlen(CSETMERGEELEMENTS);
		while (*p1 != '{' && *p1 != 0) p1++;
		p1++;
		p = p1;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit.datamerge[indx].setMergeElements = (char *) calloc(1, strlen(p1) + 1);
		strcpy(sexit.datamerge[indx].setMergeElements, p1);
	}
	if ((p = strstr(buf, CADDEXIT))) {
		char a[3][100];
		char *pp;
		splitEvent(a);
		pp = a[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit.datamerge[indx].iaddexit;
		sexit.datamerge[indx].saddExit[j].fieldName =
			(char *) calloc(1, strlen(a[0]) + 1);
		strcpy(sexit.datamerge[indx].saddExit[j].fieldName, a[0]);
		sexit.datamerge[indx].saddExit[j].clearFunc =
			(char *) calloc(1, strlen(a[1]) + 1);
		strcpy(sexit.datamerge[indx].saddExit[j].clearFunc, a[1]);
		sexit.datamerge[indx].saddExit[j].eventName =
			(char *) calloc(1, strlen(a[2]) + 1);
		strcpy(sexit.datamerge[indx].saddExit[j].eventName, a[2]);
		sexit.datamerge[indx].iaddexit++;
	}
	datamergeCondition(indx);
	return indx;
}

void datamergeCondition(int indx)
{
	int  j;
	char *p, *p1, *p2, * p3;
	if ((p = strstr(buf, CADDCONDITION))) {
		p2 = buf;
		while (*p2 != 0 && (*p2 == ' ' || *p2 == '\t')) p2++;
		*(p - 1) = 0;
		p1 = p + strlen(CADDCONDITION) + 1;
		p = p1;
		while (*p != '(') p++;
		p++;
		p3 = p;
		while (*p != ')') p++;
		*p = 0;
		for (indx = 0; indx < sexit.idatamerge; indx++) {
			if (strcmp(sexit.datamerge[indx].sName, p2) == 0) {
				j = sexit.datamerge[indx].iaddcon;
				sexit.datamerge[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p1) + 1);
				strcpy(sexit.datamerge[indx].addCondition[j], p1);
				sexit.datamerge[indx].iaddcon++;
				j++;
				sexit.datamerge[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p2) + 1);
				strcpy(sexit.datamerge[indx].addCondition[j], p2);
				sexit.datamerge[indx].iaddcon++;
				j++;
				sexit.datamerge[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p3) + 1);
				strcpy(sexit.datamerge[indx].addCondition[j], p3);
				sexit.datamerge[indx].iaddcon++;
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
		indx = sexit.ienable;
		sexit.ienable++;
		sexit.senable[indx].iaddexit = 0;
		sexit.senable[indx].iaddcon = 0;
		sexit.senable[indx].sName = (char *)calloc(1, strlen(name) + 1);
		strcpy(sexit.senable[indx].sName, name);
	}
	if ((p = strstr(buf, CSETTABNUM))) {
		while (*p != '{' && *p != 0) p++;
		p++;
		p1 = p;
		while (*p != '}' && *p != 0) p++;
		*p = 0;
		sexit.senable[indx].setTabnums = (char *)calloc(1, strlen(p1) + 1);
		strcpy(sexit.senable[indx].setTabnums, p1);
		// sexit.senable[indx].setTabnum = atoi(p1);
	}
	p = strstr(buf, CADDEXIT);
	if (!p) p = strstr(buf, CADDEXITS);
	if (p) {
		char *pp;
		splitEvent(asplit);
		pp = asplit[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit.senable[indx].iaddexit;
		sexit.senable[indx].saddExit[j].fieldName =
			(char *)calloc(1, strlen(asplit[0]) + 1);
		strcpy(sexit.senable[indx].saddExit[j].fieldName, asplit[0]);
		sexit.senable[indx].saddExit[j].clearFunc =
			(char *)calloc(1, strlen(asplit[1]) + 1);
		if(sexit.senable[indx].saddExit[j].clearFunc) strcpy(sexit.senable[indx].saddExit[j].clearFunc, (char*)asplit[1]);
		sexit.senable[indx].saddExit[j].eventName =
			(char *)calloc(1, strlen(asplit[2]) + 1);
		if(sexit.senable[indx].saddExit[j].eventName) strcpy(sexit.senable[indx].saddExit[j].eventName, (char*)asplit[2]);
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
		for (indx = 0; indx < sexit.ienable; indx++) {
			if (strcmp(sexit.senable[indx].sName, p2) == 0) {
				j = sexit.senable[indx].iaddcon;
				sexit.senable[indx].addCondition[j] =
					(char *)calloc(1, strlen(p1) + 1);
				strcpy(sexit.senable[indx].addCondition[j], p1);
				j++;
				sexit.senable[indx].addCondition[j] =
					(char *)calloc(1, strlen(p2) + 1);
				strcpy(sexit.senable[indx].addCondition[j], p2);
				j++;
				sexit.senable[indx].addCondition[j] =
					(char *)calloc(1, strlen(p3) + 1);
				strcpy(sexit.senable[indx].addCondition[j], p3);
				sexit.senable[indx].iaddcon++;
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
		indx = sexit.idisable;
		sexit.idisable++;
		sexit.sdisable[indx].iaddexit = 0;
		sexit.sdisable[indx].iaddcon = 0;
		sexit.sdisable[indx].sName = (char *)calloc(1, strlen(name) + 1);
		strcpy(sexit.sdisable[indx].sName, name);
	}
	if ((p = strstr(buf, CSETTAB))) {
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
		char *pp;
		splitEvent(asplit);
		pp = asplit[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit.sdisable[indx].iaddexit;
		sexit.sdisable[indx].saddExit[j].fieldName =
			(char *)calloc(1, strlen(asplit[0]) + 1);
		strcpy(sexit.sdisable[indx].saddExit[j].fieldName, asplit[0]);
		sexit.sdisable[indx].saddExit[j].clearFunc =
			(char *)calloc(1, strlen(asplit[1]) + 1);
		if (sexit.sdisable[indx].saddExit[j].clearFunc) strcpy(sexit.sdisable[indx].saddExit[j].clearFunc, (char*)asplit[1]);
		sexit.sdisable[indx].saddExit[j].eventName =
			(char *)calloc(1, strlen(asplit[2]) + 1);
		if(sexit.sdisable[indx].saddExit[j].eventName) strcpy(sexit.sdisable[indx].saddExit[j].eventName, (char*)asplit[2]);
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
		p1 = p + strlen(CADDCONDITION) + 1;
		while (*p1 != ' ') p1++;
		p = p1;
		while (*p != '(') p++;
		*p = 0;
		p++;
		p3 = p;
		while (*p != ')') p++;
		*p = 0;
		for (indx = 0; indx < sexit.idisable; indx++) {
			if (strcmp(sexit.sdisable[indx].sName, p2) == 0) {
				j = sexit.sdisable[indx].iaddcon;
				sexit.sdisable[indx].addCondition[j] =
					(char *)calloc(1, strlen(p1) + 1);
				strcpy(sexit.sdisable[indx].addCondition[j], p1);
				j++;
				sexit.sdisable[indx].addCondition[j] =
					(char *)calloc(1, strlen(p2) + 1);
				strcpy(sexit.sdisable[indx].addCondition[j], p2);
				j++;
				sexit.sdisable[indx].addCondition[j] =
					(char *)calloc(1, strlen(p3) + 1);
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
	char asplit[3][100];
	if (!strstr(name, CVISIBLE)) return EOF;
	indx = adVarmi(current, name);
	if (indx == EOF) {
		indx = sexit.ivisible;
		sexit.ivisible++;
		sexit.svisible[indx].iaddexit = 0;
		sexit.svisible[indx].iaddcon = 0;
		sexit.svisible[indx].sName = (char *)calloc(1, strlen(name) + 1);
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
		char *pp;
		splitEvent(asplit);
		pp = asplit[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit.svisible[indx].iaddexit;
		sexit.svisible[indx].saddExit[j].fieldName =
			(char *)calloc(1, strlen(asplit[0]) + 1);
		strcpy(sexit.svisible[indx].saddExit[j].fieldName, asplit[0]);
		sexit.svisible[indx].saddExit[j].clearFunc =
			(char *)calloc(1, strlen(asplit[1]) + 1);
		if(sexit.svisible[indx].saddExit[j].clearFunc) strcpy(sexit.svisible[indx].saddExit[j].clearFunc, (char*)asplit[1]);
		sexit.svisible[indx].saddExit[j].eventName =
			(char *)calloc(1, strlen(asplit[2]) + 1);
		if(sexit.svisible[indx].saddExit[j].eventName) strcpy(sexit.svisible[indx].saddExit[j].eventName, (char*)asplit[2]);
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
		p1 = p + strlen(CADDCONDITION) + 1;
		while (*p1 != ' ') p1++;
		p = p1;
		while (*p != '(') p++;
		*p = 0;
		p++;
		p3 = p;
		while (*p != ')') p++;
		*p = 0;
		for (indx = 0; indx < sexit.ivisible; indx++) {
			if (strcmp(sexit.svisible[indx].sName, p2) == 0) {
				j = sexit.svisible[indx].iaddcon;
				sexit.svisible[indx].addCondition[j] =
					(char *)calloc(1, strlen(p1) + 1);
				strcpy(sexit.svisible[indx].addCondition[j], p1);
				j++;
				sexit.svisible[indx].addCondition[j] =
					(char *)calloc(1, strlen(p2) + 1);
				strcpy(sexit.svisible[indx].addCondition[j], p2);
				j++;
				sexit.svisible[indx].addCondition[j] =
					(char *)calloc(1, strlen(p3) + 1);
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
	char asplit[3][100];
	if (!strstr(name, CLSTSEARCH)) return EOF;
	indx = adVarmi(current, name);
	if (indx == EOF) {
		indx = sexit.ilstsearch;
		sexit.ilstsearch++;
		sexit.slstsearch[indx].iaddexit = 0;
		sexit.slstsearch[indx].iaddcon = 0;
		sexit.slstsearch[indx].sName = (char *)calloc(1, strlen(name) + 1);
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
		char *pp;
		splitEvent(asplit);
		pp = asplit[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit.slstsearch[indx].iaddexit;
		sexit.slstsearch[indx].saddExit[j].fieldName =
			(char *)calloc(1, strlen(asplit[0]) + 1);
		strcpy(sexit.slstsearch[indx].saddExit[j].fieldName, asplit[0]);
		sexit.slstsearch[indx].saddExit[j].clearFunc =
			(char *)calloc(1, strlen(asplit[1]) + 1);
		if(sexit.slstsearch[indx].saddExit[j].clearFunc) strcpy(sexit.slstsearch[indx].saddExit[j].clearFunc, (char*)asplit[1]);
		sexit.slstsearch[indx].saddExit[j].eventName =
			(char *)calloc(1, strlen(asplit[2]) + 1);
		if(sexit.slstsearch[indx].saddExit[j].eventName) strcpy(sexit.slstsearch[indx].saddExit[j].eventName, (char*)asplit[2]);
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
		p1 = p + strlen(CADDCONDITION) + 1;
		while (*p1 != ' ') p1++;
		p = p1;
		while (*p != '(') p++;
		*p = 0;
		p++;
		p3 = p;
		while (*p != ')') p++;
		*p = 0;
		for (indx = 0; indx < sexit.ilstsearch; indx++) {
			if (strcmp(sexit.slstsearch[indx].sName, p2) == 0) {
				j = sexit.slstsearch[indx].iaddcon;
				sexit.slstsearch[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p1) + 1);
				strcpy(sexit.slstsearch[indx].addCondition[j], p1);
				sexit.slstsearch[indx].iaddcon++;
				j++;
				sexit.slstsearch[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p2) + 1);
				strcpy(sexit.slstsearch[indx].addCondition[j], p2);
				sexit.slstsearch[indx].iaddcon++;
				j++;
				sexit.slstsearch[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p3) + 1);
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
	char asplit[3][100];
	if (!strstr(name, CSIGNAL)) return EOF;
	indx = adVarmi(current, name);
	if (indx == EOF) {
		indx = sexit.isignal;
		sexit.isignal++;
		sexit.signal[indx].iaddexit = 0;
		sexit.signal[indx].iaddcon = 0;
		sexit.signal[indx].sName = (char *)calloc(1, strlen(name) + 1);
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
		char *pp;
		splitEvent(asplit);
		pp = asplit[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit.signal[indx].iaddexit;
		sexit.signal[indx].saddExit[j].fieldName =
			(char *)calloc(1, strlen(asplit[0]) + 1);
		strcpy(sexit.signal[indx].saddExit[j].fieldName, asplit[0]);
		sexit.signal[indx].saddExit[j].clearFunc =
			(char *)calloc(1, strlen(asplit[1]) + 1);
		if(sexit.signal[indx].saddExit[j].clearFunc) strcpy((char *)sexit.signal[indx].saddExit[j].clearFunc, asplit[1]);
		sexit.signal[indx].saddExit[j].eventName =
			(char *)calloc(1, strlen(asplit[2]) + 1);
		if(sexit.signal[indx].saddExit[j].eventName) strcpy((char *)sexit.signal[indx].saddExit[j].eventName, asplit[2]);
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
		p1 = p + strlen(CADDCONDITION) + 1;
		while (*p1 != ' ') p1++;
		p = p1;
		while (*p != '(') p++;
		*p = 0;
		p++;
		p3 = p;
		while (*p != ')') p++;
		*p = 0;
		for (indx = 0; indx < sexit.isignal; indx++) {
			if (strcmp(sexit.signal[indx].sName, p2) == 0) {
				j = sexit.signal[indx].iaddcon;
				sexit.signal[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p1) + 1);
				strcpy(sexit.signal[indx].addCondition[j], p1);
				sexit.signal[indx].iaddcon++;
				j++;
				sexit.signal[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p2) + 1);
				strcpy(sexit.signal[indx].addCondition[j], p2);
				sexit.signal[indx].iaddcon++;
				j++;
				sexit.signal[indx].addCondition[j] =
					(char*)calloc(1, (int)strlen(p3) + 1);
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
	char asplit[3][100];
	if (!strstr(name, CADDEXIT)) return EOF;
	indx = adVarmi(current, name);
	splitEvent(asplit);
	pp = asplit[0];
	while (*pp != 0 && *pp != '(') pp++;
	*pp = 0;
	switch (current) {
	case PDATASPLIT:
		j = sexit.datasplitfunc[indx].iaddexit;
		sexit.datasplitfunc[indx].saddExit[j].fieldName =
			(char *) calloc(1, strlen(asplit[0]) + 1);
		strcpy(sexit.datasplitfunc[indx].saddExit[j].fieldName, asplit[0]);
		sexit.datasplitfunc[indx].saddExit[j].clearFunc =
			(char *) calloc(1, strlen(asplit[1]) + 1);
		strcpy(sexit.datasplitfunc[indx].saddExit[j].clearFunc, asplit[1]);
		sexit.datasplitfunc[indx].saddExit[j].eventName =
			(char *) calloc(1, strlen(asplit[2]) + 1);
		strcpy(sexit.datasplitfunc[indx].saddExit[j].eventName, asplit[2]);
		sexit.datasplitfunc[indx].iaddexit++;
		break;
	case PDATAMERGE:
		j = sexit.datamerge[indx].iaddexit;
		sexit.datamerge[indx].saddExit[j].fieldName =
			(char *) calloc(1, strlen(asplit[0]) + 1);
		strcpy(sexit.datamerge[indx].saddExit[j].fieldName, asplit[0]);
		sexit.datamerge[indx].saddExit[j].clearFunc =
			(char *) calloc(1, strlen(asplit[1]) + 1);
		strcpy(sexit.datamerge[indx].saddExit[j].clearFunc, asplit[1]);
		sexit.datamerge[indx].saddExit[j].eventName =
			(char *) calloc(1, strlen(asplit[2]) + 1);
		strcpy(sexit.datamerge[indx].saddExit[j].eventName, asplit[2]);
		sexit.datamerge[indx].iaddexit++;
		break;
	case PSETVALUE:
		j = sexit.svalue[indx].iaddexit;
		sexit.svalue[indx].saddExit[j].fieldName =
			(char *) calloc(1, strlen(asplit[0]) + 1);
		strcpy(sexit.svalue[indx].saddExit[j].fieldName, asplit[0]);
		sexit.svalue[indx].saddExit[j].clearFunc =
			(char *) calloc(1, strlen(asplit[1]) + 1);
		strcpy(sexit.svalue[indx].saddExit[j].clearFunc, asplit[1]);
		sexit.svalue[indx].saddExit[j].eventName =
			(char *) calloc(1, strlen(asplit[2]) + 1);
		strcpy(sexit.svalue[indx].saddExit[j].eventName, asplit[2]);
		sexit.svalue[indx].iaddexit++;
		break;
	case PSETCLEAR:
		j = sexit.setmanda[indx].iaddexit;
		sexit.setmanda[indx].saddExit[j].fieldName =
			(char *) calloc(1, strlen(asplit[0]) + 1);
		strcpy(sexit.setmanda[indx].saddExit[j].fieldName, asplit[0]);
		sexit.setmanda[indx].saddExit[j].clearFunc =
			(char *) calloc(1, strlen(asplit[1]) + 1);
		strcpy(sexit.setmanda[indx].saddExit[j].clearFunc, asplit[1]);
		sexit.setmanda[indx].saddExit[j].eventName =
			(char *) calloc(1, strlen(asplit[2]) + 1);
		strcpy(sexit.setmanda[indx].saddExit[j].eventName, asplit[2]);
		sexit.setmanda[indx].iaddexit++;
		break;
	case PCLEAR:
		j = sexit.scmanda[indx].iaddexit;
		sexit.scmanda[indx].saddExit[j].fieldName =
			(char *) calloc(1, strlen(asplit[0]) + 1);
		strcpy(sexit.scmanda[indx].saddExit[j].fieldName, asplit[0]);
		sexit.scmanda[indx].saddExit[j].clearFunc =
			(char *) calloc(1, strlen(asplit[1]) + 1);
		strcpy(sexit.scmanda[indx].saddExit[j].clearFunc, asplit[1]);
		sexit.scmanda[indx].saddExit[j].eventName =
			(char *) calloc(1, strlen(asplit[2]) + 1);
		strcpy(sexit.scmanda[indx].saddExit[j].eventName, asplit[2]);
		sexit.scmanda[indx].iaddexit++;
		break;
	case PINVISIBLE:
		j = sexit.sinvisible[indx].iaddexit;
		sexit.sinvisible[indx].saddExit[j].fieldName =
			(char *) calloc(1, strlen(asplit[0]) + 1);
		strcpy(sexit.sinvisible[indx].saddExit[j].fieldName, asplit[0]);
		sexit.sinvisible[indx].saddExit[j].clearFunc =
			(char *) calloc(1, strlen(asplit[1]) + 1);
		strcpy(sexit.sinvisible[indx].saddExit[j].clearFunc, asplit[1]);
		sexit.sinvisible[indx].saddExit[j].eventName =
			(char *) calloc(1, strlen(asplit[2]) + 1);
		strcpy(sexit.sinvisible[indx].saddExit[j].eventName, asplit[2]);
		sexit.sinvisible[indx].iaddexit++;
		break;
	case PSHOWMSG:
		j = sexit.showMsg[indx].iaddexit;
		sexit.showMsg[indx].saddExit[j].fieldName =
			(char *) calloc(1, strlen(asplit[0] + 1));
		strcpy(sexit.showMsg[indx].saddExit[j].fieldName, asplit[0]);
		sexit.showMsg[indx].saddExit[j].clearFunc =
			(char *) calloc(1, strlen(asplit[1]) + 1);
		strcpy(sexit.showMsg[indx].saddExit[j].clearFunc, asplit[1]);
		sexit.showMsg[indx].saddExit[j].eventName =
			(char *) calloc(1, strlen(asplit[2]) + 1);
		strcpy(sexit.showMsg[indx].saddExit[j].eventName, asplit[2]);
		sexit.showMsg[indx].iaddexit++;
		break;
	case PQUERYLSTFUNC:
		j = sexit.squeryList[indx].iaddexit;
		sexit.squeryList[indx].saddExit[j].fieldName =
			(char *) calloc(1, strlen(asplit[0]) + 1);
		strcpy(sexit.squeryList[indx].saddExit[j].fieldName, asplit[0]);
		sexit.squeryList[indx].saddExit[j].clearFunc =
			(char *) calloc(1, strlen(asplit[1]) + 1);
		strcpy(sexit.squeryList[indx].saddExit[j].clearFunc, asplit[1]);
		sexit.squeryList[indx].saddExit[j].eventName =
			(char *) calloc(1, strlen(asplit[2]) + 1);
		strcpy(sexit.squeryList[indx].saddExit[j].eventName, asplit[2]);
		sexit.squeryList[indx].iaddexit++;
		break;
	case PENABLE:
		j = sexit.senable[indx].iaddexit;
		sexit.senable[indx].saddExit[j].fieldName =
			(char *)calloc(1, strlen(asplit[0]) + 1);
		strcpy(sexit.senable[indx].saddExit[j].fieldName, asplit[0]);
		sexit.senable[indx].saddExit[j].clearFunc =
			(char *)calloc(1, strlen(asplit[1]) + 1);
		strcpy(sexit.senable[indx].saddExit[j].clearFunc, asplit[1]);
		sexit.senable[indx].saddExit[j].eventName =
			(char *)calloc(1, strlen(asplit[2]) + 1);
		strcpy(sexit.senable[indx].saddExit[j].eventName, asplit[2]);
		sexit.senable[indx].iaddexit++;
		break;
	case PDISABLE:
		j = sexit.sdisable[indx].iaddexit;
		sexit.sdisable[indx].saddExit[j].fieldName =
			(char *)calloc(1, strlen(asplit[0]) + 1);
		strcpy(sexit.sdisable[indx].saddExit[j].fieldName, asplit[0]);
		sexit.senable[indx].saddExit[j].clearFunc =
			(char *)calloc(1, strlen(asplit[1]) + 1);
		strcpy(sexit.sdisable[indx].saddExit[j].clearFunc, asplit[1]);
		sexit.sdisable[indx].saddExit[j].eventName =
			(char *)calloc(1, strlen(asplit[2]) + 1);
		strcpy(sexit.sdisable[indx].saddExit[j].eventName, asplit[2]);
		sexit.sdisable[indx].iaddexit++;
		break;
	case PVISIBLE:
		j = sexit.svisible[indx].iaddexit;
		sexit.svisible[indx].saddExit[j].fieldName =
			(char *)calloc(1, strlen(asplit[0]) + 1);
		strcpy(sexit.svisible[indx].saddExit[j].fieldName, asplit[0]);
		sexit.svisible[indx].saddExit[j].clearFunc =
			(char *)calloc(1, strlen(asplit[1]) + 1);
		strcpy(sexit.svisible[indx].saddExit[j].clearFunc, asplit[1]);
		sexit.svisible[indx].saddExit[j].eventName =
			(char *)calloc(1, strlen(asplit[2]) + 1);
		strcpy(sexit.svisible[indx].saddExit[j].eventName, asplit[2]);
		sexit.svisible[indx].iaddexit++;
		break;
	case PLSTSEARCH:
		j = sexit.slstsearch[indx].iaddexit;
		sexit.slstsearch[indx].saddExit[j].fieldName =
			(char *)calloc(1, strlen(asplit[0]) + 1);
		strcpy(sexit.slstsearch[indx].saddExit[j].fieldName, asplit[0]);
		sexit.slstsearch[indx].saddExit[j].clearFunc =
			(char *)calloc(1, strlen(asplit[1]) + 1);
		strcpy(sexit.slstsearch[indx].saddExit[j].clearFunc, asplit[1]);
		sexit.slstsearch[indx].saddExit[j].eventName =
			(char *)calloc(1, strlen(asplit[2]) + 1);
		strcpy(sexit.slstsearch[indx].saddExit[j].eventName, asplit[2]);
		sexit.slstsearch[indx].iaddexit++;
		break;
	case PSIGNAL:
		j = sexit.signal[indx].iaddexit;
		sexit.signal[indx].saddExit[j].fieldName =
			(char *)calloc(1, strlen(asplit[0]) + 1);
		strcpy(sexit.signal[indx].saddExit[j].fieldName, asplit[0]);
		sexit.signal[indx].saddExit[j].clearFunc =
			(char *)calloc(1, strlen(asplit[1]) + 1);
		strcpy(sexit.signal[indx].saddExit[j].clearFunc, asplit[1]);
		sexit.signal[indx].saddExit[j].eventName =
			(char *)calloc(1, strlen(asplit[2]) + 1);
		strcpy(sexit.signal[indx].saddExit[j].eventName, asplit[2]);
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
		sexit.squeryList[indx].sName = (char *) calloc(1, strlen(name) + 1);
		strcpy(sexit.squeryList[indx].sName, name);
	}
	if ((p = strstr(buf, CSETTAB))) {
		p1 = strstr(buf, CSETTAB);
		p = p1 + strlen(CSETTAB);
		p1 = p;
		while (*p != ')' && *p != 0) p++;
		*p = 0;
		sexit.squeryList[indx].setTabnum = atoi(p1);
	}
	if ((p = strstr(buf, CADDEXIT))) {
		splitEvent(a);
		pp = a[0];
		while (*pp != 0 && *pp != '(') pp++;
		*pp = 0;
		j = sexit.squeryList[indx].iaddexit;
		sexit.squeryList[indx].saddExit[j].fieldName =
			(char *) calloc(1, strlen(a[0]) + 1);
		strcpy(sexit.squeryList[indx].saddExit[j].fieldName, a[0]);
		sexit.squeryList[indx].saddExit[j].clearFunc =
			(char *) calloc(1, strlen(a[1]) + 1);
		strcpy(sexit.squeryList[indx].saddExit[j].clearFunc, a[1]);
		sexit.squeryList[indx].saddExit[j].eventName =
			(char *) calloc(1, strlen(a[2]) + 1);
		strcpy(sexit.squeryList[indx].saddExit[j].eventName, a[2]);
		sexit.squeryList[indx].iaddexit++;
	}
	if ((p = strstr(buf, CSETQUERYLST))) {
		p1 = strstr(buf, CSETQUERYLST);
		p = p1 + strlen(CSETQUERYLST) + 1;
		p1 = p;
		p = strstr(p, "\")");
		if (p) {
			p += 2;
			*p = 0;
		}
		// sexit.squeryList[indx].sName = (char *) calloc(1, strlen(name)+1);
		// strcpy(sexit.squeryList[indx].sName, name);
		sexit.squeryList[indx].sQuerylist = (char *) calloc(1, strlen(p1) + 1);
		strcpy(sexit.squeryList[indx].sQuerylist, p1);
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
			if (ret != EOF) { Processed = 1; break; }
			if (strstr(buf, CENDINIT) && !strstr(buf, CBEGIN)) {
				Processed = 1;
				break;
			}
			Processed = 1;
			if (strstr(buf, cexit) || strstr(buf, "new") || (current != EOF)) {
				if ((strstr(buf, cexit) || strstr(buf, "new")) &&
					!(strstr(buf, CCONDITION) || strstr(buf, CSETTABNUM) || strstr(buf, CSETTAB) ||
					strstr(buf, CSETTABD) || strstr(buf, CSETTABS) || strstr(buf, CADDEXIT) ||
					strstr(buf, CADDEXITS))) {
					p = strstr(buf, cexit);
					if (!p) p = strstr(buf, "new");
					if (p) {
						p1 = strstr(p, " ");
						if (p1) {
							p1++;
							p = strstr(p1, " ");
							*p = 0;
							strcpy(name, p1);
						}
					}
					else name[0] = 0;
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
	p1 = p + strlen(txt);
	p = strstr(p1, "(");
	*p = 0;
	strcpy(xname, p1);
}

int getPanelno(char *xname)
{
	int len = (int)strlen(xname);
	char *p = xname;
	while (!(*p >= '0' && *p <= '9')) {
		p++;
		if (*p == 0) break;
	}
	if (strlen(p) > 0) {
		return atoi(p);
	}
	return 0;
}

int fieldtype(char *p)
{
	if (strstr(p, "TextField")) return panelTEXT;
	if (strstr(p, "Labe")) return panelLABEL;
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
		indx = ispanel;
		spanel[indx].panNo = getPanelno(xname);

		ispanel++;
		spanel[indx].panelName = (char *) calloc(1, strlen(xname) + 1);
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
				p = p1 + strlen(CPNLADD);
				p1 = p;
				while (*p != 0 && *p != '(') p++;
				*p = 0;
				ff = fieldtype(p1);
				j = spanel[indx].ifield;
				spanel[indx].fields[j].fieldname = (char *) calloc(1, strlen(p1) + 1);
				strcpy(spanel[indx].fields[j].fieldname, p1);
				spanel[indx].fields[j].ftype = ff;
				spanel[indx].ifield++;
				continue;
			}
			spanel[indx].setTitle = NULL;
			if (strstr(buf, panelTITLE)) {
				p1 = strstr(buf, panelTITLE);
				if (p1) {
					p = p1 + strlen(panelTITLE) + 1;
					p1 = p;
					while (*p != 0 && *p != '\"') p++;
					*p = 0;
					spanel[indx].setTitle = (char *)calloc(1, strlen(p1) + 1);
					strcpy(spanel[indx].setTitle, p1);
				}
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

void boundVals(struct BOUNDS *s, char * txt)
{
	char *p, *p1;
	int x[4];

	p = strstr(buf, txt);
	p1 = p + strlen(txt);
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
	p1 = p + strlen(txt);
	p = strstr(p1, "(");
	if (p) *p = 0;
	p = strstr(p1, " =");
	if (p) *p = 0;
	strcpy(xname, p1);
}

int getLabel(char *xname)
{
	int i, j;
	// label dizisi icinde karsit deger var mi
	for (i = 0; i <= panelno; i++) {
		for (j = 0; j <= lblno; j++)
			if (strlen(labels[i][j]) > 0)
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
			if (strlen(txtfields[i][j]) > 0)
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
			if (strlen(buttongrps[i][j]) > 0)
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
			if (strlen(buttons[i][j]) > 0)
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
			if (strlen(combobox[i][j]) > 0)
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
			if (strlen(chkBox[i][j]) > 0)
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
			if (strlen(tscroll[i][j]) > 0)
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
			if (strlen(table[i][j]) > 0)
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
			if (strlen(loads[i][j]) > 0)
				if (strcasecmp(loads[i][j], xname) == 0)
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

#define SETVALFNAME "setValueFieldName("
#define SETVALIN "setValueInContext("
#define SETKEYVAL "setUseKeyValues("
#define SETFNAME "setIdFieldName("
#define SETDNAMELST "setDataNameForList("

int ColumnVals(struct COLUMN *c, char *addcol)
{
	char *p, *p1;
	if (strstr(buf, addcol)) {
		p = strstr(buf, addcol);
		p1 = p + strlen(addcol) + 1;
		p = p1;
		while (*p != 0 && *p != '\"') p++;
		*p = 0;
		c->text = (char *) calloc(1, strlen(p1));
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
		c->dataname = (char *) calloc(1, strlen(p1) + 1);
		strcpy(c->dataname, p1);
		p1 = p + 2;
		p = p1;
		while (*p != 0 && *p != ',') p++;
		*p = 0;
		c->dtype = (char *) calloc(1, strlen(p1) + 1);
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
		slabel[indx].lbl = (char *) calloc(1, strlen(xname) + 1);
		strcpy(slabel[indx].lbl, xname);
		slabel[indx].lbltext = 0;
		slabel[indx].text = "";
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
				p1 = strstr(buf, LBLNAME) + strlen(LBLNAME);
				p1++;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				slabel[indx].name = (char *) calloc(1, strlen(p1) + 1);
				strcpy(slabel[indx].name, p1);
				continue;
			}
			if (strstr(buf, LBLTXT)) {
				// LBLTEXT setText found get text
				p1 = strstr(buf, LBLTXT);
				p1 = p1 + strlen(LBLTXT);
				p1++;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				if (p1) {
					slabel[indx].text = (char *)calloc(1, strlen(p1) + 1);
					strcpy(slabel[indx].text, p1);
				}
				else {
					slabel[indx].text = "";
				}
				continue;
			}
			if (strstr(buf, CSETTABNUM)) {
				p1 = strstr(buf, CSETTABNUM) + strlen(CSETTABNUM);
				p1++;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				slabel[indx].tabOrder = atoi(p1);
			}
		}
		flblfunc = 0;
	}
	if ((ftxtfunc == 0) && strstr(buf, CTXTFUNC)) {
		ftxtfunc = 1;
		Processed = 1;
		getName(xname, CTXTFUNC);
		if (strlen(xname) < 1) return ret;
		indx = istext;
		stextfield[indx].txtno = getTextField(xname);
		stextfield[indx].text = (char *) calloc(1, strlen(xname) + 1);
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
				p1 = p1 + strlen(TXTENABLED);
				if (strncasecmp(p1, "false", 5) == 0)
					stextfield[indx].enabled = false;
				else
					stextfield[indx].enabled = true;
				continue;
			}
			if (strstr(buf, TXTREQ)) {
				p1 = strstr(buf, TXTREQ);
				p1 = p1 + strlen(TXTREQ);
				if (strncasecmp(p1, "false", 5) == 0)
					stextfield[indx].required = false;
				else
					stextfield[indx].required = true;
			}
			if (strstr(buf, TXTFONT)) {
				// move font value
				p1 = strstr(buf, TXTFONT);
				p1 = p1 + strlen(TXTFONT);
				while (*p1 != 0 && *p1 != '(') p1++;
				p1++;
				p = p1;
				while (*p != 0 && *p != ')') p++;
				*p = 0;
				stextfield[indx].font = (char *) calloc(1, strlen(p1) + 1);
				strcpy(stextfield[indx].font, p1);
				continue;
			}
			if (strstr(buf, TXTDNAME)) {
				// move data Name value

				p1 = strstr(buf, TXTDNAME);
				p1 = p1 + strlen(TXTDNAME);
				p1++;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				stextfield[indx].dataName = (char *) calloc(1, strlen(p1) + 1);
				strcpy(stextfield[indx].dataName, p1);
				// label icin text sira no ekle
				// if (slabel[islabel - 1].lbltext == 0) {
				//	slabel[islabel - 1].lbltext = (char *) calloc(1, strlen(p1) + 1);
				//	strcpy(slabel[islabel - 1].lbltext, p1);
				// }
				continue;
			}
			if (strstr(buf, TXTNAME)) {
				// move Name value
				p1 = strstr(buf, TXTNAME);
				p1 = p1 + strlen(TXTNAME);
				if(p1) {
					p1++;
					p = p1;
					while (*p != 0 && *p != '\"') p++;
					*p = 0;
					stextfield[indx].name = (char *) calloc(1, strlen(p1) + 1);
					strcpy(stextfield[indx].name, p1);
					continue;
				}
			}
			if (strstr(buf, TXTFRMT)) {
				// move formatter value
				p1 = strstr(buf, TXTFRMT);
				p = p1 + strlen(TXTFRMT);
				p1 = strstr(p, TXTCONVERTER);
				if (p1) {
					p1 = p1 + strlen(TXTCONVERTER);
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
				}
				if(p1) {
					stextfield[indx].formatter = (char *) calloc(1, strlen(p1) + 1);
					strcpy(stextfield[indx].formatter, p1);
				}
				else {
					stextfield[indx].formatter = 0;
					continue;
				}
				if (strstr(buf, CSETTABNUM)) {
					p1 = strstr(buf, CSETTABNUM) + strlen(CSETTABNUM);
					p1++;
					p = p1;
					while (*p != 0 && *p != '\"') p++;
					*p = 0;
					stextfield[indx].tabOrder = atoi(p1);
				}
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
		rbutton[indx].rbut = (char *) calloc(1, strlen(xname) + 1);
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
				p1 = strstr(buf, RBUTENABLED) + strlen(RBUTENABLED);
				if (strncasecmp(p1, "false", 5) == 0)
					rbutton[indx].rbutEnabled = false;
				else
					rbutton[indx].rbutEnabled = true;
				continue;
			}
			if (strstr(buf, RBUTDISABLE)) {
				// rbutton enabled
				p1 = strstr(buf, RBUTDISABLE) + strlen(RBUTDISABLE);
				if (strncasecmp(p1, "false", 5) == 0)
					rbutton[indx].disable = false;
				else
					rbutton[indx].disable = true;
				continue;
			}
			if (strstr(buf, RBUTTAB)) {
				// rbutton tab Order
				p1 = strstr(buf, RBUTTAB) + strlen(RBUTTAB);
				// p1++;
				p = p1;
				while (*p != 0 && *p != ')') p++;
				*p = 0;
				rbutton[indx].rbutTab = atoi(p1);
				continue;
			}
			if (strstr(buf, RBUTTXT)) {
				// rbutton text
				p1 = strstr(buf, RBUTTXT) + strlen(RBUTTXT);
				p1++;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				rbutton[indx].rbutText = (char *) calloc(1, strlen(p1) + 1);
				strcpy(rbutton[indx].rbutText, p1);
				continue;
			}
			if (strstr(buf, RBUTSVAL)) {
				// rbutton text
				p1 = strstr(buf, RBUTSVAL) + strlen(RBUTSVAL);
				p1++;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				rbutton[indx].rbutVal = (char *) calloc(1, strlen(p1) + 1);
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
		button[indx].but = (char *) calloc(1, strlen(xname) + 1);
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
				p1 = strstr(buf, BUTTXT) + strlen(BUTTXT);
				p1++;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				button[indx].butText = (char *) calloc(1, strlen(p1) + 1);
				strcpy(button[indx].butText, p1);
				continue;
			}
			if (strstr(buf, BUTNAME)) {
				// button text
				p1 = strstr(buf, BUTNAME) + strlen(BUTNAME);
				p1++;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				button[indx].butName = (char *) calloc(1, strlen(p1) + 1);
				strcpy(button[indx].butName, p1);
				continue;
			}
			if (strstr(buf, BUTLOCATE)) {
				// button locater
				p1 = strstr(buf, BUTLOCATE) + strlen(BUTLOCATE);
				if (strncasecmp(p1, "false", 5) == 0)
					button[indx].butLocate = false;
				else
					button[indx].butLocate = true;
				continue;
			}
			if (strstr(buf, BUTTAB)) {
				// button tab order
				p1 = strstr(buf, BUTTAB) + strlen(BUTTAB);
				p = p1;
				while (*p != 0 && *p != ')') p++;
				*p = 0;
				button[indx].butTabOrder = atoi(p1);
				continue;
			}
			if (strstr(buf, BUTTXTTYPE)) {
				p1 = strstr(buf, BUTTXTTYPE) + strlen(BUTTXTTYPE);
				p1++;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
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
		combox[indx].comboxName = (char *) calloc(1, strlen(xname) + 1);
		strcpy(combox[indx].comboxName, xname);
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
				p1 = strstr(buf, BUTTAB) + strlen(BUTTAB);
				p = p1;
				while (*p != 0 && *p != ')') p++;
				*p = 0;
				combox[indx].comboTabOrder = atoi(p1);
				continue;
			}
			if (strstr(buf, BUTNAME)) {
				// button text
				p1 = strstr(buf, BUTNAME) + strlen(BUTNAME);
				p1++;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				combox[indx].comboxName = (char *) calloc(1, strlen(p1) + 1);
				strcpy(combox[indx].comboxName, p1);
				continue;
			}
			if (strstr(buf, TXTDNAME)) {
				p1 = strstr(buf, TXTDNAME);
				p1 = p1 + strlen(TXTDNAME);
				p1++;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				combox[indx].dataName = (char *) calloc(1, strlen(p1) + 1);
				strcpy(combox[indx].dataName, p1);
				continue;
			}
			if (strstr(buf, SETVALFNAME)) {
				p1 = strstr(buf, SETVALFNAME);
				p1 = p1 + strlen(SETVALFNAME) + 1;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				combox[indx].setvalfname = (char *) calloc(1, strlen(p1) + 1);
				strcpy(combox[indx].setvalfname, p1);
				continue;
			}
			if (strstr(buf, SETVALIN)) {
				p1 = strstr(buf, SETVALIN);
				p1 = p1 + strlen(SETVALIN) + 1;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				combox[indx].setvalin = (char *) calloc(1, strlen(p1) + 1);
				strcpy(combox[indx].setvalin, p1);
				continue;
			}
			if (strstr(buf, SETFNAME)) {
				p1 = strstr(buf, SETFNAME);
				p1 = p1 + strlen(SETFNAME) + 1;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				combox[indx].setfname = (char *) calloc(1, strlen(p1) + 1);
				strcpy(combox[indx].setfname, p1);
				continue;
			}
			if (strstr(buf, SETDNAMELST)) {
				p1 = strstr(buf, SETDNAMELST);
				p1 = p1 + strlen(SETDNAMELST) + 1;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				combox[indx].setdnamelst = (char *) calloc(1, strlen(p1) + 1);
				strcpy(combox[indx].setdnamelst, p1);
				continue;
			}
			if (strstr(buf, SETKEYVAL)) {
				p1 = strstr(buf, SETKEYVAL);
				p1 = p1 + strlen(SETKEYVAL);
				if (strncasecmp(p1, "false", 5) == 0)
					combox[indx].setkeyvals = 0;
				else
					combox[indx].setkeyvals = 1;
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
		checkBox[indx].setName = (char *) calloc(1, strlen(xname) + 1);
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
				p1 = strstr(buf, CHKSTAB) + strlen(CHKSTAB);
				p = p1;
				while (*p != 0 && *p != ')') p++;
				*p = 0;
				checkBox[indx].checkTabOrder = atoi(p1);
				continue;
			}
			if (strstr(buf, CHKNAME)) {
				// check text
				p1 = strstr(buf, CHKNAME) + strlen(CHKNAME);
				p1++;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				checkBox[indx].setName = (char *) calloc(1, strlen(p1) + 1);
				strcpy(checkBox[indx].setName, p1);
				// if (slabel[islabel - 1].lbltext == 0) {
				//	slabel[islabel - 1].lbltext = (char *) calloc(1, strlen(p1) + 1);
				//	strcpy(slabel[islabel - 1].lbltext, p1);
				// }
				continue;
			}
			if (strstr(buf, CHKDNAME)) {
				p1 = strstr(buf, CHKDNAME);
				p1 = p1 + strlen(CHKDNAME);
				p1++;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				checkBox[indx].dataName = (char *) calloc(1, strlen(p1) + 1);
				strcpy(checkBox[indx].dataName, p1);
				continue;
			}
			if (strstr(buf, CHKSVAL)) {
				p1 = strstr(buf, CHKSVAL);
				p1 = p1 + strlen(CHKSVAL) + 1;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				checkBox[indx].setval = (char *) calloc(1, strlen(p1) + 1);
				strcpy(checkBox[indx].setval, p1);
				continue;
			}
			if (strstr(buf, CHKUVAL)) {
				p1 = strstr(buf, CHKUVAL);
				p1 = p1 + strlen(CHKUVAL) + 1;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				checkBox[indx].setuval = (char *) calloc(1, strlen(p1) + 1);
				strcpy(checkBox[indx].setuval, p1);
				continue;
			}
			if (strstr(buf, CHKFONT)) {
				p1 = strstr(buf, CHKFONT);
				p1 = p1 + strlen(CHKFONT) + 1;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				checkBox[indx].font = (char *) calloc(1, strlen(p1) + 1);
				strcpy(checkBox[indx].font, p1);
				continue;
			}
			if (strstr(buf, CHKTXT)) {
				p1 = strstr(buf, CHKTXT);
				p1 = p1 + strlen(CHKTXT);
				if (strncasecmp(p1, "E", 1) == 0)
					checkBox[indx].text = "E";
				else
					checkBox[indx].text = "H";
				continue;
			}
		}
		fchkbox = 0;
	}
	if ((fbuttongrps == 0) && strstr(buf, CBUTTONGRP)) {
		fbuttongrps = 1;
		Processed = 1;
		getName(xname, (char *)CBUTTONGRP);
		if (strlen(xname) < 1) return ret;
		indx = isgroup;
		sgroup[indx].dataName = (char *)calloc(1, strlen(xname) + 1);
		strcpy(sgroup[indx].dataName, xname);
		sgroup[indx].txtno = 0;
		sgroup[indx].txtlblno = 0;
		sgroup[indx].text = 0;
		isgroup++;
		while (1) {
			ret = mygetline((char *)CENDINIT2);
			if (ret != EOF) { Processed = 1; break; }
			if (strstr(buf, CENDINIT) && !strstr(buf, CBEGIN)) {
				Processed = 1;
				break;
			}
			Processed = 1;
			if (strstr(buf, CHKDNAME)) {
				p1 = strstr(buf, CHKDNAME);
				p1 = p1 + 13;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				sgroup[indx].dataName = (char *)calloc(1, strlen(p1) + 1);
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
		scrollfield[indx].name = (char *) calloc(1, strlen(xname) + 1);
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
				p1 = p1 + strlen(TSCROLL) + 1;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				scrollfield[indx].tablename = (char *) calloc(1, strlen(p1) + 1);
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
		stable[indx].name = (char *) calloc(1, strlen(xname) + 1);
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
				p1 = p1 + strlen(MCLICK) + 1;
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
				if (ColumnVals(&stable[indx].cols[j], ADDCOLUMN) != EOF)
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
		getName(xname, (char *)CSTABLES);
		if (strlen(xname) < 1) return ret;
		indx = istable;
		stable[indx].tableno = getTable(xname);
		stable[indx].name = (char *)calloc(1, strlen(xname) + 1);
		strcpy(stable[indx].name, xname);
		istable++;

		while (1) {
			ret = mygetline((char *)CENDINIT2);
			if (ret != EOF) { Processed = 1; break; }
			if (strstr(buf, CENDINIT) && !strstr(buf, CBEGIN)) {
				Processed = 1;
				break;
			}
			Processed = 1;
			if (strstr(buf, CHKBOUND)) {
				boundVals(&stable[indx].tableBounds, (char *)CHKBOUND);
				continue;
			}
			if (strstr(buf, MCLICK)) {
				p1 = strstr(buf, MCLICK);
				p1 = p1 + strlen(MCLICK) + 1;
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
				ColkDataName(&stable[indx].cols[j].kdataname, (char *)"setKeyDataName(");
				continue;
			}
			if (strstr(buf, "setColumnWidth(")) {
				j = stable[indx].icols;
				ColWidth(&stable[indx].cols[j].colwidth, (char *)"setColumnWidth(");
				continue;
			}
			if (strstr(buf, "setTitle(")) {
				j = stable[indx].icols;
				ColTitle(&stable[indx].cols[j].title, (char *)"setTitle(");
				continue;
			}
			if (strstr(buf, "setEditable(")) {
				j = stable[indx].icols;
				ColEditVal(&stable[indx].cols[j].editval, (char *)"setEditable(");
				continue;
			}
			if (strstr(buf, ADDCOLUMN)) {
				j = stable[indx].icols;
				if (ColumnVals(&stable[indx].cols[j], (char *)ADDCOLUMN) != EOF)
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
		loader[indx].name = (char *) calloc(1, strlen(xname) + 1);
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
				p1 = strstr(buf, LOADSTR) + strlen(LOADSTR);
				p1++;
				p = p1;
				while (*p != 0 && *p != '\"') p++;
				*p = 0;
				loader[indx].loadstr = (char *) calloc(1, strlen(p1) + 1);
				strcpy(loader[indx].loadstr, p1);
			}
		}
		floader = 0;
	}
	if (strstr(buf, "}")) {
		ret = EOF;
		return ret;
	}
	if (Processed == 0)
		Processed = 1;
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
				if ((ret = detected(CQUERYLSTFUNC)) != EOF) continue;
				if ((ret = detected(CTABLE)) != EOF) continue;
				if ((ret = detected((char *)CTABLES)) != EOF) continue;
				Processed = 1;
			}
		}
	}
	return ret;
}

int  iconst;
char constname[300][150];
char consttext[300][200];
int constuniq[300];

int constVarmi(char *name, int unique, char *text)
{
	int ii;
	char *p = name;
	if (text == NULL) return -1;
	if (p && strlen(p) > 0) {

		for (ii = 0; ii < iconst; ii++) {
			if (strcmp(consttext[ii], text) == 0) return - 1;
		}
		ii = iconst;
		strcpy(constname[ii], p);
		strcpy(consttext[ii], text);
		constuniq[ii] = unique;
		iconst++;
		return constuniq[ii];
	}
	else return -1;
}

int  iconstp;
char consts[300][200];

int cExits(char *p)
{
	int  i;
	for (i = 0; i < iconstp; i++) {
		if (strcmp(consts[i], p) == 0)
			return 1;
	}
	strcpy(consts[iconstp], p);
	iconstp++;
	return 0;
}

char* pnamevar[200];
int ipname = 0;

int pnameVarmi(char* s)
{
	int i;
	for (i = 0; i < ipname; i++) {
		if (strcmp(pnamevar[i], s) == 0)
			return 1;
	}
	i = ipname;
	pnamevar[i] = (char*)calloc(1, strlen(s)+1);
	strcpy(pnamevar[i], s);
	ipname++;
	return 0;
}
void viewconstants(char *fname, char *tranid)
{
	FILE *fp;
	char fbuf[MAXCHAR + 1];
	char *p, *p1, *pname;
	int  ilk = 1, jilk = 1;
	int  acildi = 0, jflowview = 0;

	// read from flow.preference file
	// create constants using this file
	fp = fopen(fname, "r");
	if (fp) {
		while (fgets(fbuf, MAXCHAR, fp)) {
			rmnl(fbuf);
			if (strstr(fbuf, "init.")) {
				p = fbuf + 5;
				p1 = strstr(p, "=");
				if (p1) {
					*p1 = 0;
					p1++;
					if (strstr(p, "/>"))
						continue;
					if (strstr(p1, "\"\"") > 0 || strstr(p1, " />"))
						printf("    public const string Init%s = \"\";\n", p);
					else printf("    public const string Init%s = \"%s\";\n", p, p1);
				}
			}
		}
		fclose(fp);
	}
	fp = fopen(fname, "r");
	if (fp) {
		while (fgets(fbuf, MAXCHAR, fp)) {
			rmnl(fbuf);
			p = strstr(fbuf, "name.");
			if (p) {
				printf("    public const string FuncCode=\"%s\";\n", tranid);
				printf("    public sealed class FlowView\n");
				printf("    {\n");
				iconstp = 0;
				acildi = 1;
			}
			else
				if (strstr(fbuf, "view.")) {
					p1 = strstr(fbuf, ".");
					if (p1)
						pname = p1 + 1;
					else pname = fbuf;
					p = pname;
					p1 = strstr(p, "=");
					if (p1) {
						*p1 = 0;
						p1 = p1 + 1;
					}
					if (cExits(p1) == 0) {
						if (pname) {
							if (strcmp(indexname, pname) == 0)
								printf("            public const string %s = \"Index\";\n", buyukHarf(p1));
							else {
								if (strstr(pname, "\"\""))
									printf("            public const string %s = %s;\n", buyukHarf(p1), pname);
								else {
									printf("            public const string %s = \"%s\";\n", buyukHarf(p1), pname);
									if(pnameVarmi(pname) == 0 && !strstr(pname, "vcontroller"))
										printf("            public const string %s = \"%s\";\n", buyukHarf(pname), pname);
								}
							}
						}
						else printf("            public const string %s = \"\";\n", buyukHarf(p1));
					}
				}
		}
		//if (acildi) printf("    }\n");
		fclose(fp);
	}
	acildi = 0;
	fp = fopen(fname, "r");
	if (fp) {
		while (fgets(fbuf, MAXCHAR, fp)) {
			rmnl(fbuf);
			if (strstr(fbuf, "flowtag.")) {
				if (ilk) {
					printf("        public const string ViewIndex = \"Index\";\n");
					printf("        public const string Vcontroller = \"%s\";\n", tranid);
					printf("        public const string Final = \"final\";\n");
					printf("        public const string Models = \"%sViewModel\";\n", tranid);
					printf("    }\n");
					printf("    public sealed class FlowTag\n");
					printf("    {\n");
					ilk = 0;
					iconstp = 0;
					acildi = 1;
				}
				p1 = strstr(fbuf, ".");
				if (p1)
					pname = p1 + 1;
				else pname = fbuf;
				p = pname;
				p1 = strstr(p, "=");
				if (p1) {
					*p1 = 0;
					p1 = p1 + 1;
				}
				if (cExits(p1) == 0) {
					printf("        public const string %s = \"%s\";\n", buyukHarf(p1), pname);
				}
			}
		}
		/*if (acildi) printf("    }\n");*/
		fclose(fp);
	}
	fp = fopen(fname, "r");
	if (fp) {
		while (fgets(fbuf, MAXCHAR, fp)) {
			rmnl(fbuf);
			if (strstr(fbuf, "func.") || strstr(fbuf, "oper.") || strstr(fbuf, "action")) {
				if (jilk) {
					printf("    }\n");
					jilk = 0;
					printf("    public sealed class FuncTag\n");
					printf("    {\n");
					acildi = 1;
					iconstp = 0;
				}
				p1 = strstr(fbuf, ".");
				if (p1)
					pname = p1 + 1;
				else pname = fbuf;
				p = pname;
				p1 = strstr(p, "=");
				if (p1) {
					*p1 = 0;
					p1 = p1 + 1;
				}
				if (cExits(p1) == 0) {
					if (strcmp(pname, indexname) == 0) {
						printf("        public const string %s = \"Index\";\n", buyukHarf(p1));
					} else
						printf("        public const string %s = \"%s\";\n", buyukHarf(p1), pname);
				}
			}
		}
		/*if(acildi) printf("    }\n");*/
		fclose(fp);
		/* ozel degismezler */
	}
	printf("    }\n");
	printf("}\n");
}

void myconstantWrite(int ilk, int end, char *tranid, int unique, char *flowfile)
{
	int i, xx;
	if (ilk == 0) {
		iconst = 0;
		printf("// Generated by BE-CON Automatic Face Converter V:1.0\n\n");
		printf("namespace AkbankFace.Web.%s.Common.Constants\n",areaName);
		printf("{\n");
		printf("    public sealed class %sConstants\n", tranid);
		printf("    {\n");
	}

	for (i = 0; i < islabel; i++) {
		/* Label = value */
		if (slabel[i].lbltext) {
			if (slabel[i].text)
				xx = constVarmi(slabel[i].lbltext, unique, slabel[i].text);
			else xx = constVarmi(slabel[i].lbltext, unique, slabel[i].lbltext);
			if (xx == -1) continue;
			if (xx == 0) {
				if (slabel[i].text && strcmp(slabel[i].text, "%") == 0)
					printf("    public const string %s = \"\";\n",
						buyukHarf(slabel[i].lbltext));
				else
					printf("    public const string %s = \"%s\";\n",
						buyukHarf(slabel[i].lbltext), slabel[i].text);
			}
			else {
				if (slabel[i].text && strcmp(slabel[i].text, "%") == 0)
					printf("    public const string %s%03d = \"\";\n",
						buyukHarf(slabel[i].lbltext), xx);
				else
					printf("    public const string %s%03d = \"%s\";\n",
						buyukHarf(slabel[i].lbltext), xx, slabel[i].text);
			}
		}
		else
		if(slabel[i].lbl) {
			if (slabel[i].text)
				xx = constVarmi(slabel[i].lbl, unique, slabel[i].text);
			else xx = constVarmi(slabel[i].lbl, unique, slabel[i].lbl);
			if (xx == -1) continue;
			if (xx == 0) {
				if (slabel[i].text && strcmp(slabel[i].text, "%"))
					printf("    public const string %s = \"%s\";\n",
						buyukHarf(slabel[i].lbl), slabel[i].text);
				else
					printf("    public const string %s = \"\";\n", buyukHarf(slabel[i].lbl));
			}
			else {
				if (slabel[i].text && strcmp(slabel[i].text,"%"))
					printf("    public const string %s%03d = \"%s\";\n",
						buyukHarf(slabel[i].lbl), unique, slabel[i].text);
				else 
					printf("    public const string %s%03d = \"\";\n",
						buyukHarf(slabel[i].lbl), unique);
			}
		}
	}
	for (i = 0; i < ispanel; i++) {
		if (spanel[i].panNo < 0 || spanel[i].panNo > ispanel) continue;
		if (spanel[i].panelName) {
			if (strstr(spanel[i].panelName, "AkbankButton")) continue;
			if (spanel[i].setTitle) {
				xx = constVarmi(spanel[i].panelName, unique, spanel[i].setTitle);
			}
			else {
				xx = constVarmi(spanel[i].panelName, unique, spanel[i].panelName);
			}
			if (xx == -1) continue;
			if (xx == 0) {
				if (spanel[i].setTitle)
					printf("    public const string %s = \"%s\";\n",
						buyukHarf(spanel[i].panelName), spanel[i].setTitle);
				else 
					printf("    public const string %s = \"%s\";\n",
						buyukHarf(spanel[i].panelName), spanel[i].panelName);
			}
			else {
				if (spanel[i].setTitle) {
					if (unique)
						printf("    public const string %s%03d = \"%s\";\n",
						buyukHarf(spanel[i].panelName), xx, spanel[i].setTitle);
					else
						printf("    public const string %s = \"%s\";\n",
						buyukHarf(spanel[i].panelName), spanel[i].setTitle);
				}
				else {
					if (unique)
						printf("    public const string %s%03d = \"\";\n",
						buyukHarf(spanel[i].panelName), xx);
					else
						printf("    public const string %s = \"\";\n",
						buyukHarf(spanel[i].panelName));
				}
			}
		}
	}
	//for (i = 0; i < istable; i++) {
	//	for (j = 0; j < stable[i].icols; j++) {
	//		if (strlen(stable[i].cols[j].dataname) > 0) {
	//			if (constVarmi(stable[i].name, stable[i].cols[j].text)) continue;
	//			printf("    public const string %s.%s = \"%s\";\n",
	//				stable[i].name, stable[i].cols[j].dataname, stable[i].cols[j].text);
	//		}
	//		else {
	//			if (constVarmi(stable[i].name, stable[i].cols[j].text)) continue;
	//			printf("    public const string %s.Column%d = \"%s\";\n",
	//				stable[i].name, j, stable[i].cols[j].text);
	//		}
	//	}
	//}
	if (ilk == end) {
		printf("    public const string SlipTransactionName=\"printer\";\n");
		printf("    public const string SlipTaskCode=\"printer\";\n");
		printf("    public const string DateFormatStr=\"dd.MM.yyyy\";\n");
		viewconstants(flowfile, tranid);
	}
}



#define RSON 3

int r = 0;

void params(int argc, char **argv)
{
	int  i;
	for (i = 0; i < argc; i++)
		printf("%d %s, ", i, argv[i]);
	printf("\n");
}

int main(int argc, char **argv)
{
	FILE *fp;
	int  i, ret, unique;
	char *strp;
	// char htmlname[300];
	char tranid[300];
	char flowfile[300];
	char constfile[300];


	/* get tables and coulmns of connected database */
	SetConsoleOutputCP(CP_UTF8);
	// setvbuf(stdout, nullptr, _IOFBF, 30000);
	output = stdout;
	param = 0;
	if (argc >= 6) {
		param = atoi((char *)argv[1]);
		strcpy(flowfile, argv[5]);
		// strcpy(filename, argv[6]);
		strcpy(areaName, argv[3]);
		strcpy(tranid, argv[2]);
		strcpy(indexname, argv[4]);
	} else {
		printf("kullanım: constants [1/2] <tranid> <areaname> <flowfile> <java_files>\n");
		exit(0);
	}

	// p = strstr((char *)filename, ".");
	// *p = 0;
	// strcpy(htmlname, filename); strcat(htmlname, ".cs");
	// output    = fopen(htmlname,"w");
	unique = 0;
	for (i = 6; i < argc; i++) {
		fp = fopen((char *)argv[i],"rb");
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
			myconstantWrite(i - 6, argc - 7, tranid, unique, flowfile);
			unique++;
		}
		else {
			params(argc, (char **)argv);
			printf("java_file %s bulunamadı\n", argv[i]);
		}
	}
	strcpy(constfile, flowfile);
	strp = strstr(constfile, "flow.");
	if(strp) strcpy(strp, ".constants");
	/*printf("output %s\n", constfile);*/

	fp = fopen(constfile, "w");
	if (fp) {
		int ii;
		for (ii = 0; ii < iconst; ii++) {
			if (strcmp(consttext[ii], indexname) == 0)
				fprintf(fp, "java.%s=Index\n", buyukHarf(constname[ii]));
			else fprintf(fp, "java.%s=%s\n", buyukHarf(constname[ii]), buyukHarf(consttext[ii]));
		}
		fprintf(fp, "java.SlipTransactionName=printer\n");
		fprintf(fp, "java.SlipTaskCode=printer\n");
		fprintf(fp, "java.DateFormatStr=dd.MM.yyyy\n");
		// fprintf(fp, "java.DateFormatStr=dd.MM.yyyy\n");
		fclose(fp);
	}
	return 0;
}
