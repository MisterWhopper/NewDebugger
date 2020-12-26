#pragma once
#include <exception>
namespace lws {
namespace err { // custom errors
struct BadStream : public std::exception {
	const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
		return "Could not open output stream!"; // FIXME: Not verbose enough (ironic)
	}
};
struct CannotSetFlag : public std::exception {
	const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};
struct FileError : public std::exception {
	const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};
}
}