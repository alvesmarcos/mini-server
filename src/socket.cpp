/**
*******************************************
*										  *
*	+ Created By: Marcos alves            *
*									      *
*	+ Created Date: May 4th, 2016	      *
*									      *
*	+ Last Modified: May  6th, 2016	      *
*									  	  *
*	+ Title: socket.cpp					  *
*									      *
*	+ Email: marcos.alves@cc.ci.ufpb.br   *
*										  *
******************************************* **/

#include "socket.h"

Socket::Socket(unsigned int port) {
	address = {AF_INET, htons(port), (INADDR_ANY), 0};
	
	server = socket(AF_INET, SOCK_STREAM, 0);
	if(server == -1)
		throw std::runtime_error("Error socket!");
} 

Socket::~Socket() { close(); }

long Socket::accept(void) const {
	long acc = ::accept(server, 0, 0);
	return acc;
}

void Socket::bind(void) const {
	int err = ::bind(server, reinterpret_cast<const struct sockaddr*> (&address),
					sizeof(address));
	if(err!=0)
		throw std::runtime_error("Error bind!");  
}

void Socket::close(void) {
	int err = ::close(server);

	if(err == -1)
		throw std::runtime_error("Error close socket!"); 	
}

void Socket::connect(void) const {
	int err = ::connect(server, reinterpret_cast<const struct sockaddr*>(&address), 
					   sizeof(address));
	if(err)
		throw std::runtime_error("Error connect!"); 	
}

void Socket::listen(void) const {
	int err = ::listen(server, 20);
	if(err)
		throw std::runtime_error("Socket inactive!");  		
}

std::string Socket::receive(long description) const {
	char buffer[BYTES];
	int err = read(description, buffer, BYTES);

 	if(err == -1)
 		throw std::runtime_error("Error receive!");

 	return static_cast<std::string>(buffer);
}

void Socket::send(long description, std::string& buffer) const {
	int err = write(description, &buffer[0], buffer.length());

 	if(err == -1)
 		throw std::runtime_error("Error send!"); 	
}
