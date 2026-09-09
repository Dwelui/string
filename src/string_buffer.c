#include <dwelui/string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: Tweak this number after reading/researching virtual memory and segmentation
#define STRING_BUFFER_START_CAPACITY 64

StringBuffer string_buffer_start() {
    StringBuffer buffer = {
        .data     = malloc(sizeof(char) * STRING_BUFFER_START_CAPACITY),
        .length   = 0,
        .capacity = STRING_BUFFER_START_CAPACITY,
    };

    return buffer;
}

void string_buffer_append_data(StringBuffer *sb, const char *data, size_t length) {
    if (sb->length + length > sb->capacity) {
        // realloc for more capacity
    }

    memcpy(sb->data + sb->length, data, length);
    sb->length += length;
}

void string_buffer_destroy(StringBuffer *sb) {
    free(sb->data);
    sb->length   = 0;
    sb->capacity = 0;
}
