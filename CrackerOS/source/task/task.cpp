#include "task.h"

void TaskManager::loadTask(char name[256], uint32_t startAddress,
                           int priority, bool isRoot) {
  tasks.push_back(
      Task(nextId++, startAddress, Task::State::READY, priority, name, isRoot));
  std::cout << "[Manager]  Task: " << name << " loaded in adress"
            << startAddress << std::endl;
  std::cout << "[Manager] Registered: " << name << " | Addr: 0x" << std::hex
            << startAddress << std::dec
            << (isRoot ? " | [ROOT PRIVILEGES]" : " | [USER MODE]")
            << std::endl;
}
Task *TaskManager::runTask(size_t &lastIndex) {
  if (tasks.empty()) {
    return nullptr;
  }

  for (size_t i = 0; i < tasks.size(); i++) {

    size_t index = (lastIndex + i) % tasks.size();

    if (tasks[index].priority > 0 &&
        tasks[index].state != Task::State::FINISHED) {

      if (tasks[index].state == Task::State::READY) {
        tasks[index].state = Task::State::RUNNING;
      }

      lastIndex = index;

      std::cout << "[Scheduler] Switched to: " << tasks[index].name
                << " (ID: " << tasks[index].id
                << (tasks[index].isRoot ? " | ROOT" : "") << ")" << std::endl;

      return &tasks[index];
    }
  }
  return nullptr;
}
void TaskManager::runSchedule() {
    while (scheduler.size() < (size_t)THREAD_LIMIT) {
        scheduler.push_back(std::thread([this]() {
            size_t lastIndex = 0;
            while (true) {
                this->runTask(lastIndex);
            }
        }));
    }
}
void TaskManager::runCore(int coreId){
    while(running){
        std::lock_guard<std::mutex> lock(os_lock);
    }
}
void TaskManager::startOs(){
    std::vector<std::thread> kernelThreads;
    for (int i = 0; i < 8; i++) {
        kernelThreads.emplace_back(&TaskManager::runCore, this, i);
    }

    for (auto& t : kernelThreads) {
        t.join();
    }
}