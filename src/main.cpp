// Created By: Marcos alves
// Created Date: Jun 3th, 2016	  
// Last Modified: Jun 12th, 2016	      

#include "emulator.h"
#include "socket.h"


int main(int argc, char **argv) {
	
	Socket st{8080};
	Emulator emul{st};
	emul.run();

	return 0;
}
