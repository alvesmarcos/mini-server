// Created By: Marcos alves
// Created Date: Jun 3th, 2016	  
// Last Modified: Jun 11th, 2016	      

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
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

#endif //LOGGER_HPP