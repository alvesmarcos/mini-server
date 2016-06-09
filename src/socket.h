// Created By: Marcos alves
// Created Date: May 4th, 2016	  
// Last Modified: May 7th, 2016	

#ifndef SOCKET_H
#define SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <exception>
#include <iostream>

#define BYTES 	10240

class Socket {
private:
	//data members
	struct sockaddr_in address;
	int server;

public:
	//constructor
	Socket(unsigned int port);
	//destructor
	~Socket();
	//functions members
	long accept() const;
	void bind() const;
	void close();
	void connect() const;
	void listen() const;
	std::string receive(long description) const; 
	void send(long description, std::string& buffer) const;
};

#endif //SOCKET_H