/*!
 * @file main.cpp
 * @brief Test driver for universal radix sort implementation with comprehensive
 * tests and performance measurement
 */

#include "universal_radix_sort.hpp"
#include <chrono>
#include <cstdlib>
#include <functional>
#include <iomanip>
#include <random>
#include <string>
#include <vector>

using namespace radix;
using namespace std;

size_t get_max_string_length(const vector<string> &arr);
void test_signed_integers();
void test_floats();
void test_doubles();
void test_strings();
void test_strings_descending();
void test_edge_cases();
void measure_performance();

int main() {
  cout << "=== UNIVERSAL RADIX SORT TEST SUITE IN C++ ===" << endl;

  test_signed_integers();
  cout << "\n------------------------------------------------" << endl;

  test_floats();
  cout << "\n------------------------------------------------" << endl;

  test_doubles();
  cout << "\n------------------------------------------------" << endl;

  test_strings();
  cout << "\n------------------------------------------------" << endl;

  test_strings_descending();
  cout << "\n------------------------------------------------" << endl;

  test_edge_cases();
  cout << "\n------------------------------------------------" << endl;

  measure_performance();
  cout << "\n------------------------------------------------" << endl;

  cout << "\n=== ALL TESTS COMPLETED ===" << endl;
  return 0;
}

/*!
 * @brief Helper function to find maximum string length in an array
 */
size_t get_max_string_length(const vector<string> &arr) {
  size_t max_length = 0;
  for (const string &str : arr) {
    if (str.length() > max_length) {
      max_length = str.length();
    }
  }
  return max_length;
}

void test_signed_integers() {
  cout << "\n--- TEST CASE 1: SIGNED LONG INTEGERS (ASCENDING) ---" << endl;
  vector<long> array = {170, -45, 75, -9000, 802, -24, 2, 66, 0, -1};
  cout << "Original array:" << endl;
  UniversalRadixSort<long>::print_array(array);

  try {
    UniversalRadixSort<long> sorter(
        UniversalRadixSort<long>::DataType::SIGNED_INTEGER,
        UniversalRadixSort<long>::ProcessingOrder::LSB_FIRST,
        UniversalRadixSort<long>::Direction::ASCENDING);
    sorter.sort(array);
    cout << "Sorted array (ascending):" << endl;
    UniversalRadixSort<long>::print_array(array);
  } catch (const UniversalRadixSort<long>::RadixException &e) {
    cout << "Sorting failed with error: " << e.what()
         << " (code: " << static_cast<int>(e.code()) << ")" << endl;
  }

  // Test descending order
  cout << "\n--- TEST CASE 1b: SIGNED LONG INTEGERS (DESCENDING) ---" << endl;
  vector<long> array_desc = {170, -45, 75, -9000, 802, -24, 2, 66, 0, -1};
  cout << "Original array:" << endl;
  UniversalRadixSort<long>::print_array(array_desc);

  try {
    UniversalRadixSort<long> sorter(
        UniversalRadixSort<long>::DataType::SIGNED_INTEGER,
        UniversalRadixSort<long>::ProcessingOrder::LSB_FIRST,
        UniversalRadixSort<long>::Direction::DESCENDING);
    sorter.sort(array_desc);
    cout << "Sorted array (descending):" << endl;
    UniversalRadixSort<long>::print_array(array_desc);
  } catch (const UniversalRadixSort<long>::RadixException &e) {
    cout << "Sorting failed with error: " << e.what()
         << " (code: " << static_cast<int>(e.code()) << ")" << endl;
  }
}

void test_floats() {
  cout << "\n--- TEST CASE 2: IEEE 754 SINGLE-PRECISION FLOATS (ASCENDING) ---"
       << endl;
  vector<float> array = {3.14f, -1.25f, 0.5f,    -99.9f,
                         2.0f,  0.0f,   -0.001f, 100.0f};
  cout << "Original array:" << endl;
  UniversalRadixSort<float>::print_array(array);

  try {
    UniversalRadixSort<float> sorter(
        UniversalRadixSort<float>::DataType::IEEE754_FLOAT,
        UniversalRadixSort<float>::ProcessingOrder::LSB_FIRST,
        UniversalRadixSort<float>::Direction::ASCENDING);
    sorter.sort(array);
    cout << "Sorted array (ascending):" << endl;
    UniversalRadixSort<float>::print_array(array);
  } catch (const UniversalRadixSort<float>::RadixException &e) {
    cout << "Sorting failed with error: " << e.what()
         << " (code: " << static_cast<int>(e.code()) << ")" << endl;
  }

  // Test descending order
  cout
      << "\n--- TEST CASE 2b: IEEE 754 SINGLE-PRECISION FLOATS (DESCENDING) ---"
      << endl;
  vector<float> array_desc = {3.14f, -1.25f, 0.5f,    -99.9f,
                              2.0f,  0.0f,   -0.001f, 100.0f};
  cout << "Original array:" << endl;
  UniversalRadixSort<float>::print_array(array_desc);

  try {
    UniversalRadixSort<float> sorter(
        UniversalRadixSort<float>::DataType::IEEE754_FLOAT,
        UniversalRadixSort<float>::ProcessingOrder::LSB_FIRST,
        UniversalRadixSort<float>::Direction::DESCENDING);
    sorter.sort(array_desc);
    cout << "Sorted array (descending):" << endl;
    UniversalRadixSort<float>::print_array(array_desc);
  } catch (const UniversalRadixSort<float>::RadixException &e) {
    cout << "Sorting failed with error: " << e.what()
         << " (code: " << static_cast<int>(e.code()) << ")" << endl;
  }
}

