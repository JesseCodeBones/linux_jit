#pragma once
#include <cstdint>
enum RegisterIndex : uint8_t {
  AX = 0x0,
  BX = 0x3,
};

struct Mov {
  static constexpr uint8_t genInstruction(uint8_t regIndex) {
    return 0xb8 + regIndex;
  }
};

enum Instruction : uint8_t {
  MOV_AX = Mov::genInstruction(RegisterIndex::AX),
  MOV_BX = Mov::genInstruction(RegisterIndex::BX),
  RET = 0xc3,
  PUSHA = 0x60,
  REX_W = 0x48
};