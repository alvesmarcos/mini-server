/**
*******************************************
*										  *
*	+ Created By: Marcos alves            *
*									      *
*	+ Created Date: May 3th, 2016	      *
*									      *
*	+ Last Modified: May  6th, 2016	      *
*									  	  *
*	+ Title: main.cpp					  *
*									      *
*	+ Email: marcos.alves@cc.ci.ufpb.br   *
*										  *
******************************************* **/

#include <iostream>
#include <exception>
#include <vector>
#include <thread>
#include "logger.hpp"
#include "socket.h"

void activity(Socket *s, long client) {
	std::string t = "Hi, connect ok!";
	s->send(client, t);
}

int main(int argc, char **argv) {
	
	Socket st{8080};

	int client = 0;

	try {

		st.bind();
		st.listen();
		std::vector<std::thread> threads;

		while(true) {
			client = st.accept();
			threads.push_back(std::thread(activity, &st, client));
		}

	} catch (std::exception& e) {

		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return client;
}
