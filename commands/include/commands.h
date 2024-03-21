#pragma once

#include "../../memory/include/memory.h"
#include "../../exceptions/include/exceptions.h"
#include <string>
#include <iostream>

namespace commands {

    class Operation {
    public:
        explicit Operation(int val = 0, memory::OperandType reg = memory::OperandType::NONE, std::string label = "");

        virtual void
        execute(const std::string &arg, memory::Memory &memoblock);
    };

    class Begin : public Operation {
        virtual void
        execute(const std::string &arg, memory::Memory &memoblock);
    };

    class End : public Operation {
        virtual void
        execute(const std::string &arg, memory::Memory &memoblock);
    };

    class Add : public Operation {
        virtual void
        execute(const std::string &arg, memory::Memory &memoblock);

    private:

    };

    class Sub : public Operation {
        virtual void
        execute(const std::string &arg, memory::Memory &memoblock);
    };

    class Mul : public Operation {
        virtual void
        execute(const std::string &arg, memory::Memory &memoblock);
    };

    class Div : public Operation {
        virtual void
        execute(const std::string &arg, memory::Memory &memoblock);
    };

    class Push : public Operation {
    private:
        long long value{};
    public:
        virtual void
        execute(const std::string &arg, memory::Memory &memoblock);

        Push();
    };

    class Pop : public Operation {
        virtual void
        execute(const std::string &arg, memory::Memory &memoblock);
    };

    class Pushr : public Operation {
        virtual void
        execute(const std::string &arg, memory::Memory &memoblock);
    };

    class Popr : public Operation {
        virtual void
        execute(const std::string &arg, memory::Memory &memoblock);
    };

    class Out : public Operation {
        virtual void
        execute(const std::string &arg, memory::Memory &memoblock);
    };

    class In : public Operation {
        virtual void
        execute(const std::string &arg, memory::Memory &memoblock);
    };

    class Label : public Operation {
        virtual void
        execute(const std::string &arg, memory::Memory &memoblock);
    };

    void abort_if_not_started(memory::Memory &memoblock);

}
