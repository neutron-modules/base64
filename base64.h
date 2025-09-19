#ifndef BASE64_H
#define BASE64_H

#include <string>

namespace base64 {
    std::string encode(const std::string& input);
    std::string decode(const std::string& input);
}

#endif // BASE64_H
