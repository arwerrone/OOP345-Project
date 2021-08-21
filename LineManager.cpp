#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "Utilities.h"
#include "Workstation.h"
#include "LineManager.h"

using namespace std;
namespace sdds {

	LineManager::LineManager() :m_cntCustomerOrder{ 0 }, m_firstStation{ nullptr }{

	}

	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
		ifstream fin(file);
		string str;
		bool ok = true;
		size_t cnt = 0;
		m_cntCustomerOrder = pending.size();

		while (getline(fin, str)) {
			size_t pos = str.find('|');
			for (size_t i = 0; i < stations.size(); i++) {
				if (str.substr(0, pos) == stations.at(i)->getItemName()) {
					if (pos != SIZE_MAX) {
						for (size_t j = 0; j < stations.size(); j++) {
							if (str.substr(pos + 1) == stations.at(j)->getItemName()) {
								stations.at(i)->setNextStation(stations.at(j));
								activeLine.push_back(std::move(stations.at(i)));
							}
						}
					}
					else {
						activeLine.push_back(std::move(stations.at(i)));
					}
				}
			}
			for (size_t k = 0; k < activeLine.size(); k++) {
				for (size_t l = 0; l < activeLine.size(); l++) {
					if (activeLine.at(l)->getNextStation() != nullptr) {
						if (activeLine.at(k)->getItemName() == activeLine.at(l)->getNextStation()->getItemName()) {
							ok = false;
						}
					}
				}
				if (ok) {
					m_firstStation = activeLine.at(k);
				}
				ok = true;
			}
			cnt++;
		}

	}

	void LineManager::linkStations() {
		vector<Workstation*> vecWork;
		Workstation* thisStat = m_firstStation;
		while (thisStat != nullptr) {
			vecWork.push_back(thisStat);
			thisStat = thisStat->getNextStation();
		}
		activeLine = vecWork;
	}

	bool LineManager::run(std::ostream& os) {
		size_t prevOrdersFinished = completed.size() + incomplete.size();

		os << "Line Manager Iteration: " << omg++ << endl;
		if (!pending.empty()) {
			*activeLine.front() += std::move(pending.front());
			pending.erase(pending.begin());
		}

		std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* ws) {
			ws->fill(os);
		});
		std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* ws) {
			ws->attemptToMoveOrder();
		});
		m_cntCustomerOrder -= ((completed.size() + incomplete.size()) - prevOrdersFinished);

		return m_cntCustomerOrder <= 0;
	}

	void LineManager::display(std::ostream& os) const {
		for (size_t i = 0; i < activeLine.size(); i++) {
			activeLine.at(i)->display(os);
		}
	}

}