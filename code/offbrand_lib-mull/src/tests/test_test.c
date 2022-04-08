#include "../../include/offbrand.h"
#include "../../include/obdeque.h"
#include "../../include/obtest.h"
#include "../../include/offbrand.h"
#include "../../include/obint.h"
#include "../../include/private/obint_private.h"
#include "../../include/obstring.h"
#include "../../include/offbrand.h"
#include "../../include/obmap.h"
#include "../../include/private/obmap_private.h"
#include "../../include/obtest.h"

#include "../../include/offbrand.h"
#include "../../include/obstring.h"
#include "../../include/offbrand.h"
#include "../../include/obtest.h"


#include "../../include/offbrand.h"
#include "../../include/obvector.h"
#include "../../include/private/obvector_private.h" /* For testing purposes
                                                       only */
#include "../../include/obtest.h"

/** main unit test routine */
int obdeque_test() {

  obdeque *test_deque_a, *test_deque_b, *joined_deque;
  obdeque_iterator *head_it, *tail_it, *copy_it;
  obtest *a, *b, *c, *d, *e;
  uint32_t i;

  /* create test objects */
  test_deque_a = obdeque_new();
  a = obtest_new(1);
  b = obtest_new(2);
  c = obtest_new(3);
  d = obtest_new(4);
  e = obtest_new(5);


  /* test the empty deque */
  assert(obdeque_is_empty(test_deque_a) != 0);
  assert(obdeque_length(test_deque_a) == 0);
  assert(obdeque_head_iterator(test_deque_a) == NULL);
  assert(obdeque_tail_iterator(test_deque_a) == NULL);

  /* test a deque with a single element */
  obdeque_add_at_head(test_deque_a, (obj *)a);

  assert(obdeque_is_empty(test_deque_a) == 0);
  assert(obdeque_length(test_deque_a) == 1);
  assert(ob_reference_count((obj *)a) == 2);
  assert(obtest_id((obtest *)obdeque_obj_at_head(test_deque_a)) == 1);
  assert(obtest_id((obtest *)obdeque_obj_at_tail(test_deque_a)) == 1);

  head_it = obdeque_head_iterator(test_deque_a);
  tail_it = obdeque_tail_iterator(test_deque_a);

  assert(head_it != NULL);
  assert(tail_it != NULL);
  assert(obtest_id((obtest *)obdeque_obj_at_iterator(test_deque_a, head_it)) == 1);
  assert(obtest_id((obtest *)obdeque_obj_at_iterator(test_deque_a, tail_it)) == 1);

  assert(obdeque_find_obj(test_deque_a, (obj *)a));

  /* test removing the only element from the deque */
  obdeque_remove_tail(test_deque_a);

  /* check that element is still referenced because of existing iterators */
  assert(ob_reference_count((obj *)a) == 2);
  ob_release((obj *)head_it);
  ob_release((obj *)tail_it);
  assert(ob_reference_count((obj *)a) == 1);


  assert(obdeque_is_empty(test_deque_a) != 0);
  assert(obdeque_length(test_deque_a) == 0);
  assert(obdeque_head_iterator(test_deque_a) == NULL);
  assert(obdeque_tail_iterator(test_deque_a) == NULL);

  /* test deque with multiple elements */
  obdeque_add_at_tail(test_deque_a, (obj *)a);
  obdeque_add_at_head(test_deque_a, (obj *)b);
  obdeque_add_at_tail(test_deque_a, (obj *)c);
  obdeque_add_at_head(test_deque_a, (obj *)d);
  obdeque_add_at_tail(test_deque_a, (obj *)e);

  assert(obdeque_is_empty(test_deque_a) == 0);
  assert(obdeque_length(test_deque_a) == 5);

  /* test deque removal functions */
  head_it = obdeque_head_iterator(test_deque_a);
  obdeque_remove_at_iterator(test_deque_a, head_it);
  ob_release((obj *)head_it);

  head_it = obdeque_head_iterator(test_deque_a);
  do{
    assert(obtest_id((obtest *)obdeque_obj_at_iterator(test_deque_a, head_it)) != 4);
  }while(obdeque_iterate_next(test_deque_a, head_it));

  ob_release((obj *)head_it);
  obdeque_add_at_head(test_deque_a, (obj *)d);

  test_deque_b = obdeque_copy(test_deque_a);

  assert(ob_reference_count((obj *)a) == 3);
  assert(ob_compare((obj *)test_deque_a, (obj *)test_deque_b) == OB_EQUAL_TO);
  assert(ob_hash((obj *)test_deque_a) ==  ob_hash((obj *)test_deque_b));

  obdeque_sort(test_deque_a, OB_LEAST_TO_GREATEST);

  assert(obdeque_length(test_deque_a) == 5);
  assert(ob_compare((obj *)test_deque_a, (obj *)test_deque_b) == OB_NOT_EQUAL);
  assert(ob_hash((obj *)test_deque_a) !=  ob_hash((obj *)test_deque_b));

  i = 1;
  head_it = obdeque_head_iterator(test_deque_a);
  do{
    assert(obtest_id((obtest *)obdeque_obj_at_iterator(test_deque_a, head_it)) == i);
    i++;
  }while(obdeque_iterate_next(test_deque_a, head_it));

  ob_release((obj *)head_it);
  ob_release((obj *)test_deque_a);
  assert(ob_reference_count((obj *)a) == 2);

  test_deque_a = obdeque_copy(test_deque_b);
  joined_deque = obdeque_join(test_deque_a, test_deque_b);
  obdeque_sort(joined_deque, OB_GREATEST_TO_LEAST);

  assert(obdeque_length(joined_deque) == 10);
  assert(ob_reference_count((obj *)a) == 5); /* the joined deque has two references,
                                            as a is contained within twice */

  tail_it = obdeque_tail_iterator(joined_deque);
  obdeque_remove_tail(joined_deque);
  assert(obdeque_iterate_prev(joined_deque, tail_it) == 0);
  assert(obdeque_iterate_next(joined_deque, tail_it) == 0);
  ob_release((obj *)tail_it);

  tail_it = obdeque_tail_iterator(joined_deque);
  obdeque_add_at_iterator(joined_deque, tail_it, (obj *)a);
  ob_release((obj *)tail_it);

  tail_it = obdeque_tail_iterator(joined_deque);
  copy_it = obdeque_copy_iterator(tail_it);
  ob_release((obj *)tail_it);
  tail_it = copy_it;


  for(i=0; i<10; i++){
    assert(obtest_id((obtest *)obdeque_obj_at_iterator(joined_deque, tail_it)) == i/2+1);
    if(i != 9) assert(obdeque_iterate_prev(joined_deque, tail_it));
  }

  assert(obdeque_iterate_prev(joined_deque, tail_it) == 0);

  ob_release((obj *)tail_it);

  obdeque_clear(test_deque_a);
  obdeque_clear(test_deque_b);

  for(i=0; i<10; i++){
    obdeque_remove_head(joined_deque);
  }

  assert(obdeque_is_empty(joined_deque) != 0);
  assert(obdeque_length(joined_deque) == 0);
  assert(ob_reference_count((obj *)a) == 1);

  ob_release((obj *)test_deque_a);
  ob_release((obj *)test_deque_b);
  ob_release((obj *)joined_deque);
  ob_release((obj *)e);
  ob_release((obj *)d);
  ob_release((obj *)c);
  ob_release((obj *)b);
  ob_release((obj *)a);

  printf("obdeque: TESTS PASSED\n");
  return 0;
}

