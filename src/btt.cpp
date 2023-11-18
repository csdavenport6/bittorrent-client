#include "bencode.h"
#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    std::cout << "Hello World" << std::endl;

    // Read torrent file
    std::ifstream torrent_file("test/big-buck-bunny.torrent", std::ios::binary);
    if (!torrent_file.is_open()) {
        std::cerr << "Failed to open torrent file." << std::endl;
        return 1;
    }

    // Use the parser
    std::stringstream buffer;
    buffer << torrent_file.rdbuf();
    std::string torrent_data = buffer.str();

    BEncodingParser parser(torrent_data);
    try {
        BencodeValue parsed_data = parser.Parse();
        std::visit(BencodeVisitor(), parsed_data);
    } catch (const std::exception& e) {
        std::cerr << "Error parsing torrent file: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
