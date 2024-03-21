#pragma once

#include <unordered_map>
#include <string>

#include "../../stack/stack.h"

namespace memory {

    enum class OperandType {
        AX, BX, CX, DX, SP, BP, SI, DI, PC, NONE
    };

    const std::unordered_map<std::string, memory::OperandType> registers =
            {
                    {"AX", memory::OperandType::AX},
                    {"BX", memory::OperandType::BX},
                    {"CX", memory::OperandType::CX},
                    {"DX", memory::OperandType::DX},
                    {"SP", memory::OperandType::SP},
                    {"BP", memory::OperandType::BP},
                    {"SI", memory::OperandType::SI},
                    {"DI", memory::OperandType::DI},
                    {"PC", memory::OperandType::PC},
                    {"NONE", memory::OperandType::NONE},
            };

    struct Memory {

        bool is_started = false;

        std::unordered_map<OperandType, long long> registers = {
                {OperandType::AX, 0},
                {OperandType::BX, 0},
                {OperandType::CX, 0},
                {OperandType::DX, 0},
                {OperandType::SI, 0},
                {OperandType::SP, 0},
                {OperandType::BP, 0},
                {OperandType::PC, 0},
                {OperandType::DI, 0},
        };

        stack::Stack<long long> data_stack;
    };

}