int obint_test (){

  obint *a, *b, *c;
  obstring *str1, *str2;

  /* test machine integer creation and value methods */
  a = obint_new(1024);
  assert(obint_value(a) == 1024);
  b = obint_new(9581085);
  assert(obint_value(b) == 9581085);
  c = obint_new(-999);
  assert(obint_value(c) == -999);

  ob_release((obj *)a);
  ob_release((obj *)b);
  ob_release((obj *)c);

  /* test string integer creation and value methods */
  str1 = obstring_new("12345");
  a = obint_from_string(str1);
  assert(obint_value(a) == 12345);
  str2 = obint_to_string(a);
  assert(ob_compare((obj *)str1, (obj *)str2) == OB_EQUAL_TO);

  ob_release((obj *)a);
  ob_release((obj *)str1);
  ob_release((obj *)str2);

  str1 = obstring_new("-012345");
  a = obint_from_string(str1);
  ob_release((obj *)str1);
  assert(obint_value(a) == -12345);
  str1 = obstring_new("-12345");
  str2 = obint_to_string(a);
  assert(ob_compare((obj *)str1, (obj *)str2) == OB_EQUAL_TO);

  ob_release((obj *)a);
  ob_release((obj *)str1);
  ob_release((obj *)str2);

  /* test copy method */
  a = obint_new(918394);
  b = obint_copy(a);
  assert(ob_compare((obj *)a, (obj *)b) == OB_EQUAL_TO);
  assert(a != b);
  assert(a->digits != b->digits);

  ob_release((obj *)a);
  ob_release((obj *)b);

  /* test integer zero and negative methods */
  a = obint_new(1948);
  b = obint_new(-1);
  str1 = obstring_new("-0");
  c = obint_from_string(str1);
  ob_release((obj *)str1);

  assert(!obint_is_zero(a));
  assert(!obint_is_zero(b));
  assert(obint_is_zero(c));

  assert(!obint_is_negative(a));
  assert(obint_is_negative(b));
  assert(!obint_is_negative(c));

  ob_release((obj *)a);
  ob_release((obj *)b);
  ob_release((obj *)c);

  /* test integer addition */
  a = obint_new(999);
  b = obint_add_primitive(a, 1111);
  assert(obint_value(b) == 2110);
  c = obint_add(a, b);
  assert(obint_value(c) == 2110 + 999);

  ob_release((obj *)a);
  ob_release((obj *)b);
  ob_release((obj *)c);

  a = obint_new(-999);
  b = obint_add_primitive(a, 1);
  assert(obint_value(b) == -998);
  ob_release((obj *)b);
  b = obint_add_primitive(a, -1);
  assert(obint_value(b) == -1000);
  ob_release((obj *)b);
  b = obint_new(1000);
  c = obint_add(a, b);
  assert(obint_value(c) == 1);

  ob_release((obj *)a);
  ob_release((obj *)b);
  ob_release((obj *)c);

  /* test integer subtraction */
  a = obint_new(999);
  b = obint_subtract_primitive(a, 1111);
  assert(obint_value(b) == -112);
  c = obint_subtract(a, b);
  assert(obint_value(c) == 999 + 112);

  ob_release((obj *)a);
  ob_release((obj *)b);
  ob_release((obj *)c);

  a = obint_new(-999);
  b = obint_subtract_primitive(a, 1);
  assert(obint_value(b) == -1000);
  ob_release((obj *)b);
  b = obint_subtract_primitive(a, -1);
  assert(obint_value(b) == -998);
  ob_release((obj *)b);
  b = obint_new(1000);
  c = obint_subtract(a, b);
  assert(obint_value(c) == -1999);

  ob_release((obj *)a);
  ob_release((obj *)b);
  ob_release((obj *)c);

  /* test integer multiplication (size under digit limit for explicit integer
   * arithmetic) */
  a = obint_new(999);
  b = obint_multiply_primitive(a, -999);
  assert(obint_value(b) == 999*-999);
  c = obint_multiply(a, b);
  assert(obint_value(c) == 999*999*-999);

  ob_release((obj *)a);
  ob_release((obj *)b);
  ob_release((obj *)c);

  a = obint_new(-1928491);
  b = obint_multiply_primitive(a, -58);
  assert(obint_value(b) == -1928491*-58);
  ob_release((obj *)b);
  b = obint_new(2);
  c = obint_multiply(a, b);
  assert(obint_value(c) == -1928491*2);

  ob_release((obj *)a);
  ob_release((obj *)b);
  ob_release((obj *)c);

  a = obint_new(29458);
  b = obint_multiply_primitive(a, 0);
  assert(obint_is_zero(b) != 0);

  ob_release((obj *)a);
  ob_release((obj *)b);

  /* test integer division (size under digit limit for explicit integer
   * arithmetic) */
  a = obint_new(999);
  b = obint_divide_primitive(a, -999);
  assert(obint_value(b) == -1);
  c = obint_divide_primitive(a, 33);
  assert(obint_value(c) == 999/33);

  ob_release((obj *)a);
  ob_release((obj *)b);
  ob_release((obj *)c);

  a = obint_new(1940248);
  b = obint_divide_primitive(a, -2848);
  assert(obint_value(b) == 1940248/(-2848));
  c = obint_divide(a, b);
  assert(obint_value(c) == 1940248/(1940248/(-2848)));

  ob_release((obj *)a);
  ob_release((obj *)b);
  ob_release((obj *)c);

  /* test integer modulus (size under digit limit for explicit integer
   * arithmetic) */
  a = obint_new(999);
  b = obint_mod_primitive(a, -999);
  assert(obint_value(b) == 999%(-999));
  c = obint_mod_primitive(a, 33);
  assert(obint_value(c) == 999%33);

  ob_release((obj *)a);
  ob_release((obj *)b);
  ob_release((obj *)c);

  a = obint_new(1940248);
  b = obint_mod_primitive(a, -2848);
  assert(obint_value(b) == 1940248%(-2848));
  c = obint_mod(a, b);
  assert(obint_value(c) == 1940248%(1940248%(-2848)));

  ob_release((obj *)a);
  ob_release((obj *)b);
  ob_release((obj *)c);

  /* set digit limit for integer arithmetic low, for test purposes */
  obint_set_max_digits(2);

  /* test integer multiplication (size over digit limit for explicit integer
   * arithmetic) */
  a = obint_new(999);
  b = obint_multiply_primitive(a, -999);
  assert(obint_value(b) == 999*-999);
  c = obint_multiply(a, b);
  assert(obint_value(c) == 999*999*-999);

  ob_release((obj *)a);
  ob_release((obj *)b);
  ob_release((obj *)c);

  a = obint_new(-1928491);
  b = obint_multiply_primitive(a, -58);
  assert(obint_value(b) == -1928491*-58);
  ob_release((obj *)b);
  b = obint_new(2);
  c = obint_multiply(a, b);
  assert(obint_value(c) == -1928491*2);

  ob_release((obj *)a);
  ob_release((obj *)b);
  ob_release((obj *)c);

  a = obint_new(29458);
  b = obint_multiply_primitive(a, 0);
  assert(obint_is_zero(b) != 0);

  ob_release((obj *)a);
  ob_release((obj *)b);

  /* test integer division (size under digit limit for explicit integer
   * arithmetic) */
  a = obint_new(999);
  b = obint_divide_primitive(a, -999);
  assert(obint_value(b) == -1);
  c = obint_divide_primitive(a, 33);
  assert(obint_value(c) == 999/33);

  ob_release((obj *)a);
  ob_release((obj *)b);
  ob_release((obj *)c);

  a = obint_new(1940248);
  b = obint_divide_primitive(a, -2848);
  assert(obint_value(b) == 1940248/(-2848));
  c = obint_divide(a, b);
  assert(obint_value(c) == 1940248/(1940248/(-2848)));

  ob_release((obj *)a);
  ob_release((obj *)b);
  ob_release((obj *)c);

  /* test integer modulus (size over digit limit for explicit integer
   * arithmetic) */
  a = obint_new(999);
  b = obint_mod_primitive(a, -999);
  assert(obint_value(b) == 999%(-999));
  c = obint_mod_primitive(a, 33);
  assert(obint_value(c) == 999%33);

  ob_release((obj *)a);
  ob_release((obj *)b);
  ob_release((obj *)c);

  a = obint_new(1940248);
  b = obint_mod_primitive(a, -2848);
  assert(obint_value(b) == 1940248%(-2848));
  c = obint_mod(a, b);
  assert(obint_value(c) == 1940248%(1940248%(-2848)));

  ob_release((obj *)a);
  ob_release((obj *)b);
  ob_release((obj *)c);

  printf("obint: TESTS PASSED\n");
  return 0;
}

