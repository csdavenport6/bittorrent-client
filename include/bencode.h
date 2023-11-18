#ifndef BENCODE_H_
#define BENCODE_H_

#pragma once

// Forward declaration for alias
struct BencodeValueWrapper;

#include <iostream>
#include <string>
#include <variant>
#include <vector>
#include <map>
#include <memory>

using BencodeValue = std::variant<
        int,
        std::string,
        std::vector<std::shared_ptr<BencodeValueWrapper>>,
        std::map<std::string, std::shared_ptr<BencodeValueWrapper>>>;

struct BencodeValueWrapper {
    std::shared_ptr<BencodeValue> value;
};

class BEncodingParser {
    public:
        BEncodingParser(const std::string& data);
        BencodeValue Parse();

    private:
        std::string::const_iterator current;
        std::string::const_iterator end;
        BencodeValue ParseElement();
        std::string ParseString();
        int ParseInteger();
        std::vector<std::shared_ptr<BencodeValueWrapper>> ParseList();
        std::map<std::string, std::shared_ptr<BencodeValueWrapper>> ParseDictionary();
};

struct BencodeVisitor {
    void operator()(int i) const {
        std::cout << "Integer: " << i << std::endl;
    }

    void operator()(const std::string& str) const {
        std::cout << "String: " << str << std::endl;
    }

    void operator()(const std::vector<std::shared_ptr<BencodeValueWrapper>>& vec) const {
        std::cout << "List: " << std::endl;
        for (const auto& val : vec) {
            if (val && val->value) {
                std::visit(BencodeVisitor(), *(val->value));
            }
        }
    }

    void operator()(const std::map<std::string, std::shared_ptr<BencodeValueWrapper>>& dict) const {
        std::cout << "Dictionary: " << std::endl;
        for (const auto& [key, val] : dict) {
            std::cout << "Key: " << key << std::endl;
            if (val && val->value) {
                std::visit(BencodeVisitor(), *(val->value));
            }
        }
    }


};

#endif // BENCODE_H_
