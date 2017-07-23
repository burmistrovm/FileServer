#include "mime.h"

struct mapping
{
    const char *extension;
    const char *mime_type;
} mappings[] = {{"html", "text/html"},
                {"css",  "text/css"},
                {"js",   "text/javascript"},
                {"jpg",  "image/jpeg"},
                {"jpeg", "image/jpeg"},
                {"png",  "image/png"},
                {"gif",  "image/gif"},
                {"swf",  "application/x-shockwave-flash"},
                {0,      0}};

std::string extensionToType(const std::string &extension)
{
    for (mapping m: mappings) {
        if (m.extension == extension) {
            return m.mime_type;
        }
    }
    return "text/plain";
}
