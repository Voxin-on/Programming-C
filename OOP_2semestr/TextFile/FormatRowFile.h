#ifndef FORMATROWFILE_H
#define FORMATROWFILE_H

#include <vector>
#include <string>

class FormatRowFile{
    std::vector<std::string> words;
public:
    FormatRowFile() = default;
    FormatRowFile(const char* str);

    bool operator<(const FormatRowFile& other) const;
    bool operator==(const FormatRowFile& other) const;

    friend std::ostream& operator<<(std::ostream& os, const FormatRowFile& row);
};

#endif