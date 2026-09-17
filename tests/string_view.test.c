#include <dwelui/test.h>
#include <dwelui/string.h>
#include <stdio.h>
#include <string.h>
#include "data_providers.c"

TEST(from_string, {
    const char *data = test_data_get(char);

    String      string = string_from_cstr(data);
    StringView  view   = string_view_from_string(string);

    test_assert(view.length == strlen(data));

    for (size_t i = 0; i < view.length; i++) {
        test_assert(view.data[i] == data[i]);
    }

    string_destroy(&string);
})
TEST_OPTIONS(from_string, .dataProvider = cstrDataProvider())

TEST(from_cstr, {
    const char *data = test_data_get(char);

    StringView  view = string_view_from_cstr(data);

    test_assert(view.length == strlen(data));

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

TEST(equal, {
    const EqualData *data     = test_data_get(EqualData);
    const StringView a        = string_view_from_cstr(data->a);
    const StringView b        = string_view_from_cstr(data->b);
    const bool       expected = data->expected;

    test_assert(string_view_equal(a, b) == expected);
})
TEST_OPTIONS(equal, .dataProvider = equalDataProvider())
