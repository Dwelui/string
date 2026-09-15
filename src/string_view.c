#include <dwelui/string.h>
#include <string.h>

StringView string_view_from_cstr(const char *data) {
    size_t length = nullptr != data ? strlen(data) : 0;

    StringView view = {.data = (char *)data, length};

    return view;
}
