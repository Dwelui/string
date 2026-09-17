#include <dwelui/string.h>
#include <string.h>

StringView string_view_from_string(String s) {
    return (StringView){s.data, s.length};
}

StringView string_view_from_cstr(const char *data) {
    size_t     length = nullptr != data ? strlen(data) : 0;

    StringView view = {.data = (char *)data, length};

    return view;
}

bool string_view_equal(StringView a, StringView b) {
    if (a.length != b.length) {
        return false;
    }

    for (size_t i = 0; i < a.length; i++) {
        if (a.data[i] != b.data[i]) {
            return false;
        }
    }

    return true;
}
