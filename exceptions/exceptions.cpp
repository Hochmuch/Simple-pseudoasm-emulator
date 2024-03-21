#include "include/exceptions.h"


const char *exceptions::PreprocessorError::what() const noexcept {
    return "Preprocessor error!!!";
}

const char *exceptions::StackOverflowError::what() const noexcept {
    return "StackOverflow!!!";
}

const char *exceptions::ParserError::what() const noexcept {
    return "Parser error!!!";
}

const char *exceptions::EmptyStackPopError::what() const noexcept {
    return "Trying to pop from empty stack!";
}