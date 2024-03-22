#include "include/emulator.h"

void emulator::Emu::serialize(std::string &read_path, std::string &write_path) {
    parser.readfile(read_path, write_path);
}

void emulator::Emu::deserialize(std::string &serial_file) {
    this->deserializer = serializing::Deserializer(serial_file);
    std::vector<serializing::CommandToken> commands;
    while (true) {
        serializing::CommandToken token = deserializer.exec();
        commands.push_back(token);
        if (token.command == serializing::OperationCode::END) {
            break;
        }
    }
    this->preprocessor.find_functions(commands);
    this->preprocessor.calculate(commands, emulator::Emu::memoblock);
}
