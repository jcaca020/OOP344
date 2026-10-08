#include "toy.h"
#include <iomanip>

namespace seneca {

    Toy::Toy(const std::string& toy) {
        std::string temp = toy;

        // ID
        size_t pos = temp.find(':');
        std::string token = temp.substr(0, pos);

        // Remove leading spaces
        token.erase(0, token.find_first_not_of(' '));

        // Remove trailing spaces
        token.erase(token.find_last_not_of(' ') + 1);

        m_id = std::stoi(token);

        // Remove ID from string
        temp.erase(0, pos + 1);

        // NAME
        pos = temp.find(':');
        token = temp.substr(0, pos);

        token.erase(0, token.find_first_not_of(' '));
        token.erase(token.find_last_not_of(' ') + 1);

        m_name = token;

        temp.erase(0, pos + 1);

        // NUMBER OF ITEMS
        pos = temp.find(':');
        token = temp.substr(0, pos);

        token.erase(0, token.find_first_not_of(' '));
        token.erase(token.find_last_not_of(' ') + 1);

        m_numItems = std::stoi(token);

        temp.erase(0, pos + 1);

        // PRICE
        token = temp;

        token.erase(0, token.find_first_not_of(' '));
        token.erase(token.find_last_not_of(' ') + 1);

        m_price = std::stod(token);
    }

    void Toy::update(int numItems) {
        m_numItems = numItems;
    }

    std::ostream& operator<<(std::ostream& os, const Toy& toy) {

        double subtotal = toy.m_price * toy.m_numItems;
        double tax = subtotal * Toy::HST;
        double total = subtotal + tax;

        os << "Toy "
           << std::right << std::setfill('0') << std::setw(8)
           << toy.m_id
           << ": ";

        os << std::right << std::setfill('.')
           << std::setw(24) << toy.m_name;

        os << " " << std::right << std::setfill(' ')
           << std::setw(2) << toy.m_numItems
           << " items @ ";

        os << std::right << std::setfill(' ')
           << std::fixed << std::setprecision(2)
           << std::setw(6) << toy.m_price
           << "/item  subtotal: ";

        os << std::right << std::setfill(' ')
           << std::setw(7) << subtotal
           << " tax: ";

        os << std::right << std::setfill(' ')
           << std::setw(6) << tax
           << " total: ";

        os << std::right << std::setfill(' ')
           << std::setw(7) << total
           << std::endl;

        return os;
    }

}