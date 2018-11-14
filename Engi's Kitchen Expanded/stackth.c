#include <stdio.h>
#include "stackth.h"
#include "boolean.h"
#include "simul.h"

void CT(Stack *S)
/* Menmbuang makanan yang ada di tray */
/* I.S Tray mungkin kosong */
/* F.S Tray menjadi kosong,akan dibuat Stack tray yang baru */
{
	if (IsEmptyS(*S)) {
		printf("There's nothing in the tray\n");
	}
	else {
		CreateEmptyS(S);
		printf("\n");
	}
}
void CH(Stack *S)
/* Menmbuang makanan yang ada di tangan */
/* I.S Tangan mungkin kosong */
/* F.S Tangan menjadi kosong,akan dibuat Stack tangan yang baru */
{
	if (IsEmptyS(*S)) {
		printf("There's nothing in your hand !\n");
	}
	else {
		CreateEmptyS(S);
		printf("\n");
	}
}
boolean keluar()
{
	return  false;
}
void ReverseS(Stack*S,Stack*S1)
{
	infotypeS x;
	while(!IsEmptyS(*S)) 
	{
		Pop(S,&x);
		Push(S1,x);
	}
		
}
void PrintH(Stack *SH)
{
	addressS i = Top(*SH);
	while ( Top(*SH)!= 0) {
			printf("%s\n",InfoTop(*SH));
			Top(*SH)--;
			}
	Top(*SH) = i;
}
/*void putTray(Stack*SH,)
/* Membentuk makanan yang dipesan */
/* I.S Stack tangan mungkin kosong */
/* F.S Dibentuk stack makanan orderan customer. Makanan yang terbentuk akan sesuai dari tree resep*/

	
	
	
void takeIng(Stack *S1,Stack *SH,infotypeS *x)
/*Menyimpan bahan dari array ke dalam stack tangan */
/*I.S Array bahan tidak kosong*/
/* Akan terbentuk stack bahan di tangan dengan jumlah elemen maksimal 10 */
{
	if (IsFullS(*S1)) {
			printf("Your hand is full already\n");
	}
	else {	
			printf ("Hand\n");
			Push(S1,*x);
			ReverseS(S1,SH);
			PrintH(SH);
			ReverseS(SH,S1);
			
	}			
}


	
