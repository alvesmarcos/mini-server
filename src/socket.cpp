/**
*******************************************
*										  *
*	+ Created By: Marcos alves            *
*									      *
*	+ Created Date: May 4th, 2016	      *
*									      *
*	+ Last Modified: May  5th, 2016	      *
*									  	  *
*	+ Title: socket.cpp					  *
*									      *
*	+ Email: marcos.alves@cc.ci.ufpb.br   *
*										  *
******************************************* **/

#include "socket.h"

Socket::Socket(unsigned int port, Protocol protocol) {
	address = {AF_INET, htons(port), INADDR_ANY, 0};

	switch(protocol){
		case UDP: prot = SOCK_STREAM; break;
		case TCP: prot = SOCK_DGRAM;  break;
		default:  throw std::runtime_error("Invalid protocol!"); break;	
	}

	server = socket(PF_INET, prot, 0);
} 

Socket::~Socket() { /* unimplemented */ }

long Socket::accept(void) const {
	long acc = ::accept(server, 0, 0);
	return acc;
}

void Socket::bind(void) const {
	int bd = ::bind(server, reinterpret_cast<const struct sockaddr*> (&address),
					sizeof(address) != 0);
	if(!bd)
		throw std::runtime_error("Error bind!");  
}

void Socket::connect(void) const {
	int cn = ::connect(server, reinterpret_cast<const struct sockaddr*>(&address), 
					   sizeof(address) != 0);
	if(!cn)
		throw std::runtime_error("Error connect!"); 	
}

int Socket::get_protocol(void) const {
	return prot;
}

void Socket::listen(void) const {
	int ln = ::listen(server, 20);
	if(!ln)
		throw std::runtime_error("Socket inactive!");  		
}

std::string Socket::receive(long description) const {
	char buffer[BYTES];
	int err = 0;

	if(prot == SOCK_STREAM) 
 		err = recv(description, buffer, sizeof(buffer), 0);
 	else if(prot == SOCK_DGRAM)
 		err = read(description, buffer, sizeof(buffer));

 	if(err == -1)
 		throw std::runtime_error("Error receive!");

 	return static_cast<std::string>(buffer);
}

void Socket::send(long description, size_t bytes) const {
	char buffer[BYTES];
	int err = 0;

	if(prot == SOCK_STREAM)
		err = ::send(description, buffer, sizeof(buffer), 0);
	else if(prot == SOCK_DGRAM)
		err = write(description, buffer, sizeof(buffer));

 	if(err == -1)
 		throw std::runtime_error("Error send!"); 	
}
