#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define DEBUGX
#define NDEBUGX
#define GECICI

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
#define CINITCOLL  "<initColl "
#define CRMCOLL    "<removeFromColl "
#define CRMCONTEXT "<removeFromContext "

#define EINIT      "/>"
#define EOPENX      "/>"
#define EOPEN      "</openViewAk>"
#define EACTION    "</actions>"
#define ESETVAL    "/>"
#define EDOCUMENTS "/>"
#define ETRAN      "/>"
#define ETRANF     "</transition>"
#define ESTATE     "</state>"
#define ESTATEF    "/>"
#define ETRANS     "</transitions>"
#define EENTRY     "</entryActions>"
#define ENDEXEC    "/>"

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
#define CGENEXP        "<genericExprssion"

#define CTRIMS         "<trimString "
#define CTRIMID        "id=\""
#define CTRIMVAR       "variable=\""
#define CTRIMCHAR      "trimChar=\""
#define CTRIMDIR       "direction=\""
#define ETRIM          "/>"

#define CRMCOLLID      "id=\""
#define CRMCOLLDELM    "dataelement=\""
#define CRMCOLLPOLY    "policy=\""
#define CRMCOLLREPNO   "repoNo=\""

#define CRMCONTEXTID   "id=\""
#define CRMCONTEXTDELM "dataelement=\""

#define CINITCOLLID    "id=\""
#define CINITCOLLDELM  "dataelement=\""
#define CUNSTR         "<unstring "
#define CTRACE         "<writeToTrace "
#define CTRACEID       "id=\""

#define CUNSTRSRC      "source=\""

#define PSTATE     1
#define PENTRY     10
#define PTRANS     11

#define PTRAN      12
#define PACTION    13
#define POPEN      14
#define PSETVAL    15
#define PDOCUMENTS	16
#define PINIT      17
#define PCLOSE     18
#define PTRANF     19
#define PEXEC      20
#define PCONDACT   21
#define PCONDS     22
#define PCOMPCOND  23
#define PLOGICAL   24
#define PSHOWMSG	25
#define PGETSHARE  26
#define PSETSHARE  27
#define PPAD       28
#define PCCF       29
#define PGEN		30
#define PMAES      31
#define PTRIM      32
#define PINITCOLL  33
#define PRMCOLL    34
#define PUNSTR		35
#define PGENEXP    36
#define PTRACE     37
#define PRMCONTEXT 38


#define CTRANID		"id=\""
#define CTARGET		"targetState=\""

#define CINITID		"id=\""
#define COPENID		"id=\""
#define CVIEWNAME		"viewName=\""
#define CVIEWSRC		"viewSource=\""
#define CLNKCONTEXT		"linkContextTo=\""
#define CTABINTER		"tabInterval=\""
#define CTITLE		"title=\""
#define CFOOTERMSG		"footerMessage=\""
#define CAPPROVAL    "isapprovalNecessary=\""
#define CAPPTYPE     "approvalType=\""
#define CDATAELM		"dataElements=\""
#define CDEFVAL		"defValue=\""

#define COPNAME		"opName=\""
#define CFIRSTOP		"firstOperand=\""
#define CSECONDOP		"firstOperand=\""

#define CONTRUE		"onTrue ="
#define CONFALSE		"onFalse ="

#define CGETSHAREID		"id=\""
#define CGETSHARECVAR		"contextVariable=\""
#define CGETSHAREVAR	"sharedVariable=\""

#define CSETSHAREID		"id=\""
#define CSETSHAREVAR	"sharedVariable=\""
#define CSETSHAREVAL   "value=\""

#define CPADID		"id=\""
#define CPADDNAME		"dataName=\""
#define CPADCHAR		"padCharacter=\""
#define CPADLEN		"totalLength=\""
#define CPADALIGN		"alignment=\""

#define CCFID          "id=\""
#define CCFCUST        "CustomerID=\""
#define CCFSIGN        "signal=\""

#define CGENID         "id=\""
#define CGENACC        "accountNo=\""
#define CGENBR         "branchCode=\""
#define CGENCD         "currencyCode=\""
#define CGENIBAN       "IBANaccountNo=\""

#define CGENEXPID		"expressionId=\""

#define CMAESID		"id=\""
#define CMAESDOCBR		"docBranch=\""
#define CMAESDOCDT     "docDate=\""
#define CMAESDOCMAINT  "docMaintenanceNumber=\""
#define CMAESVIEW      "viewGroupId=\""
#define CMAESDOCTYPE   "docType=\""
#define CMAESOPTYPE    "operationType=\""
#define CMAESDOCHOST   "docHostFunction=\""
#define CMAESDOCID     "docIdentityTaxNo=\""
#define CMAESDOCCUST	"docCustomerNo=\""
#define CMAESSCAN		"scanningReason=\""

#define CTRACE0        "trace0=\""
#define CTRACE1        "trace1=\""
#define CTRACE2        "trace2=\""

#define FLOW   1
#define CB     3
#define CNTRL  2

#define MAXCHAR 2000
#define VMAX  20
#define MMAX  20
#define IMAX  100
#define INMAX 200
#define SMAX  50

#define FMAX  300

#define MSMAX

#define STRINGTYPE  1
#define DATETYPE    2
#define NUMERICTYPE 3
#define OTHERTYPE   4

char buf[MAXCHAR + 1];

int petition = 0;


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
	int start;
	int len;
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
	int igenexp;
	struct GENEXP egenexp[SMAX];
	int itrace;
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

int ivmodel;
struct VMODEL {
	int  istart;
	int  is;
	char *sid;
	int  refcnt;
	char *stype;
	char *stranid[5];
	char *smodel;
	char *ftype;
	int  iptype;
	char *ptype[5];
	char *pname[5];
	char *sview;
	int  ifunc;
	char *sfunckey[12];
	char *starget[12];
} vmodel[400];

#define FMAX 300

char fbuf[FMAX + 1];
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
} constants[700];


int  ivname = 0;
struct VNAME {
	char viewname[100];
	char vrecname[100];
	char vcode[3];
	int  iarray;
	char arrayName[100];
	char arrcode[3];
} vname[VMAX];

FILE *input, *output;

int Processed = 0;
int fstate = 0;
int ftrans = 0;
int fentry = 0;
int param = 0;

char progname[200];
char tranname[200];
char indexname[200];
char areaName[200];

char firstview[200];
char *getfirstview(int);
char *getconstant(char *, char *);
void addstarters(char *);
int  vmodelVarmi(int);
int  vmodelBak(char *);
int  vmodeliiBak(char *);
char *vmodelpBak(char *);
char *myReplace(char *, char, char);

int upper(char p)
{
	if(p >= 'a' && p <= 'z')
		return ((p & 0xff) - 'a' + 'A');
	return p & 0xff;
}
int strcasecmp(char *s, char *t)
{
	char *p1, *s1;
	int  i, len = (int)strlen(t);
	p1 = (char *)calloc(1, (int)strlen(t) + 1);
	for (i = 0; i < len; i++) {
		if (p1) {
			p1[i] = upper(t[i]) &0xff;
			p1[i + 1] = NULL;
		}
	}
	len = (int)strlen(s);
	s1 = (char *)calloc(1, int(strlen(s) + 1));
	for (i = 0; i < len; i++) {
		if (s1) {
			s1[i] = upper(s[i]) & 0xff;
			s1[i + 1] = NULL;
		}
	}
	return (p1 && s1) ? strcmp(p1, s1) : -1;
}

int strncasecmp(char *p, char *s, int n)
{
	int i, k;
	for (i = 0; i < n; i++) {
		k = upper(p[i]) - upper(s[i]);
		if (k != 0)
			return k;
	}
	return 0;
}

