#include "TimedTask.h"
#include <fstream>


namespace seneca {

	TimedTask::TimedTask() {

		m_numRecords = 0;
	}
	void TimedTask::startClock() {

		m_startTime = std::chrono::steady_clock::now();
	}
	void TimedTask::stopClock() {

		m_endTime = std::chrono::steady_clock::now();

	}

	void TimedTask::addTask(const char* name) {


		if (m_numRecords<10) {

			m_records[m_numRecords].m_name = name;
			m_records[m_numRecords].m_units = "nanoseconds";

			m_records[m_numRecords].m_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
				m_endTime - m_startTime);

			m_numRecords++;
		}
	}

	std::ostream& operator<< (std::ostream& os, const TimedTask& tt) {
		for (size_t i = 0; i < tt.m_numRecords; i++) {

			os << tt.m_records[i].m_name << " | "
				<< tt.m_records[i].m_duration.count() << " | "
				<< tt.m_records[i].m_units << " |\n";


		}
		return os;

	}

}