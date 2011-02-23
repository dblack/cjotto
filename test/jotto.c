#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/CUError.h>
#include "../jdict.h"
#include "../jotto.h"
static int my_suite_init(void) { return 0; }
static int my_suite_clean(void) { return 0; }
  
void test_5_hits() {
    int hits = hit_count("house", "house");
    CU_ASSERT(hits == 5);
}

void test_no_hits() {
    int hits = hit_count("house", "trick");
    CU_ASSERT(hits == 0);
}

void test_1_hits() {
    int hits = hit_count("house", "hello");
    CU_ASSERT(hits == 1);
}

void test_hits_out_of_order_do_not_count() {
    int hits = hit_count("house", "eusoh");
    CU_ASSERT(hits == 0);
}

static void add_words_to_jdict(char *words[], JDict *jdict, int count) {
    int i;
    jdict->length = count;
    for (i = 0; i < count; i++) {
	strcpy(jdict->jwords[i], words[i]);
    }
}

void test_check_for_word_in_jdict() {
    JDict * jdict = malloc(sizeof(JDict));
    jdict->jwords = malloc(2 * sizeof(jword));
    char *words[] = { "house", "mouse" };
    add_words_to_jdict(words, jdict, 2);
    CU_ASSERT(jdict_has_word("house", jdict));
    CU_ASSERT(!jdict_has_word("hello", jdict));
    free(jdict->jwords);
}

void test_winnowing_jdict() {
    JDict *jdict = malloc(sizeof(JDict));
    jdict->length = 6;
    char *words[] = { "house", "mouse", "treat", "noble", "blast", "chomp" }; 
    jdict->jwords = malloc(6 * sizeof(jword));
    add_words_to_jdict(words, jdict, 6);
    jdict_winnow(jdict, "class", 1);

    CU_ASSERT(jdict->length == 3);
    CU_ASSERT(!strcmp(jdict->jwords[0], "house"));
    CU_ASSERT(!strcmp(jdict->jwords[1], "mouse"));
    CU_ASSERT(!strcmp(jdict->jwords[2], "chomp"));
    free(jdict->jwords);
}

/* In these tests, avoid pointers to string literals because
   those literals are read-only and cannot be chomp'ed. Array
   notation causes a copy to be made. 
*/

int main() {
    CU_BasicRunMode mode = CU_BRM_VERBOSE;
    CU_ErrorAction error_action = CUEA_IGNORE;
  
    CU_ErrorCode cue = CU_initialize_registry();
    if (cue != CUE_SUCCESS) { 
	printf("ERROR in CU_initialize_registry\n");
	return;
    }
    CU_basic_set_mode(mode);
    CU_set_error_action(error_action);
  
    CU_pSuite hitCounting, wordAdding, wordChomping, wordChecking;

    hitCounting = CU_add_suite("Hit counting", my_suite_init, my_suite_clean);
    wordAdding = CU_add_suite("Word adding", my_suite_init, my_suite_clean);
    wordChecking = CU_add_suite("Word checking", my_suite_init, my_suite_clean);

    CU_ADD_TEST(hitCounting, test_5_hits);  
    CU_ADD_TEST(hitCounting, test_1_hits);  
    CU_ADD_TEST(hitCounting, test_no_hits);  
    CU_ADD_TEST(hitCounting, test_hits_out_of_order_do_not_count);


    CU_ADD_TEST(wordChecking, test_check_for_word_in_jdict);
    CU_ADD_TEST(wordChecking, test_winnowing_jdict);
  
    CU_basic_run_tests();
    CU_cleanup_registry();
}
