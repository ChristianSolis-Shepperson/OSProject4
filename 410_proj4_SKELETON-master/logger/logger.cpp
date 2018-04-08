#include "../includes/logger.h"
using namespace std;

//FIXME-- Make Class Threadsafe

Logger::Logger(std::string filename) {
	this->filename = filename;
}

Logger::~Logger() {
}

//open close and clear the log file
void Logger::clearlogfile() {

	//Used lock guards in case of exceptions
	std::lock_guard<std::mutex> lg(m);

	myFile.open(filename, std::fstream::trunc);

	//close file
	if (myFile.is_open())
		myFile.close();
}

void Logger::log(std::string data) {

	//Used lock guards in case of exceptions
	std::lock_guard<std::mutex> lg(m);

	myFile.open(filename, std::fstream::app);
	if (!myFile.is_open())
		return;

	std::string myline;

	myFile << data;

	//close file
	if (myFile.is_open())
		myFile.close();
}
