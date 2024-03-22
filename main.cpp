#include <iostream>
#include "emulator/include/emulator.h"

int main(int argc, char *argv[]) {
    std::string path = argv[1], serial_path = argv[2];
    emulator::Emu emu;
    emu.serialize(path, serial_path);
    emu.deserialize(serial_path);
    return 0;
}
