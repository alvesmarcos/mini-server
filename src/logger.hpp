/**
*******************************************
*										  *
*	+ Created By: Marcos alves            *
*									      *
*	+ Created Date: May 3th, 2016	      *
*									      *
*	+ Last Modified: May  4th, 2016	      *
*									  	  *
*	+ Title: logger.hpp					  *
*									      *
*	+ Email: marcos.alves@cc.ci.ufpb.br   *
*										  *
******************************************* **/

#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <iostream>
#include <string>
#include <mutex>

class Logger {
private:
	//constructor default
	Logger();

	//data members
	static Logger *instance;
	std::mutex mutex;
	std::ofstream output;

	//class internal
	class Cleanup { public: ~Cleanup(); };

public:
	//copy constructor delete
	Logger(const Logger& copy) = delete;
	//destructor
    ~Logger();
	
	//enum
	enum Flags {
		DEBUG,
		ERROR,
		INFO,
		WARNING
	};
	
	//member function
	static Logger& get_instance();
	void sys_register(std::string& message, Flags level); 
	std::string sys_time() const;
};

#endif //LOGGER_H