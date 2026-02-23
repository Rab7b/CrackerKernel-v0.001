#pragma once

#ifndef SHELL_H
#define SHELL_H

#include "../CPU/cpu.h"
#include "../task/task.h"
#include <fstream>
#include <vector>

class Shell {
private:
  TaskManager task_worker;
  std::vector<std::string> commands = {"/help", "/run", "/check", "/history","/exit"};
  char command[256];
  std::vector<std::string> history;

public:
  Shell() {}
  void runCommand(CPU* targetCore, int coreID);
  void getCommand();
};

#endif