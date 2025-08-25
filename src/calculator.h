#pragma once
#include <deque>
#include <map>
#include <string>

struct Trade {
    long long timestamp{};
    std::string symbol;
    char type{};
    double price{};
    int quantity{};
};

enum class Mode { FIFO, LIFO };

class PNLCalculator {
public:
    // Constructor
    PNLCalculator(Mode mode) {
        mode_ = mode;
    }
    // Process a single trade
    double process(const Trade& t);

private:
    struct Lot {
        double price;
        int qty;
    };

    // For each symbol we keep track the trades for buys and sells
    struct Book {
        std::deque<Lot> buys;
        std::deque<Lot> sells;
    };
    // map each symbol to an order book (consists of buys and sells)
    std::map<std::string, Book> books_;
    Mode mode_;

    // Helper function to push a Lot to the queue
    static void push_lot(std::deque<Lot>& q, double price, int qty);

    // Help function to pop from front (FIFO) or back (LIFO)
    static bool remove_from_queue(std::deque<Lot>& q, bool lifo, int& takeQty, double& lotPrice);
};
