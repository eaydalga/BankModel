#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <windows.h>

#define DEBUGX
#define NDEBUGX

#define PREFS "prefs\\"

#define true  1
#define false 0

#define SMAX      50
#define STATEMAX  200

#define STINITIAL  1
#define STVIEW     2
#define STACTION   3

#define SEINITMONDETARY  31
#define SEOPENVIEWAK     32
#define SESETVALUE       33

#define CSTATE     "<state "
#define CDUMMY     " "

#define CENTRY     "<entryActions>"
#define CTRANS     "<transitions>"

#define CTRAN      "<transition "
#define CACTION    "<actions"
#define CCLOSE     "<closeViewAk />"
#define COPEN      "<openViewAk "
#define CSETVAL    "<setValue "
#define CADDVAL    "<addValue "
#define CDOCUMENTS "<printDocuments "
#define CINIT      "<initMonetaryAction "

#define CEXEC      "<executeOperationActAk "
#define CEXECID    "id=\""
#define CEXECOP    "operationName=\""
#define CEXECMON   "isMonetary=\""
#define CEXECLAST  "isLastStep=\""
#define CEXECMAINT "isMaintenance=\""
#define CEXECAPPR  "isApprovalNecessary=\""
#define CEXECLNK   "linkContextTo=\""
#define EEXEC      "</executeOperationActAk>"
#define CINITCOLL  "<initColl"
#define CRMCOLL    "<removeFromColl "
#define CRMCONTEXT "<removeFromContext "

#define EINIT      "/>"
#define EOPENX      "/>"
#define ENDEXEC    "/>"
#define EOPEN      "</openViewAk>"
#define EACTION    "</actions>"
#define ESETVAL    "/>"
#define EADDVAL    "/>"
#define EDOCUMENTS "/>"
#define ETRAN      "/>"
#define ETRANF     "</transition>"
#define ESTATE     "</state>"
#define ESTATEF    "/>"
#define ETRANS     "</transitions>"
#define EENTRY     "</entryActions>"

#define CCONDACT    "<conditionAction>"
#define CCONDS      "<conditions>"
#define CCOMPCOND   "<compositeCondition "
#define CLOGICAL    "<logical "
#define ELOGICAL    "/>"
#define ECOMPCOND   "</compositeCondition>"
#define ECONDS      "</conditions>"
#define ECONDACT    "</conditionAction>"

#define CBUTTONL    "<buttonList>"
#define EBUTTONL    "</buttonList>"
#define CFOOTER     "<footerButton "
#define CTEXT       "text=\""
#define CTABORDER   "tabOrder=\""
#define CLASTSTEP   "lastStep=\""
#define CVISIBLE    "visible=\""
#define CSHOWMSG    "<showMessage "
#define ESHOWMSG    "/>"

#define CSYNC       "<syncProcState "
#define ESYNC       "</syncProcState>"

#define CID           "id=\""
#define CSHOWID        "id=\""
#define CSHOWMSGX      "message=\""
#define CSHOWTITLE     "title=\""
#define CSHOWMSGTYPE   "messageType=\""
#define CSHOWOPTTYPE   "optionType=\""
#define CSHOWDEFAULT   "defaultOption=\""
#define CGETSHARE      "<getSharedValue "
#define CSETSHARE      "<setSharedValue "
#define CPAD           "<pad "
#define CCF            "<cCFControl "
#define CGEN           "<generateIBANAccount "
#define CMAES          "<maestroScanDocument "
#define CGENEXP        "<genericExpression"

#define CTRIMS         "<trimString "
#define CTRIMID        "id=\""
#define CTRIMVAR       "variable=\""
#define CTRIMCHAR      "trimChar=\""
#define CTRIMDIR       "direction=\""
#define ETRIM          "/>"

#define CRMCOLLID      "id=\""
#define CRMCOLLDELM    "dataElement=\""
#define CRMCOLLPOLY    "policy=\""
#define CRMCOLLREPNO   "repoNo=\""

#define CRMCONTEXTID      "id=\""
#define CRMCONTEXTDELM    "dataElement=\""

#define CINITCOLLID    "id=\""
#define CINITCOLLDELM  "dataElement=\""
#define CUNSTR         "<unstring "
#define CTRACE         "<writeToTrace "
#define CTRACEID       "id=\""

#define CUNSTRSRC "source=\""

#define PSTATE     1
#define PENTRY     10
#define PTRANS     11

#define PTRAN      12
#define PACTION    13
#define POPEN      14
#define PSETVAL    15
#define PDOCUMENTS 16
#define PINIT      17
#define PCLOSE     18
#define PTRANF     19
#define PEXEC      20
#define PCONDACT   21
#define PCONDS     22
#define PCOMPCOND  23
#define PLOGICAL   24
#define PSHOWMSG   25
#define PGETSHARE  26
#define PSETSHARE  27
#define PPAD       28
#define PCCF       29
#define PGEN       30
#define PMAES      31
#define PTRIM      32
#define PINITCOLL  33
#define PRMCOLL    34
#define PUNSTR     35
#define PGENEXP    36
#define PTRACE     37
#define PRMCONTEXT 38
#define PADDVAL    39

#define CTRANID      "id=\""
#define CTARGET      "targetState=\""

#define CINITID      "id=\""
#define COPENID      "id=\""
#define CVIEWNAME    "viewName=\""
#define CVIEWSRC     "viewSource=\""
#define CLNKCONTEXT  "linkContextTo=\""
#define CTABINTER    "tabInterval=\""
#define CTITLE       "title=\""
#define CFOOTERMSG   "footerMessage=\""
#define CAPPROVAL    "isapprovalNecessary=\""
#define CAPPTYPE     "approvalType=\""
#define CDATAELM     "dataElements=\""
#define CDEFVAL      "defValue=\""

#define COPNAME      "opName"
#define CFIRSTOP     "firstOperand"
#define CSECONDOP    "secondOperand"

#define CONTRUE      "onTrue"
#define CONFALSE     "onFalse"

#define CGETSHAREID    "id=\""
#define CGETSHARECVAR  "contextVariable=\""
#define CGETSHAREVAR   "sharedVariable=\""

#define CSETSHAREID    "id=\""
#define CSETSHAREVAR   "sharedVariable=\""
#define CSETSHAREVAL   "value=\""

#define CPADID        "id=\""
#define CPADDNAME     "dataName=\""
#define CPADCHAR      "padCharacter=\""
#define CPADLEN       "totalLength=\""
#define CPADALIGN     "alignment=\""

#define CCFID          "id=\""
#define CCFCUST        "CustomerID=\""
#define CCFSIGN        "signal=\""

#define CGENID         "id=\""
#define CGENACC        "accountNo=\""
#define CGENBR         "branchCode=\""
#define CGENCD         "currencyCode=\""
#define CGENIBAN       "IBANaccountNo=\""

#define CGENEXPID         "expressionId=\""

#define CMAESID        "id=\""
#define CMAESDOCBR     "docBranch=\""
#define CMAESDOCDT     "docDate=\""
#define CMAESDOCMAINT  "docMaintenanceNumber=\""
#define CMAESVIEW      "viewGroupId=\""
#define CMAESDOCTYPE   "docType=\""
#define CMAESOPTYPE    "operationType=\""
#define CMAESDOCHOST   "docHostFunction=\""
#define CMAESDOCID     "docIdentityTaxNo=\""
#define CMAESDOCCUST   "docCustomerNo=\""
#define CMAESSCAN      "scanningReason=\""

#define CTRACE0        "trace0=\""
#define CTRACE1        "trace1=\""
#define CTRACE2        "trace2=\""

#define MAXCHAR 2000

#define FLOW 1
#define CB   2

#define VMAX  20
#define MMAX  20
#define IMAX  100
#define INMAX 200
#define SMAX  50

#define FMAX  300

#define MSMAX 250

#define STRINGTYPE  1
#define DATETYPE    2
#define NUMERICTYPE 3
#define OTHERTYPE   4

int petition = 0;

char initialscr[200];
char buf[MAXCHAR + 1];

struct EXEC {
	char *execid;
	char *execop;
	char *execmon;
	char *execlast;
	char *execmaint;
	char *execappr;
	char *execlnk;
};

struct BUTTON {
	char *buttontext;
	char *buttontabOrder;
	char *buttonlastStep;
	char *buttonvisible;
};

struct OPENX {
	char *openid;
	char *viewname;
	char *viewsrc;
	char *lnkcontext;
	char *tabinter;
	char *title;
	char *footermsg;
	int  approval;
	int  apptype;
	int  ibuttons;
	struct BUTTON buttons[SMAX];
};

struct SETVAL{
	char *dataelm;
	char *defval;
};

struct ADDVAL {
	char* addid;
	char* dataelm;
	char* defval;
};


struct LOGICAL {
	char *opname;
	char *firstop;
	char *secondop;
};

struct COMPCON {
	char * onTrue;
	char * onFalse;
	int  ilogical;
	struct LOGICAL logical[SMAX];
};

struct SHOWMSG {
	char *showid;
	char *message;
	char *title;
	char *messageType;
	char *optionType;
	char *defaultOption;
};

struct GETSHARE {
	char *shareid;
	char *sharecvar;
	char *sharevar;
};

struct SETSHARE {
	char *setid;
	char *setcvar;
	char *setvar;
};

struct PAD {
	char *padid;
	char *dname;
	char *padchar;
	char *padlen;
	char *padalign;
};

struct CCCF {
	char *ccfid;
	char *cust;
	char *sig;
};

struct GEN {
	char *genid;
	char *genacc;
	char *genbr;
	char *gencd;
	char *geniban;
	char *genexpid;
};

struct GENEXP {
	char *genid;
	char *genexpid;
};

struct MAES {
	char *maesid;
	char *maesdocbr;
	char *maesdocdt;
	char *maesdocmaint;
	char *maesview;
	char *maesdoctype;
	char *maesoptype;
	char *maesdochost;
	char *maesdocid;
	char *maesdoccust;
	char *maesscan;
};

struct TRIM {
	char *trimid;
	char *trimvar;
	char *trimchar;
	char *trimdir;
};

struct INITCOLL {
	char *id;
	char *delm;
};

struct RMCOLL {
	char *id;
	char *delm;
	char *poly;
	char *repno;
};

struct RMCONTEXT {
	char *id;
	char *delm;
};

struct UNSTR {
	char *src;
	int  start;
	int  len;
};

struct TRACE {
	char *traceid;
	char *trace0;
	char *trace1;
	char *trace2;
};
struct ENTRY {
	char *initid;
	int  iexec;
	struct EXEC eexec[SMAX];
	int  iopen;
	struct OPENX sopen[SMAX];
	int  isetval;
	struct SETVAL esetval[SMAX];
	int  iaddval;
	struct ADDVAL eaddval[SMAX];
	char *eprintid;
	int  icompcond;
	struct COMPCON ecompcon[SMAX];
	int  ishowmsg;
	struct SHOWMSG eshowmsg[SMAX];
	int  igetshare;
	struct GETSHARE egetshare[SMAX];
	int  isetshare;
	struct SETSHARE esetshare[SMAX];
	int  ipad;
	struct PAD epad[SMAX];
	int  iccf;
	struct CCCF eccf[SMAX];
	int  igen;
	struct GEN egen[SMAX];
	int  imaes;
	struct MAES emaes[SMAX];
	int  itrim;
	struct TRIM etrim[SMAX];
	int  iinitcoll;
	struct INITCOLL einitcoll[SMAX];
	int  irmcoll;
	struct RMCOLL ermcoll[SMAX];
	int  irmcontext;
	struct RMCONTEXT ermcontext[SMAX];
	int  iunstr;
	struct UNSTR unstr[SMAX];
	int  igenexp;
	struct GENEXP egenexp[SMAX];
	int  itrace;
	struct TRACE etrace[SMAX];
};

struct TRANSITION {
	char *tranid;
	char *trantarget;
	char *closes;
};

struct STATE {
	char *stateid;
	char *statetype;
	char *statetypeid;
	int  isref;
	char *staterefs[SMAX];
	char *statermodel;
	char *stateimodel;
	int  ientry;
	int  itran;
	struct ENTRY entry[5];
	struct TRANSITION trans[10];
} states[STATEMAX];
int istate;

int  ivname = 0;
struct VNAME {
	char viewname[100];
	char vrecname[100];
	char vcode[3];
	int  ivitem;
	struct ITEMS {
		int  vlen;
		char vitem[100];
		char vtype[30];
		char vitemcode[3];
	} items[IMAX];
	int  iarray;
	char arrayName[100];
	char arrcode[3];
	struct ARR {
		int  arrlen;
		char arritem[100];
		char arrtype[20];
		char arritemcode[3];
	} arr[IMAX];
} vname[VMAX];

int  imca = 0;
struct MCA {
	char fname[100];
	char recname[100];
	char code[3];
	int  imarr;
	struct MARR {
		int  mcalen;
		char mcaitem[100];
		char mcatype[20];
		char mcacode[3];
	} marr[IMAX];
	int icols;
	struct COLS {
		int  icol;
		char colname[100];
		char colcode[3];
		struct COL {
			int  collen;
			char colitem[100];
			char coltype[20];
			char mcaccode[3];
		} col[IMAX];
	} cols[4];
} mca[MMAX];

int ivmca = 0;
struct VMCA {
	char view[20][100];
	char mca[20][100];
	int yon[20];
} vmca;

int ivmodel;
struct VMODEL {
	int  istart;
	int  is;
	char *sid;
	char *stype;
	char *stranid[5];
	char *smodel;
	char *ftype;
	int  iptype;
	char *ptype[5];
	char *pname[5];
	char *sview;
	char *starget[12];
} vmodel[400];

int  iviews = 0;
struct FVIEWS {
	char v1[100];
	char v2[100];
};
struct FVIEWS fviews[200];

int iconstant;
struct CONSTANTS {
	char *vtype; // view, action, cond, oper, flow, final, java
	char *vname; // constant name R944.R944constants.<vname>
	char *vval;  // corresponding constant data
} constants[500];


int iflowcall = 0;
struct FLOWCALL {
	char *funcname;
	char *constant;
	int  jcount;
	char *tags[5];
	char *fcall[5];
} flowcall[100];

int isavestate = 0;
struct SAVESTATE {
	char stateid[50];
	int  statej;
	int  statek;
} savestate[60];

int ifuncs;
struct FUNCS {
	char *fname;
	char *fretmodel;
	char *finmodel;
} funcs[INMAX];


int isavestack = 0;
struct SAVESTACK {
	char* fn;
	char* sv;
	char* prog;
	char* trn;
	char* area;
	int  ii;
} saveStack[100];

int elseset = 0;
int braket = 0;

char  garea[100];

extern int inode;
struct NODE {
	char* nstate;
	char* nstatetype;
	char* nretmodel;
	char* ninmodel;
	char* viewmodel;
	char* bomodel;
	struct NODE* previous;
	int inext;
	struct NODE* next[8];
};
extern struct NODE nodes[100];

FILE *input, *output;

int Processed = 0;
int fstate = 0;
int ftrans = 0;
int fentry = 0;
int param = 0;
int globalvar = 0;

int  indents = 0;
int  globalData = 0;

char progname[200];
char tranname[200];
char lastView[200];
char getlistmodel[200];
char inittarget[200];
char indexname[200];
char gislem[200];
char areaName[300];

int  iextras;
char *extras[200];

int  headerVar = 0;
char indent[200];

char fbuf[FMAX + 1];
char constval[200];

int  voidreturn = 0;

int  iyazilan = 0;
char* yazilan[200];

extern void extrasYaz();
int  ekranmi(char *);
char *viewBak(char *);
char *mcaArrMi(char *);
int  viewVarMi(char *);
char *laststr(char *, char *);
int  mcaVarmi(int, char *, char *);
void funcWrite(char *, int, char *, char *, char *, char *);
char *defineFunc(char *, int, char *, char *, char **);
int  yazilanaekle(char *);
int  stringmi(int);
void getModelState();
void petitionprint(char *);
int  icontrollerstart;
char *controllerstart[200];
char initname[MAXCHAR];
int  varmi(char *);
char *myReplace(char *, char, char);
char *initVariables(char *);
int  baslik(char *);
int  baslikyaz(char *);
int  getextras(char *);
int  igetlistarr;
char *getlistarr[200];
void extradatayaz(int);
char* stringHeader(int, char*, char*, char*);
void indexRegion(int, char *, char *);
char* constVariables(char* );
void mySaveStack(char *, int, char *, char*, char*, char*);
//void yazsaveViews(char *, char*);
void operFunc(int, char*, char*);
char *evaluateDefValue(int, char *); 
int  openVarmi(int);
char *buyukHarf(char*);
char* sifirVarmi(char*);

extern void MymodelToPrint(char *, char *);
extern struct NODE* nodeBak(char*);
extern void readslip(char*, char*);
extern void readdoc(char*, char*);
int  lefttype;
int  rigthtype;
int  bufpset = 0;

struct SLINE {
	int  row;
	char* type;
	char* label;
	char* dname;
	int  col;
	char* fmt;
	int align;
	int len;
	int prec;
};
struct REGDATA {
	char* regdname;
	char* regfunc;
	int  regpage;
	int  regchange;
	int  idata;
	struct SLINE ddata[50];
};

struct BREAK {
	char* icol;
	char* id;
	int ibline;
	struct SLINE bline[20];
};

extern int idocptr;
struct DOCPTR {
	char* dfname;
	char* dname;
	int	 iheader;
	struct SLINE dheader[50];
	struct REGDATA regdata;
	int ibreak;
	struct BREAK dbreak[10];
};
extern struct DOCPTR docptr[5];

int imcaview;
struct MCAVIEW {
	char *mcaName;
	char *viewName;
} mcaview[20];

int iviewview;
struct VIEWVIEW {
	char *view1Name;
	char *view2Name;
} viewview[20];


char* indentstr()
{
	int i;
	indent[0] = 0;
	for (i = 0; i < indents; i++) {
		strcat(indent, "   ");
	}
	return indent;
}

int upper(char p)
{
	if (p >= 'a' && p <= 'z')
		p = p - 'a' + 'A';
	return (p & 0xff);
}

int strcasecmp(char *p, char *s)
{
	char *p1, *s1;
	int  i, len;
	len = (int)strlen(p);
	p1 = (char *)calloc(1, len + 1);
	if (p1) {
		for (i = 0; i < len; i++) {
			p1[i] = upper(p[i]);
			p1[i + 1] = 0;
		}
	}
	len = (int)strlen(s);
	s1 = (char *)calloc(1, len + 1);
	if (s1) {
		for (i = 0; i < len; i++) {
			s1[i] = upper(s[i]);
			s1[i + 1] = 0;
		}
	}
	if (p1 && s1)
		return strcmp(p1, s1);
	return - 1;
}

int strncasecmp(char *p, char *s, int n)
{
	int i;
	for (i = 0; i < n; i++) {
		if (upper(p[i]) > upper(s[i])) return 1;
		if (upper(p[i]) < upper(s[i])) return -1;
	}
	return 0;
}

char *trim(char *bf)
{
	char *p = bf;
	while (*p && *p == ' ') p++;
	return p;
}

void rmnl(char *bf)
{
	int len = (int)strlen(bf);
	if (bf[len - 1] == '\n') { bf[len - 1] = 0; len--; }
	if (bf[len - 1] == '\r') { bf[len - 1] = 0; len--; }
	if (bf[len - 1] == '\n') { bf[len - 1] = 0; len--; }
}

int viewVarmi(char* s)
{
	if (viewBak(s)) return 1;
	return 0;
}

void mcaArray(int i)
{
	fprintf(output, "%sModel model = new %sModel();\n", mca[i].fname, mca[i].fname);
}

void viewArray(int i)
{
	fprintf(output, "%s model = new %s();\n", vname[i].arrayName, vname[i].arrayName);
	fprintf(output, "%s", indentstr());
	if (constVariables(vname[i].arrayName))
		fprintf(output, "if(Flow.GetViewDetail(%s) != null)\n", constVariables(vname[i].arrayName));
	else fprintf(output, "if(Flow.GetViewDetail(\"%s\") != null)\n", vname[i].arrayName);
	fprintf(output, "%s", indentstr());
	if (constVariables(vname[i].arrayName))
		fprintf(output, "    model = Flow.GetViewDetail(%s).Model as %sViewModel;\n",
			constVariables(vname[i].arrayName), vname[i].arrayName);
	else fprintf(output, "    model = Flow.GetViewDetail(\"%s\").Model as %sViewModel;\n",
		vname[i].arrayName, vname[i].arrayName);
}

void saveArray(int i)
{
	fprintf(output, "%s", indentstr());
	if (constVariables(vname[i].arrayName))
		fprintf(output, "Flow.addVariableToFlow<%s>(new KeyValuePair<string, %sViewModel>(%s, model));\n",
			constVariables(vname[i].arrayName), vname[i].arrayName, constVariables(vname[i].arrayName));
	else fprintf(output, "Flow.addVariableToFlow<\"%s\">(new KeyValuePair<string, %sViewModel>(\"%s\", model));\n",
		vname[i].arrayName, vname[i].arrayName, vname[i].arrayName);
}


char *evaluateDefValue(int ftype, char *pstr)
{
	char mybuf[200];
	char outbuf[300];
	char *p, *p1, *p2;
	strcpy(mybuf, pstr);

	p = mybuf;
	outbuf[0] = 0;
	if (strstr(p, ".0.")) {
		if (*p == '@') {
			p1 = sifirVarmi(p + 1);
			strcpy(outbuf, "model.");
			strcat(outbuf, p1);
		}
		else {
			p1 = sifirVarmi(p);
			strcpy(outbuf, p1);
		}
	}
	else {
		while (p) {
			p1 = strstr(p, "@");
			if (p1) {
				if (ftype == FLOW)
					strcat(outbuf, "model.");
				else strcat(outbuf, "model.");
				p1++;
				p = p1;
				p1 = strstr(p, "+");
				if (p1) {
					*p1 = 0;
					p1++;
					strcat(outbuf, buyukHarf(p));
					p = p1;
					if (*p != '+' && *p != '@') {
						strcat(outbuf, "+\"");
						p1 = strstr(p, "+");
						if (p1) {
							*p1 = 0; p1++;
							strcat(outbuf, buyukHarf(p));
							strcat(outbuf, "\"+");
							p = p1;
						}
						else {
							strcat(outbuf, buyukHarf(p));
							strcat(outbuf, "\"");
							//if (isnumber(buyukHarf(p)))
							//	strcat(outbuf, " // burada int.Parse kullanin");
							p = p1;
						}
					}
					else {
						strcat(outbuf, "+");
					}
				}
				else {
					strcat(outbuf, buyukHarf(p));
					strcat(outbuf, "\")");/*
					if (isnumber(buyukHarf(p)))
						strcat(outbuf, " // burada int.Parse kullanin");*/
				}
				p = p1;
			}
			else {
				p2 = initVariables(p);
				if (p2)
					strcpy(outbuf, buyukHarf(p2));
				else strcat(outbuf, p);
				p = p1;
			}
		}
	}
	p2 = (char *)calloc(1, strlen(outbuf) + 1);
	if(p2) strcpy(p2, outbuf);
	return p2;
}

//char* evaluateDefValueL(int ftype, char* pstr)
//{
//	char mybuf[200];
//	char outbuf[300];
//	char* p, * p1, * p2;
//	strcpy(mybuf, pstr);
//
//	p = mybuf;
//	outbuf[0] = 0;
//	if (strstr(p, ".0.")) {
//		if (*p == '@') {
//			p1 = sifirVarmi(p + 1);
//			strcpy(outbuf, "global.");
//			strcat(outbuf, p1);
//		}
//		else {
//			p1 = sifirVarmi(p);
//			strcpy(outbuf, p1);
//		}
//	}
//	else {
//		while (p) {
//			p1 = strstr(p, "@");
//			if (p1) {
//				if (ftype == FLOW)
//					strcat(outbuf, "model.");
//				else strcat(outbuf, "model.");
//				p1++;
//				p = p1;
//				p1 = strstr(p, "+");
//				if (p1) {
//					*p1 = 0;
//					p1++;
//					strcat(outbuf, buyukHarf(p));
//					p = p1;
//					if (*p != '+' && *p != '@') {
//						strcat(outbuf, "+\"");
//						p1 = strstr(p, "+");
//						if (p1) {
//							*p1 = 0; p1++;
//							strcat(outbuf, buyukHarf(p));
//							strcat(outbuf, "\"+");
//							p = p1;
//						}
//						else {
//							strcat(outbuf, "\"+");
//							p = p1;
//						}
//					}
//					else {
//						strcat(outbuf, "+");
//					}
//				}
//				else {
//					strcat(outbuf, buyukHarf(p));
//					strcat(outbuf, "\")");
//				}
//				p = p1;
//			}
//			else {
//				p2 = initVariables(p);
//				if (p2)
//					strcpy(outbuf, buyukHarf(p2));
//				else strcat(outbuf, p);
//				p = p1;
//			}
//		}
//	}
//	p2 = (char*)calloc(1, strlen(outbuf) + 1);
//	if (p2) strcpy(p2, outbuf);
//	return p2;
//}

char* getConstant(char* mtip, char* txt)
{
	int  i;
	for (i = 0; i < iconstant; i++) {
		if (strcmp(constants[i].vtype, mtip) == 0 && (strcmp(constants[i].vval, txt) == 0)) {
			if (strcmp(constants[i].vtype, "view") == 0)
				sprintf(constval, "FlowView.%s", constants[i].vname);
			else
				if (strcmp(constants[i].vtype, "func") == 0)
					sprintf(constval, "FuncTag.%s", constants[i].vname);
				else
					if (strcmp(constants[i].vtype, "flowtag") == 0)
						sprintf(constval, "FlowTag.%s", constants[i].vname);
					else strcpy(constval, constants[i].vname);
			return constval;
		}
	}
	if (strcmp(mtip, "view") == 0)
		sprintf(constval, "FlowView.%s", txt);
	else
		if (strcmp(mtip, "func") == 0)
			sprintf(constval, "FuncTag.%s", txt);
		else
			if (strcmp(mtip, "flowtag") == 0)
				sprintf(constval, "FlowTag.%s", txt);
			else sprintf(constval, ".%s", txt);
	return constval;
}

char *getconstant(char *mtip, char *txt)
{
	int  i;
	for (i = 0; i < iconstant; i++) {
		if ((strcmp(constants[i].vtype, mtip) == 0) && (strcmp(constants[i].vval, txt) == 0)) {
			if (strcmp(constants[i].vtype, "view") == 0)
				sprintf(constval, "FlowView.%s", constants[i].vname);
			else 
				if (strcmp(constants[i].vtype, "flowtag") == 0)
					sprintf(constval, "FlowTag.%s", constants[i].vname);
				else strcpy(constval, constants[i].vname);
			return constval;
		}
	}
	if (strcmp(mtip, "view") == 0)
		sprintf(constval, "FlowView.%s", txt);
	else
	if (strcmp(mtip, "func") == 0)
		sprintf(constval, "FuncTag.%s", txt);
	else
	if (strcmp(mtip, "flowtag") == 0)
		sprintf(constval, "FlowTag.%s", txt);
	else sprintf(constval, ".%s", txt);
	return constval;

}

int iglobals = 0;
char globals[150][200];

void readglobals(char *p)
{
	int i;
	char sbuf[300];
	FILE *fp;
	fp = fopen(p, "r");
	if (fp) {
		while (fgets(sbuf, 299, fp)) {
			rmnl(sbuf);
			for (i = 0; i < iglobals; i++) {
				if (strcmp(globals[i], buyukHarf(sbuf)) == 0)
					continue;
			}
			i = iglobals;
			strcpy(globals[i], buyukHarf(sbuf));
			iglobals++;
		}
		fclose(fp);
	}
	else fprintf(output, "%s file yok\n", p);
}

char *lookglobals(char *p)
{
	int i;
	char sbuf[200];
	char *ps;
	p = buyukHarf(p);
	if (strstr(p, "model.")) return p;
	for (i = 0; i < iconstant; i++) {
		if (strcmp(constants[i].vname, p) == 0 && strcmp(constants[i].vtype,"java") == 0) {
			sprintf(sbuf, "model.%s", p);
			ps = (char *)calloc(1, strlen(sbuf) + 1);
			if(ps) strcpy(ps, sbuf);
			return ps;
		}
	}
	for (i = 0; i < iglobals; i++) {
		if (strcmp(globals[i], p) == 0) {
			sprintf(sbuf, "model.%s", p);
			ps = (char *)calloc(1, strlen(sbuf) + 1);
			if(ps) strcpy(ps, sbuf);
			return ps;
		}
	}
	return p;
}

char* lookglobalsL(char* p)
{
	int i;
	char sbuf[200];
	char* ps;
	if (strstr(p, "model.")) return p;
	p = buyukHarf(p);
	for (i = 0; i < iconstant; i++) {
		if (strcmp(constants[i].vname, p) == 0 && strcmp(constants[i].vtype, "java") == 0) {
			sprintf(sbuf, "model.%s = ", p);
			ps = (char*)calloc(1, strlen(sbuf) + 1);
			if (ps) strcpy(ps, sbuf);
			return ps;
		}
	}
	for (i = 0; i < iglobals; i++) {
		if (strcmp(globals[i], p) == 0) {
			sprintf(sbuf, "model.%s = ", p);
			ps = (char*)calloc(1, strlen(sbuf) + 1);
			if (ps) strcpy(ps, sbuf);
			return ps;
		}
	}
	return p;
}

int mygetline(char *ss, char *psync)
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
		if (!((*p1 == '/' || (*(p1+1) == '*')) ||
			(strstr(p1, "<!--")))) {
			pt = strstr(pbuf, ss);
			if (pt == NULL && psync) {
				pt = strstr(pbuf, psync);
			}
			if (pt != NULL) {
				ret = (int)(pt - buf) + (int)strlen(ss);
			}
		}
	}
	else ret = -2;
	return ret;
}


int getstate(char *sn, char *st, char *stid)
{
	char sbuf[3000];
	char *p, *p1;
	int ret;
	if ((ret = mygetline(CSTATE, CSYNC)) > 0) {
		strcpy(sbuf, buf);
		p = strstr(buf, "id=\"");
		if (p) {
			p = p + 4;
			p1 = p;
			while (*p1 && *p1 != '"') p1++;
			*p1 = 0;
			strcpy(sn, p);
			p = p1 + 1;
			p1 = strstr(p, "type=\"");
			if (p1) {
				p = p1 + 6;
				p1 = p;
				while (*p1 && *p1 != '"') p1++;
				*p1 = 0;
				strcpy(st, p);
				p1++;
				p = p1;
				p1 = strstr(p, "typeInfoId=\"");
				if (p1) {
					p = p1 + 12;
					p1 = p;
					while (*p1 && *p1 != '"') p1++;
					*p1 = 0;
					strcpy(stid, p);
				}
				else {
					stid[0] = 0;
				}
				strcpy(buf, sbuf);
				return(true);
			}
		}
	}
	return ret;
}

int beginTag(int tag)
{
	char *p;
	p = strstr(buf, "<");
	if (p) {
		if (*(p + 1) == '/') {
			if (strncasecmp(p, ETRANF, (int)strlen(ETRANF)) == 0) return PTRANF;
			return EOF;
		}
		if (tag == PSTATE) {
			if (strncasecmp(p, CENTRY, (int)strlen(CENTRY)) == 0) return PENTRY;
			if (strncasecmp(p, CTRANS, (int)strlen(CTRANS)) == 0) return PTRANS;
			return 96;
		}
		if (tag == PENTRY) {
			if (strncasecmp(p, CEXEC, (int)strlen(CEXEC)) == 0) return PEXEC;
			if (strncasecmp(p, CINIT, (int)strlen(CINIT)) == 0) return PINIT;
			if (strncasecmp(p, COPEN, (int)strlen(COPEN)) == 0) return POPEN;
			if (strncasecmp(p, CSETVAL, (int)strlen(CSETVAL)) == 0) return PSETVAL;
			if (strncasecmp(p, CADDVAL, (int)strlen(CADDVAL)) == 0) return PADDVAL;
			if (strncasecmp(p, CDOCUMENTS, (int)strlen(CDOCUMENTS)) == 0)
				return PDOCUMENTS;
			if (strncasecmp(p, CCONDACT, (int)strlen(CCONDACT)) == 0) return PCONDACT;
			if (strncasecmp(p, CSHOWMSG, (int)strlen(CSHOWMSG)) == 0) return PSHOWMSG;
			if (strncasecmp(p, CGETSHARE, (int)strlen(CGETSHARE)) == 0)
				return PGETSHARE;
			if (strncasecmp(p, CSETSHARE, (int)strlen(CSETSHARE)) == 0)
				return PSETSHARE;
			if (strncasecmp(p, CCF, (int)strlen(CCF)) == 0) return PCCF;
			if (strncasecmp(p, CPAD, (int)strlen(CPAD)) == 0) return PPAD;
			if (strncasecmp(p, CGEN, (int)strlen(CGEN)) == 0) return PGEN;
			if (strncasecmp(p, CGENEXP, (int)strlen(CGENEXP)) == 0) return PGENEXP;
			if (strncasecmp(p, CMAES, (int)strlen(CMAES)) == 0) return PMAES;
			if (strncasecmp(p, CTRIMS, (int)strlen(CTRIMS)) == 0) return PTRIM;
			if (strncasecmp(p, CINITCOLL, (int)strlen(CINITCOLL)) == 0) return PINITCOLL;
			if (strncasecmp(p, CRMCOLL, (int)strlen(CRMCOLL)) == 0) return PRMCOLL;
			if (strncasecmp(p, CRMCONTEXT, (int)strlen(CRMCONTEXT)) == 0) return PRMCONTEXT;
			if (strncasecmp(p, CUNSTR, (int)strlen(CUNSTR)) == 0) return PUNSTR;
			if (strncasecmp(p, CTRACE, (int)strlen(CTRACE)) == 0) return PTRACE;
			return 98;
		}
		if (tag == PTRANS) {
			if (strncasecmp(p, CTRAN, (int)strlen(CTRAN)) == 0) return PTRAN;
			if (strncasecmp(p, CACTION, (int)strlen(CACTION)) == 0) return PACTION;
			return 99;
		}
		if (tag == PACTION) {
			if (strncasecmp(p, CCLOSE, (int)strlen(CCLOSE)) == 0) return PCLOSE;
			return 96;
		}
		if (tag == PCONDACT) {
			if (strncasecmp(p, CCONDS, (int)strlen(CCONDS)) == 0) return PCONDS;
			return 95;
		}
		if (tag == PCONDS) {
			if (strncasecmp(p, CCOMPCOND, (int)strlen(CCOMPCOND)) == 0)
				return PCOMPCOND;
			return 94;
		}
		return 98;
	}
	return EOF;
}

int getend(char *estr, char *esync)
{
	int ret;
	Processed = 1;
	ret = mygetline(CDUMMY, NULL);
	if (ret != -2) {
		if (strstr(buf, estr))
			return true;
		if (esync && strstr(buf, esync))
			return true;
		ret = EOF;
	}
	return ret;
}

char* getView(char* p)
{
	int  i, j, k;
	for (i = 0; i < istate; i++) {
		for (j = 0; j < states[i].ientry; j++)
			for (k = 0; k < states[i].entry[j].iopen; k++)
				if (strcmp(states[i].stateid, p) == 0)
					return states[i].entry[j].sopen[k].viewname;
	}
	return p;
}

int traninfo(char *tranid, char *nstate)
{
	char *p, *p1;
	char sbuf[3000];
	strcpy(sbuf, buf);
	p = strstr(buf, CTRANID);
	if (p) {
		p = p + (int)strlen(CTRANID);
		p1 = p;
		while (*p && *p != '"') p++;
		*p = 0;
		strcpy(tranid, p1);
		p++;
	}
	else p = buf;
	p = strstr(p, CTARGET);
	if (p) {
		p = p + (int)strlen(CTARGET);
		p1 = p;
		while (*p && *p != '"') p++;
		*p = 0;
		strcpy(nstate, p1);
		strcpy(buf, sbuf);
		return true;
	}
	strcpy(buf, sbuf);
	return EOF;
}

int endtran(int indx)
{
	char tranid[200], nstate[200];
	int  iy;
	if ((strstr(buf, CTRAN) && strstr(buf, ETRAN)) || (strstr(buf, CTRAN))) {
		traninfo(tranid, nstate);
		iy = states[indx].itran;
		if ((int)strlen(tranid)) {
			states[indx].trans[iy].tranid = (char *) calloc(1, (int)strlen(tranid) + 1);
			strcpy(states[indx].trans[iy].tranid, tranid);
		}
		else states[indx].trans[iy].tranid = 0;
		if ((int)strlen(nstate)) {
			strcpy(nstate, myReplace(nstate, ' ', '_'));
			states[indx].trans[iy].trantarget = (char *) calloc(1, (int)strlen(nstate) + 1);
			strcpy(states[indx].trans[iy].trantarget, nstate);
		}
		else states[indx].trans[iy].trantarget = 0;
		states[indx].itran++;
		return true;
	}
	return EOF;
}

void ptransGet(int indx)
{
	int tag, ix;
	char *p, *p1;
	char strclose[30];
	while (getend(ETRANS, NULL) == EOF) {
		Processed = 1;
		tag = beginTag(PTRANS);
		switch (tag) {
		case PTRAN:
			while (endtran(indx) == EOF) {
				;
			}
			break;
		case PTRANF:
			break;
		case PACTION:
			while (getend(EACTION, NULL) == EOF) {
				tag = beginTag(PACTION);
				if (tag == PCLOSE) {
					p = strstr(buf, CCLOSE);
					if (p) {
						p1 = p + 1;
						p = p1;
						while (*p && *p != ' ') p++;
						*p = 0;
						strcpy(strclose, p1);
						ix = 0;
						if (states[indx].itran) {
							ix = states[indx].itran - 1;
						}
						states[indx].trans[ix].closes =
							(char *) calloc(1, (int)strlen(strclose) + 1);
						strcpy(states[indx].trans[ix].closes, strclose);
					}
				}
			}
			break;
		}
	}
}

char *params(char *target, char *p, char *ss, char c, char *txt)
{
	char sbuf[2000];
	char cstr[4];
	char *p1;
	strcpy(sbuf, buf);
	cstr[0] = c;
	cstr[1] = 0;
	p = strstr(p, ss);
	if (p) {
		if (strstr(ss, cstr)) {
			p = p + (int)strlen(ss);
			while (*p && *p == ' ') p++;
		}
		else {
			p = p + (int)strlen(ss);
			while (*p && *p != c) p++;
			if (*p == c) {
				p++;
				while (*p && *p == ' ') p++;
			}
			else {
				while (*p && *p == ' ') p++;
			}
		}
		p1 = p;
		while (*p && *p != c) p++;
		if (*p == c || *p == ' ') {
			*p = 0; p++;
		}
		p = strstr(p1, "changeState(");
		if(p) {
			p1 = p + 12;
			p = strstr(p1, ")");
			if (p) *p = 0;
			strcpy(target, p1);
		}
		else {
			strcpy(target, p1);
			p = p1;
		}
	}
	else { target[0] = 0; p = buf; }
	strcpy(buf, sbuf);
	return p;
}

int getButtonl(int indx, int ix, int iy)
{
	char *p;
	char text[300];
	char tabOrder[300];
	char lastStep[300];
	char visible[300];
	char sbuf[2000];
	int  iz;
	if (!strstr(buf, CBUTTONL)) return EOF;
	while (getend(EBUTTONL, NULL) == EOF) {
		if (strstr(buf, CFOOTER)) {
			strcpy(sbuf, buf);
			p = params(text, buf, CTEXT, '"', "FOOTER TEXT");
			p = params(tabOrder, buf, CTABORDER, '"', "FOOTER TABORDER");
			p = params(lastStep, buf, CLASTSTEP, '"', "FOOTER LASTSTEP");
			p = params(visible, buf, CVISIBLE, '"', "FOOTER VISIBLE");
			strcpy(buf, sbuf);
			iz = states[indx].entry[ix].sopen[iy].ibuttons;
			if ((int)strlen(text)) {
				states[indx].entry[ix].sopen[iy].buttons[iz].buttontext =
					(char *) calloc(1, (int)strlen(text) + 1);
				strcpy(states[indx].entry[ix].sopen[iy].buttons[iz].buttontext,
					text);
			}
			if ((int)strlen(tabOrder)) {
				states[indx].entry[ix].sopen[iy].buttons[iz].buttontabOrder =
					(char *) calloc(1, (int)strlen(tabOrder) + 1);
				strcpy(states[indx].entry[ix].sopen[iy].buttons[iz].buttontabOrder, tabOrder);
			}
			if ((int)strlen(lastStep)) {
				states[indx].entry[ix].sopen[iy].buttons[iz].buttonlastStep =
					(char *) calloc(1, (int)strlen(lastStep) + 1);
				strcpy(states[indx].entry[ix].sopen[iy].buttons[iz].buttonlastStep, lastStep);
			}
			states[indx].entry[ix].sopen[iy].ibuttons++;
		}
	}
	return true;
}

void popenGet(int indx, int ix)
{
	char *p;
	char strinit[300];
	char strvname[300];
	char strvsrc[300];
	char strlnk[300];
	char strtab[300];
	char strtitle[300];
	char strfooter[300];
	char sapproval[30];
	char sapptype[30];
	char sbuf[2000];
	int  iy;
	strcpy(sbuf, buf);
	p = params(strinit, buf, COPENID, '"', "OPEN ID");
	p = params(strvname, buf, CVIEWNAME, '"', "OPEN VNAME");
	p = params(strvsrc, buf, CVIEWSRC, '"', "OPEN VSRC");
	p = params(strlnk, buf, CLNKCONTEXT, '"', "OPEN LNKCONTEXT");
	p = params(strtab, buf, CTABINTER, '"', "OPEN TABINTER");
	p = params(strtitle, buf, CTITLE, '"', "OPEN TITLE");
	p = params(strfooter, buf, CFOOTERMSG, '"', "OPEN FOOTERMSG");
	p = params(sapproval, buf, CAPPROVAL, '"', "OPEN APPROVAL");
	p = params(sapptype, buf, CAPPTYPE, '"', "OPEN APPTYPE");
	iy = states[indx].entry[ix].iopen;
	if (iy == 0) {
		states[indx].entry[ix].sopen[iy].ibuttons = 0;
	}
	if ((int)strlen(strinit)) {
		states[indx].entry[ix].sopen[iy].openid =
			(char *) calloc(1, (int)strlen(strinit) + 1);
		strcpy(states[indx].entry[ix].sopen[iy].openid, strinit);
	}
	if ((int)strlen(strvname)) {
		states[indx].entry[ix].sopen[iy].viewname =
			(char *) calloc(1, (int)strlen(strvname) + 1);
		strcpy(states[indx].entry[ix].sopen[iy].viewname, strvname);
	}
	if ((int)strlen(strvsrc)) {
		states[indx].entry[ix].sopen[iy].viewsrc =
			(char *) calloc(1, (int)strlen(strvsrc) + 1);
		strcpy(states[indx].entry[ix].sopen[iy].viewsrc, strvsrc);
	}
	if ((int)strlen(sapproval)) {
		states[indx].entry[ix].sopen[iy].approval = false;
		if (strcmp(sapproval, "true") == 0)
			states[indx].entry[ix].sopen[iy].approval = true;
	}
	else
		states[indx].entry[ix].sopen[iy].approval = false;
	if ((int)strlen(sapptype)) {
		states[indx].entry[ix].sopen[iy].apptype = atoi(sapptype);
	}
	else
		states[indx].entry[ix].sopen[iy].apptype = 0;
	if ((int)strlen(strlnk)) {
		states[indx].entry[ix].sopen[iy].lnkcontext =
			(char *) calloc(1, (int)strlen(strlnk) + 1);
		strcpy(states[indx].entry[ix].sopen[iy].lnkcontext, strlnk);
	}
	if ((int)strlen(strtab)) {
		states[indx].entry[ix].sopen[iy].tabinter =
			(char *) calloc(1, (int)strlen(strtab) + 1);
		strcpy(states[indx].entry[ix].sopen[iy].tabinter, strtab);
	}
	if ((int)strlen(strtitle)) {
		states[indx].entry[ix].sopen[iy].title =
			(char *) calloc(1, (int)strlen(strtitle) + 1);
		strcpy(states[indx].entry[ix].sopen[iy].title, strtitle);
	}
	if ((int)strlen(strfooter)) {
		states[indx].entry[ix].sopen[iy].footermsg =
			(char *) calloc(1, (int)strlen(strfooter) + 1);
		strcpy(states[indx].entry[ix].sopen[iy].footermsg, strfooter);
	}
	states[indx].entry[ix].iopen++;
	strcpy(buf, sbuf);
}

void setvalGet(int indx, int ix)
{
	char *p;
	char dataelm[200];
	char defval[200];
	char ebuf[2000];
	int iy;
	strcpy(ebuf, buf);
	p = params(dataelm, buf, CDATAELM, '"', "SETVAL DATAELM");
	p = params(defval, buf, CDEFVAL, '"', "SETVAL DEFVALUE");
	iy = states[indx].entry[ix].isetval;
	if ((int)strlen(dataelm)) {
		states[indx].entry[ix].esetval[iy].dataelm =
			(char *) calloc(1, (int)strlen(dataelm) + 1);
		strcpy(states[indx].entry[ix].esetval[iy].dataelm, dataelm);
	}
	if ((int)strlen(defval)) {
		states[indx].entry[ix].esetval[iy].defval =
			(char *) calloc(1, (int)strlen(defval) + 1);
		strcpy(states[indx].entry[ix].esetval[iy].defval, defval);
	}
	else {
		states[indx].entry[ix].esetval[iy].defval = (char *)calloc(1, 1);
		states[indx].entry[ix].esetval[iy].defval[0] = 0;
	}
	states[indx].entry[ix].isetval++;
	strcpy(buf, ebuf);
}

void addvalGet(int indx, int ix)
{
	char* p;
	char addid[200];
	char dataelm[200];
	char defval[200];
	char ebuf[2000];
	int iy;
	strcpy(ebuf, buf);
	p = params(addid, buf, CID, '"', "ADDVAL DATAELM");
	p = params(dataelm, buf, CDATAELM, '"', "ADDVAL DATAELM");
	p = params(defval, buf, CDEFVAL, '"', "ADDVAL DEFVALUE");
	iy = states[indx].entry[ix].iaddval;
	if ((int)strlen(addid)) {
		states[indx].entry[ix].eaddval[iy].addid =
			(char*)calloc(1, (int)strlen(addid) + 1);
		strcpy(states[indx].entry[ix].eaddval[iy].addid, addid);
	}
	if ((int)strlen(dataelm)) {
		states[indx].entry[ix].eaddval[iy].dataelm =
			(char*)calloc(1, (int)strlen(dataelm) + 1);
		strcpy(states[indx].entry[ix].eaddval[iy].dataelm, dataelm);
	}
	if ((int)strlen(defval)) {
		states[indx].entry[ix].eaddval[iy].defval =
			(char*)calloc(1, (int)strlen(defval) + 1);
		strcpy(states[indx].entry[ix].eaddval[iy].defval, defval);
	}
	else {
		states[indx].entry[ix].eaddval[iy].defval = (char*)calloc(1, 1);
		states[indx].entry[ix].eaddval[iy].defval[0] = 0;
	}
	states[indx].entry[ix].iaddval++;
	strcpy(buf, ebuf);
}

void pexecGet(int indx, int ix)
{
	char *p;
	char execid[200];
	char execop[200];
	char execmon[200];
	char execlast[200];
	char execmaint[200];
	char execappr[200];
	char execlnk[200];
	char ebuf[2000];
	int  iy;
	strcpy(ebuf, buf);
	p = params(execid, buf, CEXECID, '"', "EXEC ID");
	p = params(execop, buf, CEXECOP, '"', "EXEC OPER");
	p = params(execmon, buf, CEXECMON, '"', "EXEC MON");
	p = params(execlast, buf, CEXECLAST, '"', "EXEC LAST");
	p = params(execmaint, buf, CEXECMAINT, '"', "EXEC MAINT");
	p = params(execappr, buf, CEXECAPPR, '"', "EXEC APPR");
	p = params(execlnk, buf, CEXECLNK, '"', "EXEC LNK");
	iy = states[indx].entry[ix].iexec;
	if ((int)strlen(execid)) {
		states[indx].entry[ix].eexec[iy].execid =
			(char *) calloc(1, (int)strlen(execid) + 1);
		strcpy(states[indx].entry[ix].eexec[iy].execid, execid);
	}
	if ((int)strlen(execop)) {
		states[indx].entry[ix].eexec[iy].execop =
			(char *) calloc(1, (int)strlen(execop) + 1);
		strcpy(states[indx].entry[ix].eexec[iy].execop, execop);
	}
	if ((int)strlen(execmon)) {
		states[indx].entry[ix].eexec[iy].execmon =
			(char *) calloc(1, (int)strlen(execmon) + 1);
		strcpy(states[indx].entry[ix].eexec[iy].execmon, execmon);
	}
	if ((int)strlen(execlast)) {
		states[indx].entry[ix].eexec[iy].execlast =
			(char *) calloc(1, (int)strlen(execlast) + 1);
		strcpy(states[indx].entry[ix].eexec[iy].execlast, execlast);
	}
	if ((int)strlen(execmaint)) {
		states[indx].entry[ix].eexec[iy].execmaint =
			(char *) calloc(1, (int)strlen(execmaint) + 1);
		strcpy(states[indx].entry[ix].eexec[iy].execmaint, execmaint);
	}
	if ((int)strlen(execappr)) {
		states[indx].entry[ix].eexec[iy].execappr =
			(char *) calloc(1, (int)strlen(execappr) + 1);
		strcpy(states[indx].entry[ix].eexec[iy].execappr, execappr);
	}
	if ((int)strlen(execlnk)) {
		states[indx].entry[ix].eexec[iy].execlnk =
			(char *) calloc(1, (int)strlen(execlnk) + 1);
		strcpy(states[indx].entry[ix].eexec[iy].execlnk, execlnk);
	}
	states[indx].entry[ix].iexec++;
	strcpy(buf, ebuf);
}

void getcompCond(int indx, int ix)
{
	int  iy, iz;
	char *p, sbuf[2000];
	char onTrue[200], onFalse[200];
	char opname[200];
	char firstop[200];
	char secondop[200];
	strcpy(sbuf, buf);
	p = params(onTrue, buf, CONTRUE, '"', "COMPCOND ONTRUE");
	p = params(onFalse, buf, CONFALSE, '"', "COMPCOND ONFALSE");
	iy = states[indx].entry[ix].icompcond;
	if ((int)strlen(onTrue)) {
		strcpy(onTrue, myReplace(onTrue, ' ', '_'));
		states[indx].entry[ix].ecompcon[iy].onTrue =
			(char *) calloc(1, (int)strlen(onTrue) + 1);
		strcpy(states[indx].entry[ix].ecompcon[iy].onTrue, onTrue);
	}
	if ((int)strlen(onFalse) && strcmp(onFalse, "continue")) {
		strcpy(onFalse, myReplace(onFalse, ' ', '_'));
		states[indx].entry[ix].ecompcon[iy].onFalse =
			(char *) calloc(1, (int)strlen(onFalse) + 1);
		strcpy(states[indx].entry[ix].ecompcon[iy].onFalse, onFalse);
	}
	states[indx].entry[ix].ecompcon[iy].ilogical = 0;
	while (getend(ECOMPCOND, NULL) == EOF) {
		p = strstr(buf, CLOGICAL);
		if (p) {
			strcpy(sbuf, buf);
			p = params(opname, buf, COPNAME, '"', "LOGICAL OPNAME");
			p = params(firstop, buf, CFIRSTOP, '"', "LOGICAL FIRSTOP");
			p = params(secondop, buf, CSECONDOP, '"', "LOGICAL SECONDOP");
			iz = states[indx].entry[ix].ecompcon[iy].ilogical;
			if ((int)strlen(opname)) {
				states[indx].entry[ix].ecompcon[iy].logical[iz].opname =
					(char *) calloc(1, (int)strlen(opname) + 1);
				strcpy(states[indx].entry[ix].ecompcon[iy].logical[iz].opname, opname);
			}
			if ((int)strlen(firstop)) {
				states[indx].entry[ix].ecompcon[iy].logical[iz].firstop =
					(char *) calloc(1, (int)strlen(firstop) + 1);
				strcpy(states[indx].entry[ix].ecompcon[iy].logical[iz].firstop, firstop);
			}
			if ((int)strlen(secondop)) {
				states[indx].entry[ix].ecompcon[iy].logical[iz].secondop =
					(char *) calloc(1, (int)strlen(secondop) + 1);
				strcpy(states[indx].entry[ix].ecompcon[iy].logical[iz].secondop, secondop);
			}
			strcpy(buf, sbuf);
			if ((int)strlen(opname) > 0) states[indx].entry[ix].ecompcon[iy].ilogical++;
		}
	}
	states[indx].entry[ix].icompcond++;
}

void getConds(int indx, int ix)
{
	int tag;
	while (getend(ECONDS, NULL) == EOF) {
		tag = beginTag(PCONDS);
		switch (tag) {
		case PCOMPCOND:
			getcompCond(indx, ix);
			break;
		}
	}
}

void getcondAct(int indx, int ix)
{
	int tag;

	while (getend(ECONDACT, NULL) == EOF) {
		tag = beginTag(PCONDACT);
		switch (tag) {
		case PCONDS:
			getConds(indx, ix);
			break;
		}
	}
}

void getshowMsg(int indx, int ix)
{
	int  iy;
	char id[200];
	char title[200];
	char messageType[200];
	char Msgval[2000];
	char optionType[200];
	char defaults[200];
	char *p, sbuf[2000];
	strcpy(sbuf, buf);
	iy = states[indx].entry[ix].ishowmsg;
	p = params(id, buf, CSHOWID, '"', "SHOW ID");
	p = params(Msgval, buf, CSHOWMSGX, '"', "SHOW MSG");
	p = params(title, buf, CSHOWTITLE, '"', "SHOW TITLE");
	p = params(messageType, buf, CSHOWMSGTYPE, '"', "SHOW MSGTYPE");
	p = params(optionType, buf, CSHOWOPTTYPE, '"', "SHOW OPT TYPE");
	p = params(defaults, buf, CSHOWDEFAULT, '"', "SHOW DEFAULT");
	if ((int)strlen(id)) {
		states[indx].entry[ix].eshowmsg[iy].showid =
			(char *) calloc(1, (int)strlen(id) + 1);
		strcpy(states[indx].entry[ix].eshowmsg[iy].showid, id);
	}
	if ((int)strlen(Msgval)) {
		states[indx].entry[ix].eshowmsg[iy].message =
			(char *)calloc(1, (int)strlen(Msgval) + 1);
		strcpy(states[indx].entry[ix].eshowmsg[iy].message, Msgval);
	}
	if ((int)strlen(title)) {
		states[indx].entry[ix].eshowmsg[iy].title =
			(char *) calloc(1, (int)strlen(title) + 1);
		strcpy(states[indx].entry[ix].eshowmsg[iy].title, title);
	}
	if ((int)strlen(messageType)) {
		states[indx].entry[ix].eshowmsg[iy].messageType =
			(char *) calloc(1, (int)strlen(messageType) + 1);
		strcpy(states[indx].entry[ix].eshowmsg[iy].messageType, messageType);
	}
	if ((int)strlen(optionType)) {
		states[indx].entry[ix].eshowmsg[iy].optionType =
			(char *) calloc(1, (int)strlen(optionType) + 1);
		strcpy(states[indx].entry[ix].eshowmsg[iy].optionType, optionType);
	}
	if ((int)strlen(defaults)) {
		states[indx].entry[ix].eshowmsg[iy].defaultOption =
			(char *) calloc(1, (int)strlen(defaults) + 1);
		strcpy(states[indx].entry[ix].eshowmsg[iy].defaultOption, defaults);
	}
	strcpy(buf, sbuf);
	if ((int)strlen(id) > 0) states[indx].entry[ix].ishowmsg++;
}

void getShare(int indx, int ix)
{
	int  iy;
	char id[200];
	char cvar[200];
	char var[200];
	char *p, sbuf[2000];
	strcpy(sbuf, buf);
	p = params(id, buf, CSETSHAREID, '"', "SETSHARE ID");
	p = params(cvar, buf, CSETSHAREVAR, '"', "SETSHARE VAR");
	p = params(var, buf, CSETSHAREVAL, '"', "SETSHARE VAL");
	iy = states[indx].entry[ix].igetshare;
	if ((int)strlen(id)) {
		states[indx].entry[ix].egetshare[iy].shareid =
			(char *) calloc(1, (int)strlen(id) + 1);
		strcpy(states[indx].entry[ix].egetshare[iy].shareid, id);
	}
	if ((int)strlen(cvar)) {
		states[indx].entry[ix].egetshare[iy].sharecvar =
			(char *) calloc(1, (int)strlen(cvar) + 1);
		strcpy(states[indx].entry[ix].egetshare[iy].sharecvar, cvar);
	}
	if ((int)strlen(var)) {
		states[indx].entry[ix].egetshare[iy].sharevar =
			(char *) calloc(1, (int)strlen(var) + 1);
		strcpy(states[indx].entry[ix].egetshare[iy].sharecvar, var);
	}
	strcpy(buf, sbuf);
	if ((int)strlen(id) > 0) states[indx].entry[ix].igetshare++;
}

void setShare(int indx, int ix)
{
	int  iy;
	char id[200];
	char cvar[200];
	char var[200];
	char *p, sbuf[2000];
	strcpy(sbuf, buf);
	p = params(id, buf, CSETSHAREID, '"', "SETSHARE ID");
	p = params(cvar, buf, CSETSHAREVAR, '"', "SETSHARE VAR");
	p = params(var, buf, CSETSHAREVAL, '"', "SETSHARE VAL");
	strcpy(buf, sbuf);
	iy = states[indx].entry[ix].isetshare;
	if ((int)strlen(id)) {
		states[indx].entry[ix].esetshare[iy].setid =
			(char *) calloc(1, (int)strlen(id) + 1);
		strcpy(states[indx].entry[ix].esetshare[iy].setid, id);
	}
	if ((int)strlen(cvar)) {
		states[indx].entry[ix].esetshare[iy].setcvar =
			(char *) calloc(1, (int)strlen(cvar) + 1);
		strcpy(states[indx].entry[ix].esetshare[iy].setcvar, cvar);
	}
	if ((int)strlen(var)) {
		states[indx].entry[ix].esetshare[iy].setvar =
			(char *) calloc(1, (int)strlen(var) + 1);
		strcpy(states[indx].entry[ix].esetshare[iy].setvar, var);
	}
	if ((int)strlen(id) > 0) states[indx].entry[ix].isetshare++;
}

void getPad(int indx, int ix)
{
	int  iy;
	char id[200];
	char dname[200];
	char padchar[200];
	char padlen[200];
	char align[200];
	char *p, sbuf[2000];
	strcpy(sbuf, buf);
	iy = states[indx].entry[ix].ipad;
	p = params(id, buf, CPADID, '"', "PAD ID");
	p = params(dname, buf, CPADDNAME, '"', "PAD DNAME");
	p = params(padchar, buf, CPADCHAR, '"', "PAD CHAR");
	p = params(padlen, buf, CPADLEN, '"', "PAD LEN");
	p = params(align, buf, CPADALIGN, '"', "PAD ALIGN");
	if ((int)strlen(id)) {
		states[indx].entry[ix].epad[iy].padid = (char *) calloc(1, (int)strlen(id) + 1);
		strcpy(states[indx].entry[ix].epad[iy].padid, id);
	}
	if ((int)strlen(dname)) {
		states[indx].entry[ix].epad[iy].dname = (char *) calloc(1, (int)strlen(dname) + 1);
		strcpy(states[indx].entry[ix].epad[iy].dname, dname);
	}
	if ((int)strlen(padchar)) {
		states[indx].entry[ix].epad[iy].padchar =
			(char *) calloc(1, (int)strlen(padchar) + 1);
		strcpy(states[indx].entry[ix].epad[iy].padchar, padchar);
	}
	if ((int)strlen(padlen)) {
		states[indx].entry[ix].epad[iy].padlen =
			(char *) calloc(1, (int)strlen(padlen) + 1);
		strcpy(states[indx].entry[ix].epad[iy].padlen, padlen);
	}
	if ((int)strlen(align)) {
		states[indx].entry[ix].epad[iy].padalign =
			(char *) calloc(1, (int)strlen(align) + 1);
		strcpy(states[indx].entry[ix].epad[iy].padalign, align);
	}
	if ((int)strlen(id) > 0) states[indx].entry[ix].igen++; states[indx].entry[ix].iccf++; states[indx].entry[ix].ipad++;
	strcpy(buf, sbuf);
}

void getCCF(int indx, int ix)
{
	int  iy;
	char id[200];
	char cust[200];
	char sig[200];
	char *p, sbuf[2000];
	strcpy(sbuf, buf);
	iy = states[indx].entry[ix].iccf;
	p = params(id, buf, CCFID, '"', "CCF ID");
	p = params(cust, buf, CCFCUST, '"', "CCF CUST");
	p = params(sig, buf, CCFSIGN, '"', "CCF SIGN");
	if ((int)strlen(id)) {
		states[indx].entry[ix].eccf[ix].ccfid =
			(char *) calloc(1, (int)strlen(id) + 1);
		strcpy(states[indx].entry[ix].eccf[ix].ccfid, id);
	}
	if ((int)strlen(cust)) {
		states[indx].entry[ix].eccf[ix].cust =
			(char *) calloc(1, (int)strlen(cust) + 1);
		strcpy(states[indx].entry[ix].eccf[ix].cust, cust);
	}
	if ((int)strlen(sig)) {
		states[indx].entry[ix].eccf[ix].sig =
			(char *) calloc(1, (int)strlen(sig) + 1);
		strcpy(states[indx].entry[ix].eccf[ix].sig, sig);
	}
	if ((int)strlen(id) > 0) states[indx].entry[ix].igen++; states[indx].entry[ix].iccf++;
	strcpy(buf, sbuf);
}

void getGEN(int indx, int ix)
{
	int iy;
	char id[200];
	char acc[200];
	char br[200];
	char cd[200];
	char iban[200];
	char *p, sbuf[2000];
	strcpy(sbuf, buf);
	iy = states[indx].entry[ix].igen;
	p = params(id, buf, CGENID, '"', "GEN ID");
	p = params(acc, buf, CGENACC, '"', "GEN ACC");
	p = params(br, buf, CGENBR, '"', "GEN BR");
	p = params(cd, buf, CGENCD, '"', "GEN CD");
	p = params(iban, buf, CGENIBAN, '"', "GEN IBAN");
	if ((int)strlen(id)) {
		states[indx].entry[ix].egen[iy].genid = (char *) calloc(1, (int)strlen(id) + 1);
		strcpy(states[indx].entry[ix].egen[iy].genid, id);
	}
	if ((int)strlen(acc)) {
		states[indx].entry[ix].egen[iy].genacc = (char *) calloc(1, (int)strlen(acc) + 1);
		strcpy(states[indx].entry[ix].egen[iy].genacc, acc);
	}
	if ((int)strlen(br)) {
		states[indx].entry[ix].egen[iy].genbr = (char *) calloc(1, (int)strlen(br) + 1);
		strcpy(states[indx].entry[ix].egen[iy].genbr, br);
	}
	if ((int)strlen(cd)) {
		states[indx].entry[ix].egen[iy].gencd = (char *) calloc(1, (int)strlen(cd) + 1);
		strcpy(states[indx].entry[ix].egen[iy].gencd, cd);
	}
	if ((int)strlen(iban)) {
		states[indx].entry[ix].egen[iy].geniban = (char *) calloc(1, (int)strlen(iban) + 1);
		strcpy(states[indx].entry[ix].egen[iy].geniban, iban);
	}
	if ((int)strlen(id) > 0) states[indx].entry[ix].igen++;
	strcpy(buf, sbuf);
}

void getGENEXP(int indx, int ix)
{
	int  iy;
	char *p, sbuf[2000];
	char expid[200], id[200];
	strcpy(sbuf, buf);
	iy = states[indx].entry[ix].igenexp;
	p = params(id, buf, CGENID, '"', "GEN ID");
	p = params(expid, buf, CGENEXPID, '"', "GEN EXPID");
	if ((int)strlen(id)) {
		states[indx].entry[ix].egenexp[iy].genid = (char *)calloc(1, (int)strlen(id) + 1);
		strcpy(states[indx].entry[ix].egenexp[iy].genid, id);
	}
	if ((int)strlen(expid)) {
		states[indx].entry[ix].egenexp[iy].genexpid = (char *)calloc(1, (int)strlen(expid) + 1);
		strcpy(states[indx].entry[ix].egenexp[iy].genexpid, expid);
	}
	if ((int)strlen(id) > 0) states[indx].entry[ix].igenexp++;
	strcpy(buf, sbuf);
}

void getMAES(int indx, int  ix)
{
	int  iy;
	char id[200];
	char docbr[200];
	char docdt[200];
	char docmaint[200];
	char view[200];
	char doctype[200];
	char optype[200];
	char dochost[200];
	char docid[200];
	char doccust[200];
	char scan[200];
	char *p, sbuf[2000];
	strcpy(sbuf, buf);
	iy = states[indx].entry[ix].igen;
	p = params(id, buf, CMAESID, '"', "MAES ID");
	p = params(docbr, buf, CMAESDOCBR, '"', "MAES DOCBR");
	p = params(docdt, buf, CMAESDOCDT, '"', "MAES DOCDT");
	p = params(docmaint, buf, CMAESDOCMAINT, '"', "MAES DOCMAINT");
	p = params(view, buf, CMAESVIEW, '"', "MAES VIEW");
	p = params(doctype, buf, CMAESDOCTYPE, '"', "MAES DOCTYPE");
	p = params(optype, buf, CMAESOPTYPE, '"', "MAES OPTYPE");
	p = params(dochost, buf, CMAESDOCHOST, '"', "MAES DOCHOST");
	p = params(docid, buf, CMAESDOCID, '"', "MAES DOCID");
	p = params(doccust, buf, CMAESDOCCUST, '"', "MAES DOCCUST");
	p = params(scan, buf, CMAESSCAN, '"', "MAES SCAN");
	if ((int)strlen(id)) {
		states[indx].entry[ix].emaes[iy].maesid =
			(char *) calloc(1, (int)strlen(id) + 1);
		strcpy(states[indx].entry[ix].emaes[iy].maesid, id);
	}
	if ((int)strlen(docbr)) {
		states[indx].entry[ix].emaes[iy].maesdocbr =
			(char *) calloc(1, (int)strlen(docbr) + 1);
		strcpy(states[indx].entry[ix].emaes[iy].maesdocbr, docbr);
	}
	if ((int)strlen(docdt)) {
		states[indx].entry[ix].emaes[iy].maesdocdt =
			(char *) calloc(1, (int)strlen(docdt) + 1);
		strcpy(states[indx].entry[ix].emaes[iy].maesdocdt, docdt);
	}
	if ((int)strlen(docmaint)) {
		states[indx].entry[ix].emaes[iy].maesdocmaint =
			(char *) calloc(1, (int)strlen(docmaint) + 1);
		strcpy(states[indx].entry[ix].emaes[iy].maesdocmaint, docmaint);
	}
	if ((int)strlen(view)) {
		states[indx].entry[ix].emaes[iy].maesview =
			(char *) calloc(1, (int)strlen(view) + 1);
		strcpy(states[indx].entry[ix].emaes[iy].maesview, view);
	}
	if ((int)strlen(doctype)) {
		states[indx].entry[ix].emaes[iy].maesdoctype =
			(char *) calloc(1, (int)strlen(doctype) + 1);
		strcpy(states[indx].entry[ix].emaes[iy].maesdoctype, doctype);
	}
	if ((int)strlen(optype)) {
		states[indx].entry[ix].emaes[iy].maesoptype =
			(char *) calloc(1, (int)strlen(optype) + 1);
		strcpy(states[indx].entry[ix].emaes[iy].maesoptype, optype);
	}
	if ((int)strlen(dochost)) {
		states[indx].entry[ix].emaes[iy].maesdochost =
			(char *) calloc(1, (int)strlen(dochost) + 1);
		strcpy(states[indx].entry[ix].emaes[iy].maesdochost, dochost);
	}
	if ((int)strlen(docid)) {
		states[indx].entry[ix].emaes[iy].maesdocid =
			(char *) calloc(1, (int)strlen(docid) + 1);
		strcpy(states[indx].entry[ix].emaes[iy].maesdocid, docid);
	}
	if ((int)strlen(doccust)) {
		states[indx].entry[ix].emaes[iy].maesdoccust =
			(char *) calloc(1, (int)strlen(doccust) + 1);
		strcpy(states[indx].entry[ix].emaes[iy].maesdoccust, doccust);
	}
	if ((int)strlen(scan)) {
		states[indx].entry[ix].emaes[iy].maesscan =
			(char *) calloc(1, (int)strlen(scan) + 1);
		strcpy(states[indx].entry[ix].emaes[iy].maesscan, scan);
	}
	if((int)strlen(id) > 0) states[indx].entry[ix].igen++;
	strcpy(buf, sbuf);
}

void getTrim(int indx, int  ix)
{
	int  iy;
	char id[200];
	char var[200];
	char trimc[200];
	char trimd[200];
	char *p, sbuf[2000];
	strcpy(sbuf, buf);
	iy = states[indx].entry[ix].itrim;
	p = params(id, buf, CTRIMID, '"', "TRIM ID");
	p = params(var, buf, CTRIMVAR, '"', "TRIM ID");
	p = params(trimc, buf, CTRIMCHAR, '"', "TRIM CHAR");
	p = params(trimd, buf, CTRIMDIR, '"', "TRIM DIR");
	if ((int)strlen(id)) {
		states[indx].entry[ix].etrim[iy].trimid =
			(char *) calloc(1, (int)strlen(id) + 1);
		strcpy(states[indx].entry[ix].etrim[iy].trimid, id);
	}
	if ((int)strlen(var)) {
		states[indx].entry[ix].etrim[iy].trimvar =
			(char *) calloc(1, (int)strlen(var) + 1);
		strcpy(states[indx].entry[ix].etrim[iy].trimvar, var);
	}
	if ((int)strlen(trimc)) {
		states[indx].entry[ix].etrim[iy].trimchar =
			(char *) calloc(1, (int)strlen(trimc) + 1);
		strcpy(states[indx].entry[ix].etrim[iy].trimchar, trimc);
	}
	if ((int)strlen(trimd)) {
		states[indx].entry[ix].etrim[iy].trimdir =
			(char *) calloc(1, (int)strlen(trimd) + 1);
		strcpy(states[indx].entry[ix].etrim[iy].trimdir, trimd);
	}
	if((int)strlen(id) > 0) states[indx].entry[ix].itrim++;
	strcpy(buf, sbuf);
}

void getinitColl(int indx, int  ix)
{
	int iy;
	char id[200];
	char delm[200];
	char *p, sbuf[2000];
	strcpy(sbuf, buf);
	iy = states[indx].entry[ix].iinitcoll;
	p = params(id, buf, CINITCOLLID, '"', "INITCOLL ID");
	p = params(delm, buf, CINITCOLLDELM, '"', "INITCOLL DELM");
	if ((int)strlen(id)) {
		states[indx].entry[ix].einitcoll[iy].id =
			(char *) calloc(1, (int)strlen(id) + 1);
		strcpy(states[indx].entry[ix].einitcoll[iy].id, id);
	}
	if ((int)strlen(delm)) {
		states[indx].entry[ix].einitcoll[iy].delm =
			(char *) calloc(1, (int)strlen(delm) + 1);
		strcpy(states[indx].entry[ix].einitcoll[iy].delm, delm);
	}
	if((int)strlen(id) > 0 && (int)strlen(delm) > 0)
		states[indx].entry[ix].iinitcoll++;
	strcpy(buf, sbuf);
}

void getrmColl(int indx, int  ix)
{
	int iy;
	char id[200];
	char delm[200];
	char poly[200];
	char repno[200];
	char *p, sbuf[2000];
	strcpy(sbuf, buf);
	iy = states[indx].entry[ix].irmcoll;
	p = params(id, buf, CRMCOLLID, '"', "RMCOLL ID");
	p = params(delm, buf, CRMCOLLDELM, '"', "RMCOLL DELM");
	p = params(poly, buf, CRMCOLLPOLY, '"', "RMCOLL POLY");
	p = params(repno, buf, CRMCOLLREPNO, '"', "RMCOLL REPNO");
	if ((int)strlen(id)) {
		states[indx].entry[ix].ermcoll[iy].id =
			(char *) calloc(1, (int)strlen(id) + 1);
		strcpy(states[indx].entry[ix].ermcoll[iy].id, id);
	}
	if ((int)strlen(delm)) {
		states[indx].entry[ix].ermcoll[iy].delm =
			(char *) calloc(1, (int)strlen(delm) + 1);
		strcpy(states[indx].entry[ix].ermcoll[iy].delm, delm);
	}
	if ((int)strlen(poly)) {
		states[indx].entry[ix].ermcoll[iy].poly =
			(char *) calloc(1, (int)strlen(poly) + 1);
		strcpy(states[indx].entry[ix].ermcoll[iy].poly, poly);
	}
	if ((int)strlen(repno)) {
		states[indx].entry[ix].ermcoll[iy].repno =
			(char *) calloc(1, (int)strlen(delm) + 1);
		strcpy(states[indx].entry[ix].ermcoll[iy].repno, repno);
	}
	if ((int)strlen(id) > 0 && (int)strlen(delm) > 0)
		states[indx].entry[ix].irmcoll++;
	strcpy(buf, sbuf);
}

void getrmContext(int indx, int  ix)
{
	int iy;
	char id[200];
	char delm[200];
	char *p, sbuf[2000];
	strcpy(sbuf, buf);
	iy = states[indx].entry[ix].irmcontext;
	p = params(id, buf, CRMCONTEXTID, '"', "RMCONTEXT ID");
	p = params(delm, buf, CRMCONTEXTDELM, '"', "RMCONTEXT DELM");
	if ((int)strlen(id)) {
		states[indx].entry[ix].ermcontext[iy].id =
			(char *)calloc(1, (int)strlen(id) + 1);
		strcpy(states[indx].entry[ix].ermcontext[iy].id, id);
	}
	if ((int)strlen(delm)) {
		states[indx].entry[ix].ermcontext[iy].delm =
			(char *)calloc(1, (int)strlen(delm) + 1);
		strcpy(states[indx].entry[ix].ermcontext[iy].delm, delm);
	}
	states[indx].entry[ix].irmcontext++;
	strcpy(buf, sbuf);
}

void getUnstr(int indx, int  ix)
{
	int iy;
	char src[200];
	char srcdata[200];
	char *p, *p1, sbuf[2000];
	strcpy(sbuf, buf);
	iy = states[indx].entry[ix].iunstr;
	p = params(src, buf, CUNSTRSRC, '"', "CUNSTR SRC");
	p = params(srcdata, buf, src, '/', "CUNSTR SRCDATA");
	if ((int)strlen(src)) {
		states[indx].entry[ix].unstr[iy].src =
			(char *)calloc(1, (int)strlen(src) + 1);
		strcpy(states[indx].entry[ix].unstr[iy].src, src);
	}
	if ((int)strlen(srcdata)) {
		p = strstr(srcdata, "\" ");
		if (p) {
			p = p+2;
			p1 = strstr(p, "\"");
			if (p1) {
				*p1 = 0;
				p1++;
				p = p1;
			}
		}
		else p = srcdata;
		p1 = strstr(p, ";");
		if (p1) { *p1 = 0; p1++;	}
		else p1 = srcdata;
		states[indx].entry[ix].unstr[iy].start = atoi(p);
		states[indx].entry[ix].unstr[iy].len = atoi(p1);
	}
	states[indx].entry[ix].iunstr++;
	strcpy(buf, sbuf);
}

void getTRACE(int indx, int ix)
{
	int iy;
	char id[200];
	char trc0[200];
	char trc1[200];
	char trc2[200];
	char *p, *p1, sbuf[2000];
	strcpy(sbuf, buf);
	iy = states[indx].entry[ix].itrace;
	p = params(id,   buf, CTRACEID, '\"', "CTRACE ID");
	p = params(trc0, buf, CTRACE0,  '\"', "CTRACE0 DATA");
	p = params(trc1, buf, CTRACE1,  '\"', "CTRACE1 DATA");
	p = params(trc2, buf, CTRACE2,  '\"', "CTRACE2 DATA");
	if ((int)strlen(id)) {
		states[indx].entry[ix].etrace[iy].traceid =
			(char *)calloc(1, (int)strlen(id) + 1);
		strcpy(states[indx].entry[ix].etrace[iy].traceid, id);
	}
	if ((int)strlen(trc0)) {
		p = strstr(trc0, "\"");
		if (p) {
			p = p + 2;
			p1 = strstr(p, "\"");
			if (p1) {
				*p1 = 0;
				p1++;
				p = p1;
			}
		}
		else p = trc0;
		p1 = strstr(p, ";");
		if (p1) { *p1 = 0; p1++; }
		else p1 = trc0;
		states[indx].entry[ix].etrace[iy].trace0 = (char *) calloc(1, strlen(trc0)+1);
		strcpy(states[indx].entry[ix].etrace[iy].trace0, trc0);
	}
	if ((int)strlen(trc1)) {
		p = strstr(trc1, "\"");
		if (p) {
			p = p + 2;
			p1 = strstr(p, "\"");
			if (p1) {
				*p1 = 0;
				p1++;
				p = p1;
			}
		}
		else p = trc1;
		p1 = strstr(p, ";");
		if (p1) { *p1 = 0; p1++; }
		else p1 = trc1;
		states[indx].entry[ix].etrace[iy].trace1 = (char *)calloc(1, strlen(trc1) + 1);
		strcpy(states[indx].entry[ix].etrace[iy].trace1, trc1);
	}
	if ((int)strlen(trc2)) {
		p = strstr(trc2, "\"");
		if (p) {
			p = p + 2;
			p1 = strstr(p, "\"");
			if (p1) {
				*p1 = 0;
				p1++;
				p = p1;
			}
		}
		else p = trc2;
		p1 = strstr(p, ";");
		if (p1) { *p1 = 0; p1++; }
		else p1 = trc2;
		states[indx].entry[ix].etrace[iy].trace2 = (char *)calloc(1, strlen(trc2) + 1);
		strcpy(states[indx].entry[ix].etrace[iy].trace2, trc2);
	}
	states[indx].entry[ix].itrace++;
	strcpy(buf, sbuf);
}

int newentry(int indx)
{
	int ix;
	ix = states[indx].ientry;
	states[indx].entry[ix].iexec = 0;
	states[indx].entry[ix].iopen = 0;
	states[indx].entry[ix].isetval = 0;
	states[indx].entry[ix].ishowmsg = 0;
	states[indx].entry[ix].icompcond = 0;
	states[indx].entry[ix].igetshare = 0;
	states[indx].entry[ix].isetshare = 0;
	states[indx].entry[ix].iccf = 0;
	states[indx].entry[ix].ipad = 0;
	states[indx].entry[ix].igen = 0;
	states[indx].entry[ix].igenexp = 0;
	states[indx].entry[ix].imaes = 0;
	states[indx].entry[ix].iunstr = 0;
	states[indx].entry[ix].itrace = 0;
	states[indx].ientry++;
	return ix;
}

void pentryGet(int indx, int ix)
{
	int  tag;
	char prt[200];
	char *p, *p1;
	char strinit[200];
	while (getend(EENTRY, NULL) == EOF) {
		Processed = 1;
		tag = beginTag(PENTRY);

		switch (tag) {
		case PINIT:
			while (!strstr(buf, EINIT)) {
				p = strstr(buf, CINITID);
				if (p) {
					p = p + (int)strlen(CINITID);
					p1 = p;
					while (*p && *p != '"') p++;
					*p = 0;
					strcpy(strinit, p1);

					states[indx].entry[ix].initid =
						(char *) calloc(1, (int)strlen(strinit) + 1);
					strcpy(states[indx].entry[ix].initid, strinit);
				}
			}
			break;
		case POPEN:
			popenGet(indx, ix);
			break;
		case PSETVAL:
			setvalGet(indx, ix);
			while (!strstr(buf, ESETVAL)) {
				;
			}
			break;
		case PADDVAL:
			addvalGet(indx, ix);
			while (!strstr(buf, ESETVAL)) {
				;
			}
			break;
		case PDOCUMENTS:
			params(prt, buf, "id=\"", '"', "DOC PRNT");
			if ((int)strlen(prt)) {
				states[indx].entry[ix].eprintid = (char *) calloc(1, (int)strlen(prt) + 1);
				strcpy(states[indx].entry[ix].eprintid, prt);
			}
			while (!strstr(buf, EDOCUMENTS)) {
				;
			}
			break;
		case PEXEC:
			pexecGet(indx, ix);
			while (getend(EEXEC, ENDEXEC) == EOF) {
				;
			}
			break;
		case PCONDACT:
			getcondAct(indx, ix);
			break;
		case PSHOWMSG:
			getshowMsg(indx, ix);
			break;
		case PGETSHARE:
			getShare(indx, ix);
			break;
		case PSETSHARE:
			setShare(indx, ix);
			break;
		case PPAD:
			getPad(indx, ix);
			break;
		case PCCF:
			getCCF(indx, ix);
			break;
		case PGEN:
			getGEN(indx, ix);
			break;
		case PMAES:
			getMAES(indx, ix);
			break;
		case PTRIM:
			getTrim(indx, ix);
			break;
		case PINITCOLL:
			getinitColl(indx, ix);
			break;
		case PRMCOLL:
			getrmColl(indx, ix);
			break;
		case PUNSTR:
			getUnstr(indx,ix);
			break;
		case PGENEXP:
			getGENEXP(indx, ix);
			break;
		case PTRACE:
			getTRACE(indx, ix);
			break;
		case PRMCONTEXT:
			getrmContext(indx, ix);
			break;
		}
	}
}

//void myReplace(char *str, char s, char t)
//{
//	int i, len;
//	len = (int)strlen(str);
//	for (i = 0; i<len; i++) {
//		if (str[i] == s) str[i] = t;
//		switch ((int)str[i])
//		{
//		case 'ç':
//			str[i] = 'c';
//			break;
//		case 'ğ':
//			str[i] = 'g';
//			break;
//		case 'ı':
//			str[i] = 'i';
//			break;
//		case 'ö':
//			str[i] = 'o';
//			break;
//		case 'ş':
//			str[i] = 's';
//			break;
//		case 'ü':
//			str[i] = 'u';
//			break;
//		default:
//			break;
//		}
//		if (!(str[i] >= 'A' || str[i] <= 'Z') &&
//			!(str[i] >= 'a' || str[i] <= 'z') &&
//			!(str[i] >= '0' || str[i] <= '9'))
//			str[i] = t;
//	}
//}

char *myReplace(char *str, char s, char trg)
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
		str = (char *)calloc(1, strlen(t) + 1);
		strcpy(str, t);
	}
	else strcpy(str, t);
	return str;
}

char *buyukHarf(char *s)
{
	char *p = (char *)calloc(1, strlen(s) + 1);
	strcpy(p, s);
	if (p[0] >= 'a' && p[0] <= 'z') {
		p[0] = p[0] - 'a' + 'A';
	}
	return p;
}

char *kucukHarf(char *s)
{
	char *p = (char *)calloc(1, strlen(s) + 1);
	strcpy(p, s);
	if (p[0] >= 'A' && p[0] <= 'Z') {
		p[0] = p[0] - 'A' + 'a';
	}
	return p;
}

char *constVal(char* p)
{
	int  i;
	for (i = 0; i < iconstant; i++) {
		if (strcmp(constants[i].vname, p) == 0)
			return p;
	}
	return 0;
}

int constVarmi(char *p)
{
	int  i;
	for (i = 0; i < iconstant; i++) {
		if (strcmp(constants[i].vname, p) == 0)
			return 1;
	}
	return 0;
}

void readconst(char *ffile, char *cfile)
{
	int  i;
	FILE *fp;
	char *p, *p1;
	char vvype[100];
	iconstant = 0;
	fp = fopen(ffile, "r");
	if (fp) {
		while (fgets(buf, MAXCHAR, fp)) {
			rmnl(buf);

			p = strstr(buf, ".");
			if (p) {
				*p = 0;
				p++;
				strcpy(vvype, buf);
				i = iconstant;
				p1 = strstr(p, "=");
				if (p1) {
					*p1 = 0; p1++;
					if (constVarmi(p) == 0) {
						p = myReplace(p, ' ', ' ');
						constants[i].vtype = (char *)calloc(1, strlen(vvype) + 1);
						strcpy(constants[i].vtype, vvype);
						constants[i].vval = (char *)calloc(1, strlen(p) + 1);
						strcpy(constants[i].vval, buyukHarf(p));
						constants[i].vname = (char *)calloc(1, strlen(p1) + 1);
						strcpy(constants[i].vname, buyukHarf(p1));
						iconstant++;
					}
				}
			}
		}
		fclose(fp);
		if (constVarmi("\"\"") == 0) {
			i = iconstant;
			constants[i].vtype = (char *)calloc(1, 6);
			strcpy(constants[i].vtype,"init");
			constants[i].vname = (char *)calloc(1, 3);
			strcpy(constants[i].vname, "\"\"");
			constants[i].vval = (char *)calloc(1, 9);
			strcpy(constants[i].vval, "emptystr");
			iconstant++;
		}
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
				i = iconstant;
				constants[i].vtype = (char *)calloc(1, strlen(buf) + 1);
				strcpy(constants[i].vtype, buf);
				p1 = strstr(p, "=");
				if (p1) {
					*p1 = 0; p1++;
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
}

int controllervarmi(char *p)
{
	int i, k;
	for (i = 0; i < icontrollerstart; i++) {
		if (strcmp(controllerstart[i], p) == 0)
			for (k = 0; k < iflowcall; k++) {
				if (strcmp(flowcall[k].funcname, p) == 0)
					return 1;
			}
	}
	return 0;
}
void readcontrollers(char *cpref)
{
	int  i;
	FILE *fx;
	char bfx[MAXCHAR + 1];
	i = 0;
	fx = fopen(cpref, "r");
	if (fx) {
		while(fgets(bfx, MAXCHAR, fx)) {
			rmnl(bfx);
			controllerstart[i] = (char *)calloc(1, strlen(bfx) + 1);
			strcpy(controllerstart[i], buyukHarf(bfx));
			i++;
		}
		fclose(fx);
		icontrollerstart = i;
	}
}

void AddViewtoView(char *intype, char *rtype)
{
	int  i;
	for (i = 0; i < iviewview; i++) {
		if (strcmp(viewview[i].view1Name, buyukHarf(intype)) == 0 &&
			strcmp(viewview[i].view2Name, buyukHarf(rtype)) == 0)
			return;
	}

	i = iviewview;
	viewview[i].view1Name = (char *)calloc(1, strlen(intype) + 1);
	strcpy(viewview[i].view1Name, buyukHarf(intype));
	viewview[i].view2Name = (char *)calloc(1, strlen(rtype) + 1);
	strcpy(viewview[i].view2Name, buyukHarf(rtype));
	iviewview++;
}

void AddMCAtoView(char *myexecop, char *target)
{
	int  i;
	for (i = 0; i < imcaview; i++) {
		if (strcmp(mcaview[i].mcaName, buyukHarf(myexecop)) == 0 &&
			strcmp(mcaview[i].viewName, buyukHarf(target)) == 0)
			return;
	}
	i = imcaview;
	mcaview[i].mcaName = (char *)calloc(1, strlen(myexecop) + 1);
	strcpy(mcaview[i].mcaName, buyukHarf(myexecop));
	mcaview[i].viewName = (char *)calloc(1, strlen(target) + 1);
	strcpy(mcaview[i].viewName, buyukHarf(target));
	imcaview++;
}

int itekekran;
char tekekran[20][200];
int tekEkranmi(char *s)
{
	int i;
	if (strlen(s) < 1) return 0;
	for (i = 0; i < itekekran; i++) {
		if (strcmp(tekekran[i], buyukHarf(s)) == 0)
			return 1;
	}
	i = itekekran;
	strcpy(tekekran[i], buyukHarf(s));
	itekekran++;
	return 0;
}


void statePrologue(char *prog, char *sname, char *areaName)
{
	// int i,j;
	fprintf(output, "// Generated by BE-CON Automatic Face Converter V:1.0\n\n");
	fprintf(output, "using AkbankFace.Web.Common;\n");
	fprintf(output, "using AkbankFace.Web.Common.Interfaces;\n");
	fprintf(output, "using System;\n");
	fprintf(output, "using System.Collections.Generic;\n");
	fprintf(output, "using System.Linq;\n");
	fprintf(output, "using System.Web;\n");
	fprintf(output, "using AkbankFace.Web.%s.ClientBusiness;\n", areaName);
	fprintf(output, "using System.Runtime.Serialization;\n");
	fprintf(output, "using AkbankFace.Web.%s.Common;\n", areaName);
	fprintf(output, "using AkbankFace.Web.%s.Common.Constants;\n", areaName);
	fprintf(output, "using AkbankFace.Web.%s.Models;\n", areaName);
	fprintf(output, "using AkbankFace.BranchBanking.Common;\n");

	fprintf(output, "namespace AkbankFace.Web.%s.ClientBusiness\n", areaName);
	fprintf(output, "{\n\n");

	indents=2;
	fprintf(output, "%s", indentstr());
	fprintf(output, "[Serializable]\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "public class %sFlow : PageFlow\n", sname);
	fprintf(output, "%s", indentstr());
	fprintf(output, "{\n");
}

void flowConstants(char *filename, char *prog, char *sname, char *areaName)
{
	int i, j, k;
	fprintf(output, "name.%s=%s\n", prog, prog);
	for (i = 0; i < istate; i++) {
		/*states[i].stateid = myReplace(states[i].stateid, ' ', '_');*/
		if (strstr(states[i].statetype, "view")) {
			for (j = 0; j< states[i].ientry; j++) {
				for (k = 0; k< states[i].entry[j].iopen; k++) {
					fprintf(output, "view.%s=%s\n",
						states[i].entry[j].sopen[k].viewname,
						states[i].stateid);
				}
			}
		}
	}
	fprintf(output, "view.vcontroller=%s\n", tranname);
	for (i = 0; i < istate; i++) {
		/*states[i].stateid = myReplace(states[i].stateid, ' ', '_');*/
		if (strncmp(states[i].statetype, "action", 6) == 0)
			fprintf(output, "action.%s=%s\n",
			states[i].stateid, states[i].stateid);
	}
	for (i = 0; i < istate; i++) {
		/*states[i].stateid = myReplace(states[i].stateid, ' ', '_');*/
		if (strncmp(states[i].statetype, "condition", 9) == 0)
			fprintf(output, "cond.%s=%s\n",
			states[i].stateid, states[i].stateid);
	}
	for (i = 0; i < istate; i++) {
		
		/*states[i].stateid = myReplace(states[i].stateid, ' ', '_');*/
		if (strncmp(states[i].statetype, "operation", 9) == 0)
			fprintf(output, "oper.%s=%s\n",
			states[i].stateid, states[i].stateid);
	}
	for (i = 0; i < istate; i++) {
		/*states[i].stateid = myReplace(states[i].stateid, ' ', '_');*/
		if (strncmp(states[i].statetype, "flow", 4) == 0)
			fprintf(output, "flow.%s=%s\n",
			states[i].stateid, states[i].stateid);
	}
	for (i = 0; i < istate; i++) {
		/*states[i].stateid = myReplace(states[i].stateid, ' ', '_');*/
		if (strncmp(states[i].statetype, "initial", 7) == 0)
			fprintf(output, "flow.%s=%s\n",
			states[i].stateid, states[i].stateid);
	}
	for (i = 0; i < istate; i++) {
		/*states[i].stateid = myReplace(states[i].stateid, ' ', '_');*/
		if (strncmp(states[i].statetype, "final", 5) == 0)
			fprintf(output, "final.%s=%s\n",
			states[i].stateid, states[i].stateid);
	}
}


void writetrim(int ison, struct TRIM trim[])
{
	int i;
	for (i = 0; i < ison; i++) {
		fprintf(output, "\t\tTRIM\tid %s var %s char %s dir %s\n",
			trim[i].trimid,
			trim[i].trimvar,
			trim[i].trimchar,
			trim[i].trimdir);
	}
}

void writemaes(int ison, struct MAES maes[])
{
	int i;
	for (i = 0; i < ison; i++) {
		fprintf(output, "\t\tMAES\tid %s docbr %s docdt %s docmaint %s view %s doctype %s optype %s dochost %s docid %s doccust %si scan %s\n",
			maes[i].maesid,
			maes[i].maesdocbr,
			maes[i].maesdocdt,
			maes[i].maesdocmaint,
			maes[i].maesview,
			maes[i].maesdoctype,
			maes[i].maesoptype,
			maes[i].maesdochost,
			maes[i].maesdocid,
			maes[i].maesdoccust,
			maes[i].maesscan);
	}
}

void writegen(int ison, struct GEN gen[])
{
	int i;
	for (i = 0; i < ison; i++) {
		fprintf(output, "\t\tGEN\tid %s acc %s br %s cd%s iban %s\n",
			gen[i].genid,
			gen[i].genacc,
			gen[i].genbr,
			gen[i].gencd,
			gen[i].geniban);
	}
}

void writeccf(int ison, struct CCCF ccf[])
{
	int i;
	for (i = 0; i < ison; i++) {
		fprintf(output, "\t\tCCF\tid %s cust %s sig %s\n",
			ccf[i].ccfid,
			ccf[i].cust,
			ccf[i].sig);
	}
}

void writepad(int ison, struct PAD pad[])
{
	int i;
	for (i = 0; i < ison; i++) {
		fprintf(output, "\t\tPAD\tid %s dname %s pchar %s plen %s palign %s\n",
			pad[i].padid,
			pad[i].dname,
			pad[i].padchar,
			pad[i].padlen,
			pad[i].padalign);
	}
}

void writesetshare(int ison, struct SETSHARE setshare[])
{
	int i;
	for (i = 0; i < ison; i++) {
		fprintf(output, "\t\tSETSHARE\tid %s cvar %s var %s\n",
			setshare[i].setid,
			setshare[i].setcvar,
			setshare[i].setvar);
	}
}

void writegetshare(int ison, struct GETSHARE getshare[])
{
	int i;
	for (i = 0; i < ison; i++) {
		fprintf(output, "\t\tGETSHARE\tid %s cvar %s var %s\n",
			getshare[i].shareid,
			getshare[i].sharecvar,
			getshare[i].sharevar);
	}
}

void writeshowmsg(int ison, struct SHOWMSG showmsg[])
{
	int i;
	for (i = 0; i < ison; i++) {
		fprintf(output, "\t\tSHOWMSG\tid %s msg %s title %s msgType %s opType %s defaultOp %s\n",
			showmsg[i].showid,
			showmsg[i].message,
			showmsg[i].title,
			showmsg[i].messageType,
			showmsg[i].optionType,
			showmsg[i].defaultOption);
	}
}

void writecompcon(int ison, struct COMPCON compcon[])
{
	int i, j;
	for (i = 0; i < ison; i++) {
		fprintf(output, "\t\tCOMPCON\tonTrue %s onFalse %s\n",
			compcon[i].onTrue,
			compcon[i].onFalse);
		for (j = 0; j < compcon[i].ilogical; j++) {
			fprintf(output, "\t\t\t\topname %s firstop %s second %s\n",
				compcon[i].logical[j].opname,
				compcon[i].logical[j].firstop,
				compcon[i].logical[j].secondop);
		}
	}
}

void writesetval(int ison, struct SETVAL setval[])
{
	int i;
	for (i = 0; i < ison; i++) {
		fprintf(output, "\t\tSETVAL\telm %s defval %s\n",
			setval[i].dataelm,
			setval[i].defval);
	}
}

void writesopen(int ison, struct OPENX sopen[])
{
	int i, j;
	for (i = 0; i < ison; i++) {
		fprintf(output, "\t\tOPEN\tid %s vname %s vsrc %s approval %d apptype %d lnk %s tab %s title %s footer %s\n",
			sopen[i].openid,
			sopen[i].viewname,
			sopen[i].viewsrc,
			sopen[i].approval,
			sopen[i].apptype,
			sopen[i].lnkcontext,
			sopen[i].tabinter,
			sopen[i].title,
			sopen[i].footermsg);
		for (j = 0; j < sopen[i].ibuttons; j++) {
			fprintf(output, "\t\t\t\ttext %s tab %s last %s visible %ss\n",
				sopen[i].buttons[j].buttontext,
				sopen[i].buttons[j].buttontabOrder,
				sopen[i].buttons[j].buttonlastStep,
				sopen[i].buttons[j].buttonvisible);
		}
	}
}

void writeexec(int ison, struct EXEC eexec[])
{
	int i;
	for (i = 0; i < ison; i++) {
		fprintf(output, "\t\tEXEC\tid %s op %s mon %s last %s maint %s appr %s lnk %s\n",
			eexec[i].execid,
			eexec[i].execop,
			eexec[i].execmon,
			eexec[i].execlast,
			eexec[i].execmaint,
			eexec[i].execappr,
			eexec[i].execlnk);
	}
}

/* ****************************************************************** */

int stateVarmi(char *trg)
{
	int i, j = 0;
	for (i = 0; i < istate; i++) {
		if (strcmp(states[i].stateid, trg) == 0)
			return i;
	}
	return -1;
}

void writeDebug(char *fdir, char *prog, char *sname)
{
	int i, j, ij, jj;
	for (i = 0; i < istate; i++) {
		fprintf(output, "%d %s %s\n", i, states[i].stateid, states[i].statetype);
		for (j = 0; j < states[i].itran; j++) {
			fprintf(output, "\t%d id %s closes %s target %s\n", j,
				states[i].trans[j].tranid,
				states[i].trans[j].closes,
				states[i].trans[j].trantarget);
		}
		if (states[i].ientry) fprintf(output, "\t\tientry %d\n", states[i].ientry);
		for (j = 0; j < states[i].ientry; j++) {
			if (states[i].entry[j].initid)
				fprintf(output, "\t\tinitid %s\n", states[i].entry[j].initid);
			if (states[i].entry[j].iexec)
				writeexec(states[i].entry[j].iexec, states[i].entry[j].eexec);
			if (states[i].entry[j].iopen)
				writesopen(states[i].entry[j].iopen, states[i].entry[j].sopen);
			if (states[i].entry[j].isetval)
				writesetval(states[i].entry[j].isetval, states[i].entry[j].esetval);
			if (states[i].entry[j].eprintid)
				fprintf(output, "\t\tprintid %s\n", states[i].entry[j].eprintid);
			if (states[i].entry[j].icompcond)
				writecompcon(states[i].entry[j].icompcond, states[i].entry[j].ecompcon);
			if (states[i].entry[j].ishowmsg)
				writeshowmsg(states[i].entry[j].ishowmsg, states[i].entry[j].eshowmsg);
			if (states[i].entry[j].igetshare)
				writegetshare(states[i].entry[j].igetshare, states[i].entry[j].egetshare);
			if (states[i].entry[j].isetshare)
				writesetshare(states[i].entry[j].isetshare, states[i].entry[j].esetshare);
			if (states[i].entry[j].ipad)
				writepad(states[i].entry[j].ipad, states[i].entry[j].epad);
			if (states[i].entry[j].iccf)
				writeccf(states[i].entry[j].iccf, states[i].entry[j].eccf);
			if (states[i].entry[j].igen)
				writegen(states[i].entry[j].igen, states[i].entry[j].egen);
			if (states[i].entry[j].imaes)
				writemaes(states[i].entry[j].imaes, states[i].entry[j].emaes);
			if (states[i].entry[j].itrim)
				writetrim(states[i].entry[j].itrim, states[i].entry[j].etrim);
		}
	}
	fprintf(output, "Undefined States\n");
	for (i = 0; i < istate; i++) {
		for (j = 0; j < states[i].itran; j++) {
			ij = stateVarmi(states[i].trans[j].trantarget);
			if (ij < 0)
				fprintf(output, "\ttarget %s has no id\n", states[i].trans[j].trantarget);
		}
	}
	fprintf(output, "End of Undefined States\n");
	fprintf(output, "imca %d\n", imca);
	for (i = 0; i<imca; i++) {
		fprintf(output, "%s %s(%s)\n", mca[i].code, mca[i].fname, mca[i].recname);
		for (j = 0; j<mca[i].imarr; j++) {
			fprintf(output, "\t%s %s\n", mca[i].marr[j].mcacode, mca[i].marr[j].mcaitem);
		}
		for (jj = 0; jj < mca[i].icols; jj++) {
			if (mca[i].cols[jj].icol) fprintf(output, "%s %s\n", mca[i].cols[jj].colcode, mca[i].cols[jj].colname);
			for (j = 0; j < mca[i].cols[jj].icol; j++) {
				fprintf(output, "\t%s %s\n", mca[i].cols[jj].col[j].mcaccode, mca[i].cols[jj].col[j].colitem);
			}
		}
	}
	fprintf(output, "ivname %d\n", ivname);
	for (i = 0; i<ivname; i++) {
		fprintf(output, "%s %s(%s)\n", vname[i].vcode, vname[i].viewname, vname[i].vrecname);
		for (j = 0; j<vname[i].ivitem; j++) {
			fprintf(output, "\t%s %s\n", vname[i].items[j].vitemcode, vname[i].items[j].vitem);
		}
		if (vname[i].iarray) fprintf(output, "%s %s\n", vname[i].arrcode, vname[i].arrayName);
		for (j = 0; j<vname[i].iarray; j++) {
			fprintf(output, "\t%s %s\n", vname[i].arr[j].arritemcode, vname[i].arr[j].arritem);
		}
	}
}

char *vmodelpBak(char *s)
{
	int  i;
	for (i = 0; i < ivmodel; i++) {
		if (strcmp(vmodel[i].sid, s) == 0) {
			return vmodel[i].sview;
		}
	}
	return 0;
}

void writeFlows(char *fdir, char *prog, char *sname, char *areaName)
{
	int  i;
	char *p;
	// burada yeni constant degerleri olmali
	if (indexname[0] == 0) {
		for (i = 0; i < istate; i++) {
			if (strcmp(states[i].statetype, "initial") == 0) {
				p = vmodelpBak(states[i].stateid);
				strcpy(indexname, p);
			}
		}
	}
	flowConstants(fdir, prog, sname, areaName);
}

void writeflowPref(char *fdir, char *prog, char *sname, char *areaName)
{
	int  i, j, k;
	char *p;
	getModelState();
	// burada yeni constant degerleri olmali
	if (indexname[0] == 0) {
		for (i = 0; i < istate; i++) {
			if (strcmp(states[i].statetype, "initial") == 0) {
				p = vmodelpBak(states[i].stateid);
				strcpy(indexname, p);
				break;
			}
		}
	}
	for (i = 0; i < istate; i++) {
		//states[i].stateid = myReplace(states[i].stateid, ' ', '_');
		//states[i].stateid = myReplace(states[i].stateid, '-', '_');
		if (strncmp(states[i].statetype, "view", 4) == 0) {
			//states[i].stateid = myReplace(states[i].stateid, ' ', '_');
			//states[i].stateid = myReplace(states[i].stateid, '-', '_');
			/* *********************************************************
			*   add open entry id = stateid <tranid>flow.preference entry
			* *********************************************************/
			for (j = 0; j< states[i].ientry; j++) {
				for (k = 0; k< states[i].entry[j].iopen; k++) {
					fprintf(output, "%s=%s\n",
						states[i].entry[j].sopen[k].viewname,
						states[i].stateid);
				}
			}
		}
	}
}

int extraParam(char *ss)
{
	int i;
	for (i = 0; i < iextras; i++) {
		if (strcmp(extras[i], ss) == 0)
			return 1;
	}
	return 0;
}

/*********************************************************vmodel islemleri ***********************************************************/

int  targetVarmi(char *s, char *ss)
{
	int i, j;
	for (i = 0; i < ivmodel; i++) {
		for (j = 0; vmodel[i].stranid[j] != NULL; j++)
			if(ss) {
				if (strcmp(vmodel[i].sid, s) == 0 && strstr(vmodel[i].stranid[j], ss))
					return 1;
			}
			else {
				if (strcmp(vmodel[i].starget[j], s) == 0)
					return 1;
			}
	}
	return 0;
}

void vmodelTasi(int start, int ii, int jj)
{
	int  k, j, i = ivmodel;
	char *p, *p1;
	char bfx[200];
	int islem = 0;
	vmodel[i].istart = start;
	vmodel[i].is = ii;
	vmodel[i].smodel = 0;
	vmodel[i].sview = 0;
	vmodel[i].sid = (char *)calloc(1, strlen(states[ii].stateid) + 1);
	strcpy(vmodel[i].sid, states[ii].stateid);
	vmodel[i].stype = (char *)calloc(1, strlen(states[ii].statetype) + 1);
	strcpy(vmodel[i].stype, states[ii].statetype);
	if (strcmp(vmodel[i].stype, "final") == 0) {
		vmodel[i].starget[jj] = vmodel[0].sid;
		ivmodel++;
		return;
	}
	if (states[ii].itran > 0) {
		for (j = 0; j < states[ii].itran; j++) {
			if (targetVarmi(states[ii].stateid, states[ii].trans[j].tranid) == 1) return;
			vmodel[i].starget[j] = (char *)calloc(1, strlen(states[ii].trans[j].trantarget) + 1);
			strcpy(vmodel[i].starget[j], states[ii].trans[j].trantarget);
			strcpy(bfx, states[ii].trans[j].tranid);
			p1 = strstr(bfx, ".");
			if(p1) p1++;
			else  p1 = bfx;
			p = strstr(p1, ".");
			if (p) *p = 0;
			vmodel[i].stranid[j] = (char *)calloc(1, strlen(p1) + 1);
			strcpy(vmodel[i].stranid[j], p1); // states[ii].trans[j].tranid;
			islem = 1;
		}
	}
	if (states[ii].ientry > 0 && ivmodel < istate) {
		for (j = 0; j < states[ii].ientry; j++) {
				for (k = 0; k < states[ii].entry[j].iopen; k++) {
					if (strcmp(states[ii].entry[j].sopen[k].openid, "filler")) {
						vmodel[i].sview = (char *)calloc(1, strlen(states[ii].entry[j].sopen[k].viewname) + 1);
						strcpy(vmodel[i].sview, states[ii].entry[j].sopen[k].viewname);
						islem = 1;
						break;
					}
				}
				for (k = 0; k < states[ii].entry[j].iexec; k++) {
					vmodel[i].smodel = (char *)calloc(1, strlen(states[ii].entry[j].eexec[k].execop) + 1);
					strcpy(vmodel[i].smodel, states[ii].entry[j].eexec[k].execop);
					p = strstr(vmodel[i].smodel, "ClientOp");
					if (p) {
						*p = 0;
					}
					islem = 1;
					break;
				}
				for (k = 0; k < states[ii].entry[j].icompcond; k++) {
					vmodel[i].starget[jj] = (char *)calloc(1, strlen(states[ii].entry[j].ecompcon[k].onTrue) + 1);
					strcpy(vmodel[i].starget[jj], states[ii].entry[j].ecompcon[k].onTrue);
					islem = 1;
					break;
				}
		}
	}
	if (islem) ivmodel++;
}

int vmodelBak(int ii)
{
	int  i;
	for (i = 0; i < ivmodel; i++) {
		if (vmodel[i].is == ii) return i;
	}
	return -1;
}

void vmodelViewCopy(int m, char *si, char *p)
{
	int ii, j;
	// BURADA ivmoodel in tumu icin degil m degerine kadar bak
	// for (ii = 0; ii < ivmodel; ii++)
	for (ii = m; ii < ivmodel; ii++)
		for (j = 0; vmodel[ii].starget[j] != NULL; j++) {
			if (strcmp(p, "filler") && strstr(vmodel[ii].starget[j], si)) {
				if (vmodel[ii].sview == NULL) {
					vmodel[ii].sview = (char *)calloc(1, strlen(p) + 1);
					if(vmodel[ii].sview) strcpy(vmodel[ii].sview, p);
					vmodelViewCopy(ii, vmodel[ii].sid, p);
				}
			}
		}
}

int vmodelModelCopy(int m, char *si, char *p)
{
	int ii, j, kopya=0;
	for (ii = 0; ii < ivmodel; ii++)
		for (j = 0; vmodel[ii].starget[j] != NULL; j++) {
			if (strstr(vmodel[ii].starget[j], si) && p) {
				if (vmodel[ii].smodel == NULL) {
					vmodel[ii].smodel = (char *)calloc(1, strlen(p) + 1);
					if(vmodel[ii].smodel) strcpy(vmodel[ii].smodel, p);
					kopya++;
					kopya += vmodelModelCopy(ii, vmodel[ii].sid, p);
				}
				else return kopya;
			}
		}
	return kopya;
}

void vmodelViewTasi(int m, char *p)
{
	int  ii, j;
	if (m >= 0 && vmodel[m].sview != NULL) {
		if (strcmp(p, "filler")) {
			vmodel[m].sview = (char *)calloc(1, strlen(p) + 1);
			if(vmodel[m].sview) strcpy(vmodel[m].sview, p);
			for (ii = 0; ii < m; ii++) {
				for (j = 0; vmodel[m].starget[j] != NULL; j++)
					if (vmodel[m].sid && vmodel[ii].starget[j] && 
						strcmp(vmodel[m].sid, vmodel[ii].starget[j]) == 0)
							vmodelViewTasi(ii, p);
			}
		}
	}
}

void vmodelTargetTasi(int m, int j, char *ss, char *ps)
{
	int  ii;
	char *p, *p1;
	char bfx[200];
	strcpy(bfx, ss);
	if (m >= 0 && vmodel[m].starget[j] == NULL) {
		p = strstr(bfx, ".");
		if (p) {
			p++;
			p1 = p;
		}
		else p1 = bfx;
		p = strstr(p1, ".");
		if (p) *p = 0;
		vmodel[m].stranid[j] = (char *)calloc(1, strlen(p1) + 1);
		if(vmodel[m].stranid[j]) strcpy(vmodel[m].stranid[j], p1);
		vmodel[m].starget[j] = (char *)calloc(1, strlen(ps) + 1);
		if(vmodel[m].starget[j]) strcpy(vmodel[m].starget[j], ps);
		// vmodelTargetTasi(m - 1, j, ss, p);
		for (ii = 0; ii < m; ii++) {
			for (j = 0; vmodel[m].starget[j] != NULL; j++)
				if (vmodel[m].sid && vmodel[ii].starget[j] && strcmp(vmodel[m].sid, vmodel[ii].starget[j]) == 0)
					vmodelTargetTasi(ii, j, p1, ps);
		}
	}
}

void checkOthers(int mi, int ii)
{
	int  j;
	if (states[ii].ientry > 0) {
		for (j = 0; j < states[ii].ientry; j++) {
			if (states[ii].entry[j].iopen > 0)
				vmodelViewTasi(mi, states[ii].entry[j].sopen[0].viewname);
		}
	}
	if (states[ii].itran > 0) {
		for (j = 0; j < states[ii].itran; j++) {
			if (states[ii].trans[j].trantarget) {
				vmodelTargetTasi(mi, j, states[ii].trans[j].tranid, states[ii].trans[j].trantarget);
			}
		}
	}
}

void getModelState()
{
	int  i=0;
	int  m = 0;
	int  mi;
	for (i = 0; i < istate; i++) {
		mi = m;
		if (strcmp(states[i].statetype, "initial") == 0) {
			vmodelTasi(mi, i, 0);
			m++;
			checkOthers(mi, i);
		}
		else {
			// vmodel de daha once yoksa
			if (vmodelBak(i) < 0) {
				vmodelTasi(mi, i, 0);
				// target olarak varsa
				if (targetVarmi(states[i].stateid, states[i].statetype))
					vmodel[mi].istart++;
				m++;
				checkOthers(mi, i);
			}
		}
	}
	for (i = 0; i < ivmodel; i++) {
		if (vmodel[i].sview != NULL) {
			vmodelViewCopy(i, vmodel[i].sid, vmodel[i].sview);
		}
	}
	for (i = 0; i < ivmodel; i++) {
		if (vmodel[i].smodel != NULL) {
			vmodelModelCopy(i, vmodel[i].sid, vmodel[i].smodel);
		}
	}
	for (i = 0; i < ivmodel; i++) {
		if (vmodel[i].sview == NULL) {
			//BURADA: sview null ise ilkekrani tasi
			if (strlen(indexname) > 0) {
				vmodel[i].sview = (char*)calloc(1, strlen(indexname) + 1);
				if (vmodel[i].sview) strcpy(vmodel[i].sview, indexname);
			}
			else {
				vmodel[i].sview = (char*)calloc(1, 5);
				if (vmodel[i].sview) strcpy(vmodel[i].sview, "void");
			}
		}
	}
}

int vmodelindx(char *ss)
{
	int  i;
	for (i = 0; i < ivmodel; i++) {
		if (strcmp(ss, vmodel[i].sid) == 0) {
			return i;
		}
	}
	return -1;
}

int vmodeliiBak(char *ss)
{
	int  i;
	for (i = 0; i < ivmodel; i++) {
		if (strcmp(vmodel[i].sid, ss) == 0) {
			if (vmodel[i].smodel) return -1;
			if (vmodel[i].istart == 0) return i;
			return -1;
		}
	}
	return -1;
}

int vmodeliiGet(char *ss)
{
	int i;
	char *p, *p1;
	if (ss == NULL) return -1;
	for (i = 0; i < ivmodel; i++) {
		p1 = strstr(ss, "changeState(");
		if (p1) {
			p1 = p1 + 12;
		}
		else p1 = ss;
		p = strstr(p1, ")");
		if (p) *p = 0;
		if (strcmp(vmodel[i].sid, p1) == 0)
			return i;
	}
	return -1;
}

int vmodelviewBak(char *ss)
{
	int  i;
	for (i = 0; i < ivmodel; i++) {
		if (strcmp(vmodel[i].sid, ss) == 0) {
			if (vmodel[i].sview) return -1;
			if (vmodel[i].istart == 0) return i;
			return -1;
		}
	}
	return -1;
}

char *modelBak(int ii)
{

	int i;
	for (i = 0; i < ivmodel; i++) {
		if (vmodel[i].is == ii)
			return vmodel[i].smodel;
	}
	return 0;
}
/*************************************************************************************************************************************/
int viewElement(char *s)
{
	int i, j;
	for (i = 0; i < ivname; i++) {
		for (j = 0; j < vname[i].ivitem; j++) {
			if (strcmp(vname[i].items[j].vitem, s) == 0)
				return i * 1000 + j;
		}
		for (j = 0; j < vname[i].iarray; j++) {
			if (strcmp(vname[i].arr[j].arritem, s) == 0)
				return i * 1000 + j;
		}
	}
	return -1;
}

int viewElementMi(char *view, char *s)
{
	int i, j;
	for (i = 0; i < ivname; i++) {
		if (strcmp(vname[i].viewname, view) == 0) {
			for (j = 0; j < vname[i].ivitem; j++) {
				if (strcmp(vname[i].items[j].vitem, s) == 0)
					return j;
			}
			for (j = 0; j < vname[i].iarray; j++) {
				if (strcmp(vname[i].arr[j].arritem, s) == 0)
					return j;
			}
		}
	}
	return -1;
}
char *viewBak(char *view)
{ 
	int j, i;
	for (i = 0; i < iviews; i++) {
		if (strcmp(fviews[i].v2, view) == 0)
			return fviews[i].v1;
		if (strcmp(fviews[i].v1, view) == 0)
			return fviews[i].v1;
	}
	for (j = iviews; j<200; j++) {
		if (strcmp(fviews[j].v1, view) == 0) continue;
		if (fviews[j].v1[0] == 0) {
			strcpy(fviews[j].v1, view);
			fviews[j].v1[0] = 0;
			break;
		}
	}
	return 0;
}

char *viewArrMi(char *s)
{
	int i, j;
	for (i = 0; i < ivname; i++) {
		if (vname[i].iarray > 0) {
			for (j = 0; j < vname[i].iarray; j++) {
				if (strcmp(vname[i].arr[j].arritem, s) == 0)
					return vname[i].arrayName;
			}
		}
	}
	return 0;
}

void noViews()
{
	int j;
	for (j = iviews; j<200; j++) {
		if (fviews[j].v1[0] == 0) break;
		fprintf(output, "%s\n", fviews[j].v1);
	}
}

int iflowfunc = 0;
int flowii[200];
int flowjj[200];

void addToFunctions(int ii, int jj)
{
	int  i;
	for (i = 0; i < iflowfunc; i++) {
		if (flowii[i] == ii)
			return;
	}
	i = iflowfunc;
	flowii[i] = ii;
	flowjj[i] = jj;
	iflowfunc++;
}

void initMonetary(int i)
{
	int j, set = 1;
	int yazdi = 0;
	char dummy[50];
	char other[50];
	strcpy(other, " ");

	strcpy(dummy, "fraudApp");
	strcpy(initialscr, states[i].stateid);
	fprintf(output, "Flow.Configure(%sConstants.FlowView.ViewIndex)\n", tranname);
	indents++;
	for (j = 0; j<states[i].itran; j++) {
		if (states[i].itran >= 1) {
			fprintf(output, "%s", indentstr());
			if (strstr(states[i].trans[j].tranid, ".FRAUD")) {
				fprintf(output, ".Allow(Trigger.Next, %s%s)",
					other, dummy);
				yazdi = 1;
			}
			else {
				if (yazdi) {
					fprintf(output, "\n");
					fprintf(output, "%s", indentstr());
				}
				if (strcmp(states[i].trans[j].trantarget, initialscr) == 0 || 
					strcmp(states[i].trans[j].trantarget, indexname) == 0)
					fprintf(output, ".Allow(Trigger.Next, %sConstants.FlowView.ViewIndex)", tranname);
				else {
					if (strstr(states[i].trans[j].trantarget, "final")) {
						fprintf(output, ".Allow(Trigger.Previous, %sConstants.FlowView.final)",
							tranname);
						if (set) {
							fprintf(output, "\n");
							fprintf(output, "%s", indentstr());
							fprintf(output, ".AllowDynamic(Trigger.Next, %sSelectScreen)", other); // , states[i].stateid);
							set = 0;
						}
						addToFunctions(i, j);
					}
				}
				if (strcmp(states[i].statetype, "initial") == 0) {
					fprintf(output, ".AllowDynamic(Trigger.Next, %sSelectScreen)", other); // , states[i].stateid);
					addToFunctions(i, -1);
				}
				yazdi = 1;
			}
		}
		if (yazdi) break;
	}
	fprintf(output, ";\n");
	indents--;
}

void fraudApp(int i, int otherSet)
{
	int j;
	char other[30];
	// burada fraudApp icin function call var
	fprintf(output, "%s", indentstr());
	fprintf(output, "Flow.Configure(flow%s)\n", states[i].stateid);
	indents++;
	if (otherSet)
		strcpy(other, "Business.");
	else strcpy(other, " ");
	for (j = 0; j<states[i].itran; j++) {
		fprintf(output, "%s", indentstr());
		fprintf(output, ".AllowIf(Trigger.Next, fraudapp, %s%s)",
			other, states[i].trans[j].trantarget);
		fprintf(output, ";\n");
	}
	indents--;
}

void finals(int i)
{
	fprintf(output, "%s", indentstr());
	fprintf(output, "  // final state ======\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "Flow.Configure(%sConstants.FlowView.final)\n", tranname);  // states[i].stateid);
	indents++;
	fprintf(output, "%s", indentstr());
	fprintf(output, ".Allow(Trigger.Next, \"\");\n");
	indents--;
}

void myapproval(char *trns, char *prgname)
{
	indents = 1;
	fprintf(output, "public ModelBase ApprovalGet(string akbankFaceApprovalActivityId, string akbankFaceApprovalProcessId, string akbankFaceApprovalStatus, string akbankFaceApprovalTransactionName)\n");
	fprintf(output, "    {\n");
	fprintf(output, "        return base.ApprovalGet<%sRequestMsg, %sResponseMsg>(akbankFaceApprovalActivityId, akbankFaceApprovalProcessId, akbankFaceApprovalStatus, akbankFaceApprovalTransactionName);\n", prgname, prgname);
	fprintf(output, "    }\n");

	fprintf(output, "public ModelBase ApprovalPost(ModelBase model, string commandName, string approvalProcessId, string approvalActivityId, string approvalStatus)\n");
	fprintf(output, "    {\n");
	fprintf(output, "        return base.ApprovalPost<%sRequestMsg, %sMsg>(model, commandName, approvalProcessId, approvalActivityId, approvalStatus);\n", prgname, prgname);
	fprintf(output, "    }\n");
	fprintf(output, "public string ApprovalReturn(string approvalProcessId, string approvalActivityId, string transactionName)\n");
	fprintf(output, "    {\n");
	fprintf(output, "        return ApprovalReturn<%sRequestMsg>(approvalProcessId, approvalActivityId,transactionName);\n", prgname);
	fprintf(output, "    }\n");
}

void mydataArea(char *trns, char *prgname)
{
	int  i, say;
	indents = 1;
	fprintf(output, "      public  %s%sModel model;\n", trns, prgname);
	say = 1;
	for (i = 0; i<ivname; i++) {
		if (strstr(vname[i].viewname, "KriterView"))
			fprintf(output, "        public %s%sModel model = new %s%sViewModel();\n", tranname, vname[i].viewname, tranname, vname[i].viewname);
		else fprintf(output, "        public %sModel model = new %sViewModel();\n", vname[i].viewname, vname[i].viewname);
		if (vname[i].iarray) {
			fprintf(output, "        public List<%sModel.%sModel> %sList = new List<%sModel.%sModel>();\n",
				vname[i].viewname, vname[i].arrayName,
				vname[i].arrayName,
				vname[i].viewname, vname[i].arrayName);
		}
		say++;
	}
	say = 1;
	for (i = 0; i<imca; i++) {
		fprintf(output, "        public %sModel MCAmodel%d = new %sModel();\n",
			mca[i].fname, say, mca[i].fname);
		say++;
	}
}

void approvalActions(char *prog, char *trns, char *areaName, char *requestMsg)
{
	indents = 1;
	fprintf(output, "        public IPageFlow GetApprovalFlow()\n");
	fprintf(output, "        {\n");
	fprintf(output, "            return new %sFlow();\n", trns);
	fprintf(output, "        }\n");
	fprintf(output, "        public ModelBase Approval(IPageFlow flow, string akbankFaceApprovalActivityId, string akbankFaceApprovalProcessId, string akbankFaceApprovalStatus, string akbankFaceApprovalTransactionName)\n");
	fprintf(output, "        {\n");
	fprintf(output, "            base.Approval<%s>(flow, akbankFaceApprovalActivityId, akbankFaceApprovalProcessId, akbankFaceApprovalStatus, akbankFaceApprovalTransactionName);\n", requestMsg);
	fprintf(output, "            DtsUlkeTatilGuncelBORequestMsg requestMsg = flow.GetApprovalRequest<%s>();\n", requestMsg);
	fprintf(output, "            if (requestMsg != null)\n");
	fprintf(output, "            {\n");
	fprintf(output, "                return MapFromApprovalRequest(requestMsg);\n");
	fprintf(output, "            }\n");
	fprintf(output, "            return new AkbankFaceEmptyModel();\n");

	fprintf(output, "        }\n");

	fprintf(output, "        private ModelBase MapFromApprovalRequest(%s requestMsg)\n", requestMsg);
	fprintf(output, "        {\n");
	fprintf(output, "            throw new NotImplementedException();\n");
	fprintf(output, "        }\n");

	fprintf(output, "}\n");
}

int  itekmi = 0;
char tekvar[MSMAX][100];

int  is;
char prevop[200][30];
int frtype = 0; // 1 bool, 2 vmodel, 3 void, 4 mca, 5 string

int  tekmi(char *name)
{
	int i;
	int len = (int)strlen(name);
	for (i = 0; i<itekmi; i++) {
		if (strcasecmp(tekvar[i], name) == 0)
			return 0;
	}
	i = itekmi;
	itekmi++;
	strcpy(tekvar[i], name);
	return 1;
}

char *initVariables(char *p)
{
	int  i;
	char bufp[200], *p1, *py;
	if (!p) return 0;
	p = buyukHarf(p);
	py = buyukHarf(indexname);
	p = myReplace(p, '-', '_');
	if (p[0] == 0 || strcmp(p, "\"\"") == 0) {
		sprintf(bufp, "%sConstants.emptystr", tranname);
		p1 = (char*)calloc(1, strlen(bufp) + 1);
		strcpy(p1, bufp);
		return p1;
	}
	if (strstr(p, "Constants"))
		strcpy(bufp, p);
	else {
		for (i = 0; i < iconstant; i++) {
			if (!constants[i].vval) continue;
			constants[i].vval = myReplace(constants[i].vval, ' ', '_');
			py = constants[i].vname;
			if (strcmp(constants[i].vname, indexname) == 0)
				py = "ViewIndex";
			if (strcmp(constants[i].vname, p) == 0) {
				if (strcmp(constants[i].vtype, "init") == 0) {
					py = constants[i].vval;
					p1 = strstr(py, "\"");
					if (p1) *p1 = 0;
					sprintf(bufp, "%sConstants.Init%s", tranname, py);
					p1 = (char*)calloc(1, strlen(bufp) + 1);
					strcpy(p1, bufp);
					return p1;
				}
				if (strcmp(constants[i].vtype, "view") == 0) {
					py = constants[i].vval;
					p1 = strstr(py, "\"");
					if (p1) *p1 = 0;
					sprintf(bufp, "%sConstants.FlowView.%s", tranname, py);
					p1 = (char*)calloc(1, strlen(bufp) + 1);
					strcpy(p1, bufp);
					return p1;
				}
				if (strcmp(constants[i].vtype, "flowtag") == 0 || 
					strcmp(constants[i].vtype, "flow") == 0 || 
					strcmp(constants[i].vtype, "action") == 0) {
					py = constants[i].vval;
					p1 = strstr(py, "\"");
					if (p1) *p1 = 0;
					sprintf(bufp, "%sConstants.FlowTag.%s", tranname, py);
					p1 = (char*)calloc(1, strlen(bufp) + 1);
					strcpy(p1, bufp);
					return p1;
				}
				if (strcmp(constants[i].vtype, "oper") == 0 || 
					strcmp(constants[i].vtype, "func") == 0) {
					py = constants[i].vval;
					p1 = strstr(py, "\"");
					if (p1) *p1 = 0;
					sprintf(bufp, "%sConstants.FuncTag.%s", tranname, py);
					p1 = (char*)calloc(1, strlen(bufp) + 1);
					strcpy(p1, bufp);
					return p1;
				}
			}
		}
	}
	p1 = (char *)calloc(1, strlen(bufp) + 1);
	strcpy(p1, bufp);
	return p1;
}

char *constVariables(char *p)
{
	int  i;
	char *p1, *py;
	char bufp[200];
	if (!p) return 0;
	p = buyukHarf(p);
	p = myReplace(p, '-', '_');
	if (p[0] == 0) {
		p = "\"\"";
		sprintf(bufp, "%sConstants.Initemptystr", tranname);
		p1 = (char*)calloc(1, strlen(bufp) + 1);
		strcpy(p1, bufp);
		return p1;
	}
	for (i = 0; i < iconstant; i++) {
		py = constants[i].vname;
		if (strcmp(constants[i].vname, buyukHarf(indexname)) == 0)
			py = "ViewIndex";
		if (strcmp(constants[i].vtype, "init") == 0) {
			sprintf(bufp, "%sConstants.Init%s", tranname, constants[i].vval);
			p1 = (char*)calloc(1, strlen(bufp) + 1);
			strcpy(p1, bufp);
			return p1;
		}
		if (strcmp(constants[i].vval, p) == 0) {
			if (strcmp(constants[i].vtype, "view") == 0) {
				sprintf(bufp, "%sConstants.FlowView.%s", tranname, py);
			}
			else
			if (strcmp(constants[i].vtype, "flowtag") == 0)
				sprintf(bufp, "%sConstants.FlowTag.%s", tranname, py);
			else
			if (strcmp(constants[i].vtype, "func") == 0)
				sprintf(bufp, "%sConstants.FuncTag.%s", tranname, py);
			else
				sprintf(bufp, "%sConstants.%s", tranname, py);
			p1 = (char *)calloc(1, strlen(bufp) + 1);
			strcpy(p1, bufp);
			return p1;
		}
	}
	// bulamadi ama boyle olabilir
	if (strstr(p, "View")) {
		sprintf(bufp, "%sConstants.FlowView.%s", tranname, p);
	}
	else
		sprintf(bufp, "\"%s\"", p);
	p1 = (char *)calloc(1, strlen(bufp) + 1);
	strcpy(p1, bufp);
	return p1;
	// else return 0;
}

int getfuncLoc(char *s)
{
	int  i;
	for (i = 0; i < ifuncs; i++) {
		if(strcmp(funcs[i].fname, buyukHarf(s)) == 0)
			return i;
	}
	return -1;
}

void addfunc(char *pfname, char *rmodel, char *inmodel)
{
	int  i;
	if(rmodel && strlen(rmodel) > 1) rmodel = buyukHarf(rmodel);
	if (inmodel && strlen(inmodel) > 1) inmodel = buyukHarf(inmodel);
	if (pfname && strlen(pfname) > 1) pfname = buyukHarf(pfname);
	for (i = 0; i < ifuncs; i++) {
		if (funcs[i].fname && strcmp(funcs[i].fname, pfname) == 0) {
			if (funcs[i].fretmodel == NULL && rmodel) {
				funcs[i].fretmodel = (char *)calloc(1, strlen(rmodel) + 1);
				strcpy(funcs[i].fretmodel, rmodel);
			}
			if (funcs[i].finmodel == NULL && inmodel) {
				funcs[i].finmodel = (char *)calloc(1, strlen(inmodel) + 1);
				strcpy(funcs[i].finmodel, inmodel);
			}
			return;
		}
	}
	i = ifuncs;
	funcs[i].fname = (char *)calloc(1, strlen(pfname) + 1);
	strcpy(funcs[i].fname, pfname);
	if (rmodel) {
		funcs[i].fretmodel = (char *)calloc(1, strlen(rmodel) + 1);
		strcpy(funcs[i].fretmodel, rmodel);
	}
	else
		funcs[i].fretmodel = NULL;
	if (inmodel) {
		funcs[i].finmodel = (char *)calloc(1, strlen(inmodel) + 1);
		strcpy(funcs[i].finmodel, inmodel);
	}
	else
		funcs[i].finmodel = NULL;
	ifuncs++;
}

int determine(int ret, int ii)
{
	int  j;
	int  modelvar = 0;
	if (states[ii].ientry > 0) {
		for (j = 0; j < states[ii].ientry; j++) {
			if ((states[ii].entry[j].iopen > 0) ||
				(states[ii].entry[j].iexec > 0)) {
				modelvar = 1;
				break;
			}
		}
		if (modelvar == 0) {
			for (j = 0; j < states[ii].ientry; j++) {
				if (((states[ii].entry[j].isetval > 0) || (states[ii].entry[j].ishowmsg > 0) ||
					(states[ii].entry[j].iunstr > 0) || (states[ii].entry[j].itrim > 0)) &&
					((states[ii].entry[j].iexec == 0) && (states[ii].entry[j].icompcond == 0) &&
					(states[ii].entry[j].igenexp == 0) && (states[ii].entry[j].igen == 0))) {
					if (ret == 0) {
						return 0;
					}
					if (ret == 1) {
						return 1;
					}
				}
			}
		}
	}
	return -1;
}

void setfuncParams()
{
	int i, j, ii;
	int retstr, instr;
	struct NODE* np;
	for (i = 0; i < iflowcall; i++) {
		ii = vmodeliiBak(buyukHarf(flowcall[i].funcname));
		if (ii >= 0) {
			// determine string functions
			retstr = determine(0, ii); // for return value
			instr = determine(1, ii);  // for input value
			if (retstr && instr) {
				addfunc(flowcall[i].funcname, "string", "string");
			}
			else
			if (retstr && instr == 0) {
				addfunc(flowcall[i].funcname, "string", buyukHarf(vmodel[ii].sview));
			}
			else
			if (retstr == 0 && instr) {
				addfunc(flowcall[i].funcname, buyukHarf(vmodel[ii].sview), "string");
			}
			else
				addfunc(flowcall[i].funcname, buyukHarf(vmodel[ii].sview), vmodel[ii].sview);
		}
		else
			addfunc(flowcall[i].funcname, indexname, NULL);
		for (j = 0; j < flowcall[i].jcount; j++) {
			ii = vmodeliiBak(flowcall[i].fcall[j]);
			if (ii >= 0) {
				// determine string functions
				retstr = determine(0, ii); // for return value
				instr = determine(1, ii);  // for input value
				if (retstr && instr) {
					addfunc(flowcall[i].fcall[j], "string", "string");
				}
				else
				if (retstr && instr == 0) {
					addfunc(flowcall[i].fcall[j], "string", buyukHarf(vmodel[ii].sview));
				}
				else
				if (retstr == 0 && instr) {
					addfunc(flowcall[i].fcall[j], buyukHarf(flowcall[i].funcname), "string");
				}
				else
					addfunc(flowcall[i].fcall[j], buyukHarf(flowcall[i].funcname), buyukHarf(vmodel[ii].sview));
			} else 
				addfunc(flowcall[i].fcall[j], buyukHarf(flowcall[i].funcname), NULL);
		}
	}
	for (i = 0; i < ivmodel; i++) {
		addfunc(buyukHarf(vmodel[i].sid), buyukHarf(vmodel[i].sview), buyukHarf(vmodel[i].sview));
	}
	// burada node ile func bilgilerini karsilastir
	for (i = 0; i < ifuncs; i++) {
		np = nodeBak(funcs[i].fname);
		if (!np) continue;
		if (np->ninmodel) {
			if (funcs[i].finmodel) {
				if (strcmp(funcs[i].finmodel, np->ninmodel))
					funcs[i].finmodel = np->ninmodel;
			}
			else funcs[i].finmodel = "void";
			if (np->nretmodel) {
				if (funcs[i].fretmodel) {
					if (strcmp(funcs[i].fretmodel, np->nretmodel))
						funcs[i].fretmodel = np->nretmodel;
				}
				else funcs[i].fretmodel = "void";
			}
			else funcs[i].fretmodel = "void";
		}
	}
}

void globalvars(int ftype, char *trns)
{
	int  i, j, k;
	char *p1;
	fprintf(output, "        model.True = true;\n");
	p1 = initVariables(trns);
	if (ftype == CB) {
		if (p1) {
			if(strstr(p1, "Constants"))
				fprintf(output, "        model.tranId = %s;\n", p1);
			else fprintf(output, "        model.tranId = \"%s\";\n", p1);
		}
		else {
			if (strstr(initVariables(trns), "Constants"))
				fprintf(output, "        model.tranId = %s;\n", initVariables(trns));
			else fprintf(output, "        model.tranId = \"%s\";\n", initVariables(trns));
		}
	}
	else {
		if (p1) 
			fprintf(output, "        model.tranId = %s);\n", p1);
		else { 
			if (strstr(initVariables(trns), "Constants"))
				fprintf(output, "        model.tranId = %s);\n", initVariables(trns));
			else fprintf(output, "        model.tranId = \"%s\");\n", initVariables(trns));
		}
	}
	itekmi = 0;

	for (i = 0; i<istate; i++) {
		for (j = 0; j<states[i].ientry; j++) {
			for (k = 0; k<states[i].entry[j].isetval; k++)
				if (tekmi(states[i].entry[j].esetval[k].dataelm)) {
					if (strcmp(states[i].entry[j].esetval[k].dataelm, "tranId") == 0) continue;
					if (states[i].entry[j].esetval[k].defval) {
						if (ftype == CB)
							fprintf(output, "        model.%s = ", states[i].entry[j].esetval[k].dataelm);
						else fprintf(output, "        model.%s = ", states[i].entry[j].esetval[k].dataelm);
						if (states[i].entry[j].esetval[k].defval[0] != '@') {
							if (strstr(states[i].entry[j].esetval[k].defval, "/>") ||
								states[i].entry[j].esetval[k].defval[0] == 0)
								// fprintf(output, " = \"\"");
									fprintf(output, " %s)", initVariables("\"\""));
							else {
								p1 = initVariables(states[i] .entry[j].esetval[k].defval);
								if (p1)
									fprintf(output, " %s)", p1);
								else {
									char mybuf[200];
									sprintf(mybuf, "%s", initVariables(states[i].entry[j].esetval[k].defval));
									fprintf(output, " %s)", mybuf);
								}
							}
							// fprintf(output, " = \"%s\"", states[i].entry[j].esetval[k].defval);
						}
						else {

							p1 = evaluateDefValue(ftype, states[i].entry[j].esetval[k].defval);
							if(strstr(p1, "Constants"))
								fprintf(output, " %s", p1);
							else fprintf(output, " \"%s\"", p1);
						}
					}
					fprintf(output, ";\n");
				}
		}
	}
}

void clientBusiness(char *fdir, char *prog, char *trns, char *areaName)
{
	int  i, j, k, kk, appyes;
	char *requestMsg;
	fprintf(output, "// Generated by BE-CON Automatic Face Converter V:1.0\n\n");
	fprintf(output, "using System;\n");
	fprintf(output, "using System.Collections.Generic;\n");
	fprintf(output, "using System.Linq;\n");
	fprintf(output, "using System.Web.Mvc;\n");
	fprintf(output, "using AkbankFace.Common;\n");
	fprintf(output, "using AkbankFace.Common.Interfaces;\n");
	fprintf(output, "using AkbankFace.Web.Common;\n");
	fprintf(output, "using AkbankFace.Web.Common.Interfaces;\n");
	fprintf(output, "using AkbankFace.Web.%s.Common;\n", areaName);
	fprintf(output, "using AkbankFace.Web.%s.Common.Constants;\n", areaName);
	fprintf(output, "using AkbankFace.Web.%s.ClientBusiness;\n", areaName);
	fprintf(output, "using AkbankFace.Web.%s.Contracts;\n", areaName);
	fprintf(output, "using AkbankFace.Web.%s.Models;\n", areaName);
	fprintf(output, "using AkbankFace.Web.Contracts;\n");
	fprintf(output, "using AkbankFace.BranchBanking.Common;\n");
	fprintf(output, "using AkbankFace.Web.%s.ClientBusiness.Helpers;\n", areaName);
	fprintf(output, "using System.Globalization;\n");
	fprintf(output, "using Newtnsoft.Json;\n");



	// burada prog yerine mca model adlari olacak
	// fprintf(output, "using AkbankFace.Web.%s.Contracts.%s;\n", areaName, prog);
	for (i = 0; i < imca; i++) {
		if (strstr(mca[i].recname, "RequestFmt"))
			fprintf(output, "using AkbankFace.Web.%s.Contracts.%s;\n", areaName, buyukHarf(mca[i].fname));
	}
	/// Scaffolded by Akbank MVC ClientBusiness Generated Scaffolder Version 1.0

	fprintf(output, "\nnamespace AkbankFace.Web.%s.ClientBusiness\n", areaName);
	fprintf(output, "{\n");
	fprintf(output, "    public sealed class %sClientBusiness : BranchClientBusinessBase\n", trns);
	fprintf(output, "    {\n");
	indents++;

	getModelState();
	setfuncParams();
	// bunlar constatnt altinda olabilirdi
	//for (i = 0; i < ivmodel; i++) {
	//	if (vmodel[i].sview && strcmp(vmodel[i].sview, "filler") && strcmp(vmodel[i].stype, "view") == 0)
	//		fprintf(output, "        private %sViewModel %sModel;\n", vmodel[i].sview, vmodel[i].sid);
	//}
	fprintf(output, "          %sViewModel global = new %sViewModel();\n", tranname, tranname);
	appyes = false;
	requestMsg = 0;
	for (i = 0; i<istate; i++) {
		for (j = 0; j<states[i].ientry; j++)
			for (k = 0; k<states[i].entry[j].iopen; k++)
				if (states[i].entry[j].sopen[k].approval == true) {
					appyes = true;
					for (kk = 0; kk<states[i].entry[j].iexec; kk++) {
						if ((int)strlen(states[i].entry[j].eexec[kk].execid)) {
							requestMsg = states[i].entry[j].eexec[kk].execid;
							break;
						}
						else requestMsg = 0;
					}
					if (requestMsg) break;
				}
	}
	if (appyes) {
		// myapproval(trns, prog);
		if (requestMsg) approvalActions(prog, trns, areaName, requestMsg);
	}
}

char localvar[MMAX][100];
char mcaitemcode[20];
int  imatches = 0;
char matches[100][30];

void matchOldu(char *s)
{
	strcpy(matches[imatches], s);
	imatches++;
}


int strmatch(char *s, char *t)
{
	int  iss = 0;
	int  tlen = (int)strlen(t);
	int  slen = (int)strlen(s);
	int  i = 0, j = 0, ikal = 0, jkal = 0;

	for (j = jkal; j < slen; j++) {
		for (i = ikal; i < tlen; i++) {
			char a = upper(s[j]);
			char b = upper(t[i]);
			if (a == b) {
				iss++;
				jkal = j;
				ikal = i;
				break;
			}
		}
	}
	if (iss >= 3)
		return 1;
	return 0;
}

int matchVar(char *s)
{
	int  i;
	for (i = 0; i < imatches; i++) {
		if (strcmp(matches[i], s) == 0)
			return 1;
	}
	return 0;
}


//char *mymatching(int tip, char *pview, struct MCA *pmca)
//{
//	int len, len2;
//	int j;
//
//	len = (int)strlen(pview);
//	if (tip == 1) {
//		for (j = 0; j < pmca->icol; j++) {
//			if (strcasecmp(pmca->col[j].colitem, pview) == 0) {
//				if (matchVar(pmca->col[j].colitem))
//					return 0;
//				strcpy(mcaitemcode, pmca->col[j].colitem);
//				matchOldu(pmca->col[j].colitem);
//				return pmca->col[j].colitem;
//			}
//		}
//		for (j = 0; j < pmca->icol; j++) {
//			len2 = (int)strlen(pmca->col[j].colitem);
//			if (len > len2) {
//				if (strncasecmp(pmca->col[j].colitem, pview, len2) == 0) {
//					strcpy(mcaitemcode, pmca->col[j].colitem);
//					matchOldu(pmca->col[j].colitem);
//					return pmca->col[j].colitem;
//				}
//			}
//			else {
//				if (strncasecmp(pmca->col[j].colitem, pview, len) == 0) {
//					strcpy(mcaitemcode, pmca->col[j].colitem);
//					matchOldu(pmca->col[j].colitem);
//					return pmca->col[j].colitem;
//				}
//			}
//		}
//	}
//	return 0;
//}

char *matching(int tip, char *pview, struct MCA *pmca)
{
	int len, len2;
	int j;

	len = (int)strlen(pview);
	if (tip == 1) {
		for (j = 0; j < pmca->imarr; j++) {
			if (strcasecmp(pmca->marr[j].mcaitem, pview) == 0) {
				if (matchVar(pmca->marr[j].mcaitem))
					return 0;
				strcpy(mcaitemcode, pmca->marr[j].mcatype);
				matchOldu(pmca->marr[j].mcaitem);
				return pmca->marr[j].mcaitem;
			}
		}
		for (j = 0; j < pmca->imarr; j++) {
			len2 = (int)strlen(pmca->marr[j].mcaitem);
			if (len > len2) {
				if (strncasecmp(pmca->marr[j].mcaitem, pview, len2) == 0) {
					strcpy(mcaitemcode, pmca->marr[j].mcatype);
					matchOldu(pmca->marr[j].mcaitem);
					return pmca->marr[j].mcaitem;
				}
			}
			else {
				if (strncasecmp(pmca->marr[j].mcaitem, pview, len) == 0) {
					strcpy(mcaitemcode, pmca->marr[j].mcatype);
					matchOldu(pmca->marr[j].mcaitem);
					return pmca->marr[j].mcaitem;
				}
			}
		}
	}
	return 0;
}


void readView(char *viewfile)
{
	char bf[INMAX + 1];
	FILE *ff;
	int  i, j, mtype;
	char *p, *p1, mcode[3];
	char *ps, *ps1;
	ff = fopen(viewfile, "r");
	if (ff) {
		p = strstr(viewfile, ".file");
		*p = 0;
		p1 = laststr(viewfile, "\\");
		p1++;
		p1 += 4; // transaction size
		while (fgets(bf, INMAX, ff)) {
			rmnl(bf);
			mtype = bf[0] - '0';
			mcode[0] = bf[2];
			mcode[1] = 0;
			switch (mtype) {
			case 1:
				i = ivname;
				strcpy(vname[i].viewname, buyukHarf(p1));
				strcpy(vname[i].vrecname, buyukHarf(bf + 4));
				vname[i].ivitem = 0;
				vname[i].iarray = 0;
				strcpy(vname[i].vcode, mcode);
				ivname++;
				break;
			case 2:
				j = vname[i].ivitem;
				strcpy(vname[i].items[j].vitem, buyukHarf(bf + 4));

				ps = strstr(vname[i].items[j].vitem, ":");
				if (ps) *ps = 0;
				else ps = bf + 4;
				vname[i].items[j].vlen = atoi(ps + 1);
				ps1 = strstr(ps + 1, ":");
				if (ps1) ps1++;
				else ps1 = bf + 4;
				strcpy(vname[i].items[j].vtype, ps1);

				strcpy(vname[i].items[j].vitemcode, mcode);
				vname[i].ivitem++;
				break;
			case 3:
				strcpy(vname[i].arrayName, buyukHarf(bf + 4));
				strcpy(vname[i].arrcode, mcode);
				break;
			case 4:
				j = vname[i].iarray;
				strcpy(vname[i].arr[j].arritem, buyukHarf(bf + 4));

				ps = strstr(vname[i].arr[j].arritem, ":");
				if (ps) *ps = 0;
				else ps = bf + 4;
				vname[i].arr[j].arrlen = atoi(ps + 1);
				ps1 = strstr(ps + 1, ":");
				if (ps1) ps1++;
				else ps1 = bf + 4;
				strcpy(vname[i].arr[j].arrtype, ps1);

				strcpy(vname[i].arr[j].arritemcode, mcode);
				vname[i].iarray++;
				break;
			}
		}
		fclose(ff);
	}
}

void readMCA(char *mcafile)
{
	FILE *ff;
	char bf[INMAX + 1];
	int  i, j, mtype, jj;
	char *p, *p1, mcode[3];
	char *ps, *ps1;

	ff = fopen(mcafile, "r");
	if (ff) {
		p = strstr(mcafile, "ServerOp.file");
		if(p) *p = 0;
		p1 = laststr(mcafile, "\\");
		p1++;
		p1 += 4; // tranid length
		while (fgets(bf, INMAX, ff)) {
			rmnl(bf);

			mtype = bf[0] - '0';
			mcode[0] = bf[2]; mcode[1] = 0;
			switch (mtype) {
			case 1:
				i = imca;
				strcpy(mca[i].fname, buyukHarf(p1));
				strcpy(mca[i].recname, buyukHarf(bf + 4));
				mca[i].imarr = 0;
				mca[i].icols = 0;
				strcpy(mca[i].code, mcode);
				imca++;
				break;
			case 2:
				j = mca[i].imarr;
				strcpy(mca[i].marr[j].mcaitem, buyukHarf(bf + 4));
				ps = strstr(mca[i].marr[j].mcaitem, ":");
				if (ps) *ps = 0;
				else ps = bf + 4;
				mca[i].marr[j].mcalen = atoi(ps + 1);
				ps1 = strstr(ps + 1, ":");
				if (ps1) ps1++;
				else ps1 = bf + 4;
				strcpy(mca[i].marr[j].mcatype, ps1);
				strcpy(mca[i].marr[j].mcacode, mcode);
				mca[i].imarr++;
				break;
			case 3:
				jj = mca[i].icols;
				strcpy(mca[i].cols[jj].colname, buyukHarf(bf + 4));
				strcpy(mca[i].cols[jj].colcode, mcode);
				mca[i].icols++;
				break;
			case 4:
				j = mca[i].cols[jj].icol;
				strcpy(mca[i].cols[jj].col[j].colitem, buyukHarf(bf + 4));
				ps = strstr(mca[i].cols[jj].col[j].colitem, ":");
				if (ps) *ps = 0;
				else ps = bf + 4;
				mca[i].cols[jj].col[j].collen = atoi(ps + 1);
				ps1 = strstr(ps + 1, ":");
				if (ps1) ps1++;
				else ps1 = bf + 4;
				strcpy(mca[i].cols[jj].col[j].coltype, ps1);
				strcpy(mca[i].cols[jj].col[j].mcaccode, mcode);
				mca[i].cols[jj].icol++;
				break;
			}
		}
		fclose(ff);
	}
}

int icindx = 0;
char cmodel[200][50];
char cmca[200][50];

int icVar(char *vs, char *ms)
{
	int i;
	for (i = 0; i < icindx; i++) {
		if ((strcmp(cmodel[i], buyukHarf(vs)) == 0) && (strcmp(cmca[i], buyukHarf(ms)) == 0))
			return 0;
	}
	return 1;
}

int vmcaExists(char *v, char *m, int f)
{
	int i;
	for (i = 0; i < ivmca; i++) {
		if ((strcmp(vmca.view[i], buyukHarf(v)) == 0) &&
			(strcmp(vmca.mca[i], buyukHarf(m)) == 0) &&
			vmca.yon[i] == f)
			return 0;
	}
	return -1;
}

void BSAMonetaryCall(int ix, char *areaName)
{
	int i;
	int jj, kk, ii;
	char *pmodel;
	kk = ix % 10000;
	jj = kk / 1000;
	kk = kk % 1000;
	ii = ix / 10000;
	fprintf(output, "\n%s", indentstr());
	indents = 1;
	for (i = 0; i<imca; i++) {
		if (strstr(mca[i].recname, states[ii].entry[jj].eexec[kk].execop)) {
			if (strstr(mca[i].recname, "RequestFmt")) {
				pmodel = (char *)"model";
				fprintf(output, "%s", indentstr());
				fprintf(output, "public bool %sMonetaryCall(%sModel model)\n",
					buyukHarf(mca[i].fname), mca[i].fname);
				fprintf(output, "%s", indentstr());
				fprintf(output, "{\n");
				indents++;
				fprintf(output, "%s", indentstr());
				fprintf(output, "var payLoad = %sModelMapper.Instance.ModelTo%sRequestContract(model);\n",
					mca[i].fname, buyukHarf(mca[i].fname));
				fprintf(output, "%s", indentstr());
				fprintf(output, "BSABranchRequest<%sRequest> branchRequest = new BSABranchRequest<%sRequest>();\n",
					buyukHarf(mca[i].fname), buyukHarf(mca[i].fname));
				fprintf(output, "%s", indentstr());
				fprintf(output, "// burada INVESTMENT_CURRENCY_GUNLUK_KAR_ZARAR_IZLEME_BO gibi OperationCode yazilmali\n");
				fprintf(output, "%s", indentstr());
				fprintf(output, "branchRequest.Header.PopulateBSAChannelHeaders<BranchRequestHeader>(Context, OperationCode.%sMonetary, TaskCode.%sMonetary);\n",
					buyukHarf(mca[i].fname), buyukHarf(mca[i].fname));
				fprintf(output, "%s", indentstr());
				fprintf(output, "	//  branchRequest.PayLoad = new %sRequest();\n", mca[i].fname);
				fprintf(output, "%s", indentstr());
				fprintf(output, "branchRequest.PayLoad = payLoad;\n");
				fprintf(output, "%s", indentstr());
				fprintf(output, "	//Populating \n");
				fprintf(output, "%s", indentstr());
				fprintf(output, "ServiceResponse<BSABranchResponse<%sResponse>> responseMsg = branchRequest.SendToBSAGateway<%sRequest, %sResponse>(Context);\n",
					buyukHarf(mca[i].fname), buyukHarf(mca[i].fname), buyukHarf(mca[i].fname));
				fprintf(output, "%s", indentstr());
				fprintf(output, "if (responseMsg.IsRequestSuccessful == true && responseMsg.Data != null)\n");
				fprintf(output, "%s", indentstr());
				fprintf(output, "{\n");
				fprintf(output, "%s", indentstr());
				fprintf(output, "// Burada ContractToModel(response, model); olmali...\n");
				fprintf(output, "%s", indentstr());
				fprintf(output, "    %sContractTo%sModel(responseMsg, model);\n", mca[i].fname, mca[i].fname);
				fprintf(output, "%s", indentstr());
				fprintf(output, "}\n");
				fprintf(output, "%s", indentstr());
				fprintf(output, "else\n");
				fprintf(output, "%s", indentstr());
				fprintf(output, "{\n");
				fprintf(output, "%s", indentstr());
				fprintf(output, "	model.OperationResult.IsSuccessful = responseMsg.IsRequestSuccessful;\n");
				fprintf(output, "%s", indentstr());
				fprintf(output, "	model.OperationResult.Message = responseMsg.Messages[0].ToString();\n");
				fprintf(output, "%s", indentstr());
				fprintf(output, "}\n");
				fprintf(output, "%s", indentstr());
				fprintf(output, "return responseMsg.IsRequestSuccessful;\n");
				indents--;
				fprintf(output, "%s", indentstr());
				fprintf(output, "}\n");
			}
		}
	}
	fprintf(output, "%s", indentstr());
}
void BSACall(char *areaName)
{
	int i, j, jj; // , ic;
	char *pmodel = 0;
	fprintf(output, "%s", indentstr());
	// fprintf(output, "#mcaregion\n");
	indents = 1;
	for (i = 0; i<imca; i++) {
		if (strstr(mca[i].recname, "RequestFmt")) {
			if (strcmp(mca[i].fname, "getNewCreditAccounts") == 0 ||
				strcmp(mca[i].fname, "getKrediTakipHesaplari") == 0) {
				fprintf(output, "public bool %sCall(%sModel model, %sViewModel vmodel)\n",
					mca[i].fname, buyukHarf(mca[i].fname), indexname);
				pmodel = "vmodel";
			}
			else 
			{
				fprintf(output, "%s", indentstr());
				fprintf(output, "public bool %sCall(%sModel model)\n",
					mca[i].fname, buyukHarf(mca[i].fname));
			}
			fprintf(output, "%s", indentstr());
			fprintf(output, "{\n");
			indents++;
			fprintf(output, "%s", indentstr());
			fprintf(output, "var payLoad = %sModelMapper.Instance.ModelTo%sRequestContract(model);\n",
				buyukHarf(mca[i].fname), buyukHarf(mca[i].fname));
			fprintf(output, "%s", indentstr());
			fprintf(output, "BSABranchRequest<%sRequest> branchRequest = new BSABranchRequest<%sRequest>();\n",
				buyukHarf(mca[i].fname), buyukHarf(mca[i].fname));
			fprintf(output, "%s", indentstr());
			fprintf(output, "// burada INVESTMENT_CURRENCY_GUNLUK_KAR_ZARAR_IZLEME_BO gibi OperationCode yazilmali\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "branchRequest.Header.PopulateBSAChannelHeaders<BranchRequestHeader>(Context, OperationCode.%s, TaskCode.%s);\n",
				buyukHarf(mca[i].fname), buyukHarf(mca[i].fname));
			fprintf(output, "%s", indentstr());
			fprintf(output, "	//  branchRequest.PayLoad = new %sRequest();\n", mca[i].fname);
			fprintf(output, "%s", indentstr());
			fprintf(output, "branchRequest.PayLoad = payLoad;\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "	//Populating \n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "ServiceResponse<BSABranchResponse<%sResponse>> responseMsg = branchRequest.SendToBSAGateway<%sRequest, %sResponse>(Context);\n",
				buyukHarf(mca[i].fname), buyukHarf(mca[i].fname), buyukHarf(mca[i].fname));
			fprintf(output, "%s", indentstr());
			fprintf(output, "if (responseMsg.IsRequestSuccessful == true && responseMsg.Data != null)\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "{\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "// Burada ContractToModel(response, model); olmali...\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "    %sContractTo%sModel(responseMsg, model);\n", mca[i].fname, mca[i].fname);
			fprintf(output, "%s", indentstr());
			fprintf(output, "}\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "else\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "{\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "	model.OperationResult.IsSuccessful = responseMsg.IsRequestSuccessful;\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "	model.OperationResult.Message = responseMsg.Messages[0].ToString();\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "}\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "return responseMsg.IsRequestSuccessful;\n");
			indents--;
			fprintf(output, "%s", indentstr());
			fprintf(output, "}\n");
			}
		if (strstr(mca[i].recname, "ReplyFmt")) {

			fprintf(output, "%s", indentstr());
			fprintf(output, "public void %sContractTo%sModel(ServiceResponse<BSABranchResponse<%sResponse>> response, %sModel model)\n",
				mca[i].fname, mca[i].fname, buyukHarf(mca[i].fname), buyukHarf(mca[i].fname));
			fprintf(output, "%s", indentstr());
			fprintf(output, "{\n");
			indents++;
			fprintf(output, "%s", indentstr());
			fprintf(output, "model.%sResponseProp = new %sModel.%sResponse();\n",
				buyukHarf(mca[i].fname), buyukHarf(mca[i].fname), buyukHarf(mca[i].fname));
			for (jj = 0; jj < mca[i].icols; jj++) {
				if (mca[i].cols[jj].icol > 0) {
					fprintf(output, "%s", indentstr());
					fprintf(output, "model.%sResponseProp.%s = new List<%sModel.%s>();\n",
						mca[i].fname, buyukHarf(mca[i].cols[jj].colname), mca[i].fname, buyukHarf(mca[i].cols[jj].colname));
				}
			}
			if (mca[i].imarr > 0) {
				for (j = 0; j < mca[i].imarr; j++) {
					fprintf(output, "%s", indentstr());
					if (strstr(mca[i].marr[j].mcatype, "date"))
						fprintf(output, "model.%sResponseProp.%s = DateTime.ParseExact(response.Data.PayLoad.%s, \"dd.MM.yyyy\", CultureInfo.InvariantCulture);\n",
							mca[i].fname, buyukHarf(mca[i].marr[j].mcaitem), mca[i].marr[j].mcaitem);
					else fprintf(output, "model.%sResponseProp.%s = response.Data.PayLoad.%s;\n",
							mca[i].fname, buyukHarf(mca[i].marr[j].mcaitem), mca[i].marr[j].mcaitem);
				}
			}
			for (jj = 0; jj < mca[i].icols; jj++) {
				if (mca[i].cols[jj].icol > 0) {
					fprintf(output, "%s", indentstr());
					fprintf(output, "foreach(var marr in response.Data.PayLoad.%s)\n", mca[i].cols[jj].colname);
					indents++;
					fprintf(output, "%s", indentstr());
					fprintf(output, "{\n");
					indents++;
					fprintf(output, "%s", indentstr());
					fprintf(output, "model.%sResponseProp.%s.Add(new %sModel.%s()\n",
						mca[i].fname, buyukHarf(mca[i].cols[jj].colname), mca[i].fname, buyukHarf(mca[i].cols[jj].colname));
					fprintf(output, "%s", indentstr());
					fprintf(output, "{\n");
					indents++;
					for (j = 0; j < mca[i].cols[jj].icol; j++) {
						fprintf(output, "%s", indentstr());
						fprintf(output, "		%s = marr.%s,\n",
							buyukHarf(mca[i].cols[jj].col[j].colitem), mca[i].cols[jj].col[j].colitem);
						//if (strstr(mca[i].col[j].coltype, "alphanumeric"))
						//	fprintf(output, "		%s = marr.%s,\n",
						//		buyukHarf(mca[i].col[j].colitem), mca[i].col[j].colitem);
						//else 
						//if (strstr(mca[i].col[j].coltype, "date"))
						//	fprintf(output, "		%s = Datetİme.ParseExact(marr.%s, \"dd.MM.yyyy\", CultureInfo.InvariantCulture),\n",
						//		buyukHarf(mca[i].col[j].colitem), mca[i].col[j].colitem);
						//else
						//if (strcmp(mca[i].col[j].coltype, "numeric") == 0)
						//	fprintf(output, "		%s = marr.%s.ToString(),\n",
						//		buyukHarf(mca[i].col[j].colitem), mca[i].col[j].colitem);
						//else
						//	fprintf(output, "		%s = int.Parse(marr.%s ?? \"0\"),\n",
						//		buyukHarf(mca[i].col[j].colitem), mca[i].col[j].colitem);
					}
					indents--;
					fprintf(output, "%s", indentstr());
					fprintf(output, "});\n");
					indents--;
					fprintf(output, "%s", indentstr());
					fprintf(output, "}\n");
				}
			}
			indents--;
			fprintf(output, "%s", indentstr());
			fprintf(output, "}\n");
		}
	}
	fprintf(output, "%s", indentstr());
}

void MCACall(char *areaName)
{
	int i; //  jj, ic;
	fprintf(output, "\n%s", indentstr());
	// fprintf(output, "#mcaregion\n");
	indents = 1;
	for (i = 0; i<imca; i++) {
		if (strstr(mca[i].recname, "RequestFmt")) {
			fprintf(output, "%s", indentstr());
			fprintf(output, "public bool %sCall(%sModel model)\n",
				mca[i].fname, mca[i].fname);
			fprintf(output, "%s", indentstr());
			fprintf(output, "{\n");
			indents++;
			fprintf(output, "%s", indentstr());
			fprintf(output, "var MsgContract = %sModelMapper.Instance.\n",
				mca[i].fname);
			fprintf(output, "%s", indentstr());
			fprintf(output, "    ModelTo%sRequestMsgContract(model);\n",
				mca[i].fname);
			fprintf(output, "%s", indentstr());
			fprintf(output, "// Model to Contract Mapping\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "// Populating MCA Headers\n");

			fprintf(output, "%s", indentstr());
			fprintf(output, "%sRequestMsg RequestMsg =\n", mca[i].fname);
			fprintf(output, "%s", indentstr());
			fprintf(output, "     MsgContract.PopulateMCAHeaders(Context,\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "              AkbankFace.Web.%s.Contracts.OperationCode.%s,\n", areaName, mca[i].fname);
			fprintf(output, "%s", indentstr());
			fprintf(output, "              AkbankFace.Web.%s.Contracts.TaskCode.%s);\n", areaName, mca[i].fname);
			fprintf(output, "%s", indentstr());
			fprintf(output, "//Make the Request\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "ServiceResponse<%sResponseMsg> mca%sResponseMsg =\n",
				mca[i].fname, mca[i].fname);
			fprintf(output, "%s", indentstr());
			fprintf(output, "    RequestMsg.SendToMCA<%sResponseMsg>(Context);\n",
				mca[i].fname);
			fprintf(output, "%s", indentstr());
			fprintf(output, "//Contract to Model Mapping\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "var tmapper = new %sModelMapper();\n", mca[i].fname);
			fprintf(output, "%s", indentstr());
			fprintf(output, "ServiceResponse<%sRequestMsg> reqMsg = new ServiceResponse<%sRequestMsg>();\n",
				mca[i].fname, mca[i].fname);
			fprintf(output, "%s", indentstr());
			fprintf(output, "model = tmapper.ContractToModel(reqMsg, mca%sResponseMsg); \n", mca[i].fname);
			/*fprintf(output, "%s", indentstr());
			fprintf(output, "%sContractTo%sModel(mca%sResponseMsg,model);\n", mca[i].fname, mca[i].fname, mca[i].fname);*/
			fprintf(output, "%s", indentstr());
			fprintf(output, "return mca%sResponseMsg.IsRequestSuccessful;\n", mca[i].fname);
			
			indents--;
			fprintf(output, "%s", indentstr());
			fprintf(output, "}\n");
		}
	}
	fprintf(output, "%s", indentstr());
}

int  itemscnt;
char items[50][100];
int itemsakla(char* ps)
{
	int i;
	for (i = 0; i < itemscnt; i++) {
		if (strcmp(items[i], ps) == 0)
			return i;
	}
	i = itemscnt;
	itemscnt++;
	strcpy(items[i], ps);
	return 0;
}

int itemvarmi(char* ps)
{
	int i;
	for (i = 0; i < itemscnt; i++) {
		if (strcmp(items[i], ps) == 0)
			return 1;
	}
	return 0;
}

void ViewModelToMCA()
{
	int i, j, k, jj;
	char *item;
	for (i = 0; i<ivname; i++) {
		imatches = 0;
		itemscnt = 0;
		for (j = 0; j<imca; j++) {
			if (strstr(mca[j].recname, "Request") == 0) continue;
			if (strstr(vname[i].viewname, "KriterView"))
				fprintf(output, "      public %sModel %sViewModelTo%s(%sModel request, %s%sViewModel model)\n",
						buyukHarf(mca[j].fname), vname[i].viewname, mca[j].fname, buyukHarf(mca[j].fname), tranname, vname[i].viewname);
			else fprintf(output, "      public %sModel %sViewModelTo%s(%sModel request, %sViewModel model)\n",
					buyukHarf(mca[j].fname), vname[i].viewname, mca[j].fname, buyukHarf(mca[j].fname), vname[i].viewname);
			fprintf(output, "      {\n");
			imatches = 0;
			fprintf(output, "              if(request.%sRequestProp == null)\n", buyukHarf(mca[j].fname));
			fprintf(output, "                   request.%sRequestProp = new %sModel.%sRequest();\n", buyukHarf(mca[j].fname), buyukHarf(mca[j].fname), buyukHarf(mca[j].fname));
			if (strcmp(gislem, "null")) {
				fprintf(output, "             // request.%sRequestProp.%s = model.%s;\n", buyukHarf(mca[j].fname), buyukHarf(gislem), gislem);
			}
			fprintf(output, "             // request.%sRequestProp.FonkNo = %sConstants.FuncCode; // TODO tranId degistirilebilir.\n", mca[j].fname, tranname);

			for (k = 0; k<vname[i].ivitem; k++) {
				if (strcmp(vname[i].items[k].vitemcode, "L") == 0) {
					fprintf(output, "          //TODO: request.%sRequestProp.%s  icin karsiligini ekleyin\n", mca[j].fname, buyukHarf(vname[i].items[k].vitem));
					continue;
				}
				item = matching(1, vname[i].items[k].vitem, &mca[j]);
				if (item) {
					if (strcasecmp(item, vname[i].items[k].vitem))
						fprintf(output, "//");
					if (strcmp(vname[i].items[k].vitemcode, "D") == 0) {
						if (strstr(mcaitemcode, "alpha"))
							fprintf(output, "              request.%sRequestProp.%s = model.%s.ToString(\"dd.MM.yyyy\");\n", mca[j].fname, buyukHarf(item), vname[i].items[k].vitem);
						else
							if (strstr(mcaitemcode, "date"))
								fprintf(output, "              request.%sRequestProp.%s =  model.%s;\n", mca[j].fname, buyukHarf(item), vname[i].items[k].vitem);
							else
								fprintf(output, "              request.%sRequestProp.%s = DateTime.ParseExact((model.%s ?? \"0\").ToString()), \"dd.MM.yyyy\",  CultureInfo.InvariantCulture);\n", mca[j].fname, buyukHarf(item), vname[i].items[k].vitem);
					}
					else
					if (strcmp(vname[i].items[k].vitemcode, "N") == 0) {
						if (strstr(mcaitemcode, "alpha"))
							fprintf(output, "              request.%sRequestProp.%s = model.%s.ToString();\n", mca[j].fname, buyukHarf(item), vname[i].items[k].vitem);
						else
						if (strstr(mcaitemcode, "date"))
							fprintf(output, "              request.%sRequestProp.%s = DateTime.ParseExact(model.%s.ToString(), \"dd.MM.yyyy\",  CultureInfo.InvariantCulture);\n", mca[j].fname, buyukHarf(item), vname[i].items[k].vitem);
						else
							fprintf(output, "              request.%sRequestProp.%s = model.%s;\n", mca[j].fname, buyukHarf(item), vname[i].items[k].vitem);
					}
					//else
					//if (strcmp(vname[i].items[k].vitemcode, "L") == 0) {
					//	fprintf(output, "              request.%sRequestProp.%s = model.%s ?? \"0\";\n", mca[j].fname, buyukHarf(item), vname[i].items[k].vitem);
					//}
					else if (strcmp(vname[i].items[k].vitemcode, "S") == 0) {
						if (strstr(mcaitemcode, "alpha")) 
							fprintf(output, "              request.%sRequestProp.%s = model.%s;\n", mca[j].fname, buyukHarf(item), vname[i].items[k].vitem);
						else
						if (strstr(mcaitemcode, "date"))
							fprintf(output, "              request.%sRequestProp.%s = DateTime.ParseExact(model.%s, \"dd.MM.yyyy\",  CultureInfo.InvariantCulture);\n", mca[j].fname, buyukHarf(item), vname[i].items[k].vitem);
						else
							fprintf(output, "              request.%sRequestProp.%s = int.Parse(model.%s ?? \"0\");\n", mca[j].fname, buyukHarf(item), vname[i].items[k].vitem);
					}
					else {
						// other type
						if (strstr(mcaitemcode, "alpha"))
							fprintf(output, "              request.%sRequestProp.%s = model.%s.ToString();\n", mca[j].fname, buyukHarf(item), vname[i].items[k].vitem);
						else if (strstr(mcaitemcode, "numeric"))
							fprintf(output, "              request.%sRequestProp.%s = int.Parse(model.%s.ToString() ?? \"0\");\n", mca[j].fname, buyukHarf(item), vname[i].items[k].vitem);
						else 
							fprintf(output, "              request.%sRequestProp.%s = model.%s;\n", mca[j].fname, buyukHarf(item), vname[i].items[k].vitem);
					}
					mcaitemcode[0] = 0;
					itemsakla(item);
				}
			}
			for (jj = 0; jj < mca[i].icols; jj++) {
				if (mca[j].cols[jj].icol > 0 && vname[i].iarray > 0) {
					for (k = 0; k < mca[j].cols[jj].icol; k++) {
						if (k == 0) {
							fprintf(output, "          request.%sRequestProp.%s = new List<%sModel.%s>();\n",
								mca[j].fname, buyukHarf(mca[j].cols[jj].colname), mca[j].fname, buyukHarf(mca[j].cols[jj].colname));
							fprintf(output, "          if (model.%sList != null) {\n", vname[i].arrayName);
							fprintf(output, "          foreach(var md in model.%sList) {\n", vname[i].arrayName);
							fprintf(output, "          request.%sRequestProp.%s.Add(\n", mca[j].fname, buyukHarf(mca[j].cols[jj].colname));
							fprintf(output, "          		new %sModel.%s() {\n", mca[j].fname, buyukHarf(mca[j].cols[jj].colname));
						}
						if (strstr(mca[j].cols[jj].col[k].coltype, "date"))
							fprintf(output, "               %s = DateTime.ParseExact(md.%s, \"dd.MM.yyyy\", CultureInfo.InvariantCulture),\n", buyukHarf(mca[j].cols[jj].col[k].colitem), vname[i].arr[k].arritem);
						else
							if (strstr(mca[j].cols[jj].col[k].coltype, "alphanumeric") == 0)
								fprintf(output, "               %s = int.Parse(md.%s),\n", buyukHarf(mca[j].cols[jj].col[k].colitem), vname[i].arr[k].arritem);
							else fprintf(output, "               %s = md.%s,\n", buyukHarf(mca[j].cols[jj].col[k].colitem), vname[i].arr[k].arritem);
					}
					fprintf(output, "             });\n");
					fprintf(output, "          }\n");
					fprintf(output, "          }\n");
				}
			}
			// burada olmasi gereken bilgileri ekle
			fprintf(output, "          // TODO: lutfen islemkodu, fonksiyon no, islem tarihi ve\n");
			fprintf(output, "          // sube no gibi degerlerin dogru olup olmadigina bakin. Host baglantiniz calismaz\n\n");
			for (k = 0; k < mca[j].imarr; k++) {
				if (itemvarmi(mca[j].marr[k].mcaitem))
					continue;
				else {
					fprintf(output, "          request.%sRequestProp.%s = model.%s;\n", 
						mca[j].fname, buyukHarf(mca[j].marr[k].mcaitem), mca[j].marr[k].mcaitem);
				}
			}
			fprintf(output, "          return request;\n");
			fprintf(output, "      }\n");
		}
	}
}

int McaViewVarmi(char *ms, char *vs)
{
	int  i;
	for (i = 0; i < imcaview; i++) {
		if (strcmp(mcaview[i].mcaName, ms) == 0 && strcmp(mcaview[i].viewName, vs) == 0)
			return 1;
	}
	return 0;
}

struct MCA *mBak(char *mname)
{
	int  i;
	for (i = 0; i < imca; i++) {
		if (strstr(mca[i].recname, "Reply") && strcmp(mca[i].fname, mname) == 0) 
			return &mca[i];
	}
	return 0;
}

struct MCA *mrBak(char *mname)
{
	int  i;
	for (i = 0; i < imca; i++) {
		if (strstr(mca[i].recname, "Request") && strcmp(mca[i].fname, mname) == 0) 
			return &mca[i];
	}
	return 0;
}
int isValidView(char *mcaview)
{
	int i;
	for (i = 0; i < ivname; i++) {
		if (strcmp(mcaview, vname[i].viewname) == 0)
			return 1;
	}
	return 0;
}

char *vmatching(int tip, int *jj, struct VNAME *v, struct VNAME *v2, int *kk)
{
	int i, j;
	*kk = -1;
	if (tip == 1) {
		for (i = *jj; i < v->ivitem; i++) {
			if (strcmp(v->items[i].vitemcode, "S") != 0 &&
				strcmp(v->items[i].vitemcode, "L") != 0 &&
				strcmp(v->items[i].vitemcode, "D") != 0 &&
				strcmp(v->items[i].vitemcode, "N") != 0 ) continue;
			for (j = 0; j < v2->ivitem; j++) {
				if (strcmp(v->items[i].vitem, v2->items[j].vitem) == 0) {
					*kk = j;
					*jj = i+1;
					return v2->items[j].vitem;
				}
			}
		}
		if (*kk == -1)
			*jj = v->ivitem;
	}
	if (tip == 2) {
		for (i = *jj; i < v->iarray; i++) {
			for (j = 0; j < v2->iarray; j++) {
				if (strcmp(v->arr[i].arritem, v2->arr[j].arritem) == 0) {
					*kk = j;
					*jj = i+1;
					return v2->arr[j].arritem;
				}
			}
		}
	}
	return 0;
}

void ViewToViewModel()
{
	int  i, j, jj, kk, jjj;
	int  ekle = 0;
	char *item;
	char fname[200];
	int view1, view2;

	for (i = 0; i < iviewview; i++) {
		indents = 1;
		sprintf(fname, "%sViewModelTo%s", viewview[i].view1Name, viewview[i].view2Name);
		if (yazilanaekle(fname) == 1) continue;
		if (isValidView(viewview[i].view1Name) == 0) continue;
		imatches = 0;
		if (strstr(viewview[i].view1Name, "KriterView"))
			fprintf(output, "\n      public %sViewModel %s%sViewModelTo%s(%s%sViewModel model, %sViewModel vmodel)\n",
			viewview[i].view2Name, tranname, viewview[i].view1Name, viewview[i].view2Name, tranname, viewview[i].view1Name, viewview[i].view2Name);
		else
			if (strstr(viewview[i].view2Name, "KriterView"))
				fprintf(output, "\n      public %s%sViewModel %sViewModelTo%s%s(%sViewModel model, %s%sViewModel vmodel)\n",
				tranname, viewview[i].view2Name, viewview[i].view1Name, tranname, viewview[i].view2Name, viewview[i].view1Name, tranname, viewview[i].view2Name);
			else
				fprintf(output, "\n      public %sViewModel %sViewModelTo%s(%sViewModel model, %sViewModel vmodel)\n",
				viewview[i].view2Name, viewview[i].view1Name, viewview[i].view2Name, viewview[i].view1Name, viewview[i].view2Name);

		fprintf(output, "     {\n");
		view2 = -1;
		for (j = 0; j < ivname; j++) {
			if (strcmp(viewview[i].view1Name, vname[j].viewname) == 0) {
				view1 = j;
			}
			if (strcmp(viewview[i].view2Name, vname[j].viewname) == 0) {
				view2 = j;
			}
		}
	
		jjj = 0;
		if(view2 >= 0)
			for (jj = 0; jj < vname[view1].ivitem; jj++) {
				if (strcmp(vname[view1].items[jj].vitemcode, "L") == 0) {
					fprintf(output, "         //TODO: vmodel.%s icin karsiligini ekleyin\n", vname[view2].items[jj].vitem);
					continue;
				}
				item = vmatching(1, &jjj, &vname[view1], &vname[view2], &kk);
				if (item) {
						if (strcmp(vname[view2].items[kk].vitemcode, "D") == 0) {
							if (strcmp(vname[view1].items[jj].vitemcode, "S") == 0)
								fprintf(output, "          vmodel.%s = DateTime.ParseExact(model.%s, \"dd.MM.yyyy\", CultureInfo.InvariantCulture);\n", item, item);
							else
							if (strcmp(vname[view1].items[jj].vitemcode, "N") == 0)
								fprintf(output, "          vmodel.%s = DateTime.ParseExact(model.%s, \"dd.MM.yyyy\", CultureInfo.InvariantCulture);\n", item, item);
							else fprintf(output, "          vmodel.%s = model.%s;\n", item, item);
						}
						else
						if (strcmp(vname[view2].items[kk].vitemcode, "N") == 0) {
							if (strcmp(vname[view1].items[jj].vitemcode, "S") == 0)
								fprintf(output, "          vmodel.%s = int.Parse(model.%s ?? \"0\");\n", item, item);
							else
							if (strcmp(vname[view1].items[jj].vitemcode, "D") == 0)
								fprintf(output, "          vmodel.%s = model.%s.ToString(\"dd.MM.yyyy\");\n", item, item);
							else fprintf(output, "          vmodel.%s = model.%s;\n", item, item);
						}
						else {
							if (strcmp(vname[view1].items[jj].vitemcode, "S") == 0)
								fprintf(output, "          vmodel.%s = model.%s;\n", item, item);
							else
							if (strcmp(vname[view1].items[jj].vitemcode, "D") == 0)
								fprintf(output, "          vmodel.%s = model.%s.ToString(\"dd.MM.yyyy\");\n", item, item);
							else fprintf(output, "          vmodel.%s = model.%s;\n", item, item);
						}
				}
				else {
					if (strcasecmp(vname[view2].items[kk].vitemcode, "L") == 0) {
						fprintf(output, "          //TODO: vmodel.%s; icin karsiligini ekleyin\n", vname[view2].items[jj].vitem);
					}
					else {
						item = vmatching(1, &jjj, &vname[view1], &vname[view2], &kk);
						if (item) {
							if (strcasecmp(vname[view2].items[kk].vitemcode, "D") == 0) {
								if (strcasecmp(vname[view1].items[jj].vitemcode, "S") == 0)
									fprintf(output, "          vmodel.%s = DateTime.ParseExact(model.%s, \"dd.MM.yyyy\", CultureInfo.InvariantCulture);\n", item, item);
								else
									if (strcasecmp(vname[view1].items[jj].vitemcode, "D") == 0)
										fprintf(output, "          vmodel.%s = model.%s;\n", item, item);
									else fprintf(output, "          vmodel.%s = DateTime.ParseExact(model.%s.ToString(), \"dd.MM.yyyy\", CultureInfo.InvariantCulture);\n", item, item);
							}
							else
								if (strcmp(vname[view2].items[kk].vitemcode, "N") == 0) {
									if (strcasecmp(vname[view1].items[jj].vitemcode, "S") == 0)
										fprintf(output, "          vmodel.%s = int.Parse(model.%s ?? \"0\");\n", item, item);
									else
										if (strcasecmp(vname[view1].items[jj].vitemcode, "D") == 0)
											fprintf(output, "          vmodel.%s = int.Parse((model.%s ?? \"0\").ToString(\"dd.MM.yyyy\"));\n", item, item);
										else fprintf(output, "          vmodel.%s = model.%s;\n", item, item);
								}
								else {
									if (strcmp(vname[view1].items[jj].vitemcode, "S") == 0)
										fprintf(output, "          vmodel.%s = model.%s;\n", item, item);
									else
										if (strcmp(vname[view1].items[jj].vitemcode, "D") == 0)
											fprintf(output, "          vmodel.%s = model.%s.ToString(\"dd.MM.yyyy\");\n", item, item);
										else fprintf(output, "          vmodel.%s = model.%s.ToString();\n", item, item);
								}
						}
					}
					if (strcmp(vname[view2].items[jj].vitemcode, "L") == 0) {
						fprintf(output, "       // TODO: vmodel.%s icin karsiligini ekleyin\n",
							vname[view2].items[jj].vitem);
					}
					else {
						item = vmatching(1, &jjj, &vname[view1], &vname[view2], &kk);
						if (item) {
							if (strcasecmp(vname[view2].items[kk].vitemcode, (char*)"D") == 0) {
								if (strcmp(vname[view1].items[jj].vitemcode, "D") == 0) {
									fprintf(output, "    vmodel.%s = model.%s;\n", item, item);
								}
								else
									if (strcmp(vname[view1].items[jj].vitemcode, "S") == 0) {
										fprintf(output, "    vmodel.%s = DateTime.ParseExact(model.%s, \"dd.MM.yyyy\", Cultureınfo.InvariantCulture);\n", item, item);
									}
									else {
										fprintf(output, "    vmodel.%s = DateTime.ParseExact(model.%s.ToString(), \"dd.MM.yyyy\", Cultureınfo.InvariantCulture);\n", item, item);
									}
							}
							else
								if (strcasecmp(vname[view2].items[kk].vitemcode, (char*)"S") == 0) {
									if (strcmp(vname[view1].items[jj].vitemcode, "D") == 0) {
										fprintf(output, "    vmodel.%s = model.%s.ToString(\"dd.MM.yyyy\");\n", item, item);
									}
									else
										if (strcmp(vname[view1].items[jj].vitemcode, "S") == 0) {
											fprintf(output, "    vmodel.%s = model.%s;\n", item, item);
										}
										else {
											fprintf(output, "    vmodel.%s = model.%s.ToString();\n", item, item);
										}
								}
								else {
									if (strcmp(vname[view1].items[jj].vitemcode, "D") == 0) {
										fprintf(output, "    vmodel.%s = int.Parse(model.%s.ToString(\"ddMMyyyy\"));\n", item, item);
									}
									else
										if (strcmp(vname[view1].items[jj].vitemcode, "S") == 0) {
											fprintf(output, "    vmodel.%s = int.Parse(model.%s ?? \"0\");\n", item, item);
										}
										else {
											fprintf(output, "    vmodel.%s = model.%s;\n", item, item);
										}

								}
						}
						else break;
					}
				}
				if (vname[view1].iarray > 0 && vname[view2].iarray > 0) {
					for (jj = 0; jj < vname[view1].iarray; jj++) {
						if (jj >= vname[view2].iarray) break;
						if ((int)strlen(vname[view1].arr[jj].arritem) > 0) {
							if (jj == 0) {
								// fprintf(output, "        if (vmodel.%sList == null)\n", vname[j].arrayName);
								if (strstr(mcaview[i].viewName, "KriterView"))
									fprintf(output, "     vmodel.%sList = new List<%s%sViewModel.%s>(); \n", vname[view2].arrayName, tranname, vname[view1].arrayName, vname[view1].arrayName);
								else fprintf(output, "    vmodel.%sList = new List<%sViewModel.%s>(); \n", vname[view2].arrayName, vname[view1].arrayName, vname[view1].arrayName);
								if (vname[view2].arrayName[0] != 0) {
									fprintf(output, "   if (model.%s != null) {\n", vname[view2].arrayName);
									fprintf(output, "        foreach (var marr in model.%sResponseProp.%s) {\n", vname[view2].arrayName, vname[view2].arrayName);
									if (strstr(mcaview[i].viewName, "KriterView"))
										fprintf(output, "            vmodel.%sList.Add(new %s%sViewModel.%s() {\n",
										vname[view2].arrayName, tranname, vname[view2].arrayName, vname[view2].arrayName);
									else fprintf(output, "            vmodel.%sList.Add(new %sViewModel.%s() {\n",
										vname[view2].arrayName, vname[view2].arrayName, vname[view2].arrayName);
								}
							}
							if (vname[view2].arrayName[0] != 0) 
							{
								item = vmatching(2, &jjj, &vname[view1], &vname[view2], &kk);
								if (item) {
									if (strcmp(vname[view2].arr[kk].arritemcode, "S") == 0)
										fprintf(output, "              %s = marr.%s,\n", item, item);
									else
										fprintf(output, "              %s = marr.%s.ToString(),\n", item, item);
									ekle = 1;
								}
							}
						}
					}
				}
			}
		if (ekle) {
			fprintf(output, "              });\n");
			ekle = 0;
			fprintf(output, "           }\n");
			fprintf(output, "      }\n");
		}
		if (ivname) {
			fprintf(output, "          return vmodel;\n");
		}
		fprintf(output, "     }\n");
	}
}


char * stringHeader(int ia, char *r, char *f, char *sretval)
{
	char* pm;
	if (strcmp(vmodel[ia].sview, "void")) {
		if (strstr(r, "KriterView"))
			pm = tranname;
		else pm = (char*)"";
		if (strcmp(r, "void") == 0)
			fprintf(output, "public %s %s ", r, f);
		else fprintf(output, "public %s%sViewmodel %s", pm, r, f);
		sretval = (char*)"string";
	}
	if (vmodel[ia].smodel == NULL) {
		fprintf(output, "public void %s", f);
		sretval = (char*)"void";
		voidreturn = 1;
	}
	if (strcmp(vmodel[ia].sview, "void") == 0) {
		fprintf(output, "()\n");
	}
	else {
		fprintf(output, "(string strmodel)\n");
	}
	return sretval;
}

void extradatayaz(int i)
{
	int  bir = 0;
	char *p1 = mcaview[i].mcaName;
	char *p2 = mcaview[i].viewName;
	char *ps = 0, *parr = 0; 
	char *ps1arr[] = { "UrunKodu", "DovizKodu", "BirimKodu", "UrunKodu", 0 };
	char *ps2arr[] = { "IhtarnameNo", "HesapSiraNo", "BirimKodu", "UrunKodu", 0 };
	if (strcmp(p1, "getNewCreditAccounts") == 0) {
		ps = "krediHesNoComboList";
		parr = "YeniTicariKrediHesapIColl";
		bir = 1;
	}
	if (strcmp(p1, "getKrediTakipHesaplari") == 0) {
		ps = "takipHesNoComboList";
		parr = "MusteriTakipHesaplariICol";
		bir = 2;
	}
	fprintf(output, "%s", indentstr());
	fprintf(output, "if (vmodel.%s == null)\n", ps);
	fprintf(output, "%s", indentstr());
	fprintf(output, "	vmodel.%s = new List<ListTypes>();\n", ps);
	fprintf(output, "%s", indentstr());
	fprintf(output, "if (model.%sResponseProp != null)\n", buyukHarf(p1));
	fprintf(output, "%s", indentstr());
	fprintf(output, "{\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "	foreach(var marr in model.%sResponseProp.%s)\n", buyukHarf(p1), parr);
	fprintf(output, "%s", indentstr());
	fprintf(output, "	{\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "		vmodel.%s.Add(new ListTypes\n", p1);
	fprintf(output, "%s", indentstr());
	fprintf(output, "		{\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "			Text = ");
	if (bir == 1) {
		fprintf(output, "marr.%s + \" - \" + marr.%s + \" - \" + marr.%s, \n", ps1arr[0], ps1arr[1], ps1arr[2]);
		fprintf(output, "%s", indentstr());
		fprintf(output, "			Value = marr.%s\n", ps1arr[3]);
	}
	if (bir == 2) {
		fprintf(output, "marr.%s + \" - \" + marr.%s + \" - \" + marr.%s, \n", ps2arr[0], ps2arr[1], ps2arr[2]);
		fprintf(output, "%s", indentstr());
		fprintf(output, "			Value = marr.%s\n", ps2arr[3]);
	}
	fprintf(output, "%s", indentstr());
	fprintf(output, "		});\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "	}\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "}\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "else\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "{\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "	vmodel.OperationResult.IsSuccessful = false;\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "	vmodel.OperationResult.Message = model.OperationResult.Message;\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "}\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "Flow.AddVariableToFlow<%sViewModel>(new KeyValuePair<string, %sViewModel>(%sConstants.FlowView.ViewIndex, vmodel));\n", p2, p2, tranname);
	fprintf(output, "%s", indentstr());
	fprintf(output, "return vmodel;\n");
}

void MCAToViewModel()
{
	int  i, j, jj;
	int  ekle = 0;
	char *item;
	char fname[200];
	struct MCA *mcaptr, *mcarptr;
	for (i = 0; i < imcaview; i++) {
		indents = 1;
		sprintf(fname, "%sModelTo%s", mcaview[i].mcaName, mcaview[i].viewName);
		if (yazilanaekle(fname) == 1) continue;
		if (isValidView(mcaview[i].viewName) == 0) continue;
		imatches = 0;
		if (strstr(mcaview[i].viewName, "KriterView"))
			fprintf(output, "\n      public %s%sViewModel %sModelTo%s(%sModel model, %s%sViewModel vmodel)\n",
				tranname, mcaview[i].viewName, mcaview[i].mcaName, mcaview[i].viewName, mcaview[i].mcaName, tranname, mcaview[i].viewName);
		else
			fprintf(output, "\n      public %sViewModel %sModelTo%s(%sModel model, %sViewModel vmodel)\n",
				buyukHarf(mcaview[i].viewName), mcaview[i].mcaName, mcaview[i].viewName, buyukHarf(mcaview[i].mcaName), mcaview[i].viewName);

		fprintf(output, "     {\n");
		if (getextras(mcaview[i].mcaName) >= 0) {
			extradatayaz(i);
		}
		else {
			for (j = 0; j < ivname; j++) {
				//if (j == 0 && vname[j].iarray > 0) {
				//	fprintf(output, "          int i;\n");
				//}
				imatches = 0;
				if (strcmp(mcaview[i].viewName, vname[j].viewname)) continue;
				mcaptr = mBak(mcaview[i].mcaName);
				mcarptr = mrBak(mcaview[i].mcaName);
				if (mcaptr == NULL || mcarptr == NULL) continue;
				for (jj = 0; jj < vname[j].ivitem; jj++) {
					if (strcmp(vname[j].items[jj].vitemcode, "L") == 0) {
						fprintf(output, "         //TODO: vmodel.%sResponseProp.%s icin karsiligini ekleyin\n", mcaptr->fname, buyukHarf(vname[j].items[jj].vitem));
						continue;
					}
					item = matching(1, vname[j].items[jj].vitem, mcaptr);
					if (item) {
						if (strcmp(vname[j].items[jj].vitemcode, "D") == 0) {
							if (strstr(mcaitemcode, "alpha"))
								fprintf(output, "          vmodel.%s = DateTime.ParseExact(model.%sResponseProp.%s, \"dd.MM.yyyy\", CultureInfo.InvariantCulture);\n", vname[j].items[jj].vitem, mcaptr->fname, buyukHarf(item));
							else
								if (strstr(mcaitemcode, "date"))
									fprintf(output, "          vmodel.%s = DateTime.ParseExact(model.%sResponseProp.%s, \"dd.MM.yyyy\", CultureInfo.InvariantCulture);\n", vname[j].items[jj].vitem, mcaptr->fname, buyukHarf(item));
								else fprintf(output, "          vmodel.%s = DateTime.ParseExact(model.%sResponseProp.%s.ToString(), \"dd.MM.yyyy\", CultureInfo.InvariantCulture);\n", vname[j].items[jj].vitem, mcaptr->fname, buyukHarf(item));
						}
						else
							if (strcmp(vname[j].items[jj].vitemcode, "N") == 0) {
								if (strstr(mcaitemcode, "alpha"))
									fprintf(output, "          vmodel.%s = int.Parse(model.%sResponseProp.%s ?? \"0\");\n", vname[j].items[jj].vitem, mcaptr->fname, buyukHarf(item));
								else
									if (strstr(mcaitemcode, "date"))
										fprintf(output, "          vmodel.%s = model.%sResponseProp.%s.ToString(\"dd.MM.yyyy\");\n", vname[j].items[jj].vitem, mcaptr->fname, buyukHarf(item));
									else fprintf(output, "          vmodel.%s = model.%sResponseProp.%s;\n", vname[j].items[jj].vitem, mcaptr->fname, buyukHarf(item));
							}
							else
								if (strcmp(vname[j].items[jj].vitemcode, "S") == 0) {
									if (strstr(mcaitemcode, "alpha"))
										fprintf(output, "          vmodel.%s = model.%sResponseProp.%s;\n", vname[j].items[jj].vitem, mcaptr->fname, buyukHarf(item));
									else
										if (strstr(mcaitemcode, "date"))
											fprintf(output, "          vmodel.%s = model.%sResponseProp.%s.ToString(\"dd.MM.yyyy\");\n", vname[j].items[jj].vitem, mcaptr->fname, buyukHarf(item));
										else fprintf(output, "          vmodel.%s = model.%sResponseProp.%s.ToString();\n", vname[j].items[jj].vitem, mcaptr->fname, buyukHarf(item));
								}
								else {
									// othertype could be boolean
									if(strstr(mcaitemcode, "alpha")) 
										fprintf(output, "          vmodel.%s = bool.Parse(model.%sResponseProp.%s ?? \"0\");\n", vname[j].items[jj].vitem, mcaptr->fname, buyukHarf(item));
									else if (strstr(mcaitemcode, "numeric"))
											fprintf(output, "          vmodel.%s = bool.Parse(model.%sResponseProp.%s.ToString() ?? \"0\");\n", vname[j].items[jj].vitem, mcaptr->fname, buyukHarf(item));
									else fprintf(output, "          vmodel.%s = model.%sResponseProp.%s;\n", vname[j].items[jj].vitem, mcaptr->fname, buyukHarf(item));
								}
							
					}
					else {
						if (strcasecmp(vname[j].items[jj].vitemcode, "L") == 0) {
							fprintf(output, "          //TODO: vmodel.%sRequestProp.%s; icin karsiligini ekleyin\n", mcarptr->fname, buyukHarf(vname[j].items[jj].vitem));
						}
						else {
							item = matching(1, vname[j].items[jj].vitem, mcarptr);
							if (item) {
								if (strcasecmp(vname[j].items[jj].vitemcode, "D") == 0) {
									if (strstr(mcaitemcode, "alpha"))
										fprintf(output, "          vmodel.%s = DateTime.ParseExact(model.%sRequestProp.%s, \"dd.MM.yyyy\", CultureInfo.InvariantCulture);\n", vname[j].items[jj].vitem, mcarptr->fname, buyukHarf(item));
									else
										if (strstr(mcaitemcode, "date"))
											fprintf(output, "          vmodel.%s = model.%sRequestProp.%s;\n", vname[j].items[jj].vitem, mcarptr->fname, buyukHarf(item));
										else fprintf(output, "          vmodel.%s = DateTime.ParseExact(model.%sRequestProp.%s.ToString(), \"dd.MM.yyyy\", CultureInfo.InvariantCulture);\n", vname[j].items[jj].vitem, mcarptr->fname, buyukHarf(item));
								}
								else
									if (strcmp(vname[j].items[jj].vitemcode, "N") == 0) {
										if (strstr(mcaitemcode, "alpha"))
											fprintf(output, "          vmodel.%s = int.Parse(model.%sRequestProp.%s ?? \"0\");\n", vname[j].items[jj].vitem, mcarptr->fname, buyukHarf(item));
										else
											if (strstr(mcaitemcode, "date"))
												fprintf(output, "          vmodel.%s = int.Parse((model.%sRequestProp.%s ?? \"0\").ToString(\"dd.MM.yyyy\"));\n", vname[j].items[jj].vitem, mcarptr->fname, buyukHarf(item));
											else fprintf(output, "          vmodel.%s = model.%sRequestProp.%s;\n", vname[j].items[jj].vitem, mcarptr->fname, buyukHarf(item));
									}
									else if (strcmp(vname[j].items[jj].vitemcode, "A") == 0) {
										if (strstr(mcaitemcode, "alpha"))
											fprintf(output, "          vmodel.%s = model.%sRequestProp.%s;\n", vname[j].items[jj].vitem, mcarptr->fname, buyukHarf(item));
										else
											if (strstr(mcaitemcode, "date"))
												fprintf(output, "          vmodel.%s = model.%sRequestProp.%s.ToString(\"dd.MM.yyyy\");\n", vname[j].items[jj].vitem, mcarptr->fname, buyukHarf(item));
											else fprintf(output, "          vmodel.%s = model.%sRequestProp.%s.ToString();\n", vname[j].items[jj].vitem, mcarptr->fname, buyukHarf(item));
									}
									else {
										// othertype
										if (strstr(mcaitemcode, "alpha"))
											fprintf(output, "          vmodel.%s = bool.Parse(model.%sResponseProp.%s ?? \"0\");\n", vname[j].items[jj].vitem, mcarptr->fname, buyukHarf(item));
										else if (strstr(mcaitemcode, "numeric"))
											fprintf(output, "          vmodel.%s = bool.Parse(model.%sResponseProp.%s.ToString() ?? \"0\");\n", vname[j].items[jj].vitem, mcarptr->fname, buyukHarf(item));
										else fprintf(output, "          vmodel.%s = model.%sResponseProp.%s;\n", vname[j].items[jj].vitem, mcarptr->fname, buyukHarf(item));
									}
							}
						}
					}
				}
				if (vname[j].iarray > 0 && mcaptr->icols > 0) {
					int jx;
					for (jj = 0; jj < vname[j].iarray; jj++) {
						for (jx = 0; jx < mcaptr->icols; jx++) {
							if (vname[j].iarray != mcaptr->cols[jx].icol) continue;
							if ((int)strlen(mcaptr->cols[jx].col[jj].colitem) > 0) {
								if (jj == 0) {
									// fprintf(output, "        if (vmodel.%sList == null)\n", vname[j].arrayName);
									if (strstr(mcaview[i].viewName, "KriterView"))
										fprintf(output, "     vmodel.%sList = new List<%s%sViewModel.%s>(); \n", vname[j].arrayName, tranname, mcaview[i].viewName, vname[j].arrayName);
									else fprintf(output, "    vmodel.%sList = new List<%sViewModel.%s>(); \n", vname[j].arrayName, mcaview[i].viewName, vname[j].arrayName);
									if (mcaptr->fname[0] != 0) {
										fprintf(output, "   if (model.%sResponseProp.%s != null) {\n", mcaptr->fname, buyukHarf(mcaptr->cols[jx].colname));
										fprintf(output, "        foreach (var marr in model.%sResponseProp.%s) {\n", mcaptr->fname, buyukHarf(mcaptr->cols[jx].colname));
										if (strstr(mcaview[i].viewName, "KriterView"))
											fprintf(output, "            vmodel.%sList.Add(new %s%sViewModel.%s() {\n",
												vname[j].arrayName, tranname, mcaview[i].viewName, vname[j].arrayName);
										else fprintf(output, "            vmodel.%sList.Add(new %sViewModel.%s() {\n",
											vname[j].arrayName, mcaview[i].viewName, vname[j].arrayName);
									}
								}
								if (mca[i].fname[0] != 0) {
									if (strstr(mcaptr->cols[jx].col[jj].coltype, "alpha"))
										fprintf(output,
											"              %s = marr.%s,\n",
											kucukHarf(vname[j].arr[jj].arritem), buyukHarf(mcaptr->cols[jx].col[jj].colitem));
									else
										fprintf(output,
											"              %s = marr.%s.ToString(),\n",
											kucukHarf(vname[j].arr[jj].arritem), buyukHarf(mcaptr->cols[jx].col[jj].colitem));
									ekle = 1;
								}
							}
						}
					}
					if (ekle) {
						fprintf(output, "              });\n");
						ekle = 0;
						fprintf(output, "           }\n");
						fprintf(output, "      }\n");
					}
				}
				if (ivname) {
					fprintf(output, "          return vmodel;\n");
				}
			}
		}
		fprintf(output, "     }\n");
	}
}


char *viewArrName(char *p)
{
	int i;
	for (i = 0; i < ivname; i++) {
		if (vname[i].viewname && strcmp(vname[i].viewname, p) == 0) {
			if(vname[i].iarray > 0) {
				return vname[i].arrayName;
			}
		}
	}
	return 0;
}

int ekrandaArr(char *p)
{
	int i;
	for (i = 0; i < ivname; i++) {
		if (strcmp(vname[i].viewname, p) == 0) {
			if(vname[i].iarray > 0)
				return i;
			else return -1;
		}
	}
	return -1;
}
int isplits = 0;
char *splits[10];

int splitYazildi(char *p)
{
	int i;
	for (i = 0; i < isplits; i++) {
		if (strcmp(splits[i], p) == 0)
			return 1;
	}
	i = isplits;
	splits[i] = (char *)calloc(1, strlen(p) + 1);
	strcpy(splits[i], p);
	isplits++;
	return 0;

}
char* Satir(char* sview)
{
	int i;
	for (i = 0; i < ivname; i++) {
		if (strcmp(sview, vname[i].viewname) == 0)
			if (vname[i].arrayName)
				return vname[i].arrayName;
	}
	return 0;
}

void selectedYaz()
{
	int  i, ii, iivname, icount = 0;
	char *p;
	for (i = 0; i < ivmodel; i++) {
		if (strcmp(vmodel[i].stype, "view")) continue;
		iivname = ekrandaArr(vmodel[i].sview);
		if (iivname < 0) continue;
		// ii = vmodelindx(vmodel[i].sview);
		ii = i;
		if (ii >= 0 && vmodel[ii].sview && strstr(vmodel[ii].stype, "view")) {
			char* vm, * arraysatir;
			p = vname[iivname].viewname;
			if (p && splitYazildi(p) == 0) {
				fprintf(output, "%s", indentstr());
				arraysatir = Satir(vmodel[ii].sview);
				if (arraysatir == 0)
					arraysatir = "Satir";

				vm = "";
				if (strcmp(vmodel[ii].sview, "KriterView") == 0) {
					fprintf(output, "public %s%sViewModel Split%sSelected(%s%sViewModel listmodel)\n", tranname, vmodel[ii].sview, p, tranname, vmodel[ii].sview);
					vm = tranname;
				}
				else fprintf(output, "public %sViewModel Split%sSelected(%sViewModel listmodel)\n", vmodel[ii].sview, p, vmodel[ii].sview);
				fprintf(output, "%s", indentstr());
				fprintf(output, "{\n");
				indents++;
				fprintf(output, "%s", indentstr());
				if (strcmp(vmodel[ii].sview, "KriterView") == 0)
					fprintf(output, "%s%sViewModel.%s selectedItem = new %s%sViewModel.%s();\n", tranname, vmodel[ii].sview, arraysatir, tranname, vmodel[ii].sview, arraysatir);
				else fprintf(output, "%sViewModel.%s selectedItem = new %sViewModel.%s();\n", vmodel[ii].sview, arraysatir, vmodel[ii].sview, arraysatir);
				fprintf(output, "%s", indentstr());
				if(icount > 0)
					fprintf(output, "if(!string.IsNullOrWhiteSpace(listmodel.SelectedRow%d))\n", icount);
				else fprintf(output, "if(!string.IsNullOrWhiteSpace(listmodel.SelectedRow))\n");
				fprintf(output, "%s", indentstr());
				fprintf(output, "{\n");
				indents++;
				fprintf(output, "%s", indentstr());
				if (icount > 0)
					fprintf(output, "selectedItem = JsonConvert.DeserializeObject<%s%sViewModel.%s>(listmodel.SelectedRow%d);\n", vm, vmodel[ii].sview, arraysatir, icount);
				else fprintf(output, "selectedItem = JsonConvert.DeserializeObject<%s%sViewModel.%s>(listmodel.SelectedRow);\n", vm, vmodel[ii].sview, arraysatir);
				indents--;
				fprintf(output, "%s", indentstr());
				fprintf(output, "}\n");
				fprintf(output, "%s", indentstr());
				fprintf(output, "return listmodel;\n");
				indents--;
				fprintf(output, "%s", indentstr());
				fprintf(output, "}\n");
			}
		}
	}
}

void getglobal()
{
	if (globalvar == 0) {
		fprintf(output, "%s", indentstr());
		fprintf(output, "global = FillGlobals(global);\n");
		globalvar = 1;
	}
}

//void MyGetVars()
//{
//	fprintf(output, "%s", indentstr());
//	fprintf(output, "public void SetVar(string ldata, string val)\n");
//	fprintf(output, "%s", indentstr());
//	fprintf(output, "{\n");
//	indents++;
//	//for (i = 0; i < iglobals; i++) {
//	//	if (globals[i][0] != '*' && globals[i][0] != '-') {
//	//		fprintf(output, "%s", indentstr());
//	//		fprintf(output, "If(ldata == \"%s\") { ", globals[i]);
//			fprintf(output, "%s", indentstr());
//			fprintf(output, "return Flow.GetVariableFromFlow<string>(ldata);\n");
//	//	}
//	//}
//	indents--;
//	fprintf(output, "%s", indentstr());
//	fprintf(output, "}\n");
//}
//
//void MySetVars()
//{
//	fprintf(output, "%s", indentstr());
//	fprintf(output, "public string GetVar(string ldata)\n");
//	fprintf(output, "%s", indentstr());
//	fprintf(output, "{\n");
//	indents++;
//	//for (i = 0; i < iglobals; i++) {
//	//	if (globals[i][0] != '*' && globals[i][0] != '-') {
//	//		fprintf(output, "%s", indentstr());
//	//		fprintf(output, "If(ldata == \"%s\") { ", globals[i]);
//			fprintf(output, "%s", indentstr());
//			fprintf(output, "return Flow.AddVariablesToFlow(new KeyValuePair<string, string>(ldata, val);\n");
//	//	}
//	//}
//	indents--;
//	fprintf(output, "%s", indentstr());
//	fprintf(output, "}\n");
//}

void globalYaz()
{
	fprintf(output, "%s", indentstr());
	fprintf(output, "public %sViewModel FillViewModel(%sViewModel model)\n", tranname, tranname);
	fprintf(output, "%s", indentstr());
	fprintf(output, "{\n");
	indents++;
	fprintf(output, "%s", indentstr());
	fprintf(output, "if (Flow != null)\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "{\n");
	indents++;
	fprintf(output, "%s", indentstr());
	fprintf(output, "var gdetail = Flow.GetViewDetail(%sConstants.FlowView.Models);\n", tranname);
	fprintf(output, "%s", indentstr());
	fprintf(output, "model = gdetail.Model as %sViewModel;\n", tranname);
	indents--;
	fprintf(output, "%s", indentstr());
	fprintf(output, "}\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "return model; \n");
	indents--;
	fprintf(output, "%s", indentstr());
	fprintf(output, "}\n");
	globalvar = 1;

	fprintf(output, "%s", indentstr());
	fprintf(output, "public void saveViewModel(%sViewModel global)\n", tranname);
	fprintf(output, "%s", indentstr());
	fprintf(output, "{\n");
	indents++;
	fprintf(output, "%s", indentstr());
	fprintf(output, "if (Flow != null)\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "{\n");
	indents++;
	fprintf(output, "%s", indentstr());
	fprintf(output, "Flow.AddVariableToFlow<%sViewModel>(new KeyValuePair<string, %sViewModel(%sConstants.FlowView.Models, model));\n",
		tranname, tranname, tranname);
	indents--;
	fprintf(output, "%s", indentstr());
	fprintf(output, "}\n");
	//fprintf(output, "%s", indentstr());
	//fprintf(output, "return model; \n");
	indents--;
	fprintf(output, "%s", indentstr());
	fprintf(output, "}\n");
}

void printerYaz()
{
	int  i, j;
	char *px;
	for (i = 0; i < istate; i++)
		for (j = 0; j < states[i].ientry; j++)
			if (states[i].entry[j].eprintid) {
				px = modelBak(i);
				if (petition == 1)
					petitionprint(states[i].entry[j].eprintid);
				else {
					if (yazilanaekle("PrintSlip")) continue;
					fprintf(output, "%s", indentstr());
					if (px)
						fprintf(output, "public SlipPrintModel PrintSlip(%sModel model)\n", px);
					else fprintf(output, "public SlipPrintModel PrintSlip(SlipPrintModel model)\n");
					fprintf(output, "%s", indentstr());
					fprintf(output, "{\n");
					fprintf(output, "%s", indentstr());
					fprintf(output, "		//Dekonta yazdirilmasi istenen bilgiler printModelin propertylerine atanarak printModel dondurulur.\n");
					fprintf(output, "%s", indentstr());
					fprintf(output, "       var printModel = %smodelToprint(model, Context);\n", tranname);
					fprintf(output, "%s", indentstr());
					fprintf(output, "		return printModel;\n");
					fprintf(output, "%s", indentstr());
					fprintf(output, "}\n");
					MymodelToPrint(px, states[i].entry[j].eprintid);
				}
			}
}

void ifloop(struct COMPCON *cp) {
	int ilk = 1;
	char rbuf[200], lbuf[200];

	struct LOGICAL *lp;
	int  first, fused = 0;
	char *opcode, *p;
	int  kk, opint;
	is = -1;
	prevop[0][0] = NULL;
	first = 0;
	for (kk = 0; kk < cp->ilogical; kk++) {
		lp = &cp->logical[kk];
		opint = 0;
		if (strcmp(lp->opname, "EQ") == 0)
			opcode = "==";
		else
			if (strcmp(lp->opname, "LE") == 0) {
				opcode = "<=";
				opint = 1;
				}
			else
				if (strcmp(lp->opname, "GE") == 0) {
					opcode = ">=";
					opint = 1;
				}
				else
					if (strcmp(lp->opname, "GT") == 0) {
						opcode = ">";
						opint = 1;
					}
					else
						if (strcmp(lp->opname, "LT") == 0) {
							opcode = "<";
							opint = 1;
						}
						else
							if (strcmp(lp->opname, "NEQ") == 0)
								opcode = "!=";
							else
								if (strcmp(lp->opname, "AND") == 0)
									opcode = "&&";
								else
									if (strcmp(lp->opname, "OR") == 0)
										opcode = "||";
									else
										opcode = lp->opname;
		if ((strcmp(opcode, "&&") == 0) && lp->firstop == NULL) {
			is++;
			strcpy(prevop[is],opcode);
			if (fused == 0) {
				first = 1; fused = 1;
			}
			continue;
		}
		if ((strcmp(opcode, "||") == 0) && lp->firstop == NULL) {
			is++;
			strcpy(prevop[is], opcode);
			if (fused == 0) {
				first = 1; fused = 1;
			}
			continue;
		}
		if (strcmp(lp->firstop, "1") != 0) {
			if (lp->firstop[0] == '@') {
				p = mcaArrMi(lp->firstop + 1);
				if (p)
					/*sprintf(lbuf, "model.%sProp.%s", p, buyukHarf(lp->firstop + 1));*/
					sprintf(lbuf, "%s", evaluateDefValue(CB, lp->firstop));
				else
					sprintf(lbuf, "%s", evaluateDefValue(CB, lp->firstop));
			}
			else
				strcpy(lbuf, lookglobals(lp->firstop));
			if (lp->secondop != NULL) {
				if (lp->secondop[0] == '@') {
					p = mcaArrMi(lp->secondop + 1);
					if (p)
						/*sprintf(rbuf, "model.%sProp.%s", p, buyukHarf(lp->secondop + 1));*/
						sprintf(rbuf, "%s", evaluateDefValue(CB, lp->secondop));
					else
						sprintf(rbuf, "%s", lp->secondop + 1);
				}
				else
					strcpy(rbuf, lookglobals(lp->secondop));
			}
			else rbuf[0] = 0;
			if (prevop != NULL) {
				if (first) {
					fprintf(output, "%s", indentstr());
					if (opint == 0) {
						fprintf(output, "if((%s %s %s) ",
							lbuf, opcode, initVariables(rbuf));
					}
					else {
						fprintf(output, "if((int.Parse(%s) %s %s) ",
							lbuf, opcode, rbuf);
					}
					first = 0;
					continue;
				}
				else {
					// fprintf(output, "%s", indentstr());
					if (opint == 0) {
						fprintf(output, " %s (%s %s %s)) ",
							prevop[is], lbuf, opcode, initVariables(rbuf));
					}
					else {
						fprintf(output, " %s (int.Parse(%s) %s %s)) ",
							prevop[is], lbuf, opcode, rbuf);
					}
					is--;
					if (is < 0) {
						fprintf(output, " { \n");
						prevop[0][0] = NULL;
					}
				}
			}
			else {
				fprintf(output, "%s", indentstr());
				fprintf(output, "if(%s %s %s) {\n",
					lbuf, opcode, initVariables(rbuf));
			}
		}
	}
}

void conditionWrite(int i)
{
	int j, k;
	int ilk = 1;

	struct STATE *ip;
	struct ENTRY *ep;
	struct COMPCON *cp;

	ip = &states[i];
	indents=1;
	for (j = 0; j<ip->ientry; j++) {
		ep = &ip->entry[j];
		for (k = 0; k < ep->icompcond; k++) {
			// char * onTrue;
			char *p, *p1;
			cp = &ep->ecompcon[k];
			p = strstr(cp->onTrue, "changeState(");
			if (!p) {
				if (k == 0) {
					fprintf(output, "%s", indentstr());
					fprintf(output, "public bool %sFalse()\n", ip->stateid);
					fprintf(output, "%s", indentstr());
					fprintf(output, "{\n");
					indents++;
				}
				ifloop(cp);
			}
			if (p) {
				if (k == 0) {
					fprintf(output, "%s", indentstr());
					fprintf(output, "public bool %sTrue()\n", ip->stateid);
					fprintf(output, "%s", indentstr());
					fprintf(output, "{\n");
					indents++;
				}
				p = p + 12;
				p1 = p;
				while (*p && *p != ')') p++;
				if (p) *p = 0;

				ifloop(cp);
			}
			indents++;
			fprintf(output, "%s", indentstr());
			if (p)
				fprintf(output, "return true;\n");
			else
				fprintf(output, "return false;\n");
			indents--;
			fprintf(output, "%s", indentstr());
			fprintf(output, "}\n");
		}
	}
	indents--;
}

void flowDefined()
{
	int i;
	fprintf(output, "    #region Defined\n");
	for (i = 0; i<istate; i++)
		if (strstr(states[i].statetype, "condition")) {
			conditionWrite(i);
		}
	fprintf(output, "%s", indentstr());
}

struct VNAME *findTable(char *vnames)
{
	int  i;
	fprintf(output, "%s", indentstr());
	fprintf(output, "// findTable ile mca ya da modeldeki tablo aranir <=====\n");
	for (i = 0; i<ivname; i++) {
		if (strcmp(vname[i].vrecname, vnames) == 0) {
			return &vname[i];
		}
	}
	return 0;
}

void newButtons(int ix, struct OPENX *op, int iop, char *areaName, char *mname)
{
	int j, ilk = 1;
	char *p, *p1;
	if (iop) {
		for (j = 0; j < states[ix].itran; j++) {

			p = strstr(states[ix].trans[j].tranid, "NavController");
			if (p) {
				p1 = p + strlen("NavController")+1; // noktayi da aldik
				p = strstr(p1, ".");
				if(p) *p = 0;
				if (ilk) {
					fprintf(output, "%s", indentstr());
					// fprintf(output, "%s.FunctionInfo.RemoveNextButton = true;\n", mname);
					fprintf(output, "%s.FunctionInfo.FunctionButtons = new List<ActionButton>();\n", mname);
					fprintf(output, "%s", indentstr());
					fprintf(output, "%s.FunctionInfo.RemoveNextButton = true;\n", mname);
					ilk = 0;
				}
				fprintf(output, "%s", indentstr());
				// constVariables(p1));  constVariables(states[ix].stateid));
				if (constVariables(p1))
					fprintf(output, "%s.FunctionInfo.FunctionButtons.Add(%sGeneralHelper.CreateNextButton(%s, %s, %s, true));\n", 
						mname, areaName, constVariables("Next"), constVariables(p1), constVariables(p1));
				else
					fprintf(output, "%s.FunctionInfo.FunctionButtons.Add(%sGeneralHelper.CreateNextButton(\"%s\", \"%s\", \"%s\", true));\n",
						mname, areaName, "Next", p1, p1);
			}
		}
	}
}

void httpget(int ix, int jj, int k, char *vnames, int i, char *areaName)
{
//	int j;
//	// viewNameden modeli ve degiskenlerini bul
//	struct VNAME *tname;
//	fprintf(output, "%s", indentstr());
//	fprintf(output, "[HttpGet]\n");
//
//	fprintf(output, "%s", indentstr());
//	fprintf(output, "public %sModel %s(%sModel model)\n", vnames, vnames, vnames);
//	fprintf(output, "%s", indentstr());
//	fprintf(output, "{\n");
//	indents++;
//	fprintf(output, "%s", indentstr());
//	fprintf(output, "if (Flow != null)\n");
//	fprintf(output, "%s", indentstr());
//	fprintf(output, "{\n");
//	indents++;
//	fprintf(output, "%s", indentstr());
//	fprintf(output, "model = Flow.GetVariableFromFlow<%sModel>(\"model\");\n",
//		vnames);
//	tname = findTable(vnames);
//	if (tname) {
//		if (tname->iarray) {
//			fprintf(output, "%s", indentstr());
//			fprintf(output, "%s%dList = Flow.GetVariableFromFlow<List<%sModel.%s%dModel>>(\"%sList\");\n",
//				tname->arrayName, i, vnames, tname->arrayName, i, tname->arrayName);
//			fprintf(output, "%s", indentstr());
//			fprintf(output, "model.%sList = %sList;\n", tname->arrayName, tname->arrayName);
//		}
//		indents--;
//		fprintf(output, "%s", indentstr());
//		fprintf(output, "}\n");
//		fprintf(output, "%s", indentstr());
//		fprintf(output, "else {\n");
//		indents++;
//		for (j = 0; j < tname->ivitem; j++) {
//			fprintf(output, "%s", indentstr());
//			fprintf(output, "model.%s = %s;\n", tname->items[j].vitem, tname->items[j].vitem);
//		}
//		if (tname->iarray) {
//			for (j = 0; j < tname->iarray; j++) {
//				fprintf(output, "%s", indentstr());
//				fprintf(output, "model.%s.%s = %s;\n", tname->arrayName, tname->arr[j].arritem, tname->arr[j].arritem);
//			}
//		}
//	}
//	newButtons(ix, &states[ix].entry[jj].sopen[k], states[ix].entry[jj].iopen, areaName);
//	indents--;
//
//	fprintf(output, "%s", indentstr());
//	fprintf(output, "}\n");
//	fprintf(output, "%s", indentstr());
//	fprintf(output, "return model;\n");
//	indents--;
//	fprintf(output, "%s", indentstr());
//	fprintf(output, "}\n");
}

int getmcaitem(int kk, char *item)
{
	int  i, j;
	for (i = 0; i < mca[kk].icols; i++) {
		for (j = 0; j < mca[kk].cols[i].icol; j++) {
			if (strcmp(mca[kk].cols[j].col[i].colitem, item) == 0)
				return i*100 + j;
		}
	}
	return -1;
}
void httpcoll(int ix, char *vnames, int i, char *trns, char *areaName)
{
	int  j, jj, pxdone = 0;
	int  iy = vmodelBak(ix);
	char *retval, *px, *vm = vmodel[iy].sview;
	indents = 1;
	retval = "model";
	fprintf(output, "%s", indentstr());
	fprintf(output, "public %sViewModel %s(%sViewModel model)\n", tranname, vnames, tranname);
	fprintf(output, "%s", indentstr());
	fprintf(output, "{\n");
	indents++;
	fprintf(output, "%s", indentstr());
	for (j = 0; j < states[ix].ientry; j++) {
		if (states[ix].entry[0].iinitcoll > 0) {
			px = states[ix].entry[0].einitcoll[0].delm;
			if (px) {
				for (i = 0; i < imca; i++) {
					for (jj = 0; jj < mca[i].icols; jj++) {
						if (strcmp(mca[i].cols[jj].colname, px) == 0) {
							mcaArray(i);
							fprintf(output, "%s", indentstr());
							fprintf(output, "vmodel.%sProb = new vmodel.%s();\n", buyukHarf(px), buyukHarf(px));
							// saveArray(i);
							pxdone = 1;
							retval = "vmodel";
							break;
						}
					}
				}
				if (pxdone == 0) {
					for (i = 0; i < ivname; i++) {
						if (strcmp(vname[i].arrayName, px) == 0) {
							viewArray(i);
							fprintf(output, "%s", indentstr());
							fprintf(output, "vmodel.%s = new vmodel.%s();\n", px, px);
							saveArray(i);
							pxdone = 1;
							retval = "model";
							break;
						}
					}
				}
			}
		}
	}
	for (j = 0; j < states[ix].itran; j++) {
		px = states[ix].trans[j].trantarget;
		if (px) {
			int iy = baslik(px);
			if (iy >= 0) {
				
				fprintf(output, "%s", indentstr());
				if(funcs[iy].finmodel)
					fprintf(output, "%s(model);\n", px);
				else fprintf(output, "%s();\n", px);
			}
		}
	}
	fprintf(output, "%s", indentstr());
	fprintf(output, "return %s;\n", retval);
	indents--;
	fprintf(output, "%s", indentstr());
	fprintf(output, "}\n");
	globalvar = 0;
}

void httprmcoll(int ix, char* vnames, int i, char* trns, char* areaName)
{
	int  j, jj, iy = vmodelBak(ix);
	int  pxdone = 0;
	char* vm = vmodel[iy].sview;
	char* px;
	indents = 1;
	fprintf(output, "%s", indentstr());
	fprintf(output, "public %sViewModel %s(%sViewModel model)\n", tranname, vnames, tranname);
	fprintf(output, "%s", indentstr());
	fprintf(output, "{\n");
	indents++;
	if (states[ix].ientry > 0)
		for (j = 0; j < states[ix].ientry; j++)
		{
			// p2 = states[ix].entry[j].ermcontext[0].delm;
			fprintf(output, "%s", indentstr());
			px = states[ix].entry[j].ermcoll[0].delm;
			if (px) {
				for (i = 0; i < imca; i++) {
					for (jj = 0; jj < mca[i].icols; jj++) {
						if (strcmp(mca[i].cols[jj].colname, px) == 0) {
							mcaArray(i);
							fprintf(output, "%s", indentstr());
							fprintf(output, "vmodel.%s = null;\n", px);
							saveArray(i);
							pxdone = 1;
							break;
						}
					}
				}
				if (pxdone == 0) {
					for (i = 0; i < ivname; i++) {
						if (strcmp(vname[i].arrayName, px) == 0) {
							viewArray(i);
							fprintf(output, "%s", indentstr());
							fprintf(output, "vmodel.%s = null;\n", px);
							saveArray(i);
							pxdone = 1;
							break;
						}
					}
				}
			}
		}
	fprintf(output, "%s", indentstr());
	fprintf(output, "return model;\n");
	indents--;
	fprintf(output, "%s", indentstr());
	fprintf(output, "}\n");
	globalvar = 0;
}

void httpcontext(int ix, char *vnames, int i, char *trns, char *areaName)
{
	int  j, jj, iy = vmodelBak(ix);
	int  pxdone = 0;
	char *vm = vmodel[iy].sview;
	char *px;
	indents = 1;
	fprintf(output, "%s", indentstr());
	fprintf(output, "public %sViewModel %s(%sViewModel model)\n", tranname, vnames, tranname);
	fprintf(output, "%s", indentstr());
	fprintf(output, "{\n");
	indents++;
	if (states[ix].ientry > 0)
		for (j = 0; j < states[ix].ientry; j++)
		{
			// p2 = states[ix].entry[j].ermcontext[0].delm;
			fprintf(output, "%s", indentstr());
			px = states[ix].entry[j].ermcontext[0].delm;
			if (px) {
				for (i = 0; i < imca; i++) {
					for (jj = 0; jj < mca[i].icols; jj++) {
						if (strcmp(mca[i].cols[jj].colname, px) == 0) {
							mcaArray(i);
							fprintf(output, "%s", indentstr());
							fprintf(output, "vmodel.%s = null;\n", px);
							saveArray(i);
							pxdone = 1;
							break;
						}
					}
				}
				if (pxdone == 0) {
					for (i = 0; i < ivname; i++) {
						if (strcmp(vname[i].arrayName, px) == 0) {
							viewArray(i);
							fprintf(output, "%s", indentstr());
							fprintf(output, "vmodel.%s = null;\n", px);
							saveArray(i);
							pxdone = 1;
							break;
						}
					}
				}
			}
		}
	fprintf(output, "%s", indentstr());
	fprintf(output, "return model;\n");
	indents--;
	fprintf(output, "%s", indentstr());
	fprintf(output, "}\n");
	globalvar = 0;
}
int  getextras(char *s)
{
	int i;
	for (i = 0; i < iextras; i++) {
		if (strcmp(extras[i], s) == 0)
			return i;
	}
	return -1;
}

void saveGlobal()
{
	if (globalvar == 1) {
		fprintf(output, "%s", indentstr());
		fprintf(output, "saveGlobal(global);\n");
		globalvar = 0;
	}
}

void httppost(int ix, char *vnames, int i, char *trns, char *areaName)
{
	int  j, say, ilk, ilk2, misak, iyy;
	int  mi, mj, mk, mjj;
	int  jj, kk;
	char *p, *p1;
	int  iiy = -1, callvar = 0;
	int  iy = vmodelBak(ix);
	char *vm = vmodel[iy].sview;
	char *retmodel = 0;
	struct OPENX *iop;
	if (vm == NULL)
		vm = states[ix].stateid;
	if (vnames == NULL || strcmp(vnames, "string") == 0) return;

	indents = 1;
	globalvar = 0;
	fprintf(output, "%s", indentstr());
	//if (strcmp(vnames, "IadeBordrolariGoruntulemeCikisBO") == 0)
	//	printf("// bekle\n");
	//if (strcmp(vnames, "getNewCreditAccounts") == 0) {
	//	printf("// bekle2 %s\n", extras[0]);
	//}
	iyy = vmodelindx(vnames);
	if(iyy < 0) return;
	if (vmodel[iyy].stype && strcmp(vmodel[iyy].stype, "view") == 0) {
		fprintf(output, "public %sViewModel %s(%sViewModel model)\n", tranname, vnames, tranname);
	}
	else {
		char* inptr;
		fprintf(output, "public %sViewModel %s(%sModel model", tranname, vnames, buyukHarf(vnames));
		inptr = vnames;
		if (iyy >= 0 && vmodel[iyy].stype && strcmp(vmodel[iyy].stype, "operation") == 0) {
			fprintf(output, ", %sViewModel vmodel", tranname);
			inptr = vm;
		}
		else {
			iiy = getextras(vnames);
			if (iiy >= 0) {
				fprintf(output, ", %sViewModel vmodel", tranname);
				inptr = vm;
			}
		}
		fprintf(output, ")\n");
		funcs[iy].finmodel = inptr;
	}
	fprintf(output, "%s", indentstr());
	fprintf(output, "{\n");
	indents++;
	fprintf(output, "%s", indentstr());
	fprintf(output, "/* TODO: Asagiya kodlarin eklenmesi gerekebilir */\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "// burada eslesmeyen degiskenler olabilir. Silinmesinde bir sakinca yoktur\n");

	fprintf(output, "%s", indentstr());
	if (constVariables(vm)) {
		if (states[ix].itran > 0) {
			int iy, iz;
			char *px;
			for (iz = 0; iz < states[ix].itran; iz++) {
				iy = baslik(states[ix].trans[iz].trantarget);
				if (iy >= 0 && strcmp(funcs[iy].finmodel, vm)) {
					px = "Models";
					funcs[iy].finmodel = vm;
					funcs[iy].fretmodel = vm;
					//fprintf(output, "var vmodel = new %sViewModel();\n", tranname);
					//fprintf(output, "%s", indentstr());
					//if (constVariables(px)) {
					//	fprintf(output, "    vmodel = Flow.GetViewDetail(%s).Model as %sViewModel;\n",
					//		constVariables(px), tranname);
					//}
					fprintf(output, "%s", indentstr());
					fprintf(output, "%s(model);\n", states[ix].trans[iz].trantarget);
					break;
				}
				else {
					if (iy >= 0) {
						fprintf(output, "%s", indentstr());
						fprintf(output, "%s(vmodel);\n", states[ix].trans[iz].trantarget);
						px = vm;
						funcs[iy].finmodel = px;
						funcs[iy].fretmodel = px;
						break;
					}
					else {
						char *px = "Models";
						//fprintf(output, "var vmodel = new %sViewModel();\n", tranname);
						//fprintf(output, "%s", indentstr());
						//if (constVariables(px)) {
						//	fprintf(output, "    vmodel = Flow.GetViewDetail(%s).Model as %sViewModel;\n",
						//		constVariables(px), tranname);
						//}
						fprintf(output, "%s", indentstr());
						fprintf(output, "%s(model);\n", states[ix].trans[iz].trantarget);
						break;
					}
				}
			}
		}
		else {
			fprintf(output, "%s", indentstr());
			if (strcmp(vnames, "getNewCreditAccounts") == 0 || strcmp(vnames, "getKrediTakipHesaplari") == 0) {
				fprintf(output, "%sCall(model, vmodel);\n", vnames);
			}
			else
				fprintf(output, "%sCall(model);\n", vnames);
			callvar = 1;
		}
		if (states[ix].ientry > 0) {
			iop = &states[ix].entry[0].sopen[0];
			newButtons(ix, iop, states[ix].entry[0].iopen, areaName, "model");
		}
	}
	else  {
		fprintf(output, "%s", indentstr());
		fprintf(output, "%s(vmodel);\n", states[ix].trans[i].trantarget);
		if (states[ix].ientry > 0) {
			iop = &states[ix].entry[0].sopen[0];
			newButtons(ix, iop, states[ix].entry[0].iopen, areaName, "model");
		}
	}
	retmodel = 0;

	say = 1;
	ilk = 1;
	misak = -1;
	for (i = 0; i < ivname; i++) {
		// burada vname[i]viewName == state[i].entry[j].open[k].viewName olmali
		if (strcmp(vm, vname[i].viewname) == 0) {
			if (vname[i].iarray > 0 && ilk == 1) {
				fprintf(output, "%s", indentstr());
				if (strstr(vname[i].viewname, "KriterView"))
					fprintf(output, "vmodel.%sList = new List<%s%sViewModel.%s>();\n", vname[i].arrayName, tranname, vname[i].viewname, vname[i].arrayName);
				else fprintf(output, "vmodel.%sList = new List<%sViewModel.%s>();\n", vname[i].arrayName, vname[i].viewname, vname[i].arrayName);
			}
			for (j = 0; j < vname[i].ivitem; j++) {
				fprintf(output, "%s", indentstr());
				mi = mcaVarmi(1, vnames, vname[i].items[j].vitem);
				if (mi == -1) {
					continue;
				}
				// ====================== hatali
				mj = mi % 10000;
				mi = mi / 10000;
				mk = 0;
				if (mj >= 100) {
					mjj = mj / 1000;
					mk = (mj % 1000) / 100;
					mj = (mj % 1000) % 100;
				}
				misak = mi;
				if (mk == 0) {
					if (strcmp(vname[i].items[j].vitemcode, "S") == 0) {
						if (strstr(mca[i].marr[mj].mcatype, "alpha"))
							fprintf(output, "vmodel.%s = model.%sResponseProp.%s;\n",
							vname[i].items[j].vitem, vnames, buyukHarf(mca[mi].marr[mj].mcaitem));
						else
							fprintf(output, "vmodel.%s = model.%sResponseProp.%s.ToString();\n",
							vname[i].items[j].vitem, vnames, buyukHarf(mca[mi].marr[mj].mcaitem));
					}
					else
						if (strcmp(vname[i].items[j].vitemcode, "N") == 0) {
							if (strstr(mca[i].marr[mj].mcatype, "alpha"))
								fprintf(output, "vmodel.%s = int.Parse(model.%sResponseProp.%s);\n",
								vname[i].items[j].vitem, vnames, buyukHarf(mca[mi].marr[mj].mcaitem));
							else
								fprintf(output, "vmodel.%s = model.%sResponseProp.%s;\n",
								vname[i].items[j].vitem, vnames, buyukHarf(mca[mi].marr[mj].mcaitem));
						}
						else {
							if (strstr(mca[i].marr[mj].mcatype, "alpha"))
								fprintf(output, "vmodel.%s = model.%sResponseProp.%s;\n",
								vname[i].items[j].vitem, vnames, buyukHarf(mca[mi].marr[mj].mcaitem));
							else
								fprintf(output, "vmodel.%s = model.%sResponseProp.%s.ToString();\n",
								vname[i].items[j].vitem, vnames, buyukHarf(mca[mi].marr[mj].mcaitem));
						}
				}
				else {
					for (jj = 0; jj < mca[i].icols; jj++) {
						if (strcmp(vname[i].items[j].vitemcode, "S") == 0) {
							if (strstr(mca[i].cols[jj].col[mk].coltype, "alpha"))
								fprintf(output, "vmodel.%s = model.%sResponseProp.%s;\n",
									vname[i].items[j].vitem, vnames, buyukHarf(mca[mi].cols[jj].col[mk].colitem));
							else
								fprintf(output, "vmodel.%s = model.%sResponseProp.%s.ToString();\n",
									vname[i].items[j].vitem, vnames, buyukHarf(mca[mi].cols[jj].col[mk].colitem));
						}
						else
							if (strcmp(vname[i].items[j].vitemcode, "N") == 0) {
								if (strstr(mca[i].cols[jj].col[mk].coltype, "alpha"))
									fprintf(output, "vmodel.%s = int.Parse(model.%sResponseProp.%s);\n",
										vname[i].items[j].vitem, vnames, buyukHarf(mca[mi].cols[jj].col[mk].colitem));
								else
									fprintf(output, "vmodel.%s = model.%sResponseProp.%s;\n",
										vname[i].items[j].vitem, vnames, buyukHarf(mca[mi].cols[jj].col[mk].colitem));
							}
							else {
								if (strstr(mca[i].cols[jj].col[mk].coltype, "alpha"))
									fprintf(output, "vmodel.%s = model.%sResponseProp.%s;\n",
										vname[i].items[j].vitem, vnames, buyukHarf(mca[mi].cols[jj].col[mk].colitem));
								else
									fprintf(output, "vmodel.%s = model.%sResponseProp.%s.ToString();\n",
										vname[i].items[j].vitem, vnames, buyukHarf(mca[mi].cols[jj].col[mk].colitem));
							}
					}
				}
			}
			retmodel = "vmodel";
			ilk2 = 1;
			for (j = 0; j < vname[i].iarray; j++) {
				mi = mcaVarmi(10, vnames, vname[i].arr[j].arritem);
				if (mi == -1) continue;
				mj = mi % 10000;
				mi = mi / 10000;
				mk = 0;
				if (mj > 100) {
					mjj = mj / 1000;
					mk = (mj % 1000) / 100;
					mj = (mj % 1000) % 100;
					if (ilk2 == 1) {
						fprintf(output, "%s", indentstr());
						fprintf(output, "if (vmodel.%sList == null)\n", vname[i].arrayName);
						fprintf(output, "%s", indentstr());
						if (strstr(vname[i].viewname, "KriterView"))
							fprintf(output, "    vmodel.%sList = new List<%s%sViewModel.%s>(); \n",
							vname[i].arrayName, tranname, vname[i].viewname, vname[i].arrayName);
						else fprintf(output, "    vmodel.%sList = new List<%sViewModel.%s>(); \n",
							vname[i].arrayName, vname[i].viewname, vname[i].arrayName);
						fprintf(output, "%s", indentstr());
						fprintf(output, "foreach(var marr in model.%sResponseProp.%s) {\n", vnames, buyukHarf(mca[mi].cols[mjj].colname));
						indents++;
						fprintf(output, "%s", indentstr());
						if (strstr(vname[i].viewname, "KriterView"))
							fprintf(output, "vmodel.%sList.Add(new %s%sViewModel.%s() {\n",
							vname[i].arrayName, tranname, vname[i].viewname, vname[i].arrayName);
						else fprintf(output, "vmodel.%sList.Add(new %sViewModel.%s() {\n",
							vname[i].arrayName, vname[i].viewname, vname[i].arrayName);
						ilk2 = 0;
					}
					fprintf(output, "%s", indentstr());
					fprintf(output, "%s = ", kucukHarf(vname[i].arr[j].arritem));
					kk = mk;
					if (strcmp(mca[mi].cols[mjj].col[kk].mcaccode, "R") == 0) {
						if (strstr(mca[mi].cols[mjj].col[kk].coltype, "alpha"))
							fprintf(output, "marr.%s,\n", buyukHarf(mca[mi].cols[mjj].col[kk].colitem));
						else fprintf(output, "marr.%s.ToString(),\n", buyukHarf(mca[mi].cols[mjj].col[kk].colitem));
						kk++;
						continue;
					}
					if (strcmp(mca[mi].cols[mjj].col[kk].mcaccode, "I") == 0) {
						if (strstr(mca[mi].cols[mjj].col[kk].coltype, "alpha"))
							fprintf(output, "marr.%s,\n", buyukHarf(mca[mi].cols[mjj].col[kk].colitem));
						else fprintf(output, "marr.%s.ToString(),\n", buyukHarf(mca[mi].cols[mjj].col[kk].colitem));
						kk++;
						continue;
					}
					retmodel = "vmodel";
				}
			}
			if (ilk2 == 0) {
				fprintf(output, "%s", indentstr());
				fprintf(output, "});\n");
				if (vname[i].iarray > 0) {
					indents--;
					fprintf(output, "%s", indentstr());
					fprintf(output, " }\n");
				}
			}
			for (jj = 0; jj < states[ix].ientry; jj++)
				for (kk = 0; kk < states[ix].entry[jj].iopen; kk++)
					// button varsa NavController isi yapilacak
					if (states[ix].entry[jj].sopen[kk].ibuttons) {
						for (j = 0; j < states[ix].itran; j++) {
							p = strstr(states[ix].trans[j].tranid, "NavController");
							if (p) {
								p1 = p + 14; // noktayi da aldik
								p = strstr(p1, ".");
								if (p) *p = 0;
								fprintf(output, "%s", indentstr());
								fprintf(output, "button%d = my%s.ToString();\n", say, p1);
							}
							say++;
						}
						for (j = 0; j < states[ix].entry[jj].sopen[kk].ibuttons; j++) {
							fprintf(output, "%s", indentstr());
							fprintf(output, "if (button%d == Something) {\n", j + 1);
							indents++;
							fprintf(output, "%s", indentstr());
							fprintf(output, "  // Something .ts deki OnButtonCommand degeridir\n");
							fprintf(output, "%s", indentstr());
							fprintf(output, "%sModel mca%s = %sModelToMCA%s(model);\n", vname[i].vrecname, vname[i].vrecname, vname[i].vrecname, vnames);
							fprintf(output, "%s", indentstr());
							fprintf(output, "if (%sTo%sCall(mca%s) == false)\n", vname[i].vrecname, vname[i].vrecname, vnames);
							fprintf(output, "%s", indentstr());
							fprintf(output, "{\n");
							indents++;
							if (globalvar) {
								fprintf(output, "    ");
								saveGlobal();
							}
							fprintf(output, "%s", indentstr());
							if(voidreturn) {
								fprintf(output, "return;\n");
							}
							else fprintf(output, "return null;\n");
							indents--;
							fprintf(output, "%s", indentstr());
							fprintf(output, "}\n");
							// model columns exits then
							fprintf(output, "%s", indentstr());
							fprintf(output, "model%d.%sList = %sList;\n", j+1, "modelcol", "modelcol");
							// if buttons exits and this is the button area then
							/*yazsaveViews(vname[i].vrecname, (char *)"model");*/
							//fprintf(output, "%s", indentstr());
							//fprintf(output, "StartFlow<%sFlow>(model, \"%s\", \"%s\");\n", trns, trns, vname[i].vrecname);
							// fprintf(output, "%s", indentstr());
							// fprintf(output, "Flow.AddVariableToFlow(new KeyValuePair<string, %sModel>(\"model\", model));\n", vname[i].vrecname);
							fprintf(output, "%s", indentstr());
							fprintf(output, "Flow.AddVariableToFlow(new KeyValuePair<string, List<%sModel.%sModel>>(%sList, %sList));\n",
								vname[i].vrecname, vname[i].arrayName,
								constVariables(vname[i].arrayName), vname[i].arrayName);
							retmodel = "vmodel";
							indents--;
							fprintf(output, "%s", indentstr());
							fprintf(output, " }\n");
						}
					}
		}
	}
	fprintf(output, "\n");
	if (iiy >= 0 || callvar == 1) {
		// extralar icinde
		fprintf(output, "%s", indentstr());
		fprintf(output, "%sModelTo%s(model, vmodel);\n", vnames, vm);
		AddMCAtoView(vnames, vm);
	}
	indents = 2;
	//yazsaveViews(vm, (char*)"vmodel");
	saveGlobal();
	fprintf(output, "%s", indentstr());
	if(voidreturn) {
		fprintf(output, "return;\n");
	}
	else {
		if(retmodel)
			fprintf(output, "return %s;\n", retmodel);
		else fprintf(output, "return;\n");
	}

	indents--;
	fprintf(output, "%s", indentstr());
	fprintf(output, "}\n");
	indents--;
	globalvar = 0;
}

char *listeModel(char *p, char *vmodel)
{
	int  i, j;
	char name[200];
	for (i = 0; i < ivname; i++) {
		if (vname[i].ivitem > 0)
			for (j = 0; j < vname[i].ivitem; j++) {
				if (strcmp(vname[i].items[j].vitemcode, "L") == 0) {
					strcpy(name, vname[i].items[j].vitem);
					strcat(name, "List");
					if (strcmp(name, p) == 0) {
						if (strcmp(vmodel, vname[i].viewname) == 0)
							return "model";
						else return vname[i].viewname;
					}
				}
			}
	}
	return 0;
}

//void yazgetViews(char* px, char* vtype)
//{
//	if (px && !strstr(px, "vcontroller")) {
//		fprintf(output, "%s", indentstr());
//		if (strcmp(vtype, "model") == 0)
//			fprintf(output, "    %s = Get%s();\n", vtype, px);
//		else fprintf(output, "    var %s = Get%s();\n", vtype, px);
//	}
//}

//void yazsaveViews(char* px, char* ptype)
//{
//	if (px && !strstr(px, "Vcontroller")) {
//		fprintf(output, "%s", indentstr());
//		fprintf(output, "    Save%s(%s);\n", px, ptype);
//	}
//}

void myButtons(int ix, struct VMODEL *op, int iy, char *areaName, char *mname)
{
	int j, ilk = 1;
	if (iy >= 0) {
		for (j = 0; op->stranid[j] != NULL; j++) {
			if (ilk) {
				fprintf(output, "%s", indentstr());
				// fprintf(output, "%s.FunctionInfo.RemoveNextButton = true;\n", mname);
				fprintf(output, "%s.FunctionInfo.FunctionButtons = new List<ActionButton>();\n", mname);
				ilk = 0;
			}
			fprintf(output, "%s", indentstr());
			if (constVariables(op->stranid[j]))
				fprintf(output, "%s.FunctionInfo.FunctionButtons.Add(%sGeneralHelper.CreateNextButton(%s, %s, %s, true));\n",
					mname, areaName, constVariables("Next"), constVariables(op->stranid[j]), constVariables(op->stranid[j]));
			else
				fprintf(output, "%s.FunctionInfo.FunctionButtons.Add(%sGeneralHelper.CreateNextButton(\"%s\", \"%s\", \"%s\", true));\n",
					mname, areaName, "Next", op->stranid[j], op->stranid[j]);
		}
	}
}

int isagdaki = 0;
char sagdaki[100][100];

int ilksoldami(char *ps)
{
	int i;
	for (i = 0; i < isagdaki; i++) {
		if (strcmp(sagdaki[i], ps) == 0)
			return 0;
	}
	return 1;
}

int sagaEkle(char* ps)
{
	int i = isagdaki;
	isagdaki++;
	strcpy(sagdaki[i], ps);
	return 1;
}
void writeInit(char* fmodel, int ix, struct ENTRY* pentry, int ipentry, char* trns, char* areaName)
{
	int  i, j, k, ii, iy, okkey;
	struct OPENX* iop;
	okkey = 0;
	indents = 1;
	fmodel = buyukHarf(fmodel);
	fprintf(output, "%s", indentstr());
	fprintf(output, "     public %sViewModel Index()\n", tranname);
	fprintf(output, "%s", indentstr());
	fprintf(output, "     {\n");

	indents = 3;
	fprintf(output, "%s", indentstr());
	fprintf(output, "var model = new %sViewModel();\n", tranname);
	fprintf(output, "%s", indentstr());
	fprintf(output, "var taskId = Context.Session.CurrentTab.SSOParametersGetValue(\"taskID\");\n");

	fprintf(output, "%s", indentstr());
	if(constVal("AkbankPanel"))
		fprintf(output, "model.FunctionInfo.Name = %sConstants.%s;\n", trns, constVal("AkbankPanel"));
	else fprintf(output, "model.FunctionInfo.Name = %sConstants.AkbankPanel;\n", trns);
	fprintf(output, "%s", indentstr());
	fprintf(output, "// burada button tanimi varsa ekle\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "// TODO: Listeleri ilgili model elemanina tasimak gerekir\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "// initialize model and global elements\n");
	itekmi = 0;
	globalvars(CB, trns);

	fprintf(output, "%s", indentstr());
	fprintf(output, "/* TODO: ------------------------------- some Context data -------------------------*/\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "// kullanici kodu icin --> Context.Session.User.Id;\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "// islem sube no icin --> Context.Session.User.OperationBranch.Code;\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "// islem Sube adi icin Context.Session.User.OperationBranch.Name\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "// Sube no icin --> Context.Session.User.Branch.Code;\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "// Sube adi icin Context.Session.User.Branch.Name\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "// model.terminalId\", Context.Session.User.ClientInfo.TerminalID); \n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "// kullanici ilk adi icin --> Context.Session.User.FirstName;\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "// kullanici soyadi icin Context.Session.User.SurName; \n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "// musterili oturum icin Context.Session.HasCustomerSession; \n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "// model.HostTermId =  \"\") atamasi yapilmali. BSA icin gerekli... \n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "/* ********** Buradaki veriler kosullara gore elle duzenlenebilir *********/ \n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "// TODO: benzeri global degiskenlere bilgi atanmalidir\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "// model.islemTarihi =  Context.Session.User.SistemTarihi.ToString(\"dd.MM.yyyy\"));\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "// model.islemTarihi =  DateTime.Now.ToString(\"dd-MM-yyyy\"));\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "// model.islemSube =  Context.Session.User.OperationBranch.Code);\n");
	/* ********************************************************************* */
	globalvar = 1;
	indents--;
	for (i = 0; i < istate; i++) {
		for (j = 0; j < states[i].ientry; j++) {
			for (k = 0; k < states[i].entry[j].isetval; k++)
				if (tekmi(states[i].entry[j].esetval[k].dataelm)) {
					if (states[i].entry[j].esetval[k].defval) {
						if (states[i].entry[j].esetval[k].defval[0] == '@') {
							char* pxx;
							pxx = evaluateDefValue(CB, states[i].entry[j].esetval[k].defval);
							if (ilksoldami(pxx)) {
								fprintf(output, "%s", indentstr());
								fprintf(output, "model.%s = XXX; // buraya asil degeri yazilmali\n", pxx);
							}
							fprintf(output, "%s", indentstr());
							if (viewVarMi(states[i].entry[j].esetval[k].dataelm))
								fprintf(output, "model.%s = %s;\n", states[i].entry[j].esetval[k].dataelm, evaluateDefValue(CB, states[i].entry[j].esetval[k].defval));
							else {
								fprintf(output, "%s = %s;\n", lookglobals(states[i].entry[j].esetval[k].dataelm), evaluateDefValue(CB, states[i].entry[j].esetval[k].defval));
							}
						}
					}
				}
		}
	}
	fprintf(output, "%s", indentstr());
	fprintf(output, "if (Flow == null)\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "{\n");
	indents++;
	fprintf(output, "%s", indentstr());
	fprintf(output, "StartFlow<%sFlow>(model);\n", trns);

	fprintf(output, "%s", indentstr());
	fprintf(output, "SetModels();\n");

	fprintf(output, "%s", indentstr());
	fprintf(output, "GetLists(global);\n");

	if (extraParam("customer")) {
		fprintf(output, "%s", indentstr());
		fprintf(output, "if (Context.Session.HasCustomerSession == true)\n");
		fprintf(output, "%s", indentstr());
		fprintf(output, "{\n");
		fprintf(output, "%s", indentstr());
		fprintf(output, "	// model.customerAvailable = ; gibi bir degisken kullanilmis olabilir\n");
		fprintf(output, "%s", indentstr());
		fprintf(output, "	model.islemSubeKodu =  Context.Session.CurrentCustomer.BranchCode;\n");
		fprintf(output, "%s", indentstr());
		fprintf(output, "	model.customerNo = Context.Session.CurrentCustomer.ID;\n");

		if (extraParam("getNewCreditAccounts")) {
			fprintf(output, "%s", indentstr());
			fprintf(output, "GetNewCreditAccountsModel gmodel = new GetNewCreditAccountsModel();\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "if (gmodel.GetNewCreditAccountsRequestProp == null)\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "    gmodel.GetNewCreditAccountsRequestProp = new GetNewCreditAccountsModel.GetNewCreditAccountsRequest();\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "gmodel.GetNewCreditAccountsRequestProp.CustomerId = int.Parse(model.customerNo);\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "gmodel.GetNewCreditAccountsRequestProp.IslemSubeKodu = model.islemSubeKodu;\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "model = getNewCreditAccounts(gmodel, model);\n");
		}
		if (extraParam("getKrediTakipHesaplari")) {
			fprintf(output, "%s", indentstr());
			fprintf(output, "GetKrediTakipHesaplariModel tmodel = new GetKrediTakipHesaplariModel();\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "if (tmodel.GetKrediTakipHesaplariRequestProp == null)\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "    tmodel.GetKrediTakipHesaplariRequestProp = new GetKrediTakipHesaplariModel.GetKrediTakipHesaplariRequest();\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "tmodel.GetKrediTakipHesaplariRequestProp.CustomerId = int.Parse(model.customerNo);\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "tmodel.GetKrediTakipHesaplariRequestProp.IslemSubeKodu = model.islemSubeKodu;\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "model = getKrediTakipHesaplari(tmodel, model);\n");
		}
		fprintf(output, "%s", indentstr());
		fprintf(output, "model.mevHesNoComboList = model.mevHesNoComboList;\n");
		indents--;
		fprintf(output, "%s", indentstr());
		fprintf(output, "}\n");
		fprintf(output, "%s", indentstr());
		fprintf(output, "else\n");
		fprintf(output, "%s", indentstr());
		fprintf(output, "{\n");
		indents++;
		fprintf(output, "%s", indentstr());
		fprintf(output, "	model.OperationResult.IsSuccessful = false;\n");
		fprintf(output, "%s", indentstr());
		fprintf(output, "	model.OperationResult.Message = \"Müşteri hesabı olmalı\";\n");
		fprintf(output, "%s", indentstr());
		fprintf(output, "	return model;\n");
		indents--;
		fprintf(output, "%s", indentstr());
		fprintf(output, "}\n");
	}

	inittarget[0] = 0;
	if (states[ix].itran > 0) {
		int ik;
		if (states[ix].ientry > 0) {
			iop = &states[ix].entry[0].sopen[0];
			newButtons(ix, iop, states[ix].entry[0].iopen, areaName, "model");
		}
		for (j = 0; j < states[ix].itran; j++) {
			if (strstr(states[ix].trans[j].tranid, ".OK") ||
				strstr(states[ix].trans[j].tranid, ".ENTER") ||
				strstr(states[ix].trans[j].tranid, ".TAMAM") ||
				strstr(states[ix].trans[j].tranid, ".DEVAM") ||
				strstr(states[ix].trans[j].tranid, ".CLICK")) {
				iy = stateVarmi(states[ix].trans[j].trantarget);
				if (iy >= 0) {
					ii = vmodelBak(iy);
					fprintf(output, "%s", indentstr());
					if (vmodel[ii].sview && strcmp(vmodel[ii].sview, "void")) {
						if (controllervarmi(states[ix].trans[j].trantarget))
							fprintf(output, "%s();\n", states[ix].trans[j].trantarget);
						else fprintf(output, "%s(model);\n", states[ix].trans[j].trantarget);
					}
					else fprintf(output, "%s();\n", states[ix].trans[j].trantarget);
					strcpy(inittarget, states[ix].trans[j].trantarget);
					ik = vmodelBak(ix); //  (states[ix].trans[j].trantarget);
					mySaveStack(states[ix].trans[j].trantarget, ix, vmodelpBak(states[ix].trans[j].trantarget), progname, tranname, areaName);
				}
			}
		}
	}

	// model deki listeyi global dan al  <==================================
	for (i = 0; i < igetlistarr; i++) {
		if (strstr(getlistarr[i], "No") == 0) {
			char *p;
			char *lmodel;
			int myused = 0;
			p = strstr(getlistarr[i], "=");
			if (p) {
				p++;
				lmodel = listeModel(p, fmodel);
				if (lmodel) {
					if (strcmp(lmodel, "model") == 0 || myused == 1) {
						fprintf(output, "%s", indentstr());
						if(strstr(sifirVarmi(p), "model."))
							fprintf(output, "model.%s = %s;\n", p, sifirVarmi(p));
						else fprintf(output, "model.%s = model.%s;\n", p, sifirVarmi(p));
					}
					else {
						fprintf(output, "%s", indentstr());
						if (strstr(lmodel, "KriterView"))
							fprintf(output, "%s%sViewModel lmodel = new %s%sViewModel();\n", tranname, lmodel, tranname, lmodel);
						else fprintf(output, "%sViewModel lmodel = new %sViewModel();\n", lmodel, lmodel);
						fprintf(output, "%s", indentstr());
						fprintf(output, "if (Flow.GetViewDetail(%s).Model != null) { \n", constVariables(lmodel));
						fprintf(output, "%s", indentstr());
						if (strstr(lmodel, "KriterView"))
							fprintf(output, "lmodel = Flow.GetViewDetail(%s).Model as %s%sViewModel;\n", constVariables(lmodel), tranname, lmodel);
						else fprintf(output, "lmodel = Flow.GetViewDetail(%s).Model as %sViewModel;\n", constVariables(lmodel), lmodel);
						fprintf(output, "%s", indentstr());
						fprintf(output, "}\n");
						fprintf(output, "%s", indentstr());
						fprintf(output, "lmodel.%s = model.%s;\n", p, p);
						fprintf(output, "%s", indentstr());
						if (constVariables(lmodel)) {
							if (strstr(lmodel, "KriterView"))
								fprintf(output, "Flow.AddVariableToFlow<%s%sViewModel>(new KeyValuePair<string, %s%sViewModel>(%s, lmodel));\n",
									tranname, lmodel, tranname, lmodel, constVariables(lmodel));
							else fprintf(output, "Flow.AddVariableToFlow<%sViewModel>(new KeyValuePair<string, %sViewModel>(%s, lmodel));\n",
								lmodel, lmodel, constVariables(lmodel));
						}
						myused = 1;
					}
				}
			}
		}
	}

	fprintf(output, "%s", indentstr());
	fprintf(output, "    /* TODO:************* ELLE EKLENECEKLER **************** */\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "    // Modelde bulunan uygun degiskenlere global modelden tasima yapilir.\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "    // model.degisken1 = model.islemTarihi;\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "    // model.degisken2 =model.islemYili;\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "    // model.subeNo = model.islemSube;\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "    // model.kriterBordroYil = kriterBordroYil;\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "    /* ***************************************************** */\n");

	ii = vmodelBak(ix);

	fprintf(output, "%s", indentstr());
	fprintf(output, "    // burada button tanimi varsa ekle. Ornegin:\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "    // model.FunctionInfo.FunctionButtons = new List<ActionButton>();\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "    // model.FunctionInfo.FunctionButtons.Add(%sGeneralHelper.CreateNextButton(Next, Key, view, true));\n", areaName);
	iy = vmodelindx(fmodel);
	if (iy >= 0 && vmodel[iy].stranid != NULL)
		myButtons(ix, &vmodel[iy], iy, areaName, "model");

	indents--;
	/*yazsaveViews(fmodel, (char*)"model");*/
	indents++;
	fprintf(output, "%s", indentstr());
	fprintf(output, "return model;\n");
	indents--;
	fprintf(output, "%s", indentstr());
	fprintf(output, "    }\n\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "else \n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "{\n");
	/*yazgetViews(fmodel, (char*)"model");*/
	indents++;

	if (states[ix].itran > 0) {
		for (j = 0; j < states[ix].itran; j++) {
			char* px, * ps;
			px = strstr(states[ix].trans[j].tranid, "NavController.");
			if (px) {
				px = px + 14;
				ps = strstr(px, ".");
				if (ps)*ps = 0;
				iy = stateVarmi(states[ix].trans[j].trantarget);
				if (iy >= 0) {
					ii = vmodelBak(iy);
					fprintf(output, "%s", indentstr());
					fprintf(output, "if(model.Actiontag == %s) ", initVariables(px));
					if (vmodel[ii].sview && strcmp(vmodel[ii].sview, "void")) {
						if (controllervarmi(states[ix].trans[j].trantarget))
							fprintf(output, "model = %s();\n", states[ix].trans[j].trantarget);
						else fprintf(output, "model = %s(model);\n", states[ix].trans[j].trantarget);
					}
					else {
						fprintf(output, "%s();\n", states[ix].trans[j].trantarget);
					}
					mySaveStack(states[ix].trans[j].trantarget, ix, vmodelpBak(states[ix].trans[j].trantarget), progname, tranname, areaName);
					okkey = 1;
				}
			}
		}
		if (okkey)
			saveGlobal();
		fprintf(output, "%s", indentstr());
		fprintf(output, "return model;\n");
		indents--;
		fprintf(output, "%s", indentstr());
		fprintf(output, "}\n\n");
		indents--;
		fprintf(output, "%s", indentstr());
		fprintf(output, "}\n");
		// ===> sira ile bu islemler cagrilmali // =======
		if (states[ix].itran > 0) {
			for (j = 0; j < states[ix].itran; j++) {
				if (strstr(states[ix].trans[j].tranid, "ERROR")) continue;
				ii = vmodeliiGet(states[ix].trans[j].trantarget);
				funcWrite(vmodel[ii].sid, ii, vmodel[ii].sview, progname, tranname, areaName);
			}
		}
		return;
	}
}

void indexRegion(int ix, char *trns, char *areaName)
{
	int  j, ii;
	char *fmodel;
	fprintf(output, "%s", indentstr());
	fprintf(output, "    #region Index\n");

	if (strcmp(states[ix].statetype, "initial") == 0) {
	    ii = vmodelBak(ix);
		fmodel = vmodel[ii].sview;
		if (fmodel == 0) {
			fmodel = "ViewIndex";
		}
		strcpy(getlistmodel, fmodel);
		for (j = 0; j < states[ix].ientry; j++) {
			writeInit(fmodel, ix, &states[ix].entry[j], states[ix].ientry, trns, areaName);
		}

	}
	// initial values to be loaded

	fprintf(output, "%s", indentstr());
	fprintf(output, "    #endregion\n");
}

int  istack = 0;
char stack[100][200];

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
	}
}

int varmi(char *p)
{
	int i;
	char pstr[200];
	if (p) {
		asciTasi(pstr, p);
		for (i = 0; i<istack; i++) {
			// asciTasi(sstr, stack[i]);
			if (strcmp(stack[i], p) == 0) return 1;
		}
		if (strcmp(p, "filler")) {
			i = istack;
			strcpy(stack[i], p);
			istack++;
		}
	}
	return 0;
}

char *GetlistVarmi(char *ps)
{
	int  i;
	char *p = 0;
	for (i = 0; i < igetlistarr; i++) {
		if (strlen(getlistarr[i]) < 2) continue;
		if (strstr(getlistarr[i], ps)) {
			p = strstr(getlistarr[i], "=");
			if (p) p++;
			else p = "No";
			break;
		}
	}
	if(p)
		return p;
	else return "No";
}

int icaches = 0;
char* caches[30];

void readcaches(char* gfile)
{
	char msay[5];
	int  ii=0, i, filevar = 1;
	FILE* fx;
	char fname[300], bufx[MAXCHAR];
	while (filevar) {
		sprintf(msay, "%d", ii);
		strcpy(fname, gfile);
		strcat(fname, msay);
		strcat(fname, "global.preference");
		fx = fopen(fname, "r");
		if (fx) {
			while (fgets(bufx, MAXCHAR, fx)) {
				rmnl(bufx);
				if (bufx[0] == '*') {
					i = icaches;
					caches[i] = (char*)calloc(1, strlen(bufx) + 1);
					strcpy(caches[i], buyukHarf(bufx));
					icaches++;
				}
			}
			fclose(fx);
			ii++;
		}
		else filevar = 0;
	}
}


void GetLists(char *area, char *mname)
{
	int i;
	char* p;
	indents = 1;
	fprintf(output, "%s", indentstr());
	fprintf(output, "public void GetLists(%sViewModel model)\n", tranname);
	fprintf(output, "%s", indentstr());
	fprintf(output, "{\n");
	indents++;
	fprintf(output, "%s", indentstr());
	fprintf(output, "//TODO : Buradaki liste degiskenini ilgili model adi ve model degiskeniyle\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "// degistirmekdegistirmek gerekebilir... Ya da ViewModel altinda tanimlanmalidir.\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "// Bu nedenle once model tanimi yapilmalidir.\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "// model = FillViewModel(global);\n");

	fprintf(output, "%s", indentstr());
	fprintf(output, "#region ListItems\n");
	if (strcmp(GetlistVarmi("KampanyaliUrunList"), "No")) {
		fprintf(output, "%s", indentstr());
		fprintf(output, "model.%s = Context.CommonService.GetListItems(ListConstants.KampanyaUrunTipi);\n", GetlistVarmi("KampanyaliUrunList"));
	}
	if (strcmp(GetlistVarmi("MusteriTipiList"), "No")) {
		fprintf(output, "%s", indentstr());
		fprintf(output, "model.%s = Context.CommonService.GetListItems(ListConstants.MusteriTipiList);\n", GetlistVarmi("MusteriTipiList"));
	}
	if (strcmp(GetlistVarmi("SegmentTipiList"), "No")) {
		fprintf(output, "%s", indentstr());
		fprintf(output, "model.%s = Context.CommonService.GetListItems(ListConstants.SegmentTipiList);\n", GetlistVarmi("SegmentTipiList"));
	}
	if (strcmp(GetlistVarmi("SegmentList"), "No")) {
		fprintf(output, "%s", indentstr());
		fprintf(output, "model.%s = Context.Cache.GetCache<List<MusteriSegmentList>>(AkbankFace.BranchBanking.Common.LOBCacheConstants.MusteriSegmentList)\n", GetlistVarmi("SegmentList"));
		fprintf(output, "%s", indentstr());
		fprintf(output, "  	.Select(k => new ListTypes(){ Value = k.MBB_RDE_REFKOD.ToString(), Text = k.MBB_RDE_ACIKLM.Trim() + \"--\" + k.MBB_RDE_REFKOD.ToString() }).ToList();\n");
	}
	if (strcmp(GetlistVarmi("DovizKoduList"), "No")) {
		fprintf(output, "%s", indentstr());
		fprintf(output, "model.%s = Context.Cache.GetCache<List<FaizDovizList>>(AkbankFace.BranchBanking.Common.LOBCacheConstants.FaizDovizList)\n", GetlistVarmi("DovizKoduList"));
		fprintf(output, "%s", indentstr());
		fprintf(output, "	 .Select(k => new ListTypes(){ Value = k.GNL_DVZ_KODU_NUM.ToString(), Text = k.GNL_DVZ_ADI.Trim() + \"--\" + k.GNL_DVZ_KODU_NUM.ToString() }).ToList();\n");
	}
	if (strcmp(GetlistVarmi("BolgeList"), "No")) {
		fprintf(output, "%s", indentstr());
		fprintf(output, "model.%s = Context.Cache.GetCache<List<BolgeList>>(AkbankFace.BranchBanking.Common.LOBCacheConstants.BolgeList)\n", GetlistVarmi("BolgeList"));
		fprintf(output, "%s", indentstr());
		fprintf(output, "    .Select(k => new ListTypes(){ Value = k.GNL_BRM_KODU.ToString(), Text = k.GNL_BRM_ADI.Trim() + \"--\" + k.GNL_BRM_KODU.ToString() }).ToList();\n");
	}
	if (strcmp(GetlistVarmi("SubeList"), "No")) {
		fprintf(output, "%s", indentstr());
		fprintf(output, "model.%s = Context.Cache.GetCache<List<Sube>>(CacheConstants.Branch).Select(k => new ListTypes(){ Value = string.Format(\"{0:D4}\", k.Code), Text = string.Format(\"{0:D4}\", k.Code) + \"-\" + k.Name.Trim() }).ToList();\n", GetlistVarmi("SubeList"));
	}

	if (strcmp(GetlistVarmi("IlList"), "No")) {
		fprintf(output, "%s", indentstr());
		fprintf(output, "model.%s = Context.Cache.GetCache<List<Sehir>>(AkbankFace.Web.Common.CacheConstants.CityList).Select(g => new ListTypes{ Value = g.Code.ToString(), Text = g.Name + \"--\" + g.Code.ToString() }).ToList();\n", GetlistVarmi("IlList"));
	}
	if (strcmp(GetlistVarmi("UlkeKoduList"), "No")) {
		fprintf(output, "%s", indentstr());
		fprintf(output, "model.%s = Context.Cache.GetCache<List<UlkeKoduList>>(AkbankFace.BranchBanking.Common.LOBCacheConstants.UlkeKoduList)\n", GetlistVarmi("DovizKoduList"));
		fprintf(output, "%s", indentstr());
		fprintf(output, "	 .Select(k => new ListTypes(){  Value = g.GNL_ULK_KOD.ToString(), Text = g.GNL_ULK_ADI.Trim() + \"--\" + g.GNL_ULK_KOD.ToString() }).ToList();\n");
	}
	if (strcmp(GetlistVarmi("HesapKullanimAmaciList"), "No")) {
		fprintf(output, "%s", indentstr());
		fprintf(output, "model.%s = Context.CommonService.GetListItems(ListConstants.HesapKullanimAmaciList);\n", GetlistVarmi("HesapKullanimAmaciList"));
	}

	if (strcmp(GetlistVarmi("YokIlgilenmiyorumList"), "No")) {
		fprintf(output, "%s", indentstr());
		fprintf(output, "model.%s= Context.CommonService.GetListItems(ListConstants.YokIlgilenmiyorumList);\n", GetlistVarmi("YokIlgilenmiyorumList"));
	}
	if (strcmp(GetlistVarmi("VarYokIlgilenmiyorumList"), "No")) {
		fprintf(output, "%s", indentstr());
		fprintf(output, "model.%s = Context.CommonService.GetListItems(ListConstants.VarYokIlgilenmiyorumList);\n", GetlistVarmi("VarYokIlgilenmiyorumList"));
	}
	if (strcmp(GetlistVarmi("BakiyeKontrolList"), "No")) {
		fprintf(output, "%s", indentstr());
		fprintf(output, "model.%s = Context.CommonService.GetListItems(ListConstants.BakiyeKontrolList);\n", GetlistVarmi("BakiyeKontrolList"));
	}
	if (strcmp(GetlistVarmi("MultiSelectAllState"), "No")) {
		fprintf(output, "%s", indentstr());
		fprintf(output, "model.%s = true;\n", GetlistVarmi("MultiSelectAllState"));
	}
	if (strcmp(GetlistVarmi("FonTablosuList"), "No")) {
		fprintf(output, "%s", indentstr());
		fprintf(output, "model.%s = new List<ListTypes>();\n", GetlistVarmi("FonTablosuList"));
	}
	if (strcmp(GetlistVarmi("TaskCode"), "No")) {
		fprintf(output, "%s", indentstr());
		fprintf(output, "model.%s = TaskCode.KampanyaGirisTanimlama;\n", GetlistVarmi("TaskCode"));
	}
	if (strcmp(GetlistVarmi("GetFonList"), "No")) {
		fprintf(output, "%s", indentstr());
		fprintf(output, "model.%s = KampanyaHelper.Instance.McaCallFonTablosuList(modelFonTablosu, Context);\n", GetlistVarmi("GetFonList"));
	}
	if (strcmp(GetlistVarmi("AlanKoduList"), "No")) {
		fprintf(output, "%s", indentstr());
		fprintf(output, "model.%s = Context.Cache.GetCache<List<AlanKoduList>>(CacheConstants.AlanKoduList)\n", GetlistVarmi("DovizKoduList"));
		fprintf(output, "%s", indentstr());
		fprintf(output, "	 .Select(k => new ListTypes() { Value = k.GNL_TAK_ALAN_KODU.ToString(), Text = k.GNL_TAK_ALAN_ADI.Trim() + \"--\" + k.GNL_TAK_ALAN_KODU.ToString() }).ToList();\n");
	}
	if (strcmp(GetlistVarmi("BildirimKurTuruList"), "No")) {
		fprintf(output, "%s", indentstr());
		fprintf(output, "model.%s = Context.CommonService.GetListItems(ListConstants.BildirimKurTuruList);\n", GetlistVarmi("BildirimKurTuruList"));
	}
	if (strcmp(GetlistVarmi("BildirimStatuList"), "No")) {
		fprintf(output, "%s", indentstr());
		fprintf(output, "model.%s = Context.CommonService.GetListItems(ListConstants.BildirimStatuList);\n", GetlistVarmi("BildirimStatuList"));
	}
	if (strcmp(GetlistVarmi("HesapTuruList"), "No")) {
		fprintf(output, "%s", indentstr());
		fprintf(output, "model.%s = Context.CommonService.GetListItems(ListConstants.HesapTuruList);\n", GetlistVarmi("HesapTuruList"));
	}
	if (strcmp(GetlistVarmi("OtomatikRepoFlagList"), "No")) {
		fprintf(output, "%s", indentstr());
		fprintf(output, "model.%s = Context.CommonService.GetListItems(ListConstants.OtomatikRepoFlagList);\n", GetlistVarmi("OtomatikRepoFlagList"));
	}
	extrasYaz();

	for(i=0;i<icaches;i++) {
		fprintf(output, "%s", indentstr());
		p = caches[i] + 1;
		fprintf(output, "model.%s = Context.Cache.GetCache<List<%s>>(CacheConstants.%s)\n", p, p, p);
		fprintf(output, "%s", indentstr());
		fprintf(output, "	 // Burada Select icin Cache de yer alan alan adlari kullanilmalidir\n");
		fprintf(output, "%s", indentstr());
		fprintf(output, "	 // .Select(k => new ListTypes() { Value = k.VALUEDATA.ToString(), Text = k.TEXTDATA.Trim() + \"--\" + k.VALUEDATA.ToString() }).ToList();\n");
	}

	fprintf(output, "    Flow.AddVariableToFlow<%sViewModel>(new KeyValuePair<string, %sViewModel>(%sConstants.FlowView.Models, model));\n",
		tranname, tranname, tranname);
	fprintf(output, "%s", indentstr());
	fprintf(output, "#endregion\n");

	indents--;
	fprintf(output, "%s", indentstr());
	fprintf(output, "}\n");
}

void SetModels()
{
	int j;
	char yazilan[20][100];
	int k = 0, jj, vvarmi;
	indents = 1;
	fprintf(output, "%s", indentstr());
	fprintf(output, "public void SetModels()\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "{\n");
	indents++;
	fprintf(output, "%s", indentstr());
	fprintf(output, "if (Flow != null) {\n");
	indents++;
	for (j = 0; j < ivmodel; j++) {
		if (vmodel[j].sview) {
			vvarmi = 0;
			for (jj = 0; jj < k; jj++) {
				if (strcmp(yazilan[jj], vmodel[j].sview) == 0) {
					vvarmi = 1;
					break;
				}
			}
			if (vvarmi == 0) {
				fprintf(output, "%s", indentstr());
				if (strstr(vmodel[j].sview, "KriterView"))
					fprintf(output, "%s%sViewModel m%s = new %s%sViewModel(); \n", tranname, vmodel[j].sview, vmodel[j].sview, tranname, vmodel[j].sview);
				else fprintf(output, "%sViewModel m%s = new %sViewModel(); \n", vmodel[j].sview, vmodel[j].sview, vmodel[j].sview);
				strcpy(yazilan[k], vmodel[j].sview);
				fprintf(output, "%s", indentstr());
				fprintf(output, "Flow.SetModel(%s, m%s);\n", constVariables(vmodel[j].sview), vmodel[j].sview);
				k++;
			}
		}
	}
	fprintf(output, "%s", indentstr());
	fprintf(output, "// %sViewModel global = new %sViewModel();\n", tranname, tranname);
	fprintf(output, "%s", indentstr());
	fprintf(output, "Flow.SetModel(%sConstants.FlowView.Models, model);\n",tranname);
	indents--;
	fprintf(output, "%s", indentstr());
	fprintf(output, "}\n");
	indents--;
	fprintf(output, "%s", indentstr());
	fprintf(output, "}\n");
}

int isMonetary(int ix)
{
	int i, j, k, kk, jj, ii;
	kk = ix % 10000;
	jj = kk / 1000;
	kk = kk % 1000;
	ii = ix / 10000;
	for (i = ii; i < istate; i++) {
		for (j = jj; j < states[i].ientry; j++) {
			for (k = kk; k < states[i].entry[j].iexec; k++) {
					if (states[i].entry[j].eexec[k].execmon &&
						strstr(states[i].entry[j].eexec[k].execmon, "true"))
						return i * 1000 + j * 1000 + k;
			}
		}
	}
	return -1;
}

void endClient(char *trns, int ix, char *firstmodel, char *areaName)
{
	int i, j, k, isay = 1;
	char *px;
	// bsaptr = getprefs((char*)"BSACall");
	for (i = 0; i<istate; i++) {
		voidreturn = 0;
		if (strcmp(states[i].statetype, "initial")) {
			for (j = 0; j<states[i].ientry; j++) {
				if (states[i].entry[j].iexec > 0 ) {
					for (k = 0; k < states[i].entry[j].iexec; k++) {
						if (states[i].entry[j].eexec[k].execop) {
							px = strstr(states[i].entry[j].eexec[k].execop, "ClientOp");
							if (px)
								*px = 0;
							if (!varmi(states[i].entry[j].eexec[k].execop)) {
								// httpget(i, j, k, states[i].entry[j].eexec[k].execop, isay, areaName);
								httppost(i, states[i].entry[j].eexec[k].execop, isay, trns, areaName);
								isay++;
							}
						}
						else {
							px = modelBak(i);
							if (!varmi(px)) {
								// httpget(i, j, k, px, isay, areaName);
								httppost(i, px, isay, trns, areaName);
								isay++;
							}
						}
					}
				}
				else
				if (states[i].entry[j].icompcond > 0) {
					for (k = 0; k < states[i].entry[j].icompcond; k++) {
						px = modelBak(i);
						if (!varmi(px)) {
							httppost(i, px, isay, trns, areaName);
							isay++;
						}
					}
				}
				else
				if (states[i].entry[j].iinitcoll > 0 || states[i].entry[j].irmcoll > 0) {
					for (k = 0; k < states[i].entry[j].iinitcoll; k++) {

						httpcoll(i, states[i].stateid, isay, trns, areaName);
					}
					for (k = 0; k < states[i].entry[j].irmcoll; k++) {
						indents = 1;
						httprmcoll(i, states[i].stateid, isay, trns, areaName);
					}
				}
				else
				if (states[i].entry[j].irmcontext > 0) {
					for (k = 0; k < states[i].entry[j].irmcontext; k++) {
						indents=1;
						httpcontext(i, states[i].stateid, isay, trns, areaName);
					}
				}
			}
		}
	}

	fprintf(output, "%s", indentstr());

	if (param == 41) {
		int  ikk = 0;
		BSACall(areaName);
		while (ikk >= 0) {
			ikk = isMonetary(ikk);
			if (ikk >= 0) {
				BSAMonetaryCall(ikk, areaName);
				ikk = ikk+1;
			}
		}
	}
	else
		MCACall(areaName);

	GetLists(areaName, firstmodel);
	SetModels();

}

void startClient(char *trns, int ix, char *firstmodel, char *areaName)
{

	fprintf(output, "%s", indentstr());
	fprintf(output, "    #region Ctor\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "    public %sClientBusiness()\n", trns);
	fprintf(output, "%s", indentstr());
	fprintf(output, "        : base()\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "    {\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "    }\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "    #endregion\n");

	indexRegion(ix, trns, areaName);
	endClient(trns, ix, firstmodel, areaName);
}

char *nextState(char *trantype, struct STATE *st)
{
	int i;
	char *p = NULL;
	for (i = 0; i < st->itran; i++) {
		if (strstr(st->trans[i].tranid, "SetValue") &&
			strstr(st->trans[i].tranid, trantype))
			p = st->trans[i].trantarget;
		if (strstr(st->trans[i].tranid, "Printer") &&
			strstr(st->trans[i].tranid, trantype))
			p = st->trans[i].trantarget;
		if (strstr(st->trans[i].tranid, "Unstring") &&
			strstr(st->trans[i].tranid, trantype))
			p = st->trans[i].trantarget;
		if (strstr(st->trans[i].tranid, "EvaluateExpression") &&
			strstr(st->trans[i].tranid, trantype))
			p = st->trans[i].trantarget;		
		if (strstr(st->trans[i].tranid, "NavController") &&
			strstr(st->trans[i].tranid, trantype))
			p = st->trans[i].trantarget;
		if (strstr(st->trans[i].tranid, "ShowMessage") &&
			strstr(st->trans[i].tranid, trantype))
			p = st->trans[i].trantarget;
	}
	return p;
}

void vmcaEkle(char *v, char *m, int f)
{
	int i = ivmca;
	strcpy(vmca.view[i], v);
	strcpy(vmca.mca[i], m);
	vmca.yon[i] = f;
	ivmca++;
}

char *mcaName(char *s)
{
	int i, j, jj;
	char *p, *p1;
	for (i = 0; i < imca; i++) {
		for (j = 0; j < mca[i].imarr; j++) {
			if (strcmp(mca[i].marr[j].mcaitem, s) == 0) {
				p = (char *)calloc(1, strlen(mca[i].recname) + 1);
				strcpy(p, mca[i].recname);
				p1 = strstr(p, "Fmt");
				*p1 = 0;
				return p;
			}
		}
		for (jj = 0; jj < mca[i].icols; jj++) {
			for (j = 0; j < mca[i].cols[jj].icol; j++) {
				if (strcmp(mca[i].cols[jj].col[j].colitem, s) == 0) {
					p = (char*)calloc(1, strlen(mca[i].recname) + 1);
					strcpy(p, mca[i].recname);
					p1 = strstr(p, "Fmt");
					*p1 = 0;
					return p;
				}
			}
		}
	}
	return 0;
}

char *mcaRequestMi(char *s)
{
	int i, j;
	for (i = 0; i < imca; i++) {
		for (j = 0; j < mca[i].imarr; j++) {
			if (strcmp(mca[i].marr[j].mcaitem, s) == 0) {
				return mca[i].recname;
			}
		}
	}
	return 0;
}

char *mcaArrMi(char *s)
{
	int i, j, jj;
	for (i = 0; i < imca; i++) {
		for (jj = 0; jj < mca[i].icols; jj++) {
			for (j = 0; j < mca[i].cols[jj].icol; j++) {
				if (strcmp(mca[i].cols[jj].col[j].colitem, s) == 0)
					return mca[i].cols[jj].colname;
			}
		}
	}
	return 0;
}

int mcaVarmi(int req, char *md, char *s)
{
	int i, j, ix, jj;
	ix = -1;
	for (i = 0; i < imca; i++) {
		if ((req == 0) && strstr(mca[i].recname, "Request") && strstr(mca[i].recname, md))
		{
			ix = i;
			break;
		}
		if ((req == 1 || req == 10) && strstr(mca[i].recname, "Reply") && strstr(mca[i].recname, md))
		{
			ix = i;
			break;
		}
		if (md && req == 2 && strstr(mca[i].recname, md)) {
			ix = i;
			break;
		}
	}
	if (ix == -1) return ix;
	if ((req == 0) && strstr(mca[ix].recname, "Request") && strstr(mca[ix].recname, md)) {
		for (j = 0; j < mca[i].imarr; j++) {
			if (strcasecmp(mca[ix].marr[j].mcaitem, s) == 0)
				return ix * 10000 + j;
		}
		for (jj = 0; jj < mca[ix].icols; jj++) {
			for (j = 0; j < mca[ix].cols[jj].icol; j++) {
				if (strcasecmp(mca[ix].cols[jj].col[j].colitem, s) == 0)
					return ix * 10000 + jj * 1000 + j * 100;
			}
		}
	}
	if ((req == 1) && strstr(mca[ix].recname, "Reply") && strstr(mca[ix].recname, md)) {
		for (j = 0; j < mca[ix].imarr; j++) {
			if (strcmp(mca[ix].marr[j].mcaitem, s) == 0)
				return ix * 10000 + j;
		}
	}
	if ((req == 10) && strstr(mca[ix].recname, "Reply") && strstr(mca[ix].recname, md)) {
		for (jj = 0; jj < mca[ix].icols; jj++) {
			for (j = 0; j < mca[ix].cols[jj].icol; j++) {
				if (strcasecmp(mca[ix].cols[jj].col[j].colitem, s) == 0)
					return ix * 10000 + jj * 1000 + j * 100;
			}
		}
	}
	
	if (req == 2 && strstr(mca[ix].recname, md)) {
		for (j = 0; j < mca[ix].imarr; j++) {
			if (strcasecmp(mca[ix].marr[j].mcaitem, s) == 0)
				return ix * 10000 + j;
		}
		for (jj = 0; jj < mca[ix].icols; jj++) {
			for (j = 0; j < mca[ix].cols[jj].icol; j++) {
				if (strcasecmp(mca[ix].cols[jj].col[j].colitem, s) == 0)
					return ix * 10000 + jj * 1000 + j * 100;
			}
		}
	}
	return -1;
}

int viewVarMi(char *s)
{
	if(viewBak(s)) return 1;
	return 0;
}

int funcHeader(int i, int j, int k, int mtip, char *prev, char *lprevmca, char *rtype, char *intype)
{
	char *ppx, *px = modelBak(i);
	int  ii, mi, modelvar = 0;
	char* pm;
	indents = 1;
	voidreturn = 0;
	fprintf(output, "%s", indentstr());

	mi = mcaVarmi(2, px, states[i].entry[j].esetval[k].dataelm);
	if (mi >= 0) {
		ii = vmodelviewBak(states[i].trans[0].trantarget);
		if (ii >= 0) {
			if (states[i].entry[j].iexec > 0) {
				fprintf(output, "public bool %s(%sModel model)\n",
					states[i].stateid, modelBak(i));
				baslikyaz(states[i].stateid);
				frtype = 1;
			}
			else {
				if (inittarget[0] && strcmp(inittarget, vmodel[ii].sid) == 0) {
					baslikyaz(vmodel[ii].sid);
					if (vmodel[ii].sview && strcmp(vmodel[ii].sview, "void")) {
						if (strstr(vmodel[ii].sview, "KriterView")) {
							if (controllervarmi(vmodel[ii].sid))
								fprintf(output, "public %s%sViewModel %s()\n", tranname, vmodel[ii].sview, vmodel[ii].sid);
							else fprintf(output, "public %s%sViewModel %s(%s%sViewModel model)\n",
								tranname, vmodel[ii].sview, vmodel[ii].sid, tranname, vmodel[ii].sview);
						}
						else {
							if (controllervarmi(vmodel[ii].sid)) {
								pm = "";
								if (strcmp(vmodel[ii].sid, vmodel[ii].sview) == 0)
									fprintf(output, "public %s%sViewModel %s()\n", pm, vmodel[ii].sview, vmodel[ii].sid);
								else fprintf(output, "public %s%sViewModel %s(%s%sViewModel model)\n",
									pm, vmodel[ii].sview, vmodel[ii].sid, pm, vmodel[ii].sview);
							}
							else {
								fprintf(output, "public %sViewModel %s(%sViewModel model)\n", vmodel[ii].sview, states[i].stateid, vmodel[ii].sview);
							}
						}
					}
					else {
						if (strcmp(intype, "void"))
							fprintf(output, "public void %s(%sViewModel model)\n", vmodel[ii].sid, intype);
						else fprintf(output, "public void %s()\n", vmodel[ii].sid);
						voidreturn = 1;
					}
					frtype = 2;
				}
					
				// if (inittarget[0] && strcmp(inittarget, vmodel[ii].sid) == 0) {
				// 	baslikyaz(vmodel[ii].sid);
				// 	if (vmodel[ii].sview && strcmp(vmodel[ii].sview, "void")) {
				// 		if (strstr(vmodel[ii].sview, "KriterView")) {
				// 			pm = tranname;
				// 			if (controllervarmi(vmodel[ii].sid))
				// 				fprintf(output, "public %s%sViewModel %s()\n", pm, vmodel[ii].sview, vmodel[ii].sid);
				// 			else fprintf(output, "public %s%sViewModel %s(%s%sViewModel model)\n",
				// 				pm, vmodel[ii].sview, vmodel[ii].sid, pm, vmodel[ii].sview);
				// 		}
				// 		else {
				// 			if (controllervarmi(vmodel[ii].sid)) {
				// 				if (strcmp(vmodel[ii].sid, vmodel[ii].sview) == 0)
				// 					fprintf(output, "public %sViewModel %s()\n", vmodel[ii].sview, vmodel[ii].sid);
				// 				else fprintf(output, "public %sViewModel %s(%s%sViewModel model)\n",
				// 						vmodel[ii].sview, vmodel[ii].sid, vmodel[ii].sview);
				// 			}
				// 			else {
				// 				fprintf(output, "public %sViewModel %s(%sViewModel model)\n", vmodel[ii].sview, states[i].stateid, vmodel[ii].sview);
				// 			}
				// 		}
				// 	}
				// 	else {
				// 		if (strcmp(intype, "void"))
				// 			fprintf(output, "public void %s(%sViewModel model)\n", vmodel[ii].sid, intype);
				// 		else fprintf(output, "public void %s()\n", vmodel[ii].sid);
				// 		voidreturn = 1;
				// 	}
				// 	frtype = 2;
				// }
				else {
					if (states[i].entry[j].iopen > 0) {
						if (vmodel[ii].sview && strcmp(vmodel[ii].sview, "void")) {
							if (strcmp(rtype, vmodel[ii].sview) == 0 && strcmp(intype, modelBak(i)) == 0) {
								if (strstr(rtype, "KriterView")) {
									baslikyaz(states[i].stateid);
									if (controllervarmi(states[i].stateid))
										fprintf(output, "public %s%sViewModel %s()\n", tranname, rtype, vmodel[ii].sid);
									else fprintf(output, "public %s%sViewModel %s(%s%sViewModel model)\n", tranname, rtype, vmodel[ii].sid, tranname, buyukHarf(intype));
								}
								else {
									baslikyaz(states[i].stateid);
									if (controllervarmi(states[i].stateid))
										fprintf(output, "public %sViewModel %s()\n", buyukHarf(rtype), states[i].stateid);
									else fprintf(output, "public %sViewModel %s(%sViewModel model)\n",
										rtype, states[i].stateid, buyukHarf(intype));
								}
							}
						}
						else {
							if (strcmp(intype, "void"))
								fprintf(output, "public void %s(%sViewModel)\n", states[i].stateid, intype);
							else fprintf(output, "public void %s()\n", states[i].stateid);
							voidreturn = 1;
						}
						if (vmodel[ii].sview && strcmp(vmodel[ii].sview, "void")) {
							if (strcmp(rtype, vmodel[ii].sview) == 0 && strcmp(intype, modelBak(i))) {
								if (strstr(rtype, "KriterView"))
									pm = tranname;
								else pm = "";
								baslikyaz(states[i].stateid);
								if (controllervarmi(states[i].stateid))
									fprintf(output, "public %s%sViewModel %s()\n", pm, rtype, states[i].stateid);
								else fprintf(output, "public %s%sViewModel %s(%sModel model)\n", pm, rtype, states[i].stateid, buyukHarf(intype));
							}
							if (strcmp(rtype, vmodel[ii].sview) && strcmp(intype, modelBak(i)) == 0) {
								if (strstr(rtype, "KriterView"))
									pm = tranname;
								else pm = "";
								if (controllervarmi(states[i].stateid))
									fprintf(output, "public %s%sViewModel %s()\n", tranname, vmodel[ii].sview, states[i].stateid);
								else fprintf(output, "public %s%sViewModel %s(%sModel)\n", tranname, vmodel[ii].sview, states[i].stateid, buyukHarf(intype));
							}
							if (strcmp(rtype, vmodel[ii].sview) && strcmp(intype, modelBak(i))) {
								baslikyaz(states[i].stateid);
								if (strstr(vmodel[ii].sview, "KriterView"))
									pm = tranname;
								else pm = "";
								if (controllervarmi(states[i].stateid))
									fprintf(output, "public %s%sViewModel %s()\n", pm, vmodel[ii].sview, states[i].stateid);
								else fprintf(output, "public %s%sViewModel %s(%sModel)\n", pm, vmodel[ii].sview, states[i].stateid, buyukHarf(intype));
							}
						}
						else {
							if(strcmp(intype, "void"))
								fprintf(output, "public void %s(%sViewModel)\n", states[i].stateid, intype);
							else fprintf(output, "public void %s()\n", states[i].stateid);
							voidreturn = 1;
						}
						frtype = 2;
					}
					else {
						if (rtype && strcmp(rtype, "void")) {
							baslikyaz(states[i].stateid);
							if (controllervarmi(states[i].stateid))
								fprintf(output, "public void %s()\n", states[i].stateid);
							else fprintf(output, "public void %s(%sViewModel model)\n", states[i].stateid, modelBak(i));
						}
						else {
							baslikyaz(states[i].stateid);
							if (controllervarmi(states[i].stateid))
								fprintf(output, "public void %s()\n", states[i].stateid);
							else fprintf(output, "public void %s(%sViewModel model)\n", states[i].stateid, vmodel[ii].sview);
						}
						frtype = 3;
						voidreturn = 1;
					}
				}
			}
		}
		else {
			if (states[i].entry[j].iexec > 0) {
				baslikyaz(states[i].stateid);
				fprintf(output, "public bool %s(%sModel model)\n", states[i].stateid, buyukHarf(modelBak(i)));
				frtype = 1;
			}
			else {
				if (strcmp(states[i].statetype, "action") == 0) {
					if (inittarget[0] && strcmp(inittarget, states[i].stateid) == 0) {
						baslikyaz(states[i].stateid);
						if (intype) {
							if (strstr(intype, "KriterView"))
								pm = tranname;
							else pm = (char *)"";
							fprintf(output, "public %s%sViewModel %s(%s%sViewmodel m%s)\n",
								pm, intype, states[i].stateid, pm, intype, intype);
						}
						else {
							fprintf(output, "public void %s()\n", states[i].stateid);
							frtype = 3;
							voidreturn = 1;
						}
					}
					else {
						baslikyaz(states[i].stateid);
						if (mtip == 1) {
							fprintf(output, "public %sModel %s(%sModel model)\n",
								lprevmca, states[i].stateid, buyukHarf(lprevmca));
							frtype = 4;
						}
						else {
							int g;
							g = vmodeliiGet(states[i].stateid);
							if (strstr(vmodel[g].sview, "KriterView"))
								pm = tranname;
							else pm = (char *)"";
							if (g >= 0) {
								fprintf(output, "public %s%sViewModel %s(%s%sViewModel model)\n",
									pm, vmodel[g].sview, states[i].stateid, pm, vmodel[g].sview);
							}
							else {
								fprintf(output, "public void %s()\n", states[i].stateid);
							}
							frtype = 2;
						}
					}
				}
				else {
					baslikyaz(states[i].stateid);
					fprintf(output, "public %sModel %s(%sModel model)\n",
						modelBak(i), states[i].stateid, buyukHarf(modelBak(i)));
					frtype = 4;
				}
			}
		}
		modelvar = 1;
	}
	else {
		ii = vmodelBak(i);
		if (ii >= 0) {
			if (inittarget[0] && strcmp(inittarget, vmodel[ii].sid) == 0) {
				baslikyaz(states[i].stateid);
				if (strstr(vmodel[ii].sview, "KriterView"))
					pm = tranname;
				else pm = (char *)"";
				fprintf(output, "public %s%sViewModel %s()\n", pm, vmodel[ii].sview, states[i].stateid);
				frtype = 2;
			}
			else {
				if (states[i].entry[j].iopen > 0) {
					baslik(states[i].stateid);
					if (states[i].entry[j].esetval[k].dataelm[0] == '@') {
						if (strstr(vmodel[ii].sview, "KriterView"))
							pm = tranname;
						else pm = (char *)"";
						fprintf(output, "publc %s%sViewModel %s(string %s)\n",
							pm, vmodel[ii].sview, states[i].stateid, states[i].entry[j].esetval[k].dataelm + 1);
						frtype = 2;
					}
					else {
						if (strstr(rtype, "KriterView"))
							pm = tranname;
						else pm = (char *)"";
						if (strcmp(rtype, vmodel[ii].sview) == 0 && strcmp(intype, modelBak(i)) == 0) {
							fprintf(output, "public %s%sViewModel %s(%sModel model)\n",
								pm, rtype, states[i].stateid, intype);
						}
						if (strcmp(rtype, vmodel[ii].sview) == 0 && strcmp(intype, modelBak(i))) {
							fprintf(output, "public %s%sViewModel %s(%sModel model)\n",
								pm, rtype, states[i].stateid, intype);
						}
						if (strstr(vmodel[ii].sview, "KriterView"))
							pm = tranname;
						else pm = (char *)"";
						if (strcmp(vmodel[ii].sview, vmodel[ii].sview) == 0 && strcmp(intype, modelBak(i)) == 0) {
							fprintf(output, "public %s%sViewModel %s(%sModel model)\n",
								pm, vmodel[ii].sview, states[i].stateid, intype);
						}
						if (strcmp(vmodel[ii].sview, vmodel[ii].sview) == 0 && strcmp(intype, modelBak(i))) {
							fprintf(output, "public %s%sViewModel %s(%sModel model)\n",
								pm, vmodel[ii].sview, states[i].stateid, intype);
						}
						frtype = 2;
					}
				}
				else {
					int iy;
					iy = baslik(states[i].stateid);
					baslikyaz(states[i].stateid);
					if (states[i].entry[j].isetval > 0 && states[i].entry[j].esetval[k].dataelm[0] == '@') {
						if (funcs[iy].finmodel && strcmp(funcs[iy].finmodel, "void"))
							fprintf(output, "public %sViewModel %s(%sViewModel model)\n",
								funcs[iy].finmodel, states[i].stateid, funcs[iy].finmodel); // , states[i].entry[j].esetval[k].dataelm + 1);
						else 
						if(funcs[iy].finmodel && strcmp(funcs[iy].finmodel, "void") == 0) {
							fprintf(output, "public string %s(string %s)\n",
								states[i].stateid, states[i].entry[j].esetval[k].dataelm + 1);
							vmodel[ii].ftype = (char *)"string";
						}
						frtype = 5;
					}
					else {
						// voidviewmodel oluyor??
						//if (strcmp(states[i].stateid, "oncekiSayfa") == 0)
						//	fprintf(stderr, "burada\n");
						if(funcs[iy].finmodel && strcmp(funcs[iy].finmodel, "void"))
							fprintf(output, "public %sViewModel %s(%sViewModel model) // %s\n",
								funcs[iy].finmodel, states[i].stateid, funcs[iy].finmodel, states[i].entry[j].esetval[k].dataelm);
						else
							if (funcs[iy].fretmodel && strcmp(funcs[iy].fretmodel, "void") == 0) {
								fprintf(output, "public void %s() // %s\n",
									states[i].stateid, states[i].entry[j].esetval[k].dataelm);
								voidreturn = 1;
							}
							else {
								fprintf(output, "public string %s(string %s)\n",
									states[i].stateid, states[i].entry[j].esetval[k].dataelm);
								vmodel[ii].ftype = (char *)"string";
							}
						frtype = 5;
					}
				}
			}
		}
		else {
			int iy;
			iy = baslik(states[i].stateid);
			frtype = 5;
			baslikyaz(states[i].stateid);
			if (ii <= 399) {
				vmodel[ii].ftype = (char*)calloc(1, 7);
				if(vmodel[ii].ftype) strcpy(vmodel[ii].ftype, (char*)"string");
				if (states[i].entry[j].esetval[k].dataelm[0] == '@') {
					if (funcs[iy].finmodel)
						fprintf(output, "public %sViewModel %s(%sViewModel model) // %s\n",
							funcs[iy].finmodel, states[i].stateid, funcs[iy].finmodel, states[i].entry[j].esetval[k].dataelm + 1);
					else {
						fprintf(output, "public string %s(string %s)\n",
							states[i].stateid, states[i].entry[j].esetval[k].dataelm + 1);
						strcpy(vmodel[ii].ftype, (char*)"string");
					}
				}
				else {
					if (funcs[iy].finmodel)
						fprintf(output, "public %sViewModel %s(%sViewModel model) // %s\n",
							funcs[iy].finmodel, states[i].stateid, funcs[iy].finmodel, states[i].entry[j].esetval[k].dataelm);
					else {
						fprintf(output, "public string %s(string %s)\n",
							states[i].stateid, states[i].entry[j].esetval[k].dataelm);
						strcpy(vmodel[ii].ftype, (char*)"string");
					}
				}
			}
		}
		modelvar = 0;
	}
	fprintf(output, "%s", indentstr());
	fprintf(output, "{\n");
	indents++;
	if (globalvar == 0) {
		fprintf(output, "%s", indentstr());
		fprintf(output, " global = FillGlobals(global); \n");
	}
	globalvar = 1;
	ii = vmodelBak(i);
	if (ii >= 0)
		 ppx = vmodel[ii].sid;
	else ppx = states[i].stateid;
	if (inittarget[0] && strcmp(inittarget, ppx) == 0) {
		char lyazilan[20][100];
		int jx, jj, varmi;
		k = 0;
		for (jx = 0; jx < ivmodel; jx++) {
			if (vmodel[jx].sview) {
				varmi = 0;
				for (jj = 0; jj < k; jj++) {
					if (strcmp(lyazilan[jj], vmodel[jx].sview) == 0) {
						varmi = 1;
						break;
					}
				}
				if (varmi == 0) {
					fprintf(output, "%s", indentstr());
					if (strcmp(vmodel[jx].sview, intype)) {
						if (strstr(vmodel[jx].sview, "KriterView"))
							pm = tranname;
						else pm = (char *)"";
						fprintf(output, "%s%sViewModel m%s = new %s%sViewModel();\n",
							pm, vmodel[jx].sview, vmodel[jx].sview, pm, vmodel[jx].sview);
					}
					strcpy(lyazilan[k], vmodel[jx].sview);
					k++;
				}
			}
		}
		if (k > 0) {
			fprintf(output, "%s", indentstr());
			fprintf(output, "// asagidaki degiskenlerin uygun olan modele atanmasi gerekir.\n");
		}
	}
	return modelvar;
}

int identifierType(char *p)
{
	int i, j;
	char *p1;
	p1 = strstr(p, ".");
	if (!p1) 
		 p1 = p;
	else p1++;
	for (i = 0; i < ivname; i++) {
		for (j = 0; j < vname[i].ivitem; j++) {
			if (strcmp(vname[i].items[j].vitem, p1) == 0) {
				if (strcmp(vname[i].items[j].vitemcode, "D") == 0)
					return DATETYPE;
				else if (strcmp(vname[i].items[j].vitemcode, "S") == 0)
					return STRINGTYPE;
				else if (strcmp(vname[i].items[j].vitemcode, "N") == 0)
					return NUMERICTYPE;
				else
					return OTHERTYPE;
			}
		}
	}
	return OTHERTYPE;
}

char *leftdata(int modelvar, int ii, int i, int j, int k)
{
	char *p, *p1;
	char *lbuf = (char *)calloc(1, 200);
	if (states[i].entry[j].isetval > 0 && states[i].entry[j].esetval[k].dataelm[0] == '@') {
		lefttype = STRINGTYPE;
		globalData = 1;
		fprintf(output, "// pageflow variable\n");
		if (modelvar) {
			p = mcaArrMi(states[i].entry[j].esetval[k].dataelm + 1);
			if (p) {
				p1 = mcaName(states[i].entry[j].esetval[k].dataelm + 1);
				sprintf(lbuf, "model.%s = ", states[i].entry[j].esetval[k].dataelm + 1);
			}
			else
				sprintf(lbuf, "model.%s = ", buyukHarf(states[i].entry[j].esetval[k].dataelm + 1));
		}
		else {
			sprintf(lbuf, "model.%s = ", states[i].entry[j].esetval[k].dataelm + 1);
		}
	}
	else
		if (states[i].entry[j].iaddval > 0 && states[i].entry[j].eaddval[k].dataelm[0] == '@') {
			lefttype = STRINGTYPE;
			globalData = 1;
			fprintf(output, "// pageflow variable\n");
			if (modelvar) {
				p = mcaArrMi(states[i].entry[j].eaddval[k].dataelm + 1);
				if (p) {
					p1 = mcaName(states[i].entry[j].eaddval[k].dataelm + 1);
					sprintf(lbuf, "model.%s = ", states[i].entry[j].eaddval[k].dataelm + 1);
				}
				else
					sprintf(lbuf, "model.%s = ", buyukHarf(states[i].entry[j].eaddval[k].dataelm + 1));
			}
			else {
				sprintf(lbuf, "model.%s = ", states[i].entry[j].eaddval[k].dataelm + 1);
			}

		}
		else {
			if (states[i].entry[j].isetval) {
				lefttype = identifierType(states[i].entry[j].esetval[k].dataelm);
				if (modelvar) {
					p = mcaArrMi(states[i].entry[j].esetval[k].dataelm);
					if (p) {
						p1 = mcaName(states[i].entry[j].esetval[k].dataelm);
						sprintf(lbuf, "model.%sProp.%s[i].%s", p1, p, buyukHarf(states[i].entry[j].esetval[k].dataelm));
					}
					else {
						int indx = viewElement(states[i].entry[j].esetval[k].dataelm);
						if (indx >= 0) {
							if (inittarget[0]) {
								int ik = indx / 1000;
								sprintf(lbuf, "m%s.%s", vname[ik].viewname, states[i].entry[j].esetval[k].dataelm);
							}
							else {
								if (viewElementMi(vmodel[ii].sview, states[i].entry[j].esetval[k].dataelm) >= 0)
									sprintf(lbuf, "model.%s", states[i].entry[j].esetval[k].dataelm);
								else strcpy(lbuf, states[i].entry[j].esetval[k].dataelm);
							}
						}
						else {
							sprintf(lbuf, "model.%s = ", states[i].entry[j].esetval[k].dataelm);
							globalData = 1;
						}
					}
				}
				else {
					sprintf(lbuf, "model.%s = ", states[i].entry[j].esetval[k].dataelm);
					globalData = 1;
				}
			}
			if (states[i].entry[j].iaddval) {
				lefttype = identifierType(states[i].entry[j].eaddval[k].dataelm);
				if (modelvar) {
					p = mcaArrMi(states[i].entry[j].eaddval[k].dataelm);
					if (p) {
						p1 = mcaName(states[i].entry[j].eaddval[k].dataelm);
						sprintf(lbuf, "model.%sProp.%s[i].%s", p1, p, buyukHarf(states[i].entry[j].eaddval[k].dataelm));
					}
					else {
						int indx = viewElement(states[i].entry[j].eaddval[k].dataelm);
						if (indx >= 0) {
							if (inittarget[0]) {
								int ik = indx / 1000;
								sprintf(lbuf, "m%s.%s", vname[ik].viewname, states[i].entry[j].eaddval[k].dataelm);
							}
							else {
								if (viewElementMi(vmodel[ii].sview, states[i].entry[j].eaddval[k].dataelm) >= 0)
									sprintf(lbuf, "model.%s", states[i].entry[j].eaddval[k].dataelm);
								else strcpy(lbuf, states[i].entry[j].eaddval[k].dataelm);
							}
						}
						else {
							sprintf(lbuf, "model.%s = ", states[i].entry[j].eaddval[k].dataelm);
							globalData = 1;
						}
					}
				}
				else {
					sprintf(lbuf, "model.%s = ", states[i].entry[j].esetval[k].dataelm);
					globalData = 1;
				}
			}
	}
	return lbuf;
}
/* YENI EKLENDI  */
#ifdef YENI
char* fill(char* p, char s, int n)
{
	int i;
	for (i = 0; i < n; i++) {
		p[i] = s;
	}
	return p;
}
void tasi(char* t, char* s, int len)
{
	int i;
	for (i = 0; i < len; i++) {
		t[i] = s[i];
	}
}
void reportHlines(struct DOCPTR* h)
{
	int k, kcol;
	char line[300];
	fill(line, 299, ' ');
	for (k = 0; k < h->iheader; k++) {
		kcol = h->dheader[k].col;
		tasi(line + kcol, h->dheader[k].dname, h->dheader[k].len);
	}
}

void reportLines(struct REGDATA *d)
{
	int j, kcol;
	char line[300];
	fill(line, 299, ' ');
	for (j = 0; j < d->idata; j++) {
		kcol = d->ddata[j].col;
		tasi(line + kcol, d->ddata[j].dname, d->ddata[j].len);
	}
}

void reportSlines(struct BREAK *br)
{
	int k, kcol;
	char line[300];
	fill(line, 299, ' ');
	for (k = 0; k < br->ibline; k++) {
		kcol = br->bline[k].col;
		tasi(line + kcol, br->bline[k].dname, br->bline[k].len);
	}
}

void addfields(struct BREAK* br)
{
	int k;
	for (k = 0; k < br->ibline; k++) {
		if (br->bline[k].dname) {
			// add dname 
			br->bline[k].dname += 1000; // corresponding data
		}
	}
}

void reportBreak(int i, char *name)
{
	int j;
	for (j = 0; j < docptr[i].ibreak; j++) {
		if (strcmp(name, docptr[i].dbreak[j].icol) == 0) {
			if (strcmp(docptr[i].dbreak[j].id, "After") == 0)
				addfields(&docptr[i].dbreak[j]);
			reportSlines(&docptr[i].dbreak[j]);
		}
	}
}
void reportYazma(char* name)
{
	int i, j;

	for (i = 0; i < idocptr; i++) {
		if (strcmp(name, docptr[i].dname) == 0) {
			if (docptr[i].iheader) {
				reportHlines(&docptr[i]);
			}
			reportLines(&docptr[i].regdata);
			if (docptr[i].ibreak)
				reportBreak(i, docptr[i].regdata.ddata[0].dname);
		}
	}
}
#endif
void reportYazma(char* name)
{
}

void petitionprint(char *name)
{
	fprintf(output, "%s", indentstr());
	fprintf(output, "public PetitionPrintModel PrintPetition()\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "{\n");
	indents++;
	fprintf(output, "%s", indentstr());

	fprintf(output, "SlipPrintModel printModel = new SlipPrintModel();\n");

	fprintf(output, "%s", indentstr());
	fprintf(output, "//Dekonta yazdırılması istenen bilgiler printModel’in property’lerine atanarak printModel döndürülür.\n");
	reportYazma(name);
	fprintf(output, "%s", indentstr());
	fprintf(output, "return printModel;\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "}\n\n");
	indents--;
}


/* YENI EK SONU */

int isnumber(char *s)
{
	int  len = (int) strlen(s);
	int  i;
	for (i = 0; i < len; i++)
		if (s[i] < '0' || s[i] > '9')
			if (s[i] != '.' && s[i] != ',')
				return 0;
	return 1;
}

char *prev = 0;
char *prevmca = 0;
int  tip = 0;

void addvalFunc(int i, int j, char* rtype, char* intype)
{
	int  ii, k;
	int  ilk = 1;
	int  modelvar;
	char* modelptr;
	char* fvar;
	char* svar;
	char* p, * p1, * pp, * px, * ppx;
	char lbuf[200], rbuf[200], ssvar[200];
	char retvalue[200];
	char strvalue[100];
	int  retvar = 0, setvarmis = 0;

	retvalue[0] = 0;
	strvalue[0] = 0;
	ii = -1;
	fvar = 0;
	if (states[i].entry[j].iaddval) {
		// tip ve prev degerlerini bir onceki ekrandan bak
		if (prev == 0 && prevmca == 0) {
			ii = vmodelBak(i);
			if (ii >= 0) {
				prev = vmodel[ii].sview;
				prevmca = vmodel[ii].smodel;
			}
		}
		modelvar = 0;
		for (k = 0; k < states[i].entry[j].iaddval; k++) {
			fvar = 0;
			svar = 0;
			if (states[i].entry[j].iopen) tip = 2;
			if (states[i].entry[j].iexec) tip = 1;
			if (ilk) {
				int ix;
				ix = baslik(states[i].stateid);
				if (ix >= 0) {
					ii = vmodelBak(i);
					if (funcs[i].finmodel)
						modelvar = funcHeader(i, j, k, tip, prev, prevmca, funcs[ix].fretmodel, funcs[ix].finmodel);
					else modelvar = funcHeader(i, j, k, tip, prev, prevmca, funcs[ix].fretmodel, vmodel[ii].sview);
				}
				else modelvar = funcHeader(i, j, k, tip, prev, prevmca, rtype, intype);
				if (modelvar) {
					ii = vmodelBak(i);
					prev = vmodel[ii].sview;
					prevmca = vmodel[ii].smodel;
				}
				ilk = 0;
			}
			fprintf(output, "%s", indentstr());
			p = leftdata(modelvar, ii, i, j, k);
			strcpy(lbuf, p);
			lefttype = identifierType(p);
			//if (strstr(p, "SetVar"))
			//	setvarmis = 1;
			//else setvarmis = 0;

			fvar = (states[i].entry[j].eaddval[k].dataelm[0] == '@') ? 0 : p;
			if (fvar)
				rigthtype = identifierType(states[i].entry[j].eaddval[k].dataelm);
			else rigthtype = STRINGTYPE;
			if (states[i].entry[j].eaddval[k].defval) {
				if (states[i].entry[j].eaddval[k].defval[0] == '@') {
					char rbf[200];
					p = evaluateDefValue(CB, states[i].entry[j].eaddval[k].defval);
					rigthtype = STRINGTYPE;
					rbuf[0] = 0;
					// p = states[i].entry[j].eaddval[k].defval;
					while (p) {
						p1 = strstr(p, "+");
						if (p1) {
							*p1 = 0;
							p1++;
							if (modelvar) {
								pp = mcaArrMi(p);
								if (pp) {
									px = mcaName(p);
									sprintf(rbf, "%s", p);
									getglobal();
								}
								else {
									getglobal();
									sprintf(rbf, "%s", p);
								}
							}
							else {
								getglobal();
								sprintf(rbf, "%s", p);
							}
							strcat(rbuf, rbf);
							strcat(rbuf, "+"); // concat operator
						}
						if (p1 == 0)
							if (p) strcat(rbuf, p);
						p = p1;
					}
					if ((int)strlen(rbuf) == 0) {
						p = mcaArrMi(states[i].entry[j].eaddval[k].defval + 1);
						if (p) {
							px = mcaName(p);
							getglobal();
							sprintf(rbuf, "%s", evaluateDefValue(CB, states[i].entry[j].eaddval[k].defval));
						}
						else {
							getglobal();
							sprintf(rbuf, "%s", evaluateDefValue(CB, states[i].entry[j].eaddval[k].defval));
						}
					}
					// fprintf(output,"}\n");
					svar = 0;
				}
				else {
					rigthtype = identifierType(states[i].entry[j].eaddval[k].defval);
					if (strstr(states[i].entry[j].eaddval[k].defval, "/>")) {
						svar = (char*)" ";
					}
					else {
						if (modelvar) {
							if (states[i].entry[j].eaddval[k].defval) {
								p = mcaArrMi(states[i].entry[j].eaddval[k].defval);
								if (p) {
									px = mcaName(states[i].entry[j].eaddval[k].defval);
									sprintf(ssvar, "model.%sProp.%s[i].%s", px, p, buyukHarf(states[i].entry[j].eaddval[k].defval));
									svar = ssvar;
								}
								else {
									svar = states[i].entry[j].eaddval[k].defval;
								}
							}
							else svar = (char*)" ";
						}
						else {
							svar = states[i].entry[j].eaddval[k].defval;
						}
					}
				}
			}
			else svar = (char*)" ";

			if (fvar && svar) {
				if (svar[0] == ' ') {
					if (lefttype == NUMERICTYPE)
						fprintf(output, "%s = %s;\n", lookglobals(fvar), initVariables((char*)"0"));
					else fprintf(output, "%s = %s;\n", lookglobals(fvar), initVariables((char*)"\"\""));
				}
				else {
					if (lefttype == NUMERICTYPE) {
						if (strlen(svar) > 0)
							fprintf(output, "%s = %s;\n", lookglobals(fvar), initVariables(svar));
						else fprintf(output, "%s = %s;\n", lookglobals(fvar), initVariables((char*)"0"));
					}
					else fprintf(output, "%s = %s;\n", lookglobals(fvar), initVariables(svar));
				}
			}
			if (fvar == 0 && svar)
				fprintf(output, "%s\"%s\"));\n", lbuf, svar);
			if (svar == 0 && fvar)
				if (isnumber(rbuf)) {
					fprintf(output, "%s = %s;\n", lookglobals(fvar), initVariables(rbuf));
				}
				else {
					fprintf(output, "%s = %s;\n", lookglobals(fvar), rbuf);
				}
			if (fvar == 0 && svar == 0)
				fprintf(output, "%s %s));\n", lbuf, initVariables(rbuf));
		}
		// Flow da bilgileri sakla
		ii = vmodelBak(i);
		if (ii >= 0)
			ppx = vmodel[ii].sid;
		else ppx = states[i].stateid;
		if (inittarget[0] && strcmp(inittarget, ppx) == 0) {
			int  kopen;
			int  ix, ekrandir;
			int  jj, varmi;
			k = 0;
			for (j = 0; j < ivmodel; j++) {
				ix = vmodelBak(j);
				kopen = openVarmi(ix);
				ekrandir = 0;
				if (kopen >= 0 && states[ix].ientry > 0 && states[ix].entry[kopen].iopen > 0)
					ekrandir = 1;
				if (vmodel[j].sview && ekrandir) {
					// burada tum view modeller icin model tanimi yapilir
					varmi = 0;
					for (jj = 0; jj < k; jj++) {
						if (strcmp(yazilan[jj], vmodel[j].sview) == 0) {
							varmi = 1;
							break;
						}
					}
					if (varmi == 0) {
						fprintf(output, "%s", indentstr());
						if (strstr(vmodel[j].sview, "KriterView"))
							fprintf(output, "Flow.AddVariableToFlow<%s%sViewModel>(new KeyValuePair<string, %s%sViewModel>(%sConstants.%s, m%s));\n",
								tranname, vmodel[j].sview, tranname, vmodel[j].sview, tranname, getConstant((char*)"view", vmodel[j].sview), vmodel[j].sview);
						else fprintf(output, "Flow.AddVariableToFlow<%sViewModel>(new KeyValuePair<string, %sViewModel>(%sConstants.%s, m%s));\n",
							vmodel[j].sview, vmodel[j].sview, tranname, getConstant((char*)"view", vmodel[j].sview), vmodel[j].sview);
						strcpy(yazilan[k], vmodel[j].sview);
						k++;
					}
				}
			}
		}


		fprintf(output, "%s", indentstr());
		pp = nextState((char*)".OK", &states[i]);
		if (!pp)
			pp = nextState((char*)".ENTER", &states[i]);
		if (!pp)
			pp = nextState((char*)".DEVAM", &states[i]);
		if (!pp)
			pp = nextState((char*)".TAMAM", &states[i]);
		if (!pp)
			pp = nextState((char*)".CLICK", &states[i]);
		if (ekranmi(pp)) {
			fprintf(output, "return model;\n");
		}
		else {
			if (modelvar) {
				if (frtype == 4) {
					fprintf(output, "%sModel mmodel = new %sModel();\n", modelBak(i), modelBak(i));
					fprintf(output, "%s", indentstr());
					fprintf(output, "%s(mmodel); // SetValueAction.OK\n", pp);
				}
				else
					if (frtype == 3) {
						int  jj, ixx;
						ixx = vmodeliiGet(pp);
						for (jj = 0; jj < k; jj++) {
							if (strcmp(yazilan[jj], vmodel[ixx].sview) == 0) {
								fprintf(output, "%s", indentstr());
								fprintf(output, "%s(m%s);\n", pp, yazilan[jj]);
								fprintf(output, "%s", indentstr());
								fprintf(output, "return;\n");
								retvar = 1;
								break;
							}
						}
					}
					else
						if (frtype == 6) {
							fprintf(output, "%s", indentstr());
							fprintf(output, "%sModel mmodel = new %sModel();\n", modelBak(i), modelBak(i));
							// eger vname[i].icol > 0 ek tanım yap <=========
							fprintf(output, "%s", indentstr());
							fprintf(output, "%s(model); // SetValueAction.OK\n", pp);
						}
						else
							if (frtype == 5) {
								fprintf(output, "%s", indentstr());
								fprintf(output, "%s(model); // SetValueAction.OK\n", pp);
								fprintf(output, "%s", indentstr());
								fprintf(output, "return \"\"; //TODO: Burada baska bir string de donebilir\n");
								retvar = 1;
							}
				if (frtype == 2 && retvar == 0) {
					modelptr = (char*)"model";
					int iy = baslik(pp);
					if (iy >= 0 && funcs[iy].finmodel && strcmp(funcs[iy].finmodel, intype)) {
						//px = funcs[iy].finmodel;
						//fprintf(output, "%s", indentstr());
						//if (strstr(px, "KriterView"))
						//	fprintf(output, "    var vmodel = new %s%sViewModel();\n", tranname, px); // vmodel[iy].sview);
						//else fprintf(output, "    var vmodel = new %sViewModel();\n", px);
						//fprintf(output, "%s", indentstr());
						//if (constVariables(px)) {
						//	if (strstr(px, "KriterView"))
						//		fprintf(output, "        vmodel = Flow.GetViewDetail(%s).Model as %s%sViewModel;\n",
						//			constVariables(px), tranname, px);
						//	else fprintf(output, "        vmodel = Flow.GetViewDetail(%s).Model as %sViewModel;\n",
						//		constVariables(px), px);
						//}
						modelptr = (char*)"model";
					}
					if (iy >= 0 && funcs[iy].fretmodel && strcmp(funcs[iy].fretmodel, rtype)) {
						fprintf(output, "%s", indentstr());
						fprintf(output, "%s(%s); \n", pp, modelptr);
						fprintf(output, "%s", indentstr());
						fprintf(output, "return model;\n");
					}
					else {
						fprintf(output, "%s", indentstr());
						fprintf(output, "return %s(%s);\n", pp, modelptr);
					}
				}
				else {
					if (retvar == 0) {
						fprintf(output, "%s", indentstr());
						fprintf(output, "return model; // AddValueAction.OK\n");
					}
				}
			}
			else
				if (retvar == 0) {
					fprintf(output, "return model;\n");
				}
		}
		indents--;
		fprintf(output, "%s", indentstr());
		fprintf(output, "}\n\n");
		indents--;
		if (inittarget[0]) inittarget[0] = 0;
	}
}

void setValFunc(int i, char *rtype, char *intype)
{
	int  ii, j, k, kk;
	int  ilk = 1;
	int  modelvar;
	char* modelptr;
	char* fvar;
	char* svar;
	char* p, * p1, * pp, * px, * ppx;
	char lbuf[200], rbuf[200], ssvar[200];
	char retvalue[200];
	char strvalue[100];
	int  retvar = 0, setvarmis = 0;

	retvalue[0] = 0;
	strvalue[0] = 0;
	ii = -1;
	fvar = 0;
	for (j = 0; j < states[i].ientry; j++) {
		if (states[i].entry[j].isetval) {
			// tip ve prev degerlerini bir onceki ekrandan bak
			if (prev == 0 && prevmca == 0) {
				ii = vmodelBak(i);
				if (ii >= 0) {
					prev = vmodel[ii].sview;
					prevmca = vmodel[ii].smodel;
				}
			}
			modelvar = 0;
			for (k = 0; k < states[i].entry[j].isetval; k++) {
				fvar = 0;
				svar = 0;
				if (states[i].entry[j].iopen) tip = 2;
				if (states[i].entry[j].iexec) tip = 1;
				if (ilk) {
					int ix;
					ix = baslik(states[i].stateid);
					if (ix >= 0) {
						ii = vmodelBak(i);
						if (funcs[i].finmodel)
							modelvar = funcHeader(i, j, k, tip, prev, prevmca, funcs[ix].fretmodel, funcs[ix].finmodel);
						else modelvar = funcHeader(i, j, k, tip, prev, prevmca, funcs[ix].fretmodel, vmodel[ii].sview);
					}
					else modelvar = funcHeader(i, j, k, tip, prev, prevmca, rtype, intype);
					if (modelvar) {
						ii = vmodelBak(i);
						prev = vmodel[ii].sview;
						prevmca = vmodel[ii].smodel;
					}
					ilk = 0;
				}
				fprintf(output, "%s", indentstr());
				p = leftdata(modelvar, ii, i, j, k);
				strcpy(lbuf, p);
				//if (strstr(lbuf, "SetVar"))
				//	setvarmis = 1;
				//else setvarmis = 0;
				lefttype = identifierType(p);

				fvar = (states[i].entry[j].esetval[k].dataelm[0] == '@') ? 0 : p;
				if (fvar)
					rigthtype = identifierType(states[i].entry[j].esetval[k].dataelm);
				else rigthtype = STRINGTYPE;
				if (states[i].entry[j].esetval[k].defval) {
					if (states[i].entry[j].esetval[k].defval[0] == '@') {
						char rbf[200];
						p = evaluateDefValue(CB, states[i].entry[j].esetval[k].defval);
						rigthtype = STRINGTYPE;
						rbuf[0] = 0;
						// p = states[i].entry[j].esetval[k].defval;
						while (p) {
							p1 = strstr(p, "+");
							if (p1) {
								*p1 = 0;
								p1++;
								if (modelvar) {
									pp = mcaArrMi(p);
									if (pp) {
										px = mcaName(p);
										sprintf(rbf, "%s", p);
										getglobal();
									}
									else {
										getglobal();
										sprintf(rbf, "%s", p);
									}
								}
								else {
									getglobal();
									sprintf(rbf, "%s", p);
								}
								strcat(rbuf, rbf);
								strcat(rbuf, "+"); // concat operator
							}
							if (p1 == 0)
								if (p) strcat(rbuf, p);
							p = p1;
						}
						if ((int)strlen(rbuf) == 0) {
							p = mcaArrMi(states[i].entry[j].esetval[k].defval + 1);
							if (p) {
								px = mcaName(p);
								getglobal();
								sprintf(rbuf, "%s", evaluateDefValue(CB, states[i].entry[j].esetval[k].defval));
							}
							else {
								getglobal();
								sprintf(rbuf, "%s", evaluateDefValue(CB, states[i].entry[j].esetval[k].defval));
							}
						}
						// fprintf(output,"}\n");
						svar = 0;
					}
					else {
						rigthtype = identifierType(states[i].entry[j].esetval[k].defval);
						if (strstr(states[i].entry[j].esetval[k].defval, "/>")) {
							svar = (char *)" ";
						}
						else {
							if (modelvar) {
								if (states[i].entry[j].esetval[k].defval) {
									p = mcaArrMi(states[i].entry[j].esetval[k].defval);
									if (p) {
										px = mcaName(states[i].entry[j].esetval[k].defval);
										sprintf(ssvar, "model.%sProp.%s[i].%s", px, p, buyukHarf(states[i].entry[j].esetval[k].defval));
										svar = ssvar;
									}
									else {
										svar = states[i].entry[j].esetval[k].defval;
									}
								}
								else svar = (char *)" ";
							}
							else {
								svar = states[i].entry[j].esetval[k].defval;
							}
						}
					}
				}
				else svar = (char*)" ";

				if (fvar && svar) {
					if (svar[0] == ' ') {
						if (lefttype == NUMERICTYPE)
							fprintf(output, "%s = %s;\n", lookglobals(fvar), initVariables((char*)"0"));
						else fprintf(output, "%s = %s;\n", lookglobals(fvar), initVariables((char*)"\"\""));
					}
					else {
						if (lefttype == NUMERICTYPE) {
							if (strlen(svar) > 0)
								fprintf(output, "%s = %s;\n", lookglobals(fvar), initVariables(svar));
							else fprintf(output, "%s = %s;\n", lookglobals(fvar), initVariables((char*)"0"));
						}
						else fprintf(output, "%s = %s;\n", lookglobals(fvar), initVariables(svar));
					}
				}
				if (fvar == 0 && svar)
					fprintf(output, "%s\"%s\"));\n", lbuf, svar);
				if (svar == 0 && fvar)
					if (isnumber(rbuf)) {
						if(setvarmis)
							fprintf(output, "%s %s;\n", lookglobals(fvar), initVariables(rbuf));
						else fprintf(output, "%s = %s;\n", lookglobals(fvar), initVariables(rbuf));
					}
					else {
						if(setvarmis) 
							fprintf(output, "%s %s;\n", lookglobals(fvar), rbuf);
						else fprintf(output, "%s = %s;\n", lookglobals(fvar), rbuf);
					}
				if (fvar == 0 && svar == 0)
					fprintf(output, "%s %s));\n", lbuf, initVariables(rbuf));
			}
			// Flow da bilgileri sakla
			ii = vmodelBak(i);
			if (ii >= 0)
				ppx = vmodel[ii].sid;
			else ppx = states[i].stateid;
			if (inittarget[0] && strcmp(inittarget, ppx) == 0) {
				int  kopen;
				int  ix, ekrandir;
				int  jj, varmi; 
				k = 0;
				for (j = 0; j < ivmodel; j++) {
					ix = vmodelBak(j);
					kopen = openVarmi(ix);
					ekrandir = 0;
					if (kopen >= 0 && states[ix].ientry > 0 && states[ix].entry[kopen].iopen > 0)
						ekrandir = 1;
					if (vmodel[j].sview && ekrandir) {
						// burada tum view modeller icin model tanimi yapilir
						varmi = 0;
						for (jj = 0; jj < k; jj++) {
							if (strcmp(yazilan[jj], vmodel[j].sview) == 0) {
								varmi = 1;
								break;
							}
						}
						if (varmi == 0) {
							fprintf(output, "%s", indentstr());
							if (strstr(vmodel[j].sview, "KriterView"))
								fprintf(output, "Flow.AddVariableToFlow<%s%sViewModel>(new KeyValuePair<string, %s%sViewModel>(%sConstants.%s, m%s));\n",
									tranname, vmodel[j].sview, tranname, vmodel[j].sview, tranname, getConstant((char*)"view", vmodel[j].sview), vmodel[j].sview);
							else fprintf(output, "Flow.AddVariableToFlow<%sViewModel>(new KeyValuePair<string, %sViewModel>(%sConstants.%s, m%s));\n",
								vmodel[j].sview, vmodel[j].sview, tranname, getConstant((char*)"view", vmodel[j].sview), vmodel[j].sview);
							strcpy(yazilan[k], vmodel[j].sview);
							k++;
						}
					}
				}
			}


			fprintf(output, "%s", indentstr());
			pp = nextState((char*)".OK", &states[i]);
			if (!pp)
				pp = nextState((char*)".ENTER", &states[i]);
			if (!pp)
				pp = nextState((char*)".DEVAM", &states[i]);
			if (!pp)
				pp = nextState((char*)".TAMAM", &states[i]);
			if (!pp)
				pp = nextState((char*)".CLICK", &states[i]);
			if (ekranmi(pp)) {
				fprintf(output, "return model;\n");
			}
			else {
				if (modelvar) {
					if (frtype == 4) {
						fprintf(output, "%sModel mmodel = new %sModel();\n", modelBak(i), modelBak(i));
						fprintf(output, "%s", indentstr());
						fprintf(output, "%s(mmodel); // SetValueAction.OK\n", pp);
					}
					else
						if (frtype == 3) {
							int  jj, ixx;
							ixx = vmodeliiGet(pp);
							for (jj = 0; jj < k; jj++) {
								if (strcmp(yazilan[jj], vmodel[ixx].sview) == 0) {
									fprintf(output, "%s", indentstr());
									fprintf(output, "%s(m%s);\n", pp, yazilan[jj]);
									fprintf(output, "%s", indentstr());
									fprintf(output, "return;\n");
									retvar = 1;
									break;
								}
							}
						}
						else
							if (frtype == 6) {
								fprintf(output, "%s", indentstr());
								fprintf(output, "%sModel mmodel = new %sModel();\n", modelBak(i), modelBak(i));
								// eger vname[i].icol > 0 ek tanım yap <=========
								fprintf(output, "%s", indentstr());
								fprintf(output, "%s(model); // SetValueAction.OK\n", pp);
							}
							else
								if (frtype == 5) {
									fprintf(output, "%s", indentstr());
									fprintf(output, "%s(model); // SetValueAction.OK\n", pp);
									fprintf(output, "%s", indentstr());
									fprintf(output, "return \"\"; //TODO: Burada baska bir string de donebilir\n");
									retvar = 1;
								}
					if (frtype == 2 && retvar == 0) {
						modelptr = (char *)"model";
						int iy = baslik(pp);
						if (iy >= 0 && funcs[iy].finmodel && strcmp(funcs[iy].finmodel, intype)) {
							//px = funcs[iy].finmodel;
							//fprintf(output, "%s", indentstr());
							//if (strstr(px, "KriterView"))
							//	fprintf(output, "    var vmodel = new %s%sViewModel();\n", tranname, px); // vmodel[iy].sview);
							//else fprintf(output, "    var vmodel = new %sViewModel();\n", px);
							//fprintf(output, "%s", indentstr());
							//if (constVariables(px)) {
							//	if (strstr(px, "KriterView"))
							//		fprintf(output, "        vmodel = Flow.GetViewDetail(%s).Model as %s%sViewModel;\n",
							//			constVariables(px), tranname, px);
							//	else fprintf(output, "        vmodel = Flow.GetViewDetail(%s).Model as %sViewModel;\n",
							//		constVariables(px), px);
							//}
							modelptr = (char*)"model";
						}
						if (iy >= 0 && funcs[iy].fretmodel && strcmp(funcs[iy].fretmodel, rtype)) {
							fprintf(output, "%s", indentstr());
							fprintf(output, "%s(%s); \n", pp, modelptr);
							fprintf(output, "%s", indentstr());
							fprintf(output, "return model;\n");
						}
						else {
							fprintf(output, "%s", indentstr());
							fprintf(output, "return %s(%s);\n", pp, modelptr);
						}
					}
					else {
						if (retvar == 0) {
							fprintf(output, "%s", indentstr());
							fprintf(output, "return model; // SetValueAction.OK\n");
						}
					}
				}
				else
					if (retvar == 0) {
						fprintf(output, "return model;\n");
					}
			}
			indents--;
			fprintf(output, "%s", indentstr());
			fprintf(output, "}\n\n");
			indents--;
			if (inittarget[0]) inittarget[0] = 0;
		}
		if (states[i].entry[j].iaddval) {
			addvalFunc(i, j, rtype, intype);
		}
		if (states[i].entry[j].eprintid) {
			if ((int)strlen(states[i].entry[j].eprintid) > 0) {
				px = modelBak(i);

				indents++;
				ii = vmodelBak(i);
				if (ii != -1) {
					fprintf(output, "public SlipPrintModel %s(%sModel model)\n", states[i].stateid, vmodel[ii].smodel);
				}
				else {
					vmodel[ii].ftype = (char*)"string";
					if (strstr(px, "KriterView"))
						fprintf(output, "public %s%sViewModel %s(%s%sViewModel model)\n",
							tranname, px, states[i].stateid, tranname, px);
					else fprintf(output, "public %sViewModel %s(%sViewModel model)\n",
						px, states[i].stateid, px);
					frtype = 5;
				}
				fprintf(output, "%s", indentstr());
				fprintf(output, "{\n");
				indents++;
				fprintf(output, "%s", indentstr());
				fprintf(output, "// Burada print islemi yapilir\n");
				fprintf(output, "%s", indentstr());
				fprintf(output, "var pmodel = PrintSlip(model); \n");
				fprintf(output, "%s", indentstr());
				fprintf(output, "return pmodel; \n");
				indents--;

				frtype = 2;
				fprintf(output, "%s", indentstr());
				fprintf(output, "}\n\n");
				indents--;
			}
		}
		if (states[i].entry[j].igenexp > 0) {
			for (k = 0; k < states[i].entry[j].igenexp; k++) {
				kk = vmodeliiGet(states[i].stateid);
				px = vmodel[kk].sview;
				vmodel[kk].ftype = (char*)"string";
				indents++;
				fprintf(output, "%s", indentstr());
				if (strstr(px, "KriterView"))
					fprintf(output, "public %s%sViewModel %s(%s%sViewModel model)\n",
						tranname, px, states[i].stateid, tranname, px);
				else fprintf(output, "public %sViewModel %s(%sViewModel model)\n",
					px, states[i].stateid, px);
				frtype = 5;
				fprintf(output, "%s", indentstr());
				fprintf(output, "{\n");
				indents++;
				fprintf(output, "%s", indentstr());
				fprintf(output, "model.FunctionInfo.Name = %sConstants.AkbankPanel1;\n", tranname);
				fprintf(output, "%s", indentstr());
				fprintf(output, "%s", indentstr());
				fprintf(output, "// get Combox data\n");
				fprintf(output, "%s", indentstr());
				for (kk = 0; kk < states[i].itran; kk++) {
					if (kk == 0) {
						getglobal();
						fprintf(output, "%s", indentstr());
						fprintf(output, "string %s = model.%s;\n", states[i].entry[j].egenexp[k].genexpid, states[i].entry[j].egenexp[k].genexpid);
						fprintf(output, "%s", indentstr());
						fprintf(output, "try {\n");
						indents++;
					}
					if (strstr(states[i].trans[kk].tranid, "OK")) {
						fprintf(output, "%s", indentstr());
						fprintf(output, "	%s = %s(model, %s);\n", states[i].entry[j].egenexp[k].genexpid,
							states[i].trans[kk].trantarget, states[i].entry[j].egenexp[k].genexpid);
						fprintf(output, "%s", indentstr());
						if (frtype == 5)
							fprintf(output, "return %s;\n", states[i].entry[j].egenexp[k].genexpid);
					}
					else {
						indents--;
						fprintf(output, "%s", indentstr());
						fprintf(output, "} catch {\n");
						indents++;
						fprintf(output, "%s", indentstr());
						fprintf(output, "return %s(model, %s);\n", states[i].trans[kk].trantarget, states[i].entry[j].egenexp[k].genexpid);
					}
				}
				indents--;
				fprintf(output, "%s", indentstr());
				fprintf(output, "}\n");
				indents--;
				fprintf(output, "%s", indentstr());
				fprintf(output, "}\n\n");
				indents--;
			}
		}
		if (states[i].entry[j].iunstr > 0) {
			char global[100];
			for (k = 0; k < states[i].entry[j].iunstr; k++) {
				if (ilk) {
					kk = vmodeliiGet(states[i].stateid);
					px = vmodel[kk].sview;
					indents++;
					frtype = 5;
					fprintf(output, "%s", indentstr());
					// ===> burada indata model ve return model degisecek
					vmodel[kk].ftype = (char*)"string";
					if (px) {
						if (strstr(px, "KriterView"))
							fprintf(output, "public %s%sViewModel %s(%s%sViewModel model, string %s)\n",
								tranname, px, states[i].stateid, tranname, px, states[i].entry[j].unstr[k].src);
						else fprintf(output, "public %sViewModel %s(%sViewModel model, string %s)\n",
							px, states[i].stateid, px, states[i].entry[j].unstr[k].src);
					}
					else
						fprintf(output, "public string %s(string %s)\n",
							states[i].stateid, states[i].entry[j].unstr[k].src);
					fprintf(output, "%s", indentstr());
					fprintf(output, "{\n");
					ilk = 0;
					indents++;
					fprintf(output, "%s", indentstr());
					fprintf(output, "try {\n");
					indents++;
				}
				strcpy(global, states[i].entry[j].unstr[k].src);
				getglobal();
				fprintf(output, "%s", indentstr());
				fprintf(output, "%s = %s.Substring(%d, %d);\n",
					states[i].entry[j].unstr[k].src,
					states[i].entry[j].unstr[k].src,
					states[i].entry[j].unstr[k].len,
					states[i].entry[j].unstr[k].start);
				strcpy(retvalue, states[i].entry[j].unstr[k].src);
				strcpy(strvalue, states[i].entry[j].unstr[k].src);
			}
			pp = nextState((char*)".OK", &states[i]);
			if (!pp)
				pp = nextState((char*)".ENTER", &states[i]);
			if (!pp)
				pp = nextState((char*)".DEVAM", &states[i]);
			if (!pp)
				pp = nextState((char*)".TAMAM", &states[i]);
			if (!pp)
				pp = nextState((char*)".CLICK", &states[i]);
			fprintf(output, "%s", indentstr());
			if (ekranmi(pp)) {
				fprintf(output, "return model;\n");
			}
			else {
				int  mi;
				mi = mcaVarmi(2, modelBak(i), pp);
				if (strvalue[0]) {
					if (mi >= 0)
						fprintf(output, "%s(model, %s); // unstringAction.OK\n", pp, strvalue);
					else
						fprintf(output, "%s(model, %s); // unstringAction.OK\n", pp, strvalue);
				}
				else {
					if (mi >= 0)
						fprintf(output, "%s(model); // unstringAction.OK\n", pp);
					else
						fprintf(output, "%s(model); // unstringAction.OK\n", pp);
				}
				if (frtype == 5) {
					fprintf(output, "%s", indentstr());
					if (strvalue[0])
						fprintf(output, "return %s; // burada baska bir deger de dondurulebilir \n", strvalue);
					else
						fprintf(output, "return ""; // burada baska bir deger de dondurulebilir \n");
				}
			}
			strvalue[0] = 0;
			indents--;
			fprintf(output, "%s", indentstr());
			fprintf(output, "} catch {\n");
			indents++;
			pp = nextState((char *)".ERROR", &states[i]);
			fprintf(output, "%s", indentstr());
			if (ekranmi(pp)) {
				fprintf(output, "     return \"%s\"; // unstringAction.ERROR\n", pp);
			}
			else {
				if (frtype == 5) {
					if (pp) {
						fprintf(output, "     %s(model); // unstringAction.ERROR\n", pp);
					}
					fprintf(output, "%s", indentstr());
					fprintf(output, "     return model; // unstringAction.ERROR\n");
					//fprintf(output, "     return \"\";\n");
				}
			}
			fprintf(output, "%s", indentstr());
			indents--;
			fprintf(output, "%s", indentstr());
			fprintf(output, "}\n");
			indents--;
			fprintf(output, "%s", indentstr());
			fprintf(output, "}\n");
			indents--;
		}
		if (states[i].entry[j].ishowmsg > 0) {
			for (k = 0; k < states[i].entry[j].ishowmsg; k++) {
				if (ilk) {
					int g = vmodeliiGet(states[i].stateid);
					px = vmodel[g].sview;
					indents++;
					fprintf(output, "%s", indentstr());
					fprintf(output, "/* TODO: Aslinda mesaj ekrana iletilmeli ve ts mesaji goruntulemeli...*/\n");
					fprintf(output, "%s", indentstr());
					fprintf(output, "public %sViewModel %s(%sViewModel model)\n",
						px, states[i].stateid, px);
					frtype = 5;
					fprintf(output, "%s", indentstr());
					fprintf(output, "{\n");
					indents++;
					fprintf(output, "%s", indentstr());
					if (states[i].entry[j].eshowmsg[k].message[0] == '@')
						fprintf(output, "model.OperationResult.Message = model.%s;\n", states[i].entry[j].eshowmsg[k].message + 1);
					else
						if (initVariables(states[i].entry[j].eshowmsg[k].message))
							fprintf(output, "model.OperationResult.Message = %s;\n", initVariables(states[i].entry[j].eshowmsg[k].message));
						else fprintf(output, "model.OperationResult.Message = \"%s\";\n", states[i].entry[j].eshowmsg[k].message);
					ilk = 0;
				}
			}
			pp = nextState((char*)".OK", &states[i]);
			if (!pp)
				pp = nextState((char*)".ENTER", &states[i]);
			if (!pp)
				pp = nextState((char*)".DEVAM", &states[i]);
			if (!pp)
				pp = nextState((char*)".TAMAM", &states[i]);
			if (!pp)
				pp = nextState((char*)".CLICK", &states[i]);
			fprintf(output, "%s", indentstr());
			if (ekranmi(pp)) {
				fprintf(output, "return model; // messageAction.OK\n");
			}
			else {
				if (frtype == 5) {
					fprintf(output, "%s", indentstr());
					fprintf(output, "%s(model); // messageAction.OK\n", pp);
					fprintf(output, "%s", indentstr());
					if (retvalue[0] != 0)
						fprintf(output, "return model.%s; // Burada baska bir string dondurulebilir\n", retvalue);
					else fprintf(output, "return \"\"; // Burada baska bir string dondurulebilir\n");
				}
				else {
					fprintf(output, "return %s(model); // messageAction.OK\n", pp);
				}
			}
			indents--;
			fprintf(output, "%s", indentstr());
			fprintf(output, "}\n");
		}
	}
}

void moveMmodel(char* myexecop, char* rtype, char* retval)
{
	fprintf(output, "%s", indentstr());
	fprintf(output, "    %sModelTo%s(mmodel, %s);\n", myexecop, rtype, retval);
	AddMCAtoView(myexecop, rtype);
}

int  elselink(int i, int j, char* rtype, char* intype, char* retval)
{
	char* px;
	int  iy;
	char* curr, * currval;
	px = states[i].trans[j].trantarget;
	iy = getfuncLoc(px);
	fprintf(output, "%s", indentstr());
	fprintf(output, "else {\n");
	/*indents++;*/
	if (funcs[iy].finmodel && strcmp(funcs[iy].finmodel, rtype) == 0) {
		fprintf(output, "%s", indentstr());
		fprintf(output, "    %s.OperationResult.IsSuccessful = mmodel.OperationResult.IsSuccessful;\n", retval);
		fprintf(output, "%s", indentstr());
		fprintf(output, "    %s.OperationResult.Message = mmodel.OperationResult.Message;\n", retval);
		return 1;
	}
	else {
		// cViewModel(output, rtype, retval);
		/*yazgetViews(rtype, retval);*/
		fprintf(output, "%s", indentstr());
		fprintf(output, "    %s.OperationResult.IsSuccessful = mmodel.OperationResult.IsSuccessful;\n", retval);
		fprintf(output, "%s", indentstr());
		fprintf(output, "    %s.OperationResult.Message = mmodel.OperationResult.Message;\n", retval);
		curr = rtype;
		currval = retval;
		// createView2(output, intype, retval);
		/*yazsaveViews(intype, retval);*/
		return 0;
	}
}

int  iflink(int i, int j, char* rtype, char* intype, char* myexecop, char* retval)
{
	char* px, * rtypeval;
	int  iy;
	char* currval, * curr;
	px = states[i].trans[j].trantarget;
	iy = getfuncLoc(px);
	rtypeval = retval;
	fprintf(output, "%s", indentstr());
	fprintf(output, "if(retcode == true)\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "    {\n");
	if (strcmp(intype, funcs[iy].finmodel) == 0) {
		if (strcmp(rtype, intype) == 0) {
			moveMmodel(myexecop, rtype, retval);
			currval = retval;
			curr = rtype;
		}
		else {
			// cViewModel(output, rtype, retval);
			fprintf(output, "    ");
			/*yazgetViews(rtype, retval);*/
			moveMmodel(myexecop, rtype, retval);
			curr = rtype;
			currval = retval;
			// createView2(output, intype, retval);
			/*fprintf(output, "    ");*/
			/*yazsaveViews(intype, retval);*/
		}
		fprintf(output, "    ");
		saveGlobal();
		fprintf(output, "%s", indentstr());
		fprintf(output, "    return %s(%s);\n", px, retval);
		fprintf(output, "%s", indentstr());
		fprintf(output, "    }\n");
		return 1;
	}
	return 0;
}

void mViewModel(char* rtype, char* retmodel, char* retval, char* currval)
{
	fprintf(output, "%s", indentstr());
	fprintf(output, "    %sViewModelTo%s(%s, %s);\n", retmodel, rtype, retval, currval);
	AddViewtoView(retmodel, rtype);
}

int yazilmismi(char* p)
{
	int  i;
	for (i = 0; i < iyazilan; i++) {
		if (strcmp(yazilan[i], p) == 0)
			return 1;
	}
	return 0;
}

void saklaRefs(int ii)
{
	int j, ix;
	char* svv;
	for (j = 0; j < states[ii].isref; j++) {
		if (yazilmismi(states[ii].staterefs[j]) == 0) {
			ix = stateVarmi(states[ii].staterefs[j]);
			if (ix >= 0) {
				svv = getView(states[ix].stateid);
				mySaveStack(states[ix].stateid, ix, svv, progname, tranname, areaName);
			}
		}
	}
}


int returnCall(int i, char* rtype, char* intype, char* myexecop, char* retval)
{
	int   iy, j, ret, ifset = 0;
	char* px, * currtype, * currval;
	for (j = 0; j < states[i].itran; j++) {
		if (strstr(states[i].trans[j].tranid, "Op.OK")) {
			// YAPILACAK
			saklaRefs(i);
			currval = retval;
			currtype = rtype;
			ret = iflink(i, j, rtype, intype, myexecop, retval);
			if (ret == 0) {
				retval = (char*)"vmodel";
				px = states[i].trans[j].trantarget;
				iy = getfuncLoc(px);
				// cViewModel(output, funcs[iy].finmodel, retval);
				/*yazgetViews(funcs[iy].finmodel, retval);*/
				moveMmodel(myexecop, funcs[iy].finmodel, retval);
				if (strcmp(funcs[iy].fretmodel, rtype) == 0) {
					if (globalvar) fprintf(output, "    ");
					saveGlobal();
					fprintf(output, "    return %s(%s);\n", px, retval);
					fprintf(output, "%s", indentstr());
					fprintf(output, "    }\n");
				}
				else {
					// retval = (char*)"rmodel";
					// cViewModel(output, funcs[iy].fretmodel, retval);
					// yazgetViews(output, funcs[iy].fretmodel, retval);
					fprintf(output, "%s", indentstr());
					fprintf(output, "    %s = %s(%s);\n", retval, px, retval);
					mViewModel(rtype, funcs[iy].fretmodel, retval, currval);
					/*yazsaveViews(funcs[iy].fretmodel, retval);*/
					if (globalvar) fprintf(output, "    ");
					saveGlobal();
					fprintf(output, "%s", indentstr());
					fprintf(output, "    return %s;\n", currval);
					fprintf(output, "%s", indentstr());
					fprintf(output, "    }\n");
				}
			}
			retval = currval;
			rtype = currtype;
		}
	}
	for (j = 0; j < states[i].itran; j++) {
		if (strstr(states[i].trans[j].tranid, "Op.ERROR")) {
			currval = retval;
			currtype = rtype;
			ret = elselink(i, j, rtype, intype, retval);
			if (ret == 0) {
				retval = (char*)"vmodel";
				px = states[i].trans[j].trantarget;
				iy = getfuncLoc(px);
				// cViewModel(output, funcs[iy].fretmodel, retval);
				if (funcs[iy].fretmodel && strcmp(funcs[iy].fretmodel, rtype) == 0) {
					/*yazgetViews(funcs[iy].fretmodel, retval);*/
					if (globalvar) fprintf(output, "    ");
					saveGlobal();
					fprintf(output, "%s", indentstr());
					fprintf(output, "    return %s(%s);\n", px, retval);
					fprintf(output, "%s", indentstr());
					fprintf(output, "    }\n");
				}
				else {
					retval = (char*)"rmodel";
					// cViewModel(output, funcs[iy].fretmodel, retval);
					/*yazgetViews(funcs[iy].fretmodel, retval);*/
					fprintf(output, "%s", indentstr());
					fprintf(output, "    %s = %s(%s);\n", retval, px, currval);
					mViewModel(rtype, funcs[iy].fretmodel, retval, currval);
					if (globalvar) fprintf(output, "    ");
					saveGlobal();
					fprintf(output, "%s", indentstr());
					fprintf(output, "    return %s;\n", currval);
					fprintf(output, "%s", indentstr());
					fprintf(output, "    }\n");
				}
				ifset = 1;
			}
		}
	}
	return ifset;
}

char* sifirVarmi(char* s)
{
	char* p;
	char sbuf[200];
	p = strstr(s, ".0.");
	if (p) {
		*p = 0;
		p = p + 3;
		sprintf(sbuf, "%s.%s", s, p);
		p = (char*)calloc(1, strlen(sbuf) + 1);
		strcpy(p, sbuf);
		return p;
	}
	return s;
}

void operFunc(int i, char *rtype, char *intype)
{
	int j, k;
	int ifset, iik;
	char *myexecop = NULL;
	int  isetvals;
	char *setvals[SMAX];
	char buffer[400];
	char pbuf[400];
	char *p, *p1;
	char mymodel[300];
	char *myexecmon = NULL;
	char *retval = "model";

	p = modelBak(i);

	iik = vmodelBak(i);
	frtype = 5;
	for (j = 0; j < states[i].ientry; j++) {
		for (k = 0; k < states[i].entry[j].iexec; k++) {
			// exec host call
			myexecop = states[i].entry[j].eexec[k].execop;
			myexecmon = states[i].entry[j].eexec[k].execmon;
		}
		// setvalue
		isetvals = 0;
		mymodel[0] = 0;
		for (k = 0; k < states[i].entry[j].isetval; k++) {
			p1 = mcaRequestMi(states[i].entry[j].esetval[k].dataelm);
			if (p1) {
				strcpy(pbuf, p1);
				p1 = strstr(pbuf, "Fmt");
				if (p1) *p1 = 0;
				p1 = pbuf;
				if(mymodel[0] == 0)
					strcpy(mymodel, modelBak(i));
			}
			buffer[0] = 0;
			if (states[i].entry[j].esetval[k].defval[0] == '@') {
					sprintf(buffer, "model.%s =  model.%s;\n",
						states[i].entry[j].esetval[k].dataelm,
						sifirVarmi(states[i].entry[j].esetval[k].defval + 1));
			}
			else {
				sprintf(buffer, "%s = %s;\n",
				lookglobals(states[i].entry[j].esetval[k].dataelm),
				initVariables(states[i].entry[j].esetval[k].defval));
			}
			if (buffer[0]) {
				setvals[isetvals] = (char *)calloc(1, (int)strlen(buffer) + 1);
				strcpy(setvals[isetvals], buffer);
				isetvals++;
			}
		}
	}
	indents++;

	for (j = 0; j < isetvals; j++) {
		fprintf(output, "%s", indentstr());
		fprintf(output, "%s", setvals[j]);
	}

	fprintf(output, "%s", indentstr());
	fprintf(output, "bool retcode; \n");
	if (myexecop) {
		p = strstr(myexecop, "ClientOp");
		if (p) {
			*p = 0;
		}
		fprintf(output, "%s", indentstr());
		fprintf(output, "%sModel mmodel = new %sModel();\n", myexecop, myexecop);
		// eger vname[i].icol > 0 ek tanım yap <=========
		fprintf(output, "%s", indentstr());
		fprintf(output, "%sViewModelTo%s(mmodel, model);\n", vmodel[iik].sview, myexecop);
		fprintf(output, "%s", indentstr());
		fprintf(output, "// retcode = %s ile host call gerekli\n", myexecop);
		fprintf(output, "%s", indentstr());

		if (strstr(myexecmon, "true")) {
			fprintf(output, "retcode = %sMonetaryCall(mmodel);\n", myexecop);
		}
		else
			fprintf(output, "retcode = %sCall(mmodel);\n", myexecop);
		vmcaEkle(lastView, myexecop, 0);
	}
	if (strcmp(rtype, intype) == 0)
		ifset = returnCall(i, rtype, intype, myexecop, retval);
	else {
		retval = (char*)"vmodel";
		ifset = returnCall(i, rtype, intype, myexecop, retval);
	}
	if (ifset == 0) {
		saveGlobal();
		fprintf(output, "%s", indentstr());
		fprintf(output, "    return %s;\n", retval);
		fprintf(output, "%s", indentstr());
		fprintf(output, "}\n");
	}
	indents = 1;
	//fprintf(output, "%s", indentstr());
	//fprintf(output, "// sonucu retcode olarak saklanacak \n");
	//fprintf(output, "%s", indentstr());
	fprintf(output, "%s", indentstr());
	fprintf(output, "}\n");
	voidreturn = 0;
}
	

void conditionFunc(int i, char *rtype, char *intype)
{
	int j, k;
	int ilk = 1;
	char rbuf[200], lbuf[200];
	char *px, *pm;

	struct STATE *ip;
	struct ENTRY *ep;
	struct COMPCON *cp;
	struct LOGICAL *lp;
	int  first, opint = 0;
	int  fused = 0;
	int  setret = 0;
	int kk;
	is = -1;
	prevop[0][0] = 0;
	ip = &states[i];
	frtype = 5;
	indents++;
	for (j = 0; j < ip->ientry; j++) {
		ep = &ip->entry[j];
		for (k = 0; k < ep->icompcond; k++) {
			cp = &ep->ecompcon[k];
			for (kk = 0; kk < cp->ilogical; kk++) {
				lp = &cp->logical[kk];
				if ((lp->firstop && lp->firstop[0] == '@') || (lp->secondop && lp->secondop[0] == '@')) {
					getglobal();
					break;
				}
			}
		}
		for (k = 0; k < ep->icompcond; k++) {
			// char * onTrue;
			char* p, * p1, * opcode;
			cp = &ep->ecompcon[k];
			p = strstr(cp->onTrue, "changeState(");
			if (!p)
				p1 = cp->onTrue;
			else {
				p = p + 12;
				p1 = p;
				while (*p && *p != ')') p++;
				if (p) *p = 0;
			}
			if (p1) {
				prevop[0][0] = NULL;
				first = 0;
				for (kk = 0; kk < cp->ilogical; kk++) {
					lp = &cp->logical[kk];
					if (strcmp(lp->opname, "EQ") == 0)
						opcode = "==";
					else
						if (strcmp(lp->opname, "LE") == 0) {
							opcode = "<=";
							opint = 1;
						}
						else
							if (strcmp(lp->opname, "GE") == 0) {
								opcode = ">=";
								opint = 1;
							}
							else
								if (strcmp(lp->opname, "GT") == 0) {
									opcode = ">";
									opint = 1;
								}
								else
									if (strcmp(lp->opname, "LT") == 0) {
										opcode = "<";
										opint = 1;
									}
									else
										if (strcmp(lp->opname, "NEQ") == 0)
											opcode = "!=";
										else
											if (strcmp(lp->opname, "AND") == 0)
												opcode = "&&";
											else
												if (strcmp(lp->opname, "OR") == 0)
													opcode = "||";
												else
													opcode = lp->opname;
					if ((strcmp(opcode, "&&") == 0) && lp->firstop == NULL) {
						is++;
						strcpy(prevop[is], opcode);
						if (fused == 0) {
							first = 1;
							fused = 1;
						}
						continue;
					}
					if ((strcmp(opcode, "||") == 0) && lp->firstop == NULL) {
						is++;
						strcpy(prevop[is], opcode);
						if (fused == 0) {
							first = 1;
							fused = 1;
						}
						continue;
					}
					if (strcmp(lp->firstop, "1") != 0) {
						if (lp->firstop[0] == '@') {
							p = mcaArrMi(lp->firstop + 1);
							if (p) {
								px = mcaName(lp->firstop + 1);
								sprintf(lbuf, "%s", evaluateDefValue(CB, lp->firstop + 1));
							}
							else
								sprintf(lbuf, "%s", evaluateDefValue(CB, lp->firstop));
						}
						else
							strcpy(lbuf, lp->firstop);
						if (lp->secondop != NULL) {
							if (lp->secondop[0] == '@') {
								p = mcaArrMi(lp->secondop + 1);
								if (p) {
									px = mcaName(lp->secondop + 1);
									sprintf(rbuf, "%s", evaluateDefValue(CB, lp->secondop));
								}
								else
									sprintf(rbuf, "%s", evaluateDefValue(CB, lp->secondop));
							}
							else
								strcpy(rbuf, lp->secondop);
						}
						else rbuf[0] = 0;
						if (prevop[is][0] != NULL) {
							if (first > 0) {
								fprintf(output, "%s", indentstr());
								if (opint == 0) {
									fprintf(output, "if((%s %s %s) ",
										lbuf, opcode, initVariables(rbuf));
								}
								else {
									fprintf(output, "if((int.Parse(%s) %s %s) ",
										lbuf, opcode, rbuf);
								}
								first = 0;
								continue;
							}
							else {
								if (is >= 0) {
									fprintf(output, "%s ", prevop[is]);
									is--;
								}
								if (opint == 0) {
									fprintf(output, " (%s %s %s)",
										lbuf, opcode, initVariables(rbuf));
								}
								else {
									fprintf(output, " (int.Parse(%s) %s %s)",
										lbuf, opcode, rbuf);
								}
								if (is < 0) {
									fprintf(output, ") { \n");
									prevop[0][0] = NULL;
									is = -1;
								}
								else continue;
							}
						}
						else {
							fprintf(output, "%s", indentstr());
							if (opint == 0) {
								fprintf(output, "if(%s %s %s) {\n",
									lbuf, opcode, initVariables(rbuf));
							}
							else {
								fprintf(output, "if(int.Parse(%s) %s %s) {\n",
									lbuf, opcode, rbuf);
							}
						}
						indents++;
						saveGlobal();
						fprintf(output, "%s", indentstr());
						if (ekranmi(p1)) {
							if (voidreturn) {
								// yazsaveViews(output, intype, (char*)"model");
								fprintf(output, "return;\n");
							}
							else fprintf(output, "return model;\n"); // viewBak(p1));
						}
						else {
							int  iy, inn;
							iy = vmodeliiGet(p1);
							inn = vmodeliiGet(states[i].stateid);
							if (iy >= 0 && inn >= 0 && vmodel[iy].sview && vmodel[inn].sview) {
								if (strcmp(vmodel[iy].sview, vmodel[inn].sview) == 0) {
									fprintf(output, "%s", indentstr());
									fprintf(output, "%s(model);\n", p1);
									saveGlobal();
									fprintf(output, "%s", indentstr());
									if (voidreturn) {
										// yazsaveViews(output, intype, (char*)"model");
										fprintf(output, "return;\n");
									}
									else fprintf(output, "return model;\n");
								}
								else {
									fprintf(output, "%s", indentstr());
									/*yazgetViews(vmodel[iy].sview, (char*)"vmodel");*/

									fprintf(output, "%s", indentstr());
									fprintf(output, "    model = %s(model);\n", p1); //  states[i].trans[j].trantarget);
									/*yazsaveViews(vmodel[iy].sview, (char*)"vmodel");*/
									saveGlobal();
									//fprintf(output, "%s", indentstr());

									fprintf(output, "%s", indentstr());
									if (voidreturn) {
										// yazsaveViews(output, intype, (char*)"model");
										fprintf(output, "return;\n");
									}
									else fprintf(output, "return model;\n");
								}
							}
						}
						indents--;
						fprintf(output, "%s", indentstr());
						fprintf(output, "}\n");
						setret = 0;
					}
					else {
						int  iy, inn;
						char* px;
						//iy = vmodeliiGet(p1);
						//inn = vmodeliiGet(states[i].stateid);
						iy = baslik(p1);
						inn = baslik(states[i].stateid);
						if (iy >= 0 && inn >= 0 && funcs[iy].finmodel && funcs[inn].finmodel) {
							px = funcs[iy].fretmodel;
							fprintf(output, "\n%s", indentstr());
							fprintf(output, "else {\n");
							setret = 1;
							fprintf(output, "\n%s", indentstr());
							if (strcmp(funcs[iy].fretmodel, rtype) == 0) {
								saveGlobal();
								fprintf(output, "%s", indentstr());
								if (voidreturn) {
									fprintf(output, "%s(model);\n", p1);
									fprintf(output, "%s", indentstr());
									// yazsaveViews(output, intype, (char*)"model");
									fprintf(output, "return;\n");
								}
								else fprintf(output, "return %s(model);\n", p1);
							}
							else {
								fprintf(output, "%s(model);\n", p1);
								saveGlobal();
								fprintf(output, "%s", indentstr());
								if (voidreturn) {
									// yazsaveViews(output, intype, (char*)"model");
									fprintf(output, "return;\n");
								}
								else fprintf(output, "return model;\n");
							}
						}
						else {
							if(funcs[iy].fretmodel) {
								px = funcs[iy].fretmodel;
								if (strstr(px, "KriterView"))
									pm = tranname;
								else pm = (char*)"";
								/*yazgetViews(px, (char*)"model");*/
								fprintf(output, "%s", indentstr());
								if (strcmp(funcs[iy].finmodel, funcs[iy].fretmodel) == 0)
									fprintf(output, "    model = %s(model);\n", px);
								else fprintf(output, "    %s(model);\n", px);

								if (constVariables(px)) {
									//if (strstr(px, "KriterView"))
									//	pm = tranname;
									//else pm = (char*)"";
									/*yazsaveViews(px, (char*)"vmodel");*/
									//fprintf(output, "%s", indentstr());
									//fprintf(output, "   Flow.AddVariableToFlow<%s%sViewModel>(new KeyValue<string, %s%sViewModel>(%s, vmodel);\n",
									//	pm, px, pm, px, constVariables(px));
									/*saveGlobal();*/
									fprintf(output, "%s", indentstr());
									if (voidreturn) {
										// yazsaveViews(output, intype, (char*)"model");
										fprintf(output, "return;\n");
									}
									else fprintf(output, "return model;\n");
								}
								indents--;
								fprintf(output, "%s", indentstr());
								fprintf(output, "}\n");
								setret = 0;
							}
						}
					}
					if (setret) {
						fprintf(output, "%s", indentstr());
						fprintf(output, "}\n");
						indents--;
						fprintf(output, "%s", indentstr());
						fprintf(output, "}\n");
						setret = 0;
					}
				}
			}
			indents--;
		}
	}
	voidreturn = 0;
}

int myalpha(char *s)
{
	int  len = (int)strlen(s);
	int  i;
	for (i = 0; i < len; i++) {
		if (s[i] >= 'A' && s[i] <= 'Z')
			return 1;
		if (s[i] >= 'a' && s[i] <= 'z')
			return 1;
	}
	return 0;
}

void viewFunc(int i, char *vname, char *rtype, char *intype, char *myretval)
{
	int j, k, ii, iibak, modelvar, setremove = 0;
	int  ia;
	char *pp, *p, *px, *vm;
	char lbuf[200], rbuf[200];
	ia = 0;
	ii = vmodelBak(i);
	pp = modelBak(i);

	//indents = 2;
	for (j = 0; j < states[i].ientry; j++) {
		for (k = 0; k < states[i].entry[j].iopen; k++) {
			if (rtype && intype && strcmp(rtype, intype)) {
				vm = states[i].entry[j].sopen[k].viewname;
				/*yazgetViews(rtype, (char*)"vmodel");*/
				fprintf(output, "%s", indentstr());
			}
			else {
				if (myretval && strcmp(myretval, "vmodel")) {
					if (strcmp(intype, states[i].entry[j].sopen[k].viewname)) {
						/*yazgetViews(states[i].entry[j].sopen[k].viewname, (char *)"vmodel");*/
						fprintf(output, "%s", indentstr());
					}
				}
				vm = states[i].entry[j].sopen[k].viewname;
			}

			if (strcmp(rtype, intype)) {
				/*yazgetViews(rtype, (char*)"vmodel");*/
				fprintf(output, "%s", indentstr());
			}
/*			else {
				if (myretval && strcmp(myretval, "model") == 0) {
					yazgetViews(states[i].entry[j].sopen[k].viewname, (char*)"model");
				}
			}*/			
			//if (myretval && strcmp(myretval, "vmodel") == 0) {
			//	if (rtype && strcmp(rtype, "void")) {
			//		yazsaveViews(rtype, (char*)"vmodel");
			//	}
			//	else {
			//		yazsaveViews(vm, (char*)"vmodel");
			//	}
			//}
			iibak = i;
		}
		if (states[i].entry[j].isetval) {
			for (k = 0; k < states[i].entry[j].isetval; k++) {
				if (states[i].entry[j].esetval[k].dataelm[0] == '@') {
					modelvar = viewVarmi(states[i].entry[j].esetval[k].dataelm + 1) ? 1 : 0;
					if (modelvar) {
						p = viewArrMi(states[i].entry[j].esetval[k].dataelm + 1);
						if (p) {
							if (k == 0) {
								fprintf(output, "%s", indentstr());
								fprintf(output, "vmodel.%sList = new List<%sModel.%s>();\n",
									states[i].entry[j].esetval[k].dataelm + 1, p, states[i].entry[j].esetval[k].dataelm + 1);
								fprintf(output, "%s", indentstr());
								fprintf(output, "int  i;\n");
								fprintf(output, "%s", indentstr());
								fprintf(output, "for(i = 0; i<model.%sList.Count;i++) {\n",
									states[i].entry[j].esetval[k].dataelm + 1);
								ia = 1;
							}
							sprintf(lbuf, "vmodel.%sList[i].%s", p, buyukHarf(states[i].entry[j].esetval[k].dataelm + 1));
						}
						else sprintf(lbuf, "vmodel.%s", states[i].entry[j].esetval[k].dataelm + 1);
					}
					else sprintf(lbuf, "%s", states[i].entry[j].esetval[k].dataelm + 1);
				}
				else {
					modelvar = viewVarmi(states[i].entry[j].esetval[k].dataelm) ? 1 : 0;
					if (modelvar) {
						p = viewArrMi(states[i].entry[j].esetval[k].dataelm);
						if (p) {
							if (k == 0) {
								fprintf(output, "%s", indentstr());
								fprintf(output, "vmodel.%sList = new List<%sModel.%s>();\n",
									states[i].entry[j].esetval[k].dataelm, p, states[i].entry[j].esetval[k].dataelm);
								fprintf(output, "%s", indentstr());
								fprintf(output, "int  i;\n");
								fprintf(output, "%s", indentstr());
								fprintf(output, "for(i = 0; i<model.%sList.Count;i++) {\n",
									states[i].entry[j].esetval[k].dataelm);
								ia = 1;
							}
							sprintf(lbuf, "vmodel.%sList[i].%s", p, buyukHarf(states[i].entry[j].esetval[k].dataelm));
						}
						else sprintf(lbuf, "vmodel.%s", states[i].entry[j].esetval[k].dataelm);
					}
					sprintf(lbuf, "vmodel.%s", states[i].entry[j].esetval[k].dataelm);
				}
				if (states[i].entry[j].esetval[k].defval[0] == '@') {
					modelvar = viewVarmi(states[i].entry[j].esetval[k].defval+1) ? 1 : 0;
					if (modelvar)
							sprintf(rbuf, "model.%s", states[i].entry[j].esetval[k].defval + 1);
					else sprintf(rbuf, "%s", states[i].entry[j].esetval[k].defval + 1);
				}
				else {
					modelvar = viewVarmi(states[i].entry[j].esetval[k].defval) ? 1 : 0;
					if (modelvar) {
						p = mcaArrMi(states[i].entry[j].esetval[k].defval);
						if (p) {
							px = mcaName(states[i].entry[j].esetval[k].defval);
							if (k == 0) {
								fprintf(output, "%s", indentstr());
								fprintf(output, "int  i;\n");
								fprintf(output, "%s", indentstr());
								fprintf(output, "for(i = 0; i<model.%sProp.%s.Count;i++) {\n",
									px, p);
							}
							sprintf(rbuf, "model.%sProp.%s[i].%s", px, p, states[i].entry[j].esetval[k].defval);
						}
						else sprintf(rbuf, "model.%s", states[i].entry[j].esetval[k].defval);
					}
					else {
						px = initVariables(states[i].entry[j].esetval[k].defval);
						if (px)
							sprintf(rbuf, "%s", px);
						else
							if(isnumber(states[i].entry[j].esetval[k].defval) == 0)
								sprintf(rbuf, "%s", initVariables(states[i].entry[j].esetval[k].defval));
							else sprintf(rbuf, "%s", states[i].entry[j].esetval[k].defval);
					}
				}
				if (k + 1 < states[i].entry[j].isetval) {
					fprintf(output, "%s", indentstr());
					if (rbuf[0] == ' ' || rbuf[0] == 0 || myalpha(rbuf))
						if (initVariables(rbuf))
							fprintf(output, "%s = %s;\n", lookglobals(lbuf), initVariables(rbuf));
						else fprintf(output, "%s = %s;\n", lookglobals(lbuf), rbuf);
					else fprintf(output, "%s = %s;\n", lookglobals(lbuf), rbuf);
				}
			}
			if (ia) {
				fprintf(output, "%s", indentstr());
				fprintf(output, "}\n");
			}
			fprintf(output, "%s", indentstr());
			if(rbuf[0]== ' ' || rbuf[0] == 0 || myalpha(rbuf))
				if (initVariables(rbuf))
					fprintf(output, "%s = %s;\n", lookglobals(lbuf), initVariables(rbuf));
				else fprintf(output, "%s = %s;\n", lookglobals(lbuf), rbuf);
			else fprintf(output, "%s = %s;\n", lookglobals(lbuf), rbuf);
		}
	}
	for (j = 0; j < states[i].itran; j++) {
		if (strstr(states[i].trans[j].tranid, ".ERROR") == 0) {
			px = strstr(states[i].trans[j].tranid, "NavController.");
			if (px) {
				char *ps;
				px = px + 14;
				ps = strstr(px, ".");
				if (ps) *ps = 0;
				fprintf(output, "%s", indentstr());
				fprintf(output, "if(model.Actiontag == %s) ", initVariables(px));
			}
			if (ekranmi(states[i].trans[j].trantarget)) {
				fprintf(output, "%s", indentstr());
				if (ii >= 0) {
					if (voidreturn)
						fprintf(output, "return;\n");
					else {
						if (intype && strcmp(rtype, intype) == 0)
							fprintf(output, "return model;\n");
						else fprintf(output, "return vmodel;\n");
					}
				}
				else {
					if (voidreturn)
						fprintf(output, "return;\n");
					else {
						if (viewBak(states[i].trans[j].trantarget)) {
							if (intype && strcmp(intype, states[i].trans[j].trantarget) == 0) {
								fprintf(output, "return model;\n");
								ii = vmodelBak(i);
								mySaveStack(states[i].trans[j].trantarget, ii, vmodel[ii].sview, progname, tranname, garea);
							}
							else
								if (rtype && strcmp(rtype, states[i].trans[j].trantarget) == 0) {
									fprintf(output, "return vmodel;\n");
									ii = vmodelBak(i);
									mySaveStack(states[i].trans[j].trantarget, ii, vmodel[ii].sview, progname, tranname, garea);
								}
								else fprintf(output, "return null;\n");
						}
						else fprintf(output, "return null;\n");
					}
				}
			}
			else {
				int iy = baslik(states[i].trans[j].trantarget);
				if (voidreturn)
					fprintf(output, "{ return; }\n");
				else {
					if (funcs[iy].finmodel && strcmp(funcs[iy].finmodel, intype) == 0) {
						if (strcmp(funcs[iy].fretmodel, rtype) == 0) {
							fprintf(output, "{ return %s(model); } \n", states[i].trans[j].trantarget);
						}
						else {
							indents++;
							/*fprintf(output, "%s", indentstr());*/
							fprintf(output, "{ %s(model); \n", states[i].trans[j].trantarget);
							fprintf(output, "%s", indentstr());
							fprintf(output, "return model; }\n");
							indents--;
						}
					}
					else {
						fprintf(output, "{\n");
						indents++;
						if (funcs[iy].finmodel && strcmp(funcs[iy].finmodel, "void")) {
							/*yazgetViews(funcs[iy].finmodel, (char*)"vmodel");*/
							if (funcs[iy].fretmodel && strcmp(funcs[iy].fretmodel, rtype) == 0) {
								fprintf(output, "%s", indentstr());
								fprintf(output, "return %s(vmodel);\n", states[i].trans[j].trantarget);
								fprintf(output, "%s", indentstr());
								fprintf(output, "}\n");
							}
							else {
								fprintf(output, "%s", indentstr());
								fprintf(output, "%s(vmodel);\n", states[i].trans[j].trantarget);
								fprintf(output, "%s", indentstr());
								fprintf(output, "return model;\n");
								fprintf(output, "%s", indentstr());
								fprintf(output, "}\n");
							}
						}
						else {
							fprintf(output, "%s", indentstr());
							fprintf(output, "return %s(model);\n", states[i].trans[j].trantarget);
							fprintf(output, "%s", indentstr());
							fprintf(output, "}\n");
						}
						indents--;
					}
				}
				ii = vmodelBak(i);
				mySaveStack(states[i].trans[j].trantarget, ii, vmodel[ii].sview, progname, tranname, garea);
			}
		}
		else {
			if (strstr(states[i].trans[j].tranid, ".ERROR")) {
				pp = nextState((char *)".ERROR", &states[i]);
				if (setremove == 0) {
					fprintf(output, "%s", indentstr());
					fprintf(output, "vmodel.FunctionInfo.RemoveNextButton = true;\n");
					fprintf(output, "vmodel.FunctionInfo.FunctionButtons = new List<ActionButton>();\n");
					setremove = 1;
				}
				fprintf(output, "%s", indentstr());
				if (ekranmi(pp)) {
					fprintf(output, "vmodel.FunctionInfo.FunctionButtons.Add(%sGeneralHelper.CreateNextButton(%s, %s, %s, true));\n",
						garea, constVariables((char *)"Next"), constVariables(viewBak(pp)), constVariables(viewBak(pp)));
				}
				else {
					fprintf(output, "vmodel.FunctionInfo.FunctionButtons.Add(%sGeneralHelper.CreateNextButton(%s, %s, %s, true));\n",
						garea, constVariables((char *)"Next"), constVariables(pp), constVariables(pp)); // modelBak(i);
				}
			}
			else {
				p = strstr(states[i].trans[j].tranid, ".");
				if (p)
					p++;
				else p = states[i].trans[j].tranid;
				pp = strstr(p, ".");
				if (!pp) pp = p;
				else {
					*pp = 0;
					pp = p;
				}
				if (setremove == 0) {
					fprintf(output, "%s", indentstr());
					fprintf(output, "vmodel.FunctionInfo.FunctionButtons = new List<ActionButton>();\n");
					setremove = 1;
				}
				fprintf(output, "%s", indentstr());
				if (ekranmi(pp)) {
					fprintf(output, "vmodel.FunctionInfo.FunctionButtons.Add(%sGeneralHelper.CreateNextButton(%s, %s, %s, true));\n",
						garea, constVariables((char *)"Next"), constVariables(viewBak(pp)), constVariables(viewBak(pp)));
				}
				else {
					fprintf(output, "vmodel.FunctionInfo.FunctionButtons.Add(%sGeneralHelper.CreateNextButton(%s, %s, %s, true));\n",
						garea, constVariables((char *)"Next"), constVariables(pp), constVariables(pp)); // modelBak(i);
				}
			}
		}
	}
	fprintf(output, "%s", indentstr());
	if (ii >= 0) {
		if (voidreturn)
			fprintf(output, "return;\n");
		else if(myretval)
				fprintf(output, "return %s;\n", myretval);
			else fprintf(output, "return model;\n");
	}
	indents--;
	fprintf(output, "%s", indentstr());
	fprintf(output, "}\n");
	voidreturn = 0;
}

void flowFunc(int i, char *rtype, char *intype)
{
	int   j, iy;
	char* px;
	indents= 1;
	if (yazilanaekle(states[i].stateid)) return;
	if (baslikyaz(states[i].stateid) == 0) {
		if (states[i].itran >= 0) {
			for (j = 0; j < states[i].itran; j++) {
				if (strcmp(states[i].trans[j].tranid, "finalize.OK") == 0) {
					fprintf(output, "%s", indentstr());
					fprintf(output, "public void %s()\n", states[i].stateid);
					fprintf(output, "%s", indentstr());
					fprintf(output, "{\n");
					indents++;
					px = states[i].trans[j].trantarget;
					iy = getfuncLoc(px);
					if (iy >= 0) {
						fprintf(output, "%s", indentstr());
						fprintf(output, "%s();\n", px);
					}
					indents--;
					fprintf(output, "%s", indentstr());
					fprintf(output, "}\n");
					return;
				}
			}
		}
		fprintf(output, "%s", indentstr());
		fprintf(output, "public %sViewModel %s(%sModel model)\n",
			modelBak(i), states[i].stateid, modelBak(i));
		fprintf(output, "%s", indentstr());
		fprintf(output, "{\n");
	}

	for (j = 0; j < states[i].itran; j++) {
		// return finalize.OK
		indents++;
		fprintf(output, "%s", indentstr());
		if (strstr(states[i].trans[j].tranid, ".OK") ||
			strstr(states[i].trans[j].tranid, ".ENTER") ||
			strstr(states[i].trans[j].tranid, ".DEVAM") ||
			strstr(states[i].trans[j].tranid, ".TAMAM") ||
			strstr(states[i].trans[j].tranid, ".CLICK")) {
			char *ps, pbuf[100];
			fprintf(output, "%s", indentstr());
			ps = strstr(states[i].trans[j].tranid, ".");
			if (ps) {
				*ps = 0;
				ps++;
			}
			if (j) {
				fprintf(output, "else\n");
				fprintf(output, "%s", indentstr());
			}
			sprintf(pbuf, "%sConstants.%s", tranname, ps);
			if(constVariables(ps) && strcmp(constVariables(ps), pbuf) == 0)
				fprintf(output, "if(model.Actiontag == %s) ", initVariables(ps)); // states[i].trans[j].tranid);
			else fprintf(output, "if(model.actiontag == %sConstants.FlowTag.%s) ", tranname, ps); // states[i].trans[j].tranid);
			if (ekranmi(states[i].trans[j].trantarget)) {
				fprintf(output, "%s", indentstr());
				fprintf(output, "{\n");
			}
			else {
				fprintf(output, "%s", indentstr());
				fprintf(output, "{\n");
				fprintf(output, "%s", indentstr());
				fprintf(output, "%s(model);\n", states[i].trans[j].trantarget);
				saveGlobal();
				fprintf(output, "%s", indentstr());
				fprintf(output, "return model;\n");
				fprintf(output, "%s", indentstr());
				fprintf(output, "}\n");
			}
		}
		else {
			if (strstr(states[i].trans[j].tranid, ".ERROR")) {
				char pbuf[100];
				px = strstr(states[i].trans[j].tranid, ".ERROR");
				fprintf(output, "%s", indentstr());
				if (j) {
					fprintf(output, "else\n");
					fprintf(output, "%s", indentstr());
				}
				sprintf(pbuf, "%sConstants.%s", tranname, px);
				if (constVariables(px) && strcmp(constVariables(px), pbuf) == 0)
					fprintf(output, "if(model.Actiontag == %s) ", initVariables(px));
				else fprintf(output, "if(model.Actiontag == %sConstants.FlowTag.%s) ", tranname, px);
				if (ekranmi(states[i].trans[j].trantarget)) {
					fprintf(output, "%s", indentstr());
					fprintf(output, "{\n");
					saveGlobal();
					fprintf(output, "%s", indentstr());
					fprintf(output, "    return model;\n");
					fprintf(output, "%s", indentstr());
					fprintf(output, "}\n");
				}
				else {
					fprintf(output, "%s", indentstr());
					fprintf(output, "{\n");
					fprintf(output, "%s", indentstr());
					fprintf(output, "    %s(model);\n", states[i].trans[j].trantarget);
					saveGlobal();
					fprintf(output, "%s", indentstr());
					fprintf(output, "    return model;\n");
					fprintf(output, "%s", indentstr());
					fprintf(output, "}\n");
				}
			}
			else {
				fprintf(output, "%s", indentstr());
				if (j) {
					fprintf(output, "else\n");
					fprintf(output, "%s", indentstr());
				}
				if (ekranmi(states[i].trans[j].trantarget)) {
					fprintf(output, "%s", indentstr());
					fprintf(output, "{\n");
					saveGlobal();
					fprintf(output, "%s", indentstr());
					fprintf(output, "    return model;\n");
					fprintf(output, "%s", indentstr());
					fprintf(output, "}\n");
				}
				else {
					fprintf(output, "%s", indentstr());
					fprintf(output, "{\n");
					fprintf(output, "%s", indentstr());
					fprintf(output, "    %s(model);\n", states[i].trans[j].trantarget);
					saveGlobal();
					fprintf(output, "%s", indentstr());
					fprintf(output, "    return model;\n");
					fprintf(output, "%s", indentstr());
					fprintf(output, "}\n");

				}
			}
		}
		indents--;
	}
	saveGlobal();
	fprintf(output, "%s", indentstr());
	fprintf(output, "return null;\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "}\n");
	indents--;
}

int flowtarget(char *p)
{
	int  i, j;
	for (i = 0; i < iflowcall; i++) {
		if (flowcall[i].jcount > 0) {
			for (j = 0; j < flowcall[i].jcount; j++) {
				if (strcmp(flowcall[i].fcall[j], p) == 0)
					return i;
			}
		}
	}
	return -1;
}

//void writeFunctions(int tip, char *prog, char *trn, char *areaName, char *retval)
//{
//	int  i, ii, j, kopen;
//	char *px, *returntype, *inmodel;
//	globalvar = 0;
//	retval = 0;
//	lastView[0] = 0;
//for (i = 0; i < istate; i++) {
//	if (tip == 1 && strstr(states[i].statetype, "view")) {
//		kopen = openVarmi(i);
//		if (kopen >= 0) {
//			for (j = 0; j < states[i].entry[kopen].iopen; j++) {
//				if (states[i].entry[kopen].sopen[j].viewname) {
//					strcpy(lastView, states[i].entry[kopen].sopen[j].viewname);
//					break;
//				}
//				else {
//					if (states[i].entry[kopen].sopen[j].viewsrc) {
//						px = strrchr(states[i].entry[kopen].sopen[j].viewsrc, '.');
//						if (px) px++;
//						else px = states[i].entry[kopen].sopen[j].viewsrc;
//						strcpy(lastView, px);
//						break;
//					}
//				}
//			}
//		}
//
//		ii = getfuncLoc(states[i].stateid);
//		returntype = funcs[ii].fretmodel;
//		if (strlen(lastView) < 1)
//			strcpy(lastView, funcs[ii].finmodel);
//		viewFunc(i, lastView, returntype, lastView, retval);
//	}
//	ii = getfuncLoc(states[i].stateid);
//	returntype = funcs[ii].fretmodel;
//	inmodel = funcs[ii].finmodel;
//	if (tip == 1 && strstr(states[i].statetype, "action"))
//		setValFunc(i, returntype, inmodel);
//	if (tip == 1 && strstr(states[i].statetype, "operation"))
//		operFunc(i, returntype, inmodel);
//	if (tip == 1 && strstr(states[i].statetype, "condition"))
//		conditionFunc(i, returntype, inmodel);
//	if (tip == 1 && strstr(states[i].statetype, "flow"))
//		flowFunc(i, returntype, inmodel);
//}
//}

void writeFunc(int ii, char* prog, char* trn, char* areaName)
{
	char* px;
	char* returntype = 0;
	char* inmodel = 0;
	int  i = vmodel[ii].is;
	char* returns = 0;
	char* retval = 0;
	int  kopen, j;
	struct NODE* pnode;

	if (strcmp(states[i].statetype, "action") != 0) {
		ii = getfuncLoc(states[i].stateid);
		returntype = funcs[ii].fretmodel;
		inmodel = funcs[ii].finmodel;
		pnode = nodeBak(states[i].stateid);
		if (pnode) {
			returntype = (pnode->nretmodel == NULL) ? "void" : pnode->nretmodel;
			inmodel = (pnode->ninmodel == NULL) ? "void" : pnode->ninmodel;
		}
		returns = defineFunc(returntype, i, states[i].stateid, inmodel, &retval);
	}
	if (strstr(states[i].statetype, "view")) {
		kopen = openVarmi(i);
		if (kopen >= 0) {
			lastView[0] = 0;
			for (j = 0; j < states[i].entry[kopen].iopen; j++) {
				if (states[i].entry[kopen].sopen[j].viewname) {
					strcpy(lastView, states[i].entry[kopen].sopen[j].viewname);
					break;
				}
				else {
					if (states[i].entry[kopen].sopen[j].viewsrc) {
						px = strrchr(states[i].entry[kopen].sopen[j].viewsrc, '.');
						if (px) px++;
						else px = states[i].entry[kopen].sopen[j].viewsrc;
						strcpy(lastView, px);
						break;
					}
				}
			}
		}
		ii = getfuncLoc(states[i].stateid);
		returntype = funcs[ii].fretmodel;
		inmodel = funcs[ii].finmodel;
		viewFunc(i, lastView, returntype, inmodel, retval);
	}
	else {
		ii = getfuncLoc(states[i].stateid);
		returntype = funcs[ii].fretmodel;
		inmodel = funcs[ii].finmodel;
		if (strstr(states[i].statetype, "action"))
			setValFunc(i, returntype, inmodel);
		if (strstr(states[i].statetype, "operation"))
			operFunc(i, returntype, inmodel);
		if (strstr(states[i].statetype, "condition"))
			conditionFunc(i, returntype, inmodel);
		if (strstr(states[i].statetype, "flow"))
			flowFunc(i, returntype, inmodel);
	}
}

int buviewVarmi(char* p)
{
	int i;
	for(i = 0; i < iviews; i++) {
		if (strcmp(fviews[i].v1, p) == 0)
			return 1;
	}
	return 0;
}

void viewsOku(char *fdir, char *prog, char *trn)
{
	int  ix;
	char fpref[200], vfile[300];
	char *p, *p1;
	// read flows.preference file
	FILE *ff;
	strcpy(fpref, fdir);
	strcat(fpref, PREFS);
	strcat(fpref, trn);
	strcat(fpref, "\\");
	strcat(fpref, trn);
	strcpy(vfile, fpref);
	strcat(fpref, prog);
	strcat(fpref, "flow.preference");
	ff = fopen(fpref, "r");
	if (ff) {
		while (fgets(fbuf, FMAX, ff)) {
			rmnl(fbuf);
			if (strstr(fbuf, "view.")) {
				p = strstr(fbuf, "view.");
				p1 = p + 5;
				p = strstr(p1, "=");
				if (p) {
					ix = iviews;
					*p = 0;
					p++;
					strcpy(fviews[ix].v1, buyukHarf(p1));
					strcpy(fviews[ix].v2, buyukHarf(p));
					iviews++;
					fviews[iviews].v1[0] = 0;
				}
			}
		}
		fclose(ff);
	}


	strcat(vfile, ".files");
	ff = fopen(vfile, "r");
	if (ff) {
		while (fgets(fbuf, FMAX, ff)) {
			rmnl(fbuf);
			if (strstr(fbuf, "VIEW ")) {
				p = strstr(fbuf, "VIEW ");
				if (p) {
					p = p + 5;
					p1 = strstr(p, ".file");
					if (p1) *p1 = 0;
					if (buviewVarmi(p) == 0) {
						ix = iviews;
						strcpy(fviews[ix].v1, buyukHarf(p + 4));
						strcpy(fviews[ix].v2, buyukHarf(p + 4));
						iviews++;
						fviews[iviews].v1[0] = 0;
					}
				}
			}
		}
		fclose(ff);
	}
}

int  yazilanaekle(char *ps)
{
	int  i;
	if (ps == NULL) return 1;
	if (strstr(buyukHarf(ps), "Final")) return 1;
	if (iyazilan == 0) {
		i = iyazilan;
		yazilan[i] = (char*)calloc(1, strlen(ps) + 1);
		strcpy(yazilan[i], "Vcontroller");
		iyazilan++;
	}
	for (i = 0; i < iyazilan; i++) {
		if (strcmp(yazilan[i], ps) == 0) return 1;
	}
	i = iyazilan;
	yazilan[i] = (char *)calloc(1, strlen(ps) + 1);
	strcpy(yazilan[i], buyukHarf(ps));
	iyazilan++;
	return 0;
}

char *getErrormsg(char *target)
{
	int j;
	int ii = vmodeliiBak(target);
	if (ii < 0) return 0;
	int i = vmodel[ii].is;
	if (states[i].ientry > 0) {
		for (j = 0; j < states[i].ientry; j++)
			if (states[i].entry[j].ishowmsg > 0)
				return buyukHarf(states[i].stateid);
	}
	if (strstr(vmodel[ii].stranid[j], "ERROR"))
		return getErrormsg(vmodel[ii].sid);
	return 0;
}


char* voidHeader(int iaa, char* r, char* f, char* a, char* sretval)
{
	char* pm, * pmr;
	r = buyukHarf(r);
	a = buyukHarf(a);
	f = buyukHarf(f);
	if (controllervarmi(f)) {
		if (a) {
			if (strstr(a, "KriterView"))
				pm = tranname;
			else pm = (char*)"";
			if (strstr(r, "KriterView"))
				pmr = tranname;
			else pmr = (char*)"";
			if (iaa >= 0 && states[iaa].isref == 1) {
				if (strcmp(r, "void") == 0) {
					voidreturn = 1;
					fprintf(output, "public void %s ", f);
				}
				else fprintf(output, "public %s%sViewModel %s(", pm, r, f);
				if (strcmp(a, "void") == 0) {
					fprintf(output, ")\n");
					voidreturn = 1;
				}
				else fprintf(output, "%s%sViewModel vmodel)\n", pm, a);
				sretval = (char*)"vmodel";
			}
			else {
				if (strcmp(r, "void") == 0) {
					fprintf(output, "public void %s ", f);
					voidreturn = 1;
				}
				else fprintf(output, "public %s%sViewModel %s(", pm, r, f);
				if (strcmp(a, "void") == 0)
					fprintf(output, ")\n");
				else fprintf(output, "%s%sViewModel vmodel)\n", pm, a);
				sretval = (char*)"vmodel";
			}
		}
		else {
			sretval = (char*)"";
			if (r) {
				if (strstr(r, "KriterView"))
					pmr = tranname;
				else pmr = (char*)"";
				fprintf(output, "public %s%sViewModel %s()\n", pmr, r, f);
				sretval = (char*)"void";
			}
			else {
				fprintf(output, "public void %s()\n", f);
				sretval = (char*)"void";
				voidreturn = 1;
			}
		}
	}
	else {
		if (strstr(a, "KriterView"))
			pm = tranname;
		else pm = (char*)"";
		if (strstr(r, "KriterView"))
			pmr = tranname;
		else pmr = (char*)"";
		if (iaa >= 0 && states[iaa].isref == 1) {
			if (strcmp(r, "void") == 0) {
				fprintf(output, "public void %s ", f);
				voidreturn = 1;
			}
			else fprintf(output, "public %s%sViewModel %s", pm, r, f);
			if (strcmp(a, "void") == 0) {
				fprintf(output, "()\n");
				sretval = (char*)"void";
			}
			else {
				fprintf(output, "(%s%sViewModel model)\n", pm, a);
				sretval = (char*)"model";
			}
		}
		else {
			if (strcmp(r, "void") == 0) {
				fprintf(output, "public void %s ", f);
				voidreturn = 1;
			}
			else fprintf(output, "public %s%sViewModel %s", pmr, r, f);
			if (strcmp(a, "void") == 0) {
				fprintf(output, "()\n");
				sretval = (char*)"void";
			}
			else {
				fprintf(output, "(%s%sViewModel model)\n", pmr, a);
				sretval = (char*)"model";
			}
		}
	}
	// if (strcmp(sretval, "void") == 0) voidreturn = 1;
	return sretval;
}

#ifdef HATA
char* voidHeader(FILE* out, int iaa, char* r, char* f, char* a, char* sretval)
{
	char* pm, * pmr;
	if (controllervarmif) {
		if a {
			if (strstr(a, "KriterView"))
				pm = tranname;
			else pm = (char*)"";
			if (strstr(r, "KriterView"))
				pmr = tranname;
			else pmr = (char*)"";
			if (iaa >= 0 && states[iaa].isref == 1) {
				if (strcmp(r, "void") == 0) {
					voidreturn = 1;
					fprintf(output, "public void %s ", f);
				}
				else fprintf(output, "public %s%sViewModel %s(", pm, r, f);
				if (strcmp(a, "void") == 0) {
					fprintf(output, ")\n");
					voidreturn = 1;
				}
				else fprintf(output, "%s%sViewModel vmodel)\n", pm, a);
				sretval = (char*)"vmodel";
			}
			else {
				if (strcmp(r, "void") == 0) {
					fprintf(output, "public void %s ", f);
					voidreturn = 1;
				}
				else fprintf(output, "public %s%sViewModel %s(", pm, r, f);
				if (strcmp(a, "void") == 0)
					fprintf(output, ")\n");
				else fprintf(output, "%s%sViewModel vmodel)\n", pm, a);
				sretval = (char*)"vmodel";
			}
		}
		else {
			sretval = (char*)"";
			if r {
				if (strstr(r, "KriterView"))
					pmr = tranname;
				else pmr = (char*)"";
				fprintf(output, "public %s%sViewModel %s()\n", pmr, r, f);
				sretval = (char*)"void";
			}
			else {
				fprintf(output, "public void %s()\n", f);
				sretval = (char*)"void";
				voidreturn = 1;
			}
		}
	}
	else {
		if (strstr(a, "KriterView"))
			pm = tranname;
		else pm = (char*)"";
		if (strstr(r, "KriterView"))
			pmr = tranname;
		else pmr = (char*)"";
		if (iaa >= 0 && states[iaa].isref == 1) {
			if (strcmp(r, "void") == 0) {
				fprintf(output, "public void %s ", f);
				voidreturn = 1;
			}
			else fprintf(output, "public %s%sViewModel %s", pm, r, f);
			if (strcmp(a, "void") == 0) {
				fprintf(output, "()\n");
				sretval = (char*)"void";
			}
			else {
				fprintf(output, "(%s%sViewModel model)\n", pm, a);
				sretval = (char*)"model";
			}
		}
		else {
			if (strcmp(r, "void") == 0) {
				fprintf(output, "public void %s ", f);
				voidreturn = 1;
			}
			else fprintf(output, "public %s%sViewModel %s", pmr, r, f);
			if (strcmp(a, "void") == 0) {
				fprintf(output, "()\n");
				sretval = (char*)"void";
			}
			else {
				fprintf(output, "(%s%sViewModel model)\n", pmr, a);
				sretval = (char*)"model";
			}
		}
	}
	// if (strcmp(sretval, "void") == 0) voidreturn = 1;
	return sretval;
}
#endif

char* digerHeader(int ii, int strval, int say, char* r, char* f, char* a, char* sretval)
{
	char* pm, * pmr;
	int  ia, iaa;
	int  j, ik;
	r = buyukHarf(r);
	f = buyukHarf(f);
	a = buyukHarf(a);
	if (a && strstr(a, "KriterView"))
		pm = tranname;
	else pm = (char*)"";
	if (r && strstr(r, "KriterView"))
		pmr = tranname;
	else pmr = (char*)"";
	//if (strstr(f, "finalize"))
	//	fprintf(stderr, "burada\n");
	if (say > 0 && say != states[ii].isref) {
		fprintf(output, "%s", indentstr());
		fprintf(output, "//TODO: burada farklı return model isteyen fonksiyonlar var\n");
		fprintf(output, "%s", indentstr());
		if (strval) {
			if (r && strcmp(r, "void") == 0) {
				fprintf(output, "public void %s (string strmodel)\n", f);
				voidreturn = 1;
			}
			else fprintf(output, "public %s%sViewModel %s(string strmodel)\n", pmr, r, f);
			sretval = (char*)"string";
		}
		else {
			if (controllervarmi(f)) {
				if (r && strcmp(r, "void") == 0) {
					fprintf(output, "public void %s()\n", f);
					voidreturn = 1;
				}
				else fprintf(output, "public %s%sViewModel %s()\n", pmr, r, f);
				sretval = (char*)"void";
			}
			else {
				if (r && strcmp(r, "void") == 0)
					fprintf(output, "public %s %s(%s%sViewModel model))\n", r, f, pm, a);
				else fprintf(output, "public %s%sViewModel %s(%s%sViewModel model)\n", pm, a, f, pm, a);
				sretval = (char*)"model";
			}
		}
	}
	else
		if (states[ii].isref == 1 && say == 0)
		{
			fprintf(output, "%s", indentstr());
			if (strval)
			{
				int ixx;
				char* pp = vmodelpBak(states[ii].staterefs[0]);
				ixx = vmodeliiGet(states[ii].staterefs[0]);
				if (strstr(pp, "KriterView"))
					pm = tranname;
				else pm = (char*)"";
				if (pp && strcmp(vmodel[ixx].ftype, "void") == 0) {
					fprintf(output, "public %s %s(string strmodel)\n", pp, f);
					voidreturn = 1;
				}
				else fprintf(output, "public %s%sViewModel %s(string strmodel)\n", pm, (pp), f);
				sretval = (char*)"string";
			}
			else
				if (controllervarmi(f)) {
					if (strstr(f, "KriterView"))
						pm = tranname;
					else pm = (char*)"";
					if (r && strcmp(r, "void") == 0) {
						fprintf(output, "public %s %s();\n", r, f);
						voidreturn = 1;
					}
					else fprintf(output, "public %s%sViewModel %s();\n", pm, r, f);
					sretval = (char*)"void";
				}
				else {
					int ixx, iy;
					char* pp = vmodelpBak(states[ii].staterefs[0]);
					ia = vmodeliiGet(a);
					if (ia >= 0) iaa = vmodel[ia].is;
					else iaa = -1;
					ixx = vmodeliiGet(states[ii].staterefs[0]);
					iy = vmodel[ixx].is;
					ixx = vmodeliiGet(states[ii].staterefs[0]);
					if (pp && strstr(pp, "KriterView")) {
						if (strstr(pp, "KriterView"))
							if (a && strstr(a, "KriterView"))
								if (a && pp && strcmp(pp, a) == 0)
									fprintf(output, "public %s%sViewModel %s(%s%sViewModel model)\n",
										tranname, (pp), f, tranname, a);
								else
									if (iaa >= 0 && states[iaa].isref == 1)
										fprintf(output, "public %s%sViewModel %s(%s%sViewModel model)\n",
											tranname, a, f, tranname, a);
									else
										fprintf(output, "public %s%sViewModel %s(%s%sViewModel model)\n",
											tranname, (pp), f, tranname, a);
							else
								if (a && strcmp(pp, a) == 0)
									fprintf(output, "public %s%sViewModel %s(%sViewModel model)\n", tranname, (pp), f, a);
								else
									if (iaa >= 0 && states[iaa].isref == 1)
										fprintf(output, "public %s%sViewModel %s(%sViewModel model)\n", tranname, a, f, a);
									else
										fprintf(output, "public %s%sViewModel %s(%sViewModel model)\n", tranname, pp, f, a);

					}
					else {
						if (iaa >= 0 && states[iaa].isref == 1)
							fprintf(output, "public %sViewModel %s(%sViewModel model)\n", a, f, a);
						else
							if (pp == NULL && (vmodel[ixx].ftype == NULL || strcmp(vmodel[ixx].ftype, "void")))
								fprintf(output, "public %sViewModel %s(%sViewModel model)\n", r, f, a);
							else fprintf(output, "public %sViewModel %s(%sViewModel model)\n", pp, f, a);
					}
					sretval = (char*)"model";
				}
			sretval = vmodelpBak(states[ii].staterefs[0]);
			if (sretval && r && strcmp(sretval, r))
				sretval = (char*)"vmodel";
			else sretval = (char*)"model";
		}
		else {
			ik = 1;
			for (j = 0; j < states[ii].isref; j++) {
				if (r && strcmp(vmodelpBak(states[ii].staterefs[j]), r)) {
					if (ik) {
						fprintf(output, "%s", indentstr());
						fprintf(output, "// TODO: Bu fonksiyondan donus asagdakilerden biri olabilir\n");
						ik = 0;
					}
					fprintf(output, "%s", indentstr());
					fprintf(output, "//    %s\n", vmodelpBak(states[ii].staterefs[j]));
				}
			}
			baslikyaz(f);
			fprintf(output, "%s", indentstr());
			if (strval) {
				int iy = vmodeliiBak(a);
				int ixx = vmodel[iy].is;
				if (states[ixx].isref == 1)
					fprintf(output, "public %sViewModel %s(%sViewModel model)\n", a, f, a);
				else
					if (r && strstr(r, "KriterView"))
						fprintf(output, "public %s%sViewModel %s(%sViewModel model)\n", tranname, r, f, a);
					else fprintf(output, "public %sViewModel %s(%sViewModel model)\n", r, f, a);
				sretval = (char*)"model";
			}
			else
				if (controllervarmi(f)) {
					if (r && strstr(r, "KriterView"))
						fprintf(output, "public %s%sViewModel %s()\n", tranname, r, f);
					else fprintf(output, "public %sViewModel %s()\n", r, f);
					sretval = 0;
				}
				else {
					int  iy = vmodeliiBak(a);
					int  ixx = vmodel[iy].is;
					if (states[ixx].isref == 1) {
						if (a && strstr(a, "KriterView"))
							fprintf(output, "public %s%sViewModel %s(%s%sViewModel model)\n", tranname, a, f, tranname, a);
						else fprintf(output, "public %sViewModel %s(%sViewModel model)\n", a, f, a);
					}
					if (r && strstr(r, "KriterView")) {
						if (a && strstr(a, "KriterView"))
							fprintf(output, "public %s%sViewModel %s(%s%sViewModel model)\n", tranname, r, f, tranname, a);
						else fprintf(output, "public %sViewModel %s(%sViewModel model)\n", r, f, a);
					}
					else fprintf(output, "public %sViewModel %s(%sViewModel model)\n", r, f, a);
					sretval = (char*)"model";
				}
		}
	return sretval;
}

char* findaHeader(char* r, char* f, char* a, char* sretval)
{
	int  iy = stateVarmi(a);
	int ixx = vmodelBak(iy);
	fprintf(output, "%s", indentstr());
	if (r && iy >= 0) {
		if (states[ixx].isref == 1)
			if (strstr(a, "KriterView"))
				fprintf(output, "public %s%sViewModel %s(%s%sViewModel model)\n", tranname, a, f, tranname, a);
			else fprintf(output, "public %sViewModel %s(%sViewModel model)\n", a, f, a);
		else
			if (strstr(r, "KriterView")) {
				if (a)
					if (strstr(a, "KriterView"))
						fprintf(output, "public %s%sViewModel %s(%s%sViewModel model)\n", tranname, r, f, tranname, a);
					else fprintf(output, "public %sViewModel %s(%sViewModel model)\n", r, f, a);
				else fprintf(output, "public %s%sViewModel %s()\n", tranname, r, f);
			}
			else
				if (a)
					fprintf(output, "public %sViewModel %s(%sViewModel model)\n", r, f, a);
				else fprintf(output, "public %sViewModel %s()\n", r, f);
		sretval = (char*)"model";
	}
	else {
		sretval = (char*)"model";
		if (strstr(a, "KriterView"))
			if (a)
				fprintf(output, "public %s%sViewModel %s(%s%sViewModel model)\n", tranname, a, f, tranname, a);
			else {
				fprintf(output, "public void %s()\n", f);
				sretval = (char*)"void";
				voidreturn = 1;
			}
		else
			if (a)
				fprintf(output, "public %sViewModel %s(%sViewModel model)\n", a, f, a);
			else {
				fprintf(output, "public void %s()\n", f);
				sretval = (char*)"void";
				voidreturn = 1;
			}
	}
	return sretval;
}

char* defineFunc(char* r, int ii, char* f, char* a, char** myretval)
{
	int  j, ix, iy, say = 0;
	int  ia;
	char* sretval = (char*)"model";
	int  strval;
	char* rtype, * intype;
	struct NODE* pnode;
	indents = 1;
	voidreturn = 0;
	if (ii >= 0) {
		strval = stringmi(ii);
		for (j = 0; j < states[ii].isref; j++) {
			ix = getfuncLoc(states[ii].staterefs[j]);
			rtype = funcs[ix].fretmodel;
			if (strcmp(rtype, "void") == 0) {
				if (strcmp(rtype, r)) {
					funcs[ix].fretmodel = r;
					rtype = r;
				}
			}
			else if (!rtype) rtype = r;
			intype = funcs[ix].finmodel;
			if (strcmp(intype, "void") == 0) {
				if (strcmp(intype, a)) {
					funcs[ix].finmodel = a;
					intype = a;
				}
			}
			else if (!intype) intype = a;
			if (r && rtype && strcmp(rtype, r) == 0)
				say++;
		}
		f = myReplace(f, ' ', '_');
		ia = vmodelBak(ii);
		if (ia >= 0) {
			pnode = nodeBak(f);
			if (pnode) {
				r = (pnode->nretmodel == NULL) ? "void" : pnode->nretmodel;
				a = (pnode->ninmodel == NULL) ? "void" : pnode->ninmodel;
			}
			if (say == states[ii].isref) {
				if (strval) {
					sretval = stringHeader(ia, r, f, sretval);
				}
				else {
					if (vmodel[ia].sview && strcmp(vmodel[ia].sview, "void")) {
						sretval = voidHeader(ii, r, f, a, sretval);
					}
					else {
						char* pmr, * pm;
						if (r && strstr(r, "Kriter"))
							pmr = tranname;
						else pmr = (char*)"";
						if (a && strstr(a, "Kriter"))
							pm = tranname;
						else pm = (char*)"";
						if (r && strcmp(r, "void")) {
							fprintf(output, "public %s%sViewModel %s(", pmr, r, f);
						}
						else {
							fprintf(output, "public void %s(", f);
							voidreturn = 1;
						}
						if (a && strcmp(a, "void")) {
							fprintf(output, "%s%sViewModel model)\n", pm, a);
						}
						else {
							fprintf(output, ")\n");
						}
					}
				}
			}
			else {
				iy = stateVarmi(f);
				ia = vmodelBak(ii);
				if (ia >= 0) {
					sretval = digerHeader(ii, strval, say, r, f, a, sretval);
				}
			}
		}
	}
	else {
		pnode = nodeBak(f);
		if (pnode) {
			r = (pnode->nretmodel == NULL) ? "void" : pnode->nretmodel;
			a = (pnode->ninmodel == NULL) ? "void" : pnode->ninmodel;
		}
		sretval = findaHeader(r, f, a, sretval);
	}
	fprintf(output, "%s", indentstr());
	fprintf(output, "{\n");
	frtype = 2;
	indents++;
	if (globalvar == 0) {
		fprintf(output, "%s", indentstr());
		fprintf(output, "global = FillGlobals(global);\n");
		globalvar = 1;
	}
	if (ii >= 0) {
		if (strcmp(states[ii].statetype, "final") == 0) {
			fprintf(output, "%s", indentstr());
			if (voidreturn)
				fprintf(output, "return;\n");
			else fprintf(output, "return null;\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "}\n");
		}
		if ((strstr(states[ii].stateid, "final") || strstr(states[ii].stateid, "Final")) && 
			strcmp(states[ii].statetype, "flow") == 0) {
			if (yazilanaekle(states[ii].stateid)) {
				if (states[ii].itran > 0) {
					int  iyy;
					// states[ii].trans[0].trantarget
					iyy = getfuncLoc(states[ii].trans[0].trantarget);
					if (iyy >= 0) {
						fprintf(output, "%s", indentstr());
						fprintf(output, "%s(%s);\n", states[ii].trans[0].trantarget, sretval);
					}
					else {
						fprintf(output, "%s", indentstr());
						fprintf(output, "%s();\n", states[ii].trans[0].trantarget);
					}
					fprintf(output, "%s", indentstr());
					fprintf(output, "return null;\n");
					fprintf(output, "%s", indentstr());
					fprintf(output, "}\n");
				}
				else {
					fprintf(output, "%s", indentstr());
					if (voidreturn)
						fprintf(output, "return;\n");
					else fprintf(output, "return null;\n");
					fprintf(output, "%s", indentstr());
					fprintf(output, "}\n");
				}
			}
		}
	}
	*myretval = sretval;
	return r;
}

void writeReturn()
{
	indents++;
	saveGlobal();
	fprintf(output, "%s", indentstr());
	if (voidreturn)
		fprintf(output, "return;\n");
	else fprintf(output, "return model;\n");
	indents--;
}

void endfunc()
{
	indents--;
	fprintf(output, "%s", indentstr());
	fprintf(output, "}\n");
	globalvar = 0;
}

void writeError(char *inmodel, char *msg)
{
	fprintf(output, "%s", indentstr());
	fprintf(output, "model.OperationResult.IsRequestSuccessful = false;\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "model.OperationResult.Message = %s;\n", initVariables(msg));
}

void mySaveStack(char *f, int ix, char *ssv, char *pg, char *tr, char *a)
{
	int  i;
	if (f == NULL) f = " ";
	if (ssv == NULL) ssv = " ";
	for (i = 0; i < isavestack; i++) {
		if (strcmp(saveStack[i].fn, f) == 0)
			return;
	}
	/*fprintf(output, "==%s\n", f);*/
	saveStack[i].fn = (char *)calloc(1, strlen(f) + 1);
	strcpy(saveStack[i].fn, buyukHarf(f));
	saveStack[i].sv = (char *)calloc(1, strlen(ssv) + 1);
	strcpy(saveStack[i].sv, buyukHarf(ssv));
	saveStack[i].prog = (char *)calloc(1, strlen(pg) + 1);
	strcpy(saveStack[i].prog, buyukHarf(pg));
	saveStack[i].trn = (char *)calloc(1, strlen(tr) + 1);
	strcpy(saveStack[i].trn, buyukHarf(tr));
	saveStack[i].area = (char *)calloc(1, strlen(a) + 1);
	strcpy(saveStack[i].area, buyukHarf(a));
	saveStack[i].ii = ix;
	isavestack++;
}

int stringmi(int ix)
{
	if (states[ix].ientry == 0)
		return 0;
	if (states[ix].ientry > 0)
		if (states[ix].entry[0].iexec == 0 &&
			states[ix].entry[0].igen == 0 &&
			states[ix].entry[0].iopen == 0 &&
			states[ix].entry[0].isetval > 0)
			return 1;
	return 0;
}

void changefuncs(char* fn, char* rtype, char* intype)
{
	int i;
	for (i = 0; i < ifuncs; i++) {
		if (strcmp(funcs[i].fname, fn) == 0) {
			if (!funcs[i].finmodel)
				funcs[i].finmodel = (char*)"void";
			if (strcmp(funcs[i].finmodel, "void") == 0)
				funcs[i].finmodel = intype;
			if (!funcs[i].fretmodel)
				funcs[i].fretmodel = (char*)"void";
			if (strcmp(funcs[i].fretmodel, "void") == 0)
				funcs[i].fretmodel = rtype;
			return;
		}
	}
}

//void funcWrite(char* fname, int ii, char* prog, char* trn)
//{
//	int  j, ix;
//	char* rtype, * inmodel;
//	char* msg;
//	char* returns = 0;
//	char* retval;
//	if (ii >= 0 && vmodel[ii].stype && strcmp(vmodel[ii].stype, "initial") == 0) return;
//	if (ii >= 0 && vmodel[ii].stype && strcmp(vmodel[ii].stype, "final") == 0) return;
//		if (yazilanaekle(fname) == 1) return;
//		if (ii >= 0) {
//			rtype = vmodel[ii].sview;
//			inmodel = vmodel[ii].sview;
//			writeFunc(ii, prog, trn, areaName);
//			j = 0;
//			while (vmodel[ii].stranid[j] != NULL) {
//				if (strstr(vmodel[ii].stranid[j], "ERROR")) {
//					msg = getErrormsg(vmodel[ii].starget[j]);
//					if (msg != NULL)
//						writeError(inmodel, msg);
//				}
//				ix = vmodeliiGet(vmodel[ii].starget[j]);
//				if (ix >= 0) {
//					fname = vmodel[ix].sid;
//					changefuncs(fname, rtype, inmodel);
//					mySaveStack(fname, ix, vmodel[ix].sview, progname, trn, areaName);
//					fname = vmodel[ix].sid;
//					funcWrite(fname, ix, prog, trn);
//				}
//				j++;
//			}
//		}
//		else {
//			char* inmodel2;
//			char* pm;
//			int  jx, strval, yok = 1;
//			for (ix = 0; ix < iflowcall; ix++) {
//				if (strcmp(flowcall[ix].funcname, fname) == 0) {
//					ix = baslik(fname);
//					if (ix >= 0) {
//						rtype = funcs[ix].fretmodel;
//						if (funcs[ix].finmodel)
//							inmodel = funcs[ix].finmodel;
//						else inmodel = rtype;
//					}
//					else {
//						rtype = fname;
//						inmodel = fname;
//					}
//					indents = 1;
//					returns = defineFunc(rtype, ii, fname, inmodel, &retval);
//					if (ix < 99 && flowcall[ix].jcount) {
//						for (jx = 0; jx < flowcall[ix].jcount; jx++) {
//							ii = vmodeliiGet(flowcall[ix].fcall[jx]);
//							inmodel2 = vmodel[ii].sview;
//							if (jx == 0) {
//								if (globalvar == 0) {
//									fprintf(output, "%s", indentstr());
//									fprintf(output, "global = fillGlobals(global);\n");
//									globalvar = 1;
//								}
//								fprintf(output, "%s", indentstr());
//								if (strcmp(inmodel2, " ")) {
//									int iy = baslik(inmodel2);
//									if (constVariables(inmodel2)) {
//										if (iy == 0 && funcs[iy].finmodel && strcmp(funcs[iy].finmodel, inmodel2)) {
//											yazgetViews(funcs[iy].finmodel, (char*)"vmodel");
//										}
//									}
//								}
//								else {
//									int iy = baslik(flowcall[ix].funcname);
//									if (iy >= 0 && funcs[iy].finmodel && strcmp(funcs[iy].finmodel, inmodel) != 0) {
//										yazgetViews(funcs[iy].finmodel, (char*)"vmodel");
//									}
//								}
//							}
//							fprintf(output, "%s", indentstr());
//							if (constVariables(flowcall[ix].tags[jx]))
//								fprintf(output, "if(global.actiontag == %s) {\n", constVariables(flowcall[ix].tags[jx]));
//							indents++;
//							strval = stringmi(vmodel[ii].is);
//							mySaveStack(vmodel[ii].sid, ii, vmodel[ii].sview, prog, trn, areaName);
//							if (inmodel) {
//								if (strcmp(inmodel, inmodel2) == 0) {
//									if (strval == 1) {
//										int iy = baslik(flowcall[ix].fcall[jx]);
//										if (iy >= 0 && funcs[iy].finmodel) {
//											fprintf(output, "%s", indentstr());
//											if (strcmp(funcs[iy].finmodel, inmodel) == 0)
//												fprintf(output, "%s(model);\n", flowcall[ix].fcall[jx]);
//											else {
//												fprintf(output, "%s", indentstr());
//												fprintf(output, "%s(vmodel);\n", flowcall[ix].fcall[jx]);
//											}
//										}
//										else {
//											yazgetViews(flowcall[ix].funcname, (char*)"vmodel");
//											fprintf(output, "%s", indentstr());
//											fprintf(output, "%s(vmodel);\n", flowcall[ix].fcall[jx]);
//										}
//									}
//									else
//										if (strcmp(rtype, vmodel[ii].sview) == 0) {
//											int iy = baslik(flowcall[ix].fcall[jx]);
//											if (strcmp(funcs[iy].fretmodel, rtype) == 0) {
//												fprintf(output, "%s", indentstr());
//												fprintf(output, "model = %s(model);\n", flowcall[ix].fcall[jx]);
//											}
//											else {
//												fprintf(output, "%s", indentstr());
//												fprintf(output, "%s(model);\n", flowcall[ix].fcall[jx]);
//											}
//											if (states[ii].ientry > 0 && states[ii].entry[0].iopen > 0)
//												newButtons(ii, states[ii].entry[0].sopen, states[ii].entry[0].iopen, areaName, (char*)"model");
//											saveGlobal();
//											fprintf(output, "%s", indentstr());
//											if (voidreturn)
//												fprintf(output, "return;\n");
//											else fprintf(output, "return model;\n");
//										}
//										else {
//											fprintf(output, "%s", indentstr());
//											fprintf(output, "    model = %s(vmodel);\n", flowcall[ix].fcall[jx]);
//
//											if (states[ii].ientry > 0 && states[ii].entry[0].iopen > 0)
//												newButtons(ii, states[ii].entry[0].sopen, states[ii].entry[0].iopen, areaName, (char*)"model");
//											saveGlobal();
//											fprintf(output, "%s", indentstr());
//											fprintf(output, "    return model;\n");
//										}
//								}
//								else {
//									if (strval == 1) {
//										int iy = baslik(flowcall[ix].fcall[jx]);
//										if (funcs[iy].finmodel) {
//											char* px = funcs[iy].finmodel;
//											yazgetViews(px, (char*)"vmodel");
//										}
//										else {
//											yazgetViews(flowcall[ix].funcname, (char*)"vmodel");
//										}
//										fprintf(output, "%s", indentstr());
//										fprintf(output, "%s(vmodel);\n", flowcall[ix].fcall[jx]);
//									}
//									else
//										if (strcmp(rtype, vmodel[ii].sview) == 0) {
//											fprintf(output, "%s", indentstr());
//											fprintf(output, "    model = %s(vmodel);\n", flowcall[ix].fcall[jx]);
//											if (states[ii].ientry > 0 && states[ii].entry[0].iopen > 0)
//												newButtons(ii, states[ii].entry[0].sopen, states[ii].entry[0].iopen, areaName, (char*)"model");
//											saveGlobal();
//											fprintf(output, "%s", indentstr());
//											if (voidreturn)
//												fprintf(output, "    return;\n");
//											else fprintf(output, "    return model;\n");
//										}
//										else {
//											fprintf(output, "%s", indentstr());
//											if (returns && strcmp(returns, inmodel2)) {
//												char* px;
//												int iy = baslik(flowcall[ix].fcall[jx]);
//												if (iy >= 0 && funcs[iy].finmodel) {
//													yazgetViews(funcs[iy].finmodel, (char*)"vmodel");
//
//													fprintf(output, "%s", indentstr());
//													fprintf(output, "    vmodel = %s(vmodel);\n", flowcall[ix].fcall[jx]);
//													fprintf(output, "%s", indentstr());
//													if (states[ii].ientry > 0 && states[ii].entry[0].iopen > 0)
//														newButtons(ii, states[ii].entry[0].sopen, states[ii].entry[0].iopen, areaName, (char*)"model");
//													fprintf(output, "    if(vmodel != null)\n");
//													fprintf(output, "%s", indentstr());
//													fprintf(output, "    {\n");
//													fprintf(output, "%s", indentstr());
//													if (constVariables(flowcall[ix].funcname)) {
//														px = flowcall[iy].funcname;
//														if (strstr(px, "KriterView"))
//															pm = tranname;
//														else pm = (char*)"";
//														fprintf(output, "    Floww.AddVariableToFlow<%s%sViewModel>(new KeeyValuePair<string, %s%sViewModel>(%s, vmodel));\n",
//															pm, px, pm, px, constVariables(px));
//													}
//													saveGlobal();
//													fprintf(output, "%s", indentstr());
//													if (voidreturn)
//														fprintf(output, "    return;\n");
//													else fprintf(output, "     return model;\n");
//													fprintf(output, "%s", indentstr());
//													fprintf(output, "   }\n");
//													globalvar = 0;
//												}
//											}
//											else {
//												int iy = baslik(flowcall[ix].fcall[jx]);
//												if (iy >= 0 && funcs[iy].finmodel) {
//													yazgetViews(funcs[iy].finmodel, (char*)"model");
//
//													fprintf(output, "    model = %s(vmodel);\n", flowcall[ix].fcall[jx]);
//													fprintf(output, "%s", indentstr());
//													if (states[ii].ientry > 0 && states[ii].entry[0].iopen > 0)
//														newButtons(ii, states[ii].entry[0].sopen, states[ii].entry[0].iopen, areaName, (char*)"model");
//													fprintf(output, "%s", indentstr());
//													fprintf(output, "    if(model != null)\n");
//													fprintf(output, "%s", indentstr());
//													fprintf(output, "    {\n");
//													yazsaveViews(flowcall[ix].funcname, (char*)"vmodel");
//
//													saveGlobal();
//													fprintf(output, "%s", indentstr());
//													if (voidreturn)
//														fprintf(output, "      return;\n");
//													else fprintf(output, "      return model;\n");
//													fprintf(output, "%s", indentstr());
//													fprintf(output, "    }\n");
//												}
//											}
//										}
//								}
//							}
//							else {
//								saveGlobal();
//								fprintf(output, "%s", indentstr());
//								if (voidreturn)
//									fprintf(output, "      return;\n");
//								else fprintf(output, "      return model;\n");
//							}
//							indents--;
//							fprintf(output, "%s", indentstr());
//							fprintf(output, "}\n");
//							globalvar = 0;
//						}
//					}
//					writeReturn();
//					endfunc();
//					yok = 0;
//					break;
//				}
//			}
//			if (yok) {
//				rtype = fname;
//				inmodel = fname;
//				ix = baslik(fname);
//				if (ix >= 0) {
//					rtype = funcs[ix].fretmodel;
//					inmodel = funcs[ix].finmodel;
//					if (inmodel == 0)
//						inmodel = fname;
//				}
//				defineFunc(rtype, ii, fname, inmodel, &retval);
//				writeReturn();
//				endfunc();
//			}
//		}
//		voidreturn = 0;
//	}


void funcWrite(char *fname, int ii, char *ssv, char *prog, char *trn, char *areaName)
{
	int  j, ix;
	char *rtype, *inmodel;
	char *msg;
	char *returns = 0;
	char *retval;
	struct NODE* pnode;
	if (ii >= 0 && vmodel[ii].stype && strcmp(vmodel[ii].stype, "initial") == 0) return;
	if (ii >= 0 && vmodel[ii].stype && strcmp(vmodel[ii].stype, "final") == 0) return;
	if(yazilanaekle(fname) == 1) return;
	/*fprintf(output, "++%s\n", fname);*/
	if (ii >= 0) {
		rtype = vmodel[ii].sview;
		inmodel = vmodel[ii].sview;

		writeFunc(ii, prog, trn, areaName);
		j = 0;
		while (vmodel[ii].stranid[j] != NULL) {
			if (strstr(vmodel[ii].stranid[0], "ERROR")) {
				msg = getErrormsg(vmodel[ii].starget[0]);
				if (msg != NULL)
					writeError(inmodel, msg);
			}
			ix = vmodeliiGet(vmodel[ii].starget[j]);
			if (ix >= 0) {
				fname = vmodel[ix].sid;
				changefuncs(fname, rtype, inmodel);
				mySaveStack(fname, ix, vmodel[ix].sview, progname, tranname, areaName);
				fname = vmodel[ix].sid;
				funcWrite(fname, ix, vmodel[ix].sview, progname, tranname, areaName);
			}
			j++;
		}
	}
	else {
		char *inmodel2;
		int  jx, strval, yok = 1;
		for (ix = 0; ix < iflowcall; ix++) {
			if (strcmp(flowcall[ix].funcname, fname) == 0) {
				int ix;
				ix = baslik(fname);
				if (ix >= 0) {
					rtype = funcs[ix].fretmodel;
					if (funcs[ix].finmodel)
						inmodel = funcs[ix].finmodel;
					else inmodel = rtype;
				}
				else {
					rtype = fname;
					inmodel = fname;
				}
				indents = 1;
				pnode = nodeBak(fname);
				if (pnode) {
					rtype = (pnode->nretmodel == NULL) ? "void" : pnode->nretmodel;
					inmodel = (pnode->ninmodel == NULL) ? "void" : pnode->ninmodel;
				}
				returns = defineFunc(rtype, ii, fname, inmodel, &retval);

				for (jx = 0; jx < flowcall[ix].jcount; jx++) {
					ii = vmodeliiGet(flowcall[ix].fcall[jx]);
					inmodel2 = vmodel[ii].sview;
					if (inmodel2 == NULL) inmodel2 = " ";
					if (jx == 0) {
						if (globalvar == 0) {
							fprintf(output, "%s", indentstr());
							fprintf(output, "global = FillGlobals(global);\n");
							globalvar = 1;
						}
						fprintf(output, "%s", indentstr());
						if (strcmp(inmodel2, " ")) {
							int iy = baslik(inmodel2);
							if (constVariables(inmodel2)) {
								if (iy == 0 && funcs[iy].finmodel && strcmp(funcs[iy].finmodel, inmodel2)) {
									/*yazgetViews(funcs[iy].finmodel, (char*)"vmodel");*/
								}
							}
						}
		//				else {
		//int iy = baslik(flowcall[ix].funcname);
		//					if (iy >= 0 && funcs[iy].finmodel && strcmp(funcs[iy].finmodel, inmodel) != 0) {
		//						yazgetViews(funcs[iy].finmodel, (char*)"vmodel");
		//					}					
		//				}
					}
					fprintf(output, "%s", indentstr());
					if (constVariables(flowcall[ix].tags[jx]))
						fprintf(output, "if (model.Actiontag == %s) {\n",constVariables(flowcall[ix].tags[jx]));
					indents++;

					strval = stringmi(vmodel[ii].is);
					mySaveStack(vmodel[ii].sid, ii, vmodel[ii].sview, prog, trn, areaName);
					if (inmodel) {
						if (strcmp(inmodel, inmodel2) == 0) {
							if (strval == 1) {
								int iy = baslik(flowcall[ix].fcall[jx]);
								if (iy >= 0 && funcs[iy].finmodel) {
									fprintf(output, "%s", indentstr());
									if (strcmp(funcs[iy].finmodel, inmodel) == 0) {
										fprintf(output, "%s(model);\n", flowcall[ix].fcall[jx]);
									}
									else {
										fprintf(output, "%s", indentstr());
										fprintf(output, "%s(vmodel);\n", flowcall[ix].fcall[jx]);
									}
								}
								else {
									/*yazgetViews(flowcall[ix].funcname, (char*)"vmodel");*/
									fprintf(output, "%s", indentstr());
									fprintf(output, "%s(vmodel);\n", flowcall[ix].fcall[jx]);
								}
							}
							else
								if (strcmp(rtype, vmodel[ii].sview) == 0) {
									int iy = baslik(flowcall[ix].fcall[jx]);
									if (strcmp(funcs[iy].fretmodel, rtype) == 0) {
										fprintf(output, "%s", indentstr());
										fprintf(output, "model = %s(model);\n", flowcall[ix].fcall[jx]);
									}
									else {
										fprintf(output, "%s", indentstr());
										fprintf(output, "%s(model);\n", flowcall[ix].fcall[jx]);
									}
									if (states[ii].ientry > 0 && states[ii].entry[0].iopen > 0)
										newButtons(ii, states[ii].entry[0].sopen, states[ii].entry[0].iopen, areaName, "model");
									saveGlobal();
									fprintf(output, "%s", indentstr());
									if (voidreturn)
										fprintf(output, "return;\n");
									else fprintf(output, "return model;\n");
								}
								else {
									fprintf(output, "%s", indentstr());
									fprintf(output, "    model = %s(vmodel);\n", flowcall[ix].fcall[jx]);

									if (states[ii].ientry > 0 && states[ii].entry[0].iopen > 0)
										newButtons(ii, states[ii].entry[0].sopen, states[ii].entry[0].iopen, areaName, (char*)"model");
									saveGlobal();
									fprintf(output, "%s", indentstr());
									if (voidreturn)
										fprintf(output, "    return;\n");
									else fprintf(output, "    return model;\n");
								}
						}
						else { 
							if (strval == 1) {
								int iy = baslik(flowcall[ix].fcall[jx]);
								//if (funcs[iy].finmodel) {
								//	char* px = funcs[iy].finmodel;
								//	yazgetViews(px, (char*)"vmodel");
								//}
								//else {
								//	yazgetViews(flowcall[ix].funcname, (char*)"vmodel");
								//}
								fprintf(output, "%s", indentstr());
								fprintf(output, "%s(vmodel);\n", flowcall[ix].fcall[jx]);
							}
							else
								if (strcmp(rtype, vmodel[ii].sview) == 0) {
									fprintf(output, "%s", indentstr());
									fprintf(output, "    model = %s(vmodel);\n", flowcall[ix].fcall[jx]);
									if (states[ii].ientry > 0 && states[ii].entry[0].iopen > 0)
										newButtons(ii, states[ii].entry[0].sopen, states[ii].entry[0].iopen, areaName, "model");
									saveGlobal();
									fprintf(output, "%s", indentstr());
									if (voidreturn)
										fprintf(output, "    return;\n");
									else fprintf(output, "    return model;\n");
								}
								else {
									fprintf(output, "%s", indentstr());
									if (returns && strcmp(returns, inmodel2)) {
										int iy = baslik(flowcall[ix].fcall[jx]);
										if (iy >= 0 && funcs[iy].finmodel) {
											/*yazgetViews(funcs[iy].finmodel, (char*)"vmodel");*/

											//fprintf(output, "%s", indentstr());
											//fprintf(output, "    vmodel = %s(vmodel);\n", flowcall[ix].fcall[jx]);
											//fprintf(output, "%s", indentstr());
											//if (states[ii].ientry > 0 && states[ii].entry[0].iopen > 0)
											//	newButtons(ii, states[ii].entry[0].sopen, states[ii].entry[0].iopen, areaName, (char*)"model");
											//saveGlobal();
											//fprintf(output, "    if(vmodel != null)\n");
											//fprintf(output, "%s", indentstr());
											//fprintf(output, "    {\n");
											//fprintf(output, "%s", indentstr());
											//if (constVariables(flowcall[ix].funcname)) {
											//	px = flowcall[ix].funcname;
											//	if (strstr(px, "KriterView"))
											//		pm = tranname;
											//	else pm = (char*)"";
											//	fprintf(output, "    Flow.AddVariableToFlow<%s%sViewModel>(new KeyValuePair<string, %s%sViewModel>(%s, vmodel));\n",
											//		pm, px, pm, px, constVariables(px));
											//}
											//saveGlobal();
											//fprintf(output, "%s", indentstr());
											//if (voidreturn)
											//	fprintf(output, "    return;\n");
											//else fprintf(output, "     return model;\n");
											//fprintf(output, "%s", indentstr());
											//fprintf(output, "   }\n");
											globalvar = 0;
										}
									}
									else {
										int iy = baslik(flowcall[ix].fcall[jx]);
										if (iy >= 0 && funcs[iy].finmodel) {
											/*yazgetViews(funcs[iy].finmodel, (char*)"model");*/

											fprintf(output, "    model = %s(model);\n", flowcall[ix].fcall[jx]);
											fprintf(output, "%s", indentstr());
											if (states[ii].ientry > 0 && states[ii].entry[0].iopen > 0)
												newButtons(ii, states[ii].entry[0].sopen, states[ii].entry[0].iopen, areaName, (char*)"model");
											fprintf(output, "%s", indentstr());
											fprintf(output, "    if(model != null)\n");
											fprintf(output, "%s", indentstr());
											fprintf(output, "    {\n");
											/*yazsaveViews(flowcall[ix].funcname, (char*)"vmodel");*/

											saveGlobal();
											fprintf(output, "%s", indentstr());
											if (voidreturn)
												fprintf(output, "      return;\n");
											else fprintf(output, "      return model;\n");
											fprintf(output, "%s", indentstr());
											fprintf(output, "    }\n");
										}
									}
								}
						}
					}
					else {
						saveGlobal();
						fprintf(output, "%s", indentstr());
						if (voidreturn)
							fprintf(output, "      return;\n");
						else fprintf(output, "      return model;\n");
					}
					indents--;
					fprintf(output, "%s", indentstr());
					fprintf(output, "}\n");
					globalvar = 0;
				}
				writeReturn();
				endfunc();
				yok = 0;
				break;
			}
		}
		if (yok) {
			int ix;
			rtype = fname;
			inmodel = fname;
			ix = baslik(fname);
			if (ix >= 0) {
				rtype = funcs[ix].fretmodel;
				inmodel = funcs[ix].finmodel;
				if (inmodel == 0)
					inmodel = fname;
			}
			pnode = nodeBak(fname);
			if (pnode) {
				rtype = (pnode->nretmodel == NULL) ? "void" : pnode->nretmodel;
				inmodel = (pnode->ninmodel == NULL) ? "void" : pnode->ninmodel;
			}
			defineFunc(rtype, ii, fname, inmodel, &retval);
			writeReturn();
			endfunc();
		}
	}
	voidreturn = 0;
}

int controllerstartvarmi(char *fnam)
{
	int i;
	for (i = 0; i < icontrollerstart; i++) {
		if (strcmp(controllerstart[i], fnam) == 0)
			return 1;
	}
	return 0;
}
char *byaz[120];
int  ibaslikyaz = 0;
 
int  baslikyaz(char *fnam)
{
	int i;
	for (i = 0; i < ibaslikyaz; i++)
	{
		if (strcmp(byaz[i], fnam) == 0)
			return 1;
	}
	byaz[ibaslikyaz] = (char *)calloc(1, strlen(fnam) + 1);
	strcpy(byaz[ibaslikyaz], fnam);
	ibaslikyaz++;
	return 0;
}

int baslik(char *fnam)
{
	int i;
	int varmis = 0;
	for (i = 0; i < ifuncs; i++) {
		if (strcmp(funcs[i].fname, fnam) == 0)
			return i;
	}
	return -1;
}


void basla(char *prog, char *trn, char *areaName) 
{
	int  ic, ii, iy, i, j, buldu;
	char *fname;
	for (ic = 0; ic < icontrollerstart; ic++) {
		if (strcmp(controllerstart[ic], "Index") == 0) continue;
		ii = vmodeliiGet(controllerstart[ic]);
		if (ii < 0)
			 fname = controllerstart[ic];
		else fname = vmodel[ii].sid;
		funcWrite(fname, ii, vmodel[ii].sview, prog, trn, areaName);
	}

	
	for (i = 0; i < istate; i++) {
		buldu = 0;
		for (j = 0; j < iyazilan; j++) {
			if (strcmp(yazilan[j], states[i].stateid) == 0)
				buldu = 1;
		}
		if (buldu == 0) {
			ii = vmodeliiGet(states[i].stateid);
			funcWrite(states[i].stateid, ii, vmodel[ii].sview, prog, trn, areaName);
		}
	}
	for (iy = 0; iy < isavestack; iy++) {
		funcWrite(saveStack[iy].fn, saveStack[iy].ii, saveStack[iy].sv, saveStack[iy].prog, saveStack[iy].trn, saveStack[iy].area);
	}
	isavestack = 0;
}

void finalstate()
{
	int i, ii, yazar = 0;
	for (i = 0; i < istate; i++) {
		if (strcmp(states[i].statetype, "final") == 0) {
			ii = vmodelBak(i);
			fprintf(output, "%s", indentstr());
			if (strstr(vmodel[ii].sview, "KriterView"))
				fprintf(output, "public %s%sViewModel %s(%s%sViewModel model)\n", tranname, vmodel[ii].sview, states[i].stateid, tranname, vmodel[ii].sview);
			else fprintf(output, "public %sViewModel %s(%sViewModel model)\n", vmodel[ii].sview, states[i].stateid, vmodel[ii].sview);
			fprintf(output, "%s", indentstr());
			fprintf(output, "{\n");
			indents++;
			fprintf(output, "%s", indentstr());
			fprintf(output, "// Program bitti...\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "model.OperationResult.IsSuccessful = false;\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "model.OperationResult.Message = \"Program Bitti\";\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "return model; \n");
			yazar = 1;
		}
		else {
			fprintf(output, "%s", indentstr());
			fprintf(output, "public void %s()\n", states[i].stateid);
			fprintf(output, "%s", indentstr());
			fprintf(output, "{\n");
			indents++;
			fprintf(output, "%s", indentstr());
			fprintf(output, "// Program bitti...\n");
			yazar = 1;
		}
		if (yazar) {
			indents--;
			fprintf(output, "%s", indentstr());
			fprintf(output, "}\n");
			break;
		}
	}
}

//void saveViews(char* fmodel)
//{
//	fprintf(output, "%s", indentstr());
//	fprintf(output, "Flow.AddVariableToFlow<%sViewModel>(new KeyValuePair<string, %sViewModel>(%s, model));\n",
//		fmodel, fmodel, constVariables(fmodel));
//}
//
//void getViews(char* myvmodel, char* viewtype)
//{
//	char* pw;
//	if (strstr(myvmodel, "KriterView"))
//		pw = tranname;
//	else pw = (char*)"";
//	fprintf(output, "%s", indentstr());
//	fprintf(output, "%s%sViewModel %s = new %s%sViewModel();\n", pw, myvmodel, viewtype, pw, myvmodel);
//	fprintf(output, "%s", indentstr());
//	fprintf(output, "if(Flow.GetViewDetail(%sConstants.FlowView.%s) != null)\n", tranname, myvmodel);
//	indents++;
//	fprintf(output, "%s", indentstr());
//	fprintf(output, "%s = Flow.GetViewDetail(%sConstants.FlowView.%s).Model as %s%sViewModel;\n",
//		viewtype, tranname, myvmodel, pw, myvmodel);
//	indents--;
//}

int itasi;
char* tasima[200];
int tasindi(char* p)
{
	int i;
	for (i = 0; i < itasi; i++) {
		if (strcmp(tasima[i], p) == 0)
			return 1;
	}
	i = itasi;
	itasi++;
	tasima[i] = (char*)calloc(1, strlen(p) + 1);
	strcpy(tasima[i], p);
	return 0;
}

//void writeViewFunc()
//{
//	int  i;
//	indents = 1;
//	for (i = 0; i < iviews; i++) {
//		// fviews[i].v1,
//		if (!strstr(fviews[i].v1, "Vcontroller")) {
//			if (tasindi(fviews[i].v1)) continue;
//			fprintf(output, "%s", indentstr());
//			fprintf(output, "public %sViewModel Get%s()\n", fviews[i].v1, fviews[i].v1);
//			fprintf(output, "%s", indentstr());
//			fprintf(output, "{\n");
//
//			indents++;
//			getViews(fviews[i].v1, (char*)"model");
//			fprintf(output, "%s", indentstr());
//			fprintf(output, "return model;\n");
//			indents--;
//			fprintf(output, "%s", indentstr());
//			fprintf(output, "}\n");
//			fprintf(output, "%s", indentstr());
//			fprintf(output, "public void Save%s(%sViewModel model)\n", fviews[i].v1, fviews[i].v1);
//			fprintf(output, "%s", indentstr());
//			fprintf(output, "{\n");
//
//			indents++;
//			saveViews(fviews[i].v1);
//			indents--;
//			fprintf(output, "%s", indentstr());
//			fprintf(output, "}\n");
//		}
//	}
//}


void ClientProlog(char *fdir, char *prog, char *trn, char *areaName)
{
	int  i;
	clientBusiness(fdir, prog, trn, areaName);
	
	for (i = 0; i < istate; i++) {
		if (strncmp(states[i].statetype, "initial", 7) == 0) {
			char *px = modelBak(i); // states[i].stateid
			startClient(trn, i, px, areaName);
		}
	}

	basla(prog, trn, areaName);
	MCAToViewModel();
	ViewModelToMCA();
	/*ViewToViewModel();*/
	globalYaz();
	/*MySetVars();*/
	/*MyGetVars();*/
	selectedYaz();

	printerYaz();
	finalstate();
	noViews();
	/*writeViewFunc();*/

	fprintf(output, "%s", indentstr());
	fprintf(output, "}\n");
	fprintf(output, "\n}\n");
	globalvar = 0;
}

int ekranmi(char *ekr)
{
	int i, len;
	if (ekr) {
		len = (int)strlen(ekr);
		for (i = 0; i < istate; i++) {
			if (strcmp(states[i].stateid, ekr) == 0) {
				if ((strcmp(states[i].statetype, "view") == 0) ||
					(strcmp(states[i].statetype, "initial") == 0))
					return true;
				else return false;
			}
		}
	}
	return false;
}

void views(int i, int otherSet)
{
	int j, yazdi;
	char other[30];
	yazdi = 0;
	if (otherSet)
		strcpy(other, "Business.");
	else strcpy(other, " ");
	
	if (strcmp(states[i].stateid, indexname) == 0) return;
	indents = 2;
	/*indents++;*/
	if (tekEkranmi(states[i].entry[0].sopen[0].viewname)) return;
	fprintf(output, "%s", indentstr());
	fprintf(output, "Flow.Configure(%sConstants.FlowView.%s)\n", tranname, states[i].stateid);
	for (j = 0; j<states[i].itran; j++) {
		states[i].trans[j].trantarget = myReplace(states[i].trans[j].trantarget, ' ', '_');
		states[i].trans[j].trantarget = myReplace(states[i].trans[j].trantarget, '-', '_');
		if (yazdi) fprintf(output, "\n");
		yazdi = false;

		if (states[i].itran > 1) {
			indents = 2;
			fprintf(output, "%s", indentstr());
			fprintf(output, ".AllowDynamic(Trigger.Next, SelectScreen)"); // , states[i].stateid);
			yazdi = true;
			addToFunctions(i, j);
		}
		else {
			if (ekranmi(states[i].trans[j].trantarget)) {
				if ((strstr(states[i].trans[j].tranid, ".DEVAM")) ||
					(strstr(states[i].trans[j].tranid, ".CLICK")) ||
					(strstr(states[i].trans[j].tranid, ".TAMAM"))) {
					if (yazdi) fprintf(output, "\n");
					fprintf(output, "%s", indentstr());
					if (strcmp(states[i].trans[j].trantarget, initialscr) == 0)
						fprintf(output, ".Allow(Trigger.Next, %sConstants.FlowView.ViewIndex)", tranname);
					else
						fprintf(output, ".Allow(Trigger.Next, %s)",
						states[i].trans[j].trantarget);
					yazdi = true;
				}
				if (strstr(states[i].trans[j].tranid, "ESC") ||
					strstr(states[i].trans[j].tranid, "GERI")) {
					if (yazdi) fprintf(output, "\n");
					fprintf(output, "%s", indentstr());
					if (strcmp(states[i].trans[j].trantarget, initialscr) == 0)
						fprintf(output, ".Allow(Trigger.Previous, %sConstants.FlowView.ViewIndex)", tranname);
					else
						fprintf(output, ".Allow(Trigger.Previous, %s)", 
							states[i].trans[j].trantarget);
					yazdi = true;
				}
			}
			else {
				if ((strstr(states[i].trans[j].tranid, ".DEVAM")) ||
					(strstr(states[i].trans[j].tranid, ".CLICK")) ||
					(strstr(states[i].trans[j].tranid, ".TAMAM"))) {
					if (yazdi) fprintf(output, "\n");
					indents = 3;
					fprintf(output, "%s", indentstr());
					fprintf(output, ".AllowDynamic(Trigger.Next, SelectScreen)");
					addToFunctions(i, j);
					yazdi = true;
				}
				if (strstr(states[i].trans[j].tranid, "ESC") ||
					strstr(states[i].trans[j].tranid, "GERI")) {
					if (yazdi) fprintf(output, "\n");
					indents = 3;
					fprintf(output, "%s", indentstr());
					fprintf(output,
						".AllowDynamic(Trigger.Previous, SelectScreen)"); // , states[i].stateid);
					addToFunctions(i, j);
					yazdi = true;
				}
			}
			if (yazdi == false) {
				strcpy(other, " ");
				if (ekranmi(states[i].trans[j].trantarget))
					strcpy(other, "Business.");
				indents = 3;
				fprintf(output, "%s", indentstr());
				if (strcmp(states[i].trans[j].trantarget, initialscr) == 0)
					fprintf(output, ".Allow(Trigger.Next, %sConstants.FlowView.ViewIndex)", tranname);
				else
					if (ekranmi(states[i].trans[j].trantarget)) {
						fprintf(output, ".Allow(Trigger.Next, %s%s)\n", other, states[i].trans[j].trantarget);
					}
					else {
						fprintf(output, ".AllowDynamic(Trigger.Next, SelectScreen)\n");
					}
				indents = 3;
				fprintf(output, "%s", indentstr());
				if (strcmp(states[i].trans[j].trantarget, initialscr) == 0)
					fprintf(output, ".Allow(Trigger.Previous,  %sConstants.FlowView.ViewIndex)", tranname);
				else
					if (ekranmi(states[i].trans[j].trantarget)) {
						fprintf(output, ".Allow(Trigger.Previous, %s%s)",
							other, states[i].trans[j].trantarget);
					}
				yazdi = true;
			}
		}
		indents--;
		if (yazdi) { fprintf(output, ";\n"); break; }
	}
}

int  nextid(char *p)
{
	int  i;
	p = myReplace(p, ' ', '_');
	for (i = 0; i < istate; i++){
		if (strcmp(states[i].stateid, buyukHarf(p)) == 0)
			return i;
	}
	fprintf(output, "p YOK %s\n", p);
	return -1;
}

char *flowifloop(struct COMPCON *cp, int k1) {
	char rbuf[200], lbuf[200];
	char outs[2000];
	char* pp;

	struct LOGICAL *lp;
	int  first, fused = 0;
	char *opcode, *p;
	int  kk, opint, ifvar;
	is = -1;
	prevop[0][0] = NULL;
	first = 0;
	ifvar = 0;
	outs[0] = 0;
	for (kk = k1; kk < (cp+k1)->ilogical; kk++) {
		lp = &cp->logical[kk];
		opint = 0;
		if (strcmp(lp->opname, "EQ") == 0)
			opcode = "==";
		else
			if (strcmp(lp->opname, "LE") == 0) {
				opcode = "<=";
				opint = 1;
			}
			else
				if (strcmp(lp->opname, "GE") == 0) {
					opcode = ">=";
					opint = 1;
				}
				else
					if (strcmp(lp->opname, "GT") == 0) {
						opcode = ">";
						opint = 1;
					}
					else
						if (strcmp(lp->opname, "LT") == 0) {
							opcode = "<";
							opint = 1;
						}
						else
							if (strcmp(lp->opname, "NEQ") == 0)
								opcode = "!=";
							else
								if (strcmp(lp->opname, "AND") == 0)
									opcode = "&&";
								else
									if (strcmp(lp->opname, "OR") == 0)
										opcode = "||";
									else
										opcode = lp->opname;
		if ((strcmp(opcode, "&&") == 0) && lp->firstop == NULL) {
			is++;
			strcpy(prevop[is], opcode);
			if (fused == 0) {
				first = 1;
				fused = 1;
			}
			continue;
		}
		if ((strcmp(opcode, "||") == 0) && lp->firstop == NULL) {
			is++;
			strcpy(prevop[is], opcode);
			if (fused == 0) {
				first = 1;
				fused = 1;
			}
			continue;
		}
		if (ifvar != 1 && strcmp(opcode, "&&") != 0 && strcmp(opcode, "||") != 0 && lp->firstop != NULL)
			ifvar = 1;
		if (strcmp(lp->firstop, "1") != 0) {
			if (lp->firstop[0] == '@') {
				p = mcaArrMi(lp->firstop + 1);
				if (p)
					sprintf(lbuf, "%s", evaluateDefValue(FLOW, lp->firstop));
				else
					sprintf(lbuf, "%s", evaluateDefValue(FLOW, lp->firstop));
			}
			else
				strcpy(lbuf, lp->firstop);
			if (lp->secondop != NULL) {
				if (lp->secondop[0] == '@') {
					p = mcaArrMi(lp->secondop + 1);
					if (p)
						sprintf(rbuf, "%s", evaluateDefValue(FLOW, lp->secondop));
					else
						sprintf(rbuf, "%s", evaluateDefValue(FLOW, lp->secondop));
				}
				else
					strcpy(rbuf, lp->secondop);
			}
			else rbuf[0] = 0;
			if (is >= 0 && prevop[is][0]) {
				if (first) {
					indents--;
					fprintf(output, "%s", indentstr());
					if (opint == 0) {
						fprintf(output, "if((%s %s %s) ", lbuf, opcode, initVariables(rbuf));
					}
					else {
						fprintf(output, "if((int.Parse(%s) %s %s) ", lbuf, opcode, rbuf);
					}
					first = 0;
					continue;
				}
				else {
					if (opint == 0) {
						if (kk + 1 != cp->ilogical) {
							fprintf(output, " %s (%s %s %s) ",
								prevop[is], lbuf, opcode, initVariables(rbuf));
						}
						else {
							fprintf(output, " %s (%s %s %s)) ",
								prevop[is], lbuf, opcode, initVariables(rbuf));
						}
					}
					else {
						fprintf(output, " %s (int.Parse(%s) %s %s)) ",
							prevop[is], lbuf, opcode, rbuf);
					}
					is--;
					if (is < 0) {
						fprintf(output, " { \n");
						prevop[0][0] = NULL;
					}
				}
			}
			else {
				fprintf(output, "%s", indentstr());
				fprintf(output, "if(%s %s %s) {\n",
					lbuf, opcode, initVariables(rbuf));
			}
		}
	}
	pp = (char *)calloc(1, strlen(outs) + 1);
	strcpy(pp, outs);
	return pp;
}
char *setcond(int ii, int jj, int kk)
{
	char *out;
	out = flowifloop(states[ii].entry[jj].ecompcon, kk);
	return out;
}

int setnext(int ii, int jj, char *tfalse, int k1)
{
	int  k;
	char *p, *p1;
	if (ii < 0) return ii;
	for (k = k1; k < states[ii].entry[jj].icompcond; k++){
		p = 0;
		if (strcmp(tfalse,"true") == 0)
			 p = strstr(states[ii].entry[jj].ecompcon[k].onTrue, "changeState(");
		else {
			if (states[ii].entry[jj].ecompcon[k].onFalse)
				p = strstr(states[ii].entry[jj].ecompcon[k].onFalse, "changeState(");
		}
		if (p) {
			p1 = p + 12;
			p = p1;
			while (*p && *p != ')') p++;
			if (p) {
				*p = 0;
			}
			return nextid(p1);
		}
	}
	return -1;
}

int condset = 0;
int  icbfunc = 0;
char *cbfunc1[100];
char *cbfunc4[100];
char *cbfunc3[100];
char *cbfunc2[100];
char cbfuncName[200];

void cbfuncCall(char *px, char *p1, char *target)
{
	int  i;
	for (i = 0; i < icbfunc; i++) {
		if (strcmp(cbfunc1[i], px) == 0 && strcmp(cbfunc2[i], target) == 0) return;
	}
	i = icbfunc;
	cbfunc1[i] = (char *)calloc(1, strlen(px) + 1);
	strcpy(cbfunc1[i], px);
	cbfunc2[i] = (char *)calloc(1, strlen(target) + 1);
	strcpy(cbfunc2[i], target);
	cbfunc4[i] = (char *)calloc(1, strlen(p1) + 1);
	strcpy(cbfunc4[i], p1);
	if (strlen(cbfuncName) > 0) {
		cbfunc3[i] = (char *)calloc(1, strlen(cbfuncName) + 1);
		strcpy(cbfunc3[i], cbfuncName);
	}
	else {
		cbfunc3[i] = NULL;
	}
	icbfunc++;
}

void shiftsaved()
{
	int i;
	for (i = 1; i < isavestate; i++) {
		strcpy(savestate[i - 1].stateid, savestate[i].stateid);
		savestate[i - 1].statej = savestate[i].statej;
		savestate[i - 1].statek = savestate[i].statek;
	}
	if(isavestate) isavestate--;
}

int getsaved()
{
	char *bufp;
	int  nnstate;
	nnstate = nextid(savestate[0].stateid);
	bufp = setcond(nnstate, savestate[0].statej, savestate[0].statek);
	if (strlen(bufp) > 2) {
		fprintf(output, "%s\n", bufp);
		indents++;
		fprintf(output, "%s", indentstr());
	}
	shiftsaved();
	return nnstate;
}
void setothers(int nn, int j, int k1)
{
	int  k, ii;
	char *p, *p1;
	ii = isavestate;
	for (k = k1; k < states[nn].entry[j].icompcond; k++) {
		p = 0;
		if (states[nn].entry[j].ecompcon[k].onTrue) {
			p = strstr(states[nn].entry[j].ecompcon[k].onTrue, "changeState(");
		} 
		else
		if (states[nn].entry[j].ecompcon[k].onFalse) {
			p = strstr(states[nn].entry[j].ecompcon[k].onFalse, "changeState(");
		}
		if (p) {
			p1 = p + 12;
			p = strstr(p1, ")");
			if (p) *p = 0;
		}
		else p1 = p;
		if (p1) {
			strcpy(savestate[ii].stateid, p1);
			savestate[ii].statej = j;
			savestate[ii].statek = k;
		}
	}
}

char *getView(int ii, int jj, char *tag)
{
	int  j, k;
	int  nstate, nnstate, nstate2;
	char *bufp, *mytag;
	int  kopen;
	cbfuncName[0] = 0;
	if (jj >= 0) {
		mytag = tag;
		nstate = ii;
		while (nstate >= 0) {
			nnstate = -1;

			if (states[nstate].itran > 0)
				kopen = openVarmi(nstate);
				for (j = 0; j < states[nstate].itran; j++) {
					if (strstr(states[nstate].trans[j].tranid, mytag) &&
						states[nstate].ientry > 0 && kopen >= 0) {
							for (k = 0; k < states[nstate].entry[kopen].iopen; k++) {
								if (strcmp(states[nstate].entry[kopen].sopen[k].viewname, "filler") != 0) {
									// return states[nstate].entry[j].sopen[k].viewname;
									strcpy(cbfuncName, states[nstate].entry[kopen].sopen[k].viewname);
									return states[nstate].stateid;
								}
							}
						}
				}
		
			// ekran yok
			nnstate = nstate;
			do {
				if (states[nnstate].itran > 0)
					nnstate = nextid(states[nnstate].trans[0].trantarget);
			} while (strcmp(states[nnstate].statetype, "view") &&
					 strcmp(states[nnstate].statetype, "final") &&
					 strcmp(states[nnstate].statetype, "initial") &&
					 strcmp(states[nnstate].statetype, "condition"));

			if (strcmp(states[nnstate].statetype, "condition") == 0) {
				for (j = 0; j < states[nnstate].ientry; j++) {
					if (states[nnstate].entry[j].icompcond > 0) {
						nstate = nnstate;
						for (k = 0; k < states[nnstate].entry[j].icompcond; k++) {
							bufp = setcond(nnstate, j, k);
							if (strlen(bufp) > 2) {
								fprintf(output, "%s\n", bufp);
								indents++;
								fprintf(output, "%s", indentstr());
							}
							nstate2 = setnext(nnstate, j, "true", k);
							setothers(nnstate, j, k);
							if (nstate == nstate2) {
								// search for nextstate
								nstate2 = getsaved();
							}
							nstate = nstate2;
							if (nstate >= 0 && strcmp(states[nstate].statetype, "view") == 0) {
								mytag = "view";
								nnstate = nstate;
								elseset = 1;
							}
							braket++;
							condset = 1;
							break;
						}
					}
				}

			}
			if (strcmp(states[nnstate].statetype, "view") == 0) {
				// return states[nnstate].entry[0].sopen[0].viewname;
				strcpy(cbfuncName, states[nnstate].entry[0].sopen[0].viewname);
				return states[nnstate].stateid;
			}
			if (strcmp(states[nnstate].statetype, "initial") == 0) {
				strcpy(cbfuncName, "Index");
				return states[nnstate].stateid;
			}
			if (strcmp(states[nnstate].statetype, "final") == 0) {
				strcpy(cbfuncName, "final");
				return states[nnstate].stateid;
			}
		}
	}
	return 0;
}

char *getOnlyView(int ii)
{
	// look for the next view of stateid
	int  j, k, newnstate, nnstate;
	int  nstate = flowii[ii];
	char *bufp;
	if (states[nstate].ientry > 0) {
		for (j = 0; j < states[nstate].ientry; j++) {
			if (states[nstate].entry[j].iopen > 0)
				return states[nstate].entry[j].sopen[0].viewname;
		}
	}

	nnstate = nstate;
	do {
		if (states[nnstate].itran > 0)
			for (j = 0; j < states[nnstate].itran; j++) {
				newnstate = nextid(states[nnstate].trans[j].trantarget);
				if (strcmp(states[newnstate].statetype,"final")) {
					nnstate = newnstate;
					if(strcmp(states[nnstate].statetype, "view") == 0 || 
						strcmp(states[nnstate].statetype, "condition") == 0)
						break;
				}
			}
	} while (strcmp(states[nnstate].statetype, "view") && 
		     strcmp(states[nnstate].statetype, "condition"));

	if (strcmp(states[nnstate].statetype, "condition") == 0) {
		for (j = 0; j < states[nnstate].ientry; j++) {
			if (states[nnstate].entry[j].icompcond > 0) {
				for (k = 0; k < states[nnstate].entry[j].icompcond; k++) {
					bufp = setcond(nnstate, j, k);
					// fprintf(output, "%s {\n", bufp);
					bufpset = 1;
					nstate = setnext(nnstate, j, "true", k);
					setothers(nnstate, j, k);
				}
			}
		}
	}
	if (strcmp(states[nnstate].statetype, "view") == 0) {
		return states[nnstate].entry[0].sopen[0].viewname;
	}
	ii++;
	if (ii < iflowfunc) {
		return getOnlyView(ii);
	}
	return 0;
}

int nState(char *p)
{
	int  i;
	for (i = 0; i < istate; i++)
	{
		if (strcmp(states[i].stateid, p) == 0) {
			return i;
		}
	}
	return -1;
}

int getnState(char *p)
{
	int  i, j, k;
	for (i = 0; i < istate; i++)
	{
		if (states[i].ientry > 0) {
			for (j = 0; j < states[i].ientry; j++) {
				if (states[i].entry[j].iopen > 0) {
					for (k = 0; k < states[i].entry[j].iopen; k++) {
						if (strcmp(states[i].entry[j].sopen[k].viewname, p) == 0)
							return i * 1000 + j * 100 + k;
					}
				}
			}
		}
	}
	return -1;
}
char *xptr[6];

void mysplit(char *bf, char *s)
{
	int  i;
	char *p, *p1;
	i = 0;
	p1 = bf;
	while (p1) {
		p = strstr(p1, s);
		if (p) {
			*p = 0;
			xptr[i] = (char *)calloc(1, strlen(p1) + 1);
			strcpy(xptr[i], p1);
			i++;
			p++;
			p1 = p;
		}
		else {
			xptr[i] = (char *)calloc(1, strlen(p1) + 1);
			strcpy(xptr[i], p1);
			i++;
			p1 = p;
		}
	}
}

void targetSay(int ii, char *s)
{
	int  i;
	int  j;
	int say = 0;
	s = buyukHarf(s);
	for (i = 0; i < istate; i++)
	{
		for (j = 0; j < states[i].itran; j++)
		{
			if (strcmp(states[i].trans[j].trantarget, s) == 0) {
				say = states[ii].isref;
				states[ii].staterefs[say] = (char *)calloc(1, strlen(states[i].stateid) + 1);
				strcpy(states[ii].staterefs[say], states[i].stateid);
				states[ii].isref++;
			}
		}
	}
}

void setTranref()
{
	int i;
	for (i = 0; i < istate; i++)
	{
		targetSay(i, states[i].stateid);
	}
}
int openVarmi(int i)
{
	int j, k;
	for(j=0;j<states[i].ientry;j++) {
		for(k=0;k<states[i].entry[j].iopen;k++)
			if(states[i].entry[j].sopen[k].viewname)
				return(j);
	}
	return -1;
}

char* flowgetView(int ii, int jj, char* tag)
{
	int  j, k;
	int nstate, nnstate, nstate2;
	char* bufp, * mytag;
	int kopen;
	cbfuncName[0] = 0;
	if (jj >= 0) {
		mytag = tag;
		nstate = ii;
		while (nstate >= 0) {
			if (states[nstate].itran > 0) {
				kopen = openVarmi(nstate);
				for (j = 0; j < states[nstate].itran; j++) {
					if (strstr(states[nstate].trans[j].tranid, mytag) &&
						states[nstate].ientry > 0 && kopen >= 0) {
						for (k = 0; k < states[nstate].entry[kopen].iopen; k++) {
							if (strcmp(states[nstate].entry[kopen].sopen[k].viewname, "filler") != 0) {
								strcpy(cbfuncName, states[nstate].entry[kopen].sopen[k].viewname);
								return states[nstate].stateid;
							}
						}
					}
				}
			}
			nnstate = nstate;
			do {
				if (states[nnstate].itran > 0)
					nnstate = nextid(states[nnstate].trans[0].trantarget);
			} while (strcmp(states[nnstate].statetype, "view") &&
				strcmp(states[nnstate].statetype, "final") &&
				strcmp(states[nnstate].statetype, "initial") &&
				strcmp(states[nnstate].statetype, "condition"));
			if (strcmp(states[nnstate].statetype, "condition") == 0) {
				for (j = 0; j < states[nnstate].ientry; j++) {
					nstate = nnstate;
					for (k = 0; k < states[nnstate].entry[j].icompcond; k++) {
						bufp = setcond(nnstate, j, k);
						if (strlen(bufp) > 2) {
							fprintf(output, "%s\n", bufp);
							indents++;
							fprintf(output, "%s", indentstr());
						}
						nstate2 = setnext(nnstate, j, (char*)"true", k);
						setothers(nnstate, j, k);
						if (nstate == nstate2) {
							nstate2 = getsaved();
						}
						nstate = nstate2;
						if (nstate == 0 && strcmp(states[nstate].statetype, "view") == 0) {
							mytag = (char*)"view";
							nnstate = nstate;
							elseset = 1;
						}
						braket++;
						condset = 1;
						break;
					}
				}
			}
			if (strcmp(states[nnstate].statetype, "view") == 0) {
				int kz, kopen = openVarmi(nnstate);
				if (kopen >= 0) {
					for (kz = 0; kz < states[nnstate].entry[kopen].iopen; kz++) {
						if (states[nnstate].entry[kopen].sopen[kz].viewname && 
							strcmp(states[nnstate].entry[kopen].sopen[kz].viewname, "filler")) {
							strcpy(cbfuncName, states[nnstate].entry[kopen].sopen[kz].viewname);
							return states[nnstate].stateid;
						}
					}
				}
			}
			if (strcmp(states[nnstate].statetype, "initial") == 0) {
				strcpy(cbfuncName, "Index");
				return states[nnstate].stateid;
			}
			if (strcmp(states[nnstate].statetype, "final") == 0) {
				strcpy(cbfuncName, "final");
				return states[nnstate].stateid;
			}
		}
	}
	return 0;
}


void writeStates(char *prog, char *sname, char *areaName)
{
	int  i, j, ii, jj, k, i2, inext;
	int  indexmi;
	char* pstate, * ptype;
	char* p, * p1, * pp, * px;
	char savednext[100];
	char* carr = (char *) "abcdefghjklmno";
	indents = 1;
	savednext[0] = 0;
	fprintf(output, "%s", indentstr());
	for (i = 0; i < istate; i++) {
		states[i].stateid = buyukHarf(states[i].stateid);
		states[i].stateid = myReplace(states[i].stateid, ' ', '_');
		states[i].stateid = myReplace(states[i].stateid, '-', '_');
		if (strncmp(states[i].statetype, "initial", 7) == 0) {
			fprintf(output, "public %sFlow()\n", sname);
			fprintf(output, "%s", indentstr());
			fprintf(output, "    : base(%s)\n", states[i].stateid);
			fprintf(output, "%s", indentstr());
			fprintf(output, "  {\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "  }\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "public %sFlow(SerializationInfo info, StreamingContext context)\n", buyukHarf(prog));
			fprintf(output, "%s", indentstr());
			fprintf(output, "    : base(info, context)\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "{\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "}\n");
			break;
		}
	}
	/* ******************************************************
	fprintf(output,"%s", indentstr());
	******************************************************* */
	indents--;
	fprintf(output, "%s", indentstr());
	fprintf(output, "   public override void ConfigureFlow()\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "   {\n");
	indents++;
	indents++;
	fprintf(output, "%s", indentstr());
	for (i = 0; i < istate; i++) {
		if (strncmp(states[i].statetype, "final", 5) == 0)
			finals(i);
		if (strncmp(states[i].statetype, "initial", 7) == 0)
			initMonetary(i);
		if (strncmp(states[i].statetype, "view", 4) == 0)
			views(i, 1);
	}
	indents--;
	fprintf(output, "%s", indentstr());
	fprintf(output, "}\n");
	globalvar = 0;
	indents = 2;
	fprintf(output, "%s", indentstr());
	fprintf(output, "public string SelectScreen()\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "{\n");
	for (i = 0; i < iflowfunc; i++) {
		pstate = states[flowii[i]].stateid;
		ptype = states[flowii[i]].statetype;

		indents++;
		pp = getOnlyView(i);
		if (i == 0) {
			fprintf(output, "%s", indentstr());
			if (strcmp(ptype, (char*)"initial") == 0)
				fprintf(output, "var detail = GetViewDetail(%sConstants.FlowView.ViewIndex);\n", tranname);
			else fprintf(output, "var detail = GetViewDetail(%sConstants.FlowView.%s);\n", tranname, pstate);
			fprintf(output, "%s", indentstr());
			fprintf(output, "var model = gdetail.Model as %sViewModel;\n", tranname);
			fprintf(output, "%s", indentstr());
			fprintf(output, "if(model != null)\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "{\n");
			indents++;
		}
		else {
			if (condset) {
				fprintf(output, "}\n");
				condset = 0;
				fprintf(output, "%s", indentstr());
			}
		}
		ii = getnState(pp);
		i2 = ii / 1000;
		jj = ii - i2 * 1000;
		j = jj / 100;
		k = jj - j * 100;
		fprintf(output, "%s", indentstr());
		fprintf(output, "if(model.fcall == %s) {\n", initVariables(savednext));
		indents++;
		for (j = jj; j < states[i2].itran; j++) {
			p = strstr(states[i2].trans[j].tranid, ".");
			if (p) p++;
			else p = states[i2].trans[j].tranid;
			p1 = p;
			p = strstr(p1, ".");
			if (p)* p = 0;
			if (strcmp(p1, "OK") == 0 || strcmp(p1, "ERROR") == 0) continue;
			fprintf(output, "%s", indentstr());
			if (constVariables(p1))
				fprintf(output, "if(model.CommandTag == %s) {\n", constVariables(p1));
			else fprintf(output, "if(model.CommandTag == %s) {\n", initVariables(p1));
			indents++;
			fprintf(output, "%s", indentstr());
			if (states[i2].trans[j].closes) {
				if (strstr(states[i2].trans[j].closes, "close")) {
					inext = nState(states[i2].trans[j].trantarget);
					px = flowgetView(inext, j, p1);
					if (px == NULL)
						px = (char*)"ViewIndex";
					if (condset == 1) {
						fprintf(output, "%s", indentstr());
						if (constVariables(p1))
							fprintf(output, "model.Actiontag = %s;\n", constVariables(p1));
						else fprintf(output, "model.actiontag = %s;\n", initVariables(p1));
						fprintf(output, "%s", indentstr());
						if (strcmp(p1, "BACKWARD") == 0 || strcmp(p1, "FORWARD") == 0)
							fprintf(output, "model.fcall = %s;\n", initVariables(savednext));
						else {
							if (strcmp(p1, "ESC") == 0)
								fprintf(output, "model.Fcall = %s;\n", initVariables((char*)"\"\""));
							else {
								fprintf(output, "model.fcall = %s;\n", initVariables(states[i2].trans[j].trantarget));
								strcpy(savednext, states[i2].trans[j].trantarget);
							}
						}
						//fprintf(output, "%s", indentstr());
						//fprintf(output, "AddVariableToFlow<%sViewModel>(new KeyValuePair<string, %sViewModel>(%sConstants.FlowView.Models, model))\n;",
						//	tranname, tranname, tranname);
						fprintf(output, "%s", indentstr());
						fprintf(output, "return %sConstants.FlowView.%s; // Call %s in CB\n",
							tranname, px, states[i2].trans[j].trantarget);
						cbfuncCall(px, p1, states[i2].trans[j].trantarget);
					}
					else {
						if (condset == 1)
							fprintf(output, "%s", indentstr());
						if (constVariables(p1))
							fprintf(output, "model.Actiontag = %s;\n", constVariables(p1));
						else fprintf(output, "model.Actiontag = %s;\n", initVariables(p1));
						fprintf(output, "%s", indentstr());
						if (strcmp(p1, "BACKWARD") == 0 || strcmp(p1, "FORWARD") == 0)
							fprintf(output, "model.Fcall = %s;\n", initVariables((char*) "\"\""));
						else {
							fprintf(output, "model.Fcall = %s;\n", initVariables(states[i2].trans[j].trantarget));
							strcpy(savednext, states[i2].trans[j].trantarget);
						}
						//fprintf(output, "%s", indentstr());
						//fprintf(output, "AddVariableToFlow<%sViewModel>(new KeyValuePair<string, %sViewModel>(%sConstants.FlowView.Models, model));\n",
						//	tranname, tranname, tranname);
						fprintf(output, "%s", indentstr());
						if (px == NULL)
							px = (char*)"ViewIndex";
						fprintf(output, "return %sConstants.FlowView.%s; // Call %s in CB\n",
							tranname, px, states[i2].trans[j].trantarget);
						cbfuncCall(px, p1, states[i2].trans[j].trantarget);
					}
				}
				fprintf(output, "%s", indentstr());
				fprintf(output, "}\n");
				globalvar = 0;
			}
			else {
				px = flowgetView(i2, j, p1);
				if (px == NULL)
					px = (char*)"ViewIndex";
				fprintf(output, "%s", indentstr());
				if (constVariables(p1))
					fprintf(output, "model.Actiontag = %s);\n", constVariables(p1));
				else fprintf(output, "model.Actiontag = %s);\n", initVariables(p1));
				fprintf(output, "%s", indentstr());
				fprintf(output, "model.Fcall = %s;\n", initVariables(states[i2].trans[j].trantarget));
				strcpy(savednext, states[i2].trans[j].trantarget);
				//fprintf(output, "%s", indentstr());
				//fprintf(output, "AddVariableToFlow<%sViewModel>(new KeyValuePair<string, %sViewModel>(%sConstants.FlowView.Models, model));\n",
				//	tranname, tranname, tranname);
				cbfuncCall(px, p1, px);
				if (braket == 0 && elseset == 0) {
					fprintf(output, "%s}\n", indentstr());
					braket--;
				}
				if (braket == 0 && elseset == 1) {
					fprintf(output, "%s} else {\n", indentstr());
				}
			}
			indents--;
			if (elseset) {
				fprintf(output, "%s", indentstr());
				fprintf(output, "}\n");
				elseset = 0;
			}
			if (condset) {
				fprintf(output, "%s", indentstr());
				fprintf(output, "%s}\n", indentstr());
				condset = 0;
			}
		}
		indents--;
		elseset = 0;
		braket = 0;
		if (condset == 0) {
			fprintf(output, "%s", indentstr());
			fprintf(output, "}\n");
			indents--;
		}
	}
	fprintf(output, "%s", indentstr());
	fprintf(output, "}\n");
	indents--;
	if (bufpset) {
		fprintf(output, "%s", indentstr());
		fprintf(output, "}\n");
		indents--;
	}
	bufpset = 0;
	//saveGlobal();
	fprintf(output, "%s", indentstr());
	fprintf(output, "return %sConstants.FlowView.ViewIndex;\n", tranname);
	indents--;
	fprintf(output, "%s", indentstr());
	fprintf(output, "}\n");

	//indents = 1;
	//fprintf(output, "%s", indentstr());
	//fprintf(output, "public string GetVar(string ldata)\n");
	//fprintf(output, "%s", indentstr());
	//fprintf(output, "{\n");
	//indents++;
	//fprintf(output, "%s", indentstr());
	//fprintf(output, "reurn GetVariableFromFlow<string>(ldata);\n");
	//indents--;
	//fprintf(output, "%s", indentstr());
	//fprintf(output, "}\n");

	indents = 1;
	fprintf(output, "%s", indentstr());
	fprintf(output, "public override void ConfigureViews()\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "{\n");
	indents++;
	itekekran = 0;
	indexmi = 0;
	for (i = 0; i < istate; i++) {
		if (strncmp(states[i].statetype, "view", 4) == 0) {
			char viewn[100];
			int kz, kopen = openVarmi(i);
			if (strcmp(initname, states[i].stateid) == 0) continue;
			viewn[0] = 0;
			if (kopen >= 0) {
				for (kz = 0; kz < states[i].entry[kopen].iopen; kz++) {
					if (states[i].entry[kopen].sopen[kz].viewname) {
						strcpy(viewn, states[i].entry[kopen].sopen[kz].viewname);
						break;
					}
				}
			}
			if (tekEkranmi(viewn) == 0) {
				if (strcmp(indexname, viewn) == 0)
					indexmi = 1;
				fprintf(output, "%s", indentstr());
				fprintf(output, "Views.Add(%sConstants.FlowView.%s, new PageFlowState\n",
					tranname, states[i].stateid);
				fprintf(output, "%s", indentstr());
				fprintf(output, "{\n");
				indents++;
				fprintf(output, "%s", indentstr());
				fprintf(output, "Action = %sConstants.FlowView.%s,\n", sname, states[i].stateid);
				fprintf(output, "%s", indentstr());
				fprintf(output, "Controller = %sConstants.FlowView.vcontroller,\n", sname);
				fprintf(output, "%s", indentstr());
				fprintf(output, "DisplayName = \"%s - %s\",\n",
					prog, viewBak(states[i].stateid));
				fprintf(output, "%s", indentstr());
				fprintf(output, "Area = ModuleConstants.AreaName, \n");
				fprintf(output, "%s", indentstr());
				fprintf(output, "Name = %sConstants.FlowView.%s\n", sname, states[i].stateid);
				indents--;
				fprintf(output, "%s", indentstr());
				fprintf(output, "});\n");
			}
		}
	}
	if (indexmi == 0) {
		fprintf(output, "%s", indentstr());
		fprintf(output, "Views.Add(%sConstants.FlowView.ViewIndex, new PageFlowState\n",
			tranname);
		fprintf(output, "%s", indentstr());
		fprintf(output, "{\n");
		indents++;
		fprintf(output, "%s", indentstr());
		fprintf(output, "Action = %sConstants.FlowView.ViewIndex,\n", sname);
		fprintf(output, "%s", indentstr());
		fprintf(output, "Controller = %sConstants.FlowView.vcontroller,\n", sname);
		fprintf(output, "%s", indentstr());
		fprintf(output, "DisplayName = \"%s - %s\",\n",
			prog, indexname);
		fprintf(output, "%s", indentstr());
		fprintf(output, "Area = ModuleConstants.AreaName, \n");
		fprintf(output, "%s", indentstr());
		fprintf(output, "Name = %sConstants.FlowView.ViewIndex\n", sname);
		indents--;
		fprintf(output, "%s", indentstr());
		fprintf(output, "});\n");
	}
	// global model icin ekran tanimi
	fprintf(output, "%s", indentstr());
	fprintf(output, "Views.Add(%sConstants.FlowView.Models, new PageFlowState\n",
		tranname);
	fprintf(output, "%s", indentstr());
	fprintf(output, "{\n");
	indents++;
	fprintf(output, "%s", indentstr());
	fprintf(output, "Action = %sConstants.FlowView.Models,\n", sname);
	fprintf(output, "%s", indentstr());
	fprintf(output, "Controller = %sConstants.FlowView.vcontroller,\n", sname);
	fprintf(output, "%s", indentstr());
	fprintf(output, "DisplayName = \"%s - globals\",\n", prog);
	fprintf(output, "%s", indentstr());
	fprintf(output, "Area = ModuleConstants.AreaName, \n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "Name = %sConstants.FlowView.Models\n", sname);
	indents--;
	fprintf(output, "%s", indentstr());
	fprintf(output, "});\n");

	fprintf(output, "%s", indentstr());
	fprintf(output, "Views.Add(%sConstants.FlowView.final, new PageFlowState\n",
		tranname);
	fprintf(output, "{\n");
	indents++;
	fprintf(output, "%s", indentstr());
	fprintf(output, "Action = %sConstants.FlowView.final,\n", sname);
	fprintf(output, "%s", indentstr());
	fprintf(output, "Controller = %sConstants.FlowView.vcontroller,\n", sname);
	fprintf(output, "%s", indentstr());
	fprintf(output, "DisplayName = \"%s - final\",\n", prog);
	fprintf(output, "%s", indentstr());
	fprintf(output, "Area = ModuleConstants.AreaName, \n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "Name = %sConstants.FlowView.final\n", sname);
	indents--;
	fprintf(output, "%s", indentstr());
	fprintf(output, "});\n");

	indents--;
	fprintf(output, "%s", indentstr());
	fprintf(output, "}\n");

	indents = 1;
	fprintf(output, "%s", indentstr());
	fprintf(output, "public override void ConfigureSubFlows()\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "{\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "}\n");
	indents = 1;
	fprintf(output, "%s", indentstr());
	fprintf(output, "}\n");
	indents--;
	fprintf(output, "%s", indentstr());
	fprintf(output, "}\n");
}

char *laststr(char *p, char *st)
{
	char *p1 = p;
	char *px = NULL;
	while (*p1) {
		while (*p1 && *p1 != st[0]) p1++;
		if (*p1) {
			px = p1;
			p1++;
		}
	}
	return px;
}

void filesOku(char *progfile, char *tran)
{
	FILE *ff;
	char *p;
	char bf[INMAX + 1];
	char mcafile[200], viewfile[200];
	ff = fopen(progfile, "r");
	if (ff) {
		while (fgets(bf, INMAX, ff)) {
			rmnl(bf);
			if (strncmp(bf, "MCA ", 4) == 0) {
				strcpy(mcafile, progfile);
				p = laststr(mcafile, "\\");
				if (p) {
					p++; *p = 0;
				}
				strcat(mcafile, bf + 4);
				readMCA(mcafile);
			}
			else {
				strcpy(viewfile, progfile);
				p = laststr(viewfile, "\\");
				if (p) {
					p++; *p = 0;
				}
				strcat(viewfile, bf + 5);
				readView(viewfile);
			}
		}
		fclose(ff);
	}
	else {
		fprintf(stderr, "Error: %s file not found\n", progfile);
		exit(0);
	}
}

void mapperHeader(char *fdir, char *tranName, char *fname, char *areaname)
{
	fprintf(output, "using System;\n");
	fprintf(output, "using System.Collections.Generic;\n");
	fprintf(output, "using System.Linq;\n");
	fprintf(output, "using AkbankFace.Web.Common;\n");
	fprintf(output, "using AkbankFace.Web.%s.Contracts;\n", areaname);
	fprintf(output, "using AkbankFace.Web.%s.Models;\n", areaname);
	fprintf(output, "using AkbankFace.Common;\n");
	fprintf(output, "using AkbankFace.Common.Interfaces;\n");
	fprintf(output, "using System.Text.RegularExpressions;\n");
	fprintf(output, "using System.Globalization;\n");
	fprintf(output, "using AkbankFace.Web.Common;\n");
	fprintf(output, "using AkbankFace.Web.Common.Interfaces;\n");
	fprintf(output, "using System.Xml.Serialization;\n");
	fprintf(output, "using System.IO;\n");
	fprintf(output, "using AkbankFace.Web.%s.Models; \n", areaname );
	fprintf(output, "using AkbankFace.Web.Contracts;\n");
	fprintf(output, "using AkbankFace.%s.Contracts;\n", areaname);
	fprintf(output, "using AkbankFace.Web.Shell.Models;\n");
	fprintf(output, "using AkbankFace.Web.Shell.Common;\n");
	fprintf(output, "using AkbankFace.Web.Contracts;\n");
	fprintf(output, "using Microsoft.Ajax.Utilities;\n");
	fprintf(output, "using AkbankFace.BranchBanking.Common;\n");
	fprintf(output, "using Newtonsoft.Json;\n");
	fprintf(output, "using AkbankFace.Web.%s.ClientBusiness.Helpers;\n\n", areaname);

	fprintf(output, "namespace AkbankFace.Web.%s.ClientBusiness\n", areaname);
	fprintf(output, "{\n");
	fprintf(output, "    public partial class %sModelMapper\n", fname);
	fprintf(output, "    {\n");
}

void mappers(char *fdir, char *progname, char *tranname, char *area)
{
	mapperHeader(fdir, tranname, progname, area);
	// ViewModelToMCA();
	// MCAToViewModel();
	fprintf(output, "}\n");
}

void readgetlist(char *gfile)
{
	FILE *fx;
	char bfx[MAXCHAR+1];
	igetlistarr = 0;
	fx = fopen(gfile, "r");
	if(fx) {
		while (fgets(bfx, MAXCHAR, fx)) {
			rmnl(bfx);
			getlistarr[igetlistarr] = (char *)calloc(1, strlen(bfx)+1);
			strcpy(getlistarr[igetlistarr], buyukHarf(bfx));
			igetlistarr++;
		}
		fclose(fx);
	}
	else fprintf(output, "file yok %s\n", gfile);
}


void readflowcall(char *fname)
{
	FILE *fx;
	char bfx[MAXCHAR + 1];
	int  i, j, buldu;
	iflowcall = 0;
	fx = fopen(fname, "r");
	if (fx) {
		while (fgets(bfx, MAXCHAR, fx)) {
			rmnl(bfx);
			mysplit(bfx, ":");
			buldu = 0;
			for (i = 0; i < iflowcall; i++) {
				if (strcmp(flowcall[i].constant, xptr[0]) == 0) {
					j = flowcall[i].jcount;
					flowcall[i].tags[j] = (char *)calloc(1, strlen(xptr[1]) + 1);
					strcpy(flowcall[i].tags[j], buyukHarf(xptr[1]));
					flowcall[i].fcall[j] = (char *)calloc(1, strlen(xptr[3]) + 1);
					strcpy(flowcall[i].fcall[j], buyukHarf(xptr[3]));
					flowcall[i].jcount++;
					buldu = 1;
					break;
				}
			}
			if (buldu == 0) {
				i = iflowcall;
				flowcall[i].constant = (char *)calloc(1, strlen(xptr[0]) + 1);
				strcpy(flowcall[i].constant, buyukHarf(xptr[0]));
				flowcall[i].funcname = (char *)calloc(1, strlen(xptr[2]) + 1);
				strcpy(flowcall[i].funcname, buyukHarf(xptr[2]));
				flowcall[i].jcount = 0;
				j = flowcall[i].jcount;
				flowcall[i].tags[j] = (char *)calloc(1, strlen(xptr[1]) + 1);
				strcpy(flowcall[i].tags[j], buyukHarf(xptr[1]));
				flowcall[i].fcall[j] = (char *)calloc(1, strlen(xptr[3]) + 1);
				strcpy(flowcall[i].fcall[j], buyukHarf(xptr[3]));
				flowcall[i].jcount++;
				iflowcall++;
			}
		}
		fclose(fx);
	}
}

void readextras(char *fname)
{
	char bufx[201];
	FILE *fx;
	fx = fopen(fname, "r");
	if (fx) {
		iextras = 0;
		while (fgets(bufx, 200, fx)) {
			rmnl(bufx);
			extras[iextras] = (char *)calloc(1, strlen(bufx) + 1);
			strcpy(extras[iextras], buyukHarf(bufx));
			iextras++;
		}
		fclose(fx);
	}
}

void cbYazdir(char *fname)
{
	int  i;
	FILE *fx;
	fx = fopen(fname, "w");
	if(fx) {
		for (i = 0; i < icbfunc; i++)
			if (cbfunc3[i] && strlen(cbfunc3[i]) > 0)
			     fprintf(fx, "%s:%s:%s:%s\n", cbfunc1[i], cbfunc4[i], cbfunc3[i], cbfunc2[i]);
			else fprintf(fx, "%s:%s: :%s\n", cbfunc1[i], cbfunc4[i], cbfunc2[i]);
		fclose(fx);
	}
	else
		fprintf(output, "olmadi %s acilamadi\n", fname);
}

void clientYaz(char *sfile)
{
	FILE *fx;
	int  i;
	fx = output;
	if (fx) {
		for (i = 0; i < ivmodel; i++) {
			if (vmodel[i].ftype != NULL)
				 fprintf(fx, "%s:%s:%s\n", vmodel[i].sid, vmodel[i].sview, vmodel[i].ftype);
			else fprintf(fx, "%s:%s:%s\n", vmodel[i].sid, vmodel[i].sview, vmodel[i].smodel);
		}
	}
	else {
		fprintf(output, "%s dosya yaratilamadi\n", sfile);
	}
}


//int serkes()
//{
//	time_t rawtime;
//	struct tm * timeinfo;
//
//	time(&rawtime);
//	timeinfo = localtime(&rawtime);
//	if (timeinfo->tm_year == 119 && timeinfo->tm_mon <= 4)  return 1;
//	return 0;
//}
extern int bakBakalim(char *, int);

int main(int argc, char **argv)
{
	FILE *fp;
	int ret;
	int  i, nproc, tag, indx, ix;
	int  procId;
	int  eprint;
	char *p, filename[300];
	char flowsname[300];
	char myarea[100];
	char progfile[200];
	char indexfile[200];
	char flowfile[200];
	char constfile[200];
	char controllerpref[200];
	char globalfile[200];
	char getlistfile[200];
	char clientname[200];
	char extrafile[200];
	char fname[200], gfile[300];

	char sname[200], stype[200], stypeid[200];

	/* get tables and coulmns of connected database */
	// SetConsoleOutputCP(CP_UTF8);
	// setvbuf(stdout, nullptr, _IOFBF, 1000);
	output = stdout;
	param = 0;
	istate = 0;
	ifuncs = 0;
	if (argc > 5) {
		param = atoi(argv[1]);
		strcpy(tranname, argv[2]);
		strcpy(myarea, argv[3]);
		strcpy(indexname, argv[4]);
		strcpy(gislem, argv[5]);
		eprint = atoi(argv[6]);
		if (eprint == 2 || eprint == 3)
			petition = 1;
		procId = atoi(argv[7]);
		nproc = atoi(argv[8]);
		strcpy(garea, myarea);
	} else {
		for (i = 0; i < argc; i++)
			fprintf(output, "%d %s, ", i, argv[i]);
		fprintf(output, "\n");
		fprintf(output, "kullanım: proc2cb [1/2/3/4] <tranid> <area> <indexname> nproc <procfiles>\n");
		fprintf(output, "    1 Debug Info\n");
		fprintf(output, "    2 <tranid>[<program>]flow.cs\n");
		fprintf(output, "    3 <tranid><program>]flow.preference\n");
		fprintf(output, "    4 PREFS<tranid>[program].file\n");
		fprintf(output, "    5 <tranid><program>]mapper.cs\n");
		fprintf(output, "    6 <tranid><program>]flow.preference\n");
		fprintf(output, "    7 <tranid><program>]client.preference\n");
		return(0);
	}
	if (bakBakalim("be1converter", procId) == 0) {
		/*for (i = 0; i < argc; i++)
			fprintf(output, "%d %s, ", i, argv[i]);*/
		return(-2);
	}
	//if(serkes() == 0) {
	//	fprintf(stderr, "hmm Olmadi...\n");
	//	exit(2);
	//}
	for (i = 0; i < nproc; i++) {
		strcpy(fname, argv[i + 9]);
		fp = fopen(fname, "r");
		if (i == 0) {
			strcpy(filename, fname);
			p = strstr(filename, "Proc.");
			*p = 0;
			p = laststr(filename, "\\");
			if (p) p++;
			else  p = filename;
			strcpy(progname, p);
			*p = 0;
			strcpy(progfile, filename);
			p = strstr(progfile, "INDIRS");
			if (p) {
				*p = 0;
			}
			strcpy(filename, progfile);
			strcpy(indexfile, filename);
			strcpy(flowfile, filename);
			strcpy(getlistfile, flowfile);
			strcat(progfile, PREFS);
			strcat(progfile, tranname);
			strcat(progfile, "\\");
			strcat(progfile, tranname);
			strcat(progfile, ".files");
			strcpy(flowsname, filename);
			strcat(flowsname, "Root\\");
			strcat(flowsname, tranname);
			strcat(flowsname, "\\");
			strcat(flowsname, tranname);
			strcat(flowsname, "Flow.cs");
			strcat(indexfile, PREFS);
			strcat(indexfile, tranname);
			strcat(indexfile, "\\");
			strcpy(extrafile, indexfile);
			strcat(indexfile, tranname);
			strcat(indexfile, "Index.txt");
			strcat(extrafile, tranname);
			strcat(extrafile, "extras.txt");

			strcat(flowfile, PREFS);
			strcat(flowfile, tranname);
			strcat(flowfile, "\\");
			strcpy(getlistfile, flowfile);
			strcat(flowfile, tranname);
			strcpy(fname, flowfile);
			strcpy(globalfile, flowfile);
			strcpy(gfile, fname);
			strcat(globalfile, "global.preference");
			strcat(fname, "flowcall.preference");
			strcpy(constfile, flowfile);
			strcpy(controllerpref, flowfile);
			strcpy(clientname, flowfile);	

			strcat(flowfile, progname);
			strcat(flowfile, "flow.preference");
			strcat(constfile, progname);
			strcat(constfile, ".constants");
			strcat(controllerpref, progname);
			strcat(controllerpref, "controller.preference");
			strcat(clientname, "client.preference");
			strcat(getlistfile, tranname);
			strcat(getlistfile, "GetList.txt");
		}
		if (fp) {
			input = fp;
			fstate = 0;
			ftrans = 0;
			fentry = 0;

			do {
				sname[0] = 0;
				stype[0] = 0;
				ret = getstate(sname, stype, stypeid);
				if (ret > 0) {
					indx = istate;
					states[indx].stateid = (char *)calloc(1, (int)strlen(sname) + 1);
					states[indx].statetype = (char *)calloc(1, (int)strlen(stype) + 1);
					strcpy(sname, myReplace(sname, ' ', '_'));
					strcpy(states[indx].stateid, buyukHarf(sname));
					strcpy(states[indx].statetype, stype);
					if (strlen(stypeid) > 0) {
						states[indx].statetypeid = (char *)calloc(1, strlen(stypeid) + 1);
						strcpy(states[indx].statetypeid, stypeid);
					}
					else
						states[indx].statetypeid = 0;
					states[indx].ientry = 0;
					states[indx].itran = 0;
					states[indx].isref = 0;
					istate++;
					if (strstr(buf, ESTATEF)) continue;
					while (getend(ESTATE, ESYNC) == EOF) {
						Processed = 1;
						tag = beginTag(PSTATE);
						switch (tag) {
						case PENTRY:
							fentry = 1;
							ix = newentry(indx);
							pentryGet(indx, ix);
							break;
						case PTRANS:
							ftrans = 1;
							ptransGet(indx);
							ftrans = 0;
							break;
						default:
							fprintf(output, "**** %s\n", buf);
							break;
						}
					}
				}
				Processed = 1;
			} while (ret != -2);
			fclose(fp);
			if (param != 3 && i == 0) {
				viewsOku(filename, progname, tranname);
				filesOku(progfile, tranname);
				readconst(flowfile, constfile);
				readcontrollers(controllerpref);
				readgetlist(getlistfile);
				readglobals(globalfile);
				readextras(extrafile);
				readcaches(gfile);
				setTranref();
				if (eprint > 0) {
					char myfile[300];
					strcpy(myfile, argv[9]);
					p = strstr(myfile, "\\INDIRS");
					if (p) {
						p++;
						*p = 0;
						if(eprint == 1 || eprint == 3)
							readslip(tranname, myfile);
						if (eprint == 2 || eprint == 3)
							readdoc(tranname, myfile);
					}
				}

			}
			switch (param) {
			case 2:
				statePrologue(progname, tranname, myarea);
				writeStates(progname, tranname, myarea);
				// pref altina cb function call bilgilerini yaz
				cbYazdir(fname);
				break;
			case 3:
				readflowcall(fname);
				writeFlows(filename, progname, tranname, myarea);
				break;
			case 4:
				readflowcall(fname);
				ClientProlog(filename, progname, tranname, myarea);
				break;
			case 41:
				readflowcall(fname);
				ClientProlog(filename, progname, tranname, myarea);
				break;
			case 5:
				mappers(filename, progname, tranname, myarea);
				break;
			case 6:
				writeflowPref(filename, progname, tranname, myarea);
				break;
			case 7:
				readflowcall(fname);
				getModelState();
				setfuncParams();
				clientYaz(clientname);
				break;
			default:
				writeDebug(filename, progname, tranname);
			}
		}
	}
	return 0;
}


/************************************************************
Bulduklarimi <comment> TODO: biciminde yazmaliyim

model == null sa eeklenecek new icin gerekli

*/