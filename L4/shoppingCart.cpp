#include "shoppingCart.h"
#include <utility>

namespace seneca {

    ShoppingCart::ShoppingCart(
        const std::string& name,
        int age,
        const Toy* toys[],
        size_t count
    ) {
        m_name = name;
        m_age = age;
        m_count = count;

        if (m_count > 0) {

            m_toys = new const Toy*[m_count];

            for (size_t i = 0; i < m_count; i++) {
                m_toys[i] = new Toy(*toys[i]);
            }
        }
    }

    // Copy Constructor
    ShoppingCart::ShoppingCart(const ShoppingCart& other) {

        m_name = other.m_name;
        m_age = other.m_age;
        m_count = other.m_count;

        if (m_count > 0) {

            m_toys = new const Toy*[m_count];

            for (size_t i = 0; i < m_count; i++) {
                m_toys[i] = new Toy(*other.m_toys[i]);
            }
        }
    }

    // Copy Assignment
    ShoppingCart& ShoppingCart::operator=(
        const ShoppingCart& other
    ) {

        if (this != &other) {

            // Delete existing toys
            if (m_toys) {

                for (size_t i = 0; i < m_count; i++) {
                    delete m_toys[i];
                }

                delete[] m_toys;
            }

            m_toys = nullptr;
            m_count = other.m_count;
            m_name = other.m_name;
            m_age = other.m_age;

            if (m_count > 0) {

                m_toys = new const Toy*[m_count];

                for (size_t i = 0; i < m_count; i++) {
                    m_toys[i] = new Toy(*other.m_toys[i]);
                }
            }
        }

        return *this;
    }

    // Move Constructor
    ShoppingCart::ShoppingCart(
        ShoppingCart&& other
    ) noexcept {

        m_name = std::move(other.m_name);
        m_age = other.m_age;
        m_toys = other.m_toys;
        m_count = other.m_count;

        other.m_toys = nullptr;
        other.m_count = 0;
        other.m_age = 0;
        other.m_name.clear();
    }

    // Move Assignment
    ShoppingCart& ShoppingCart::operator=(
        ShoppingCart&& other
    ) noexcept {

        if (this != &other) {

            // Release current resources
            if (m_toys) {

                for (size_t i = 0; i < m_count; i++) {
                    delete m_toys[i];
                }

                delete[] m_toys;
            }

            m_name = std::move(other.m_name);
            m_age = other.m_age;
            m_toys = other.m_toys;
            m_count = other.m_count;

            other.m_toys = nullptr;
            other.m_count = 0;
            other.m_age = 0;
            other.m_name.clear();
        }

        return *this;
    }

    // Destructor
    ShoppingCart::~ShoppingCart() {

        if (m_toys) {

            for (size_t i = 0; i < m_count; i++) {
                delete m_toys[i];
            }

            delete[] m_toys;
        }
    }

    std::ostream& operator<<(
        std::ostream& os,
        const ShoppingCart& cart
    ) {

        static int CALL_CNT = 1;

        os << "-------------------------- Order "
           << CALL_CNT++
           << ": ";

        if (cart.m_toys == nullptr) {

            os << "This shopping cart is invalid. "
               << "--------------------------"
               << std::endl;

        }
        else {

            os << "Shopping for "
               << cart.m_name
               << " "
               << cart.m_age
               << " years old ("
               << cart.m_count
               << " toys)"
               << " --------------------------"
               << std::endl;

            if (cart.m_count == 0) {

                os << "Empty shopping cart! "
                   << "--------------------------"
                   << std::endl;
            }
            else {

                for (size_t i = 0; i < cart.m_count; i++) {
                    os << *cart.m_toys[i];
                }

                os << "--------------------------"
                   << std::endl;
            }
        }

        return os;
    }

}