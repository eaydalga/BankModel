
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

extern int extraParam(char *);
extern FILE *output;
extern char * indentstr();
extern int iextras;
extern char* extras[200];

void extrasYaz()
{
	int i;
	for (i = 0; i < iextras; i++) {
		if (strcmp(extras[i], "mvdhesap") == 0 && extraParam("mvdhesap")) {
			fprintf(output, "%s", indentstr());
			fprintf(output, "var accts = Context.CommonService.GetCustomerAccounts();\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "List<ListTypes> list = new List<ListTypes>(); \n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "foreach(var acc in accts.MvdHesapList) {\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "	list.Add(new ListTypes(){\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "		Text = acc.Sube + \"--\" + acc.HesapNo + \"--\" + acc.HesapTipi + \"--\" + acc.HesapTuru + \"--\" + acc.DovizKodu,\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "		Value = acc.Sube + \"--\" + acc.HesapNo + \"--\" + acc.HesapTuru\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "	});\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "}\n");
			fprintf(output, "%s", indentstr());
			fprintf(output, "global.mevHesNoComboList = list; // modelde baska bir degisken de olabilir\n");
		}
		else
			if (strcmp(extras[i], "opdDurum") == 0 && extraParam("opdDurum")) {
				fprintf(output, "%s", indentstr());
				fprintf(output, "// --------------- bu liste uygulamaya göre sonradan eklendi --------------------------------\n");
				fprintf(output, "%s", indentstr());
				fprintf(output, "global.odpDurumList = new List<ListTypes>();\n");
				fprintf(output, "%s", indentstr());
				fprintf(output, "global.odpDurumList.Add(new ListTypes(){ Text = \"HAZIRLAMADA\", Value = \"H\" });\n");
				fprintf(output, "%s", indentstr());
				fprintf(output, "global.odpDurumList.Add(new ListTypes(){ Text = \"ONAYLANDI\", Value = \"O\" });\n");
				fprintf(output, "%s", indentstr());
				fprintf(output, "global.odpDurumList.Add(new ListTypes(){ Text = \"REJECTED\", Value = \"R\" }); \n");
				fprintf(output, "// ---------------- sonradan eklemenin sonu -----------------------\n");
			}
			else
				if (strcmp(extras[i], "hesDurum") == 0 && extraParam("hesDurum")) {
					fprintf(output, "// --------------- bu liste uygulamaya göre sonradan eklendi --------------------------------\n");
					fprintf(output, "%s", indentstr());
					fprintf(output, "global.hesDurumList = new List<ListTypes>();\n");
					fprintf(output, "%s", indentstr());
					fprintf(output, "global.hesDurumList.Add(new ListTypes(){ Text = \"AKTİF\", Value = \"A\" });\n");
					fprintf(output, "%s", indentstr());
					fprintf(output, "global.hesDurumList.Add(new ListTypes(){ Text = \"GECİKMİŞ\", Value = \"G\" });\n");
					fprintf(output, "%s", indentstr());
					fprintf(output, "global.hesDurumList.Add(new ListTypes(){ Text = \"KAPALI\", Value = \"K\" });\n");
					fprintf(output, "%s", indentstr());
					fprintf(output, "global.hesDurumList.Add(new ListTypes(){ Text = \"TAKİP\", Value = \"T\" });\n");
					fprintf(output, "%s", indentstr());
					fprintf(output, "// ---------------- sonradan eklemenin sonu -----------------------\n");
				}
				else
					if (strcmp(extras[i], "birimMahiyeti") == 0 && extraParam("bildirimMahiyeti")) {
						fprintf(output, "// --------------- bu liste uygulamaya göre sonradan eklendi --------------------------------\n");
						fprintf(output, "%s", indentstr());
						fprintf(output, "global.bildirimMahiyetiList = new List<ListTypes>();\n");
						fprintf(output, "%s", indentstr());
						fprintf(output, "global.bildirimMahiyetiList.Add(new ListTypes(){ Text = \"POSTFINANSMAN SATIS\", Value = \"D\"}); \n");
						fprintf(output, "%s", indentstr());
						fprintf(output, "global.bildirimMahiyetiList.Add(new ListTypes(){ Text = \"POSTFINANSMAN ALIS\", Value = \"C\"  });\n");
						fprintf(output, "%s", indentstr());
						fprintf(output, "global.bildirimMahiyetiList.Add(new ListTypes(){ Text = \"YURTDIŞI KREDİ KULLANDIRIM\", Value = \"9\" });\n");
						fprintf(output, "%s", indentstr());
						fprintf(output, "global.bildirimMahiyetiList.Add(new ListTypes(){ Text = \"KREDİ KAPAMA\", Value = \"8\" });\n");
						fprintf(output, "%s", indentstr());
						fprintf(output, "global.bildirimMahiyetiList.Add(new ListTypes(){ Text = \"KREDİ KULLANDIRIM\", Value = \"7\" });\n");
						fprintf(output, "%s", indentstr());
						fprintf(output, "global.bildirimMahiyetiList.Add(new ListTypes(){ Text = \"DTH SATIŞ\", Value = \"6\"});\n");
						fprintf(output, "%s", indentstr());
						fprintf(output, "global.bildirimMahiyetiList.Add(new ListTypes(){ Text = \"DTH ALIŞ\", Value = \"5\"});\n");
						fprintf(output, "%s", indentstr());
						fprintf(output, "global.bildirimMahiyetiList.Add(new ListTypes(){ Text = \"EFEKTİF SATIŞ\", Value = \"4\"});\n");
						fprintf(output, "%s", indentstr());
						fprintf(output, "global.bildirimMahiyetiList.Add(new ListTypes(){ Text = \"EFEKTİF ALIŞ\", Value = \"3\"});\n");
						fprintf(output, "%s", indentstr());
						fprintf(output, "global.bildirimMahiyetiList.Add(new ListTypes(){ Text = \"İTHALAT DÖVİZ SATIŞ\", Value = \"2\"}); \n");
						fprintf(output, "%s", indentstr());
						fprintf(output, "global.bildirimMahiyetiList.Add(new ListTypes(){ Text = \"İHRACAT DÖVİZ ALIŞ\", Value = \"1\"});\n");
						fprintf(output, "%s", indentstr());
						fprintf(output, "global.bildirimMahiyetiList.Add(new ListTypes(){ Text = \"HEPSİ\", Value = \"H\"});\n");
						fprintf(output, "%s", indentstr());
						fprintf(output, "global.bildirimMahiyetiList.Add(new ListTypes(){ Text = \"YURTDIŞI KREDİ KAPAMA\", Value = \"0\"});\n");
						fprintf(output, "%s", indentstr());
						fprintf(output, "// ---------------- sonradan eklemenin sonu -----------------------\n");
					}
					else {
						if (!(extraParam("getNewCreditAccounts") || extraParam("getKrediTakipHesaplari"))) {
							// getlist gibi olacak
							if (strlen(extras[i]) > 2) {
								fprintf(output, "%s", indentstr());
								fprintf(output, "global.%s = Context.CommonService.GetListItems(ListConstants.%s);\n", extras[i], extras[i]);
							}
						}
					}
	}
}