#ifndef EMULATOR2_SERIALIZER_H
#define EMULATOR2_SERIALIZER_H

#include <iostream>
#include <fstream>
#include "../../exceptions/include/exceptions.h"


namespace serializing {

    enum class OperationCode {
        BEGIN,
        END,
        PUSH,
        POP,
        PUSHR,
        POPR,
        ADD,
        SUB,
        MUL,
        DIV,
        OUT,
        IN,
        JMP,
        JEQ,
        JNE,
        JA,
        JAE,
        JB,
        JBE,
        CALL,
        RET,
        LABEL
    };

    struct CommandToken {
        OperationCode command;
        std::string operand;
        CommandToken();
        CommandToken(OperationCode command, std::string &operand);
    };

    class Serializer {
    private:
        std::ofstream stream;
        std::string path;
    public:
        Serializer();
        Serializer(std::string &file_path);

        void exec(const CommandToken &token);

        void close();

    };

    class Deserializer {
    private:
        std::ifstream stream;
        std::string path;
    public:
        Deserializer();

        explicit Deserializer(std::string &file_path);

        CommandToken exec();

    };
}

#endif //EMULATOR2_SERIALIZER_H
