#include <dwelui/string.h>
#include <dwelui/test.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_providers.c"

TEST(from_buffer, {
    const char *fixtureFilepath = test_data_get(char);
    FILE       *fixtureFd       = fopen(fixtureFilepath, "r");
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

typedef struct {
    const char *cstr;
    const char *search;
    const char *replace;
    const char *replaced;
    size_t      count;
} ReplaceData;
TEST_DATA_PROVIDER(replaceDataProvider, {
    static const ReplaceData item1 = {"a b c d", " ", "-", "a-b-c-d", 3};
    test_data_add("a b c d -> a-b-c-d", item1);

    static const ReplaceData item2 = {"abc def ghi", " ", "-", "abc-def-ghi", 2};
    test_data_add("abc def ghi -> abc-def-ghi", item2);

    static const ReplaceData item3 = {"abc def ghi", " def ", "-", "abc-ghi", 1};
    test_data_add("abc def ghi -> abc-ghi", item3);

    static const ReplaceData item4 = {"a b c d", " ", "-", "a-b-c d", 2};
    test_data_add("a b c d -> a-b-c d", item4);
})
TEST(replace, {
    const ReplaceData *data = test_data_get(ReplaceData);

    String             actual        = string_from_cstr(data->cstr);
    String             expected      = string_from_cstr(data->replaced);
    StringView         search        = string_view_from_cstr(data->search);
    StringView         replace       = string_view_from_cstr(data->replace);
    size_t             count = data->count;

    size_t             actualCount = string_replace(&actual, search, replace, count);

    test_assert(string_equal(actual, expected) == true);
    test_assert(actualCount == count);

    string_destroy(&actual);
    string_destroy(&expected);
})
TEST_OPTIONS(replace, .dataProvider = replaceDataProvider())

TEST(equal, {
    const EqualData *data     = test_data_get(EqualData);
    String           a        = string_from_cstr(data->a);
    String           b        = string_from_cstr(data->b);
    const bool       expected = data->expected;

    test_assert(string_equal(a, b) == expected);

    string_destroy(&a);
    string_destroy(&b);
})
TEST_OPTIONS(equal, .dataProvider = equalDataProvider())
