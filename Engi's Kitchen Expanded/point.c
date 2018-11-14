#include <stdio.h>
#include "boolean.h"
#include "point.h"
#include <math.h>

#define PI 3.14

/* *** Definisi ABSTRACT DATA TYPE POINT *** */
/* typedef struct {
	float X;
	float Y;
} POINT; */

/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk POINT *** */
POINT MakePOINT (float X, float Y)
/* Membentuk sebuah POINT dari komponen-komponennya */
{
	/* KAMUS LOKAL */
	POINT P;
	
	/* ALGORITMA */
	Absis(P) = X;
	Ordinat(P) = Y;
	return P;
}

/* *** KELOMPOK Interaksi dengan I/O device, BACA/TULIS  *** */
void BacaPOINT (POINT *P)
/* Membaca nilai absis dan ordinat dari keyboard dan membentuk POINT P berdasarkan
dari nilai absis dan ordinat tersebut */
/* I.S. Sembarang */
/* F.S. P terdefinisi */
{
	/* KAMUS LOKAL */
	float X;
	float Y;
	
	/* ALGORITMA */
	scanf ("%f %f", &X, &Y);
	Absis(*P) = X;
	Ordinat(*P) = Y;
}
void TulisPOINT (POINT P)
/* Nilai P ditulis ke layar dengan format "(X,Y)" */
/* I.S. P terdefinisi */
/* F.S. P tertulis di layer dengan format "(X,Y)" */
{
	printf ("(%f,%f)", Absis(P), Ordinat(P));
}

/* *** Kelompok operasi relasional terhadap POINT *** */
boolean EQP (POINT P1, POINT P2)
/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
{
	return (Absis(P1) == Absis(P2)) && (Ordinat(P1) == Ordinat(P2));
}
boolean NEQP (POINT P1, POINT P2)
/* Mengirimkan true jika P1 tidak sama dengan P2 */
{
	return (!EQP (P1, P2));
}

/* *** Kelompok menentukan di mana P berada *** */
boolean IsOrigin (POINT P)
/* Menghasilkan true jika P adalah titik origin */
{
	return ((Absis(P) == 0) && (Ordinat(P) == 0));
}
boolean IsOnSbX (POINT P)
/* Menghasilkan true jika P terletak Pada sumbu X */
{
	return (Ordinat(P) == 0);
}
boolean IsOnSbY (POINT P)
/* Menghasilkan true jika P terletak pada sumbu Y */
{
	return (Absis(P) == 0);
}
int Kuadran (POINT P)
/* Menghasilkan kuadran dari P: 1, 2, 3, atau 4 */
/* Prekondisi : P bukan Titik Origin, */
/*              dan P tidak terletak di salah satu sumbu */
{
	if (!IsOrigin(P) && !IsOnSbX(P) && !IsOnSbY(P)) {
		if ((Absis(P) > 0) && (Ordinat(P) > 0))
			return 1;
		else if ((Absis(P) < 0) && (Ordinat(P) > 0))
			return 2;
		else if ((Absis(P) < 0) && (Ordinat(P) < 0))
			return 3;
		else if ((Absis(P) > 0) && (Ordinat(P) < 0))
			return 4;
	}
}

/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */
POINT NextX (POINT P)
/* Mengirim salinan P dengan absis ditambah satu */
{
	Absis(P) = Absis(P) + 1;
	return P;
}
POINT NextY (POINT P)
/* Mengirim salinan P dengan ordinat ditambah satu */
{
	Ordinat(P) = Ordinat(P) + 1;
	return P;
}
POINT PlusDelta (POINT P, float deltaX, float deltaY)
/* Mengirim salinan P yang absisnya adalah Absis(P) + deltaX dan ordinatnya adalah Ordinat(P) + deltaY */
{
	Absis(P) = Absis(P) + deltaX;
	Ordinat(P) = Ordinat(P) + deltaY;
	return P;
}
POINT MirrorOf (POINT P, boolean SbX)
/* Menghasilkan salinan P yang dicerminkan terhadap salah satu sumbu */
/* Jika SbX bernilai true, maka dicerminkan terhadap sumbu X */
/* Jika SbX bernilai false, maka dicerminkan terhadap sumbu Y */
{
	if (SbX)
		Ordinat(P) = -1 * Ordinat(P);
	else /* !SbX */
		Absis(P) = -1 * Absis(P);
	return P;
}
float Jarak0 (POINT P)
/* Menghitung jarak P ke (0,0) */
{
	return (sqrt((Absis(P) * Absis(P)) + (Ordinat(P) * Ordinat(P))));
}
float Panjang (POINT P1, POINT P2)
/* Menghitung panjang garis yang dibentuk P1 dan P2 */
/* Perhatikanlah bahwa di sini spec fungsi kurang baik sebab menyangkut ADT Garis. Tuliskan spec fungsi yang lebih tepat. */
{
	/* KAMUS LOKAL */
	float slshX, slshY;
	
	/* ALGORITMA */
	slshX = Absis(P1) - Absis(P2);
	slshY = Ordinat(P1) - Ordinat(P2);
	return (sqrt((slshX * slshX) + (slshY * slshY)));
}
void Geser (POINT *P, float deltaX, float deltaY)
/* I.S. P terdefinisi */
/* F.S. P digeser, absisnya sebesar deltaX dan ordinatnya sebesar deltaY */
{
	Absis(*P) = Absis(*P) + deltaX;
	Ordinat(*P) = Ordinat(*P) + deltaY;
}
void GeserKeSbX (POINT *P)
/* I.S. P terdefinisi */
/* F.S. P berada pada sumbu X dengan absis sama dengan absis semula. */
/* Proses : P digeser ke sumbu X. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (9,0) */
{
	Ordinat(*P) = 0;
}
void GeserKeSbY (POINT *P)
/* I.S. P terdefinisi*/
/* F.S. P berada pada sumbu Y dengan ordinat yang sama dengan semula. */
/* Proses : P digeser ke sumbu Y. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (0,9) */
{
	Absis(*P) = 0;
}
void Mirror (POINT *P, boolean SbX)
/* I.S. P terdefinisi */
/* F.S. P dicerminkan tergantung nilai SbX atau SbY */
/* Jika SbX true maka dicerminkan terhadap sumbu X */
/* Jika SbX false maka dicerminkan terhadap sumbu Y */
{
	if (SbX)
		Ordinat(*P) = -1 * Ordinat(*P);
	else /* !SbX */
		Absis(*P) = -1 * Absis(*P);
}
void Putar (POINT *P, float Sudut)
/* I.S. P terdefinisi */
/* F.S. P digeser sebesar Sudut derajat dengan sumbu titik (0,0) */
{
	/* Kamus Lokal */
	float R;
	
	/* ALGORITMA */
	R = (Sudut * PI)/180;
	Absis(*P) = (cos(R) * Absis(*P)) - (sin(R) * Ordinat(*P));
	Ordinat(*P) = (sin(R) * Absis(*P)) + (cos(R) * Ordinat(*P));
}

