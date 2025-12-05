/*!
 * @file universal_radix_sort.hpp
 * @brief C++ implementation of universal radix sort with class-based design
 *
 * This header provides a template class for universal radix sort implementation
 * supporting multiple data types with configurable sort direction and order.
 */

#ifndef UNIVERSAL_RADIX_SORT_HPP
#define UNIVERSAL_RADIX_SORT_HPP

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace radix {

/*!
 * @brief Universal Radix Sort implementation with class-based design
 *
 * This class template provides a flexible and type-safe implementation of
 * radix sort for various data types including signed integers, floating-point
 * numbers, and strings.
 *
 * @tparam T The data type to be sorted
 *
 * @example
 * // Sort integers in ascending order
 * UniversalRadixSort<int>
 * sorter(UniversalRadixSort<int>::DataType::SIGNED_INTEGER); std::vector<int>
 * data = {170, -45, 75, -9000, 802, -24, 2, 66, 0, -1}; sorter.sort(data);
 */
template <typename T> class UniversalRadixSort {
public:
  /*!
   * @brief Enumeration of supported data types
   */
  enum class DataType {
    UNSIGNED_OR_STRING = 0, ///< Unsigned integers or fixed-length strings
    SIGNED_INTEGER = 1,     ///< Signed integers
    IEEE754_FLOAT = 2,      ///< IEEE 754 single-precision floating point
    IEEE754_DOUBLE = 3      ///< IEEE 754 double-precision floating point
  };

  /*!
   * @brief Enumeration of sort direction
   */
  enum class Direction {
    ASCENDING = true,  ///< Sort from smallest to largest
    DESCENDING = false ///< Sort from largest to smallest
  };

  /*!
   * @brief Enumeration of byte processing order
   */
  enum class ProcessingOrder {
    LSB_FIRST = true, ///< Process from least significant byte to most
    MSB_FIRST = false ///< Process from most significant byte to least
  };

  /*!
   * @brief Enumeration of error codes
   */
  enum class ErrorCode {
    SUCCESS = 0,       ///< Operation completed successfully
    NULL_POINTER = -1, ///< Null pointer passed as argument
    INVALID_ELEMENT_SIZE =
        -2, ///< Element size doesn't match data type requirements
    MEMORY_ALLOCATION = -3,    ///< Failed to allocate required memory
    UNSUPPORTED_DATA_TYPE = -4 ///< Data type is not supported
  };

  /*!
   * @brief Exception class for radix sort errors
   */
  class RadixException : public std::runtime_error {
  public:
    explicit RadixException(ErrorCode code, const std::string &message)
        : std::runtime_error(message), code_(code) {}

    ErrorCode code() const { return code_; }

  private:
    ErrorCode code_;
  };

  /*!
   * @brief Constructor with configuration parameters
   *
   * @param dataType Type of data to be sorted (default: UNSIGNED_OR_STRING)
   * @param order Byte processing order (default: LSB_FIRST)
   * @param direction Sort direction (default: ASCENDING)
   */
  explicit UniversalRadixSort(
      DataType data_type = DataType::UNSIGNED_OR_STRING,
      ProcessingOrder order = ProcessingOrder::LSB_FIRST,
      Direction direction = Direction::ASCENDING)
      : data_type_(data_type), processing_order_(order), direction_(direction) {
  }

  /*!
   * @brief Sort an array of elements
   *
   * @param array Pointer to the array to be sorted
   * @param n Number of elements in the array
   * @throw RadixException if sorting fails
   */
  void sort(T *array, const size_t n) {
    if (array == nullptr) {
      throw RadixException(ErrorCode::NULL_POINTER, "Array pointer is null");
    }

    if (n <= 1) {
      return; // Nothing to sort
    }

    // Validate data type and element size compatibility
    validate_data_type(sizeof(T));

    bool need_post_processing = false;

    // Pre-processing based on data type
    need_post_processing = pre_process_data(array, n);

    // Special handling for string sorting
    if (data_type_ == DataType::UNSIGNED_OR_STRING &&
        processing_order_ == ProcessingOrder::MSB_FIRST) {
      radix_sort_strings(reinterpret_cast<char *>(array), n, sizeof(T));
      return;
    }

    // Allocate temporary buffer for counting sort
    std::unique_ptr<T[]> temp_array(new T[n]);

    // Main sorting loop
    if (processing_order_ == ProcessingOrder::LSB_FIRST) {
      // LSB-first (right to left): optimal for numeric types
      for (size_t byte_index = 0; byte_index < sizeof(T); ++byte_index) {
        counting_sort_byte(array, n, byte_index, temp_array.get());
      }
    } else {
      // MSB-first (left to right): optimal for fixed-length strings
      for (size_t byte_index = 0; byte_index < sizeof(T); ++byte_index) {
        counting_sort_byte(array, n, byte_index, temp_array.get());
      }
    }

    // Post-processing to restore original representation
    if (need_post_processing) {
      post_process_data(array, n);
    }

    // Apply reverse for descending order (for non-string types)
    if (direction_ == Direction::DESCENDING &&
        data_type_ != DataType::UNSIGNED_OR_STRING) {
      reverse_array(array, n);
    }
  }

  /*!
   * @brief Sort a vector of elements
   *
   * @param vec Vector to be sorted
   * @throw RadixException if sorting fails
   */
  void sort(std::vector<T> &vec) {
    if (!vec.empty()) {
      sort(vec.data(), vec.size());
    }
  }

  /*!
   * @brief Validate data type compatibility with element size
   *
   * @param elementSize Size of each element in bytes
   * @throw RadixException if validation fails
   */
  void validate_data_type(const size_t element_size) const {
    switch (data_type_) {
    case DataType::IEEE754_FLOAT:
      if (element_size != sizeof(float)) {
        throw RadixException(
            ErrorCode::INVALID_ELEMENT_SIZE,
            "Element size must match sizeof(float) for IEEE754_FLOAT");
      }
      break;
    case DataType::IEEE754_DOUBLE:
      if (element_size != sizeof(double)) {
        throw RadixException(
            ErrorCode::INVALID_ELEMENT_SIZE,
            "Element size must match sizeof(double) for IEEE754_DOUBLE");
      }
      break;
    case DataType::SIGNED_INTEGER:
    case DataType::UNSIGNED_OR_STRING:
      // No specific size requirements for these types
      break;
    default:
      throw RadixException(ErrorCode::UNSUPPORTED_DATA_TYPE,
                           "Unsupported data type");
    }
  }

  /*!
   * @brief Utility function to print integer array
   */
  static void print_array(const std::vector<int> &arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
      std::cout << arr[i];
      if (i < arr.size() - 1)
        std::cout << " ";
    }
    std::cout << std::endl;
  }

  /*!
   * @brief Utility function to print long array
   */
  static void print_array(const std::vector<long> &arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
      std::cout << arr[i];
      if (i < arr.size() - 1)
        std::cout << " ";
    }
    std::cout << std::endl;
  }

  /*!
   * @brief Utility function to print float array
   */
  static void print_array(const std::vector<float> &arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
      std::cout << std::fixed << std::setprecision(3) << arr[i];
      if (i < arr.size() - 1)
        std::cout << " ";
    }
    std::cout << std::endl;
  }

  /*!
   * @brief Utility function to print double array
   */
  static void print_array(const std::vector<double> &arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
      std::cout << std::fixed << std::setprecision(6) << arr[i];
      if (i < arr.size() - 1)
        std::cout << " ";
    }
    std::cout << std::endl;
  }

  /*!
   * @brief Utility function to print string array
   */
  static void print_array(const std::vector<std::string> &arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
      std::cout << "'" << arr[i] << "'";
      if (i < arr.size() - 1)
        std::cout << " ";
    }
    std::cout << std::endl;
  }

