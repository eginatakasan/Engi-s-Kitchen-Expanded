/* ********** Definisi TYPE MATRIKS dengan indeks integer dan elemen character ********** */

#include <stdio.h>
#include "boolean.h"
#include "matriks.h"
#include <math.h>

/* Ukuran minimum dan maksimum baris dan kolom */
#define BrsMin 1
#define BrsMax 100
#define KolMin 1
#define KolMax 100

/* NBrsEff <= 1 dan NKolEff <= 1 */
/* Indeks matriks yang digunakan: [BrsMin..BrsMax][KolMin..KolMax] */
/* Memori matriks yang dipakai selalu di "ujung kiri atas" */

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */              
/* *** Konstruktor membentuk MATRIKS *** */
void MakeMATRIKS (int NB, int NK, MATRIKS * M)
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */
{
	(*M).NBrsEff = NB;
	(*M).NKolEff = NK;
}

/* *** Selektor "DUNIA MATRIKS" *** */
boolean IsIdxValid (int i, int j)
/* Mengirimkan true jika i, j adalah indeks yang valid untuk matriks apa pun */
{
	return ((i >= BrsMin) && (i <= BrsMax) && (j >= KolMin) && (j <= KolMax));
}

/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
indeks GetFirstIdxBrs (MATRIKS M)
/* Mengirimkan indeks baris terkecil M */
{
	return BrsMin;
}
indeks GetFirstIdxKol (MATRIKS M)
/* Mengirimkan indeks kolom terkecil M */
{
	return KolMin;
}
indeks GetLastIdxBrs (MATRIKS M)
/* Mengirimkan indeks baris terbesar M */
{
	return NBrsEff(M);
}
indeks GetLastIdxKol (MATRIKS M)
/* Mengirimkan indeks kolom terbesar M */
{
	return NKolEff(M);
}
boolean IsIdxEff (MATRIKS M, indeks i, indeks j)
/* Mengirimkan true jika i, j adalah indeks efektif bagi M */
{
	return ((i >= BrsMin) && (i <= NBrsEff(M)) && (j >= KolMin) && (j <= NKolEff(M)));
}
ElTypeM GetElmtDiagonal (MATRIKS M, indeks i)
/* Mengirimkan elemen M(i,i) */
{
	return ElmtM(M,i,i);
}

/* ********** Assignment  MATRIKS ********** */
void CopyMATRIKS (MATRIKS MIn, MATRIKS * MHsl)
/* Melakukan assignment MHsl  MIn */
{
	/* KAMUS LOKAL */
	indeks i, j;
	
	/* ALGORITMA */
	MakeMATRIKS(GetLastIdxBrs(MIn), GetLastIdxKol(MIn), MHsl);
	for (i = BrsMin; i <= GetLastIdxBrs(MIn); i++) {
		for (j = KolMin; j <= GetLastIdxKol(MIn); j++)
			ElmtM(*MHsl,i,j) = ElmtM(MIn,i,j);
	}
}

/* ********** KELOMPOK BACA/TULIS ********** */ 
void BacaMATRIKS (MATRIKS * M, int NB, int NK)
/* I.S. IsIdxValid(NB,NK) */ 
/* F.S. M terdefinisi nilai elemen efektifnya, berukuran NB x NK */
/* Proses: Melakukan MakeMATRIKS(M,NB,NK) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika NB = 3 dan NK = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10 
*/
{
	/* KAMUS LOKAL */
	indeks i, j;
	ElTypeM x;
	
	/* ALGORITMA */
	MakeMATRIKS(NB, NK, M);
	for (i = BrsMin; i <= NB; i++) {
		for (j = KolMin; j <= NK; j++) {
			scanf ("%c",&x);
			ElmtM(*M,i,j) = x;
		}
	}
}
void TulisMATRIKS (MATRIKS M)
/* I.S. M terdefinisi */
/* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/
{
	/* KAMUS LOKAL */
	indeks i, j;
	
	/* ALGORITMA */
	for (i = BrsMin; i <= GetLastIdxBrs(M); i++) {
		for (j = KolMin; j < GetLastIdxKol(M); j++) {
			printf ("%d ",ElmtM(M,i,j));
		}
		if (i == GetLastIdxBrs(M))
			printf ("%d",ElmtM(M,i,GetLastIdxKol(M)));
		else /* i != GetLastIdxBrs(M) */
			printf ("%d\n",ElmtM(M,i,GetLastIdxKol(M)));
	}
}

