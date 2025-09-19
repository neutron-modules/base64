# Base64 Box Module for Neutron

A high-performance Base64 encoding and decoding module for the Neutron programming language.

## Overview

This module provides efficient Base64 functionality for Neutron programs through a combination of:
- **Native C++ implementation** for maximum performance
- **Neutron integration** for seamless usage
- **Standard compliance** with RFC 4648 Base64 encoding

## Features

- Fast Base64 encoding and decoding
- Support for all ASCII characters
- Proper padding handling
- Round-trip encoding integrity
- Error-resistant implementation

## Installation

The module is built using Neutron's Box Module system:

```bash
./neutron --build-box base64
```

This creates `box/base64/base64.so` which is automatically loaded when the module is imported.

## Usage

### Basic Usage

```neutron
use base64;

var original = "Hello, World!";
var encoded = base64.encode(original);
var decoded = base64.decode(encoded);

say("Original: " + original);
say("Encoded: " + encoded);
say("Decoded: " + decoded);
```

### Functions

#### `base64.encode(string)`
Encodes a string to Base64 format.

**Parameters:**
- `string` - The text to encode

**Returns:**
- Base64-encoded string

**Example:**
```neutron
var encoded = base64.encode("Neutron");
// Returns: "TmV1dHJvbg=="
```

#### `base64.decode(string)`
Decodes a Base64 string back to original text.

**Parameters:**
- `string` - The Base64 string to decode

**Returns:**
- Decoded text string

**Example:**
```neutron
var decoded = base64.decode("TmV1dHJvbg==");
// Returns: "Neutron"
```

### Practical Examples

#### Secure Token Generation
```neutron
use base64;

// Create a secure token from user data
var user_data = "user_id=123&role=admin&expires=2023-12-31";
var token = base64.encode(user_data);
say("Secure Token: " + token);

// Later, decode the token to verify user data
var verified_data = base64.decode(token);
say("Verified Data: " + verified_data);
```

#### Data Transmission
```neutron
use base64;

// Prepare data for transmission
var message = "This is confidential information!";
var safe_message = base64.encode(message);
send_to_api(safe_message);  // Transmit encoded data

// Receive and decode data
var received_data = receive_from_api();
var original_message = base64.decode(received_data);
```

## Technical Details

### Implementation

The module uses a hybrid approach:
- **Core algorithms** implemented in optimized C++
- **Module interface** integrated with Neutron's VM
- **Function exposure** through standard module registration

### Performance

- Native C++ implementation ensures maximum speed
- Minimal memory allocation overhead
- Efficient string handling routines

### Standards Compliance

- Fully compliant with RFC 4648 Base64 encoding
- Proper MIME Base64 alphabet usage
- Correct padding with '=' characters
- Standard decoding behavior

## Testing

The module has been tested with:
- Standard text strings
- Empty strings
- Single characters
- Special characters and symbols
- Numerical data
- Mixed content strings
- Unicode characters (where supported)

## Limitations

- Currently limited to ASCII character support
- Function definitions in Neutron module files (.nt) have parser limitations in current Neutron version

## Future Enhancements

Planned improvements include:
- URL-safe Base64 variant support
- Streaming encoding/decoding for large data
- Additional validation functions
- Enhanced error reporting

## Directory Structure

```
box/base64/
├── base64.cpp      # Core encoding/decoding implementation
├── base64.h        # Headers and declarations
├── native.cpp      # Neutron module interface
├── base64.nt       # Neutron utilities (loader)
├── README.md       # This documentation
```

## Build Process

To build the module from source:

```bash
# Navigate to Neutron root directory
cd /path/to/neutron

# Build the Base64 module
./neutron --build-box base64
```

This command compiles the C++ source files and creates a shared library that is automatically recognized by the Neutron runtime.

## Contributing

Contributions are welcome! Please feel free to submit issues or pull requests for:
- Bug fixes
- Performance improvements
- New features
- Documentation enhancements

## License

This module is part of the Neutron project and is distributed under the same license terms.

## Author

Created as part of the Neutron programming language ecosystem by Yasakei
