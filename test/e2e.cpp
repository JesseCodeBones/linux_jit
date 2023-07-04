#include <cmath>
#include <cstdint>
#include <cstring>
#include <functional>
#include <gtest/gtest.h>
#include <sys/mman.h>
#include <vector>
#include "../src/executable_memory.hpp"
#include "../src/x86_instruction_generator.hpp"
TEST(jit_e2e, t1) {
  ExecutableMemory memory;
  memory.insert(InstructionGenerator::generateMovEAX(-42));
  memory.insert(InstructionGenerator::generateRet());
  const size_t mmap_size = std::ceil(memory.getSize() / ((float)4096)) * 4096;
  void *jitPtr = mmap(nullptr, mmap_size, PROT_READ | PROT_EXEC | PROT_WRITE,
                      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  std::memcpy(jitPtr, memory.getPtr(), memory.getSize());
  typedef uint32_t (*func)();
  func f = (func)jitPtr;
  uint32_t returnValue = f();
  ASSERT_EQ(-42, returnValue);
}