/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP MATRIKS ********** */
boolean EQM (MATRIKS M1, MATRIKS M2)
/* Mengirimkan true jika M1 = M2, yaitu NBElmtM(M1) = NBElmtM(M2) dan */
/* untuk setiap i,j yang merupakan indeks baris dan kolom M1(i,j) = M2(i,j) */
/* Juga merupakan strong EQP karena GetFirstIdxBrs(M1) = GetFirstIdxBrs(M2) 
   dan GetLastIdxKol(M1) = GetLastIdxKol(M2) */
{
	/* KAMUS LOKAL */
	indeks i, j;
	boolean E;
	
	/* ALGORITMA */
	if ((GetLastIdxBrs(M1) != GetLastIdxBrs(M2)) || (GetLastIdxKol(M1) != GetLastIdxKol(M2)))
		return false;
	else /* (GetLastIdxBrs(M1) == GetLastIdxBrs(M2)) && (GetLastIdxKol(M1) == GetLastIdxKol(M2) */ {
		E = true;
		i = BrsMin;
		j = KolMin;
		while ((i <= GetLastIdxBrs(M1)) && E) {
			if (ElmtM(M1,i,j) != ElmtM(M2,i,j))
				E = false;
			else /* ElmtM(M1,i,j) == ElmtM(M2,i,j) */
				j++;
			if (j > GetLastIdxKol(M1)) {
				i++;
				j = GetFirstIdxBrs(M1);
			}
			i++;
		} /* (j > GetLastIdxBrs(M1)) || !E */
	return E;
	}
}
boolean NEQM (MATRIKS M1, MATRIKS M2)
/* Mengirimkan true jika M1 tidak sama dengan M2 */
{
	return !EQM(M1,M2);
}
boolean EQSize (MATRIKS M1, MATRIKS M2)
/* Mengirimkan true jika ukuran efektif matriks M1 sama dengan ukuran efektif M2 */
/* yaitu GetBrsEff(M1) = GetNBrsEff (M2) dan GetNKolEff (M1) = GetNKolEff (M2) */
{
	return ((GetLastIdxBrs(M1) == GetLastIdxBrs(M2)) && (GetLastIdxKol(M1) == GetLastIdxKol(M2)));
}

/* ********** Operasi lain ********** */
int NBElmtM (MATRIKS M)
/* Mengirimkan banyaknya elemen M */
{
	return (GetLastIdxBrs(M) * GetLastIdxKol(M));
}

/* ********** KELOMPOK TEST TERHADAP MATRIKS ********** */
boolean IsBujurSangkar (MATRIKS M)
/* Mengirimkan true jika M adalah matriks dg ukuran baris dan kolom sama */
{
	return (GetLastIdxBrs(M) == GetLastIdxKol(M));
}
boolean IsSimetri (MATRIKS M)
/* Mengirimkan true jika M adalah matriks simetri : IsBujurSangkar(M) 
   dan untuk setiap elemen M, M(i,j)=M(j,i) */
{
	/* KAMUS LOKAL */
	indeks i, j;
	boolean S;
	
	/* ALGORITMA */
	if (!IsBujurSangkar(M))
		return false;
	else /* IsBujurSangkar(M) */ {
		S = true;
		i = BrsMin;
		while ((i <= GetLastIdxBrs(M)) && S) {
			j = KolMin;
			while ((j <= GetLastIdxKol(M)) && S) {
				if (ElmtM(M,i,j) != ElmtM(M,j,i))
					S = false;
				j++;
			} /* (j > GetLastIdxKol(M1)) || !S */
			i++;
		} /* (j > GetLastIdxBrs(M1)) || !S */
		return S;
	}
}
boolean IsSatuan (MATRIKS M)
/* Mengirimkan true jika M adalah matriks satuan: IsBujurSangkar(M) dan 
   setiap elemen diagonal M bernilai 1 dan elemen yang bukan diagonal bernilai 0 */
{
	/* KAMUS LOKAL */
	indeks i, j;
	boolean Sat;
	
	/* ALGORITMA */
	if (!IsBujurSangkar(M))
		return false;
	else /* IsBujurSangkar(M) */ {
		Sat = true;
		i = BrsMin;
		while ((i <= GetLastIdxBrs(M)) && Sat) {
			j = KolMin;
			while ((j <= GetLastIdxKol(M)) && Sat) {
				if (i == j) {
					if (GetElmtDiagonal(M,i) != 1)
						Sat = false;
				}
				else /* i != j */ {
					if (ElmtM(M,i,j) != 0)
						Sat = false;
				}
				j++;
			} /* (j > GetLastIdxKol(M1)) || !Sat */
			i++;
		} /* (j > GetLastIdxBrs(M1)) || !Sat */
		return Sat;
	}
}
boolean IsSparse (MATRIKS M)
/* Mengirimkan true jika M adalah matriks sparse: mariks “jarang” dengan definisi: 
   hanya maksimal 5% dari memori matriks yang efektif bukan bernilai 0 */
{
	/* KAMUS LOKAL */
	boolean sprs;
	indeks i, j, li, lj;
	int c;
	
	/* ALGORITMA */
	sprs = true;
	i = GetFirstIdxBrs(M);
	li = GetLastIdxBrs(M);
	lj = GetLastIdxKol(M);
	c = 0;
	while ((sprs) && (i <= li)) {
		j = GetFirstIdxKol(M);
		while ((sprs) && (j <= lj)) {
			if (ElmtM(M,i,j) > 0) {
				c++;
			}
			sprs = ((double) c / NBElmtM(M)) <= 0.05;
			j++;
		}
		i++;
	}
	return sprs;
}   

void Transpose (MATRIKS *M)
/* I.S. M terdefinisi dan IsBujursangkar(M) */
/* F.S. M "di-transpose", yaitu setiap elemen M(i,j) ditukar nilainya dengan elemen M(j,i) */
{
	/* KAMUS LOKAL */
	indeks i, j;
	MATRIKS temp;
	
	/* ALGORITMA */
	MakeMATRIKS(GetFirstIdxBrs(*M), GetLastIdxBrs(*M), &temp);
	for (i = BrsMin; i <= GetLastIdxBrs(*M); i++) {
		for (j = KolMin; j <= GetLastIdxKol(*M); j++) {
			ElmtM(temp,i,j) = ElmtM(*M,i,j);
		}
	}
	for (i = BrsMin; i <= GetLastIdxBrs(*M); i++) {
		for (j = KolMin; j <= GetLastIdxKol(*M); j++) {
			ElmtM(*M,i,j) = ElmtM(temp,i,j);
		}
	}
}

