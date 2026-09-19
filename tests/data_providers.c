#include <dwelui/test.h>

TEST_DATA_PROVIDER(stringBufferFixtureDataProvider, {
    test_data_add("lorem_64.txt", "tests/fixtures/lorem_64.txt");
    test_data_add("lorem_64_special.txt", "tests/fixtures/lorem_64_special.txt");
    test_data_add("lorem_1024.txt", "tests/fixtures/lorem_1024.txt");
})

TEST_DATA_PROVIDER(cstrDataProvider, {
    test_data_add("Hello world!", "Hello world!");
    test_data_add("", "");
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

typedef struct {
    const char *haystack;
    const char *needle;
    int32_t     position;
} PositionAtData;
TEST_DATA_PROVIDER(positionAtDataProvider, {
    static PositionAtData item1 = {"Hello world!", "Hello", 0};
    test_data_add("Hello world! <- Hello at 0", item1);

    static PositionAtData item2 = {"Hello world!", "world", 6};
    test_data_add("Hello world! <- world at 6", item2);

    static PositionAtData item3 = {"Hello world!", "!", 11};
    test_data_add("Hello world! <- ! at 11", item3);

    static PositionAtData item4 = {"Hello world!", "d!", 10};
    test_data_add("Hello world! <- d! at 10", item4);

    static PositionAtData item5 = {"Hello world!", "?", -1};
    test_data_add("Hello world! <- ? at -1", item5);

    static PositionAtData item6 = {"Hello world!", "", 0};
    test_data_add("Hello world! <- \'\' at 0", item6);

    static PositionAtData item7 = {"", "", 0};
    test_data_add("\'\' <- \'\' at 0", item7);

    static PositionAtData item8 = {"Hello", "world!", -1};
    test_data_add("Hello <- world! at -1", item8);

    static PositionAtData item9 = {"ghi", " def ", -1};
    test_data_add("ghi <- \' def \' at -1", item9);
})

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
