#include <dwelui/test.h>
#include <dwelui/string.h>
#include <stdio.h>
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

typedef struct {
    const char *a;
    const char *b;
    const bool  expected;
} EqualData;
TEST_DATA_PROVIDER(equalDataProvider, {
    static const EqualData item1 = {"abc", "abc", true};
    test_data_add("abc abc", item1);

    static const EqualData item2 = {"abc", "cba", false};
    test_data_add("abc cba", item2);

    static const EqualData item3 = {"", "", true};
    test_data_add(" ", item3);
})

TEST(equal, {
    const EqualData *data     = test_data_get(EqualData);
    const StringView a        = string_view_from_cstr(data->a);
    const StringView b        = string_view_from_cstr(data->b);
    const bool       expected = data->expected;

    test_assert(string_view_equal(a, b) == expected);
})
TEST_OPTIONS(equal, .dataProvider = equalDataProvider())
