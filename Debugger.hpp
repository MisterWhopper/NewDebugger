// Ensure this file is only included once
#pragma once
#ifndef _LWS_DEBUGGER_
#define _LWS_DEBUGGER_
#include <iostream>
#include <fstream>
#include <string>
namespace lws {
namespace dbg {
class Debugger {
	public:
		enum DebugLevel { // Allows us to know how verbose a debug statement is.
			LOW,
			MEDIUM,
			HIGH
		};
		Debugger(const std::string& _originCls, 
				DebugLevel _default=DebugLevel::MEDIUM,
				std::ostream& _stdoutput=std::cout,
				std::ostream& _erroutput=std::cerr);
		std::ostream& operator<<(const std::string& msg);
		std::ostream& operator<<(const char* msg);
		std::ostream& operator<<(const int& msg);
		std::ostream& operator<<(const double& msg);
		std::ostream& operator<<(const float& msg);
		std::ostream& operator<<(std::ostream& os);
	protected: // use protected instead of private; if the user wants to inherit from this and change our state, fine by me.
		DebugLevel defLevel;
		std::string originCls;
		static std::ostream* outputStream; // we want this staic, so everything gets written to a specific place.
		static std::ostream* errStream;
};
}
namespace err { // custom errors
struct BadStream : public std::exception {
	const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};
}
}
#endif