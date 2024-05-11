#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proc.h"

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

int islipptr;
struct SLIPPTR {
	char* sfname;
	char* sname;
	int isline;
	struct SLINE sline[200];
};
struct SLIPPTR slipptr[5];

struct REGDATA {
	char* regdname;
	char* regfunc;
	int  regpage;
	int  regchange;
	char* regusebrk;
	int  idata;
	struct SLINE ddata[50];
};

struct BREAK {
	char* icol;
	char* id;
	int ibline;
	struct SLINE bline[20];
};

int idocptr;
struct DOCPTR {
	char* dfname;
	char* dname;
	int	 iheader;
	struct SLINE dheader[50];
	struct REGDATA regdata;
	int ibreak;
	struct BREAK dbreak[10];
};
struct DOCPTR docptr[5];

extern void rmnl(char*);
char* getp(char* data, char* s, char* bf)
{
	char* p, * p1;
	char bfx[300];
	strcpy(bfx, bf);
	p = strstr(bf, s);
	if (p) {
		p = p + strlen(p);
		p1 = strstr(p, ":");
		if (p1) *p1 = 0;
	}
	if(p) strcpy(data, p);
	strcpy(bf, bfx);
	return data;
}

char* getline(char* rdata, char* tdata, char* ndata, char* bdata, char* cdata, char* fdata, char* adata, char* ldata, char* pdata, char* xbuf)
{
	char* p;
	p = getp(rdata, ":row=", xbuf);
	p = getp(tdata, "type=", xbuf);
	if (p) {
		ndata[0] = 0;
		bdata[0] = 0;
		if(strcmp(tdata, "DATA") == 0)
			p = getp(ndata, "name=", xbuf);
		if (strcmp(tdata, "LABEL") == 0)
			p = getp(bdata, "label=", xbuf);
	}
	p = getp(cdata, "col=", xbuf);
	p = getp(fdata, "fmt=", xbuf);
	if (p) {
		if (strcmp(fdata, "Currency") == 0) {
			p = getp(adata, "align=", xbuf);
			p = getp(ldata, "len=", xbuf);
			p = getp(pdata, "prec=", xbuf);
		}
	}
	return p;
}

void readslip(char* trn, char* dir)
{
	FILE* fp;
	char* p, * p1;
	char rdata[200], tdata[200], ndata[200], bdata[200],
		cdata[200], fdata[200], adata[200], ldata[200], pdata[200];
	char fname[300], xbuf[300];
	int i, j;
	strcpy(fname, dir);
	strcat(fname, "\\");
	strcat(fname, PREFS);
	strcat(fname, trn);
	strcat(fname, "printer2.pref");
	fp = fopen(fname, "r");
	if (fp) {
		while (fgets(xbuf, MAXCHAR, fp)) {
			rmnl(xbuf);
			if (xbuf[0] == '2') {
				i = islipptr;
				islipptr++;
				p = strstr(xbuf, "\"");
				if (p) {
					p++;
					p1 = strstr(p, "\"");
					if (p1) {
						*p1 = 0;
						p1++;
					}
					slipptr[i].sfname = (char*)calloc(1, strlen(p) + 1);
					strcpy(slipptr[i].sfname, p);
					slipptr[i].isline = 0;
					p = p1;
				}
				if (p) p = strstr(p, ":");
				if (p) {
					p++;
					slipptr[i].sname = (char*)calloc(1, strlen(p) + 1);
					strcpy(slipptr[i].sname, p);
					slipptr[i].isline = 0;
				}
				else break;
			}
			if (xbuf[0] == ' ') {
				p = getline(rdata, tdata, ndata, bdata, cdata, fdata, adata, ldata, pdata, xbuf);
				if(p) {
					if (rdata[0]) {
						j = slipptr[i].isline;
						slipptr[i].isline++;
						slipptr[i].sline[j].row = atoi(rdata);
					}
					if (tdata[0]) {
						slipptr[i].sline[j].type = (char *)calloc(1, strlen(tdata)+1);
						strcpy(slipptr[i].sline[j].type, tdata);
					}
					if (ndata[0]) {
						slipptr[i].sline[j].dname = (char*)calloc(1, strlen(ndata) + 1);
						strcpy(slipptr[i].sline[j].type, ndata);
					}
					if (bdata[0]) {
						slipptr[i].sline[j].label = (char*)calloc(1, strlen(bdata) + 1);
						strcpy(slipptr[i].sline[j].label, bdata);
					}
					if (cdata[0]) {
						slipptr[i].sline[j].col = atoi(cdata);
					}
					if (fdata[0]) {
						slipptr[i].sline[j].fmt = (char*)calloc(1, strlen(fdata) + 1);
						strcpy(slipptr[i].sline[j].fmt, fdata);
						if (strcmp(slipptr[i].sline[j].fmt, "Currency") == 0) {
							if(adata[0])
								slipptr[i].sline[j].align = atoi(adata);
							if (ldata[0])
								slipptr[i].sline[j].len = atoi(ldata);
							if (pdata[0])
								slipptr[i].sline[j].prec = atoi(pdata);
						}
					}
				}
			}
		}
		fclose(fp);
	}
}

