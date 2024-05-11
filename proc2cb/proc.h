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

struct EXEC {
	char* execid;
	char* execop;
	char* execmon;
	char* execlast;
	char* execmaint;
	char* execappr;
	char* execlnk;
};

struct BUTTON {
	char* buttontext;
	char* buttontabOrder;
	char* buttonlastStep;
	char* buttonvisible;
};

struct OPENX {
	char* openid;
	char* viewname;
	char* viewsrc;
	char* lnkcontext;
	char* tabinter;
	char* title;
	char* footermsg;
	int  approval;
	int  apptype;
	int  ibuttons;
	struct BUTTON buttons[SMAX];
};

struct SETVAL {
	char* dataelm;
	char* defval;
};

struct ADDVAL {
	char* addid;
	char* dataelm;
	char* defval;
};


struct LOGICAL {
	char* opname;
	char* firstop;
	char* secondop;
};

struct COMPCON {
	char* onTrue;
	char* onFalse;
	int  ilogical;
	struct LOGICAL logical[SMAX];
};

struct SHOWMSG {
	char* showid;
	char* message;
	char* title;
	char* messageType;
	char* optionType;
	char* defaultOption;
};

struct GETSHARE {
	char* shareid;
	char* sharecvar;
	char* sharevar;
};

struct SETSHARE {
	char* setid;
	char* setcvar;
	char* setvar;
};

struct PAD {
	char* padid;
	char* dname;
	char* padchar;
	char* padlen;
	char* padalign;
};

struct CCCF {
	char* ccfid;
	char* cust;
	char* sig;
};

struct GEN {
	char* genid;
	char* genacc;
	char* genbr;
	char* gencd;
	char* geniban;
	char* genexpid;
};

struct GENEXP {
	char* genid;
	char* genexpid;
};

struct MAES {
	char* maesid;
	char* maesdocbr;
	char* maesdocdt;
	char* maesdocmaint;
	char* maesview;
	char* maesdoctype;
	char* maesoptype;
	char* maesdochost;
	char* maesdocid;
	char* maesdoccust;
	char* maesscan;
};

struct TRIM {
	char* trimid;
	char* trimvar;
	char* trimchar;
	char* trimdir;
};

struct INITCOLL {
	char* id;
	char* delm;
};

struct RMCOLL {
	char* id;
	char* delm;
	char* poly;
	char* repno;
};

struct RMCONTEXT {
	char* id;
	char* delm;
};

struct UNSTR {
	char* src;
	int  start;
	int  len;
};

struct TRACE {
	char* traceid;
	char* trace0;
	char* trace1;
	char* trace2;
};
struct ENTRY {
	char* initid;
	int  iexec;
	struct EXEC eexec[SMAX];
	int  iopen;
	struct OPENX sopen[SMAX];
	int  isetval;
	struct SETVAL esetval[SMAX];
	int  iaddval;
	struct ADDVAL eaddval[SMAX];
	char* eprintid;
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
	char* tranid;
	char* trantarget;
	char* closes;
};

struct STATE {
	char* stateid;
	char* statetype;
	char* statetypeid;
	int  isref;
	char* staterefs[SMAX];
	char* statermodel;
	char* stateimodel;
	int  ientry;
	int  itran;
	struct ENTRY entry[5];
	struct TRANSITION trans[10];
};
extern struct STATE states[STATEMAX];
extern int istate;

extern int  ivname;
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
};

extern struct VNAME vname[VMAX];

extern FILE* output;
extern char tranname[200];