#define ARRAY_SIZE 2048

/**
 * @brief Main unit testing routine
 */
int obmap_test (){

  uint32_t i;

  obmap *test_map, *map_copy;
  obtest *a, *b, *c, *d, *e, *f, *g, *h;
  obtest *test_array[ARRAY_SIZE];
  obtest *test;

  test_map = obmap_new();
  a = obtest_new(1);
  b = obtest_new(2);
  c = obtest_new(3);
  d = obtest_new(103923);
  e = obtest_new(1+MAP_CAPACITIES[0]); /* ensures hash collision with a */
  f = obtest_new(1+2*MAP_CAPACITIES[0]);
  g = obtest_new(1+3*MAP_CAPACITIES[0]);
  h = obtest_new(1+4*MAP_CAPACITIES[0]);

  assert(ob_hash((obj *)a)%MAP_CAPACITIES[0] == ob_hash((obj *)e)%MAP_CAPACITIES[0]);

  assert(obmap_lookup(test_map, (obj *)a) == NULL);

  obmap_insert(test_map, (obj *)a, (obj *)b);
  test = (obtest *)obmap_lookup(test_map, (obj *)a);

  assert(test);
  assert(ob_compare((obj *)b, (obj *)test) == OB_EQUAL_TO);
  assert(ob_reference_count((obj *)test) > 1);

  obmap_insert(test_map, (obj *)e, (obj *)c);
  obmap_insert(test_map, (obj *)f, (obj *)d);
  obmap_insert(test_map, (obj *)g, (obj *)e);
  obmap_insert(test_map, (obj *)h, (obj *)f);
  test = (obtest *)obmap_lookup(test_map, (obj *)a);

  assert(ob_compare((obj *)b, (obj *)test) == OB_EQUAL_TO);
  assert(ob_compare((obj *)c, (obj *)test) != OB_EQUAL_TO);

  test = (obtest *)obmap_lookup(test_map, (obj *)e);

  assert(ob_compare((obj *)c, (obj *)test) == OB_EQUAL_TO);
  assert(ob_compare((obj *)b, (obj *)test) != OB_EQUAL_TO);

  test = (obtest *)obmap_lookup(test_map, (obj *)a);
  obmap_insert(test_map, (obj *)a, NULL); /* remove binding of a -> b */

  assert(obmap_lookup(test_map, (obj *)a) == NULL);
  assert(ob_reference_count((obj *)test) == 1);

  test = (obtest *)obmap_lookup(test_map, (obj *)h);
  assert(ob_compare((obj *)f, (obj *)test) == OB_EQUAL_TO);

  map_copy = obmap_copy(test_map);
  obmap_insert(test_map, (obj *)e, NULL); /* remove binding of e -> c */
  test = (obtest *)obmap_lookup(map_copy, (obj *)e);

  assert(ob_compare((obj *)test, (obj *)c) == OB_EQUAL_TO);

  obmap_remove(test_map, (obj *)e);
  test = (obtest *)obmap_lookup(map_copy, (obj *)e);

  assert(ob_compare((obj *)test, (obj *)c) == OB_EQUAL_TO);

  test = (obtest *)obmap_lookup(test_map, (obj *)e);

  assert(test == NULL);

  assert(ob_hash((obj *)test_map) != ob_hash((obj *)map_copy));
  assert(ob_compare((obj *)test_map, (obj *)map_copy) != OB_EQUAL_TO);

  obmap_insert(test_map, (obj *)e, (obj *)c);

  assert(ob_hash((obj *)test_map) == ob_hash((obj *)map_copy));
  assert(ob_compare((obj *)test_map, (obj *)map_copy) == OB_EQUAL_TO);

  obmap_clear(map_copy);

  assert(obmap_lookup(map_copy, (obj *)e) == NULL);
  assert(obmap_lookup(map_copy, (obj *)a) == NULL);
  assert(obmap_lookup(map_copy, (obj *)f) == NULL);

  for(i=0; i<ARRAY_SIZE; i++){
    test_array[i] = obtest_new(i);
    obmap_insert(test_map, (obj *)test_array[i], (obj *)test_array[i]);
  }

  for(i=0; i<ARRAY_SIZE; i++)
    assert(ob_compare((obj *) test_array[i],
                   obmap_lookup(test_map, (obj *)test_array[i])) ==OB_EQUAL_TO);

  ob_release((obj *)a);
  ob_release((obj *)b);
  ob_release((obj *)c);
  ob_release((obj *)d);
  ob_release((obj *)e);
  ob_release((obj *)f);
  ob_release((obj *)g);
  ob_release((obj *)h);

  ob_release((obj *)test_map);
  ob_release((obj *)map_copy);

  for(i=0; i<ARRAY_SIZE; i++)
    ob_release((obj *)test_array[i]);

  printf("obmap: TESTS PASSED\n");

  return 0;
}

