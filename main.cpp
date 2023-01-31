#include <iostream>
#include <string>
#include <vector>

#include <stdlib.h> // used to change text and bg colour of console.
#include "Auditor.h"
#include "Logging.h"
#include "ApiStream.h"
#include "HostNode.h"

int main(int argc, char* argv[]) {

    // =========+===================== SETUP ===============================
    // argument parsing
    std::vector<std::string> arguments(argv, argv + argc); arguments.reserve(10);
    for (std::string& args : arguments) {
        std::cout << "Run args: " << args << std::endl;
    }

    bool createLogFile = false;
    bool createAPIEndpoint = false;
    std::cout << "Create Log: " << std::boolalpha << createLogFile << std::endl;
    std::cout << "API Endpoint: " << std::boolalpha << createAPIEndpoint << std::endl;
    system("Color 0A"); // set values for stdlib.h in order to change console text and bg colour.

    std::vector<std::wstring> systemAccountStorage; systemAccountStorage.reserve(20); // instance storage - account information - passed to auditor.
    std::vector<HostNode> globalStorage; globalStorage.reserve(50);
    int hostQuantity = 5;
    HostNode hostInstance;
    Auditor audit;
    Logging log;
    ApiStream api;
    // =====================================================================

 try {
    audit.checkSystemAccount(systemAccountStorage); 
    hostInstance.setAccountList(systemAccountStorage);

    globalStorage.push_back(hostInstance);
    globalStorage[0].printAccountList();

    audit.checkFilePermissions();
    audit.checkSchTasks();
    audit.checkStartItems();
 }
 catch(std::exception& e){
     std::cout << e.what();
     exit(1);
 }

 std::getchar();
 return 0;
}
