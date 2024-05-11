#include "defs.h"

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
		char *setTabnum;
		int iaddexit;
		struct SADDEXIT saddExit[10];
		int iaddcon;
		char *addCondition[10];
	} scmanda[50];
	int isetmanda;
	struct SETMANDA {
		char *sName;
		char *setTabnum;
		int iaddexit;
		struct SADDEXIT saddExit[10];
		int iaddcon;
		char *addCondition[10];
	} setmanda[50];
	int iInvisible;
	struct SINVISIBLE {
		char *sName;
		char *setTabnum;
		int iaddexit;
		struct SADDEXIT saddExit[10];
		int iaddcon;
		char *addCondition[10];
	} sinvisible[50];
	int isvalue;
	struct SVALUE {
		char *sName;
		char *setTabnum;
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
		char *setTabnum;
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
		char *setTabnum;
		char *dataElement;
		int iaddexit;
		struct SADDEXIT saddExit[10];
		int iaddcon;
		char *addCondition[10];
	} datasplitfunc[50];
	int idatamerge;
	struct DATAMERGE {
		char *sName;
		char *setTabnum;
		char *setMergeElements;
		int iaddexit;
		struct SADDEXIT saddExit[10];
		int iaddcon;
		char *addCondition[10];
	} datamerge[50];
	int iqueryList;
	struct QUERYLST {
		char *sName;
		char *setTabnum;
		char *sQuerylist;
		int iaddexit;
		struct SADDEXIT saddExit[10];
	} squeryList[50];
	int idisable;
	struct DISABLE {
		char *sName;
		char *setTabnum;
		int iaddexit;
		struct SADDEXIT saddExit[10];
		int iaddcon;
		char *addCondition[10];
	} sdisable[50];
	int ienable;
	struct ENABLE {
		char *sName;
		char *setTabnums;
		int iaddexit;
		struct SADDEXIT saddExit[10];
		int iaddcon;
		char *addCondition[10];
	} senable[50];
	int ivisible;
	struct VISIBLE {
		char *sName;
		char *setTabnum;
		int iaddexit;
		struct SADDEXIT saddExit[10];
		int iaddcon;
		char *addCondition[10];
	} svisible[50];
	int ilstsearch;
	struct LSTSEARCH {
		char *sName;
		char *setTabnum;
		int iaddexit;
		struct SADDEXIT saddExit[10];
		int iaddcon;
		char *addCondition[10];
	} slstsearch[50];
	int isignal;
	struct SIGNAL {
		char *sName;
		char *setTabnum;
		int iaddexit;
		struct SADDEXIT saddExit[10];
		int iaddcon;
		char *addCondition[10];
	} signal[50];
} sexit;

struct COLUMN {
	char *text;
	int  begincol;
	int  endcol;
	int  left;
	char *dataname;
	char *dtype;
	int  dpoint;
	int  size;
	int  colwidth;
	char *title;
	char *kdataname;
	int  editval;
};

int istable;
struct STABLE {
	int  tableno;
	int  tabOrder;
	char *name;
	int  mclick;
	struct BOUNDS tableBounds;
	int  icols;
	struct COLUMN cols[20];
} stable[100];

int iscroll;
struct SSCROLL {
	int  scrollno;
	char *tabOrder;
	struct BOUNDS scrollBounds;
	char *name;
	char *tablename;
} scrollfield[50];

int istext;
struct STEXTFIELD {
	int  txtno;
	char *tabOrder;
	int  txtlblno;
	char *text;
	struct BOUNDS stxtbound;
	int  enabled;
	int  required;
	char *font;
	char *dataName;
	char *name;
	char *formatter;
} stextfield[150];

int islabel;
struct SLABEL {
	int  lblno;
	char *tabOrder;
	char *lbl;
	struct BOUNDS slblbound;
	char *name;
	char *text;
	char *lbltext;
} slabel[150];

int irbutton;
struct RBUTTON {
	int  rbutno;
	char *rbut;
	struct BOUNDS rbutBound;
	int  rbutEnabled;
	int  disable;
	char *rbutTab;
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
	char *butTabOrder;
} button[50];

int icombox;
struct COMBOX {
	int comboNo;
	char *comboTabOrder;
	struct BOUNDS comboBounds;
	char *fcomboxName;
	char *comboxName;
	char *dataName;
	char *setvalfname;
	char *setvalin;
	int  setkeyvals;
	int  setreq;
	char *setfname;
	char *setdnamelst;
} combox[100];

int ichkno;
struct CHECKBOX {
	int checkNo;
	char *checkTabOrder;
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

int isgroup;
struct SGROUP {
	int txtno;
	int txtlblno;
	char *text;
	char *dataName;
	char *name;
	int  txtline;
} sgroup[50];
