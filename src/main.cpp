// Created By: Marcos alves
// Created Date: Jun 3th, 2016	  
// Last Modified: Jun 11th, 2016	      

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
