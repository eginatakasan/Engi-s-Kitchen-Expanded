#include <stdio.h>
#include "boolean.h"

/* *** Definisi TYPE JAM <HH:MM:SS> *** */
typedef struct {
	int HH; /* integer [0..23] */
	int MM; /* integer [0..59] */
	int SS; /* integer [0..59] */
} JAM;

/* ***************************************************************** */
/* DEFINISI PRIMITIF 												 */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE 									 */
/* ***************************************************************** */
boolean IsJAMValid (int H, int M, int S)
/* Mengirim true  jika H,M,S dapat membentuk J yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah Jam */
{
	return ((H >= 0) && (H <= 23) && (M >= 0) && (M <= 59) && (S >= 0) && (S <= 59));
}

/* *** Konstruktor: Membentuk sebuah JAM dari komponen-komponennya *** */
JAM MakeJAM (int HH, int MM, int SS)
/* Membentuk sebuah JAM dari komponen-komponennya yang valid */
/* Prekondisi : HH, MM, SS valid untuk membentuk JAM */
{
	/* KAMUS LOKAL */
	JAM J;
	
	/* ALGORITMA */
	J.HH = HH;
	J.MM = MM;
	J.SS = SS;
	return J;
}

/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */
void BacaJAM (JAM *J)
/* I.S. : J tidak terdefinisi */
/* F.S. : J terdefinisi dan merupakan jam yang valid */
/* Proses : mengulangi membaca komponen H,M,S sehingga membentuk J */
/* 		  yang valid. Tidak mungkin menghasilkan J yang tidak valid. */
{
	/* KAMUS LOKAL */
	int H;
	int M;
	int S;
	
	/* ALGORITMA */
	scanf ("%d %d %d", &H, &M, &S);
	while (!IsJAMValid(H, M, S)) {
		printf ("Salah, masukkan ulang\n");
		scanf ("%d %d %d", &H, &M, &S);
	}
	/* IsJAMValid(H, M, S) */
	(*J).HH = H;
	(*J).MM = M;
	(*J).SS = S;
}
void TulisJAM (JAM J)
/* I.S. : J sembarang */
/* F.S.: Nilai J ditulis dg format HH:MM:SS */
/* Proses : menulis nilai setiap komponen J ke layar */
{
	printf ("%02d:%02d:%02d", J.HH, J.MM, J.SS);
}

/* ***************************************************************** */
/* KELOMPOK KONVERSI TERHADAP TYPE 									 */
/* ***************************************************************** */
int JAMToDetik (JAM J) 
/* Diberikan sebuah JAM, mengkonversi menjadi jumlah Detik dari pukul 0:0:0 */
/* Rumus: detik = 3600 * HH + 60 * MM + SS */
/* nilai maksimum = 3600 * 23 + 59 * 60+ 59 */
/* Hati-hati dengan representasi integer pada bahasa implementasi */ 
/* kebanyakan sistem mengimplementasi integer, */
/* bernilai maksimum kurang dari nilai maksimum hasil konversi */
{
	return ((3600 * J.HH) + (60 * J.MM) + J.SS);
}

JAM DetikToJAM (int N)
/* Mengirim konversi detik ke JAM */
/* Pada beberapa bahasa, representasi integer tidak cukup untuk */
/* menampung N */
/* Catatan: Jika N ≥ 86400, maka harus dikonversi dulu menjadi jumlah detik yang 
  mewakili jumlah detik yang mungkin dalam 1 hari, yaitu dengan rumus: N1 = N mod
  86400, baru N1 dikonversi menjadi JAM */
{
	/* KAMUS LOKAL */
	JAM J;
	
	/* ALGORITMA */
	if (N < 0)
		N = 86400 + N;
	else
		N = N % 86400;
	J.HH = N / 3600;
	J.MM = (N % 3600) / 60;
	J.SS = (N % 60);
	return J;
}
  
/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */
/* *** Kelompok Operator Relational *** */
boolean JEQ (JAM J1, JAM J2)
/* Mengirimkan true jika J1=J2, false jika tidak */
{
	return ((J1.HH == J2.HH) && (J1.MM == J2.MM) && (J1.SS == J2.SS));
}
boolean JNEQ (JAM J1, JAM J2)
/* Mengirimkan true jika J1 tidak sama dengan J2 */
{
	return ((J1.HH != J2.HH) && (J1.MM != J2.MM) && (J1.SS != J2.SS));
}
boolean JLT (JAM J1, JAM J2)
/* Mengirimkan true jika J1<J2 , false jika tidak */
{
	if (J1.HH < J2.HH)
		return (J1.HH < J2.HH);
	else if (J1.HH == J2.HH) {
		if (J1.MM < J2.MM)
			return (J1.MM < J2.MM);
		else if (J1.MM == J2.MM) {
			return (J1.SS < J2.SS);
		}
	}
}
boolean JGT (JAM J1, JAM J2)
/* Mengirimkan true jika J1>J2, false jika tidak */
{
	if (J1.HH > J2.HH)
		return (J1.HH > J2.HH);
	else if (J1.HH == J2.HH) {
		if (J1.MM > J2.MM)
			return (J1.MM > J2.MM);
		else if (J1.MM == J2.MM) {
			return (J1.SS > J2.SS);
		}
	}
}
/* *** Operator aritmatika JAM *** */
JAM NextDetik (JAM J)
/* Mengirim 1 detik setelah J dalam bentuk JAM */
{
	if (J.SS == 59) {
		J.SS = 0;
		J.HH += 1;
	}
	else /* J.SS != 59 */
		J.SS += 1;
	return J;
}
JAM NextNDetik (JAM J, int N)
/* Mengirim N detik setelah J dalam bentuk JAM */
{
	J.SS += N;
	if (J.SS > 60) {
		J.SS = 60 - J.SS;
		J.HH += 1;
	}
	return J;
}
JAM PrevDetik (JAM J)
/* Mengirim 1 detik sebelum J dalam bentuk JAM */
{
	if (J.SS == 0) {
		J.SS = 59;
		J.HH -= 1;
	}
	else /* J.SS != 0 */
		J.SS -= 1;
	return J;
}
JAM PrevNDetik (JAM J, int N)
/* Mengirim N detik sebelum J dalam bentuk JAM */
{
	if (J.SS < N) {
		J.SS = 60 - N + J.SS;
		J.HH -= 1;
	}
	else /* J.SS >= N */
		J.SS -= N;
	return (J);
}
/* *** Kelompok Operator Aritmetika *** */
int Durasi (JAM Jaw, JAM Jakh) 
/* Mengirim JAkh-JAw dlm Detik, dengan kalkulasi */
/* Jika JAw > JAkhir, maka JAkhir adalah 1 hari setelah JAw */
{
	return (JAMToDetik(Jakh) - JAMToDetik(Jaw));
}
