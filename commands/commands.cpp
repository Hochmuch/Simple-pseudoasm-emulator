#include "include/commands.h"

void commands::Operation::execute(const std::string &arg, memory::Memory &memoblock) {
}

commands::Operation::Operation(int val, memory::OperandType reg, std::string label) {

}

void commands::Begin::execute(const std::string &arg, memory::Memory &memoblock) {
    if (memoblock.is_started) {
        throw exceptions::PreprocessorError();
    }
    memoblock.is_started = true;
}

commands::Push::Push() = default;

void commands::Push::execute(const std::string &arg, memory::Memory &memoblock) {
    abort_if_not_started(memoblock);
    memoblock.data_stack.push(std::stoll(arg));
}


void commands::Pop::execute(const std::string &arg, memory::Memory &memoblock) {
    abort_if_not_started(memoblock);
    memoblock.data_stack.pop();
}

void commands::Pushr::execute(const std::string &arg, memory::Memory &memoblock) {
    abort_if_not_started(memoblock);
    memoblock.data_stack.push(memoblock.registers[memory::registers.at(arg)]);

}

void commands::Popr::execute(const std::string &arg, memory::Memory &memoblock) {
    abort_if_not_started(memoblock);
    memoblock.registers[memory::registers.at(arg)] = memoblock.data_stack.getTop();
    memoblock.data_stack.pop();
    // КОНКРЕТНО
}

void commands::Add::execute(const std::string &arg, memory::Memory &memoblock) {
    abort_if_not_started(memoblock);
    long long val1 = memoblock.data_stack.getTop();
    memoblock.data_stack.pop();
    long long val2 = memoblock.data_stack.getTop();
    memoblock.data_stack.pop();
    memoblock.data_stack.push(val1 + val2);
}

void commands::Sub::execute(const std::string &arg, memory::Memory &memoblock) {
    abort_if_not_started(memoblock);
    long long val1 = memoblock.data_stack.getTop();
    memoblock.data_stack.pop();
    long long val2 = memoblock.data_stack.getTop();
    memoblock.data_stack.pop();
    memoblock.data_stack.push(val2 - val1);
}

void commands::Mul::execute(const std::string &arg, memory::Memory &memoblock) {
    abort_if_not_started(memoblock);
    long long val1 = memoblock.data_stack.getTop();
    memoblock.data_stack.pop();
    long long val2 = memoblock.data_stack.getTop();
    memoblock.data_stack.pop();
    memoblock.data_stack.push(val2 * val1);
}

void commands::Div::execute(const std::string &arg, memory::Memory &memoblock) {
    abort_if_not_started(memoblock);
    long long val1 = memoblock.data_stack.getTop();
    memoblock.data_stack.pop();
    long long val2 = memoblock.data_stack.getTop();
    memoblock.data_stack.pop();
    memoblock.data_stack.push(val2 / val1);
}

void commands::Out::execute(const std::string &arg, memory::Memory &memoblock) {
    abort_if_not_started(memoblock);
    std::cout << memoblock.data_stack.getTop() << std::endl;
    memoblock.data_stack.pop();
}

void commands::In::execute(const std::string &arg, memory::Memory &memoblock) {
    abort_if_not_started(memoblock);
    long long val;
    std::cin >> val;
    memoblock.data_stack.push(val);
}

void commands::Label::execute(const std::string &arg, memory::Memory &memoblock) {

}

void commands::End::execute(const std::string &arg, memory::Memory &memoblock) {
    if (!memoblock.is_started) {
        throw exceptions::PreprocessorError();
    }
    memoblock.is_started = false;
}

void commands::abort_if_not_started(memory::Memory &memoblock) {
    if (!memoblock.is_started) {
        throw exceptions::PreprocessorError();
    }
}