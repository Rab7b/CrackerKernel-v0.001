#include "source/include.cpp"

int main() {
  
  CPU cpu(1000000000ULL);
  
  TaskManager manager;
  Bootloader bootloader;
  if (bootloader.biosPost()){
    
    bootloader.boot(cpu, manager);
    size_t last = manager.getIndex();
    
    manager.loadTask({}, 0x00, 0, true);
    cpu.executeStep(manager, last);
    
  }
  return 0;
}