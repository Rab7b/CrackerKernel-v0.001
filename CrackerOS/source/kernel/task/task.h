#pragma once

#ifndef TASK_H
#define TASK_H

#include <cstdint>
#include <cstring>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class CPU;

struct Task {
  uint64_t id;
  uint64_t ip;
  enum class State { READY, RUNNING, FINISHED };
  State state;
  int priority;
  char name[256];
  bool isRoot;
  Task(uint64_t _id, uint64_t _ip, State _state, int _priority, char _name[256],
       bool root)
      : id(_id), ip(_ip), state(_state), priority(_priority), isRoot(root) {
    std::memcpy(name, _name, sizeof(name));
  }
};

class TaskManager {
private:
  std::vector<Task> tasks;
  std::vector<CPU *> cores;
  std::mutex os_lock;
  std::vector<std::thread> scheduler;
  const int THREAD_LIMIT = 8;
  uint32_t nextId = 1;
  bool running = true;

public:
  TaskManager();
  ~TaskManager();
  bool loadTask(char name[256], uint64_t startAddress, int priority = 1,
                bool isRoot = false);
  void runCore(int coreId);
  void startOs();
  Task *runTask(size_t &lastIndex);
  void runSchedule();
  size_t getIndex();
};
#endif