/**
*******************************************
*										  *
*	+ Created By: Marcos alves            *
*									      *
*	+ Created Date: May 4th, 2016	      *
*									      *
*	+ Last Modified: May  5th, 2016	      *
*									  	  *
*	+ Title: socket.h					  *
*									      *
*	+ Email: marcos.alves@cc.ci.ufpb.br   *
*										  *
******************************************* **/

#ifndef SOCKET_H
#define SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

#define BYTES 	1024

class Socket {
private:
	//data members
	struct sockaddr_in address;
	int prot;
	long server;

public:
	//enum
	enum Protocol {
		UDP = SOCK_STREAM,
		TCP = SOCK_DGRAM
	};
	//constructor
	Socket(unsigned int port, Protocol protocol);
	//destructor
	~Socket();
	//functions members
	long accept() const;
	void bind() const;
	void connect() const;
	int get_protocol() const;
	void listen() const;
	std::string receive(long description) const;
	void send(long description, size_t bytes) const;
};

#endif //SOCKET_H