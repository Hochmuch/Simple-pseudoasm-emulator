#ifndef EMULATOR2_PREPROCESSOR_H
#define EMULATOR2_PREPROCESSOR_H

#include "../../parser/include/parser.h"

namespace preprocessing {

    class Preprocessor {
    private:
        std::vector<parsing::CommandToken> tokenized_program;
        std::unordered_map<std::string, long long> label_index;
        std::unordered_map<std::string, long long> functions;
        bool is_function_run = false;
    public:
        void find_functions(std::vector<parsing::CommandToken> &program);

        void calculate(std::vector<parsing::CommandToken> &program, memory::Memory &memoblock);

        void run_function(std::vector<parsing::CommandToken> &program, long long &start_function_index,
                          memory::Memory &memoblock, long long leave);

        void run_instruction(std::vector<parsing::CommandToken> &program,
                             long long int &index, bool is_function,
                             memory::Memory &memoblock);
    };
}


#endif //EMULATOR2_PREPROCESSOR_H
