/*
    Exercise 6 - Parrot Server

    Automated tests for this one not implemented yet! 😭
    Plan is to fork and exec your Parrot Server and then send requests to it.
*/

#include "../../vendor/unity/unity.h"
#include "../src/parrot_server.h"

void placeholder(void)
{
    TEST_IGNORE()
}

int main(void)
{
    UnityBegin("test/test_parrot_server.c");

    RUN_TEST(placeholder);

    UnityEnd();
    return 0;
}
