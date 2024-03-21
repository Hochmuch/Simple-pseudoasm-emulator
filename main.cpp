#include <iostream>
#include "emulator/include/emulator.h"

int main(int argc, char *argv[]) {
    std::string path = argv[1];
    emulator::Emu emu;
    emu.execute(path);
    return 0;
}
