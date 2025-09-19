#include "base64.h"
#include "vm.h"
#include <string>
#include <vector>
#include <stdexcept>

// Native function to encode a string to base64
neutron::Value base64_encode(std::vector<neutron::Value> arguments) {
    if (arguments.size() != 1) {
        throw std::runtime_error("Expected 1 argument for base64.encode().");
    }
    if (arguments[0].type != neutron::ValueType::STRING) {
        throw std::runtime_error("Argument for base64.encode() must be a string.");
    }
    std::string input = std::get<std::string>(arguments[0].as);
    std::string encoded = base64::encode(input);
    return neutron::Value(encoded);
}

// Native function to decode a base64 string
neutron::Value base64_decode(std::vector<neutron::Value> arguments) {
    if (arguments.size() != 1) {
        throw std::runtime_error("Expected 1 argument for base64.decode().");
    }
    if (arguments[0].type != neutron::ValueType::STRING) {
        throw std::runtime_error("Argument for base64.decode() must be a string.");
    }
    std::string input = std::get<std::string>(arguments[0].as);
    std::string decoded = base64::decode(input);
    return neutron::Value(decoded);
}

// Module initialization function
extern "C" void neutron_module_init(neutron::VM* vm) {
    // Create a module environment
    auto env = std::make_shared<neutron::Environment>();
    
    // Register base64 encode function
    env->define("encode", neutron::Value(new neutron::NativeFn(base64_encode, 1)));
    
    // Register base64 decode function
    env->define("decode", neutron::Value(new neutron::NativeFn(base64_decode, 1)));
    
    // Create the module and register it in the VM's globals
    auto module = new neutron::Module("base64", env);
    vm->define_module("base64", module);
}
