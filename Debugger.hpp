#pragma once
#ifndef _LWS_DEBUGGER_
#define _LWS_DEBUGGER_
#include <iostream>
#include <fstream>
#include <string>
class Debugger {
	public:
		enum DebugLevel { // Allows us to know how verbose a debug statement is.
			LOW,
			MEDIUM,
			HIGH
		};
		Debugger();
		Debugger(const std::string& _originCls, 
				DebugLevel _default=DebugLevel::MEDIUM,
				std::ostream& _output=std::cout);
		Debugger();
		std::ostream& operator<<(const std::string& msg);
		std::ostream& operator<<(const char* msg);
		std::ostream& operator<<(const int& msg);
		std::ostream& operator<<(const double& msg);
		std::ostream& operator<<(const float& msg);
		std::ostream& operator<<(ostream& os);
	private:
		DebugLevel defaultLevel;
		std::string originCls;
};
#endif