void slineTasi(struct SLINE *p, char *rdata, char *tdata, char* ndata, char* bdata, char* cdata, char* fdata, char* adata, char* ldata, char* pdata)
{
	if (rdata[0]) {
		p->row = atoi(rdata);
	}
	if (tdata[0]) {
		p->type = (char*)calloc(1, strlen(tdata) + 1);
		strcpy(p->type, tdata);
	}
	if (ndata[0]) {
		p->dname = (char*)calloc(1, strlen(ndata) + 1);
		strcpy(p->dname, ndata);
	}
	if (bdata[0]) {
		p->label = (char*)calloc(1, strlen(bdata) + 1);
		strcpy(p->label, bdata);
	}
	if (cdata[0])
		p->col = atoi(cdata);
	if (fdata[0]) {
		p->fmt = (char*)calloc(1, strlen(fdata) + 1);
		strcpy(p->fmt, fdata);
		if (strcmp(p->fmt, "Currency") == 0) {
			if (adata)
				p->align = atoi(adata);
			if (ldata)
				p->len = atoi(ldata);
			if (pdata)
				p->prec = atoi(pdata);
		}
	}
}

void readdoc(char* trn, char* dir)
{
	FILE* fp;
	char* p, * p1, data[300];
	char rdata[200], tdata[200], ndata[200], bdata[200],
		cdata[200], fdata[200], adata[200], ldata[200], pdata[200];
	char bidata[200], bcdata[200];
	char dname[200], dfunc[20], dpage[20], dchange[100], duse[200];
	char fname[300], xbuf[300];
	int  i, j, k;
	int regheader = 0;
	int regdata = 0;
	int regbreak = 0;
	strcpy(fname, dir);
	strcat(fname, "\\");
	strcat(fname, PREFS);
	strcat(fname, trn);
	strcat(fname, "printer1.pref");
	fp = fopen(fname, "r");
	if (fp) {
		while(fgets(xbuf, MAXCHAR, fp)) {
			rmnl(xbuf);
			if (xbuf[0] == '1') {
				i = idocptr;
				idocptr++;
				p = strstr(xbuf, "\"");
				if (p) {
					p++;
					p1 = strstr(p, "\"");
					if(p1) {
						*p1 = 0;
						p1++;
					}
					docptr[i].dfname = (char*)calloc(1, strlen(p) + 1);
					strcpy(docptr[i].dfname, p);
					p = p1;
				}
				if (p) p = strstr(p, ":");
				if (p) {
					p++;
					docptr[i].dname = (char*)calloc(1, strlen(p) + 1);
					strcpy(docptr[i].dname, p);
					docptr[i].iheader = 0;
					docptr[i].regdata.idata = 0;
					docptr[i].ibreak = 0;
				}
				else break;
			}
			if (xbuf[0] == '0') { 
				p = getp(data, ":regheader", xbuf);
				if (p) {
					regheader = 1;
					regdata = 0;
					regbreak = 0;
				}
				else {
					p = getp(data, ":regdata", xbuf);
					if (p) {
						regheader = 0;
						regdata = 1;
						regbreak = 0;
						p = getp(dname, "dname=", xbuf);
						if (p) {
							docptr[i].regdata.regdname = (char*)calloc(1, strlen(dname) + 1);
							strcpy(docptr[i].regdata.regdname, dname);
							p = getp(dfunc, "func=", xbuf);
							if (p) {
								docptr[i].regdata.regfunc = (char*)calloc(1, strlen(dfunc) + 1);
								strcpy(docptr[i].regdata.regfunc, dfunc);
							}
							p = getp(dpage, "page=", xbuf);
							if (p) docptr[i].regdata.regpage = atoi(dpage);
							p = getp(dchange, "change=", xbuf);
							if (p) docptr[i].regdata.regchange = atoi(dchange);
							p = getp(duse, "userbrk=", xbuf);
							if (p) {
								docptr[i].regdata.regusebrk = (char*)calloc(1, strlen(duse) + 1);
								strcpy(docptr[i].regdata.regusebrk, duse);
							}
						}
					}
					else {
						p = getp(data, ":regbreak", xbuf);
						if (p) {
							regheader = 0;
							regdata = 0;
							regbreak = 1;
							p = getp(bcdata, "icol=", xbuf);
							if (p) p = getp(bidata, "id=", xbuf);
						}
					}
				}
			}
			if (xbuf[0] == ' ') {
				if (regheader) {
					p = getline(rdata, tdata, ndata, bdata, cdata, fdata, adata, ldata, pdata, xbuf);
					if (p) {
						if (rdata[0]) {
							j = docptr[i].iheader;
							docptr[i].iheader++;
						}
						slineTasi(&docptr[i].dheader[j], rdata, tdata, ndata, bdata, cdata, fdata, adata, ldata, pdata);
					}
				}
				if (regdata) {
					p = getline(rdata, tdata, ndata, bdata, cdata, fdata, adata, ldata, pdata, xbuf);
					if (p) {
						if (rdata[0]) {
							j = docptr[i].regdata.idata;
							docptr[i].regdata.idata++;
						}
						slineTasi(&docptr[i].regdata.ddata[j], rdata, tdata, ndata, bdata, cdata, fdata, adata, ldata, pdata);
					}
				}
				if (regbreak) {
					p = getline(rdata, tdata, ndata, bdata, cdata, fdata, adata, ldata, pdata, xbuf);
					if (p) {
						if (docptr[i].ibreak == 0) {
							if (bcdata[0]) {
								j = docptr[i].ibreak;
								docptr[i].ibreak++;
								docptr[i].dbreak[j].icol = (char*)calloc(1, strlen(bcdata) + 1);
								strcpy(docptr[i].dbreak[j].icol, bcdata);
								if (bidata[0]) {
									docptr[i].dbreak[j].id = (char *)calloc(1, strlen(bidata)+1);
									strcpy(docptr[i].dbreak[j].id, bidata);
								}
							}
						}
						if (rdata[0]) {
							k = docptr[i].dbreak[j].ibline;
							docptr[i].dbreak[j].ibline++;
						}
						slineTasi(&docptr[i].dbreak[j].bline[k], rdata, tdata, ndata, bdata, cdata, fdata, adata, ldata, pdata);
					}
				}
			}
		}
		fclose(fp);
	}
}

