#include "Debugger.hpp"

namespace lws {
namespace dbg {

Debugger::Debugger(const std::string& _originCls, DebugLevel _default=DebugLevel::MEDIUM, std::ostream& _output, std::ostream& _erroutput=std::cerr) {
    originCls = _originCls;
    defLevel = _default;
    outputStream = &_output; // we have to indirectly use pointers, as the copy constructor via operator= is protected.
    errStream = &_erroutput;
    if(!outputStream || outputStream->bad() || !errStream || errStream->bad()) {
        throw err::BadStream();
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