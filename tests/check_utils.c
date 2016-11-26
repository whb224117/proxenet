/**
 * Test suite for utils.h
 */
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <check.h>

#include "../utils.h"


START_TEST(proxenet_xzero_test)
{
        char *buf = proxenet_xmalloc(10);
        memset(buf, '\x41', 10);
        proxenet_xzero(buf, 10);
        ck_assert_int_eq(buf[0], 0x00);
        proxenet_xfree(buf);
}
END_TEST


START_TEST(proxenet_xstrdup2_test)
{
        char *buf = proxenet_xstrdup2("THIS IS A TEST");
        ck_assert_str_eq(buf, "THIS IS A TEST");
        proxenet_xfree(buf);
}
END_TEST


START_TEST(proxenet_lstrip_test)
{
        const char orig[] = "X-Header-Test: blahblah";
        char *str;

        str = proxenet_xstrdup2(orig);
        proxenet_lstrip(str);
        ck_assert_str_eq(str, orig);
        proxenet_xfree(str);

        str = proxenet_xstrdup2("   \t \rX-Header-Test: blahblah");
        proxenet_lstrip(str);
        ck_assert_str_eq(str, orig);
        proxenet_xfree(str);
}
END_TEST


START_TEST(proxenet_rstrip_test)
{
        const char orig[] = "X-Header-Test: blahblah";
        char *str;

        str = proxenet_xstrdup2(orig);
        proxenet_rstrip(str);
        ck_assert_str_eq(str, orig);
        proxenet_xfree(str);

        str = proxenet_xstrdup2("X-Header-Test: blahblah   \t \r\n");
        proxenet_rstrip(str);
        ck_assert_str_eq(str, orig);
        proxenet_xfree(str);
}
END_TEST


START_TEST(proxenet_strip_test)
{
        const char orig[] = "X-Header-Test: blahblah";
        char *str;

        str = proxenet_xstrdup2(orig);
        proxenet_strip(str);
        ck_assert_str_eq(str, orig);
        proxenet_xfree(str);

        str = proxenet_xstrdup2("   \t \nX-Header-Test: blahblah   \t \r\n");
        proxenet_strip(str);
        ck_assert_str_eq(str, orig);
        proxenet_xfree(str);
}
END_TEST


Suite * utils_suite(void)
{
    Suite *s;
    TCase *tc_memory, *tc_string;

    s = suite_create("utils");

    /* Test for memory alloc/de-alloc functions */
    tc_memory = tcase_create("Memory");
    tcase_add_test(tc_memory, proxenet_xzero_test);

    /* Test for string manipulation functions */
    tc_string = tcase_create("String");
    tcase_add_test(tc_string, proxenet_xstrdup2_test);
    tcase_add_test(tc_string, proxenet_lstrip_test);
    tcase_add_test(tc_string, proxenet_rstrip_test);
    tcase_add_test(tc_string, proxenet_strip_test);

    suite_add_tcase(s, tc_memory);
    suite_add_tcase(s, tc_string);
    return s;
}


int main(void)
{
         int number_failed;
         Suite *s;
         SRunner *sr;

         s = utils_suite();
         sr = srunner_create(s);

         srunner_run_all(sr, CK_NORMAL);
         number_failed = srunner_ntests_failed(sr);
         srunner_free(sr);
         return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}