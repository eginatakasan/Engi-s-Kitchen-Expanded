//13517060
//Vivianni
//23 September 2018
//Mesin Kata

#include "boolean.h"
#include "mesinkar.h"
#include "mesinkata.h"
#include <stdio.h>

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

void STARTKATA(char *file)
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
		SalinLayout();
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

	while (CC!=MARK && CC!=' ' && i<=NMax)
	{
		CKata.TabKata[i]=CC;
		ADV();
		i++;
	}
	CKata.Length=i-1;

	if(i==NMax+1)
	{
		while (CC!=MARK && CC!=' ')
		{
			ADV();
		}
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