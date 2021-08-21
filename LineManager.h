#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "Utilities.h"
#include "Workstation.h"
#include "LineManager.h"

namespace sdds {

	class LineManager {
		std::vector<Workstation*> activeLine;
		size_t m_cntCustomerOrder{0};
		Workstation* m_firstStation{nullptr};
		size_t omg = 1;
	public:
		LineManager();
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		void linkStations();
		bool run(std::ostream& os);
		void display(std::ostream& os) const;

	};

}

#endif