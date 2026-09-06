#include <dwelui/string.h>

// TODO: Is it worth not using standart librararies? What are the trade offs?
// Avoid using std libs like "string" and others...

String string_from_data(const char *data, size_t length) {
    return (String){.data = nullptr, .length = 0};
}