void test_doubles() {
  cout << "\n--- TEST CASE 3: IEEE 754 DOUBLE-PRECISION FLOATS (ASCENDING) ---"
       << endl;
  vector<double> array = {3.1415926535,
                          -1.25,
                          0.5,
                          -99.9999,
                          2.0,
                          0.0,
                          -0.000001,
                          100.0,
                          1.7976931348623157e+308,
                          -1.7976931348623157e+308};
  cout << "Original array:" << endl;
  UniversalRadixSort<double>::print_array(array);

  try {
    UniversalRadixSort<double> sorter(
        UniversalRadixSort<double>::DataType::IEEE754_DOUBLE,
        UniversalRadixSort<double>::ProcessingOrder::LSB_FIRST,
        UniversalRadixSort<double>::Direction::ASCENDING);
    sorter.sort(array);
    cout << "Sorted array (ascending):" << endl;
    UniversalRadixSort<double>::print_array(array);
  } catch (const UniversalRadixSort<double>::RadixException &e) {
    cout << "Sorting failed with error: " << e.what()
         << " (code: " << static_cast<int>(e.code()) << ")" << endl;
  }

  // Test descending order
  cout
      << "\n--- TEST CASE 3b: IEEE 754 DOUBLE-PRECISION FLOATS (DESCENDING) ---"
      << endl;
  vector<double> array_desc = {3.1415926535,
                               -1.25,
                               0.5,
                               -99.9999,
                               2.0,
                               0.0,
                               -0.000001,
                               100.0,
                               1.7976931348623157e+308,
                               -1.7976931348623157e+308};
  cout << "Original array:" << endl;
  UniversalRadixSort<double>::print_array(array_desc);

  try {
    UniversalRadixSort<double> sorter(
        UniversalRadixSort<double>::DataType::IEEE754_DOUBLE,
        UniversalRadixSort<double>::ProcessingOrder::LSB_FIRST,
        UniversalRadixSort<double>::Direction::DESCENDING);
    sorter.sort(array_desc);
    cout << "Sorted array (descending):" << endl;
    UniversalRadixSort<double>::print_array(array_desc);
  } catch (const UniversalRadixSort<double>::RadixException &e) {
    cout << "Sorting failed with error: " << e.what()
         << " (code: " << static_cast<int>(e.code()) << ")" << endl;
  }
}

void test_strings() {
  cout << "\n--- TEST CASE 4: FIXED-LENGTH STRINGS (LEXICOGRAPHICAL ASCENDING) "
          "---"
       << endl;
  vector<string> original_strings = {"banana", "apple",      "zebra",
                                     "fig",    "grapefruit", "cherry"};
  size_t max_len = get_max_string_length(original_strings);
  size_t element_size = max_len + 1; // +1 for null terminator

  cout << "Maximum string length: " << max_len << " characters" << endl;
  cout << "Element size (with null terminator): " << element_size << " bytes"
       << endl;

  // Create fixed-length string buffer
  vector<char> padded_buffer(original_strings.size() * element_size);

  // Copy and pad strings with null terminators
  for (size_t i = 0; i < original_strings.size(); ++i) {
    char *dest = &padded_buffer[i * element_size];
    strncpy(dest, original_strings[i].c_str(), element_size);
    dest[element_size - 1] = '\0'; // Ensure null termination
  }

  cout << "Original strings (padded):" << endl;
  for (size_t i = 0; i < original_strings.size(); ++i) {
    cout << "'" << &padded_buffer[i * element_size] << "' ";
  }
  cout << endl;

  try {
    // MSB-first (false) for string sorting, with ascending order
    UniversalRadixSort<char> sorter(
        UniversalRadixSort<char>::DataType::UNSIGNED_OR_STRING,
        UniversalRadixSort<char>::ProcessingOrder::MSB_FIRST,
        UniversalRadixSort<char>::Direction::ASCENDING);

    // Sort the buffer as fixed-length strings
    sorter.sort(padded_buffer.data(), original_strings.size());

    cout << "Sorted strings (ascending):" << endl;
    for (size_t i = 0; i < original_strings.size(); ++i) {
      cout << "'" << &padded_buffer[i * element_size] << "' ";
    }
    cout << endl;
  } catch (const UniversalRadixSort<char>::RadixException &e) {
    cout << "Sorting failed with error: " << e.what()
         << " (code: " << static_cast<int>(e.code()) << ")" << endl;
  }
}

