#include <iostream>
#include <string>
#include <algorithm>
#include "Utilities.h"

using namespace std;
namespace sdds {

	char Utilities::m_delimiter = ' ';

	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}

	void Utilities::setDelimiter(char newDelimiter) {
		m_delimiter = newDelimiter;
	}
	char Utilities::getDelimiter() {
		return m_delimiter;
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
		string toret = "";
		size_t extracted = next_pos;
		next_pos = str.find(m_delimiter, extracted);

		if (next_pos == string::npos) {
			toret = str.substr(extracted);
			m_widthField = max(toret.length(), m_widthField);
			more = false;
		}
		else if (extracted == next_pos)
		{
			more = false;
			throw "No token found!";
		}
		else {
			toret = str.substr(extracted, next_pos - extracted);
			m_widthField = max(toret.length(), m_widthField);
			more = true;
		}
		next_pos++;
		return toret;
	}

}
