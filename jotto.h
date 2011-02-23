#define JOTTO_NO_RESULT 0
#define JOTTO_HUMAN_WON 1
#define JOTTO_COMPUTER_WON 2
#define JOTTO_TIE (JOTTO_HUMAN_WON | JOTTO_COMPUTER_WON)
#define JOTTO_INVALID_HIT_COUNT -1
#define JOTTO_HUMAN_OFFSET 25
#define JOTTO_COMPUTER_OFFSET 35
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

typedef struct {
  unsigned short value;
  char message[30];
} JottoStatus;

typedef struct {
  char guess[6];
  int hits;
} JottoGuess;


void play_against_human(JDict *);
int hit_count(char *, char *);
