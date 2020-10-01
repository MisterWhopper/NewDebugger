#include "Debugger.hpp"

namespace lws {
namespace dbg {

Debugger::Debugger(const std::string& _originCls, std::ostream& _output, std::ostream& _erroutput, const std::initializer_list<DebugFlag> _default) {
    m_originCls = _originCls;
    if(_default.size() > 0) {
        for(auto flag : _default) {
            try {
                setFlag(flag);
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
                setFlag(flag);
            } catch (err::CannotSetFlag err) {
                continue; // we just don't want to set this flag.
            }
        }
    }  // if the user has no flags set, there will be no output, which is on them.
    setFlag(USING_FILES); // we are using files, so when we use the << operator we know to use these and not the ostreams
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

#ifdef DEBUG // The actual implementation; we only want these if the user wants to debug.

#else

#endif

}
namespace err {

const char* BadStream::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW {
    return "Could not open output stream!"; // FIXME: Not verbose enough (ironic)
}

}
}