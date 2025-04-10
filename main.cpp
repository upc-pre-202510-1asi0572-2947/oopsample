#include "ConsumableResource.h"
#include <iostream>
#include "Process.h"
#include "Task.h"
#include "UsableResource.h"

int main() {
    try {
        const auto compilationProcess = std::unique_ptr<Process>(
            new Process("CompileMain", "Compile main.cpp",
                {"CentralProcessingUnit", "Memory"}, 15));
        compilationProcess->
        addResource(std::unique_ptr<UsableResource>(new UsableResource("CentralProcessingUnit", 3)));
        compilationProcess->
        addResource(std::unique_ptr<ConsumableResource>(new ConsumableResource("Memory", 4096)));
        compilationProcess->
        addTask(std::unique_ptr<Task>(new Task("ScanSourceCode", "Tokenize main.cpp",
            {"CentralProcessingUnit", "Memory"}, 2)));
        std::cout << "Starting compilation process..." << std::endl;
        compilationProcess->run();

    } catch (std::exception &e) {
        std::cerr << "Critical error: " << e.what() << std::endl;
    }
}
