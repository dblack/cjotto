#include <time.h>
#define JOTTO_FILENAME "fives"
#define JOTTO_WORD_SIZE  5

typedef char jword[6];

typedef struct {
  int length;
  jword *jwords;
} JDict;

char *jdict_random_word(JDict *);
void jdict_winnow(JDict *, char *, int);
JDict *jdict_initialize();
void jdict_free(JDict *);
