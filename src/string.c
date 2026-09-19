#include <dwelui/string.h>
#include <stdint.h>
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
    StringView   sView   = string_view_from_string(*s);
    StringBuffer sBuffer = string_buffer_start();

    size_t       foundCount = 0;
    int32_t      jumpSteps  = string_view_position_at(sView, search);
    printf("jumpSteps: %d\n", jumpSteps);

    while (jumpSteps >= 0) {
        printf("Found search start: %d %c\n", sView.data[0], sView.data[0]);
        string_buffer_append_data(&sBuffer, sView.data, jumpSteps);
        string_buffer_append_data(&sBuffer, replace.data, replace.length);

        printf("Current sBuffer:");
        for (size_t i = 0; i < sBuffer.length; i++) {
            printf("%c", sBuffer.data[i]);
        }
        printf("\n");

        sView.data += jumpSteps + search.length;
        sView.length -= jumpSteps + search.length;
        printf("Next sView start: %d %c\n", sView.data[0], sView.data[0]);

        printf("sView length: %zu search length: %zu\n", sView.length, search.length);
        jumpSteps = string_view_position_at(sView, search);
        printf("Next jumpSteps: %d\n", jumpSteps);
        if (jumpSteps == -1) {
            string_buffer_append_data(&sBuffer, sView.data, sView.length);
        }

        foundCount++;
        if (foundCount == count) {
            break;
        }


        printf("\n");
    }

    printf("sBuffer:");
    for (size_t i = 0; i < sBuffer.length; i++) {
        printf("%c", sBuffer.data[i]);
    }
    printf("\n");

    String sReplaced = string_from_buffer(sBuffer);
    string_buffer_destroy(&sBuffer);
    string_destroy(s);
    s->data   = sReplaced.data;
    s->length = sReplaced.length;

    return foundCount;
}

bool string_equal(String a, String b) {
    return string_view_equal(string_view_from_string(a), string_view_from_string(b));
}