void test_strings_descending() {
  cout << "\n--- TEST CASE 4b: FIXED-LENGTH STRINGS (LEXICOGRAPHICAL "
          "DESCENDING) ---"
       << endl;
  vector<string> original_strings = {"banana", "apple",      "zebra",
                                     "fig",    "grapefruit", "cherry"};
  size_t max_len = get_max_string_length(original_strings);
  size_t element_size = max_len + 1; // +1 for null terminator

  // Create fixed-length string buffer
  vector<char> padded_buffer(original_strings.size() * element_size);

  // Copy and pad strings with null terminators
  for (size_t i = 0; i < original_strings.size(); ++i) {
    char *dest = &padded_buffer[i * element_size];
    strncpy(dest, original_strings[i].c_str(), element_size);
    dest[element_size - 1] = '\0'; // Ensure null termination
  }

  cout << "Original strings (padded):" << endl;
  for (size_t i = 0; i < original_strings.size(); ++i) {
    cout << "'" << &padded_buffer[i * element_size] << "' ";
  }
  cout << endl;

  try {
    // MSB-first (false) for string sorting, with descending order
    UniversalRadixSort<char> sorter(
        UniversalRadixSort<char>::DataType::UNSIGNED_OR_STRING,
        UniversalRadixSort<char>::ProcessingOrder::MSB_FIRST,
        UniversalRadixSort<char>::Direction::DESCENDING);

    // Sort the buffer as fixed-length strings
    sorter.sort(padded_buffer.data(), original_strings.size());

    cout << "Sorted strings (descending):" << endl;
    for (size_t i = 0; i < original_strings.size(); ++i) {
      cout << "'" << &padded_buffer[i * element_size] << "' ";
    }
    cout << endl;
  } catch (const UniversalRadixSort<char>::RadixException &e) {
    cout << "Sorting failed with error: " << e.what()
         << " (code: " << static_cast<int>(e.code()) << ")" << endl;
  }
}

void test_edge_cases() {
  cout << "\n--- TEST CASE 5: EDGE CASES AND ERROR HANDLING ---" << endl;

  // Test case 1: Empty array
  vector<int> empty_array;
  try {
    UniversalRadixSort<int> sorter;
    sorter.sort(empty_array);
    cout << "Empty array test: PASSED (successfully handled)" << endl;
  } catch (const UniversalRadixSort<int>::RadixException &e) {
    cout << "Empty array test: FAILED" << endl;
  }

  // Test case 2: NULL pointer (simulated by trying to sort nullptr)
  try {
    UniversalRadixSort<int> sorter;
    sorter.sort(nullptr, 10);
    cout << "NULL pointer test: FAILED (expected exception not thrown)" << endl;
  } catch (const UniversalRadixSort<int>::RadixException &e) {
    if (e.code() == UniversalRadixSort<int>::ErrorCode::NULL_POINTER) {
      cout << "NULL pointer test: PASSED (expected error code: "
           << static_cast<int>(UniversalRadixSort<int>::ErrorCode::NULL_POINTER)
           << ", got: " << static_cast<int>(e.code()) << ")" << endl;
    } else {
      cout << "NULL pointer test: FAILED (unexpected error code)" << endl;
    }
  }
}

// Performance measurement functions
double measure_time(const function<void()> &func) {
  auto start = chrono::high_resolution_clock::now();
  func();
  auto end = chrono::high_resolution_clock::now();
  return chrono::duration<double, milli>(end - start).count();
}

void generate_random_ints(vector<int32_t> &data, size_t size) {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int32_t> dist(numeric_limits<int32_t>::min(),
                                         numeric_limits<int32_t>::max());

  data.clear();
  data.reserve(size);
  for (size_t i = 0; i < size; i++) {
    data.push_back(dist(gen));
  }
}

void generate_random_floats(vector<float> &data, size_t size) {
  random_device rd;
  mt19937 gen(rd());
  uniform_real_distribution<float> dist(-1e7, 1e7);

  data.clear();
  data.reserve(size);
  for (size_t i = 0; i < size; i++) {
    data.push_back(dist(gen));
  }
}

