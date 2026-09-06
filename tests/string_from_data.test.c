#include <dwelui/string.h>
#include <dwelui/test.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

TEST(creates_valid_string, {
    const char* data = "Hello world!";
    size_t length = strlen(data);

    String string = string_from_data(data, length);

    // validate .data field by checking against "data" variable
    // validate .length field by checking against "length" variable
    // validate .capacity field by checking that it's equal of higher than ".length" field
})

TEST(string_outlives_original_stack_data, {
    char* data = "Hello world!";
    size_t length = strlen(data);

    String string = string_from_data(data, length);

    data = nullptr;

    // validate .data field by checking against "data" variable
    // validate .length field by checking against "length" variable
    // validate .capacity field by checking that it's equal of higher than ".length" field
})

TEST(string_outlives_original_heap_data, {
    const char* data = "Hello world!";
    size_t length = strlen(data);

    char* dataHeap = malloc(sizeof(char) * length + 1);
    memcpy(dataHeap, data, length);
    dataHeap[length] = '\0';

    String string = string_from_data(dataHeap, length);

    free(dataHeap);

    // validate .data field by checking against "data" variable
    // validate .length field by checking against "length" variable
    // validate .capacity field by checking that it's equal of higher than ".length" field
})
