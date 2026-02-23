#include "cpu.h"

void CPU::getMemory(uint64_t &needs) {
  
  if (needs > totalSize) {

    uint64_t *new_memory = new uint64_t[needs]();

    if (memory != nullptr) {
      std::copy(memory, memory + totalSize, new_memory);
      delete[] memory;
    }

    memory = new_memory;
    totalSize = needs;
  }
}

bool CPU::detect() {
  bool found = false;
  if (totalSize < 12) {
    return false;
  }

  for (size_t i = 0; i <= totalSize - 12; ++i) {

    if (memory[i] == hex_32[0]) {
      if (std::memcmp(&memory[i], hex_32, 12 * sizeof(uint64_t)) == 0) {
        std::cout << "[Security] 32-bit threat neutralized at: 0x" << std::hex
                  << i << std::endl;
        std::fill_n(&memory[i], 12, 0x90);
        i += 11;
        found = true;
        continue;
      }
    }

    if (memory[i] == hex_64[0]) {
      if (std::memcmp(&memory[i], hex_64, 11 * sizeof(uint64_t)) == 0) {
        std::cout << "[Security] 64-bit threat neutralized at: 0x" << std::hex
                  << i << std::endl;
        std::fill_n(&memory[i], 11, 0x90);
        i += 10;
        found = true;
      }
    }
  }
  return found;
}

void CPU::push(uint64_t &value) {
  if (sp > 0) {
    memory[sp] = value;
    sp--;
  }
}

uint8_t CPU::pop() {
  if (sp < totalSize - 1) {
    sp++;
    return (uint8_t)memory[sp];
  }
  return 0;
}

void CPU::newTask(uint64_t address, uint64_t *taskData, uint64_t taskSize) {

    uint64_t needs = address + taskSize;
  
    if (needs > totalSize){
      return;
    }else{
      getMemory(needs);
    }

    for (uint64_t i = 0; i < taskSize; i++) {
        memory[address + i] = taskData[i];
    }

    sp = needs - 1;

    detect();
}