// Created By: Marcos alves
// Created Date: Jun 6th, 2016	  
// Last Modified: Jun 12th, 2016	

#ifndef EMULATOR_H
#define EMULATOR_H

#include <vector>
#include <thread>
#include <sstream>
#include <map>
#include <string>
#include <cstring>
#include <regex>
#include "logger.hpp"
#include "socket.h"

class Emulator {
private:
	//data members
	std::map<std::string, std::string> types;
	std::vector<std::regex> rules;
	Socket* socket;
	std::vector<std::thread> threads; 
	//functions members
	void activity(int client);
	std::string calculate_vote(std::string s);
	bool regex_test(std::string& expr) const;

public:
	//constructor
	Emulator(Socket& skt);
	//destructor
	~Emulator();
	//functions members
	void run();
};

#endif //EMULATOR_H