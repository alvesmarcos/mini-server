// Created By: Marcos alves
// Created Date: May 6th, 2016	  
// Last Modified: May 7th, 2016	

#ifndef EMULATOR_H
#define EMULATOR_H

#include <vector>
#include <thread>
#include <sstream>
#include <string>
#include <cstring>
#include <regex>
#include "logger.hpp"
#include "socket.h"

class Emulator {
private:
	//data members
	std::vector<std::regex> rules;
	Socket* socket;
	std::vector<std::thread> threads; 
	//functions members
	//void activity(long client);
	bool regex_test(std::string& expr);
	void load_rules();
	std::vector<std::string> split(std::string str, char delimiter);

public:
	void activity(int& client);
	//constructor
	Emulator(Socket* skt);
	//destructor
	~Emulator();
	//functions members
	void run();
};

#endif //EMULATOR_H