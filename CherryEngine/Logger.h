#ifndef LOGGER_H
#define LOGGER_H

#include <string>

namespace Logger {
	void logWithLabel(const std::string& label, const std::string& message);
}

#endif
