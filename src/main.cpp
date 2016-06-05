/**
*******************************************
*										  *
*	+ Created By: Marcos alves            *
*									      *
*	+ Created Date: May 3th, 2016	      *
*									      *
*	+ Last Modified: May  4th, 2016	      *
*									  	  *
*	+ Title: main.cpp					  *
*									      *
*	+ Email: marcos.alves@cc.ci.ufpb.br   *
*										  *
******************************************* **/

#include <iostream>
#include "logger.hpp"

int main(int argc, char **argv) {

	std::string t = "Test ok!";
	
	Logger::get_instance().sys_register(t, Logger::INFO);

	return 0;
}
