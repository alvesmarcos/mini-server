// Created By: Marcos alves
// Created Date: Jun 7th, 2016	  
// Last Modified: Jun 12th, 2016	

#include "emulator.h"

Emulator::Emulator(Socket& skt):
				//load types
				types { {"html", "text/html"},
						{"gif", "image/gif"}, 
						{"jpg", "image/jpg"},
						{"png", "image/png"} },
				//load rules HTTP
				rules { std::regex("GET \\/[[:alnum:]]+\\.[[:alnum:]]+ HTTP\\/1\\.1"),
			    		std::regex("Host: .+"),
						std::regex("User-Agent: .+"),
			    		std::regex("Accept: .+"),
						std::regex("Accept-Language: .+"),
						std::regex("Accept-Encoding: .+") },
				//init-value socket
				socket(&skt) {/* unimplemented */ }

Emulator::~Emulator() { /* unimplemented */ }

void Emulator::activity(int client) {
	std::string recv {socket->receive(client)};
	recv += "IP address: " + socket->get_client_ip();
	Logger::get_instance().sys_register(recv, Logger::INFO);

	//variants message
	std::string status{"200 OK"};
	std::string content_type{"none"};
	std::string content{""};

	if(!regex_test(recv))
		status = "400 Bad Request";
	else {
		std::string::size_type position {recv.find("HTTP") - 5}; //[SPACE]+|HTTP| - 
		std::string file {recv.substr(4, position)};

		std::ifstream read{"../base/" + calculate_vote(file)};
		if(!read.good())
			status = "404 Not Found";
		else {
			std::string copy{(std::istreambuf_iterator<char>(read)),
                       		 (std::istreambuf_iterator<char>())};
			content = copy;
			position = file.find(".") + 1;
			content_type = types[file.substr(position, file.length())];
			read.close();
		}
	}	

	std::string message { "\nHTTP/1.1 " + status +
						  "\nDate: " + Logger::get_instance().sys_time() +
						  "Server: alvesmarcos/Ubuntu" +
						  "\nAccess-Control-Allow-Origin: *"
					      "\nContent-Length: " + std::to_string(content.length()) +
						  "\nContent-Type: " + content_type +
						  "\nConnection: Closed\n\n" + content };
	
	socket->send(client, message);
	close(client);
} 

bool Emulator::regex_test(std::string& expr) const {
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

// ================= ALTERAÇÃO PARA UMA APLICAÇÃO ESPECÍFICA ======================
std::string Emulator::calculate_vote(std::string s){
	std::fstream file("../base/database.txt", std::fstream::in);
	std::string line, content;

	int count = 1;
	bool flag = true;
	int value = std::stoi(s.substr(1, 1));

	while (getline(file, line)){
		if(count == value){
     		std::cout << line << '\n';
     		content += std::to_string(std::stoi(line) + 1) + '\n';
     		flag = false;
     	}
     	if(line!="\n" && flag)
     		content += line + '\n';
     	flag = true;
     	count++;
    }
    file.close();
    file.open("../base/database.txt", std::fstream::out | std::fstream::trunc);
    file << content;
    file.close();
    
    return "database.txt";
}