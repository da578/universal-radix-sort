# Universal Radix Sort C++ Library

[![C++](https://img.shields.io/badge/C++-17/20-blue?logo=c%2B%2B)](https://isocpp.org/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)](https://github.com/yourusername/universal-radix-sort/actions)
[![Platform](https://img.shields.io/badge/platform-cross--platform-lightgrey)](https://en.wikipedia.org/wiki/Cross-platform)

A high-performance, type-safe implementation of universal radix sort in C++ with support for multiple data types and configurable sorting options.

## Features

- **Template-based design**: Type-safe implementation with compile-time checking
- **Multiple data types support**:
  - Signed integers (int, long, etc.)
  - IEEE 754 floating-point numbers (float, double)
  - Fixed-length strings
- **Configurable options**:
  - Ascending or descending order
  - LSB-first or MSB-first processing
  - Automatic pre/post processing for special data types
- **Exception safety**: Comprehensive error handling with meaningful exceptions
- **Modern C++**: Utilizes smart pointers, STL algorithms, and RAII principles
- **Zero external dependencies**: Only requires standard C++ libraries

## Installation

### Header-only Library

Simply copy the `universal_radix_sort.hpp` header file into your project's include directory:

```cpp
#include "universal_radix_sort.hpp"
```

### CMake Integration

Add this repository as a submodule:

```bash
git submodule add https://github.com/da578/universal-radix-sort.git
```

Then in your CMakeList.txt:

```cmake
add_subdirectory(universal-radix-sort)
target_link_libraries(your_target PRIVATE universal_radix_sort)
```

## Usage Example

### Sorting Signed Integers

```cpp
#include "universal_radix_sort.hpp"
#include <vector>

int main() {
    std::vector<int> numbers = {170, -45, 75, -9000, 802, -24, 2, 66, 0, -1};

    radix::UniversalRadixSort<int> sorter(
        radix::UniversalRadixSort<int>::DataType::SIGNED_INTEGER,
        radix::UniversalRadixSort<int>::ProcessingOrder::LSB_FIRST,
        radix::UniversalRadixSort<int>::Direction::ASCENDING
    );

    sorter.sort(numbers);

    // Print sorted array
    radix::UniversalRadixSort<int>::printArray(numbers);
    return 0;
}
```

### Sorting Floats Descending Order

```cpp
std::vector<float> floats = {3.14f, -1.25f, 0.5f, -99.9f, 2.0f, 0.0f, -0.001f, 100.0f};

radix::UniversalRadixSort<float> sorter(
    radix::UniversalRadixSort<float>::DataType::IEEE754_FLOAT,
    radix::UniversalRadixSort<float>::ProcessingOrder::LSB_FIRST,
    radix::UniversalRadixSort<float>::Direction::DESCENDING
);

sorter.sort(floats);
```

### Sorting Fixed-Length-Strings

```cpp
// Create fixed-length string buffer
const size_t MAX_LEN = 20; // Maximum string length including null terminator
const size_t N = 3;       // Number of strings
std::vector<char> buffer(N * MAX_LEN);

// Copy strings to buffer
std::vector<std::string> strings = {"banana", "apple", "cherry"};
for (size_t i = 0; i < N; ++i) {
    strncpy(&buffer[i * MAX_LEN], strings[i].c_str(), MAX_LEN);
    buffer[i * MAX_LEN + MAX_LEN - 1] = '\0'; // Ensure null termination
}

// Sort strings (MSB-first for lexicographical order)
radix::UniversalRadixSort<char> sorter(
    radix::UniversalRadixSort<char>::DataType::UNSIGNED_OR_STRING,
    radix::UniversalRadixSort<char>::ProcessingOrder::MSB_FIRST,
    radix::UniversalRadixSort<char>::Direction::ASCENDING
);

sorter.sort(buffer.data(), N);
```

## API Documentation

### Class Template: `UniversalRadixSort<T>`

**Nested Enumerations**

- `DataType`: Specifies the data type to be sorted
  - `UNSIGNED_OR_STRING`
  - `SIGNED_INTEGER`
  - `IEEE754_FLOAT`
  - `IEEE754_DOUBLE`
- `Direction`: Specifies sort direction
  - `ASCENDING`
  - `DESCENDING`
- `ProcessingOrder`: Specifies byte processing order
  - `LSB_FIRST` (recommended for numeric types)
  - `MSB_FIRST` (recommended for strings)
- `ErrorCode`: Error codes for exception handling
  - `SUCCESS`
  - `NULL_POINTER`
  - `INVALID_ELEMENT_SIZE`
  - `MEMORY_ALLOCATION`
  - `UNSUPPORTED_DATA_TYPE`

**Public Methods**

- `UniversalRadixSort(DataType, ProcessingOrder, Direction)`: Constructor with configuration
- `sort(T* array, const size_t n)`: Sort array of elements
- `sort(std::vector<T>& vec)`: Sort vector of elements
- `validate_data_type(size_t element_size)`: Validate data type compatibility
- `print_array()`: Static utility methods for printing different array types

**Exception Handling**

- `RadixException`: Exception class thrown on errors, containing error code and message

## performance
Universal radix sort achieves O(n·k) time complexity where k is the number of bytes per element, outperforming O(n log n) comparison sorts for large datasets with small key sizes.
| Data Type           | Elements | Time (ms) | Comparison with std::sort |
|---------------------|----------|-----------|---------------------------|
| int32_t             | 100,000  | 4.9       | 3.4x faster               |
| float               | 100,000  | 5.9       | 2.7x faster               |
| Fixed-length string | 100,000  | 29.9      | 7.0x faster               |

Performance measured on Intel i5-3320M @ 3,30GHz, results may vary

**License**
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
