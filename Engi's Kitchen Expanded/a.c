#include "mesinkar.h"
#include "mesinkata.h"
#include <stdio.h>

typedef enum {
  _layout
} option;

int main(){
	STARTLAYOUT();
	while(CC != '.'){
		ADV(_layout);
	}
	
}