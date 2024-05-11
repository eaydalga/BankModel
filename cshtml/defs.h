#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBG
#define DEBGX

#define true  1
#define false 0

#define PREFS "prefs\\"
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
#define CADDPANEL "Panel"
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
#define CBUTTONGROUP "ButtonGroup("

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

#define CPERPAGE    15


#define PXCMANDA    11
#define PXSMANDA    22
#define PXSVALUE    33
#define PXSHOWMSG    44
#define PXINVISIBLE    55
#define PXDATASPLIT    66
#define PXDATAMERGE    77
#define PXQUERYLST    88
#define PXDISABLE    99
#define PXENABLE     12
#define PXSIGNAL     23
#define PXVISIBLE    34

