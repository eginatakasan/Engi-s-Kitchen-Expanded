/* MODUL TABEL STRING */
/* Berisi definisi dan semua primitif pemrosesan tabel string */
/* Penempatan elemen selalu rapat kiri */
/* Versi I : dengan banyaknya elemen didefinisikan secara eksplisit, 
   memori tabel statik */

#include "array.h"
#include "boolean.h"
#include <stdio.h>
#include <string.h>

void MakeEmpty (TabStr * T)
/* I.S. T sembarang */
/* F.S. Terbentuk tabel T kosong dengan kapasitas IdxMax-IdxMin+1 */
{
	(*T).Neff = 0;
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int NbElmtA (TabStr T)
/* Mengirimkan banyaknya elemen efektif tabel */
/* Mengirimkan nol jika tabel kosong */
{
	return T.Neff;
}
/* *** Daya tampung container *** */
int MaxNbEl (TabStr T)
/* Mengirimkan maksimum elemen yang dapat ditampung oleh tabel */
{
	return (IdxMax - IdxMin + 1);
}
/* *** Selektor INDEKS *** */
IdxType GetFirstIdxA (TabStr T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */
{
	return IdxMin;
}
IdxType GetLastIdxA (TabStr T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */
{
	return (T.Neff + IdxMin - 1);
}

/* ********** Test Indeks yang valid ********** */
boolean IsIdxValidA (TabStr T, IdxType i)
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara indeks yang terdefinisi utk container*/
{
	return ((i >= IdxMin) && (i <= IdxMax));
}
boolean IsIdxEffA (TabStr T, IdxType i)
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara FirstIdx(T)..LastIdx(T) */
{
	return ((i >= GetFirstIdxA(T)) && (i <= GetLastIdxA(T)));
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean IsEmptyA (TabStr T)
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */
{
	return (T.Neff == 0);
}
/* *** Test tabel penuh *** */
boolean IsFullA (TabStr T)
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */
{
	return (T.Neff == MaxNbEl(T));
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi tabel dari pembacaan *** */
void BacaIsi (TabStr * T)
/* I.S. T sembarang */
/* F.S. Tabel T terdefinisi */
/* Proses : membaca banyaknya elemen T dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
/*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= MaxNbEl(T) */
/*    Jika N tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < N <= MaxNbEl(T); Lakukan N kali: Baca elemen mulai dari indeks 
      IdxMin satu per satu diakhiri enter */
/*    Jika N = 0; hanya terbentuk T kosong */
{
	int N,i;
	scanf("%d",&N);
	while (N<0 || N>MaxNbEl(*T)){
		scanf("%d",&N);
	}
	printf("%d\n", N);
	if (N==0){
		MakeEmpty(&(*T));
	} 
	else{
		for (i=IdxMin;i<=N;i++){
			scanf("%s", &ElmtA(*T,i));
		}
		Neff(*T)=N;
	}
}

void TulisIsi (TabStr T)
/* Proses : Menuliskan isi tabel dengan traversal */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong : indeks dan elemen tabel ditulis berderet ke bawah */
/*      Jika T kosong : Hanya menulis "Tabel kosong" */
/* Contoh: Jika isi Tabel: [1, 20, 30, 50]
   Maka tercetak di layar:
   [1]1
   [2]20
   [3]30
   [4]50
*/
{
	/* KAMUS LOKAL */
	IdxType i;
	
	/* ALGORITMA */
	if (IsEmptyA(T))
		printf ("Tabel kosong\n");
	else /* !IsEmptyA(T) */ {
		for (i = IdxMin; i <= GetLastIdxA(T); i++)
			printf ("[%d]%s\n",i,ElmtA(T,i));
	}
}
void TulisIsiTab (TabStr T)
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku; 
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika tabel kosong : menulis [] */
{
	/* KAMUS LOKAL */
	IdxType i;
	
	/* ALGORITMA */
	if (IsEmptyA(T))
		printf ("[]");
	else /* !IsEmptyA(T) */ {
		printf ("[");
		for (i = IdxMin; i <= (GetLastIdxA(T) - 1); i++) {
			printf ("%s,",ElmtA(T,i));
		}
		printf ("%s]",ElmtA(T,i));
	}
}

/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan tabel : < =, > *** */
boolean IsEQ (TabStr T1, TabStr T2)
/* Mengirimkan true jika T1 sama dengan T2 yaitu jika ukuran T1 = T2 dan semua elemennya sama */
{
	/* KAMUS LOKAL */
	IdxType i;
	boolean EQ;
	
	/* ALGORITMA */
	EQ = false;
	if (GetLastIdxA(T1) != GetLastIdxA(T2))
		EQ = false;
	else if (IsEmptyA(T1) && IsEmptyA(T2))
		EQ = true;
	else if (GetLastIdxA(T1) == GetLastIdxA(T2)) {
		i = IdxMin;
		EQ = true;
		while ((i <= GetLastIdxA(T1)) && EQ) {
			if (ElmtA(T1,i) != ElmtA(T2,i))
				EQ = false;
			else /* ElmtA(T1,i) == ElmtA(T2,i) */
				i++;
		} /* (i > GetLastIdxA(T1)) || !EQ */
	}
	return EQ;
}


/* ********** SEARCHING ********** */
/* ***  Perhatian : Tabel boleh kosong!! *** */
IdxType Search1 (TabStr T, ElTypeA X)
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = X */
/* Jika tidak ada, mengirimkan IdxUndef */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel T kosong */
/* Memakai skema search TANPA boolean */
{
	/* KAMUS LOKAL */
	IdxType i;
	
	/* ALGORITMA */
	if (IsEmptyA(T))
		return IdxUndef;
	else /* GetLastIdxA(T) != 0 */ {
		i = IdxMin;
		while ((i <= GetLastIdxA(T)) && (ElmtA(T,i) != X))
			i++;
		/* (i > GetLastIdxA(T)) && (ElmtA(T,i) == X) */
		if (i > GetLastIdxA(T))
			return IdxUndef;
		else /* i <= GetLastIdxA(T) */
			return i;
	}
}
IdxType Search2 (TabStr T, ElTypeA X)
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = X */
/* Jika tidak ada, mengirimkan IdxUndef */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel T kosong */
/* Memakai skema search DENGAN boolean Found */
{
	/* KAMUS LOKAL */
	boolean Found;
	IdxType i;
	
	/* ALGORITMA */
	if (IsEmptyA(T))
		return IdxUndef;
	else /* !IsEmptyA(T) */ {
		Found = false;
		i = IdxMin;
		while ((i <= GetLastIdxA(T)) && !Found) {
			if (ElmtA(T,i) == X)
				Found = true;
			else /* ElmtA(T,i) != X */
				i++;
		} /* (i > GetLastIdxA(T)) || Found */
		if (Found)
			return i;
		else /* !Found */
			return IdxUndef;
	}
}
boolean SearchB (TabStr T, ElTypeA X)
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
/* Memakai Skema search DENGAN boolean */
{
	/* KAMUS LOKAL */
	boolean Found;
	IdxType i;
	
	/* ALGORITMA */
	if (GetLastIdxA(T) == 0)
		return false;
	else /* GetLastIdxA(T) != 0 */ {
		Found = false;
		i = IdxMin;
		while ((i <= GetLastIdxA(T)) && !Found) {
			if (ElmtA(T,i) == X)
				Found = true;
			else /* ElmtA(T,i) != X */
				i++;
		} /* (i > GetLastIdxA(T) || Found */
		return Found;
	}
}
boolean SearchSentinel (TabStr T, ElTypeA X)
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
/* dengan metoda sequential search dengan sentinel */
/* Untuk sentinel, manfaatkan indeks ke-0 dalam definisi array dalam Bahasa C 
   yang tidak dipakai dalam definisi tabel */
{
	/* KAMUS LOKAL */
	IdxType i;
	
	/* ALGORITMA */
	if (IsEmptyA(T))
		return false;
	else /* !IsEmptyA(T) */ {
		strcpy(ElmtA(T,0), X);
		i = GetLastIdxA(T);
		while ((i >= IdxMin) && (ElmtA(T,i) != X)) {
			i--;
		} /* (i < IdxMin) || (ElmtA(T,i) == X) */
		if (i != 0)
			return true;
		else /* i == 0 */
			return false;
	}
}

/* ********** OPERASI LAIN ********** */
void CopyTab (TabStr Tin, TabStr * Tout)
/* I.S. Tin terdefinisi, Tout sembarang */
/* F.S. Tout berisi salinan dari Tin (elemen dan ukuran identik) */
/* Proses : Menyalin isi Tin ke Tout */
{
	/* KAMUS LOKAL */
	IdxType i;
	
	/* ALGORITMA */
	if (IsEmptyA(Tin))
		MakeEmpty(Tout);
	else /* !IsEmptyA(Tin) */ {
		for (i = IdxMin; i <= GetLastIdxA(Tin); i++)
			strcpy(ElmtA(*Tout,i), ElmtA(Tin,i));
	}
	(*Tout).Neff = Tin.Neff;
}


/* ********** MENAMBAH ELEMEN ********** */
/* *** Menambahkan elemen terakhir *** */
void AddAsLastEl (TabStr * T, ElTypeA X)
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */
{
	if (IsEmptyA(*T))
		strcpy(ElmtA(*T,IdxMin), X);
	else /* !IsEmptyA(T) */
		strcpy(ElmtA(*T,(*T).Neff + 1), X);
	(*T).Neff++;
}
void AddEli (TabStr * T, ElTypeA X, IdxType i)
/* Menambahkan X sebagai elemen ke-i tabel tanpa mengganggu kontiguitas 
   terhadap elemen yang sudah ada */
/* I.S. Tabel tidak kosong dan tidak penuh */
/*      i adalah indeks yang valid. */
/* F.S. X adalah elemen ke-i T yang baru */
/* Proses : Geser elemen ke-i+1 s.d. terakhir */
/*          Isi elemen ke-i dengan X */
{
	/* KAMUS LOKAL */
	IdxType j;
	
	/* ALGORITMA */
	if (i == GetLastIdxA(*T)) {
		AddAsLastEl(T,X);
	}
	else /* i != GetLastIdxA(*T) */ {
		for (j = GetLastIdxA(*T); j >= i; j--) 
			strcpy(ElmtA(*T,j + 1), ElmtA(*T,j));
		strcpy(ElmtA(*T,i), X);
	}
	(*T).Neff++;
}

/* ********** MENGHAPUS ELEMEN ********** */
void DelLastEl (TabStr * T, ElTypeA * X)
/* Proses : Menghapus elemen terakhir tabel */
/* I.S. Tabel tidak kosong */
/* F.S. X adalah nilai elemen terakhir T sebelum penghapusan, */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */
{
	strcpy(*X, ElmtA(*T,GetLastIdxA(*T)));
	(*T).Neff--;
}
void DelEli (TabStr * T, IdxType i, ElTypeA * X)
/* Menghapus elemen ke-i tabel tanpa mengganggu kontiguitas */
/* I.S. Tabel tidak kosong, i adalah indeks efektif yang valid */
/* F.S. X adalah nilai elemen ke-i T sebelum penghapusan */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */
/* Proses : Geser elemen ke-i+1 s.d. elemen terakhir */
/*          Kurangi elemen efektif tabel */
{
	/* KAMUS LOKAL */
	IdxType j;
	
	/* ALGORITMA */
	strcpy(*X, ElmtA(*T,i));
	if (i != GetLastIdxA(*T))	
	for (j = i; j <= GetLastIdxA(*T); j++)
		strcpy(ElmtA(*T,j), ElmtA(*T,j + 1));
	(*T).Neff--;
}

/* ********** TABEL DGN ELEMEN UNIK (SETIAP ELEMEN HANYA MUNCUL 1 KALI) ********** */
void AddElUnik (TabStr * T, ElTypeA X)
/* Menambahkan X sebagai elemen terakhir tabel, pada tabel dengan elemen unik */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/*      dan semua elemennya bernilai unik, tidak terurut */
/* F.S. Jika tabel belum penuh, menambahkan X sbg elemen terakhir T, 
        jika belum ada elemen yang bernilai X. 
		Jika sudah ada elemen tabel yang bernilai X maka I.S. = F.S. 
		dan dituliskan pesan "nilai sudah ada" */
/* Proses : Cek keunikan dengan sequential search dengan sentinel */
/*          Kemudian tambahkan elemen jika belum ada */
{
	if (IsEmptyA(*T)) {
		strcpy(ElmtA(*T,IdxMin), X);
		(*T).Neff++;
	}
	else /* !IsEmptyA(*T) */ {
		if (!SearchSentinel(*T,X)) {
			strcpy(ElmtA(*T,GetLastIdxA(*T) + 1), X);
			(*T).Neff++;
		}
		else /* SearchSentinel(*T,X) */ {
			printf("nilai sudah ada\n");
		}
	}
}

/* ********** TABEL DGN ELEMEN TERURUT MEMBESAR ********** */
IdxType SearchUrut (TabStr T, ElTypeA X)
/* Prekondisi: Tabel T boleh kosong. Jika tidak kosong, elemen terurut membesar. */
/* Mengirimkan indeks di mana harga X dengan indeks terkecil diketemukan */
/* Mengirimkan IdxUndef jika tidak ada elemen tabel bernilai X */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel kosong */
{
	return Search2(T,X);
}
void Del1Urut (TabStr * T, ElTypeA X)
/* Menghapus X yang pertama kali (pada indeks terkecil) yang ditemukan */
/* I.S. Tabel tidak kosong */
/* F.S. Jika ada elemen tabel bernilai X , */
/*      maka banyaknya elemen tabel berkurang satu. */
/*      Jika tidak ada yang bernilai X, tabel tetap. */
/*      Setelah penghapusan, elemen tabel tetap kontigu! */
/* Proses : Search indeks ke-i dengan elemen ke-i = X. */
/*          Delete jika ada. */
{
	/* KAMUS LOKAL */
	ElTypeA j;
	
	/* ALGORITMA */
	if (SearchB(*T,X))
		DelEli(T,Search1(*T,X),&j);
}





