#ifndef EMULATOR2_PARSER_H
#define EMULATOR2_PARSER_H

#include <fstream>
#include <vector>
#include <memory>

#include "../../commands/include/commands.h"

namespace parsing {

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
        parsing::OperationCode command;
        std::string operand;
        CommandToken(parsing::OperationCode command, std::string &operand);
    };

    extern std::unordered_map<std::string, OperationCode> operation_codes;
    extern std::unordered_map<parsing::OperationCode, std::shared_ptr<commands::Operation>> token_to_class;

    class Parser {
    private:
        std::ifstream file;
    public:
        std::vector<parsing::CommandToken> readfile(std::string &path);

        std::pair<std::string, std::string> parse_line(const std::string &line);

        bool is_number(const std::string &s);

        parsing::CommandToken string_to_token(std::pair<std::string, std::string>);
    };
}

#endif //EMULATOR2_PARSER_H
