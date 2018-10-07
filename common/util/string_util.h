/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

/**
 * @file
 * @brief Some string util functions.
 */

#ifndef MODULES_COMMON_UTIL_STRING_UTIL_H_
#define MODULES_COMMON_UTIL_STRING_UTIL_H_

#include <boost/algorithm/string.hpp>

#include <functional>
#include <sstream>
#include <string>
#include <vector>

#include "google/protobuf/stubs/stringprintf.h"
#include "google/protobuf/stubs/strutil.h"

/**
 * @namespace apollo::common::util
 * @brief apollo::common::util
 */
namespace apollo {
namespace common {
namespace util {

// Expose some useful utils from protobuf.
using google::protobuf::Join;
using google::protobuf::StrAppend;
using google::protobuf::StrCat;
using google::protobuf::StringPiece;
using google::protobuf::StringPrintf;

/**
 * @brief Check if a string ends with a pattern.
 * @param ori The original string. To see if it ends with a specified pattern.
 * @param pat The target pattern. To see if the original string ends with it.
 * @return Whether the original string ends with the specified pattern.
 */
inline bool EndWith(const std::string& ori, const std::string& pat) {
  return StringPiece(ori).ends_with(pat);
}
inline bool StartWith(const std::string& ori, const std::string& pat) {
  return StringPiece(ori).starts_with(pat);
}

/**
 * @brief split string by one character
 * @param [in]: the string you want to split
 * @param [in]: the character
 * @param [out]: result strings after exploded by character
 **/
void split(const std::string& str, char ch, std::vector<std::string>* result);

/**
 * @brief: trim the left side empty space of string
 * @param [in/out]: trimed string
 * @return: void
 **/
void ltrim(std::string* str);
inline std::string ltrim(std::string str) {
  ltrim(&str);
  return str;
}

/**
 * @brief: trim the right side empty space of string
 * @param [in/out]: trimed string
 * @return: void
 **/
void rtrim(std::string* str);
inline std::string rtrim(std::string str) {
  rtrim(&str);
  return str;
}

/**
 * @brief: trim the string, in place vesion
 * @param [in/out]: trimed string
 * @return: void
 **/
void trim(std::string* str);
inline std::string trim(std::string str) {
  trim(&str);
  return str;
}

template <typename T>
std::string Print(const T& val) {
  std::ostringstream oss;
  oss << val;
  return oss.str();
}

/**
 * @brief Make arrays, conatiners and iterators printable.
 *
 * Usage:
 *   vector<int> vec = {1, 2, 3};
 *   std::cout << PrintIter(vec);
 *   std::cout << PrintIter(vec, ",");
 *   std::cout << PrintIter(vec.begin(), vec.end());
 *   std::cout << PrintIter(vec.begin(), vec.end(), "|");
 *
 *   int array[] = {1, 2, 3};
 *   std::cout << PrintIter(array);
 *   std::cout << PrintIter(array, "|");
 *   std::cout << PrintIter(array + 0, array + 10, "|");
 */
template <typename Iter>
std::string PrintIter(const Iter& begin, const Iter& end,
                      const std::string& delimiter = " ") {
  std::string result;
  Join(begin, end, delimiter.c_str(), &result);
  return result;
}

template <typename Iter>
std::string PrintIter(const Iter& begin, const Iter& end,
                      const std::function<std::string(Iter)> transformer,
                      const std::string& delimiter = " ") {
  std::string result;
  if (transformer) {
    for (auto iter = begin; iter != end; ++iter) {
      if (iter == begin) {
        StrAppend(&result, transformer(*iter));
      } else {
        StrAppend(&result, delimiter, transformer(*iter));
      }
    }
  } else {
    PrintIter(begin, end, delimiter);
  }
  return result;
}

template <typename Container, typename Iter>
std::string PrintIter(const Container& container,
                      const std::function<std::string(Iter)> transformer,
                      const std::string& delimiter = " ") {
  return PrintIter(container.begin(), container.end(), transformer, delimiter);
}

template <typename Container>
std::string PrintIter(const Container& container,
                      const std::string& delimiter = " ") {
  return PrintIter(container.begin(), container.end(), delimiter);
}

template <typename T, int length>
std::string PrintIter(T (&array)[length], T* end,
                      const std::string& delimiter = " ") {
  std::string result;
  Join(array, end, delimiter.c_str(), &result);
  return result;
}

template <typename T, int length>
std::string PrintIter(T (&array)[length], const std::string& delimiter = " ") {
  return PrintIter(array, array + length, delimiter);
}

/**
 * @brief Make conatiners and iterators printable. Similar to PrintIter but
 *        output the DebugString().
 */
template <typename Iter>
std::string PrintDebugStringIter(const Iter& begin, const Iter& end,
                                 const std::string& delimiter = " ") {
  std::string result;
  for (auto iter = begin; iter != end; ++iter) {
    if (iter == begin) {
      StrAppend(&result, iter->DebugString());
    } else {
      StrAppend(&result, delimiter, iter->DebugString());
    }
  }
  return result;
}

template <typename Container>
std::string PrintDebugStringIter(const Container& container,
                                 const std::string& delimiter = " ") {
  return PrintDebugStringIter(container.begin(), container.end(), delimiter);
}

std::string Base64Decode(const std::string &base64_str);

}  // namespace util
}  // namespace common
}  // namespace apollo

#endif  // MODULES_COMMON_UTIL_STRING_UTIL_H_