int obstring_test (){

  obstring *str1, *str2, *str3, *null_str;
  obvector *tokens;
  const char *contents;

  str1 = obstring_new("Hello, World!");

  /* Test obstring_new and obstring_cstring */
  contents = obstring_cstring(str1);
  assert(strcmp(contents, "Hello, World!") == 0);


  /* Test obstring_copy_substring and obstring_length */
  str2 = obstring_copy_substring(str1, 0, 5);
  contents = obstring_cstring(str2);
  assert(strcmp(contents, "Hello") == 0);

  ob_release((obj *)str2);

  str2 = obstring_copy_substring(str1, -15, 7);
  contents = obstring_cstring(str2);
  assert(strcmp(contents, "Hello") == 0);

  ob_release((obj *)str2);

  str2 = obstring_copy_substring(str1, 0, obstring_length(str1));
  contents = obstring_cstring(str2);
  assert(strcmp(contents, "Hello, World!") == 0);

  ob_release((obj *)str2);

  null_str = obstring_copy_substring(str1, 20, 2);
  assert(obstring_length(null_str) == 0);

  /* Test obstring_char_at_index */
  assert(obstring_char_at_index(str1, 0) == 'H');
  assert(obstring_char_at_index(str1, -5) == 'o');
  assert(obstring_char_at_index(str1, -20) == '\0');
  assert(obstring_char_at_index(str1, 20) == '\0');
  assert(obstring_char_at_index(null_str, 0) == '\0');

  /* Test String Concatenation */
  str2 = obstring_new(" And hello again!");
  str3 = obstring_concat(str1, str2);
  contents = obstring_cstring(str3);
  assert(strcmp(contents, "Hello, World! And hello again!") == 0);

  ob_release((obj *)str2);

  str2 = obstring_concat(null_str, str1);
  contents = obstring_cstring(str2);
  assert(strcmp(contents, "Hello, World!") == 0);

  /* Test String Comparision */
  assert(ob_compare((obj *)str1, (obj *)str2) == OB_EQUAL_TO);
  assert(ob_compare((obj *)str1, (obj *)str3) == OB_LESS_THAN);
  assert(ob_compare((obj *)str1, (obj *)null_str) == OB_GREATER_THAN);

  ob_release((obj *)str2);
  ob_release((obj *)str3);

  /* Test String Splits */
  str2 = obstring_new("Testing string split   into#!many");
  tokens = obstring_split(str2, " ");
  assert(strcmp(obstring_cstring((obstring *)obvector_obj_at_index(tokens, 0)), "Testing")
         == 0);
  assert(strcmp(obstring_cstring((obstring *)obvector_obj_at_index(tokens, 3)),
                           "into#!many") == 0);

  ob_release((obj *)tokens);

  tokens = obstring_split(str2, "#!");
  assert(strcmp(obstring_cstring((obstring *)obvector_obj_at_index(tokens, 0)),
                           "Testing string split   into") == 0);
  assert(strcmp(obstring_cstring((obstring *)obvector_obj_at_index(tokens, 1)), "many")
         == 0);

  ob_release((obj *)tokens);

  /* Test String Search */

  assert(obstring_find_substring(str2, "Testing") != 0);
  assert(obstring_find_substring(str2, "#!many") != 0);
  assert(obstring_find_substring(str2, "Hello World") == 0);

  /* Test Regex Match */
  str3 = obstring_match_regex(str1, "[Hh]el{1,2}.");
  assert(strcmp(obstring_cstring(str3), "Hello") == 0);
  ob_release((obj *)str3);

  str3 = obstring_match_regex(str2, " *into[#!]{2,2}.*$");
  assert(strcmp(obstring_cstring(str3), "   into#!many") == 0);

  ob_release((obj *)str3);
  ob_release((obj *)str2);
  ob_release((obj *)str1);
  ob_release((obj *)null_str);

  /* TESTS COMPLETE */
  printf("obstring: TESTS PASSED\n");

  return 0;
}

