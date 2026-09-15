#include <dwelui/test.h>
#include <dwelui/string.h>
#include <string.h>

TEST_DATA_PROVIDER(cstrDataProvider, {
    test_data_add("Hello world!", "Hello world!");
    test_data_add("", "");
})

TEST(from_cstr, {
    const char *data   = test_data_get(char);
    size_t      length = strlen(data);

    StringView  view = string_view_from_cstr(data);

    test_assert(view.length == length);

    for (size_t i = 0; i < view.length; i++) {
        test_assert(view.data[i] == data[i]);
    }
})
TEST_OPTIONS(from_cstr, .dataProvider = cstrDataProvider())

TEST(from_cstr_with_nullptr, {
    const char *data = nullptr;

    StringView  view = string_view_from_cstr(data);

    test_assert(view.length == 0);

    for (size_t i = 0; i < view.length; i++) {
        test_assert(view.data[i] == data[i]);
    }
})
