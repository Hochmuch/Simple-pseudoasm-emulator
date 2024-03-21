#include "include/parser.h"


std::pair<std::string, std::string> parsing::Parser::parse_line(const std::string &line) {
    std::pair<std::string, std::string> parsed_line = {"", ""};
    bool writing_to_opcode = true;
    for (char i: line) {
        if (isalpha(i) && writing_to_opcode) {
            parsed_line.first += i;
        } else if (i == ' ' && writing_to_opcode) {
            writing_to_opcode = false;
        } else if (isalpha(i) && !writing_to_opcode && parsed_line.first != "PUSH") {
            parsed_line.second += i;
        } else if ((isdigit(i) || i == '-' && parsed_line.second.empty()) && !writing_to_opcode && parsed_line.first == "PUSH") {
            parsed_line.second += i;
        } else {
            throw exceptions::ParserError();
        }
    }
    if (parsing::operation_codes.find(parsed_line.first) == parsing::operation_codes.end()) {
        throw exceptions::ParserError();
    }
    if ((parsed_line.first == "PUSHR" || parsed_line.first == "POPR") &&
        memory::registers.find(parsed_line.second) == memory::registers.end()) {
        throw exceptions::ParserError();
    }
    if (parsed_line.first == "PUSH" && !Parser::is_number(parsed_line.second)) {
        throw exceptions::ParserError();
    }
    return parsed_line;
}

parsing::CommandToken parsing::Parser::string_to_token(std::pair<std::string, std::string> string_data) {
    parsing::OperationCode command = parsing::operation_codes[string_data.first];
    std::string arg = string_data.second;
    parsing::CommandToken result(command, arg);
    return result;
}

std::vector<parsing::CommandToken> parsing::Parser::readfile(std::string &path) {
    std::vector<parsing::CommandToken> parsed_file;
    file = std::ifstream(path);
    std::string line;
    while (std::getline(file, line)) {
        std::pair<std::string, std::string> parsed_line = parse_line(line);
        parsed_file.push_back(Parser::string_to_token(parsed_line));
    }
    file.close();
    return parsed_file;
}

bool parsing::Parser::is_number(const std::string &s) {
    long long count = 0;
    for (auto i : s) {
        count += isdigit(i);
    }
    return (count == s.size()) || (s[0] == '-' && count == s.size() - 1);
}

parsing::CommandToken::CommandToken(parsing::OperationCode command, std::string &operand) {
    this->command = command;
    this->operand = operand;
}

std::unordered_map<parsing::OperationCode, std::shared_ptr<commands::Operation>> parsing::token_to_class =
        {
                {parsing::OperationCode::PUSH,  std::make_shared<commands::Push>()},
                {parsing::OperationCode::POP,   std::make_shared<commands::Pop>()},
                {parsing::OperationCode::BEGIN, std::make_shared<commands::Begin>()},
                {parsing::OperationCode::END,   std::make_shared<commands::End>()},
                {parsing::OperationCode::PUSHR, std::make_shared<commands::Pushr>()},
                {parsing::OperationCode::POPR,  std::make_shared<commands::Popr>()},
                {parsing::OperationCode::ADD,   std::make_shared<commands::Add>()},
                {parsing::OperationCode::SUB,   std::make_shared<commands::Sub>()},
                {parsing::OperationCode::MUL,   std::make_shared<commands::Mul>()},
                {parsing::OperationCode::DIV,   std::make_shared<commands::Div>()},
                {parsing::OperationCode::OUT,   std::make_shared<commands::Out>()},
                {parsing::OperationCode::IN,    std::make_shared<commands::In>()},
                {parsing::OperationCode::LABEL, std::make_shared<commands::Label>()}
        };

std::unordered_map<std::string, parsing::OperationCode> parsing::operation_codes = {
        {"PUSH",  parsing::OperationCode::PUSH},
        {"POP",   parsing::OperationCode::POP},
        {"PUSHR", parsing::OperationCode::PUSHR},
        {"POPR",  parsing::OperationCode::POPR},
        {"ADD",   parsing::OperationCode::ADD},
        {"SUB",   parsing::OperationCode::SUB},
        {"MUL",   parsing::OperationCode::MUL},
        {"DIV",   parsing::OperationCode::DIV},
        {"OUT",   parsing::OperationCode::OUT},
        {"IN",    parsing::OperationCode::IN},
        {"BEGIN", parsing::OperationCode::BEGIN},
        {"END",   parsing::OperationCode::END},
        {"JMP",   parsing::OperationCode::JMP},
        {"JEQ",   parsing::OperationCode::JEQ},
        {"JNE",   parsing::OperationCode::JNE},
        {"JA",    parsing::OperationCode::JA},
        {"JAE",   parsing::OperationCode::JAE},
        {"JB",    parsing::OperationCode::JB},
        {"JBE",   parsing::OperationCode::JBE},
        {"CALL",  parsing::OperationCode::CALL},
        {"RET",   parsing::OperationCode::RET},
        {"LABEL", parsing::OperationCode::LABEL}
};