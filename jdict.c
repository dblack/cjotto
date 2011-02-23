#include "jdict.h"
#include "jotto.h"

static int get_word_count()
{
    struct stat filestat;
    stat(JOTTO_FILENAME, &filestat);
    int fsize = (int)filestat.st_size;
    return  (fsize + 1) / 6;
}

static int load_words_from_file(char *filename, JDict *jdict)
{
    char buffer[7];
    int i = 0;
    FILE *fp = fopen(filename, "r");
    while ((fgets(buffer, 7, fp) != NULL)) {
	buffer[5] = '\0';
	strncpy(jdict->jwords[i++], buffer, 6);
    }  
    fclose(fp);
}

static int hits_match_between_words(char *word1, char *word2, int hits)
{
    return hit_count(word1, word2) == hits;
}

JDict *jdict_initialize()
{
    int word_count = get_word_count();
    JDict *jdict = malloc(sizeof(JDict));
    jdict->jwords = malloc(word_count * sizeof(jword));
    load_words_from_file(JOTTO_FILENAME, jdict);
    jdict->length = word_count;

    return jdict;
}

void jdict_free(JDict *jdict)
{
    free(jdict->jwords);
    free(jdict);
}

void jdict_winnow(JDict *jdict, char *guess, int hits)
{
    int i, j = 0;
    char *word;
    int word_count = jdict->length;
    jword *tmp_jwords = malloc(word_count * sizeof(jword));

    for (i = 0; i < word_count; i++) {
	word = jdict->jwords[i];
	if (hits_match_between_words(word, guess, hits)) {
	    strncpy(tmp_jwords[j++], word, 6);
	}
    }
  
    jdict->jwords = realloc(tmp_jwords, j * sizeof(jword));
    jdict->length = j;
}

char *jdict_random_word(JDict *jdict)
{
    time_t *tp = malloc(sizeof(time_t));
    time(tp);
    srandom((long)*tp);
    free(tp);

    return jdict->jwords[random() % jdict->length];
}

int jdict_has_word(char *word, JDict *jdict)
{
    int i;
    for (i = 0; i < jdict->length; i++) {
	if (!strcmp(jdict->jwords[i], word)) {
	    return 1;
	}
    }
    return 0;
}

