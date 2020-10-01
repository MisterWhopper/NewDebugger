#include "Debugger.hpp"

namespace lws {
namespace dbg {

Debugger::Debugger(const std::string& _originCls, const DebugFlag* _default=nullptr, std::ostream& _output, std::ostream& _erroutput=std::cerr) {
    originCls = _originCls;
    if(_default) {
        // if this segfaults, blame: https://www.tutorialspoint.com/how-do-i-find-the-length-of-an-array-in-c-cplusplus
        size_t arrSize = (size_t)(*(&_default + 1) - _default);
        for(size_t i = 0; i < arrSize; ++i) {
            try {
                setFlag(_default[i]);
            } catch (err::CannotSetFlag err) {
                continue; // we just don't want to set this flag.
            }
        }
    }
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