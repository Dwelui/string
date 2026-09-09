#include <dwelui/test.h>
#include <dwelui/string.h>

TEST(start_and_destroy, {
    StringBuffer buffer = string_buffer_start();

    string_buffer_destroy(&buffer);
})
