// This file is just for demonstrating methods of the Debugger object as it develops

#include "../Debugger.hpp"

using namespace lws;

int main() {
    // Create a debugger instance
    dbg::Debugger dbg("main",{dbg::Debugger::DebugFlag::VERBOSE_HIGH});
}