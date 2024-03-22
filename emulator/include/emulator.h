#ifndef EMULATOR2_EMULATOR_H
#define EMULATOR2_EMULATOR_H

#include "../../preprocessor/include/preprocessor.h"
#include "../../serializer/include/serializer.h"

namespace emulator {

    class Emu {
    private:
        parsing::Parser parser;
        preprocessing::Preprocessor preprocessor;
        std::vector<commands::Operation> program;
        memory::Memory memoblock;
        serializing::Deserializer deserializer;
    public:
        void serialize(std::string &read_path, std::string &write_path);
        void deserialize(std::string &serial_file);
    };

}


#endif //EMULATOR2_EMULATOR_H