private:
  DataType data_type_;               ///< Type of data being sorted
  ProcessingOrder processing_order_; ///< Byte processing order
  Direction direction_;              ///< Sort direction

  /*!
   * @brief Pre-process data based on data type
   *
   * @param array Pointer to the array to be processed
   * @param n Number of elements
   * @return true if post-processing is needed
   */
  bool pre_process_data(T *array, const size_t n) {
    switch (data_type_) {
    case DataType::IEEE754_FLOAT:
      float_pre_post_processing(reinterpret_cast<float *>(array), n, true);
      return true;
    case DataType::IEEE754_DOUBLE:
      double_pre_post_processing(reinterpret_cast<double *>(array), n, true);
      return true;
    case DataType::SIGNED_INTEGER:
      flip_msb_for_signed_types(array, n);
      return true;
    default:
      return false;
    }
  }

  /*!
   * @brief Post-process data to restore original representation
   *
   * @param array Pointer to the array to be processed
   * @param n Number of elements
   */
  void post_process_data(T *array, const size_t n) {
    switch (data_type_) {
    case DataType::IEEE754_FLOAT:
      float_pre_post_processing(reinterpret_cast<float *>(array), n, false);
      break;
    case DataType::IEEE754_DOUBLE:
      double_pre_post_processing(reinterpret_cast<double *>(array), n, false);
      break;
    case DataType::SIGNED_INTEGER:
      flip_msb_for_signed_types(array, n);
      break;
    default:
      break;
    }
  }

  /*!
   * @brief Flip MSB for signed integer types
   *
   * @param array Pointer to the array of signed integers
   * @param n Number of elements
   */
  void flip_msb_for_signed_types(T *array, const size_t n) {
    unsigned char *bytes = reinterpret_cast<unsigned char *>(array);
    const unsigned char SIGN_BIT_MASK = 0x80; // 10000000 in binary

    for (size_t i = 0; i < n; ++i) {
      size_t mbs_index = i * sizeof(T) + (sizeof(T) - 1);
      bytes[mbs_index] ^= SIGN_BIT_MASK;
    }
  }

  /*!
   * @brief Pre/post processing for IEEE 754 float values
   *
   * @param array Pointer to the array of float values
   * @param n Number of elements
   * @param isPreprocess true for pre-processing, false for post-processing
   */
  void float_pre_post_processing(float *array, const size_t n,
                                 const bool is_pre_process) {
    union FloatConverter {
      float f;
      uint32_t u32;
    };

    const uint32_t SIGN_BIT_MASK = 0x80000000U;

    for (size_t i = 0; i < n; ++i) {
      FloatConverter converter;
      converter.f = array[i];

      if (is_pre_process) {
        // Convert to sortable representation
        if (converter.u32 & SIGN_BIT_MASK) {
          converter.u32 = ~converter.u32; // Negative values: flip all bits
        } else {
          converter.u32 ^= SIGN_BIT_MASK; // Positive values: flip sign bit only
        }
      } else {
        // Restore original representation
        if (converter.u32 & SIGN_BIT_MASK) {
          converter.u32 ^= SIGN_BIT_MASK; // Was positive: flip sign bit back
        } else {
          converter.u32 = ~converter.u32; // Was negative: flip all bits back
        }
      }

      array[i] = converter.f;
    }
  }

  /*!
   * @brief Pre/post processing for IEEE 754 double values
   *
   * @param array Pointer to the array of double values
   * @param n Number of elements
   * @param isPreprocess true for pre-processing, false for post-processing
   */
  void double_pre_post_processing(double *array, const size_t n,
                                  const bool is_pre_process) {
    union DoubleConverter {
      double d;
      uint64_t u64;
    };

    const uint64_t SIGN_BIT_MASK = 0x8000000000000000ULL;

    for (size_t i = 0; i < n; ++i) {
      DoubleConverter converter;
      converter.d = array[i];

      if (is_pre_process) {
        // Convert to sortable representation
        if (converter.u64 & SIGN_BIT_MASK) {
          converter.u64 = ~converter.u64; // Negative values: flip all bits
        } else {
          converter.u64 ^= SIGN_BIT_MASK; // Positive values: flip sign bit only
        }
      } else {
        // Restore original representation
        if (converter.u64 & SIGN_BIT_MASK) {
          converter.u64 ^= SIGN_BIT_MASK; // Was positive: flip sign bit back
        } else {
          converter.u64 = ~converter.u64; // Was negative: flip all bits back
        }
      }

      array[i] = converter.d;
    }
  }

  /*!
   * @brief Counting sort implementation for a single byte position
   *
   * @param array Pointer to the array to be sorted
   * @param n Number of elements
   * @param byteIndex Index of the byte to sort by
   * @param tempArray Temporary array for sorting
   */
  void counting_sort_byte(T *array, const size_t n, const size_t byte_index,
                          T *temp_array) {
    constexpr size_t RADIX_BASE = 256;
    size_t count[RADIX_BASE] = {0};
    unsigned char *bytes = reinterpret_cast<unsigned char *>(array);

    // Count occurrences of each byte value
    for (size_t i = 0; i < n; ++i) {
      unsigned char byte_value = bytes[i * sizeof(T) + byte_index];
      count[byte_value]++;
    }

    // Convert counts to cumulative positions (prefix sum)
    for (size_t i = 1; i < RADIX_BASE; ++i) {
      count[i] += count[i - 1];
    }

    // Build output array in reverse order for stability
    unsigned char *temp_bytes = reinterpret_cast<unsigned char *>(temp_array);
    for (size_t i = n; --i > 0;) {
      unsigned char byte_value = bytes[i * sizeof(T) + byte_index];
      size_t outputPos = --count[byte_value];
      std::memcpy(&temp_bytes[outputPos * sizeof(T)], &bytes[i * sizeof(T)],
                  sizeof(T));
    }

    // Copy sorted elements back to original array
    std::memcpy(array, temp_array, n * sizeof(T));
  }

  /*!
   * @brief Specialized string sorting function for lexicographical ordering
   *
   * @param array Pointer to the array of fixed-length strings
   * @param n Number of elements
   * @param elementSize Size of each string element in bytes
   */
  void radix_sort_strings(char *array, const size_t n,
                          const size_t element_size) {
    // Use std::sort with custom comparator for proper string sorting
    auto comparator = [element_size](const char *a, const char *b) {
      return std::strncmp(a, b, element_size) < 0;
    };

    // Create array of pointers to sort
    std::vector<char *> pointers;
    pointers.reserve(n);
    for (size_t i = 0; i < n; ++i) {
      pointers.push_back(&array[i * element_size]);
    }

    // Sort pointers based on string content
    if (direction_ == Direction::ASCENDING) {
      std::sort(pointers.begin(), pointers.end(), comparator);
    } else {
      std::sort(pointers.begin(), pointers.end(),
                [comparator](const char *a, const char *b) {
                  return !comparator(a, b) && a != b;
                });
    }

    // Create temporary buffer to hold sorted data
    std::vector<char> temp_buffer(n * element_size);
    for (size_t i = 0; i < n; ++i) {
      std::memcpy(&temp_buffer[i * element_size], pointers[i], element_size);
    }

    // Copy back to original array
    std::memcpy(array, temp_buffer.data(), n * element_size);
  }

  /*!
   * @brief Reverse an array to change sort order
   *
   * @param array Pointer to the array to be reversed
   * @param n Number of elements
   */
  void reverse_array(T *array, const size_t n) {
    for (size_t i = 0; i < n / 2; ++i) {
      std::swap(array[i], array[n - 1 - i]);
    }
  }
};

} // namespace radix

#endif // UNIVERSAL_RADIX_SORT_HPP
