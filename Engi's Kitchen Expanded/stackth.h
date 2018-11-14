#ifndef stackth_H
#define stackth_H

#include <string.h>
#include "boolean.h"
#include "stackt.h"
//#include "bintree.h"

void CT(Stack *S);
/* Menmbuang makanan yang ada di tray */
/* I.S Tray mungkin kosong */
/* F.S Tray menjadi kosong,akan dibuat Stack tray yang baru */
void CH(Stack*S);
/* Menmbuang makanan yang ada di tangan */
/* I.S Tangan mungkin kosong */
/* F.S Tangan menjadi kosong,akan dibuat Stack tangan yang baru */
/*void dispayhand(Stack S);*/
 void ReverseS(Stack*S,Stack*S1);
 /* Mengreverse stack */
 /*I.S Stack tidak kosong*/
 /*F.S Stack keluar akan direverse,Stack sebelumnya menjadi kosong*/
void PrintH(Stack *SH);
/* Mengeprint data yang ada dalam stack tangan*/

/*void putTray(Stack*S);/* adt tree */
/* Membentuk makanan yang dipesan */
/* I.S Stack tangan mungkin kosong */
/* F.S Dibentuk stack makanan orderan customer. Makanan yang terbentuk akan sesuai dari tree resep*/

void takeIng(Stack*SH,Stack *S1,infotypeS *x);
/*Menyimpan bahan dari array ke dalam stack tangan */
/*I.S Array bahan tidak kosong*/
/* Akan terbentuk stack bahan di tangan dengan jumlah elemen maksimal 10 */
boolean keluar();

#endif