// Created By: Marcos alves
// Created Date: Jun 4th, 2016	  
// Last Modified: Jun 11th, 2016	

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
	struct sockaddr_in address_client;
	int server;

public:
	//constructor
	Socket(unsigned int port);
	//destructor
	~Socket();
	//functions members
	int accept();
	void bind() const;
	void close();
	void connect() const;
	std::string get_ip() const;
	std::string get_client_ip() const;
	void listen() const;
	std::string receive(long description) const; 
	void send(long description, std::string& buffer) const;
};

#endif //SOCKET_H