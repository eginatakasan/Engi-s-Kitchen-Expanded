//13517060
//Vivianni
//23 September 2018
//Mesin Kata

#include "boolean.h"
#include "mesinkar.h"
#include "mesinkata.h"
#include <stdio.h>
#include <string.h>

boolean EndKata;
Kata CKata;


void BacaInput(Kata *Input)
{
	ADVINPUT();
	int i = 1;
	while (CC!=BLANK && CC!=ENTER && i<=NMax)
	{
		(*Input).TabKata[i]=CC;
		ADVINPUT();
		i++;
	}
	(*Input).Length=i-1;
}



void IgnoreBlank()
{
	while (CC==' ' && CC!=MARK)
	{
		ADV();
	}
}

void STARTKATA(char *file, boolean IsForLayout)
{
	START(file);
	IgnoreBlank();
 	if (CC==MARK)
 	{
  		EndKata = true;
 	}
 	else 
 	{
  		EndKata = false;
  		if(IsForLayout)
   			SalinLayout();
  		else
   			SalinKata();
 	}
}

void ADVKATA()
{
	if (CC==MARK)
	{
		EndKata = true;
	}
	else 
	{
		EndKata = false;
		SalinKata();
		IgnoreBlank();
	}
}

void SalinKata()
{
	int i=1;
	while (CC!=MARK && i<=NMax)
	{
		CKata.TabKata[i]=CC;
		ADV();
		i++;
	}
	CKata.Length=i-1;

	if(i==NMax+1)
	{
		while (CC!=MARK)
		{
			ADV();
		}
	}
}

boolean IsKataSama(Kata Kata1, char *s)
{
	int i;
	char command[20];
	memcpy(command,s,strlen(s));
	if (Kata1.Length !=  strlen(s))
	{
		return false;
	}
	else
	{
		boolean sama = true;
		int i = 1;
		while ((i<=Kata1.Length) && (sama))
		{
			if (Kata1.TabKata[i]!=command[i-1])
			{
				sama = false;
			}
			else
			{
				i++;
			}
		}
		return sama;
	}
}

void ADVLAYOUT()
{
	if (CC==MARK)
	{
		EndKata = true;
		ADVL();
		

	}
	else 
	{
		EndKata = false;
		SalinLayout();
	}
}

void SalinLayout()
{
	int i=1;

	while (CC!=MARK)
	{
		CKata.TabKata[i]=CC;
		ADVL();
		i++;
	}
	CKata.Length=i-1;

}