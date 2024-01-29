#include "logger.h"
#include <iostream>
#include <fstream>
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

	void logWithLabel(const std::string& label, const std::string& message, bool logToFile, const std::string& filename) {
		std::string timestamp = getCurrentTimestamp();
		std::string formattedMessage = "[" + timestamp + "] [" + label + "] " + message;

		std::cout << formattedMessage << std::endl;

		if (logToFile) {
			std::ofstream logFile(filename, std::ios::app);
			if (logFile.is_open()) {
				logFile << formattedMessage << std::endl;
				logFile.close();
			}
			else {
				std::cerr << "Error: Unable to open log file: " << filename << "\n";
			}
		}
	}
}