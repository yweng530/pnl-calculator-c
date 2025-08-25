#include <iostream>
#include <fstream>
#include <sstream>
#include "calculator.h"

static bool parse_trade_line(const std::string& line, Trade& trade) {
    if (line.empty()) {
        return false;
    }
    // read and process the line
    std::stringstream ss(line);
    std::string token;
    std::string fields[5];
    int idx = 0;
    while (std::getline(ss, token, ',')) {
        if (idx < 5) {
            fields[idx] = token;
            idx += 1;
        }
    }
    if (idx < 5) {
        return false;
    }
    try {
        trade.timestamp = std::stoll(fields[0]);
        trade.symbol = fields[1];
        trade.type = fields[2][0]; // get the char
        trade.price = std::stod(fields[3]);
        trade.quantity = std::stoi(fields[4]);
    } catch (...) {
        return false;
    }
    return (trade.type == 'B' || trade.type == 'S') && trade.quantity > 0;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << "<input.csv> <fifo|lifo>\n";
        return 1;
    }
    std::string path = argv[1];
    std::string modeStr = argv[2];
    Mode mode;
    if (modeStr == "fifo") {
        mode = Mode::FIFO;
    } else if (modeStr == "lifo") {
        mode = Mode::LIFO;
    } else {
        std::cerr << "Second argument must be 'fifo' or 'lifo'\n";
        return 1;
    }
    // Print header
    std::cout << "TIMESTAMP,SYMBOL,PNL\n";

    PNLCalculator calculator(mode);
    return 0;
}
