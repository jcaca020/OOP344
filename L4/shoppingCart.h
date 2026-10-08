#ifndef SENECA_SHOPPINGCART_H
#define SENECA_SHOPPINGCART_H

#include <iostream>
#include <string>
#include <cstddef>

#include "toy.h"

namespace seneca {

    class ShoppingCart {

        std::string m_name{};
        int m_age{};
        const Toy** m_toys{};
        size_t m_count{};

    public:

        ShoppingCart(
            const std::string& name,
            int age,
            const Toy* toys[],
            size_t count
        );

        // Copy constructor
        ShoppingCart(const ShoppingCart& other);

        // Copy assignment
        ShoppingCart& operator=(const ShoppingCart& other);

        // Move constructor
        ShoppingCart(ShoppingCart&& other) noexcept;

        // Move assignment
        ShoppingCart& operator=(ShoppingCart&& other) noexcept;

        // Destructor
        ~ShoppingCart();

        friend std::ostream& operator<<(
            std::ostream& os,
            const ShoppingCart& cart
        );
    };

}

#endif