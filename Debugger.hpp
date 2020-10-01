// Ensure this file is only included once
#pragma once
#ifndef _LWS_DEBUGGER_
#define _LWS_DEBUGGER_
#include <iostream>
#include <fstream>
#include <string>
namespace lws { // part of the ongoing lwslib project
namespace dbg {
class Debugger {
	public:
		enum DebugFlag { // Allows us to know how to process input. We OR these together to set values in an int
			VERBOSE_LOW 	= 1,	// Only print errors and messages with high importance
			VERBOSE_MEDIUM	= 2,	// Print messages with priority MEDIUM or LOW
			VERBOSE_HIGH	= 4,	// Print all messages
			USING_FILES		= 8,	// Are we using file streams for output? Internal-only.
			COLOR_SUPPORT	= 16	// Does this stream support coloring using terminal characters? Cannot be set with USING_FILES flag.
		};
		Debugger(											// Constructor using ostreams
				const std::string& _originCls, 				// name of the originating class 
				std::ostream& _stdoutput=std::cout,			// The output stream for standard logging 
				std::ostream& _erroutput=std::cerr,			// The output stream for error messages 
				const std::initializer_list<DebugFlag>
				_default={DebugFlag::VERBOSE_MEDIUM} 		// array of flags to set at initialization
		);
		Debugger(											// Constuctor using fstreams
				const std::string& _originCls,				// name of the originating class
				const std::string& _stdfile,				// filename for standard output file
				const std::string& _errfile,				// filename for error output file (set to "" if not needed)
				const std::initializer_list<DebugFlag>
				_default={DebugFlag::VERBOSE_MEDIUM} 		// array of flags to set at initialization
		);
		~Debugger();										// If we are using files, we want to close them.
		std::ostream& operator<<(const std::string& msg);
		std::ostream& operator<<(const char* msg);
		std::ostream& operator<<(const int& msg);
		std::ostream& operator<<(const double& msg);
		std::ostream& operator<<(const float& msg);
		std::ostream& operator<<(std::ostream& os);
		void setFlag(const DebugFlag& nflag);
	protected: 									// use protected instead of private; if the user wants to inherit from this and change our state, fine by me.
		int m_flags;
		std::string m_originCls;
		static std::ostream* m_outputStream; 	// we want this staic, so everything gets written to a specific place.
		static std::ostream* m_errStream;		// we have to use pointers as the copy-constructor is protected
		static std::ifstream m_fileStd;			// if the user is using files, then we want to manage these ourselves.
		static std::ifstream m_fileErr;			// if the user is using files, then we want to manage these ourselves.
		static std::string m_fileStdName;		// std::fstream objects do not store the file name; we may want to
		static std::string m_fileErrName;
};
}
namespace err { // custom errors
struct BadStream : public std::exception {
	const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};
struct CannotSetFlag : public std::exception {
	const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};
struct FileError : public std::exception {
	const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};
}
}
#endif