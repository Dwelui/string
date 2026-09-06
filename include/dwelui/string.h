#ifndef DWELUI_STRING_H
#define DWELUI_STRING_H

#include <stddef.h>

// TODO:
// - [ ] document in header file, about ownership and other stuff...
// - [ ] How much space does this struct take up, and how it matters.
// - [ ] Is it possible to optimize the space?
struct String {
    char  *data;
    size_t length;
    size_t capacity;
};

typedef struct String String;

String                string_from_data(const char *data, size_t length);

#endif // DWELUI_STRING_H
