#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm> 
#include "Station.h"
#include "Utilities.h"

using namespace std;
namespace sdds {

	size_t Station::m_widthField = 0;
	int Station::id_generator = 1;

	Station::Station() {

	}

	Station::Station(const std::string& str) {
		m_id = id_generator;
		Utilities utility;
		size_t traveco = 0;
		bool ok = true;

		try {
			m_name = utility.extractToken(str, traveco, ok);
			m_serial = stoi(utility.extractToken(str, traveco, ok));
			m_inStock = stoi(utility.extractToken(str, traveco, ok));
			m_widthField = max(utility.getFieldWidth(), m_widthField);
			m_desc = utility.extractToken(str, traveco, ok);
		}
		catch (string& err) {
			cout << err;
		}
		id_generator++;
	}

	const std::string& Station::getItemName() const {
		return m_name;
	}

	unsigned int Station::getNextSerialNumber() {
		m_serial++;
		return m_serial - 1;
	}

	unsigned int Station::getQuantity() const {
		return m_inStock;
	}

	void Station::updateQuantity() {
		m_inStock--;
		if (m_inStock < 0) {
			m_inStock = 0;
		}
	}

	void Station::display(std::ostream& os, bool full) const {
		os << right << "[" << setw(3) << setfill('0') << m_id << "]";
		os << " Item: " << setw(m_widthField) << left << setfill(' ') << m_name;
		os << " [" << setw(6) << right << setfill('0') << m_serial << "]";

		if (full) {
			os << " Quantity: " << setw(m_widthField) << left << setfill(' ') << m_inStock;
			os << " Description: " << m_desc << endl;
		}
		else {
			os << std::endl;
		}

	}

}
