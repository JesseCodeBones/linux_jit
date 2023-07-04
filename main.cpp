#include <array>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <sys/mman.h>
#include "src/x86_instruction_generator.hpp"
int main(int, char **) {
  std::array<uint8_t, 6> executable{};
  const auto jit1 = InstructionGenerator::generateMovEAX(0xffff);
  uint32_t pos = 0;
  for (uint8_t code : jit1) {
    executable[pos] = code;
    pos++;
  }
  const auto jit2 = InstructionGenerator::generateRet();
  for (uint8_t code : jit2) {
    executable[pos] = code;
    pos++;
  }
  void *jitPtr = mmap(nullptr, 4096, PROT_READ | PROT_EXEC | PROT_WRITE,
                      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  std::memcpy(jitPtr, executable.data(), executable.size());
  typedef uint32_t(*func)() ;
  func f = (func) jitPtr;
  uint32_t returnValue = f();
  std::cout << "jit return value is " << returnValue << std::endl;
}
