#include <array>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <sys/mman.h>
enum JIT : uint8_t { MOV_EAX = 0xb8 };

class JITInstruction {
public:
  static std::array<uint8_t, 5> generateMovEAX(uint32_t value) {
    uint8_t value0 = value & 0b11111111;
    uint8_t value1 = value >> 8 & 0b11111111;
    uint8_t value2 = value >> 16 & 0b11111111;
    uint8_t value3 = value >> 24 & 0b11111111;
    return {JIT::MOV_EAX, value0, value1, value2, value3};
  }
  static std::array<uint8_t, 1> generateRet() { return {0xc3}; }
};
int main(int, char **) {
  std::array<uint8_t, 6> executable{};
  const auto jit1 = JITInstruction::generateMovEAX(0xffff);
  uint32_t pos = 0;
  for (uint8_t code : jit1) {
    executable[pos] = code;
    pos++;
  }
  const auto jit2 = JITInstruction::generateRet();
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
