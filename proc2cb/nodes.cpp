#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proc.h"

int inode;
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
} nodes[100];

extern FILE* input, * output;
extern char indexname[200];

int  ieski;
char* eskisi[100];
int eskiVarmi(char* s)
{
	int i;
	for (i = 0; i < ieski; i++) {
		if (strcmp(eskisi[i], s) == 0)
			return 1;
	}
	i = ieski;
	eskisi[i] = (char*)calloc(1, strlen(s) + 1);
	strcpy(eskisi[i], s);
	ieski++;
	return 0;
}

int mystateBak(char* s)
{
	int i;
	for (i = 0; i < ieski; i++) {
		if (strcmp(states[i].stateid, s) == 0)
			return i;
	}
	return -1;
}
void oncekineTasi(struct NODE* p)
{
	if (p->previous) {
		if (p->previous->viewmodel == NULL) {
			p->previous->viewmodel = p->viewmodel;
			if (p->previous->ninmodel == NULL) p->previous->ninmodel = p->viewmodel;
			oncekineTasi(p->previous);
		}
	}
}
struct NODE* nodeBak(char* s)
{
	int i;
	for (i = 0; i < inode; i++) {
		if (strcmp(nodes[i].nstate, s) == 0)
			return &nodes[i];
	}
	return 0;
}
struct NODE* nodeEkle(int, struct NODE*);

void compTara(char* s, int i)
{
	char* py;
	int  jj, ss;
	struct NODE* pnode;
	if (s && strcmp(s, "continue")) {
		py = strstr(s, "changeState(");
		if (py) {
			py = py + 12;
			ss = mystateBak(py);
			if (ss >= 0) {
				pnode = nodeEkle(ss, &nodes[i]);
				jj = nodes[i].inext;
				nodes[i].next[jj] = pnode;
				nodes[jj].inext++;
			}
		}
		else {
			ss = mystateBak(s);
			if (ss >= 0) {
				pnode = nodeEkle(ss, &nodes[i]);
				jj = nodes[i].inext;
				nodes[i].next[jj] = pnode;
				nodes[i].inext++;
			}
		}
	}
}
void rearrange(struct NODE* pnode)
{
	if (pnode->viewmodel) {
		if (pnode->ninmodel) {
			if (pnode->nretmodel == NULL) pnode->ninmodel;
		}
		else {
			pnode->nretmodel = pnode->viewmodel;
			pnode->ninmodel = pnode->viewmodel;
		}
	}
	else {
		pnode->nretmodel = NULL;
		pnode->ninmodel = NULL;
	}
}

struct NODE* nodeEkle(int ss, struct NODE* pnode)
{
	int i, j, k;
	struct STATE* st;
	struct NODE* px, * ppnode;
	char* s;
	st = &states[ss];
	s = st->stateid;
	px = nodeBak(s);
	if(px)
		return px;
	i = inode;
	inode++;
	nodes[i].nstate = (char*)calloc(1, strlen(s) + 1);
	strcpy(nodes[i].nstate, s);
	nodes[i].viewmodel = 0;
	nodes[i].bomodel = 0;
	nodes[i].nstatetype = (char*)calloc(1, strlen(st->statetype) + 1);
	strcpy(nodes[i].nstatetype, st->statetype);
	if (pnode)
		nodes[i].previous = pnode;
	else {
		nodes[i].nretmodel = indexname;
		nodes[i].ninmodel = indexname;
	}
	if (st->ientry > 0) {
		for (j = 0; j < st->ientry; j++) {
			for (k = 0; k < st->entry[j].iopen; k++) {
				if (st->entry[j].sopen[k].viewname && !strstr(st->entry[j].sopen[k].viewname, "filler")) {
					nodes[i].viewmodel = (char*)calloc(1, strlen(st->entry[j].sopen[k].viewname) + 1);
					strcpy(nodes[i].viewmodel, st->entry[j].sopen[k].viewname);
					oncekineTasi(&nodes[i]);
				}
			}

			for (k = 0; k < st->entry[j].iexec; k++) {
				if (st->entry[i].eexec[k].execop) {
					char xbuf[200];
					strcpy(xbuf, st->entry[j].eexec[k].execop);
					nodes[i].bomodel = (char*)calloc(1, strlen(xbuf) + 1);
					strcpy(nodes[i].bomodel, xbuf);
					nodes[i].ninmodel = nodes[i].bomodel;
				}
			}
			for (k = 0; k < st->entry[j].icompcond; k++) {
				if (st->entry[j].ecompcon[k].onTrue) {
					compTara(st->entry[j].ecompcon[k].onTrue, i);
				}
				if (st->entry[j].ecompcon[k].onFalse) {
					compTara(st->entry[j].ecompcon[k].onFalse, i);
				}
			}
		}
	}
	if (st->itran > 0) {
		int jj;
		for (j = 0; j < st->itran; j++) {
			if (eskiVarmi(st->trans[j].trantarget) == 0) {
				ss = mystateBak(st->trans[j].trantarget);
				if (ss >= 0) {
					ppnode = nodeEkle(ss, &nodes[i]);
					jj = nodes[i].inext;
					nodes[i].next[jj] = ppnode;
					nodes[i].inext++;
				}
			}
			else {
				struct NODE* pxnode;
				pxnode = nodeBak(st->trans[j].trantarget);
				if (pxnode) {
					jj = nodes[i].inext;
					nodes[i].next[jj] = pxnode;
					nodes[i].inext++;
				}
			}
		}
	}
	return &nodes[i];
}
void statesYap()
{
	int i;
	struct NODE* pnode;
	pnode = 0;
	for (i = 0; i < istate; i++) {
		if (eskiVarmi(states[i].stateid) == 0) {
			pnode = nodeEkle(i, pnode);
		}
	}
	for (i = 0; i < inode; i++) {
		rearrange(&nodes[i]);
	}
}

void writeMyStates()
{
	int i, j;
	struct NODE* px;
	for (i = 0; i < istate; i++) {
		fprintf(output, "%s ", nodes[i].nstate);
		if (nodes[i].previous) {
			px = nodes[i].previous;
			fprintf(output, " prev %s\t\tviewmodel %s\n", px->nstate, px->viewmodel);
		}
		else fprintf(output, "\n");
		fprintf(output, "\ttype %s\tretmode %s\t\tinmodel %s\n",
			nodes[i].nstatetype, (nodes[i].nretmodel == 0) ? "void" : nodes[i].nretmodel, 
			(nodes[i].ninmodel == 0) ? "void" : nodes[i].ninmodel);
		for (j = 0; j < nodes[i].inext; j++) {
			px = nodes[i].next[j];
			fprintf(output, "\tnextState %s type %s retmodel %s inmodel %s prev %s\n",
				px->nstate, px->nstatetype, px->nretmodel, (px->ninmodel == 0) ? "void" : px->ninmodel, px->nstate);
		}
	}
}