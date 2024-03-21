#ifndef EMULATOR2_EMULATOR_H
#define EMULATOR2_EMULATOR_H

#include "../../preprocessor/include/preprocessor.h"

namespace emulator {

    class Emu {
    private:
        parsing::Parser parser;
        preprocessing::Preprocessor preprocessor;
        std::vector<commands::Operation> program;
        memory::Memory memoblock;
    public:
        void execute(std::string &path);
    };

}


#endif //EMULATOR2_EMULATOR_H