void generate_random_strings(vector<string> &data, size_t size, size_t length) {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<char> char_dist('a', 'z');

  data.clear();
  data.reserve(size);
  for (size_t i = 0; i < size; i++) {
    string str(length, ' ');
    for (size_t j = 0; j < length; j++) {
      str[j] = char_dist(gen);
    }
    data.push_back(str);
  }
}

double measure_radix_sort(vector<int32_t> &data) {
  UniversalRadixSort<int32_t> sorter(
      UniversalRadixSort<int32_t>::DataType::SIGNED_INTEGER,
      UniversalRadixSort<int32_t>::ProcessingOrder::LSB_FIRST,
      UniversalRadixSort<int32_t>::Direction::ASCENDING);

  return measure_time([&]() { sorter.sort(data); });
}

double measure_std_sort(vector<int32_t> &data) {
  return measure_time([&]() { sort(data.begin(), data.end()); });
}

double measure_radix_sort(vector<float> &data) {
  UniversalRadixSort<float> sorter(
      UniversalRadixSort<float>::DataType::IEEE754_FLOAT,
      UniversalRadixSort<float>::ProcessingOrder::LSB_FIRST,
      UniversalRadixSort<float>::Direction::ASCENDING);

  return measure_time([&]() { sorter.sort(data); });
}

double measure_std_sort(vector<float> &data) {
  return measure_time([&]() { sort(data.begin(), data.end()); });
}

double measure_radix_sort_strings(vector<char> &buffer, size_t n,
                                  size_t element_size) {
  UniversalRadixSort<char> sorter(
      UniversalRadixSort<char>::DataType::UNSIGNED_OR_STRING,
      UniversalRadixSort<char>::ProcessingOrder::MSB_FIRST,
      UniversalRadixSort<char>::Direction::ASCENDING);

  return measure_time([&]() { sorter.sort(buffer.data(), n); });
}

double measure_std_sort_strings(vector<string> &data) {
  return measure_time([&]() { sort(data.begin(), data.end()); });
}

void measure_performance() {
  cout << "\n";
  cout << "--- Performance ---\n";
  cout << "\nUniversal radix sort achieves O(n·k) time complexity where k is "
          "the number of bytes per element,\n";
  cout << "outperforming O(n log n) comparison sorts for large datasets with "
          "small key sizes.\n\n";

  cout << "┌───────────────────────────┬───────────┬───────────────┬───────────"
          "────────────────┐\n";
  cout << "│ Data Type                 │ Elements  │ Time (ms)     │ "
          "Comparison with std::sort │\n";
  cout << "├───────────────────────────┼───────────┼───────────────┼───────────"
          "────────────────┤\n";

  // Measure for int32_t
  {
    const size_t size = 100000;
    vector<int32_t> data;
    generate_random_ints(data, size);

    double radix_time = measure_radix_sort(data);
    double std_time = measure_std_sort(data);
    double speedup = std_time / radix_time;

    cout << "│ int32_t                   │ " << setw(8) << size << "  │ "
         << setw(12) << fixed << setprecision(1) << radix_time << "  │ "
         << fixed << setprecision(1) << speedup << "x faster               │\n";
  }

  // Measure for float
  {
    const size_t size = 100000;
    vector<float> data;
    generate_random_floats(data, size);

    double radix_time = measure_radix_sort(data);
    double std_time = measure_std_sort(data);
    double speedup = std_time / radix_time;

    cout << "│ float                     │ " << setw(8) << size << "  │ "
         << setw(12) << fixed << setprecision(1) << radix_time << "  │ "
         << fixed << setprecision(1) << speedup << "x faster               │\n";
  }

  // Measure for fixed-length strings
  {
    const size_t size = 100000;
    const size_t string_length = 10;
    vector<string> string_data;
    generate_random_strings(string_data, size, string_length);

    size_t element_size = string_length + 1;
    vector<char> buffer(string_data.size() * element_size);

    for (size_t i = 0; i < string_data.size(); i++) {
      char *dest = &buffer[i * element_size];
      strncpy(dest, string_data[i].c_str(), element_size);
      dest[element_size - 1] = '\0';
    }

    double radix_time =
        measure_radix_sort_strings(buffer, string_data.size(), element_size);
    double std_time = measure_std_sort_strings(string_data);
    double speedup = std_time / radix_time;

    cout << "│ Fixed-length string       │ " << setw(8) << size << "  │ "
         << setw(12) << fixed << setprecision(1) << radix_time << "  │ "
         << fixed << setprecision(1) << speedup << "x faster               │\n";
  }

  cout << "└───────────────────────────┴───────────┴───────────────┴───────────"
          "────────────────┘\n";
  cout << "\nPerformance measured on " << "current machine"
       << ", results may vary\n";
}
