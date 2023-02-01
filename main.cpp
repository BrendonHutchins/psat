#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <stdlib.h> // used to change text and bg colour of console.
#include "Auditor.h"
#include "Logging.h"
#include "ApiStream.h"

int main(int argc, char* argv[]) {
    // =========+===================== SETUP ===============================
    // argument parsing
    enum definedArgs {accounts, tasks, startup};
    std::vector<std::string> arguments(argv, argv + argc); arguments.reserve(10);
    for (std::string& args : arguments) {
        std::cout << "Run args: " << args << std::endl;
    }

    bool createLogFile = false;
    bool createAPIEndpoint = false;
    std::cout << "Create Log: " << std::boolalpha << createLogFile << std::endl;
    std::cout << "API Endpoint: " << std::boolalpha << createAPIEndpoint << std::endl << std::endl;
    system("Color 0A"); // set values for stdlib.h in order to change console text and bg colour.

    Auditor audit;
    Logging log;
    ApiStream api;
    // =====================================================================

 try {

    audit.checkSystemAccount(); // get/assign Host user list.
    audit.checkFilePermissions();
    audit.checkSchTasks();
    audit.checkStartItems();
    audit.postResults();

 }
 catch(std::exception& e) {
     std::cout << e.what();
     exit(1);
 }

 std::getchar();
 return 0;
}
