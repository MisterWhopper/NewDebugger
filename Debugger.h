// Ensure this file is only included once
#pragma once
#ifndef _LWS_DEBUGGER_
#define _LWS_DEBUGGER_

#include "DebuggerErrors.h"

#include <fstream>
#include <iostream>
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

		enum MessagePriority { // Set the priority of an individual message
			LOW 	= 0,
			MED 	= 1,
			HIGH 	= 2
		};

		struct DebugMessage { // construct for a message written to the debugger
			public:
				DebugMessage(const std::string& originator, const std::string& msg, const MessagePriority& priority=LOW) {
					m_originator = originator;
					m_msg = msg;
					m_priority = priority;
				};
				DebugMessage(const std::string& msg, const MessagePriority& priority=LOW, const std::string& originator=NULL) {
					m_originator = originator;
					m_msg = msg;
					m_priority = priority;
				};
				std::string origin() { return m_originator; };
				std::string msg() { return m_msg; }
				MessagePriority priority() { return m_priority; }
			private:
				std::string m_originator = NULL;
				MessagePriority m_priority = LOW;
				std::string m_msg = NULL;
		};

		// Annotated constructors, purely for documentation's sake.

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

		Debugger::Debugger(const std::string& _originCls, std::ostream& _output, std::ostream& _erroutput, const std::initializer_list<DebugFlag> _default) {
			m_originCls = _originCls;
			if(_default.size() > 0) {
				for(auto flag : _default) {
					try {
						flipFlag(flag);
					} catch (err::CannotSetFlag err) {
						continue; // we just don't want to set this flag.
					}
				}
			}  // if the user has no flags set, there will be no output, which is on them.
			m_outputStream = &_output; // we have to indirectly use pointers, as the copy constructor via operator= is protected.
			m_errStream = &_erroutput;
			if(!m_outputStream || m_outputStream->bad() || !m_errStream || m_errStream->bad()) { // did any of the streams fail?
				throw err::BadStream();
			}
		}

		Debugger::Debugger(const std::string& _originCls, const std::string& _stdfile, const std::string& _errfile, const std::initializer_list<DebugFlag> _default) {
			m_originCls = _originCls;
			if(_default.size() > 0) {
				for(auto flag : _default) {
					try {
						flipFlag(flag);
					} catch (err::CannotSetFlag err) {
						continue; // we just don't want to set this flag.
					}
				}
			}  // if the user has no flags set, there will be no output, which is on them.
			flipFlag(USING_FILES); // we are using files, so when we use the << operator we know to use these and not the ostreams
			m_outputStream = nullptr; // make sure we really can't use these
			m_errStream = nullptr;
			m_fileStd.open(_stdfile);
			if(m_fileStd.fail()) {
				throw err::FileError();
			} else {
				m_fileStdName = std::string(_stdfile);
			}
			m_fileErr.open(_errfile);
			if(m_fileErr.fail()) {
				throw err::FileError();
			} else {
				m_fileErrName = std::string(_errfile);
			}
			if(true) {
				throw err::BadStream();
			}
		}
		Debugger::~Debugger() {         // Close files we may have open
			if(m_fileStd.is_open()) {
				m_fileStd.close();
			}
			if(m_fileErr.is_open()) {
				m_fileErr.close();
			}
		}
		std::ostream& operator<<(const std::string& msg);
		std::ostream& operator<<(const char* msg);
		std::ostream& operator<<(const int& msg);
		std::ostream& operator<<(const double& msg);
		std::ostream& operator<<(const float& msg);
		std::ostream& operator<<(std::ostream& os);

		// Are these functions below strictly necessary? Maybe not, but doing it was a nice bitwise exercise

		// set/unset a flag 
		void flipFlag(const DebugFlag& nflag) {
			m_flags ^= nflag;
		};

		// set a flag
		void setFlag(const DebugFlag& nflag) {
			m_flags |= nflag;
		}

		// unset a flag
		void unsetFlag(const DebugFlag& nflag) {
			m_flags &= ~nflag;
		}

		bool checkFlag(const DebugFlag& nflag) {
			return (m_flags & nflag) != 0;
		}
	protected: 										// use protected instead of private; if the user wants to inherit from this and change our state, fine by me.
		int m_flags;								// flags to change the behavior of the logging system
		std::string m_originCls;					// specifies the class that this message originiated from
		static std::ostream* m_outputStream; 		// we want this staic, so everything gets written to a specific place.
		static std::ostream* m_errStream;			// we have to use pointers as the copy-constructor is protected
		static std::ifstream m_fileStd;				// if the user is using files, then we want to manage these ourselves.
		static std::ifstream m_fileErr;				// if the user is using files, then we want to manage these ourselves.
		static std::string m_fileStdName;			// std::fstream objects do not store the file name; we may want to
		static std::string m_fileErrName;
};
}
}
#endif