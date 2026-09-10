#include <dwelui/string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

String string_from_buffer(StringBuffer sb) {
    String string = {
        .data = nullptr,
        .length = sb.length
    };

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

void string_destroy(String *s) {
    if (0 == s->length) {
        return;
    }

    free(s->data);
    s->data = nullptr;
    s->length = 0;
}
