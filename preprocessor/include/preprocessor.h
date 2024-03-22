#ifndef EMULATOR2_PREPROCESSOR_H
#define EMULATOR2_PREPROCESSOR_H

#include "../../parser/include/parser.h"
#include "../../serializer/include/serializer.h"

namespace preprocessing {

    extern std::vector<serializing::OperationCode> func_exit_commands;

    class Preprocessor {
    private:
        std::vector<serializing::CommandToken> tokenized_program;
        std::unordered_map<std::string, long long> label_index;
        std::unordered_map<std::string, std::pair<long long, long long>> functions;
        serializing::Serializer serializer;
    public:
        void find_functions(std::vector<serializing::CommandToken> &program);

        void calculate(std::vector<serializing::CommandToken> &program, memory::Memory &memoblock);

        void run_function(std::vector<serializing::CommandToken> &program, std::string &function,
                          memory::Memory &memoblock);

        void run_instruction(std::vector<serializing::CommandToken> &program,
                             long long int &index, bool is_function,
                             memory::Memory &memoblock);

        void serialize(std::string &serial_file, std::vector<serializing::CommandToken> &program);
    };
}


#endif //EMULATOR2_PREPROCESSOR_H
