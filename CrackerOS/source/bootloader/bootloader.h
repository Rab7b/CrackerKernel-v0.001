#pragma once

#ifndef BOOTLOADER_H
#define BOOTLOADER_H

#include "../kernel/CPU/cpu.h"
#include "../kernel/task/task.h"
#include <iostream>

class Bootloader {
public:
  bool biosPost();
  void boot(CPU &cpu, TaskManager &manager);
};

#endif