int vnameAl(char* vmodel)
{
	int i;
	for (i = 0; i < ivname; i++) {
		if (strcmp(vname[i].viewname, vmodel) == 0)
			return i;
	}
	return -1;
}

char* modeldenAl(int i, char* s)
{
	int j;
	for (j = 0; j < vname[i].ivitem; j++) {
		if (strcmp(vname[i].items[j].vitem, s) == 0)
			return s;
	}
	return 0;
}


void MymodelToPrint(char* viewmodel, char *printerName)
{
	int  i, j;
	char* p;
	char* pdoviz = "dvzKodu";
	int ivm = vnameAl(viewmodel);

	fprintf(output, "        public SlipPrintModel %smodelToprint(%sModel model, IBranchBusinessContext context)\n", tranname, viewmodel);
	fprintf(output, "        {\n");
	fprintf(output, "			SlipPrintModel printModel = new SlipPrintModel(); \n");
	fprintf(output, "        	if (model != null)\n");
	fprintf(output, "        	{\n");

	fprintf(output, "        		string dovizAdi = context.CommonService.GetCurrencyName(); \n");
	fprintf(output, "        		string branchCode = context.Session.User.Branch.Code;\n");
	fprintf(output, "        		string branchName = context.Session.User.Branch.Name;\n");
	fprintf(output, "        		string userName = context.Session.User.UserName;\n");
	fprintf(output, "        		printModel.slipTransactionName = %sConstants.SlipTransactionName; \n", tranname);
	fprintf(output, "        		printModel.slipTaskCode = %sConstants.SlipTaskCode; \n", tranname);
	fprintf(output, "        		printModel.slipBranchCode = branchCode; \n");
	fprintf(output, "        		printModel.slipBranchName = branchName; \n");
	fprintf(output, "        		printModel.slipIslemTarihi = DateTime.Now.ToString(%sConstants.DateTimeFormatStr, System.Globalization.CultureInfo.InvariantCulture); \n", tranname);
	fprintf(output, "        		printModel.slipAlacakliValorTarihi = DateTime.Now.ToString(%sConstants.DateFormatStr, System.Globalization.CultureInfo.InvariantCulture); \n", tranname);
	fprintf(output, "        		printModel.slipSchRefFis = ; \n");
	fprintf(output, "        		printModel.slipDovizKodu1 = dovizKodu.ToString();\n");
	fprintf(output, "        		printModel.slipKullaniciFisNo = kullanýcýDekontNo;\n");
	fprintf(output, "        		printModel.slipSubeFisNo =fisNo;\n");

	fprintf(output, "        		//TODO: Burasý düzelecek\n");
	fprintf(output, "        		//printModel.slipAciklama1 = aciklama;\n");
	fprintf(output, "        		//printModel.slipDovizAdi1 = dovizAdi; \n");
	fprintf(output, "        		//printModel.slipPerformerUserName = userName; \n");
	fprintf(output, "        		//printModel.slipKarsiSubeKodu = model.KarsiSube;\n");
	fprintf(output, "        		//printModel.slipKarsiSubeAdi = context.CommonService.GetSubeAdi(model.KarsiSube, false);\n");
	fprintf(output, "        		//printModel.slipAmountList = amountList;\n");
	fprintf(output, "        		//printModel.slipTotalAmount = string.Format(\"{0:n}\", model.IslemTutar);\n");
	fprintf(output, "        		//printModel.slipTotalAmountText = context.CommonService.ConvertNumberToStringFormatted(model.AmountList.Where(x => x.debitCreditType == DebitCreditType.Debit).Sum(x => Convert.ToDecimal(x.value)));\n");
	fprintf(output, "        		//printModel.slipTotalAmountCredit = string.Format(\"{0:n}\", model.AmountList.Where(x => x.debitCreditType == DebitCreditType.Credit).Sum(x => Convert.ToDecimal(x.value)));\n");
	fprintf(output, "        		//printModel.slipTotalAmountDebit = string.Format(\"{0:n}\", model.AmountList.Where(x => x.debitCreditType == DebitCreditType.Debit).Sum(x => Convert.ToDecimal(x.value)));\n");
	fprintf(output, "        		//printModel.slipTotalAmountCurrency = context.CommonService.GetCurrencyName(dovizKodu.ToString().PadLeft(3, '0'));\n");
	fprintf(output, "        		//TODO: Bitti\n");

	for (i = 0; i < islipptr; i++) {
		if (strcmp(slipptr[i].sname, printerName) == 0) {
			for (j = 0; j < slipptr[i].isline; j++) {
				if (slipptr[i].sline[j].dname[0]) {
					p = modeldenAl(ivm, slipptr[i].sline[j].dname);
					if (p)
						fprintf(output, "        		printModel.slip%s = model.%s;\n", p, p);
					else fprintf(output, "        		// printModel.slip%s = ;\n", slipptr[i].sline[j].dname);
				}
			}
		}
	}

	fprintf(output, "        		if (context.Session.User.ClientInfo.SSMBranchFlag)\n");
	fprintf(output, "        		{\n");
	fprintf(output, "        			//model.AmountList.Where(x => x.explanation.ToString().Trim() == \"SCH\").FirstOrDefault().debitCreditType = DebitCreditType.General;\n");
	fprintf(output, "        		}\n");
	fprintf(output, "        		printModel.OperationResult.Message = null;\n");

	fprintf(output, "        	}\n");
	fprintf(output, "        	return printModel;\n");
	fprintf(output, "        }\n");
}
