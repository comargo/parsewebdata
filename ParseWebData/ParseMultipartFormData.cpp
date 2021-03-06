/*
 * ParseMultipartFormData.cpp
 *
 *  Created on: Jul 10, 2012
 *      Author: cyril
 */

#include <ParseWebData.h>
#include "ParseWebData_local.h"
#include "ParseMultipartFormData.h"

#include <sstream>
#include <algorithm>

namespace ParseWebData {
namespace ParseMultipartFormData {

class ParseData {
public:
	ParseData(WebDataMap& _dataMap) :
			dataMap(_dataMap) {
	}
	void operator()(std::string data) {
		WebData outData;
		std::istringstream dataStream(data);
		std::string header;
		while (true) {
			std::string line;
			std::getline(dataStream, line);
			if (line.rfind('\r') == line.length() - 1)
				line.erase(line.rfind('\r'), 1);
			if (line.empty())
				break;
			header += line + "\n";
		}
		outData.attributes = map_pairs(header, "\n", ": ");
		string_map::iterator iter = outData.attributes.find(
				"Content-Disposition");
		if (iter != outData.attributes.end()) {
			string_map extraParam = map_pairs(
					std::string("type=") + (*iter).second, "; ", "=");
			outData.attributes.erase(iter);
			outData.attributes.insert(extraParam.begin(), extraParam.end());
		}

		for (iter = outData.attributes.begin();
				iter != outData.attributes.end(); ++iter) {
			std::string::size_type start = (*iter).second.find_first_not_of(
					"\"");
			std::string::size_type stop = (*iter).second.find_last_not_of("\"");
			if (start == std::string::npos)
				(*iter).second.clear();
			else
				(*iter).second = (*iter).second.substr(start, stop - start + 1);
		}

		std::ostringstream valueStream;
		std::copy(std::istreambuf_iterator<char>(dataStream),
				std::istreambuf_iterator<char>(),
				std::ostreambuf_iterator<char>(valueStream));

		outData.value = valueStream.str();
		dataMap.insert(std::make_pair(outData.attributes["name"], outData));
	}

private:
	WebDataMap& dataMap;
};

void sanitize_parts(string_list& parts) {
	string_list::iterator iter = parts.begin();
	while (iter != parts.end()) {

		if ((*iter).find("--\r\n") == 0) { // If part starts with --\r\n - it is last boundary. remove
			iter = parts.erase(iter);
			continue;
		}

		if ((*iter).find("\r\n") == 0) { // Due to split command all parts starts with empty line. Remove it
			(*iter).erase(0, 2);
		}
		if ((*iter).rfind("\r\n") == (*iter).length() - 2) { // Due to split command all parts ends with CRLF. Remove it
			(*iter).erase((*iter).rfind("\r\n"), 2);
		}
		++iter;
	}
}

bool parse_data(const std::string& data, const string_map& content_type,
		WebDataMap& dataMap) {

	string_map::const_iterator bndIter = content_type.find("boundary");
	if (content_type.end() == bndIter) // No boundary indicator!
		return false;
	string_list parts = split(data, std::string("--") + bndIter->second, false);
	sanitize_parts(parts);
	std::for_each(parts.begin(), parts.end(), ParseData(dataMap));
	return true;
}

} // namespace ParseMultipartFormData
} // namespace ParseWebData

