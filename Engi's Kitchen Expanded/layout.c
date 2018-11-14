#include <stdio.h>
#include <string.h>
#include "queue.h"
#include "matriks.h"
#include "point.h"
#include "stackt.h"
#include "array.h"
#include "jam.h"
#include "simul.h"
#include "mesinkata.h"


MATRIKS Map;
char layoutc;
static FILE *layoutfile;
typedef char string[300];
typedef enum { 
   _player,
   _money,
   _time,
   _food,
   _info
} condition;

simulation Sim;
Queue QMain;
int NBFood;
POINT player;
Queue QLay;
Stack Food;
Stack Hand;
string Info;
TabStr Order;


void CalculateSpace(int len,condition label){ //menambah space di cmd biar bingkainya tetap
   /*kamus lokal*/
   int i;

   /*algoritma*/
   switch(label){
      case _player: 
         for(i=7-len;i>0;i--)
            printf(" ");
         break;
      case _money:
         for(i=9-len;i>0;i--)
            printf(" ");
         break;
      case _time:
         for(i=5-len;i>0;i--)
            printf(" ");
         break;
      case _food:
      	 for(i=12-len;i>0;i--)
      	 	printf(" ");
   		 break;
   	  case _info:
   	  	 for(i=54-len;i>0;i--)
   	  	 	printf(" ");
   }
}

void PrintCust(Queue *Q, int HeadQ, boolean *done){ //print Customer ke layar
	if (!(*done)){
		if( (IsEmptyQ(*Q))){
			printf(" ");
			*done = true;
		}
		else if ((NBElmtQ(*Q)==1) ){
			printf("%d",InfoHead(*Q));
			Head(*Q) = HeadQ;
			*done = true;
		}
		else{ /*NBElmtQ > 1 && !done*/
			printf("%d",InfoHead(*Q));
			Head(*Q) = Head(*Q)%MaxElQ(*Q) + 1;
		}
	}
	else{
		printf(" ");
	}
}

void PrintMap(MATRIKS M,int brs, int kol){ //print Map ke layar
	//kamus lokal
	
	//algoritma
	printf("%c",ElmtM(M,brs,kol));	
}

void PrintStack(Stack *S, int i, boolean *done){ //print Food & Hand ke layar
	if ((Top(*S)!= Nol) && !(*done)) {
			printf("%s",InfoTop(*S));
			CalculateSpace(strlen(InfoTop(*S)),_food);
			Top(*S)--;
	}
	else{
		*done = true;
		Top(*S) = i;
	}

	if(*done){
		printf(" ");
		CalculateSpace(1,_food);
	}

}

void PrintOrder(TabStr T,int *j){ //print Order dan nomor mejanya ke layar
	/* kamus lokal*/
	boolean found;

	/*algoritma*/
	found = false;
	if (strlen(ElmtA(T,*j)) == 0){
		while((*j<=6) && !(found)){
			if(strlen(ElmtA(T,*j))!=0)
				found = true;
			else
				*j = *j + 1;
		}
	}
	if (*j<=6){
		printf("%s,%d",ElmtA(T,*j),*j);
		CalculateSpace(strlen(ElmtA(T,*j))+2,_food);
		*j = *j + 1;
	}
	else 
		CalculateSpace(0,_food);
}

void DrawUntil(){ //baca dan print dari layout_file.txt sampe ketemu CC
   int i;


   EndKata = false;
	while (!EndKata) {
      for (i=1;i<=CKata.Length;i++) {
         printf("%c",CKata.TabKata[i]);
      }

      ADVLAYOUT();

      // printf("\n");
      // printf("Is EndKata1? %d", EndKata);
      // printf("\n");
   }
   ADVLAYOUT();
   // printf("Is EndKata2? %d", EndKata);
   // printf("\n");
}

void CekInfo(string* Info){//mengecek barang di sekitar player untuk info

}

void PrintInfo(string Info){//menampilkan info ke layar
	printf("%s",Info);
}

void DrawLayout() { //menggambar layout dan semua elemennya
   /* kamus lokal*/
   string layoutstr;
   string moneystr;
   string timestr;
   addressS N; 
   boolean doneCust, doneStack;
   int i,j,HeadQ;
   

   /* algoritma */
   STARTKATA("Layout_file.txt");

   //upper border
   printf(" ");
   DrawUntil();

   //PlayerName display
   printf("%s",Sim.name);
   CalculateSpace(strlen(Sim.name),_player);


   //simulation.money display
   DrawUntil();
   sprintf(moneystr,"%d",Sim.money);
   printf("%s",moneystr);
   CalculateSpace(strlen(moneystr),_money);

   //life display
   DrawUntil();
   printf("%d",Sim.life);

   //simulation.time display
   DrawUntil();
   printf("%d",Sim.time);
   sprintf(timestr,"%d",Sim.time);
   CalculateSpace(strlen(timestr),_time);
   
   //Customer, Map, Tray(Food Stack)
   N = Top(Food);
   HeadQ = Head(QLay);
   doneCust = false;
   doneStack = false;
   for(i=1;i<=8;i++){
   	DrawUntil();
      PrintCust(&QLay,HeadQ,&doneCust);

      DrawUntil();

      if(i<9){
      	for(j=1;j<=7;j++){
      		PrintMap(Map,i,j);
      		DrawUntil();
      	}
      	PrintMap(Map,i,8);
      }
      
      DrawUntil();

      PrintStack(&Food,N,&doneStack);
   }

   //Order, Hand 
   doneStack = false;
   N = Top(Hand);
   j=1;
   for(i=1;i<=6;i++){
   		DrawUntil();
   		PrintOrder(Order,&j);
	   	DrawUntil();
	   	PrintStack(&Hand,N,&doneStack);
	   }

   	//Info
   	DrawUntil();
   	CekInfo(&Info);
   	PrintInfo(Info);
   	CalculateSpace(strlen(Info),_info);
   	DrawUntil();
}


int main(){
	int i;
	strcpy(Sim.name, "Eginata");
	Sim.time = 12;
	Sim.money = 500;
	Sim.life = 3;

	CreateEmptyQ(&QLay,8);
	CreateEmptyS(&Food);
	MakeMATRIKS(8,8,&Map);
	
	CreateEmptyS(&Hand);
	player = MakePOINT(2,2);

	Add(&QLay, 2);
	Add(&QLay, 4);
	Add(&QLay, 1);
	Add(&QLay, 1);
	Add(&QLay, 2);
	Add(&QLay, 1);
	Add(&QLay, 4);
	
	Push(&Food, "Burger");
	Push(&Food, "Burger");
	Push(&Food, "Sup");
	Push(&Food, "Sosis");
	Push(&Food, "Sosis");
	Push(&Food, "Sosis");
	Push(&Food, "Sosis");
	Push(&Food, "Sosis");
	Push(&Hand, "Kepala Vivi");
	Push(&Hand, "Kerbau");

	strcpy(ElmtA(Order,1), "Burger");
	strcpy(ElmtA(Order,4),"Sosis");
	
	strcpy(Info,"Hello there");
	ElmtM(Map,player.X,player.Y) = 'P';
	
	DrawLayout();
}
