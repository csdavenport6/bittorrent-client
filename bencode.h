#ifndef BENCODE_H_
#define BENCODE_H_

#include <iostream>
#include <string>
#include <variant>
#include <vector>
#include <map>

class BEncodingParser {
    public:
        BEncodingParser(const std::string& data);
        std::variant<int, std::string, std::vector<std::variant<int, std::string>>, std::map<std::string, std::variant<int, std::string>>> Parse();

    private:
        std::string::const_iterator current;
        std::string::const_iterator end;
        std::variant<int, std::string, std::vector<std::variant<int, std::string>>, std::map<std::string, std::variant<int, std::string>>> ParseElement();
        std::string ParseString();
        int ParseInteger();
        std::vector<std::variant<int, std::string>> ParseList();
        std::map<std::string, std::variant<int, std::string>> ParseDictionary();
};



#endif // BENCODE_H_
