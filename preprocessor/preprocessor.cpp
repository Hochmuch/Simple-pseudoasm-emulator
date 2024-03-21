#include "include/preprocessor.h"

void preprocessing::Preprocessor::calculate(std::vector<parsing::CommandToken> &program, memory::Memory &memoblock) {
    long long index = 0;
    while (index < program.size()) {
        run_instruction(program, index, false, memoblock);
        index++;
    }
    /*
    for (const auto &command: program) {
        if (parsing::token_to_class.find(command.command) != parsing::token_to_class.end()) {
            parsing::token_to_class[command.command]->execute(command.operand, memoblock);
        }
    }
     */
}

void preprocessing::Preprocessor::find_functions(std::vector<parsing::CommandToken> &program) {
    std::vector<std::string> labels;
    for (long long i = 0; i < program.size(); ++i) {
        if (program[i].command == parsing::OperationCode::LABEL) {
            this->label_index[program[i].operand] = i;
            labels.push_back(program[i].operand);
        } else if (program[i].command == parsing::OperationCode::RET) {
            this->functions[labels.back()] = i;
        }
    }
}

void preprocessing::Preprocessor::run_function(std::vector<parsing::CommandToken> &program,
                                               long long int &start_function_index, memory::Memory &memoblock,
                                               long long leave) {
    long long index = start_function_index + 1;
    while (program[index].command != parsing::OperationCode::RET) {
        run_instruction(program, index, true, memoblock);
        index++;
    }

}

void preprocessing::Preprocessor::run_instruction(std::vector<parsing::CommandToken> &program,
                                                  long long int &index,
                                                  bool is_function, memory::Memory &memoblock) {
    switch (program[index].command) {
        long long top1, top2;
        case parsing::OperationCode::JMP:
            index = this->label_index[program[index].operand];
            break;
        case parsing::OperationCode::JEQ:
            top1 = memoblock.data_stack.getTop();
            memoblock.data_stack.pop();
            top2 = memoblock.data_stack.getTop();
            memoblock.data_stack.push(top1);
            if (top1 == top2) {
                index = this->label_index[program[index].operand];
            }
            break;
        case parsing::OperationCode::JNE:
            top1 = memoblock.data_stack.getTop();
            memoblock.data_stack.pop();
            top2 = memoblock.data_stack.getTop();
            memoblock.data_stack.push(top1);
            if (top1 != top2) {
                index = this->label_index[program[index].operand];
            }
            break;
        case parsing::OperationCode::JA:
            top1 = memoblock.data_stack.getTop();
            memoblock.data_stack.pop();
            top2 = memoblock.data_stack.getTop();
            memoblock.data_stack.push(top1);
            if (top1 > top2) {
                index = this->label_index[program[index].operand];
            }
            break;
        case parsing::OperationCode::JAE:
            top1 = memoblock.data_stack.getTop();
            memoblock.data_stack.pop();
            top2 = memoblock.data_stack.getTop();
            memoblock.data_stack.push(top1);
            if (top1 >= top2) {
                index = this->label_index[program[index].operand];
            }
            break;
        case parsing::OperationCode::JB:
            top1 = memoblock.data_stack.getTop();
            memoblock.data_stack.pop();
            top2 = memoblock.data_stack.getTop();
            memoblock.data_stack.push(top1);
            if (top1 < top2) {
                index = this->label_index[program[index].operand];
            }
            break;
        case parsing::OperationCode::JBE:
            top1 = memoblock.data_stack.getTop();
            memoblock.data_stack.pop();
            top2 = memoblock.data_stack.getTop();
            memoblock.data_stack.push(top1);
            if (top1 > top2) {
                index = this->label_index[program[index].operand];
            }
            break;
        case parsing::OperationCode::CALL:
            this->run_function(program, this->functions[program[index].operand], memoblock, index);
            break;
        case parsing::OperationCode::RET:
            if (is_function) {
                return;
            }
            break;
        case parsing::OperationCode::LABEL:
            break;
        default:
            parsing::token_to_class[program[index].command]->execute(program[index].operand, memoblock);
            break;
    }
}
