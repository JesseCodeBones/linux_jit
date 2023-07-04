#include <cstdint>
#include <gtest/gtest.h>

#include <sys/mman.h>
#include <cstring>
#include <vector>
#include <functional>
#include "../src/x86_instruction_generator.hpp"
#include "../src/executable_memory.hpp"
TEST(jit_e2e, t1) {
  ExecutableMemory memory;
  memory.insert(InstructionGenerator::generateMovEAX(42));
  memory.insert(InstructionGenerator::generateRet());
  void *jitPtr = mmap(nullptr, 4096, PROT_READ | PROT_EXEC | PROT_WRITE,
                      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  std::memcpy(jitPtr, memory.getPtr(), memory.getSize());
  typedef uint32_t(*func)() ;
  func f = (func) jitPtr;
  uint32_t returnValue = f();
  ASSERT_EQ(42, returnValue);
}