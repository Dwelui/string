#include <dwelui/string.h>
#include <dwelui/test.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

DATA_PROVIDER(stringDataProvider, {
    test_data_add("hello world", "Hello world!");
    test_data_add("", "");
})

TEST(creates, {
    const char *data   = test_data_get(char);
    size_t      length = strlen(data);

    String      string = string_from_data(data, length);

    test_assert(string.length == length);

    for (size_t i = 0; i < string.length; i++) {
        test_assert(string.data[i] == data[i]);
    }

    string_destroy(&string);
})
TEST_OPTIONS(creates, .dataProvider = stringDataProvider())

TEST(outlives_original_heap_data, {
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
TEST_OPTIONS(outlives_original_heap_data, .dataProvider = stringDataProvider())
