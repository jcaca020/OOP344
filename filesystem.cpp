
#include "Filesystem.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <utility>

namespace seneca {

    // Removes spaces from the beginning and end of a string
    static std::string trim(const std::string& str) {

        size_t first = str.find_first_not_of(" \t\r\n");

        if (first == std::string::npos) {
            return "";
        }

        size_t last = str.find_last_not_of(" \t\r\n");

        return str.substr(first, last - first + 1);
    }


    // Splits a path into its individual components
    static std::vector<std::string> splitPath(
        const std::string& path
    ) {

        std::vector<std::string> components;
        std::stringstream ss(path);
        std::string component;

        while (std::getline(ss, component, '/')) {

            component = trim(component);

            if (!component.empty()) {
                components.push_back(component);
            }
        }

        return components;
    }


    // Constructor
    Filesystem::Filesystem(
        const std::string& filename,
        const std::string& rootName
    ) {

        m_root = new Directory(rootName);
        m_current = m_root;

        std::ifstream file(filename);

        if (!file) {
            delete m_root;
            m_root = nullptr;
            m_current = nullptr;

            throw std::runtime_error(
                "Cannot open file: " + filename
            );
        }

        std::string line;

        while (std::getline(file, line)) {

            line = trim(line);

            if (line.empty()) {
                continue;
            }

            // Check if the line represents a file
            size_t separator = line.find('|');

            bool isFile = separator != std::string::npos;

            std::string resourcePath;
            std::string contents;

            if (isFile) {

                resourcePath = trim(
                    line.substr(0, separator)
                );

                contents = trim(
                    line.substr(separator + 1)
                );

            }
            else {

                resourcePath = trim(line);

            }

            std::vector<std::string> components =
                splitPath(resourcePath);

            if (components.empty()) {
                continue;
            }

            Directory* current = m_root;

            // Number of directory components
            size_t dirCount = components.size();

            if (isFile) {
                dirCount--;
            }

            // Create or locate the directories
            for (size_t i = 0; i < dirCount; ++i) {

                std::string dirName = components[i] + "/";

                Directory* next = dynamic_cast<Directory*>(
                    current->find(dirName)
                );

                if (next == nullptr) {

                    next = new Directory(dirName);

                    *current += next;
                }

                current = next;
            }

            // Create the file if the resource is a file
            if (isFile) {

                File* newFile = new File(
                    components.back(),
                    contents
                );

                *current += newFile;
            }
        }
    }


    // Move constructor
    Filesystem::Filesystem(Filesystem&& other) noexcept {

        m_root = other.m_root;
        m_current = other.m_current;

        other.m_root = nullptr;
        other.m_current = nullptr;
    }


    // Move assignment operator
    Filesystem& Filesystem::operator=(
        Filesystem&& other
    ) noexcept {

        if (this != &other) {

            delete m_root;

            m_root = other.m_root;
            m_current = other.m_current;

            other.m_root = nullptr;
            other.m_current = nullptr;
        }

        return *this;
    }


    // Destructor
    Filesystem::~Filesystem() {

        delete m_root;

        m_root = nullptr;
        m_current = nullptr;
    }


    // Adds a resource to the current directory
    Filesystem& Filesystem::operator+=(Resource* resource) {

        *m_current += resource;

        return *this;
    }


    // Changes the current directory
    Directory* Filesystem::change_directory(
        const std::string& directory
    ) {

        if (directory.empty()) {

            m_current = m_root;

            return m_current;
        }

        Directory* target = dynamic_cast<Directory*>(
            m_current->find(directory)
        );

        if (target == nullptr) {

            throw std::invalid_argument(
                "Cannot change directory! " +
                directory + " not found!"
            );
        }

        m_current = target;

        return m_current;
    }


    // Returns the current directory
    Directory* Filesystem::get_current_directory() const {

        return m_current;
    }

}
