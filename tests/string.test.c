#include <dwelui/string.h>
#include <dwelui/test.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_providers.c"

TEST(from_buffer, {
    FILE *fixtureFd = fopen(test_data_get(char), "r");
    if (nullptr == fixtureFd) {
        perror("fopen");
    }

    size_t       chuckSize = 12;
    char         data[chuckSize + 1];
    size_t       length      = 0;
    size_t       totalLength = 0;

    StringBuffer buffer = string_buffer_start();

    do {
        length = fread(data, 1, chuckSize, fixtureFd);
        totalLength += length;

        string_buffer_append_data(&buffer, data, length);
    } while (0 != length);

    String string = string_from_buffer(buffer);

    test_assert(string.length == totalLength);

    string_buffer_destroy(&buffer);
    string_destroy(&string);
})
TEST_OPTIONS(from_buffer, .dataProvider = stringBufferFixtureDataProvider())

TEST(from_data, {
    const char *data   = test_data_get(char);
    size_t      length = strlen(data);

    String      string = string_from_data(data, length);

    test_assert(string.length == length);

    for (size_t i = 0; i < string.length; i++) {
        test_assert(string.data[i] == data[i]);
    }

    string_destroy(&string);
})
TEST_OPTIONS(from_data, .dataProvider = cstrDataProvider())

TEST(from_cstr, {
    const char *data = test_data_get(char);

    String      string = string_from_cstr(data);

    test_assert(string.length == strlen(data));

    for (size_t i = 0; i < string.length; i++) {
        test_assert(string.data[i] == data[i]);
    }

    string_destroy(&string);
})
TEST_OPTIONS(from_cstr, .dataProvider = cstrDataProvider())

TEST(clone, {
    const char *data = test_data_get(char);

    String      string = string_from_cstr(data);
    String      clone  = string_clone(string);
    string_destroy(&string);

    test_assert(clone.length == strlen(data));

    for (size_t i = 0; i < clone.length; i++) {
        test_assert(clone.data[i] == data[i]);
    }

    string_destroy(&clone);
})
TEST_OPTIONS(clone, .dataProvider = cstrDataProvider())

TEST(from_data_outlives_original_heap_data, {
    const char *data   = test_data_get(char);
    size_t      length = strlen(data);

    char       *dataHeap = malloc(sizeof(char) * length + 1);
    memcpy(dataHeap, data, length);
    dataHeap[length] = '\0';

    String string = string_from_data(dataHeap, length);

    free(dataHeap);

    test_assert(string.length == length);

    for (size_t i = 0; i < string.length; i++) {
        test_assert(string.data[i] == data[i]);
    }

    string_destroy(&string);
})
TEST_OPTIONS(from_data_outlives_original_heap_data, .dataProvider = cstrDataProvider())
