#pragma once
#include <any>
#include <array>
#include <cstdint>
#include <utility>
#include <vector>

template <typename T, typename = void>
struct IsIteratorType : std::false_type {};

template <typename T>
struct IsIteratorType<T, std::void_t<decltype(std::declval<T>().at(std::declval<std::size_t>())),
                                     decltype(std::declval<T>().size())>>
    : std::true_type {};

class ExecutableMemory {
public:
  ExecutableMemory() = default;
  ExecutableMemory(const ExecutableMemory &src) = delete;
  ExecutableMemory(ExecutableMemory &&src) = delete;
  ExecutableMemory &operator=(const ExecutableMemory &src) = delete;
  ExecutableMemory &operator=(ExecutableMemory &&src) = delete;
  template <typename T>
  void insert(T &&instruction){
    static_assert(IsIteratorType<decltype(instruction)>(), "not a iterator type");
    for (uint32_t i = 0; i<instruction.size(); ++i) {
      memory.push_back(instruction.at(i));
    }
  }
  void* getPtr(){
    return memory.data();
  }
  std::size_t getSize(){
    return memory.size();
  }
private:
  std::vector<uint8_t> memory;
};