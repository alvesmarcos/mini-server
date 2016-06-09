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

	Emulator emt{&st};

	int client = 0;

	/*std::regex exp_http("GET .+");

	std::string rev = "GET /arquivo.html HTTP/1.1";

	std::clog << std::regex_search(rev, rules::GET);
*/
	try {

		st.bind();
		st.listen();
		
		while(true) {
			client = st.accept();
			emt.activity(client);
		}

	} catch (std::exception& e) {

		std::cerr << "Exception: " << e.what() << std::endl;
	}

	/*std::string fnames = "GET /arquivo.html HTTP/1.1\nHost: www.test101.com\nUser-Agent: Mozilla/4.0\nAccept: image/gif\nAccept-Language: en-us\nAccept-Encoding: gzip, deflate\n";
    
    //std::regex txt_regex("GET: .+\\HTTP\nHost: .+\\\n\\Accept: .+");
 	 
 	 std::regex txt_regex{"GET .+\\HTTP/1.1\n"
 	 					  "Host: .+\n"
 	 					  "Accept: .+\n"
 	 					  "Accept-Language: .+\n"
 	 					  "Accept-Encoding: .+\n"
 	 					  "User-Agent: .+\n"};

    std::cout << fnames << ": " << std::regex_search(fnames, Emulator::rule) << std::endl;
    */   
 
	return 0;
}
