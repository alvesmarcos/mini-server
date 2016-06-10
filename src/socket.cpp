// Created By: Marcos alves
// Created Date: May 4th, 2016	  
// Last Modified: May 7th, 2016	

#include "socket.h"

Socket::Socket(unsigned int port) {
	address = {AF_INET, htons(port), (INADDR_ANY), 0};
	
	server = socket(AF_INET, SOCK_STREAM, 0);
	if(server == -1)
		throw std::runtime_error("Error socket!");
} 

Socket::~Socket() { close(); }

int Socket::accept(void) const {
	socklen_t size = sizeof(address_client);
	int acc = ::accept(server, const_cast<struct sockaddr*>(reinterpret_cast<struct sockaddr const*>
	 				  (&address_client)), &size);
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

std::string Socket::get_ip(void) const {
	char* ip = inet_ntoa(address_client.sin_addr);
	return static_cast<std::string>(ip);
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

 	std::string copy{ buffer, static_cast<size_t>(err) };

 	return copy;
}

void Socket::send(long description, std::string& buffer) const {
	int err = write(description, &buffer[0], buffer.length());

 	if(err == -1)
 		throw std::runtime_error("Error send!"); 	
}
