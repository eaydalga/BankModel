#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true  1
#define false 0

#define  SEPERATOR "\\"
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
#define CCOMBOBOX  "kbankComboBox "
#define CCHECKBOX  "kbankCheckBox "
#define CLOADER "com.akbank.client.staticdata.DataLoader "
#define LOADSTR "load("
#define CQUERYLSTFUNC "queryListFunction"
#define CSETQUERYLST  "setQueryString("
#define CBUTTONGROUP "ButtonGroup("

#define MXCHAR    200
#define MAXCHAR   200
#define MAXLABELS 200
#define LBLMAX    20
#define LBLSIZE   40
#define MAXTXT    200
#define TXTMAX    20
#define TXTSIZE   100
#define NPANEL    10
#define MAXBTN    400
#define BTNSIZE   100
#define INMAX     300

#define CINIT "initialize()"
#define CENDINIT "}"
#define CENDINIT2 "    }"
#define CBEGIN "{"
// this.setName("name"); --> <h1> name </h1>
#define CPAGE ".setName("
// this.setTitle("YatirimFonuAlim_MuVMeVDview");
#define CTITLE ".setTitle("
// this.setBounds(0, 0, 739, 599); css -> border()
#define CBOUND ".setBounds("
// this.add(get{panelname}(), null);  <div name=panelname> ... </div>
#define CADD ".add(get"
// this.add(get{buttonname}(), null);  <div name=buttonname> ... </div>
#define CADDPANEL "Panel"
#define CADDBUTTON "Button"
// get{buttongrp}().add(get{AkbankRadioButton}());
#define CSCROLL   "crollPane"
#define CSTABLE   "kbankTable get"
#define CTABLE   "kbankTable "
#define CGETGRP "getAn"
#define CSTABLES   "kbankSmartTable get"
#define CTABLES   "kbankSmartTable "
#define CTABLESP   "kbankSmartTableScroll "
#define CGETGRPS "getAn"
#define CLAYOUT "this.setLayout("

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
#define CADDEXIT "ddExitEvent(get"
#define CADDEXITS "addExitEvent(this"
#define CSHOWMSG "howMessageFunction"
#define CSETVALUE "etValueFunction"
#define CDATAMERGE "ataMergeFunction"
#define CDATASPLIT "ataSplitFunction"
#define CCLEAR "learMandatoryFunction"
#define CSETCLEAR "etMandatorysFunction"
#define CENABLE "enableFunction"
#define CDISABLE "disableFunction"
#define CVISIBLE "visibleFunction"
#define CLSTSEARCH "listSearchFunction"
#define CSIGNAL "signalFunction"
#define CINVISIBLE "nvisibleFunction"
#define CADDCONDITION "ddCondition("
#define CCONDITION ".Condition."
#define CSETTABNUM    "etTabNumber("
#define CSETTAB "etTabNumbers("
#define CSETTABD "setTabNumbersToDisable("
#define CSETTABS "setTabNumbersToEnable("
#define CSETMERGEELEMENTS "setMergeElements("
#define CANDCONDITION "ndCondition"

#define CSETTITLE "etTitle("
#define CSETMSG "etMessage("
#define CSETMSGTYPE "etMessageType("
#define CSETMSGOPTION "etOptionType("

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


#define CPANELDEC "client.widgets.AkbankTitledEmbeddedPanel get"
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


#define CLBLFUNC "kbankLabel get"
#define CTXTFUNC "kbankTextField get"
#define CRBUTTON "kbankRadioButton get"
#define CGETBUTTON "kbankButton get"
#define COMBOBOX  "kbankComboBox get"
#define CHECKBOX  "kbankCheckBox get"
#define SCROLL    "kbankTableScrollPane get"
#define SCROLLS    "kbankSmartTableScrollPane get"

#define panelTITLE ".setTitle("

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
#define TXTDATE    "DateConverter"

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

#define CHKBOUND "setBounds("
#define CHKFONT  "setFont("
#define CHKDNAME "setDataName("
#define CHKNAME "setName("
#define CHKTXT  "setText("
#define CHKSVAL  "setSelectedValue("
#define CHKUVAL  "setUnSelectedValue("
#define CHKSTAB  "setTabOrder("

#define SETVALFNAME "setValueFieldName("
#define SETVALIN "setValueInContext("
#define SETKEYVAL "setUseKeyValues("
#define SETFNAME "setIdFieldName("
#define SETDNAMELST "setDataNameForList("
#define SETREQ "setRequired("

#define RSON 3

#define PREFS "prefs\\"

#define PXCMANDA    11
#define PXSMANDA    22
#define PXSVALUE    33
#define PXSHOWMSG    44
#define PXINVISIBLE    55
#define PXDATASPLIT    66
#define PXDATAMERGE    77
#define PXQUERYLST    88
#define PXDISABLE     99
#define PXENABLE      12
#define PXSIGNAL      23
#define PXVISIBLE     34
#define PXLSTSEARCH   89

#define VMAX 20
#define MMAX 20
#define IMAX 100

#define STRING  "1"
#define NUMERIC "3"

#define CPERPAGE   15
