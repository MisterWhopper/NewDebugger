# NewDebugger
A Custom Debugger for C++

This `Debugger` object will allow for more verbose logging inside objects. Can write to any output, including filestreams.

This `Debugger` class is meant to be similar to the `dbg()` in the fantastic project [SerenityOS](https://github.com/SerenityOS/serenity/). 

## Usage

```c++
class userDefined {
    private:
        lws::dbg::Debugger dbg;
    public:
        userDefined() {
            dbg = lws::dbg::Debugger("userDefined");
        }
};