#include "include/preprocessor.h"

std::vector<serializing::OperationCode> preprocessing::func_exit_commands = {serializing::OperationCode::RET,
                                                                             serializing::OperationCode::JMP,
                                                                             serializing::OperationCode::JEQ,
                                                                             serializing::OperationCode::JNE,
                                                                             serializing::OperationCode::JA,
                                                                             serializing::OperationCode::JAE,
                                                                             serializing::OperationCode::JB,
                                                                             serializing::OperationCode::JBE};

void preprocessing::Preprocessor::calculate(std::vector<serializing::CommandToken> &program, memory::Memory &memoblock) {
    long long index = 0;
    while (index < program.size()) {
        run_instruction(program, index, false, memoblock);
        index++;
    }
}

void preprocessing::Preprocessor::find_functions(std::vector<serializing::CommandToken> &program) {
    std::vector<std::string> labels;
    for (long long i = 0; i < program.size(); ++i) {
        if (program[i].command == serializing::OperationCode::LABEL) {
            this->label_index[program[i].operand] = i;
            labels.push_back(program[i].operand);
        } else if (program[i].command == serializing::OperationCode::RET) {
            this->functions[labels.back()] = {this->label_index[labels.back()], i};
        }
    }
}

void preprocessing::Preprocessor::run_function(std::vector<serializing::CommandToken> &program,
                                               std::string &function, memory::Memory &memoblock) {
    long long index = this->functions[function].first + 1;
    while (true) {
        run_instruction(program, index, true, memoblock);
        index++;
        if (index >= this->functions[function].second) {
            break;
        }
    }

}

void preprocessing::Preprocessor::run_instruction(std::vector<serializing::CommandToken> &program,
                                                  long long int &index,
                                                  bool is_function, memory::Memory &memoblock) {
    switch (program[index].command) {
        long long top1, top2;
        case serializing::OperationCode::JMP:
            index = this->label_index[program[index].operand];
            break;
        case serializing::OperationCode::JEQ:
            top1 = memoblock.data_stack.getTop();
            memoblock.data_stack.pop();
            top2 = memoblock.data_stack.getTop();
            memoblock.data_stack.push(top1);
            if (top1 == top2) {
                index = this->label_index[program[index].operand];
            }
            break;
        case serializing::OperationCode::JNE:
            top1 = memoblock.data_stack.getTop();
            memoblock.data_stack.pop();
            top2 = memoblock.data_stack.getTop();
            memoblock.data_stack.push(top1);
            if (top1 != top2) {
                index = this->label_index[program[index].operand];
            }
            break;
        case serializing::OperationCode::JA:
            top1 = memoblock.data_stack.getTop();
            memoblock.data_stack.pop();
            top2 = memoblock.data_stack.getTop();
            memoblock.data_stack.push(top1);
            if (top1 > top2) {
                index = this->label_index[program[index].operand];
            }
            break;
        case serializing::OperationCode::JAE:
            top1 = memoblock.data_stack.getTop();
            memoblock.data_stack.pop();
            top2 = memoblock.data_stack.getTop();
            memoblock.data_stack.push(top1);
            if (top1 >= top2) {
                index = this->label_index[program[index].operand];
            }
            break;
        case serializing::OperationCode::JB:
            top1 = memoblock.data_stack.getTop();
            memoblock.data_stack.pop();
            top2 = memoblock.data_stack.getTop();
            memoblock.data_stack.push(top1);
            if (top1 < top2) {
                index = this->label_index[program[index].operand];
            }
            break;
        case serializing::OperationCode::JBE:
            top1 = memoblock.data_stack.getTop();
            memoblock.data_stack.pop();
            top2 = memoblock.data_stack.getTop();
            memoblock.data_stack.push(top1);
            if (top1 > top2) {
                index = this->label_index[program[index].operand];
            }
            break;
        case serializing::OperationCode::CALL:
            this->run_function(program, program[index].operand, memoblock);
            break;
        case serializing::OperationCode::RET:
            if (is_function) {
                return;
            }
            break;
        case serializing::OperationCode::LABEL:
            if (this->functions.find(program[index].operand) != this->functions.end() && !is_function) {
                index = functions[program[index].operand].second;
            }
            break;
        default:
            parsing::token_to_class[program[index].command]->execute(program[index].operand, memoblock);
            break;
    }
}

void preprocessing::Preprocessor::serialize(std::string &serial_file, std::vector<serializing::CommandToken> &program) {

}
