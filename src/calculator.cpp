#include "calculator.h"

bool PNLCalculator::remove_from_queue(std::deque<Lot>& q, bool lifo, int& takeQty, double& lotPrice) {
    if (q.empty()) {
        return false;
    }
    Lot lot;
    if (lifo) {
        lot = q.back();
    } else {
        lot = q.front();
    }
    int used = std::min(takeQty, lot.qty);
    takeQty -= used;
    lotPrice = lot.price;

    lot.qty -= used;
    // if matched (no leftover), remove that lot from the queue
    if (lot.qty == 0) {
        if (lifo) {
            q.pop_back();
         } else {
            q.pop_front();
         }
    }
    return true;
}

void PNLCalculator::push_lot(std::deque<Lot>& q, double price, int qty) {
    if (qty > 0) {
        q.push_back(Lot{price, qty});
    }
}

double PNLCalculator::process(const Trade& t) {
    Book& book = books_[t.symbol];
    bool lifo = (mode_ == Mode::LIFO);
    double pnl = 0.0;

    if (t.type == 'B') { // current process is buy
        // search the lots in sells
        int remaining = t.quantity;
        while (remaining > 0 && !book.sells.empty()) {
            int need = remaining;
            double sellPrice = 0.0;
            if (!remove_from_queue(book.sells, lifo, need, sellPrice)) {
                break;
            }
            int matchQty = remaining - need;
            remaining = need;
            pnl += matchQty * (sellPrice - t.price);
        }
        // if there's leftover, add to buys
        push_lot(book.buys, t.price, remaining);
    } else if (t.type == 'S') { // current process is sell
        // search the lots in buys
        int remaining = t.quantity;
        while (remaining > 0 && !book.buys.empty()) {
            int need = remaining;
            double buyPrice = 0.0;
            if (!remove_from_queue(book.buys, lifo, need, buyPrice)) {
                break;
            }
            int matchQty = remaining - need;
            remaining = need;
            pnl += matchQty * (t.price - buyPrice);
        }
        // if there's leftover, add to sells
        push_lot(book.sells, t.price, remaining);
    }
    return pnl;
}
