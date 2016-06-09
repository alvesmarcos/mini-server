// Created By: Marcos alves
// Created Date: May 7th, 2016	  
// Last Modified: May 7th, 2016	

#include "emulator.h"

Emulator::Emulator(Socket* skt): socket(skt) { load_rules(); }

Emulator::~Emulator() { /* unimplemented */ }

void Emulator::activity(int& client) {
	std::string recv = socket->receive(client);
	
	//variants message
	std::string status = "OK";
	std::string content_type = "none";
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
						  "\nDate: " + static_cast<const std::string>(__DATE__)+ 
						  " " + static_cast<const std::string>(__TIME__) + " GMT"
						  "\nServer: test"
					      "\nContent-Length: " + std::to_string(content.length()) +
						  "\nContent-Type: " + content_type + "; utf8"
						  "\nConnection: Closed\n\n" + content;
	
	socket->send(client, message);

	close(client);
} 

void Emulator::load_rules(void) {
	rules.push_back(std::regex("GET \\/.+ HTTP\\/1\\.1"));
	rules.push_back(std::regex("Host: .+"));
	rules.push_back(std::regex("User-Agent: .+"));
	rules.push_back(std::regex("Accept: .+"));
	rules.push_back(std::regex("Accept-Language: .+"));
	rules.push_back(std::regex("Accept-Encoding: .+"));
}

bool Emulator::regex_test(std::string& expr) {
	std::vector<std::string> expr_vec = split(expr, '\n');

	/*if(expr_vec.size() < rules.size()) return false;
*//*	
	std::clog << expr_vec[1] << std::endl;

	for(unsigned int i = 0 ; i < 1 ; ++i)
		if(!std::regex_search(expr_vec[i], rules[i])) return false;
*/
	return true;
}

std::vector<std::string> Emulator::split(std::string str, char delimiter) {
	std::vector<std::string> buffer;
  	std::stringstream ss(str);
  	std::string tok;
  
  	while(std::getline(ss, tok, delimiter))
  		buffer.push_back(tok);

	return buffer;	
}