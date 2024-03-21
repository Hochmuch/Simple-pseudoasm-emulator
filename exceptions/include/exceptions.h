//
// Created by hochmuch on 21/03/2024.
//

#ifndef EMULATOR2_EXCEPTIONS_H
#define EMULATOR2_EXCEPTIONS_H

#include <stdexcept>

namespace exceptions {

    class PreprocessorError : std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override;
    };

    class ParserError : std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override;
    };

    class StackOverflowError : std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override;
    };

    class EmptyStackPopError : std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override;
    };
}

#endif //EMULATOR2_EXCEPTIONS_H
