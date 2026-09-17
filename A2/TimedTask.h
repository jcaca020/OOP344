#ifndef SENECA_TIMEDTASK_H
#define SENECA_TIMEDTASK_H

#include <iostream>
#include<string>
#include<chrono>


namespace seneca {

	class TimedTask {
		struct Task{


		std::string m_name;
		std::string m_units;
		std::chrono::steady_clock::duration m_duration;
	};

	size_t m_numRecords;
	std::chrono::steady_clock::time_point m_startTime;
	std::chrono::steady_clock::time_point m_endTime;
	Task m_records[10];

	public:

		TimedTask();
		void startClock();
		void stopClock();
		void addTask(const char* name);
		
		friend std::ostream& operator<<(std::ostream& os, const TimedTask& tt);
	};


}

#endif