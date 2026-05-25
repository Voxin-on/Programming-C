#include "FormatRowFile.h"
#include <sstream>
#include <iostream>

FormatRowFile::FormatRowFile(const char* str){
    if (!str) return;
    std::string line(str);
    std::istringstream iss(line);
    std::string word;

    while (iss >> word)
        words.push_back(word);

}

bool FormatRowFile::operator<(const FormatRowFile& other) const{
    return this->words < other.words;
}
bool FormatRowFile::operator==(const FormatRowFile& other) const{
    return this->words == other.words;
}

std::ostream& operator<<(std::ostream& os, const FormatRowFile& row) {
    for (size_t i = 0; i < row.words.size(); ++i) {
        os << row.words[i];
        if (i + 1 < row.words.size()) os << " ";
    }
    return os;
}