int obtest_test(){

  int i;
  obtest *test_obj, *a, *b;
  test_obj = obtest_new(1);
  a = obtest_new(3);
  b = obtest_new(3);

  /* ob_retain object, reference count should be 4 */
  for(i=0; i<3; i++){
    ob_retain((obj *)test_obj);
  }

  if(ob_reference_count((obj *)test_obj) != 4){
    fprintf(stderr, "obtest_test: reference count not incrememted correctly by "
                    "ob_retain\nTEST FAILED\n");
    exit(1);
  }

  /* ob_release object until test_obj is deallocated or until ob_release has been
   * called more than 4 times */
  i=0;
  while(++i < 5 && ob_release((obj *)test_obj) != NULL){}

  if(i<4){
    fprintf(stderr, "obtest_test: test_obj ob_released before reference count "
                    "reached zero, TEST FAILED\n");
    exit(1);
	}
  else if(i>4){
    fprintf(stderr, "obtest_test: test_obj not ob_released when reference count "
                    "reached zero\n");
    exit(1);
	}

  if(!ob_has_same_class((obj *)a, (obj *)b)){
    fprintf(stderr, "obtest_test: Two obtest objects were not of the same "
                    "class, TEST FAILED\n");
    exit(1);
  }

  if(!ob_has_class((obj *)a, "obtest")){
    fprintf(stderr, "obtest_test: An obtest object was not considered to be an "
                    "obtest object during check, TEST FAILED\n");
    exit(1);
  }

  ob_hash((obj *)a);

  printf("obtest: TEST PASSED\n");
  return 0;
}

