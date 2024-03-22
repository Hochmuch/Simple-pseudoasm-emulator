#ifndef EMULATOR2_PARSER_H
#define EMULATOR2_PARSER_H

#include <fstream>
#include <vector>
#include <memory>

#include "../../commands/include/commands.h"
#include "../../serializer/include/serializer.h"

namespace parsing {

    extern std::unordered_map<std::string, serializing::OperationCode> operation_codes;
    extern std::unordered_map<serializing::OperationCode, std::shared_ptr<commands::Operation>> token_to_class;

    class Parser {
    private:
        std::ifstream file;
        serializing::Serializer serializer;
    public:
        void readfile(std::string &path, std::string &write_path);

        std::pair<std::string, std::string> parse_line(const std::string &line);

        bool is_number(const std::string &s);

        serializing::CommandToken string_to_token(std::pair<std::string, std::string>);
    };
}

#endif //EMULATOR2_PARSER_H
