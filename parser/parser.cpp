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

serializing::CommandToken parsing::Parser::string_to_token(std::pair<std::string, std::string> string_data) {
    serializing::OperationCode command = parsing::operation_codes[string_data.first];
    std::string arg = string_data.second;
    serializing::CommandToken result(command, arg);
    return result;
}

void parsing::Parser::readfile(std::string &read_path, std::string &write_path) {
    this->serializer = serializing::Serializer(write_path);
    std::vector<serializing::CommandToken> parsed_file;
    file = std::ifstream(read_path);
    std::string line;
    while (std::getline(file, line)) {
        std::pair<std::string, std::string> parsed_line = parse_line(line);
        serializer.exec(Parser::string_to_token(parsed_line));
        //parsed_file.push_back(Parser::string_to_token(parsed_line));
    }
    file.close();
    this->serializer.close();
    //return parsed_file;
}

bool parsing::Parser::is_number(const std::string &s) {
    long long count = 0;
    for (auto i : s) {
        count += isdigit(i);
    }
    return (count == s.size()) || (s[0] == '-' && count == s.size() - 1);
}

serializing::CommandToken::CommandToken(serializing::OperationCode command, std::string &operand) {
    this->command = command;
    this->operand = operand;
}

serializing::CommandToken::CommandToken() = default;

std::unordered_map<serializing::OperationCode, std::shared_ptr<commands::Operation>> parsing::token_to_class =
        {
                {serializing::OperationCode::PUSH,  std::make_shared<commands::Push>()},
                {serializing::OperationCode::POP,   std::make_shared<commands::Pop>()},
                {serializing::OperationCode::BEGIN, std::make_shared<commands::Begin>()},
                {serializing::OperationCode::END,   std::make_shared<commands::End>()},
                {serializing::OperationCode::PUSHR, std::make_shared<commands::Pushr>()},
                {serializing::OperationCode::POPR,  std::make_shared<commands::Popr>()},
                {serializing::OperationCode::ADD,   std::make_shared<commands::Add>()},
                {serializing::OperationCode::SUB,   std::make_shared<commands::Sub>()},
                {serializing::OperationCode::MUL,   std::make_shared<commands::Mul>()},
                {serializing::OperationCode::DIV,   std::make_shared<commands::Div>()},
                {serializing::OperationCode::OUT,   std::make_shared<commands::Out>()},
                {serializing::OperationCode::IN,    std::make_shared<commands::In>()},
                {serializing::OperationCode::LABEL, std::make_shared<commands::Label>()}
        };

std::unordered_map<std::string, serializing::OperationCode> parsing::operation_codes = {
        {"PUSH",  serializing::OperationCode::PUSH},
        {"POP",   serializing::OperationCode::POP},
        {"PUSHR", serializing::OperationCode::PUSHR},
        {"POPR",  serializing::OperationCode::POPR},
        {"ADD",   serializing::OperationCode::ADD},
        {"SUB",   serializing::OperationCode::SUB},
        {"MUL",   serializing::OperationCode::MUL},
        {"DIV",   serializing::OperationCode::DIV},
        {"OUT",   serializing::OperationCode::OUT},
        {"IN",    serializing::OperationCode::IN},
        {"BEGIN", serializing::OperationCode::BEGIN},
        {"END",   serializing::OperationCode::END},
        {"JMP",   serializing::OperationCode::JMP},
        {"JEQ",   serializing::OperationCode::JEQ},
        {"JNE",   serializing::OperationCode::JNE},
        {"JA",    serializing::OperationCode::JA},
        {"JAE",   serializing::OperationCode::JAE},
        {"JB",    serializing::OperationCode::JB},
        {"JBE",   serializing::OperationCode::JBE},
        {"CALL",  serializing::OperationCode::CALL},
        {"RET",   serializing::OperationCode::RET},
        {"LABEL", serializing::OperationCode::LABEL}
};