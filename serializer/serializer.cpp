#include "include/serializer.h"

serializing::Serializer::Serializer(std::string &file_path) {
    if (this->stream.is_open()) {
        throw exceptions::SerializerError();
    }
    this->path = file_path;
    this->stream.open(this->path, std::ios::out);
}

void serializing::Serializer::exec(const serializing::CommandToken &token) {
    if (!this->stream.is_open()) {
        throw exceptions::SerializerError();
    }
    long long length = token.operand.size();
    stream.write(reinterpret_cast<const char *>(&token.command), sizeof(serializing::OperationCode));
    stream.write(reinterpret_cast<const char *>(&length), sizeof(length));
    stream.write(token.operand.data(), length);
}

void serializing::Serializer::close() {
    if (!this->stream.is_open()) {
        throw exceptions::SerializerError();
    }
    this->stream.close();
}

serializing::Serializer::Serializer() = default;

serializing::Deserializer::Deserializer(std::string &file_path) {
    this->path = file_path;
}

serializing::CommandToken serializing::Deserializer::exec() {
    if (!this->stream.is_open()) {
        this->stream.open(this->path, std::ios::in);
    }
    serializing::CommandToken token;
    stream.read(reinterpret_cast<char *>(&token.command), sizeof(serializing::OperationCode));
    long long length;
    stream.read(reinterpret_cast<char *>(&length), sizeof(length));
    token.operand.resize(length);
    stream.read(token.operand.data(), length);
    return token;
}

serializing::Deserializer::Deserializer() = default;
