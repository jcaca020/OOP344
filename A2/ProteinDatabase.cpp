#include "ProteinDatabase.h"
#include <fstream>

namespace seneca {

	ProteinDatabase::ProteinDatabase() {
		m_size = 0;
		m_UIDs = nullptr;
		m_sequences = nullptr;

	}

	size_t ProteinDatabase::size()const {
		return m_size;

	}

	std::string ProteinDatabase::operator[](size_t index)const {
		if (index < m_size)
		{
			return m_sequences[index];
		}
		else
		{
			return"";

		}
	}

		std::string ProteinDatabase::getUID(size_t index)const
		{
			if (index < m_size)
			{
				return m_UIDs[index];
			}
			else

			{
				return "None";

			}
		}

		ProteinDatabase::ProteinDatabase(const char* filename)
		{
			m_size = 0;
			m_UIDs = nullptr;
			m_sequences = nullptr;

			std::ifstream file(filename);
			std::string line;

			while (std::getline(file, line))
			{

				if (line[0] == '>')
				{
					m_size++;

				}
			}

			m_UIDs = new std::string[m_size];
			m_sequences = new std::string[m_size];

			file.clear();
			file.seekg(0);

			size_t index = 0;
			std::string sequence;

			while (std::getline(file, line)) {

				if (line[0] == '>') {
					if (index > 0) {
						m_sequences[index - 1] = sequence;
						sequence.clear();
					}

					size_t first = line.find('|');
					size_t second = line.find('|', first + 1);

					m_UIDs[index] = line.substr(first + 1, second - first - 1);
					index++;
				}
				else
				{
					sequence += line;
				}
			}
			if (index > 0) {
				m_sequences[index - 1] = sequence;
			}
		}


			ProteinDatabase::~ProteinDatabase() {
				delete[] m_UIDs;
				delete[] m_sequences;
			}

	

	ProteinDatabase::ProteinDatabase(const ProteinDatabase& other) {
		m_size = other.m_size;

		m_UIDs = new std::string[m_size];
		m_sequences = new std::string[m_size];

		for (size_t i = 0; i < m_size; i++) {

			m_UIDs[i] = other.m_UIDs[i];
			m_sequences[i] = other.m_sequences[i];
		}

	}

	ProteinDatabase& ProteinDatabase:: operator=(const ProteinDatabase& other) {
		if (this != &other) {

			delete[]m_UIDs;
			delete[]m_sequences;

			m_size = other.m_size;

			m_UIDs = new std::string[m_size];
			m_sequences = new std::string[m_size];

			for (size_t i = 0; i < m_size; i++) {
				m_UIDs[i] = other.m_UIDs[i];
				m_sequences[i] = other.m_sequences[i];


			}
		}
		return*this;

	}

	ProteinDatabase::ProteinDatabase(ProteinDatabase&& other) {

		m_size = other.m_size;
		m_UIDs = other.m_UIDs;
		m_sequences = other.m_sequences;

		other.m_size=0;
		other.m_UIDs=nullptr;
		other.m_sequences = nullptr;
	}

	ProteinDatabase& ProteinDatabase::operator=(ProteinDatabase&& other) {

		if (this != &other) {
			delete[]m_UIDs;
			delete[]m_sequences;

			m_size = other.m_size;

			m_UIDs = other.m_UIDs;
			m_sequences = other.m_sequences;

			other.m_size = 0;
			other.m_UIDs = nullptr;
			other.m_sequences = nullptr; 
		}
		return*this;
	}

};

			
		

