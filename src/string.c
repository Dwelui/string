#include <dwelui/string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

String string_from_buffer(StringBuffer sb) {
    String string = {.data = nullptr, .length = sb.length};

    string.data = malloc(sizeof(char) * string.length);
    if (nullptr == string.data) {
        perror("malloc");
    }

    memcpy(string.data, sb.data, string.length);

    return string;
}

String string_from_data(const char *data, size_t length) {
    String string = {.data = nullptr, length};

    if (0 == string.length) {
        return string;
    }

    string.data = malloc(sizeof(char) * string.length);
    memcpy(string.data, data, string.length);

    return string;
}

String string_from_cstr(const char *cstr) {
    return string_from_data(cstr, strlen(cstr));
}

String string_clone(String s) {
    return string_from_data(s.data, s.length);
}

void string_destroy(String *s) {
    if (0 == s->length) {
        return;
    }

    free(s->data);
    s->data   = nullptr;
    s->length = 0;
}

void string_replace(String *s, StringView search, StringView replace, size_t *count) {
    (void) s, (void)search, (void)replace, (void)count;
}

bool string_equal(String a, String b) {
    return string_view_equal(string_view_from_string(a), string_view_from_string(b));
}
