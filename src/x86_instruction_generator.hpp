#pragma once
#include <array>
#include <cstdint>
#include "x86_instruction.hpp"
class InstructionGenerator {
public:
  template <typename T>
  static std::array<uint8_t, sizeof(T) + 1> MovE_RD(Instruction targetRegister,T value) {
    static_assert(sizeof(T) == 4, "move eax only accept 4 byte value");
    uint8_t value0 = value & 0b11111111;
    uint8_t value1 = value >> (8 * 1) & 0b11111111;
    uint8_t value2 = value >> (8 * 2) & 0b11111111;
    uint8_t value3 = value >> (8 * 3) & 0b11111111;

    return {targetRegister, value0, value1, value2, value3};
  }

  template <typename T>
  static std::array<uint8_t, sizeof(T) + 2> MovR_RD(Instruction targetRegister, T value) {
    static_assert(sizeof(T) == 8, "move rax only accept 8 byte value");
    uint8_t value0 = value & 0b11111111;
    uint8_t value1 = value >> (8 * 1) & 0b11111111;
    uint8_t value2 = value >> (8 * 2) & 0b11111111;
    uint8_t value3 = value >> (8 * 3) & 0b11111111;
    uint8_t value4 = value >> (8 * 4) & 0b11111111;
    uint8_t value5 = value >> (8 * 5) & 0b11111111;
    uint8_t value6 = value >> (8 * 6) & 0b11111111;
    uint8_t value7 = value >> (8 * 7) & 0b11111111;
    return {Instruction::REX_W,
            targetRegister,
            value0,
            value1,
            value2,
            value3,
            value4,
            value5,
            value6,
            value7};
  }

  template <typename T>
  static std::array<uint8_t, sizeof(T) + 1> Mov(uint8_t regIndex, T value) {
  }
  static std::array<uint8_t, 1> Ret() {
    return {Instruction::RET};
  }
  static std::array<uint8_t, 1> PushA() {
    return {Instruction::PUSHA};
  }
};