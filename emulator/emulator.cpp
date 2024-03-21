#include "include/emulator.h"

void emulator::Emu::execute(std::string &path) {
    std::vector<parsing::CommandToken> commands = parser.readfile(path);
    this->preprocessor.find_functions(commands);
    this->preprocessor.calculate(commands, emulator::Emu::memoblock);
}
