#include "jdict.h"
#include "jotto.h"

static void get_human_guess(char *h_guess)
{
    scanf("%s", h_guess);
    h_guess[5] = '\0';
}

static int get_hits_from_human(int *c_hits)
{
    scanf("%d", c_hits);
}

static void *humans_turn(JottoGuess *hjg, char *c_word, JDict *reference)
{
    char h_guess[7];
    int h_hits = JOTTO_INVALID_HIT_COUNT;
  
    do {
	get_human_guess(h_guess);
	if (jdict_has_word(h_guess, reference)) {
	    h_hits = hit_count(h_guess, c_word); 
	}
	else {
	    printf("No such word; try again: ");
	}
    } while (h_hits == JOTTO_INVALID_HIT_COUNT);
  
    strncpy(hjg->guess, h_guess, 6);
    hjg->hits = h_hits;
}

static void report_outcome(JottoStatus *status, char *c_word)
{
    switch(status->value) {
    case JOTTO_TIE:
	sprintf(status->message, "We tied!\n");
	break;
    case JOTTO_HUMAN_WON:
	sprintf(status->message, "You win!\n");
	break;
    case JOTTO_COMPUTER_WON:
	sprintf(status->message, "I win! My word was %s.\n", c_word);
	break;
    default:
	printf("Shouldn't reach here!\n");
    }
}

static void pretty_print_guess(JottoGuess *info, int offset) {
    char format[30];
    char *cp = format;
    sprintf(cp, "%%%ds: %%d\n", offset); 
    printf(cp, info->guess, info->hits);
}

int hit_count(char *word1, char *word2)
{
    int hits = 0;
    int i;
    for (i = 0; i < JOTTO_WORD_SIZE; i++) {
	word1[i] == word2[i] && hits++;
    }
    return hits;
}

void play_against_human(JDict *reference)
{
    int c_hits;
    JDict *jdict = jdict_initialize(reference->length);
    char *c_word = jdict_random_word(reference);
    JottoStatus *status = malloc(sizeof(JottoStatus));
    JottoGuess *hjg = malloc(sizeof(JottoGuess));
    JottoGuess *cjg = malloc(sizeof(JottoGuess));

    status->value = JOTTO_NO_RESULT;

    while (status->value == JOTTO_NO_RESULT) {
	printf("Your guess: ");
    
	humans_turn(hjg, c_word, reference);
	pretty_print_guess(hjg, JOTTO_HUMAN_OFFSET);

	if (hjg->hits == 5) {
	    printf("I get one more guess.\n");
	    status->value |= JOTTO_HUMAN_WON;
	}

	if (jdict->length == 0) {
	    printf("There are no words left.\n");
	    status->value |= JOTTO_COMPUTER_WON;
	}
	else {
	    strncpy(cjg->guess, jdict_random_word(jdict), 6);
	    printf("My guess: %s ", cjg->guess);
	    get_hits_from_human(&cjg->hits);
	    pretty_print_guess(cjg, JOTTO_COMPUTER_OFFSET);
      
	    if (cjg->hits == 5) {
		status->value |= JOTTO_COMPUTER_WON;
	    }
	    else {
		jdict_winnow(jdict, cjg->guess, cjg->hits);
	    }
	}
    }
    report_outcome(status, c_word);
    printf("%s", status->message);
    free(status);
    free(hjg);
    free(cjg);
    jdict_free(jdict);
}

