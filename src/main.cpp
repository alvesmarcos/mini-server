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
#include "logger.hpp"
#include "socket.h"

int main(int argc, char **argv) {
	
	Socket st{8080};

	int client = 0;

	st.bind();
	st.listen();

	while(true)
		client = st.accept();

	return client;
}
