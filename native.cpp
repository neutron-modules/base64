#include <neutron.h>
#include <string>
#include <cstring>

// Include the base64 implementation directly to avoid linking issues
namespace base64 {
    static const std::string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    static inline bool is_base64(unsigned char c) {
        return (isalnum(c) || (c == '+') || (c == '/'));
    }

    std::string encode(const std::string& input) {
        std::string ret;
        int i = 0;
        int j = 0;
        unsigned char char_array_3[3];
        unsigned char char_array_4[4];
        size_t in_len = input.size();
        const char* bytes_to_encode = input.c_str();

        while (in_len--) {
            char_array_3[i++] = *(bytes_to_encode++);
            if (i == 3) {
                char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
                char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
                char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
                char_array_4[3] = char_array_3[2] & 0x3f;

                for (i = 0; (i < 4); i++)
                    ret += base64_chars[char_array_4[i]];
                i = 0;
            }
        }

        if (i) {
            for (j = i; j < 3; j++)
                char_array_3[j] = '\0';

            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (j = 0; (j < i + 1); j++)
                ret += base64_chars[char_array_4[j]];

            while ((i++ < 3))
                ret += '=';
        }

        return ret;
    }

    std::string decode(const std::string& encoded_string) {
        size_t in_len = encoded_string.size();
        int i = 0;
        int j = 0;
        int in_ = 0;
        unsigned char char_array_4[4], char_array_3[3];
        std::string ret;

        while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
            char_array_4[i++] = encoded_string[in_]; in_++;
            if (i == 4) {
                for (i = 0; i < 4; i++)
                    char_array_4[i] = base64_chars.find(char_array_4[i]);

                char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
                char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
                char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

                for (i = 0; (i < 3); i++)
                    ret += char_array_3[i];
                i = 0;
            }
        }

        if (i) {
            for (j = i; j < 4; j++)
                char_array_4[j] = 0;

            for (j = 0; j < 4; j++)
                char_array_4[j] = base64_chars.find(char_array_4[j]);

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
        }

        return ret;
    }
}

// Native function to encode a string to base64
NeutronValue* base64_encode(NeutronVM* vm, int argCount, NeutronValue** args) {
    if (argCount != 1) {
        // Return empty string on wrong arg count
        return neutron_new_string("", 0);
    }
    
    if (!neutron_is_string(args[0])) {
        // Return empty string on wrong type
        return neutron_new_string("", 0);
    }
    
    size_t length;
    const char* input = neutron_get_string(args[0], &length);
    std::string input_str(input, length);
    std::string encoded = base64::encode(input_str);
    return neutron_new_string(encoded.c_str(), encoded.length());
}

// Native function to decode a base64 string
NeutronValue* base64_decode(NeutronVM* vm, int argCount, NeutronValue** args) {
    if (argCount != 1) {
        // Return empty string on wrong arg count
        return neutron_new_string("", 0);
    }
    
    if (!neutron_is_string(args[0])) {
        // Return empty string on wrong type
        return neutron_new_string("", 0);
    }
    
    size_t length;
    const char* input = neutron_get_string(args[0], &length);
    std::string input_str(input, length);
    std::string decoded = base64::decode(input_str);
    return neutron_new_string(decoded.c_str(), decoded.length());
}

// Module initialization function
extern "C" void neutron_module_init(NeutronVM* vm) {
    // Define the functions in the module
    neutron_define_native(vm, "encode", base64_encode, 1);
    neutron_define_native(vm, "decode", base64_decode, 1);
}