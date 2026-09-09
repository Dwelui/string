#include <assert.h>
#include <dwelui/test.h>
#include <dwelui/string.h>
#include <string.h>

TEST(start_and_destroy, {
    StringBuffer buffer = string_buffer_start();

    string_buffer_destroy(&buffer);
})

TEST(after_append_data_count_field_is_correct, {
    StringBuffer buffer = string_buffer_start();
    string_buffer_append_data(&buffer, "Hello World!", strlen("Hello World!"));

    test_assert(buffer.length == strlen("Hello World!"));

    string_buffer_destroy(&buffer);
})
