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

size_t string_replace(String *s, StringView search, StringView replace, size_t count) {
    StringBuffer buffer     = string_buffer_start();
    StringView   sView      = string_view_from_string(*s);
    size_t       foundCount = 0;
    for (size_t i = 0; i < s->length - search.length; i++) {
        // Don't search for more than it was requested
        if (foundCount == count) {
            break;
        }

        sView.data++;
        sView.length--;
        if (true == string_view_starts_with(sView, search)) {
            string_buffer_append_data(&buffer, sView.data, sView.length - search.length);
            string_buffer_append_data(&buffer, replace.data, replace.length);
            foundCount++;
        }
    }

    String result = string_from_buffer(buffer);
    string_destroy(s);
    s = &result;

    return foundCount;
}

bool string_equal(String a, String b) {
    return string_view_equal(string_view_from_string(a), string_view_from_string(b));
}
