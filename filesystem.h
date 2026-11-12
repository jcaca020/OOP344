
#ifndef SENECA_FILESYSTEM_H
#define SENECA_FILESYSTEM_H

#include "Directory.h"
#include "Resource.h"
#include <string>

namespace seneca {

    class Filesystem {

        Directory* m_root{};
        Directory* m_current{};

    public:
        Filesystem(
            const std::string& filename,
            const std::string& rootName = ""
        );

        Filesystem(const Filesystem&) = delete;
        Filesystem& operator=(const Filesystem&) = delete;

        Filesystem(Filesystem&& other) noexcept;
        Filesystem& operator=(Filesystem&& other) noexcept;

        ~Filesystem();

        Filesystem& operator+=(Resource* resource);

        Directory* change_directory(
            const std::string& directory = ""
        );

        Directory* get_current_directory() const;
    };

}

#endif
