#pragma once
#include <any>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

template <typename T, typename = void>
struct IsIteratorType : std::false_type {};

template <typename T>
struct IsIteratorType<T, std::void_t<decltype(std::declval<T>().at(std::declval<std::size_t>())),
                                     decltype(std::declval<T>().size())>> : std::true_type {};

class JITMeta {
public:
  void *executablePtr;
  std::unordered_map<std::string, void *> linkedFunctions;
};

class ExecutableMemory {
public:
  ExecutableMemory() noexcept {
  };
  ExecutableMemory(const ExecutableMemory &src) = delete;
  ExecutableMemory(ExecutableMemory &&src) = delete;
  ExecutableMemory &operator=(const ExecutableMemory &src) = delete;
  ExecutableMemory &operator=(ExecutableMemory &&src) = delete;
  template <typename T>
  void insert(T &&instruction) {
    static_assert(IsIteratorType<decltype(instruction)>(), "not a iterator type");
    static_assert(sizeof(decltype(std::declval<T>().at(std::declval<std::size_t>()))) == 1,
                  "only accept elements with 1 byte size");
    for (uint32_t i = 0; i < instruction.size(); ++i) {
      memory.push_back(instruction.at(i));
    }
  }
  void *getPtr() {
    return memory.data();
  }
  std::size_t getSize() {
    return memory.size();
  }
  JITMeta &getMeta() {
    return meta;
  }
  JITMeta* getMetaPtr(){
    return &meta;
  }
  template <typename T>
  void writeLittleEndian(T value) {
    for (uint32_t i = 0; i < sizeof(T); ++i) {
      memory.push_back((value >> (8 * i)) & 0xFF);
    }
  }

private:
  std::vector<uint8_t> memory;
  JITMeta meta;
};