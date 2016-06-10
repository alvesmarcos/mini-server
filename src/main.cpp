// Created By: Marcos alves
// Created Date: May 3th, 2016	  
// Last Modified: May 7th, 2016	      

#include <iostream>
#include <exception>
#include <vector>
#include <thread>
#include <regex>
#include "emulator.h"
#include "logger.hpp"
#include "socket.h"


int main(int argc, char **argv) {
	
	Socket st{8080};
	Emulator emt{st};

	emt.run();

	return 0;
}
