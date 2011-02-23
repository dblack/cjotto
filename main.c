#include "jdict.h"
#include "jotto.h"

int main()
{
    JDict *reference_dict = jdict_initialize();
    char play = 'y';
  
    while(play == 'y') {
	play_against_human(reference_dict);
	printf("Another game? (y/n) ");
	scanf("%s", &play);
    }
  
    printf("Bye!\n");   
    jdict_free(reference_dict);
}


