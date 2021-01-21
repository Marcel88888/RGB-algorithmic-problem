
#ifndef RGB_ALGORITHMIC_PROBLEM_COMMANDLINEARGUMENTSPARSING_H
#define RGB_ALGORITHMIC_PROBLEM_COMMANDLINEARGUMENTSPARSING_H

#include <functional>   // std::function
#include <iostream>     // std::cout, std::endl
#include <map>          // std::map
#include <memory>       // std::unique_ptr
#include <string>       // std::string
#include <sstream>      // std::stringstream
#include <string_view>  // std::string_view
#include <variant>      // std::variant
#include <vector>       // std::vector

using std::function;
using std::cout, std::endl;
using std::map;
using std::unique_ptr;
using std::string;
using std::stringstream;
using std::string_view;
using std::variant;
using std::vector;

template<class Opts>
struct CmdOpts : Opts {
    using MyProp = std::variant<string Opts::*, int Opts::*, double Opts::*, bool Opts::*>;
    using MyArgPair = std::pair<string, MyProp>;

    ~CmdOpts() = default;

    Opts parse(int argc, const char *argv[]) {
        vector<string_view> vargv(argv, argv + argc);
        for (int idx = 0; idx < argc; ++idx)
            for (auto &cbk : callbacks)
                cbk.second(idx, vargv);

        return static_cast<Opts>(*this);
    }

    static unique_ptr<CmdOpts> Create(std::initializer_list<MyArgPair> args) {
        auto cmdOpts = unique_ptr<CmdOpts>(new CmdOpts());
        for (const auto &customPair : args) cmdOpts->register_callback(customPair);
        return cmdOpts;
    }

    CmdOpts(const CmdOpts &) = delete;

    CmdOpts(CmdOpts &&) = delete;

    CmdOpts &operator=(const CmdOpts &) = delete;

    CmdOpts &operator=(CmdOpts &&) = delete;


private:
    using callback_t = function<void(int, const vector<string_view> &)>;
    map<string, callback_t> callbacks;

    CmdOpts() = default;

    auto register_callback(const string &name, MyProp prop) {
        callbacks[name] = [this, name, prop](int idx, const vector<string_view> &argv) {
            if (argv[idx] == name) {
                visit(
                        [this, idx, &argv](auto &&arg) {
                            if (idx < (int) argv.size() - 1) {
                                stringstream value;
                                value << argv[idx + 1];
                                value >> this->*arg;
                            }
                        },
                        prop);
            }
        };
    };

    auto register_callback(MyArgPair p) { return register_callback(p.first, p.second); }
};


#endif //RGB_ALGORITHMIC_PROBLEM_COMMANDLINEARGUMENTSPARSING_H