int obvector_test(){

  uint32_t i, id;
  obtest *tests[6], *singleton, *tmp;
  obvector *main_vec, *copy_vec;

  main_vec = obvector_new(1);
  singleton = obtest_new(7);

  for(i=0; i<6; i++){
    tests[i] = obtest_new(i);
    obvector_store_at_index(main_vec, (obj *)tests[i], i);

    if(ob_reference_count((obj *)tests[i]) != 2){
      fprintf(stderr, "obvector_test: vector did not properly ob_retain element "
                      "TEST FAILED\n");
      exit(1);
    }

    ob_release((obj *)tests[i]); /* vector should maintain only references */
  }

  if(obvector_length(main_vec) != 6){
    fprintf(stderr, "obvector_test: vector size is off, TEST FAILED\n");
    exit(1);
  }

  for(i=0; i<6; i++){
    if(obtest_id((obtest *)obvector_obj_at_index(main_vec,i)) != i){
      fprintf(stderr, "obvector_test: vector does not contain added contents "
                      "in expected order\nTEST FAILED\n");
      printf("%d\n", i);
      exit(1);
    }
  }

  obvector_store_at_index(main_vec, (obj *)singleton, 12);
  if(obvector_length(main_vec) != 13){
    fprintf(stderr, "obvector_test: store did not properly extend length "
                    "TEST FAILED\n");
    exit(1);
  }


  obvector_store_at_index(main_vec, NULL, 12);
  if(obvector_length(main_vec) != 6){
    fprintf(stderr, "obvector_test: remove did not properly get rid of element "
                    "TEST FAILED\n");
    exit(1);
  }

  if(ob_reference_count((obj *)singleton) != 1){
    fprintf(stderr, "obvector_test: vector did not ob_release element on removal "
                    "TEST FAILED\n");
    exit(1);
  }

  tmp = (obtest *)obvector_obj_at_index(main_vec, 3);
  ob_retain((obj *)tmp);

  obvector_store_at_index(main_vec, (obj *)singleton, 3);
  if(ob_reference_count((obj *)tmp) != 1){
    fprintf(stderr, "obvector_test: vector did not ob_release element on "
                    "replacement, TEST FAILED\n");
    exit(1);
  }

  if(obvector_length(main_vec) != 6 ||
     obtest_id((obtest *)obvector_obj_at_index(main_vec, 3)) !=
     obtest_id(singleton)){
    fprintf(stderr, "obvector_test: element was not added properly to vector "
                    "at index\nTEST FAILED\n");
    exit(1);
  }

  obvector_store_at_index(main_vec, (obj *)tmp, 3);

  /* reduce reference count to 1, so only vector holds reference to obj */
  ob_release((obj *)tmp);

  if(obvector_find_obj(main_vec, (obj *)singleton)){
    fprintf(stderr, "obvector_test: vector did not replace element correctly, "
                    "or was not found\nTEST FAILED\n");
    exit(1);
  }

  obvector_store_at_index(main_vec, (obj *)singleton, 10);
  if(obvector_length(main_vec) != 11){
    fprintf(stderr, "obvector_test: store did not properly extend length "
                    "TEST FAILED\n");
    exit(1);
  }

  obvector_sort(main_vec, OB_LEAST_TO_GREATEST);
  if(obvector_length(main_vec) != 7){
    fprintf(stderr, "obvector_test: sort did not properly remove NULLs "
                    "TEST FAILED\n");
    fprintf(stderr, "obvector_test: vector size == %d\n",
                    obvector_length(main_vec));
    for(i=0; i<obvector_length(main_vec); i++){
      if(obvector_obj_at_index(main_vec, i)) printf("object\n");
      else printf("NULL\n");
    }
    exit(1);
  }

  id = 0;
  for(i=0; i<obvector_length(main_vec); i++){
    if(id > obtest_id((obtest *)obvector_obj_at_index(main_vec, i))){
      fprintf(stderr, "obvector_test: vector was not sorted least to "
                      "greatest, TEST FAILED\n");
      exit(1);
    }
    id = obtest_id((obtest *)obvector_obj_at_index(main_vec, i));
  }

  obvector_store_at_index(main_vec, NULL, 6);
  obvector_store_at_index(main_vec, (obj *)singleton, 10);

  obvector_sort(main_vec, OB_GREATEST_TO_LEAST);
  if(obvector_length(main_vec) != 7){
    fprintf(stderr, "obvector_test: second sort did not properly remove NULLs "
                    "TEST FAILED\n");
    exit(1);
  }

  id = 10;
  for(i=0; i<obvector_length(main_vec); i++){
    if(id < obtest_id((obtest *)obvector_obj_at_index(main_vec, i))){
      fprintf(stderr, "obvector_test: vector was not sorted greatest to "
                      "least, TEST FAILED\n");
      exit(1);
    }
    id = obtest_id((obtest *)obvector_obj_at_index(main_vec, i));
  }

  copy_vec = obvector_copy(main_vec);

  assert(ob_compare((obj *)copy_vec, (obj *)main_vec) == OB_EQUAL_TO);
  assert(ob_hash((obj *)copy_vec) == ob_hash((obj *)main_vec));

  ob_release((obj *)singleton); /* ob_release singleton once so it is only referenced
                                by containing vectors */

  for(i=0; i<obvector_length(main_vec); i++){
    if(ob_reference_count((obj *)(obtest *)obvector_obj_at_index(main_vec, i)) != 2){
      fprintf(stderr, "obvector_test: vector contents not ob_retained on copy, "
                      "TEST FAILED\n");
      exit(1);
    }
  }

  /* get obj at index and ob_retain it so it isnt deallocated */
  tmp = (obtest *)obvector_obj_at_index(main_vec, 3);
  ob_retain((obj *)tmp);

  obvector_store_at_index(main_vec, NULL, 3);

  assert(ob_compare((obj *)copy_vec, (obj *)main_vec) == OB_NOT_EQUAL);
  assert(ob_hash((obj *)copy_vec) != ob_hash((obj *)main_vec));

  if(obvector_find_obj(main_vec, (obj *)tmp)){
    fprintf(stderr, "obvector_test: Item was not removed properly from vector"
                    "index, TEST FAILED\n");
    exit(1);
  }

  obvector_store_at_index(main_vec, (obj *)tmp, 3);
  assert(obvector_length(main_vec) == 7);
  obvector_concat(main_vec, copy_vec);
  assert(obvector_length(main_vec) == 14);

  for(i=0; i<obvector_length(main_vec)/2; i++){
    if(obtest_id((obtest *)obvector_obj_at_index(main_vec,i)) !=
       obtest_id((obtest *)obvector_obj_at_index(main_vec,i+7))){
      fprintf(stderr, "obvector_test: Copy of vector not appended properly, "
                      "TEST FAILED\n");
      exit(1);
    }
  }

  ob_release((obj *)main_vec);
  ob_release((obj *)copy_vec);

  if(ob_reference_count((obj *)tmp) != 1){
    fprintf(stderr, "obvector_test: ob_releases of obvector container did not "
                    "properly manage\ncontained obtest reference count, TEST "
                    "FAILED\n");
    exit(1);
  }

  ob_release((obj *)tmp);

  printf("obvector: TESTS PASSED\n");
  return 0;
}

int main() {
    obdeque_test();
    obint_test();
    obmap_test();
    obstring_test();
    obtest_test();
    obvector_test();
    
}