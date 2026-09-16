#include <dwelui/string.h>
#include <dwelui/test.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

TEST_DATA_PROVIDER(stringDataProvider, {
    test_data_add("Hello world!", "Hello world!");
    test_data_add("", "");
})

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
TEST_OPTIONS(from_data, .dataProvider = stringDataProvider())

TEST(from_cstr, {
    const char *data = test_data_get(char);

    String      string = string_from_cstr(data);

    test_assert(string.length == strlen(data));

    for (size_t i = 0; i < string.length; i++) {
        test_assert(string.data[i] == data[i]);
    }

    string_destroy(&string);
})
TEST_OPTIONS(from_cstr, .dataProvider = stringDataProvider())

// TEST(clone, {
//     const char *data   = test_data_get(char);
//     size_t      length = strlen(data);
//
//     String      string = string_from_data(data, length);
//     String      clone  = string_clone(string);
//
//     test_assert(string.length == length);
//
//     for (size_t i = 0; i < string.length; i++) {
//         test_assert(string.data[i] == data[i]);
//     }
//
//     string_destroy(&string);
// })

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
TEST_OPTIONS(from_data_outlives_original_heap_data, .dataProvider = stringDataProvider())
