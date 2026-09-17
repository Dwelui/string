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
