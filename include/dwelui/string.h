#ifndef DWELUI_STRING_H
#define DWELUI_STRING_H

#include <stddef.h>

typedef struct {
    char  *data;
    size_t length;
} String;

typedef struct {
    char  *data;
    size_t length;
} StringView;

typedef struct {
    StringView *items;
    size_t      count;
} StringViewList;

typedef struct {
    char  *data;
    size_t length;
    size_t capacity;
} StringBuffer;

// String --------------------------------

String         string_from_buffer(StringBuffer sb);
String         string_from_view(StringView sv);
String         string_from_data(const char *data, size_t length);
String         string_from_cstr(const char *cstr);
String         string_clone(String s);
bool           string_append(String *s, StringView part);
void           string_destroy(String *s);
StringViewList string_split_string(String *haystack, StringView delimiter);
bool           string_equals(String a, String b);
bool           string_trim(String *s);

// StringView ----------------------------

StringView     string_view_from_buffer(StringBuffer sb);
StringView     string_view_from_string(String s);
StringView     string_view_from_data(const char *data, size_t length);
StringView     string_view_from_cstr(const char *data);
StringView     string_view_clone(StringView sv);
bool           string_view_equals(StringView a, StringView b);
bool           string_view_trim(StringView *sv);
StringViewList string_split(StringView haystack, StringView delimiter);
void           string_view_list_destroy(StringViewList *svl);

// StringBuffer --------------------------

StringBuffer string_buffer_start(); // allocate a smart amount from the get go.
StringBuffer string_buffer_append_data(StringBuffer *sb, const char *part, size_t length);
StringBuffer string_buffer_clean(
    StringBuffer
        *sb); // removes data, leaves allocated space for repeated buildings of similar data.
void string_buffer_destroy(StringBuffer *sb);

#endif // DWELUI_STRING_H
