
#include "Directory.h"
#include <iomanip>
#include <algorithm>
#include <stdexcept>

namespace seneca {

    Directory::Directory(const std::string& name) {
        m_name = name;
    }

    Directory::~Directory() {
        for (auto resource : m_contents) {
            delete resource;
        }
    }

    void Directory::update_parent_path(const std::string& path) {
        m_parent_path = path;

        for (auto resource : m_contents) {
            resource->update_parent_path(this->path());
        }
    }

    std::string Directory::name() const {
        return m_name;
    }

    std::string Directory::path() const {
        return m_parent_path + m_name;
    }

    int Directory::count() const {
        return static_cast<int>(m_contents.size());
    }

    size_t Directory::size() const {
        size_t total = 0;

        for (auto resource : m_contents) {
            total += resource->size();
        }

        return total;
    }

    NodeType Directory::type() const {
        return NodeType::DIR;
    }

    Directory& Directory::operator+=(Resource* resource) {

        auto existing = std::find_if(
            m_contents.begin(),
            m_contents.end(),
            [resource](const Resource* item) {
                return item->name() == resource->name();
            }
        );

        if (existing != m_contents.end()) {
            throw std::runtime_error(
                "Resource already exists!"
            );
        }

        m_contents.push_back(resource);

        resource->update_parent_path(this->path());

        return *this;
    }

    Resource* Directory::find(
        const std::string& name,
        const std::vector<OpFlags>& flags
    ) {

        auto it = std::find_if(
            m_contents.begin(),
            m_contents.end(),
            [&name](const Resource* resource) {
                return resource->name() == name;
            }
        );

        if (it != m_contents.end()) {
            return *it;
        }

        bool recursive = std::find(
            flags.begin(),
            flags.end(),
            OpFlags::RECURSIVE
        ) != flags.end();

        if (recursive) {
            for (auto resource : m_contents) {

                if (resource->type() == NodeType::DIR) {

                    Directory* dir =
                        dynamic_cast<Directory*>(resource);

                    Resource* found = dir->find(name, flags);

                    if (found != nullptr) {
                        return found;
                    }
                }
            }
        }

        return nullptr;
    }

    void Directory::remove(
        const std::string& name,
        const std::vector<OpFlags>& flags
    ) {

        auto it = std::find_if(
            m_contents.begin(),
            m_contents.end(),
            [&name](const Resource* resource) {
                return resource->name() == name;
            }
        );

        if (it == m_contents.end()) {
            throw std::string(
                name + " does not exist in " + m_name
            );
        }

        bool recursive = std::find(
            flags.begin(),
            flags.end(),
            OpFlags::RECURSIVE
        ) != flags.end();

        if ((*it)->type() == NodeType::DIR && !recursive) {
            throw std::invalid_argument(
                name + " is a directory. Pass the recursive flag to delete directories."
            );
        }

        delete *it;

        m_contents.erase(it);
    }

    void Directory::display(
        std::ostream& os,
        const std::vector<FormatFlags>& flags
    ) const {

        os << "Total size: " << size() << " bytes\n";

        bool longFormat = std::find(
            flags.begin(),
            flags.end(),
            FormatFlags::LONG
        ) != flags.end();

        for (auto resource : m_contents) {

            os << (resource->type() == NodeType::DIR ? "D" : "F");

            os << " | "
               << std::left << std::setw(15)
               << resource->name()
               << " | ";

            if (longFormat) {

                if (resource->type() == NodeType::DIR) {
                    os << std::right << std::setw(2)
                       << resource->count();
                }
                else {
                    os << "  ";
                }

                os << " | "
                   << std::right << std::setw(10)
                   << resource->size()
                   << " bytes";
            }

            os << " |\n";
        }
    }

}
