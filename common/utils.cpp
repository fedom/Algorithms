#include "utils.h"

std::string string_join(const std::vector<std::string> &vec, const std::string &delim) {

    std::string r;

    int i = 0;
    for (i = 0; i < vec.size() - 1; i++) {
        r += vec[i];
        r += delim;
    }

    r += vec[i];

    return r;
}

std::vector<std::string> string_split(const std::string &s, const std::string &delimiters) {
    std::vector<std::string> tokens;
    size_t start_pos = s.find_first_not_of(delimiters, 0); 
    size_t end_pos = s.find_first_of(delimiters, start_pos);

    while (start_pos != std::string::npos) {
        tokens.push_back(s.substr(start_pos, end_pos - start_pos));
        start_pos = s.find_first_not_of(delimiters, end_pos);
        end_pos = s.find_first_of(delimiters, start_pos);
    }   

    return tokens;
}


std::vector<int> string_vec_to_int_vec(const std::vector<std::string> &str_vec) {
    std::vector<int> num_vec;

    for (auto i : str_vec) {
        num_vec.push_back(atoi(i.c_str())); 
    }

    return num_vec;
}

std::vector<std::string> int_vec_to_string_vec(const std::vector<int> &int_vec) {
    std::vector<std::string> str_vec;

    for (auto i : int_vec) {
        str_vec.push_back(std::to_string(i)); 
    }

    return str_vec;



}
