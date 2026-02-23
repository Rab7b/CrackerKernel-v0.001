#include "shell.h"

void Shell::getCommand() {
  std::cout << std::endl;
  std::cin >> command;
}

// We pass which core we want to use for this command
void Shell::runCommand(CPU* targetCore, int coreID) {

    if (strcmp(command, "/help") == 0) {
        history.push_back(command);
        std::cout << "/help - all commands\n/check - scan for madness\n/run - load task\n";
    } 

    else if (strcmp(command, "/check") == 0) {
        history.push_back(command);

        if (targetCore->detect()) {
            std::cout << "CORE " << coreID << ": VIRUS!\n";
        } else {
            std::cout << "CORE " << coreID << ": Fine\n";
        }
    } 

    else if (strcmp(command, "/run") == 0) {
        std::string task_name;
        std::cin >> task_name;
        history.push_back(command);
        history.push_back(" ");
        history.push_back(task_name.c_str());

        uint64_t fake_code = 777; 
        targetCore->newTask(0x1000, &fake_code, 1);

        std::cout << "Task loaded onto Core " << coreID << " at address 0x1000\n";
    }
}