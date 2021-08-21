#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include "CustomerOrder.h"
#include "Utilities.h"
#include "Station.h"

namespace sdds {

	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder() :m_name{ "" }, m_product{ "" }, m_cntItem{ 0 }, m_lstItem{nullptr} {
		//m_name = "";
		//m_product = "";
		//m_cntItem = 0;
		//m_lstItem = nullptr;
	}

	CustomerOrder::CustomerOrder(std::string& str) {
		Utilities util;
		size_t next_pos = 0;
		bool ok = true;
		m_cntItem = 0;

		m_name = util.extractToken(str, next_pos, ok);
		m_product = util.extractToken(str, next_pos, ok);

		size_t another_pos = next_pos;

		while (ok) {
			util.extractToken(str, next_pos, ok);
			m_cntItem++;
		}

		m_lstItem = new Item * [m_cntItem];
		ok = true;

		for (size_t i = 0; i < m_cntItem; i++) {
			m_lstItem[i] = new Item(util.extractToken(str, another_pos, ok));
		}

		if (util.getFieldWidth() > m_widthField) {
			m_widthField = util.getFieldWidth();
		}

	}

	CustomerOrder::CustomerOrder(const CustomerOrder&) {
		throw std::string("No copy operations are allowed!");
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
		*this = std::move(src);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
		if (this != &src) {
			if (m_lstItem != nullptr) {
				for (size_t i = 0; i < m_cntItem; i++) {
					delete m_lstItem[i];
				}
			}

			delete[] m_lstItem;
			m_name = src.m_name;
			m_product = src.m_product;
			m_cntItem = src.m_cntItem;
			m_lstItem = src.m_lstItem;
			src.m_lstItem = nullptr;
		}
		return *this;
	}

	CustomerOrder::~CustomerOrder() {
		if (m_lstItem) {
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}
		}
		delete[] m_lstItem;
		m_lstItem = nullptr;
	}

	bool CustomerOrder::isFilled() const {
		bool toret = true;

		for (size_t i = 0; i < m_cntItem && toret; i++) {
			if (m_lstItem[i]->m_isFilled == false) {
				toret = false;
			}
		}

		return toret;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		bool toret = true;
		std::for_each(m_lstItem, (m_lstItem + m_cntItem), [itemName, &toret](const Item* item) {
			if (item->m_itemName == itemName && !item->m_isFilled) toret = false;
			});
		return toret;
	}


	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == station.getItemName()) {
				if (station.getQuantity() > 0) {
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;

					os << std::right << "    Filled ";
					os << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
				else {
					os << std::right << "    Unable to fill ";
					os << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
			}
		}

	}

	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; i++) {
			os << "[" << std::setw(6) << std::right << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
			os << std::setw(m_widthField) << std::left << std::setfill(' ') << m_lstItem[i]->m_itemName << " - ";
			os << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
		}
	}

}