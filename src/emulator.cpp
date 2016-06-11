// Created By: Marcos alves
// Created Date: Jun 7th, 2016	  
// Last Modified: Jun 11th, 2016	

#include "emulator.h"

Emulator::Emulator(Socket& skt): socket(&skt) {
	rules.push_back(std::regex("GET \\/.+ HTTP\\/1\\.1"));
	rules.push_back(std::regex("Host: .+"));
	rules.push_back(std::regex("User-Agent: .+"));
	rules.push_back(std::regex("Accept: .+"));
	rules.push_back(std::regex("Accept-Language: .+"));
	rules.push_back(std::regex("Accept-Encoding: .+"));
}

Emulator::~Emulator() { /* unimplemented */ }

void Emulator::activity(int client) {
	std::string recv = socket->receive(client);
	recv += "IP address: " + socket->get_client_ip();
	Logger::get_instance().sys_register(recv, Logger::INFO);

	//variants message
	std::string status("200 OK");
	std::string content_type("none");
	std::string content("");

	if(!regex_test(recv))
		status = "400 Bad Request";
	else {
		std::string::size_type position = recv.find("HTTP") - 5; //[SPACE]+|HTTP| - 
		std::string file =  recv.substr(4, position);
		std::ifstream read("../base/" + file);
		if(!read.good())
			status = "404 Not Found";
		else {
			std::string copy{(std::istreambuf_iterator<char>(read)),
                       		 (std::istreambuf_iterator<char>())};
			content = copy;
			position = file.find(".");
			content_type = file.substr(position, file.length());
			read.close();
		}
	}	

	std::string message = "\nHTTP/1.1 " + status +
						  "\nDate: " + Logger::get_instance().sys_time() +
						  "\nServer: alvesmarcos/Ubuntu"
					      "\nContent-Length: " + std::to_string(content.length()) +
						  "\nContent-Type: " + content_type + "; utf8"
						  "\nConnection: Closed\n\n" + content;
	
	socket->send(client, message);
	close(client);
} 

bool Emulator::regex_test(std::string& expr) {
	std::vector<std::string> expr_vec;

	//split string
	char* token = std::strtok(&expr[0], "\n");
    while(token!=nullptr){
       expr_vec.push_back(token);
       token = std::strtok(nullptr, "\n");
    }
   
	if(expr_vec.size() < rules.size())
		return false;
	
	for(unsigned int i = 0 ; i < rules.size() ; ++i)
		if(!std::regex_search(expr_vec[i], rules[i])) 
			return false;

	return true;
}

void Emulator::run(void) {
	
	try {
		socket->bind();
		socket->listen();
				
		while(true) {
			int client = socket->accept();
			threads.push_back(std::thread(&Emulator::activity, this, client));
		}
	} catch (std::exception& e) {
		std::cerr << "About: " <<  e.what() <<std::endl;
	}
}
