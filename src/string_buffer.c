#include <dwelui/string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: Tweak this number after reading/researching virtual memory and segmentation
#define STRING_BUFFER_START_CAPACITY 64

StringBuffer string_buffer_start() {
    StringBuffer buffer = {
        .data     = nullptr,
        .length   = 0,
        .capacity = STRING_BUFFER_START_CAPACITY,
    };

    buffer.data = malloc(sizeof(char) * STRING_BUFFER_START_CAPACITY);
    if (nullptr == buffer.data) {
        perror("malloc");
    }

    return buffer;
}

void string_buffer_append_data(StringBuffer *sb, const char *data, size_t length) {
    if (sb->length + length > sb->capacity) {
        while (sb->capacity < sb->length + length) {
            sb->capacity *= 2;
        }

        sb->data = realloc(sb->data, sizeof(char) * sb->capacity);
        if (nullptr == sb->data) {
            perror("realloc");
        }
    }

    memcpy(sb->data + sb->length, data, length);
    sb->length += length;
}

void string_buffer_destroy(StringBuffer *sb) {
    free(sb->data);
    sb->length   = 0;
    sb->capacity = 0;
}
