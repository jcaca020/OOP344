#ifndef SENECA_CONFIRMATIONORDER_H
#define SENECA_CONFIRMATIONORDER_H

#include <iostream>
#include <cstddef>

#include "toy.h"

namespace seneca {

    class ConfirmationOrder {

        const Toy** m_toys{};
        size_t m_count{};

    public:

        ConfirmationOrder() = default;

        // Copy constructor
        ConfirmationOrder(const ConfirmationOrder& other);

        // Copy assignment
        ConfirmationOrder& operator=(
            const ConfirmationOrder& other
        );

        // Move constructor
        ConfirmationOrder(
            ConfirmationOrder&& other
        ) noexcept;

        // Move assignment
        ConfirmationOrder& operator=(
            ConfirmationOrder&& other
        ) noexcept;

        // Destructor
        ~ConfirmationOrder();

        ConfirmationOrder& operator+=(const Toy& toy);

        ConfirmationOrder& operator-=(const Toy& toy);

        friend std::ostream& operator<<(
            std::ostream& os,
            const ConfirmationOrder& order
        );
    };

}

#endif