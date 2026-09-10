#ifndef DWELUI_STRING_H
#define DWELUI_STRING_H

#include <stddef.h>

/**
 * @brief Mutable string that owns its character buffer.
 *
 * @var String::data
 *      Owned character buffer. NULL when length is 0.
 *      The buffer is exactly `length` bytes long; it has no unused
 *      capacity beyond the string contents.
 *      Must be released with string_destroy().
 *
 * @var String::length
 *      Number of character bytes in `data`.
 */
typedef struct {
    char  *data;
    size_t length;
} String;

/**
 * @brief Immutable string view that does not own its character buffer.
 *
 * @var StringView::data
 *      Borrowed character buffer. NULL when length is 0.
 *      The buffer is not owned and must remain valid for the lifetime of the view.
 *
 * @var StringView::length
 *      Number of character bytes in the view, starting at `data`.
 */
typedef struct {
    char  *data;
    size_t length;
} StringView;

typedef struct {
    StringView *items;
    size_t      count;
} StringViewList;

/**
 * @brief Growable string that owns its character buffer.
 *
 * @var StringBuffer::data
 *      Owned character buffer, initialized with string_buffer_start().
 *      The buffer may have unused capacity beyond `length` to allow
 *      amortized growth by string_buffer_append_data() and other
 *      append functions.
 *      Must be released with string_buffer_destroy(), or reset for
 *      reuse with string_buffer_clean() without releasing its allocation.
 *
 * @var StringBuffer::length
 *      Number of character bytes currently stored in `data`.
 *
 * @var StringBuffer::capacity
 *      Number of character bytes allocated for `data`.
 */
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

StringView     string_view_from_string(String s);
StringView     string_view_from_data(const char *data, size_t length);
StringView     string_view_from_cstr(const char *data);
StringView     string_view_clone(StringView sv);
bool           string_view_equals(StringView a, StringView b);
bool           string_view_trim(StringView *sv);
StringViewList string_split(StringView haystack, StringView delimiter);
void           string_view_list_destroy(StringViewList *svl);

// StringBuffer --------------------------

StringBuffer string_buffer_start();
void         string_buffer_append_data(StringBuffer *sb, const char *data, size_t length);
void         string_buffer_clean(StringBuffer *sb);
void         string_buffer_destroy(StringBuffer *sb);

#endif // DWELUI_STRING_H
