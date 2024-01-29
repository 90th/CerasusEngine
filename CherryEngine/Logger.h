#ifndef LOGGER_H
#define LOGGER_H

#include <string>

namespace Logger {
	void logWithLabel(const std::string& label, const std::string& message, bool logToFile = false, const std::string& filename = "log.txt");
}

#endif // LOGGER_H
