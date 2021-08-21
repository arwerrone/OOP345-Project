#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include <iostream>
#include <vector>
#include "Station.h"
#include "CustomerOrder.h"

extern std::vector<sdds::CustomerOrder> pending;
extern std::vector<sdds::CustomerOrder> completed;
extern std::vector<sdds::CustomerOrder> incomplete;

namespace sdds {

	class Workstation : public Station {
		std::vector<CustomerOrder> m_orders;
		Workstation* m_pNextStation = nullptr;
	public:
		Workstation();
		Workstation(const std::string& str);
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);

	};

}

#endif