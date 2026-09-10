#include <assert.h>
#include <dwelui/test.h>
#include <dwelui/string.h>
#include <stdio.h>
#include <string.h>

TEST(start_and_destroy, {
    StringBuffer buffer = string_buffer_start();

    string_buffer_destroy(&buffer);
})

DATA_PROVIDER(stringBufferFixtureDataProvider, {
    test_data_add("lorem_64.txt", "tests/fixtures/lorem_64.txt");
    test_data_add("lorem_64_special.txt", "tests/fixtures/lorem_64_special.txt");
    test_data_add("lorem_1024.txt", "tests/fixtures/lorem_1024.txt");
})

TEST(after_append_data_count_is_correct, {
    FILE *fixtureFd = fopen(test_data_get(char), "r");
    if (nullptr == fixtureFd) {
        perror("fopen");
    }

    StringBuffer buffer = string_buffer_start();

    size_t       chuckSize = 12;
    char         data[chuckSize + 1];
    size_t       length      = 0;
    size_t       totalLength = 0;

    do {
        length = fread(data, 1, chuckSize, fixtureFd);
        totalLength += length;

        string_buffer_append_data(&buffer, data, length);
    } while (0 != length);

    test_assert(buffer.length == totalLength);

    string_buffer_destroy(&buffer);
})
TEST_OPTIONS(after_append_data_count_is_correct, .dataProvider = stringBufferFixtureDataProvider())

TEST(to_string_data_and_length_are_correct, {
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

    // test_assert for data is correct. Can read file in one go instead of building in chuncks
    test_assert(string.length == totalLength);

    // free buffer
    // free string
})
TEST_OPTIONS(to_string_data_and_length_are_correct, .dataProvider = stringBufferFixtureDataProvider())
