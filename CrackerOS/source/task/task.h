#pragma once

#ifndef TASK_H
#define TASK_H

#include "../CPU/cpu.h"
#include <cstdint>
#include <cstring>
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

struct Task {
  uint32_t id;
  uint32_t ip;
  enum class State { READY, RUNNING, FINISHED };
  State state;
  int priority;
  char name[256];
  bool isRoot;
  Task(uint32_t _id, uint32_t _ip, State _state, int _priority, char _name[256],
       bool root)
      : id(_id), ip(_ip), state(_state), priority(_priority), isRoot(root) {
    std::memcpy(name, _name, sizeof(name));
  }
};

class TaskManager {
private:
  std::vector<Task> tasks;
  std::vector<CPU*> cores;
  std::mutex os_lock;
  std::vector<std::thread> scheduler;
  const int THREAD_LIMIT = 8;
  uint32_t nextId = 1;
  bool running = true;
public:
  TaskManager() {
    for (int i = 0; i < THREAD_LIMIT; i++){
      cores.push_back(new CPU(0xFFFF));
    }
  }
  ~TaskManager(){
    for (auto core : cores){
      delete core;
      core = nullptr;
    }
  }
  void loadTask(char name[256], uint32_t startAddress, int priority = 1,bool isRoot = false);
  void runCore(int coreId);
  void startOs();
  Task *runTask(size_t &lastIndex);
  void runSchedule();
};
#endif