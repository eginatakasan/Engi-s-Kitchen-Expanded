/* File : queue.c */
/* Definisi ADT Queue dengan representasi array secara eksplisit dan alokasi dinamik */
/* Model Implementasi Versi III dengan circular buffer */

#include "boolean.h"
#include "queue.h"
#include <stdlib.h>

#define Nol 0
/* Konstanta untuk mendefinisikan address tak terdefinisi */

/* Definisi Queue kosong: HEAD=Nol; TAIL=Nol. */
/* Catatan implementasi: T[0] tidak pernah dipakai */

/* ********* AKSES (Selektor) ********* */
/* Jika Q adalah Queue, maka akses elemen : */
#define Head(Q) (Q).HEAD
#define Tail(Q) (Q).TAIL
#define InfoHead(Q) (Q).T[(Q).HEAD]
#define InfoTail(Q) (Q).T[(Q).TAIL]
#define MaxElQ(Q) (Q).MaxElQ

/* ********* Prototype ********* */
boolean IsEmptyQ (Queue Q)
/* Mengirim true jika Q kosong: lihat definisi di atas */
{
	return ((Head(Q) == Nol) && (Tail(Q) == Nol));
}
boolean IsFullQ (Queue Q)
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxElQ */
{
	return (Tail(Q)%MaxElQ(Q)+1 == Head(Q));
}
int NBElmtQ (Queue Q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
{
	if (IsEmptyQ(Q))
		return 0;
	else if (Tail(Q) >= Head(Q))
		return (Tail(Q) - Head(Q) + 1); 
	else /* !IsEmptyQ(Q) && (Tail(Q) < Head(Q)) */
		return (MaxElQ(Q) + Tail(Q) - Head(Q) + 1);
}

/* *** Kreator *** */
void CreateEmptyQ (Queue * Q, int Max)
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxElQ=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */
{
	(*Q).T = (infotypeQ *) malloc ((Max + 1) * sizeof(infotypeQ));
	if ((*Q).T != NULL) {
		MaxElQ(*Q) = Max;
		Head(*Q) = Nol;
		Tail(*Q) = Nol;
	}
	else /* (*Q).T == NULL */
        MaxElQ(*Q) = 0;
}

/* *** Destruktor *** */
void DeAlokasiQ (Queue * Q)
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxElQ(Q) diset 0 */
{
	free ((*Q).T);
	MaxElQ(*Q) = 0;
}

/* *** Primitif Add/Delete *** */
void Add (Queue * Q, infotypeQ X)
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */
{
	if (IsEmptyQ(*Q)) {
		Head(*Q) = 1;
		Tail(*Q) = 1;
		InfoTail(*Q) = X;
	}
	else{
		Tail(*Q) = Tail(*Q)%MaxElQ(*Q) + 1;
		InfoTail(*Q) = X;
	}
}
void Del (Queue * Q, infotypeQ * X)
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = Nolai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */
{
	*X = InfoHead(*Q);
	if (NBElmtQ(*Q) == 1) {
		Head(*Q) = Nol;
		Tail(*Q) = Nol;
	}
	else /* NBElmtQ(*Q) == 1 */
		Head(*Q) = Head(*Q)%MaxElQ(*Q) + 1;
}