int buyukh(char s)
{
	if (s >= 'a' && s <= 'z')
		return s - 'a' + 'A';
	return s;
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

char *buyukHarf(char *s)
{
	char *p = (char *)calloc(1, strlen(s) + 1);
	if (p) {
		strcpy(p, s);
		if (p[0] >= 'a' && p[0] <= 'z') {
			p[0] = p[0] - 'a' + 'A';
		}
	}
	return p;
}

char *kucukHarf(char *s)
{
	char *p = (char *)calloc(1, strlen(s) + 1);
	if (p) {
		strcpy(p, s);
		if (p[0] >= 'A' && p[0] <= 'Z') {
			p[0] = p[0] - 'A' + 'a';
		}
	}
	return p;
}

char indent[200];
int  indents = 0;

char *indentstr()
{
	int i;
	indent[0] = 0;
	for (i = 0; i<indents; i++) {
		strcat(indent, "   ");
	}
	return indent;
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
		if (!((*p1 == '/' || *(p1+1) == '*') ||
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

int getstate(char *sn, char *st, char* stid)
{
	char sbuf[3000];
	char *p, *p1;
	int ret;
	if ((ret = mygetline((char *)CSTATE, (char *)CSYNC)) > 0) {
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
					while (*p1 && *p1 != '"') p++;
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
			if (strncasecmp(p, ETRANF,(int)strlen(ETRANF)) == 0) return PTRANF;
			return EOF;
		}
		if (tag == PSTATE) {
			if (strncasecmp(p, CENTRY,(int)strlen(CENTRY)) == 0) return PENTRY;
			if (strncasecmp(p, CTRANS,(int)strlen(CTRANS)) == 0) return PTRANS;
			return 96;
		}
		if (tag == PENTRY) {
			if (strncasecmp(p, CEXEC,(int)strlen(CEXEC)) == 0) return PEXEC;
			if (strncasecmp(p, CINIT,(int)strlen(CINIT)) == 0) return PINIT;
			if (strncasecmp(p, COPEN,(int)strlen(COPEN)) == 0) return POPEN;
			if (strncasecmp(p, CSETVAL,(int)strlen(CSETVAL)) == 0) return PSETVAL;
			if (strncasecmp(p, CDOCUMENTS,(int)strlen(CDOCUMENTS)) == 0)
				return PDOCUMENTS;
			if (strncasecmp(p, CCONDACT,(int)strlen(CCONDACT)) == 0) return PCONDACT;
			if (strncasecmp(p, CSHOWMSG,(int)strlen(CSHOWMSG)) == 0) return PSHOWMSG;
			if (strncasecmp(p, CGETSHARE,(int)strlen(CGETSHARE)) == 0)
				return PGETSHARE;
			if (strncasecmp(p, CSETSHARE,(int)strlen(CSETSHARE)) == 0)
				return PSETSHARE;
			if (strncasecmp(p, CCF,(int)strlen(CCF)) == 0) return PCCF;
			if (strncasecmp(p, CPAD,(int)strlen(CPAD)) == 0) return PPAD;
			if (strncasecmp(p, CGEN,(int)strlen(CGEN)) == 0) return PGEN;
			if (strncasecmp(p, CMAES,(int)strlen(CMAES)) == 0) return PMAES;
			if (strncasecmp(p, CTRIMS,(int)strlen(CTRIMS)) == 0) return PTRIM;
			if (strncasecmp(p, CINITCOLL,(int)strlen(CINITCOLL)) == 0) return PINITCOLL;
			if (strncasecmp(p, CRMCOLL,(int)strlen(CRMCOLL)) == 0) return PRMCOLL;
			if (strncasecmp(p, (char *)CUNSTR, (int)strlen(CUNSTR)) == 0) return PUNSTR;
			if (strncasecmp(p, (char *)CTRACE, (int)strlen(CTRACE)) == 0) return PTRACE;

			return 98;
		}
		if (tag == PTRANS) {
			if (strncasecmp(p, CTRAN,(int)strlen(CTRAN)) == 0) return PTRAN;
			if (strncasecmp(p, CACTION,(int)strlen(CACTION)) == 0) return PACTION;
			return 99;
		}
		if (tag == PACTION) {
			if (strncasecmp(p, CCLOSE,(int)strlen(CCLOSE)) == 0) return PCLOSE;
			return 96;
		}
		if (tag == PCONDACT) {
			if (strncasecmp(p, CCONDS,(int)strlen(CCONDS)) == 0) return PCONDS;
			return 95;
		}
		if (tag == PCONDS) {
			if (strncasecmp(p, CCOMPCOND,(int)strlen(CCOMPCOND)) == 0)
				return PCOMPCOND;
			return 94;
		}
		return 97;
	}
	return EOF;
}

int getend(char *estr, int tt)
{
	int ret;
	Processed = 1;
	ret = mygetline(CDUMMY, CSYNC);
	if (ret != -2) {
		if (strstr(buf, estr))
			return true;
		if (tt && strstr(buf, "/>"))
			return true;
		ret = EOF;
	}
	return ret;
}

int traninfo(char *tranid, char *nstate)
{
	char *p, *p1;
	char sbuf[3000];
	strcpy(sbuf, buf);
	p = strstr(buf, CTRANID);
	if (p) {
		p = p +(int)strlen(CTRANID);
		p1 = p;
		while (*p && *p != '\"') p++;
		*p = 0;
		strcpy(tranid, p1);
		p++;
	}
	else p = buf;
	p = strstr(p, CTARGET);
	if (p) {
		p = p +(int)strlen(CTARGET);
		p1 = p;
		while (*p && *p != '\"') p++;
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
		if (strlen(tranid)) {
			states[indx].trans[iy].tranid = (char *) calloc(1,(int)strlen(tranid) + 1);
			strcpy(states[indx].trans[iy].tranid, tranid);
		}
		else states[indx].trans[iy].tranid = 0;
		if (strlen(nstate)) {
			states[indx].trans[iy].trantarget = (char *) calloc(1,(int)strlen(nstate) + 1);
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
	while (getend(ETRANS, 0) == EOF) {
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
			while (getend(EACTION, 0) == EOF) {
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
							(char *) calloc(1,(int)strlen(strclose) + 1);
						strcpy(states[indx].trans[ix].closes, strclose);
					}
				}
			}
			break;
		}
	}
}

char *params(char *mtarget, char *p, char *ss, char c, char *txt)
{
	char sbuf[2000];
	char cstr[4];
	char* p1;
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
		if (p) {
			p1 = p + 12;
			p = strstr(p1, ")");
			if (p) *p = 0;
			strcpy(mtarget, p1);
		}
		else {
			strcpy(mtarget, p1);
			p = p1;
		}
	}
	else { mtarget[0] = 0; p = buf; }
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
	while (getend(EBUTTONL, 0) == EOF) {
		if (strstr(buf, CFOOTER)) {
			strcpy(sbuf, buf);
			p = params(text, buf, CTEXT, '"', "FOOTER TEXT");
			p = params(tabOrder, buf, CTABORDER, '"', "FOOTER TABORDER");
			p = params(lastStep, buf, CLASTSTEP, '"', "FOOTER LASTSTEP");
			p = params(visible, buf, CVISIBLE, '"', "FOOTER VISIBLE");
			strcpy(buf, sbuf);
			iz = states[indx].entry[ix].sopen[iy].ibuttons;
			if (strlen(text)) {
				states[indx].entry[ix].sopen[iy].buttons[iz].buttontext =
					(char *) calloc(1,(int)strlen(text) + 1);
				strcpy(states[indx].entry[ix].sopen[iy].buttons[iz].buttontext,
					text);
			}
			if (strlen(tabOrder)) {
				iz = states[indx].entry[ix].sopen[iy].ibuttons;
				states[indx].entry[ix].sopen[iy].buttons[iz].buttontabOrder =
					(char *) calloc(1,(int)strlen(tabOrder) + 1);
				strcpy(states[indx].entry[ix].sopen[iy].buttons[iz].buttontabOrder, tabOrder);
			}
			if (strlen(lastStep)) {
				iz = states[indx].entry[ix].sopen[iy].ibuttons;
				states[indx].entry[ix].sopen[iy].buttons[iz].buttonlastStep =
					(char *) calloc(1,(int)strlen(lastStep) + 1);
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
	p = params(sapproval, p, (char *)CAPPROVAL, '"', (char *)"OPEN APPROVAL");
	p = params(sapptype, p, (char *)CAPPTYPE, '"', (char *)"OPEN APPTYPE");
	iy = states[indx].entry[ix].iopen;
	if (iy == 0) {
		states[indx].entry[ix].sopen[iy].ibuttons = 0;
	}
	if (strlen(strinit)) {
		states[indx].entry[ix].sopen[iy].openid =
			(char *) calloc(1,(int)strlen(strinit) + 1);
		strcpy(states[indx].entry[ix].sopen[iy].openid, buyukHarf(strinit));
	}
	if (strlen(strvname)) {
		states[indx].entry[ix].sopen[iy].viewname =
			(char *) calloc(1,(int)strlen(strvname) + 1);
		strcpy(states[indx].entry[ix].sopen[iy].viewname, buyukHarf(strvname));
	}
	if (strlen(strvsrc)) {
		states[indx].entry[ix].sopen[iy].viewsrc =
			(char *) calloc(1,(int)strlen(strvsrc) + 1);
		strcpy(states[indx].entry[ix].sopen[iy].viewsrc, buyukHarf(strvsrc));
	}
	if (strlen(sapproval)) {
		states[indx].entry[ix].sopen[iy].approval = false;
		if (strcmp(sapproval, "true") == 0)
			states[indx].entry[ix].sopen[iy].approval = true;
	}
	else
		states[indx].entry[ix].sopen[iy].approval = false;
	if (strlen(sapptype)) {
		states[indx].entry[ix].sopen[iy].apptype = atoi(sapptype);
	}
	else
		states[indx].entry[ix].sopen[iy].apptype = 0;
	if (strlen(strlnk)) {
		states[indx].entry[ix].sopen[iy].lnkcontext =
			(char *) calloc(1,(int)strlen(strlnk) + 1);
		strcpy(states[indx].entry[ix].sopen[iy].lnkcontext, strlnk);
	}
	if (strlen(strtab)) {
		states[indx].entry[ix].sopen[iy].tabinter =
			(char *) calloc(1,(int)strlen(strtab) + 1);
		strcpy(states[indx].entry[ix].sopen[iy].tabinter, strtab);
	}
	if (strlen(strtitle)) {
		states[indx].entry[ix].sopen[iy].title =
			(char *) calloc(1,(int)strlen(strtitle) + 1);
		strcpy(states[indx].entry[ix].sopen[iy].title, buyukHarf(strtitle));
	}
	if (strlen(strfooter)) {
		states[indx].entry[ix].sopen[iy].footermsg =
			(char *) calloc(1,(int)strlen(strfooter) + 1);
		strcpy(states[indx].entry[ix].sopen[iy].footermsg, buyukHarf(strfooter));
	}
	states[indx].entry[ix].iopen++;
	strcpy(buf, sbuf);
}

void setvalGet(int indx, int ix)
{
	char *p;
	char dataelm[200];
	char mdefval[200];
	char ebuf[2000];
	int iy;
	strcpy(ebuf, buf);
	p = params(dataelm, buf, CDATAELM, '"', "SETVAL DATAELM");
	p = params(mdefval, buf, CDEFVAL, '"', "SETVAL DEFVALUE");
	iy = states[indx].entry[ix].isetval;
	if (strlen(dataelm)) {
		states[indx].entry[ix].esetval[iy].dataelm =
			(char *) calloc(1,(int)strlen(dataelm) + 1);
		strcpy(states[indx].entry[ix].esetval[iy].dataelm, buyukHarf(dataelm));
	}
	if (strlen(mdefval)) {
		states[indx].entry[ix].esetval[iy].defval =
			(char *) calloc(1,(int)strlen(mdefval) + 1);
		strcpy(states[indx].entry[ix].esetval[iy].defval, buyukHarf(mdefval));
	}
	states[indx].entry[ix].isetval++;
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
	if (strlen(execid)) {
		states[indx].entry[ix].eexec[iy].execid =
			(char *) calloc(1,(int)strlen(execid) + 1);
		strcpy(states[indx].entry[ix].eexec[iy].execid, buyukHarf(execid));
	}
	if (strlen(execop)) {
		states[indx].entry[ix].eexec[iy].execop =
			(char *) calloc(1,(int)strlen(execop) + 1);
		strcpy(states[indx].entry[ix].eexec[iy].execop, buyukHarf(execop));
	}
	if (strlen(execmon)) {
		states[indx].entry[ix].eexec[iy].execmon =
			(char *) calloc(1,(int)strlen(execmon) + 1);
		strcpy(states[indx].entry[ix].eexec[iy].execmon, execmon);
	}
	if (strlen(execlast)) {
		states[indx].entry[ix].eexec[iy].execlast =
			(char *) calloc(1,(int)strlen(execlast) + 1);
		strcpy(states[indx].entry[ix].eexec[iy].execlast, execlast);
	}
	if (strlen(execmaint)) {
		states[indx].entry[ix].eexec[iy].execmaint =
			(char *) calloc(1,(int)strlen(execmaint) + 1);
		strcpy(states[indx].entry[ix].eexec[iy].execmaint, execmaint);
	}
	if (strlen(execappr)) {
		states[indx].entry[ix].eexec[iy].execappr =
			(char *) calloc(1,(int)strlen(execappr) + 1);
		strcpy(states[indx].entry[ix].eexec[iy].execappr, execappr);
	}
	if (strlen(execlnk)) {
		states[indx].entry[ix].eexec[iy].execlnk =
			(char *) calloc(1,(int)strlen(execlnk) + 1);
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
	if (strlen(onTrue)) {
		strcpy(onTrue, myReplace(onTrue, ' ', '_'));
		states[indx].entry[ix].ecompcon[iy].onTrue =
			(char *) calloc(1,(int)strlen(onTrue) + 1);
		strcpy(states[indx].entry[ix].ecompcon[iy].onTrue, onTrue);
	}
	if (strlen(onFalse) && strcmp(onFalse, "continue")) {
		strcpy(onTrue, myReplace(onFalse, ' ', '_'));
		states[indx].entry[ix].ecompcon[iy].onFalse =
			(char *) calloc(1,(int)strlen(onFalse) + 1);
		strcpy(states[indx].entry[ix].ecompcon[ix].onFalse, onFalse);
	}
	states[indx].entry[ix].ecompcon[iy].ilogical = 0;
	while (getend(ECOMPCOND, 0) == EOF) {
		p = strstr(buf, CLOGICAL);
		if (p) {
			strcpy(sbuf, buf);
			p = params(opname, buf, COPNAME, '"', "LOGICAL OPNAME");
			p = params(firstop, buf, CFIRSTOP, '"', "LOGICAL FIRSTOP");
			p = params(secondop, buf, CSECONDOP, '"', "LOGICAL SECONDOP");
			iz = states[indx].entry[ix].ecompcon[iy].ilogical;
			if (strlen(opname)) {
				states[indx].entry[ix].ecompcon[iy].logical[iz].opname =
					(char *) calloc(1,(int)strlen(opname) + 1);
				strcpy(states[indx].entry[ix].ecompcon[iy].logical[iz].opname, buyukHarf(opname));
			}
			if (strlen(firstop)) {
				states[indx].entry[ix].ecompcon[iy].logical[iz].firstop =
					(char *) calloc(1,(int)strlen(firstop) + 1);
				strcpy(states[indx].entry[ix].ecompcon[iy].logical[iz].firstop, buyukHarf(firstop));
			}
			if (strlen(secondop)) {
				states[indx].entry[ix].ecompcon[iy].logical[iz].secondop =
					(char *) calloc(1,(int)strlen(secondop) + 1);
				strcpy(states[indx].entry[ix].ecompcon[iy].logical[iz].secondop, buyukHarf(secondop));
			}
			strcpy(buf, sbuf);
			states[indx].entry[ix].ecompcon[iy].ilogical++;
		}
	}
	states[indx].entry[ix].icompcond++;
}

void getConds(int indx, int ix)
{
	int tag;

	while (getend(ECONDS, 0) == EOF) {
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

	while (getend(ECONDACT, 0) == EOF) {
		tag = beginTag(PCONDACT);
		switch (tag) {
		case PCONDS:
			getConds(indx, ix);
			break;

		}
	}
}

char Msgval[2000];

void getshowMsg(int indx, int ix)
{
	int  iy;
	char *id;
	char *message;
	char *title;
	char *messageType;
	char *optionType;
	char *defaults;
	char *p, sbuf[2000];
	strcpy(sbuf, buf);
	id = Msgval;
	//message = (char*)calloc(1, 3001);
	//title = (char*)calloc(1, 3001);
	//messageType = (char*)calloc(1, 3001);
	//optionType = (char*)calloc(1, 3001);
	//defaults = (char*)calloc(1, 3001);
	iy = states[indx].entry[ix].ishowmsg;
	p = params(id, buf, CSHOWID, '"', "SHOW ID");
	if (strlen(id)) {
		states[indx].entry[ix].eshowmsg[iy].showid =
			(char *) calloc(1,(int)strlen(id) + 1);
		strcpy(states[indx].entry[ix].eshowmsg[iy].showid, buyukHarf(id));
	}
	message = id;
	p = params(message, buf, CSHOWMSGX, '"', "SHOW MSG");
	if (strlen(message)) {
		states[indx].entry[ix].eshowmsg[iy].message =
			(char *)calloc(1, (int)strlen(message) + 1);
		strcpy(states[indx].entry[ix].eshowmsg[iy].message, message);
	}
	title = message;
	p = params(title, buf, CSHOWTITLE, '"', "SHOW TITLE");
	if (strlen(title)) {
		states[indx].entry[ix].eshowmsg[iy].title =
			(char *) calloc(1,(int)strlen(title) + 1);
		strcpy(states[indx].entry[ix].eshowmsg[iy].title, buyukHarf(title));
	}
	messageType = title;
	p = params(messageType, buf, CSHOWMSGTYPE, '"', "SHOW MSGTYPE");
	if (strlen(messageType)) {
		states[indx].entry[ix].eshowmsg[iy].messageType =
			(char *) calloc(1,(int)strlen(messageType) + 1);
		strcpy(states[indx].entry[ix].eshowmsg[iy].messageType, messageType);
	}
	optionType = messageType;
	p = params(optionType, buf, CSHOWOPTTYPE, '"', "SHOW OPT TYPE");
	if (strlen(optionType)) {
		states[indx].entry[ix].eshowmsg[iy].optionType =
			(char *) calloc(1,(int)strlen(optionType) + 1);
		strcpy(states[indx].entry[ix].eshowmsg[iy].optionType, optionType);
	}
	defaults = optionType;
	p = params(defaults, buf, CSHOWDEFAULT, '"', "SHOW DEFAULT");
	if (strlen(defaults)) {
		states[indx].entry[ix].eshowmsg[iy].defaultOption =
			(char *) calloc(1,(int)strlen(defaults) + 1);
		strcpy(states[indx].entry[ix].eshowmsg[iy].defaultOption, defaults);
	}
	strcpy(buf, sbuf);
	states[indx].entry[ix].ishowmsg++;
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
	if (strlen(id)) {
		states[indx].entry[ix].egetshare[iy].shareid =
			(char *) calloc(1,(int)strlen(id) + 1);
		strcpy(states[indx].entry[ix].egetshare[iy].shareid, buyukHarf(id));
	}
	if (strlen(cvar)) {
		states[indx].entry[ix].egetshare[iy].sharecvar =
			(char *) calloc(1,(int)strlen(cvar) + 1);
		strcpy(states[indx].entry[ix].egetshare[iy].sharecvar, cvar);
	}
	if (strlen(var)) {
		states[indx].entry[ix].egetshare[iy].sharevar =
			(char *) calloc(1,(int)strlen(var) + 1);
		strcpy(states[indx].entry[ix].egetshare[iy].sharecvar, var);
	}
	strcpy(buf, sbuf);
	states[indx].entry[ix].igetshare++;
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
	if (strlen(id)) {
		states[indx].entry[ix].esetshare[iy].setid =
			(char *) calloc(1,(int)strlen(id) + 1);
		strcpy(states[indx].entry[ix].esetshare[iy].setid, buyukHarf(id));
	}
	if (strlen(cvar)) {
		states[indx].entry[ix].esetshare[iy].setcvar =
			(char *) calloc(1,(int)strlen(cvar) + 1);
		strcpy(states[indx].entry[ix].esetshare[iy].setcvar, cvar);
	}
	if (strlen(var)) {
		states[indx].entry[ix].esetshare[iy].setvar =
			(char *) calloc(1,(int)strlen(var) + 1);
		strcpy(states[indx].entry[ix].esetshare[iy].setvar, var);
	}
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
	if (strlen(id)) {
		states[indx].entry[ix].epad[iy].padid = (char *) calloc(1,(int)strlen(id) + 1);
		strcpy(states[indx].entry[ix].epad[iy].padid, buyukHarf(id));
	}
	if (strlen(dname)) {
		states[indx].entry[ix].epad[iy].dname = (char *) calloc(1,(int)strlen(dname) + 1);
		strcpy(states[indx].entry[ix].epad[iy].dname, buyukHarf(dname));
	}
	if (strlen(padchar)) {
		states[indx].entry[ix].epad[iy].padchar =
			(char *) calloc(1,(int)strlen(padchar) + 1);
		strcpy(states[indx].entry[ix].epad[iy].padchar, padchar);
	}
	if (strlen(padlen)) {
		states[indx].entry[ix].epad[iy].padlen =
			(char *) calloc(1,(int)strlen(padlen) + 1);
		strcpy(states[indx].entry[ix].epad[iy].padlen, padlen);
	}
	if (strlen(align)) {
		states[indx].entry[ix].epad[iy].padalign =
			(char *) calloc(1,(int)strlen(align) + 1);
		strcpy(states[indx].entry[ix].epad[iy].padalign, align);
	}
	states[indx].entry[ix].ipad++;
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
	if (strlen(id)) {
		states[indx].entry[ix].eccf[ix].ccfid =
			(char *) calloc(1,(int)strlen(id) + 1);
		strcpy(states[indx].entry[ix].eccf[ix].ccfid, buyukHarf(id));
	}
	if (strlen(cust)) {
		states[indx].entry[ix].eccf[ix].cust =
			(char *) calloc(1,(int)strlen(cust) + 1);
		strcpy(states[indx].entry[ix].eccf[ix].cust, cust);
	}
	if (strlen(sig)) {
		states[indx].entry[ix].eccf[ix].sig =
			(char *) calloc(1,(int)strlen(sig) + 1);
		strcpy(states[indx].entry[ix].eccf[ix].sig, sig);
	}
	states[indx].entry[ix].iccf++;
	strcpy(buf, sbuf);
}

void getGEN(int indx, int ix)
{
	int  iy;
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
	if (strlen(id)) {
		states[indx].entry[ix].egen[iy].genid = (char *) calloc(1,(int)strlen(id) + 1);
		strcpy(states[indx].entry[ix].egen[iy].genid, buyukHarf(id));
	}
	if (strlen(acc)) {
		states[indx].entry[ix].egen[iy].genacc = (char *) calloc(1,(int)strlen(acc) + 1);
		strcpy(states[indx].entry[ix].egen[iy].genacc, acc);
	}
	if (strlen(br)) {
		states[indx].entry[ix].egen[iy].genbr = (char *) calloc(1,(int)strlen(br) + 1);
		strcpy(states[indx].entry[ix].egen[iy].genbr, br);
	}
	if (strlen(cd)) {
		states[indx].entry[ix].egen[iy].gencd = (char *) calloc(1,(int)strlen(cd) + 1);
		strcpy(states[indx].entry[ix].egen[iy].gencd, cd);
	}
	if (strlen(iban)) {
		states[indx].entry[ix].egen[iy].geniban = (char *) calloc(1,(int)strlen(iban) + 1);
		strcpy(states[indx].entry[ix].egen[iy].geniban, iban);
	}
	states[indx].entry[ix].igen++;
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
	if (strlen(id)) {
		states[indx].entry[ix].emaes[iy].maesid =
			(char *) calloc(1,(int)strlen(id) + 1);
		strcpy(states[indx].entry[ix].emaes[iy].maesid, buyukHarf(id));
	}
	if (strlen(docbr)) {
		states[indx].entry[ix].emaes[iy].maesdocbr =
			(char *) calloc(1,(int)strlen(docbr) + 1);
		strcpy(states[indx].entry[ix].emaes[iy].maesdocbr, docbr);
	}
	if (strlen(docdt)) {
		states[indx].entry[ix].emaes[iy].maesdocdt =
			(char *) calloc(1,(int)strlen(docdt) + 1);
		strcpy(states[indx].entry[ix].emaes[iy].maesdocdt, docdt);
	}
	if (strlen(docmaint)) {
		states[indx].entry[ix].emaes[iy].maesdocmaint =
			(char *) calloc(1,(int)strlen(docmaint) + 1);
		strcpy(states[indx].entry[ix].emaes[iy].maesdocmaint, docmaint);
	}
	if (strlen(view)) {
		states[indx].entry[ix].emaes[iy].maesview =
			(char *) calloc(1,(int)strlen(view) + 1);
		strcpy(states[indx].entry[ix].emaes[iy].maesview, buyukHarf(view));
	}
	if (strlen(doctype)) {
		states[indx].entry[ix].emaes[iy].maesdoctype =
			(char *) calloc(1,(int)strlen(doctype) + 1);
		strcpy(states[indx].entry[ix].emaes[iy].maesdoctype, doctype);
	}
	if (strlen(optype)) {
		states[indx].entry[ix].emaes[iy].maesoptype =
			(char *) calloc(1,(int)strlen(optype) + 1);
		strcpy(states[indx].entry[ix].emaes[iy].maesoptype, optype);
	}
	if (strlen(dochost)) {
		states[indx].entry[ix].emaes[iy].maesdochost =
			(char *) calloc(1,(int)strlen(dochost) + 1);
		strcpy(states[indx].entry[ix].emaes[iy].maesdochost, dochost);
	}
	if (strlen(docid)) {
		states[indx].entry[ix].emaes[iy].maesdocid =
			(char *) calloc(1,(int)strlen(docid) + 1);
		strcpy(states[indx].entry[ix].emaes[iy].maesdocid, buyukHarf(docid));
	}
	if (strlen(doccust)) {
		states[indx].entry[ix].emaes[iy].maesdoccust =
			(char *) calloc(1,(int)strlen(doccust) + 1);
		strcpy(states[indx].entry[ix].emaes[iy].maesdoccust, doccust);
	}
	if (strlen(scan)) {
		states[indx].entry[ix].emaes[iy].maesscan =
			(char *) calloc(1,(int)strlen(scan) + 1);
		strcpy(states[indx].entry[ix].emaes[iy].maesscan, scan);
	}
	states[indx].entry[ix].igen++;
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
	if (strlen(id)) {
		states[indx].entry[ix].etrim[iy].trimid =
			(char *) calloc(1,(int)strlen(id) + 1);
		strcpy(states[indx].entry[ix].etrim[iy].trimid, buyukHarf(id));
	}
	if (strlen(var)) {
		states[indx].entry[ix].etrim[iy].trimvar =
			(char *) calloc(1,(int)strlen(var) + 1);
		strcpy(states[indx].entry[ix].etrim[iy].trimvar, buyukHarf(var));
	}
	if (strlen(trimc)) {
		states[indx].entry[ix].etrim[iy].trimchar =
			(char *) calloc(1,(int)strlen(trimc) + 1);
		strcpy(states[indx].entry[ix].etrim[iy].trimchar, trimc);
	}
	if (strlen(trimd)) {
		states[indx].entry[ix].etrim[iy].trimdir =
			(char *) calloc(1,(int)strlen(trimd) + 1);
		strcpy(states[indx].entry[ix].etrim[iy].trimdir, trimd);
	}
	states[indx].entry[ix].itrim++;
	strcpy(buf, sbuf);
}

void getinitColl(int indx, int  ix)
{
	int iy;
	char id[200];
	char delm[200];
	char *p, sbuf[2000];
	strcpy(sbuf, buf);
	iy = states[indx].entry[ix].itrim;
	p = params(id, buf, CINITCOLLID, '"', "INITCOLL ID");
	p = params(delm, buf, CINITCOLLDELM, '"', "INITCOLL DELM");
	if (strlen(id)) {
		states[indx].entry[ix].einitcoll[iy].id =
			(char *) calloc(1,(int)strlen(id) + 1);
		strcpy(states[indx].entry[ix].einitcoll[iy].id, buyukHarf(id));
	}
	if (strlen(delm)) {
		states[indx].entry[ix].einitcoll[iy].delm =
			(char *) calloc(1,(int)strlen(delm) + 1);
		strcpy(states[indx].entry[ix].einitcoll[iy].delm, delm);
	}
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
	iy = states[indx].entry[ix].itrim;
	p = params(id, buf, CRMCOLLID, '"', "RMCOLL ID");
	p = params(delm, buf, CRMCOLLDELM, '"', "RMCOLL DELM");
	p = params(poly, buf, CRMCOLLPOLY, '"', "RMCOLL POLY");
	p = params(repno, buf, CRMCOLLREPNO, '"', "RMCOLL REPNO");
	if (strlen(id)) {
		states[indx].entry[ix].ermcoll[iy].id =
			(char *) calloc(1,(int)strlen(id) + 1);
		strcpy(states[indx].entry[ix].ermcoll[iy].id, buyukHarf(id));
	}
	if (strlen(delm)) {
		states[indx].entry[ix].ermcoll[iy].delm =
			(char *) calloc(1,(int)strlen(delm) + 1);
		strcpy(states[indx].entry[ix].ermcoll[iy].delm, delm);
	}
	if (strlen(poly)) {
		states[indx].entry[ix].ermcoll[iy].poly =
			(char *) calloc(1,(int)strlen(poly) + 1);
		strcpy(states[indx].entry[ix].ermcoll[iy].poly, poly);
	}
	if (strlen(repno)) {
		states[indx].entry[ix].ermcoll[iy].repno =
			(char *) calloc(1,(int)strlen(delm) + 1);
		strcpy(states[indx].entry[ix].ermcoll[iy].repno, repno);
	}
	states[indx].entry[ix].irmcoll++;
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
	states[indx].entry[ix].imaes = 0;
	states[indx].ientry++;
	return ix;
}

void pentryGet(int indx, int ix)
{
	int  tag;
	char prt[200];
	char *p, *p1;
	char strinit[200];
	while (getend(EENTRY, 0) == EOF) {
		Processed = 1;
		tag = beginTag(PENTRY);

		switch (tag) {
		case PINIT:
			while (!strstr(buf, EINIT)) {
				p = strstr(buf, CINITID);
				if (p) {
					p = p +(int)strlen(CINITID);
					p1 = p;
					while (*p && *p != '"') p++;
					*p = 0;
					strcpy(strinit, p1);
					states[indx].entry[ix].initid =
						(char *) calloc(1,(int)strlen(strinit) + 1);
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
		case PDOCUMENTS:
			params(prt, buf, "id=\"", '"', "DOC PRNT");
			if (strlen(prt)) {
				states[indx].entry[ix].eprintid = (char *) calloc(1,(int)strlen(prt) + 1);
				strcpy(states[indx].entry[ix].eprintid, buyukHarf(prt));
			}
			while (!strstr(buf, EDOCUMENTS)) {
				;
			}
			break;
		case PEXEC:
			pexecGet(indx, ix);
			while (getend(EEXEC, 1) == EOF) {
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
		}
	}
}

int  iclient = 0;
char *clientfunc[200];
char *clientvname[200];
char *clientretval[200];

void readvnames(char *sfile)
{
	FILE *fx;
	char *p, *p1;
	int  i;
	char bufx[MAXCHAR + 1];
	fx = fopen(sfile, "r");
	if (fx) {
		while (fgets(bufx, MAXCHAR, fx)){
			rmnl(bufx);
			p1 = strstr(bufx, ":");
			if (p1 == NULL) continue;
			*p1=0;
			p1++;
			p = strstr(p1, ":");
			if (p) {
				*p = 0;
				p++;
				i = iclient;
				clientfunc[i] = (char*)calloc(1, strlen(bufx) + 1);
				clientvname[i] = (char*)calloc(1, strlen(p1) + 1);
				clientretval[i] = (char*)calloc(1, strlen(p) + 1);
				strcpy(clientfunc[i], buyukHarf(bufx));
				strcpy(clientvname[i], buyukHarf(p1));
				if(strcmp(p, "(null)") == 0)
					strcpy(clientretval[i], "void"); //burada null da olabilir
				else strcpy(clientretval[i], buyukHarf(p));
				iclient++;
			}
		}
		fclose(fx);
	}
#ifdef GECICI
	else {
		fprintf(output, "%s bulunamadi\n", sfile);
	}
#endif
}
void myApproval(int varmi, char *progname, char *tranname, char *area)
{
	if (varmi) {
		fprintf(output, "       [HttpPost]\n");
		fprintf(output, "       public ActionResult Approval();\n");
		fprintf(output, "       [HttpGet]\n");
		fprintf(output, "       public ActionResult Approval(string approvalStatus, string approvalProcessId, string approvalActivityId, string transactionName);\n");
		fprintf(output, "       [HttpGet]\n");
		fprintf(output, "       public ActionResult ApprovalReturn(string approvalStatus, string approvalProcessId, string approvalActivityId, string transactionName);\n");
	}
}

void myPrologue(char *view_name, char *tranname, char *area)
{
	fprintf(output, "// Generated by BE-CON Automatic Face Converter V:1.0\n\n");
	fprintf(output, "using System;\n");
	fprintf(output, "using System.Collections.Generic;\n");
	fprintf(output, "using System.Linq;\n");
	fprintf(output, "using System.Web;\n");
	fprintf(output, "using System.Web.Mvc;\n");
	fprintf(output, "using AkbankFace.Web.Common;\n");
	fprintf(output, "using AkbankFace.Web.Common.Interfaces;\n");
	fprintf(output, "using AkbankFace.Web.%s.Models;\n", area);

	fprintf(output, "using AkbankFace.Web.%s.ClientBusiness;\n", area);
	fprintf(output, "// using AkbankFace.Web.%s.ClientBusiness.%s;\n", area, tranname);
	// fprintf(output, "using AkbankFace.Web.%s.Models;\n", area);
	fprintf(output, "using AkbankFace.Web.%s.Common.Constants;\n", area);
	fprintf(output, "using AkbankFace.BranchBanking.Common;\n\n");
	fprintf(output, "using AkbankFace.Web.%s.Common;\n\n", area);
	fprintf(output, "namespace AkbankFace.Web.%s.WebUI.Controllers\n", area);
	fprintf(output, "{\n");
	fprintf(output, "    public class %sController : BranchControllerBase<%sClientBusiness>\n", tranname, tranname);
	fprintf(output, "       {\n");
	fprintf(output, "       public %sController() : base() { }\n", tranname);
}

int itarget = 0;
char *target[SMAX];

int targetmi(char *name)
{
	int i;
	for (i = 0; i< itarget; i++) {
		if (strcmp(target[i], name) == 0) return true;
	}
	return false;
}

void targetEkle(char *view)
{
	int ix;
	ix = itarget;
	target[ix] = (char *) calloc(1,(int)strlen(view) + 1);
	strcpy(target[ix], view);
	itarget++;
}

char *newParam(char *p)
{
	int  i;
	for (i = 0; i < iclient; i++) {
		if (strcmp(clientfunc[i], p) == 0)
			return clientretval[i];
	}
	return NULL;
}


void redirectFunc(char* vname)
{
	fprintf(output, "%s", indentstr());
	fprintf(output, "public void redirect()\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "{\n");
	indents++;
	fprintf(output, "%s", indentstr());
	fprintf(output, "RedirectToAcion(%sConstants.%s, %sConstants.FlowView.vcontroller, new\n",
		tranname, getconstant((char*)"view", (char*)"Index"), tranname);
	fprintf(output, "%s", indentstr());
	fprintf(output, "{\n");
	indents++;
	fprintf(output, "%s", indentstr());
	fprintf(output, "Area= ModuleConstants.AreaName,\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "AKBANK_FACE_CONTEXT_MULTIWINDOW_KEY = Business.Context.Session.CurrentTab.TabGuid\n");
	fprintf(output, "%s", indentstr());
	indents--;
	fprintf(output, "});\n");
	indents--;
	fprintf(output, "%s", indentstr());
	fprintf(output, "}\n");
	indents--;
}

int arrName(char *p)
{
	int  i;
	for (i = 0; i < ivname; i++) {
		if (vname[i].viewname && strcmp(vname[i].viewname, p) == 0 && vname[i].iarray > 0) { // <==================
			return 1;
		}
	}
	return 0;
}

void writeTag(int param, int direction, char *transname, char *pstr, char *tar, char *v_name, char *vname)
{
	char *p, *p1;
	p = strstr(pstr, ".");
	if (p) {
		*p = 0;
		p++;
		p1 = strstr(p, "\"");
		if (p1) {
			*p1 = 0;
		}
		else {
			p1 = strstr(p, ".");
			if (p1)
				*p1 = 0;
		}
		myReplace(p, ' ', '_');
		if (param == 2) {

			fprintf(output, "%s", indentstr());
			fprintf(output, "if (model.CommandTag == %sConstants.%s)\n", tranname, getconstant("flowtag", p));
			fprintf(output, "%s", indentstr());
			fprintf(output, "{\n");
			indents++;
		}
		 addstarters(tar);
		if (param == 2) {
			int  iarr;
			if (vname && strcmp(v_name, vname) != 0) {
				if (strcmp(p, "GERI") == 0 || strcmp(p, "ESC") == 0) {
					fprintf(output, "%s", indentstr());
					if(strcmp(vname, indexname) == 0)
						fprintf(output, "model = Business.Index(model);\n");
					else fprintf(output, "model = Business.%s(model);\n", vname);
				}
				else {
					fprintf(output, "%s", indentstr());
					if (strcmp(vname, indexname) == 0)
						fprintf(output, "model = Business.Index(model);\n");
					else fprintf(output, "model = Business.%s(model);\n", vname);
				}
				indents--;
			}
			else {
				if (vname) {
					//fprintf(output, "%s", indentstr());
					//fprintf(output, "Business.Flow.AddVariableToFlow<%sViewModel>(new KeyValuePair<string, %sViewModel>(%sConstants.Models, model));\n", 
					//	tranname, tranname, tranname);
					iarr = arrName(vname);
					if (iarr >=0) {
						fprintf(output, "%s", indentstr());
						fprintf(output, "if (model.SelectedRow != \"\")\n");
						fprintf(output, "%s", indentstr());
						fprintf(output, "{\n");
						indents++;
						fprintf(output, "%s", indentstr());
						fprintf(output, "Business.Split%sSelected(model); \n", vname);
						fprintf(output, "%s", indentstr());
						fprintf(output, "Business.%s(model);\n", vmodel[iarr].starget[0]);
						indents--;
						fprintf(output, "%s", indentstr());
						fprintf(output, "}\n");
					}
				}

				fprintf(output, "%s", indentstr());
				fprintf(output, "return View(model); \n");
				indents--;
			}
			fprintf(output, "%s", indentstr());
			fprintf(output, "}\n");
		}
	}
}

char *newstateBak(char *s)
{
	int  i;
	for (i = 0; i < iclient; i++) {
		if (strcmp(clientfunc[i], s) == 0) {
			return clientvname[i];
		}
	}
	return 0;
}

void httpPost(int param, char *view_name, char *trans_model, int ii)
{
	int  j, k;
	if (!targetmi(view_name)) {
		if (param == 2) {
			fprintf(output, "%s", indentstr());
			fprintf(output, "[HttpPost]\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "public ActionResult %s(%sViewModel model)\n", view_name, tranname);
			fprintf(output, "%s", indentstr());
			fprintf(output, "{\n");
			indents++;
		}

		if (states[ii].itran > 0) {
			char *vname, *viewname;
			for (j = 0; j < states[ii].itran; j++) {
				viewname = vmodelpBak (states[ii].stateid);
				if (viewname) {
					if (states[ii].itran > 0) {
						for (k = 0; k < states[ii].itran; k++) {
							vname = newstateBak(states[ii].trans[k].trantarget);
							writeTag(param, 1, trans_model, states[ii].trans[k].tranid, 
								     states[ii].trans[k].trantarget, view_name, vname);

						}
					}
				}
			}
		}
		if (param == 2) {

			//indents++;
			fprintf(output, "%s", indentstr());
			fprintf(output, "return View(model);\n");

			indents--;
			fprintf(output, "%s", indentstr());
			fprintf(output, "}\n");
		}
		targetEkle(view_name);
	}
}

char *myReplace(char *str, char s, char trg)
{
	int i, len;
	int k = 0;
	char t[200];
	len = (int)strlen(str);
	for (i = 0; i < len; i++) {
		if (str[i] == s) str[i] = trg;
	}
	for (i = 0; i < len;i++) {
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
		} else
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
		} else
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
	return str;
}

void viewsOku(char *dir, char *prog, char *trn)
{
	int  ix;
	char fpref[200];
	char *p, *pp;
	// read flows.preference file
	FILE *ff;
	p = strstr(dir, "\\INDIR");
	if (p) *p = 0;
	strcpy(fpref, dir);
	strcat(fpref, "\\");
	strcat(fpref, PREFS);
	strcat(fpref, trn);
	strcat(fpref, "\\");
	strcat(fpref, trn);
	strcat(fpref, prog);
	strcat(fpref, "flow.preference");
	ff = fopen(fpref, "r");
	if (ff) {
		while (fgets(fbuf, FMAX, ff)) {
			rmnl(fbuf);
			pp = strstr(fbuf, ".");
			if (pp) {
				*pp = 0;
				if (strcmp(fbuf, "view")) continue;
				pp++;
			}
			else pp = fbuf;
			p = strstr(pp, "=");
			if (p) {
				ix = iviews;
				*p = 0;
				p++;
				strcpy(fviews[ix].v1, pp);
				strcpy(fviews[ix].v2, p);
				iviews++;
				fviews[iviews].v1[0] = 0;
			}
		}
		fclose(ff);
	}
	//else {
	//	fprintf(output, "Error %s file not found..\n", fpref);
	//	exit(0);
	//}
}

char *viewBak(int ii, char *view)
{
	int i;
	for (i = 0; i < iviews; i++) {
		if (strcmp(fviews[i].v2, view) == 0 || strstr(fviews[i].v2,view))
			return fviews[i].v2;
	}
	for (i = 0; i < iviews; i++) {
		if (strcmp(fviews[i].v1, view) == 0 || strstr(fviews[i].v1, view))
			return fviews[i].v1;
	}
	//for (j = iviews; j<200; j++) {
	//	if (strcmp(fviews[j].v1, view) == 0) continue;
	//	if (fviews[j].v1[0] == 0) {
	//		strcpy(fviews[j].v1, view);
	//		fviews[j].v1[0] = 0;
	//		break;
	//	}
	//}
	// return getfirstview(ii);
	for (i = 0; i < ivmodel; i++) {
		if (strcmp(vmodel[i].sid, view) == 0 || strstr(vmodel[i].sid, view))
			return vmodel[i].sview;
	}
	return 0;
}

//char *getView(char *p, int ii)
//{
//	int  i, j, k;
//	for (i = 0; i < istate; i++) {
//		for (j = 0; j<states[i].ientry; j++)
//			for (k = 0; k<states[i].entry[j].iopen; k++)
//				if (strcmp(states[i].stateid, p) == 0)
//					return states[i].entry[j].sopen[k].viewname;
//	}
//	return getfirstview(ii);
//}

int  targetVarmi(char *s, char *ss)
{
	int i, j;
	for (i = 0; i < ivmodel; i++) {
		for (j = 0; vmodel[i].stranid[j] != NULL; j++)
			if (ss) {
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
		strcpy(vmodel[m].stranid[j], p1);
		vmodel[m].starget[j] = (char *)calloc(1, strlen(ps) + 1);
		strcpy(vmodel[m].starget[j], ps);
		// vmodelTargetTasi(m - 1, j, ss, p);
		for (ii = 0; ii < m; ii++) {
			for (j = 0; vmodel[m].starget[j] != NULL; j++)
				if (vmodel[m].sid && strcmp(vmodel[m].sid, vmodel[ii].starget[j]) == 0)
					vmodelTargetTasi(ii, j, p1, ps);
		}
	}
}
int vmodelViewTasi(int m, char *p)
{
	int  ii, j, kopya = 0;

	if (m >= 0 && vmodel[m].sview != NULL) {
		if (strcasecmp(p, "filler")) {
			vmodel[m].sview = (char *)calloc(1, strlen(p) + 1);
			strcpy(vmodel[m].sview, p);
			for (ii = 0; ii < m; ii++) {
				for (j = 0; vmodel[m].starget[j] != NULL && j < 7; j++) {
					if (vmodel[m].sid && vmodel[ii].starget[j] &&
						strcmp(vmodel[m].sid, vmodel[ii].starget[j]) == 0) {
						vmodelViewTasi(ii, p);
						kopya = 1;
					}
				}
			}
		}
	}
	return kopya;
}
int vmodelModelCopy(int m, char *si, char *p)
{
	int ii, j, kopya = 0;
	for (ii = 0; ii < ivmodel; ii++) {
		for (j = 0; (vmodel[ii].starget[j] != NULL) && j < 7; j++) {
			if (strstr(vmodel[ii].starget[j], si)) {
				if (vmodel[ii].smodel == NULL) {
					vmodel[ii].smodel = (char *)calloc(1, strlen(p) + 1);
					strcpy(vmodel[ii].smodel, p);
					kopya++;
					kopya += vmodelModelCopy(ii, vmodel[ii].sid, p);
				}
				else 
					return kopya;
			}
		}
	}
	return kopya;
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
			if (p1) p1++;
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
				if (strcasecmp(states[ii].entry[j].sopen[k].openid, "filler")) {
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

int vmodelVarmi(int ii)
{
	int  i;
	for (i = 0; i < ivmodel; i++) {
		if (vmodel[i].is == ii) return 1;
	}
	return 0;
}

void vmodelViewCopy(int m, char *si, char *p)
{
	int ii, j;
	for (ii = 0; ii < ivmodel; ii++)
		for (j = 0; vmodel[ii].starget[j] != NULL; j++) {
			if (strcasecmp(p, "filler") && strstr(vmodel[ii].starget[j], si)) {
				if (vmodel[ii].sview == NULL) {
					vmodel[ii].sview = (char *)calloc(1, strlen(p) + 1);
					strcpy(vmodel[ii].sview, p);
					vmodelViewCopy(ii, vmodel[ii].sid, p);
				}
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
	int  i = 0;
	int  m = 0;
	int  mi,  say;
	for (i = 0; i < istate; i++) {
		mi = m;
		if (strcmp(states[i].statetype, "initial") == 0) {
			vmodelTasi(mi, i, 0);
			m++;
			checkOthers(mi, i);
		}
		else {
			// vmodel de daha once yoksa
			if (vmodelBak(states[i].stateid) < 0) {
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
	say = 0;
	for (i = 0; i < ivmodel; i++) {
		if (vmodel[i].smodel == NULL) say++;
	}
	for (i = 0; i < ivmodel && say > 0; i++) {
		if (vmodel[i].smodel != NULL) {
			say -= vmodelModelCopy(i, vmodel[i].sid, vmodel[i].smodel);
		}
	}
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

char *vmodelpBak(char *ss)
{
	int  i;
	for (i = 0; i < ivmodel; i++) {
		if ((strcmp(vmodel[i].sid, ss) == 0))
			return vmodel[i].sview;
	}
	return 0;
}
int vmodelBak(char *p)
{
	int i;
	for (i = 0; i < ivmodel; i++)
		if (strcmp(vmodel[i].sid,p) == 0)
			return i;
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
char constval[200];
char *getconstant(char *tip, char *txt)
{
	int  i;
	for (i = 0; i < iconstant; i++) {
		if ((strcasecmp(constants[i].vtype, tip) == 0) && (strcmp(constants[i].vval, txt) == 0)) {
			if (strcmp(constants[i].vtype, "view") == 0)
				 sprintf(constval, "FlowView.%s", constants[i].vname);
			else
			if (strcasecmp(constants[i].vtype, "func") == 0)
				sprintf(constval, "FuncTag.%s", constants[i].vname);
			else
			if (strcasecmp(constants[i].vtype, "flowtag") == 0)
				sprintf(constval, "FlowTag.%s", constants[i].vname);
			else strcpy(constval, constants[i].vname);
			return constval;
		}
	}
	if (strcasecmp(tip, "view") == 0)
		sprintf(constval, "FlowView.%s", txt);
	else
	if (strcasecmp(tip, "func") == 0)
		sprintf(constval, "FuncTag.%s", txt);
	else
	if (strcasecmp(tip, "flowtag") == 0)
		sprintf(constval, "FlowTag.%s", txt);
	else sprintf(constval, ".%s", txt);
	return constval;
}

int targetSay(char *s)
{
	int i, j;
	int say = 0;
	for (i = 0; i < istate; i++) {
		for (j = 0; j < states[i].itran; j++) {
			if (strcmp(states[i].trans[j].trantarget, s) == 0)
				say++;
		}
	}
	return say;
}

void setTranref()
{
	int i;
	for (i = 0; i < istate; i++)
	{
		targetSay(states[i].stateid);
	}
}

int stateBak(char *ss)
{
	int  i;
	for (i = 0; i < istate; i++) {
		if (strcmp(states[i].stateid, ss) == 0)
			return i;
	}
	return -1;
}
char *getfirstview(int ii)
{
	int  j;
	char st[200];
	while (ii < istate && ii != EOF) {
		if (states[ii].ientry > 0) {
			for (j = 0; j < states[ii].ientry; j++) {
				if (states[ii].entry[j].iopen > 0)
					return states[ii].entry[j].sopen[0].viewname;
			}
			if (states[ii].itran > 0) {
				for (j = 0; j < states[ii].itran; j++) {
					if (strstr(states[ii].trans[j].tranid, "OK")) {
						strcpy(st, states[ii].trans[j].trantarget);
						ii = stateBak(st);
						break;
					}
				}
				continue;
			}
		}
		if (states[ii].itran > 0) {
			for (j = 0; j < states[ii].itran; j++) {
				if (strstr(states[ii].trans[j].tranid, "OK")) {
					strcpy(st, states[ii].trans[j].trantarget);
					ii = stateBak(st);
				}
			}
		}
		else return 0;
	}
	return 0;
}

int stateViewBak(char *ss)
{
	int  i;
	if (ss == NULL) return -1;
	if (strcmp(ss, "filler") == 0) return -1;
	for (i = 0; i < ivmodel; i++) {
		if (vmodel[i].sview) {
			if (strcasecmp(ss, "filler") && strcmp(vmodel[i].sview, ss) == 0)
				return vmodel[i].is;
		}
	}
	return -1;
}

int  istarting = 0;
char *starting[200];

void addstarters(char *p)
{
	int  i;
	for (i = 0; i < istarting; i++) {
		if (strcmp(starting[i], p) == 0) return;
	}
	i = istarting;
	istarting++;
	starting[i] = (char *)calloc(1, strlen(p) + 1);
	strcpy(starting[i], p);
}

int ionceki = 0;
char onceki[300][200];

int  oncekiView(int ii)
{
	int i,j;
	char *p;
	if (ii < 0) return 1;
	for (i = 0; i < ivmodel; i++) {
		if (vmodel[i].is == ii) {
			p = vmodel[i].sview;
			if (strcasecmp(p, "filler") == 0) return 1;
			for (j = 0; j < ionceki; j++) {
				if (strcmp(onceki[j], p) == 0)
					return 1;
			}
			strcpy(onceki[ionceki], p);
			ionceki++;
			return 0;
		}
	}
	return 1;
}

void petitionprint()
{
	fprintf(output, "%s", indentstr());
	fprintf(output, "[HttpGet]\n");
	fprintf(output, "%s", indentstr());
	fprintf(output,"public ActionResult PrintPetition()\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "{\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "	return View(Business.PrintPetition());\n");
	fprintf(output, "%s", indentstr());
	fprintf(output, "}\n");
}

void writeStates(int param, char *view_name, char *transname, char *area)
{
	int  i, ii, k, varmi, j, ilk = 0;
	char *pp;
	char *mypp;
	int  iuse = 0;
	int  iused[200];
	indents++;
	getModelState();

	setTranref();

	for (i = 0; i < istate; i++) {
		if (strncmp(states[i].statetype, "initial", 7) == 0) {
			if (indexname[0] == 0) {
				pp = vmodelpBak(states[i].statetype);
			} else
				pp = viewBak(i, indexname);
			if(pp) 
				 strcpy(firstview, pp);
			else {
				strcpy(firstview, "Index");
				pp = firstview;
			}
			/*p1 = getView(states[i].stateid, i);*/
			ii = stateViewBak(pp);
			if (ii < 0 && ilk == 1) continue;
			mypp = modelBak(ii);

			if (param == 2) {
				indents++;
				fprintf(output, "%s", indentstr());
				if(strcmp(pp, "Index"))
					fprintf(output, "// Index() replaces %s;\n", pp);
				
				fprintf(output, "%s", indentstr());
				fprintf(output, "[HttpGet]\n");
				fprintf(output, "%s", indentstr());
				fprintf(output, "public ActionResult Index()\n");
				/*addstarters("Index");*/
				fprintf(output, "%s", indentstr());
				fprintf(output, "{\n");
				indents++;
				fprintf(output, "%s", indentstr());
				fprintf(output, "return View(Business.Index());\n");
				indents--;
				fprintf(output, "%s", indentstr());
				fprintf(output, "}\n");
				targetEkle(view_name);
				iused[0] = i;
				iuse++;
				fprintf(output, "%s", indentstr());
				fprintf(output, "[HttpPost]\n");
				fprintf(output, "%s", indentstr());
				// burada ilk model olmali
				if (vmodel[i].sview == NULL)
					vmodel[i].sview = firstview;
				fprintf(output, " public ActionResult Index(%sViewModel model)\n", tranname);
				fprintf(output, "%s", indentstr());
				fprintf(output, "{\n");
				indents++;
				//fprintf(output, "%s", indentstr());
				//fprintf(output, "if(model.CommandTag != null) {\n");
				//indents++;
				//fprintf(output, "%s", indentstr());
				//fprintf(output, "             // Business.Flow.AddVariableToFlow<%sViewModel>(new KeyValuePair<string, %sViewModel>(%sConstants.Models, model));\n", 
				//	tranname, tranname, tranname);
				//indents--;
				//fprintf(output, "%s", indentstr());
				//fprintf(output, "        }\n");

				fprintf(output, "%s", indentstr());
				fprintf(output, "return View(model);\n");
				indents--;
				fprintf(output, "%s", indentstr());
				fprintf(output, "}\n");
				ilk = 1;
			}
			break;
		}
	}
	// Bir sonraki operation state bulunacak
	// logic: Action.OK ara varsa target nextstate olur
	//        yoksa NavController state al (iz bırak) target nextstate olsun
	// nextstate condition ise geri dön
	// baska NavController ara
	// yoksa <model elle belirlenecek>

	for (i = 0; i < istate; i++) {
		pp = viewBak(i, states[i].stateid);
		if (pp == 0) continue;
		if (strcmp(states[i].statetype, "view") != 0 && 
			strcmp(states[i].statetype, "initial") != 0) continue;
			
		if (strcmp(states[i].statetype, "initial") == 0) {
			pp = "Index";
		}
		else {
			if (strcmp(states[i].statetype, "view") == 0) {
				pp = states[i].entry[0].sopen[0].viewname;
				if (strcasecmp(pp, "filler") == 0) continue;
				if (strcmp(pp, indexname) == 0)
					pp = (char*)"Index";
			}
		}
		if (strstr(pp, "Index")) continue;
		varmi = 0;
		for (k = 0; k < iuse; k++) {
			if (iused[k] == i) {
				varmi = 1;
				break;
			}
		}
		if (varmi) continue;
		iused[iuse] = i;
		iuse++;
		strcpy(view_name, pp);
		myReplace(view_name, ' ', '_');
		myReplace(view_name, '-', '_');
		if (strncmp(states[i].statetype, "view", 4) == 0) {
			if (oncekiView(i)) continue;
			mypp = modelBak(i);
			if (param == 2) {
				fprintf(output, "%s", indentstr());
				fprintf(output, "[HttpGet]\n");
				fprintf(output, "%s", indentstr());
				fprintf(output, "public ActionResult %s()\n", view_name);
				/*addstarters(view_name);*/
				fprintf(output, "%s", indentstr());
				fprintf(output, "{\n");
				indents++;
				fprintf(output, "%s", indentstr());
				fprintf(output, "var model = new %sViewModel();\n", view_name);
				fprintf(output, "%s", indentstr());
				fprintf(output, "if (Business.Flow.GetViewDetail(%sConstants.Models) == null)\n", tranname);
				indents++;
				fprintf(output, "%s", indentstr());
				fprintf(output, "model = Business.Flow.GetViewDetail(%sConstants.Models).Model as %sViewModel;\n",
					tranname, tranname);
				indents--;
				fprintf(output, "%s", indentstr());
				fprintf(output, "return View(Business.%s(model));\n", view_name);
				// CB icinde view_name() islemi view_nameViewModel olarak dönmeli... 
			}

			addstarters(view_name);
			if (param == 2) {
				indents--;
				fprintf(output, "%s", indentstr());
				fprintf(output, "    }\n");
			}
			httpPost(param, pp, transname, i); // view_name
		}
		//}
		for (j = 0; j < states[i].ientry; j++) {
			if (states[i].entry[j].eprintid > 0) {
				if (petition == 1)
					petitionprint();
				else {
					fprintf(output, "%s", indentstr());
					fprintf(output, "[HttpPost]\n");
					fprintf(output, "%s", indentstr());
					fprintf(output, "public SlipPrintResult PrintSlip()\n");
					fprintf(output, "%s", indentstr());
					fprintf(output, "{\n");
					indents++;
					fprintf(output, "%s", indentstr());
					fprintf(output, "var model = Business.PrintSlip();\n");
					fprintf(output, "%s", indentstr());
					fprintf(output, "var printresult = new SlipPrintResult(model);\n");
					fprintf(output, "%s", indentstr());
					fprintf(output, "return printresult;\n");
					fprintf(output, "%s", indentstr());
					fprintf(output, "}\n");
				}
			}
		}
	}
	// bunlar en sona bir kez ekleyip call edilmeli...
	if (param == 2) {
		fprintf(output, "%s", indentstr());
		fprintf(output, "public ActionResult Flowtest()\n");
		fprintf(output, "%s", indentstr());
		fprintf(output, "{\n");
		indents++;
		fprintf(output, "%s", indentstr());
		fprintf(output, "if (Business.Flow == null)\n");
		fprintf(output, "%s", indentstr());
		fprintf(output, "{\n");
		indents++;
		fprintf(output, "%s", indentstr());
		fprintf(output, "redirect();\n");
		indents--;
		fprintf(output, "%s", indentstr());
		fprintf(output, "}\n");
		fprintf(output, "%s", indentstr());
		fprintf(output, "return Content(\"OK\");\n");
		indents--;
		fprintf(output, "%s", indentstr());
		fprintf(output, "}\n");

		fprintf(output, "%s", indentstr());
		fprintf(output, "public ActionResult ModelError()\n");
		fprintf(output, "%s", indentstr());
		fprintf(output, "{\n");
		indents++;
		fprintf(output, "%s", indentstr());
		fprintf(output, "redirect();\n");
		indents--;
		fprintf(output, "%s", indentstr());
		fprintf(output, "}\n");

		redirectFunc(view_name);
		
		fprintf(output, "%s", indentstr());
		fprintf(output, "}\n");
		indents--;
		fprintf(output, "%s", indentstr());
		fprintf(output, "}\n");
	}
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

void readconst(char *ffile, char *cfile)
{
	int  i;
	FILE *fp;
	char *p, *p1;
	iconstant = 0;
	fp = fopen(ffile, "r");
	if (fp) {
		while (fgets(buf, MAXCHAR, fp)) {
			rmnl(buf);
			p = strstr(buf, ".");
			if (p) {
				*p = 0;
				p++;
				i = iconstant;
				myReplace(buf, ' ', '_');
				constants[i].vtype = (char *)calloc(1, strlen(buf) + 1);
				strcpy(constants[i].vtype, buyukHarf(buf));
				p1 = strstr(p, "=");
				if (p1) {
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
#ifdef GECICI
	 else {
		printf("file yok %s\n", ffile);
		return;
	}
#endif
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
				strcpy(constants[i].vtype, buyukHarf(buf));
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
	//else {
	//	printf("file yok %s\n", cfile);
	//	return;
	//}
}

int  iglob = 0;
char glob[200][40];
int  igetlistarr = 0;
char *getlistarr[100];
int  iflowtag;
char *flowtag[100];

void globEkle(char *s)
{
	int i;
	for (i = 0; i < iglob; i++) {
		if (strcmp(glob[i], s) == 0) {
			return;
		}
	}
	i = iglob;
	strcpy(glob[i], s);
	iglob++;
}

void readgetlist(char *gfile)
{
	FILE *fx;
	char bfx[MAXCHAR + 1];
	igetlistarr = 0;
	fx = fopen(gfile, "r");
	if (fx) {
		while (fgets(bfx, MAXCHAR, fx)) {
			rmnl(bfx);
			getlistarr[igetlistarr] = (char *)calloc(1, strlen(bfx) + 1);
			strcpy(getlistarr[igetlistarr], buyukHarf(bfx));
			igetlistarr++;
		}
		fclose(fx);
	}
	else fprintf(output, "file yok %s\n", gfile);
}

void flowtagEkle(int type, char *p)
{
	int  i;
	myReplace(p, ' ', '_');
	for (i = 0; i < iflowtag; i++) {
		if (strcmp(flowtag[i], p) == 0)
			return;
	}
	i = iflowtag;
	flowtag[i] = (char *)calloc(1, strlen(p) + 3);
	sprintf(flowtag[i], "%d%s", type, p);
	iflowtag++;
}

char *defval[200];
int  idefval = 0;

void defekle(char *p)
{
	int i;
	for (i = 0; i < idefval; i++) {
		if (strcmp(defval[i], p) == 0)
			return;
	}
	i = idefval;
	defval[i] = (char *)calloc(1, strlen(p) + 1);
	strcpy(defval[i], p);
	idefval++;
}

extern int bakBakalim(char *, int);

void readView(char* viewfile)
{
	char bf[INMAX + 1];
	FILE* ff;
	int  i, mtype;
	char* p, * p1, mcode[3];
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
				vname[i].iarray = 0;
				strcpy(vname[i].vcode, mcode);
				ivname++;
				break;
			case 3:
				strcpy(vname[i].arrayName, buyukHarf(bf + 4));
				strcpy(vname[i].arrcode, mcode);
				vname[i].iarray++;
				break;
			}
		}
		fclose(ff);
	}
}


void filesOku(char* progfile)
{
	FILE* ff;
	char* p;
	char bf[INMAX + 1];
	char viewfile[200];
	ff = fopen(progfile, "r");
	if (ff) {
		while (fgets(bf, INMAX, ff)) {
			rmnl(bf);
			if (strncmp(bf, "VIEW ", 5) == 0) {
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
}

int main(int argc, char **argv)
{
	FILE *fp, *fx;
	int ret;
	int tag, indx, ix;
	int  i, avail, procId;
	char *p, filename[300];
	char controller[300];

	char bufx[300];

	char sname[200], stype[200];
	char flowfile[200], constfile[200];
	char controllerpref[200], file1[200];
	char client[200], indexfile[200];
	char pname[200], *pp;
	char getlistf[200], procfile[200];
	char sid[SMAX];
	/// NOT PetitionPrint islemi olacaksa petition = 1 olmali 
	/* get tables and coulmns of connected database */
	output = stdout;
	param = 0;
	istate = 0;
	SetConsoleOutputCP(CP_UTF8);
		if (argc == 7) {
			param = atoi(argv[1]);
			strcpy(tranname, argv[2]);
			strcpy(areaName, argv[3]);
			avail = atoi(argv[4]);
			procId = atoi(argv[5]);
			strcpy(filename, argv[6]);
			strcpy(procfile, argv[6]);
		} else {
			for (i = 1; i < argc; i++) {
				fprintf(output, "%d %s, ", i, argv[i]);
			}
			fprintf(output, "\n");
			fprintf(output, "%d\n", argc);
			fprintf(output, "kullanım: controller [1/2] <tranid> <areaName> <proc_file> \n");
			fprintf(output, "1 <tranid> <areaName> <proc_file>  Debug Info\n");
			fprintf(output, "2 <tranid> <areaName> <proc_file> creates <tranid>Controller.cs\n");
			fprintf(output, "3 <tranid> <areaName> <proc_file> creates controller.preference\n");
			fprintf(output, "4 <tranid> <areaName> <proc_file> creates global variables temp file\n");
			fprintf(output, "5 <tranid> <areaName> <proc_file> creates flowtag for constants\n");
			exit(0);
		}
	if (bakBakalim("be1converter", procId) == 0) {
		exit(1);
	}
		p = strstr(filename, "Proc.");
		*p = 0;
		p = laststr(filename, "\\");
		if (p) {
			*p = 0;  p++;
		}
		else  p = filename;
		strcpy(progname, p);

		strcpy(pname, progname);

		strcpy(flowfile, filename);
		strcpy(client, filename);
		pp = strstr(client, "INDIRS");
		*pp = 0;
		pp = strstr(flowfile, "INDIRS");
		strcpy(pp, PREFS);
		strcat(pp, tranname);
		strcat(pp, "\\");
		strcat(pp, tranname);
		strcpy(indexfile, client);
		strcat(indexfile, PREFS);
		strcat(indexfile, tranname);
		strcat(indexfile, "\\");
		strcpy(getlistf, indexfile);
		strcat(indexfile, tranname);
		strcpy(file1, indexfile);
		strcat(file1, ".files");
		strcat(client, pp);
		strcat(pp, pname);
		strcpy(constfile, flowfile);
		strcpy(controllerpref, flowfile);
		strcat(controllerpref, "Controller.preference");
		strcat(client, "client.preference");
		strcat(pp, "flow.preference");
		strcat(constfile, ".constants");
		strcat(indexfile, "Index.txt");
		strcat(getlistf, tranname);
		strcat(getlistf, "GetList.txt");

		fx = fopen(indexfile, "r");
		if (fx) {
			fgets(bufx, 200, fx);
			rmnl(bufx);
			strcpy(indexname, bufx);
			if (bufx[0] < 'A' || bufx[0] > 'Z')
				if (bufx[0] <'a' || bufx[0] > 'z')
					strcpy(indexname, bufx + 3);
			fclose(fx);
		}
		else  indexname[0] = 0;
		strcpy(controller, filename);
		strcat(controller, "\\Root\\");
		strcat(controller, tranname);
		strcat(controller, "\\");
		strcat(controller, tranname);
		strcat(controller, "Controller.cs");
		viewsOku(filename, progname, tranname);

		// output    = fopen(controller,"w");
		fp = fopen(procfile, "r");
		if (fp) {
			input = fp;
			fstate = 0;
			ftrans = 0;
			fentry = 0;

			do {
				sname[0] = 0;
				stype[0] = 0;
				ret = getstate(sname, stype, sid);
				if (ret > 0) {
					indx = istate;
					states[indx].stateid = (char *)calloc(1, (int)strlen(sname) + 1);
					states[indx].statetype = (char *)calloc(1, (int)strlen(stype) + 1);
					states[indx].statetypeid = (char*)calloc(1, strlen(sid) + 1);
					strcpy(states[indx].stateid, buyukHarf(sname));
					strcpy(states[indx].statetype, stype);
					strcpy(states[indx].statetypeid, sid);
					states[indx].ientry = 0;
					states[indx].itran = 0;
					istate++;
					if (strstr(buf, ESTATEF)) continue;
					while (getend(ESTATE, 0) == EOF) {
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
							//default:
							//	fprintf(output, "**** %s\n", buf);
							//	break;
						}
					}
				}
				Processed = 1;
			} while (ret != -2);
			fclose(fp);

			if (param == 2) {
				readconst(flowfile, constfile);
				readvnames(client);
				filesOku(file1);

				myPrologue(progname, tranname, areaName);
				myApproval(avail, progname, tranname, areaName);
				writeStates(param, progname, tranname, areaName);
			}
			else
				if (param == 3) {
					readvnames(client);
					writeStates(param, progname, tranname, areaName);
					for (i = 0; i < istarting; i++) {
						fprintf(output, "%s\n", starting[i]);
					}
				}
				else
					if (param == 4) {
						int  j, k, m;
						readgetlist(getlistf);
						for (i = 0; i < istate; i++) {
							if (states[i].ientry > 0)
								for (j = 0; j < states[i].ientry; j++) {
									if (states[i].entry[j].icompcond > 0) {
										for (k = 0; k < states[i].entry[j].icompcond; k++) {
											if (states[i].entry[j].ecompcon[k].ilogical > 0)
												for (m = 0; m < states[i].entry[j].ecompcon[k].ilogical; m++) {
													if (states[i].entry[j].ecompcon[k].logical[m].firstop &&
														states[i].entry[j].ecompcon[k].logical[m].firstop[0] == '@')
														globEkle(states[i].entry[j].ecompcon[k].logical[m].firstop + 1);
													if (states[i].entry[j].ecompcon[k].logical[m].secondop &&
														states[i].entry[j].ecompcon[k].logical[m].secondop[0] == '@')
														globEkle(states[i].entry[j].ecompcon[k].logical[m].secondop + 1);
												}
										}
									}
									if (states[i].entry[j].isetval > 0) {
										for (k = 0; k < states[i].entry[j].isetval; k++) {
											if (states[i].entry[j].esetval[k].defval) {
												char *p1, *p;
												p = states[i].entry[j].esetval[k].defval;
												while (p && *p == '@') {
													p1 = strstr(p, "+--+");
													if (p1) {
														*p1 = 0;
														globEkle(p + 1);
														p = p1 + 4;
													}
													else {
														p1 = strstr(p, "+.+");
														if (p1) {
															*p1 = 0;
															globEkle(p + 1);
															p = p1 + 3;
														}
														else {
															p1 = strstr(p, "+@");
															if (p1) {
																*p1 = 0;
																globEkle(p + 1);
																p = p1 + 1;
															}
															else {
																globEkle(p + 1);
																p = 0;
															}
														}
													}
												}
											}
											if (states[i].entry[j].esetval[k].dataelm) {
												char *p1, *p;
												p = states[i].entry[j].esetval[k].dataelm;
												while (p && *p == '@') {
													p1 = strstr(p, "+--+");
													if (p1) {
														*p1 = 0;
														globEkle(p + 1);
														p = p1 + 4;
													}
													else {
														p1 = strstr(p, "+.+");
														if (p1) {
															*p1 = 0;
															globEkle(p + 1);
															p = p1 + 3;
														}
														else {
															p1 = strstr(p, "+@");
															if (p1) {
																*p1 = 0;
																globEkle(p + 1);
																p = p1 + 1;
															}
															else {
																globEkle(p + 1);
																p = 0;
															}
														}
													}
												}
											}
										}
									}
								}
						}
						globEkle("-True");
						globEkle("-retcode");
						globEkle("tranId");
						for (i = 0; i < istate; i++) {
							for (j = 0; j < states[i].ientry; j++) {
								for (k = 0; k < states[i].entry[j].isetval; k++) {
									globEkle(states[i].entry[j].esetval[k].dataelm);
								}
							}
						}
						for (i = 0; i < iglob; i++) {
							fprintf(output, "%s\n", glob[i]);
						}
						for (i = 0; i < igetlistarr; i++) {
							if (strstr(getlistarr[i], "No") == 0) {
								p = strstr(getlistarr[i], "=");
								if (p) {
									p++;
								}
								else p = getlistarr[i];
								fprintf(output, "*%s\n", p);
							}
						}
					}
					else
						if (param == 5) {
							int  i, j, k;
							char *p, *p1;
							for (i = 0; i < istate; i++) {
								for (j = 0; j < states[i].ientry; j++) {
									if (states[i].entry[j].isetval > 0)
										for (k = 0; k < states[i].entry[j].isetval; k++) {
											if(states[i].entry[j].esetval[k].defval)
												defekle(states[i].entry[j].esetval[k].defval);
										}
								}
								for (j = 0; j < states[i].itran; j++) {
									if (states[i].trans[j].tranid && strstr(states[i].trans[j].tranid, "NavController")) {
										p = strstr(states[i].trans[j].tranid, ".");
										if (p) {
											p++;
											p1 = p;
											while (*p && *p != '.') p++;
											if (p) *p = 0;
										}
										else p1 = states[i].trans[j].tranid;
										flowtagEkle(0, p1);
										flowtagEkle(1, states[i].stateid);
									}
								}
							}
							for (i = 0; i < idefval; i++) {
								char *p, *p1;
								if (strcmp(defval[i], "/>") == 0)
									fprintf(output, "init.emptrstr=\"\"\n");
								else {
									if (defval[i][0] == '@') continue;
									if (defval[i][0] == '\"') {
										p = defval[i] + 1;
										p1 = strstr(p, "\"");
										if (p1) *p1 = 0;
										fprintf(output, "init.%s=%s\n", p, p);
									}
									else fprintf(output, "init.%s=%s\n", defval[i], defval[i]);
								}
							}
							for (i = 0; i < iflowtag; i++) {
								if (flowtag[i][0] == '0')
									fprintf(output, "flowtag.%s=%s\n", flowtag[i] + 1, flowtag[i] + 1);
							}
							fprintf(output, "flowtag.Next=Next\n");
							for (i = 0; i < iflowtag; i++) {
								if (flowtag[i][0] == '1')
									fprintf(output, "func.%s=%s\n", flowtag[i] + 1, flowtag[i] + 1);
							}

						}
		}
		return 0;
}
