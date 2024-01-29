#include "logger.h"
#include <iostream>
#include <ctime>

namespace Logger {
	std::string getCurrentTimestamp() {
		time_t now;
		struct tm timeinfo;
		char timestamp[64];

		time(&now);
		localtime_s(&timeinfo, &now);
		strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &timeinfo);

		return std::string(timestamp);
	}

	void logWithLabel(const std::string& label, const std::string& message) {
		std::string timestamp = getCurrentTimestamp();
		std::string formattedMessage = "[" + timestamp + "] [" + label + "] " + message;

		std::cout << formattedMessage << "\n";
	}
}