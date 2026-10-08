#include "confirmationOrder.h"
#include <utility>

namespace seneca {

    // Copy Constructor
    ConfirmationOrder::ConfirmationOrder(
        const ConfirmationOrder& other
    ) {

        m_count = other.m_count;

        if (m_count > 0) {

            m_toys = new const Toy*[m_count];

            for (size_t i = 0; i < m_count; i++) {
                m_toys[i] = other.m_toys[i];
            }
        }
    }

    // Copy Assignment
    ConfirmationOrder& ConfirmationOrder::operator=(
        const ConfirmationOrder& other
    ) {

        if (this != &other) {

            delete[] m_toys;

            m_toys = nullptr;
            m_count = other.m_count;

            if (m_count > 0) {

                m_toys = new const Toy*[m_count];

                for (size_t i = 0; i < m_count; i++) {
                    m_toys[i] = other.m_toys[i];
                }
            }
        }

        return *this;
    }

    // Move Constructor
    ConfirmationOrder::ConfirmationOrder(
        ConfirmationOrder&& other
    ) noexcept {

        m_toys = other.m_toys;
        m_count = other.m_count;

        other.m_toys = nullptr;
        other.m_count = 0;
    }

    // Move Assignment
    ConfirmationOrder& ConfirmationOrder::operator=(
        ConfirmationOrder&& other
    ) noexcept {

        if (this != &other) {

            delete[] m_toys;

            m_toys = other.m_toys;
            m_count = other.m_count;

            other.m_toys = nullptr;
            other.m_count = 0;
        }

        return *this;
    }

    // Destructor
    ConfirmationOrder::~ConfirmationOrder() {

        // IMPORTANT:
        // We only delete the ARRAY.
        // We DO NOT delete the Toy objects.

        delete[] m_toys;
    }

    ConfirmationOrder& ConfirmationOrder::operator+=(
        const Toy& toy
    ) {

        // Check if toy already exists
        for (size_t i = 0; i < m_count; i++) {

            if (m_toys[i] == &toy) {
                return *this;
            }
        }

        // Create a new array
        const Toy** temp = new const Toy*[m_count + 1];

        // Copy existing addresses
        for (size_t i = 0; i < m_count; i++) {
            temp[i] = m_toys[i];
        }

        // Add address of new toy
        temp[m_count] = &toy;

        // Delete old array
        delete[] m_toys;

        // Replace with new array
        m_toys = temp;

        ++m_count;

        return *this;
    }

    ConfirmationOrder& ConfirmationOrder::operator-=(
        const Toy& toy
    ) {

        size_t index = m_count;

        // Find toy
        for (size_t i = 0; i < m_count; i++) {

            if (m_toys[i] == &toy) {
                index = i;
                break;
            }
        }

        // Toy not found
        if (index == m_count) {
            return *this;
        }

        // Shift everything left
        for (size_t i = index; i + 1 < m_count; i++) {
            m_toys[i] = m_toys[i + 1];
        }

        --m_count;

        // Resize
        if (m_count == 0) {

            delete[] m_toys;
            m_toys = nullptr;

        }
        else {

            const Toy** temp = new const Toy*[m_count];

            for (size_t i = 0; i < m_count; i++) {
                temp[i] = m_toys[i];
            }

            delete[] m_toys;

            m_toys = temp;
        }

        return *this;
    }

    std::ostream& operator<<(
        std::ostream& os,
        const ConfirmationOrder& order
    ) {

        os << "-------------------------- "
              "Confirmations to Send"
              " --------------------------"
           << std::endl;

        if (order.m_count == 0) {

            os << "There are no confirmations to send!"
               << std::endl;

        }
        else {

            for (size_t i = 0; i < order.m_count; i++) {
                os << *order.m_toys[i];
            }
        }

        os << "--------------------------"
           << std::endl;

        return os;
    }

}