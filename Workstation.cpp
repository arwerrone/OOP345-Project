#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <string>
#include "Workstation.h"

using namespace std;

std::vector<sdds::CustomerOrder> pending{};
std::vector<sdds::CustomerOrder> completed{};
std::vector<sdds::CustomerOrder> incomplete{};

namespace sdds {

	Workstation::Workstation() : m_pNextStation{ nullptr } {

	}

	Workstation::Workstation(const string& str) : Station(str), m_pNextStation{ nullptr } {
	
	}

	void Workstation::fill(std::ostream& os) {
		if (!m_orders.empty()) {
			m_orders.begin()->fillItem(*this, os);
		}
	}

	bool Workstation::attemptToMoveOrder() {
		bool toret = false;
		if (!m_orders.empty()) {
			if (m_orders.front().isItemFilled(getItemName()) || getQuantity() <= 0) {
				if (m_pNextStation != nullptr) {
					*m_pNextStation += std::move(m_orders.front());
					m_orders.erase(m_orders.begin());
					toret = true;
				}
				else {
					if (m_orders.front().isFilled()) {
						completed.push_back(std::move(m_orders.front()));
					}
					else {
						incomplete.push_back(std::move(m_orders.front()));
					}
					m_orders.erase(m_orders.begin());
					toret = true;
				}
			}
		}
		return toret;
	}

	void Workstation::setNextStation(Workstation* station) {
		m_pNextStation = station;
	}

	Workstation* Workstation::getNextStation() const {
		return m_pNextStation;
	}

	void Workstation::display(std::ostream& os) const {
		os << getItemName() << " --> ";
		os << (m_pNextStation != nullptr ? m_pNextStation->getItemName() : "End of Line");
		os << endl;
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
		m_orders.push_back(std::move(newOrder));
		return *this;
	}

}