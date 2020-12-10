#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <vector>

std::string string_join(const std::vector<std::string> &vec, const std::string &delim);
std::vector<std::string> string_split(const std::string &s, const std::string &delims);
std::vector<int> string_vec_to_int_vec(const std::vector<std::string> &str_vec);
std::vector<std::string> int_vec_to_string_vec(const std::vector<int> &int_vec);

#endif//UTILS_H
