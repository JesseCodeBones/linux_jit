#pragma once
#include <array>
#include <cstdint>
#include "x86_instruction.hpp"
class InstructionGenerator {
public:
  static std::array<uint8_t, 5> generateMovEAX(uint32_t value) {
    uint8_t value0 = value & 0b11111111;
    uint8_t value1 = value >> 8 & 0b11111111;
    uint8_t value2 = value >> 16 & 0b11111111;
    uint8_t value3 = value >> 24 & 0b11111111;
    return {Instruction::MOV_EAX, value0, value1, value2, value3};
  }
  static std::array<uint8_t, 1> generateRet() {
    return {Instruction::RET};
  }
};