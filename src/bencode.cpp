#include "bencode.h"

BEncodingParser::BEncodingParser(const std::string& data) : current(data.begin()), end(data.end()) {}

BencodeValue BEncodingParser::Parse() {
    return ParseElement();
}

BencodeValue BEncodingParser::ParseElement() {
    if (*current == 'i') {
        return ParseInteger();
    } else if (isdigit(*current)) {
        return ParseString();
    } else if (*current == 'l') {
        return ParseList();
    } else if (*current == 'd') {
        return ParseDictionary();
    }
    throw std::runtime_error("Invalid BEncoding");
}

std::string BEncodingParser::ParseString() {
    auto colon = std::find(current, end, ':');
    if (colon == end) throw std::runtime_error("Invalid string in BEncoding");

    int len = std::stoi(std::string(current, colon));
    current = colon + 1;

    auto start = current;
    current += len;
    return std::string(start, current);
}

int BEncodingParser::ParseInteger() {
    current++; // skip 'i'
    auto endInt = std::find(current, end, 'e');
    if (endInt == end) throw std::runtime_error("Invalid integer in BEncoding");

    int num = std::stoi(std::string(current, endInt));
    current = endInt + 1; // skip 'e'
    return num;
}

std::vector<std::shared_ptr<BencodeValueWrapper>> BEncodingParser::ParseList() {
    current++; // skip 'l'
    std::vector<std::shared_ptr<BencodeValueWrapper>> list;

    while (*current != 'e') {
        // Create a shared pointer to a new BencodeValueWrapper
        auto wrapper = std::make_shared<BencodeValueWrapper>();

        // Parse the next element and assign it to the wrapper's value
        wrapper->value = std::make_shared<BencodeValue>(ParseElement());

        // Add the wrapper to the list
        list.push_back(wrapper);
    }
    current++; // skip 'e'

    return list;
}

std::map<std::string, std::shared_ptr<BencodeValueWrapper>> BEncodingParser::ParseDictionary() {
    current++; // skip 'd'
    std::map<std::string, std::shared_ptr<BencodeValueWrapper>> dict;

    while (*current != 'e') {
        // Create a shared ptr to a new BencodeValueWrapper
        auto wrapper = std::make_shared<BencodeValueWrapper>();

        // Parse the next element
        std::string key = ParseString();
        wrapper->value = std::make_shared<BencodeValue>(ParseElement());

        // The wrapper is the value
        dict[key] = wrapper;
    }
    current++; // skip 'e'

    return dict;
}

