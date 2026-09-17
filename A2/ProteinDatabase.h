#ifndef SENECA_PROTEINDATABASE_H
#define SENECA_PROTEINDATABASE_H

#include <string>
#include <cstddef>

namespace seneca {
	class ProteinDatabase {
		size_t m_size{};
		std::string* m_UIDs{};
		std::string* m_sequences{};
	public:
		ProteinDatabase();

		size_t size()const;

		std::string operator[](size_t index)const;
		std::string getUID(size_t index) const;

		ProteinDatabase(const char*);
		~ProteinDatabase();

		ProteinDatabase(const ProteinDatabase& other);
		ProteinDatabase& operator=(const ProteinDatabase& other);

		ProteinDatabase(ProteinDatabase&& other);
		ProteinDatabase& operator=(ProteinDatabase&& other);

		};
	

}
#endif

