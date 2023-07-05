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
  memory.insert(InstructionGenerator::MovE_RD(Instruction::MOV_AX, -42));
  memory.insert(InstructionGenerator::Ret());
  const size_t mmap_size = std::ceil(memory.getSize() / ((float)4096)) * 4096;
  void *jitPtr = mmap(nullptr, mmap_size, PROT_READ | PROT_EXEC | PROT_WRITE,
                      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  memory.getMeta().executablePtr = jitPtr;
  std::memcpy(jitPtr, memory.getPtr(), memory.getSize());
  typedef uint32_t (*func)();
  func f = (func)(jitPtr);
  uint32_t returnValue = f();
  ASSERT_EQ(-42, returnValue);
}

TEST(jit_e2e, pureAsm) {
  // asm("mov $0x123456789abcdef,%rbx");
  asm("lea 0xfa, %rax");
  std::cout << "end\n";
}

TEST(jit_e2e, sys_call) {
  ExecutableMemory memory;

  // std::string helloWorld = "hello world";
  // memory.insert(InstructionGenerator::PushA());
  auto *metaPtr = memory.getMetaPtr();
  memory.insert(InstructionGenerator::MovR_RD(Instruction::MOV_AX, reinterpret_cast<uintptr_t>(metaPtr)));
  memory.insert(InstructionGenerator::Ret());
  const size_t mmap_size = std::ceil(memory.getSize() / ((float)4096)) * 4096;
  void *jitPtr = mmap(nullptr, mmap_size, PROT_READ | PROT_EXEC | PROT_WRITE,
                      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  memory.getMeta().executablePtr = jitPtr;
  std::memcpy(jitPtr, memory.getPtr(), memory.getSize());
  typedef uint64_t (*func)();
  func f = (func)(jitPtr);
  uint64_t returnValue = f();
  std::cout << "0x" << std::hex << returnValue << std::endl;
}