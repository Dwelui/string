#ifndef DWELUI_STRING_H
#define DWELUI_STRING_H

#include <stddef.h>

struct String {
    char  *data;
    size_t length;
};

typedef struct String String;

String                string_from_data(const char *data, size_t length);

#endif // DWELUI_STRING_H
