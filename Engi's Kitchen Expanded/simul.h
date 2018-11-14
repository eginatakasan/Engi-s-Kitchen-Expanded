/* File : simul.h */
/* ADT simulasi Engi's Kitchen Expansion */

#ifndef simul_H
#define simul_H

#include <stdlib.h>
#include <string.h>
#include "boolean.h"
#include "jam.h"
#include "point.h"
#include "array.h"
#include "matriks.h"
// #include "mesinkata.h"
#include "queue.h"
#include "stackt.h"
// #include "listlinier.h"
// #include "bintree.h"




/* Definisi Type Data */
typedef struct {
	char name[7];
	int time;
	long money;
	int life;
} simulation;

typedef struct {
	int n;
	int tick;
	int table;
	char order[20];
} customer;

typedef struct {
	int nBahan;
	TabStr bahan[5];
} resep;
typedef struct {
	char name[20];
	int harga;
	resep rsp;
} food;
typedef char TabOrd[20][12];

#endif
