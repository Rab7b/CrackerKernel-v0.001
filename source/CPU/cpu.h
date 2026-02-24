#pragma once

#ifndef CPU_H
#define CPU_H

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>

class CPU {
private:
  static uint64_t *memory;
  uint64_t hex_32[12] = {0x31, 0xC0, 0x50, 0x68, 0xB8, 0xCD, 0xBAADF00D, 0xCCCCCCCC, 0xCDCDCDCD, 0xDDDDDDDD, 0xFEEEFEEE, 0xDEADBEEF};
  uint64_t hex_64[11] = {0x90, 0xCC, 0x05, 0xEB, 0xFF, 0xC3, 0x31, 0xCDCDCDCDCDCDCDCD, 0xCCCCCCCCCCCCCCCC, 0xDDDDDDDDDDDDDDDD, 0xFDFDFDFD};
  uint64_t sp;
  static size_t totalSize;
public:
  CPU(size_t ramSize) {
    totalSize = ramSize;
    try{
      memory = new uint64_t[ramSize]();
    }catch (std::bad_alloc){
      std::cout << "[CPU]: Not enough memory" << std::endl;
    }
    sp = (ramSize > 0xFFFF) ? 0xFFFF : (uint64_t)(ramSize - 1);
  }

  ~CPU() { delete[] memory; }

  void cleanConsole() { (void)std::system("clear"); }

  void getMemory(uint64_t& needs);

  bool detect();

  void push(uint64_t& value);

  uint8_t pop();

  void newTask(uint64_t address, uint64_t *taskData, uint64_t taskSize);
};

#endif
