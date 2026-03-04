#include "bootloader.h"

bool Bootloader::biosPost() {
  std::cout << "[BIOS] Checking memory..." << std::endl;
  std::cout << "[BIOS] Finding CPU..." << std::endl;
  std::cout << "[BIOS] 8 Thread slots available." << std::endl;
  return true;
}
void Bootloader::boot(CPU &cpu, TaskManager &manager) {
  std::cout << "[BOOT] Loading Kernel into memory..." << std::endl;

  uint64_t idle[3] = {0xDE, 0x01, 0x00};
  cpu.newTask(0, idle, 3);

  char task[256] = "Boot_loader";
  manager.loadTask(task, 0, 0, true);

  cpu.detect();
  std::cout << "[BOOT] Jumping to Kernel execution..." << std::endl;
}