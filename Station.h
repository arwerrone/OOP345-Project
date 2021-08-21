#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <iostream>
#include <string>

namespace sdds {

	class Station {
		int m_id{};
		std::string m_name{};
		std::string m_desc{};
		unsigned int m_serial{};
		unsigned int m_inStock{};
		static size_t m_widthField;
		static int id_generator;
	public:
		Station();	//CHANGE MADE BECAUSE OF MS3
		Station(const std::string&);
		const std::string& getItemName() const;
		unsigned int getNextSerialNumber();
		unsigned int getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;

	};

}

#endif