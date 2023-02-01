#include <iostream>
#include <string>
#include <map>
#include <filesystem>
#include "HostNode.h"
#include <vector>


#ifndef PSAT_AUDITOR_H
#define PSAT_AUDITOR_H

namespace fs = std::filesystem;
//====================================
// Required for the NetUserEnum function (lmaccess.h)

#ifndef UNICODE
#define UNICODE
#endif
#pragma comment(lib, "netapi32.lib")

#include <stdio.h>
#include <assert.h>
#include <windows.h>
#include <lm.h>
#include <vector>

//=================================
// required for windows certificate store

#include <Wincrypt.h>
#pragma comment(lib, "crypt32.lib")
//=================================


//====================================
//  Required for Owner of File Object
#include "accctrl.h"
#include "aclapi.h"
#include <tchar.h>
#pragma comment(lib, "advapi32.lib")

//====================================
// Required for LPWSTR to string convesion
#include <atlstr.h>

class Auditor {
public:
	void checkSystemAccount();

	void checkFireWall();

	void checkStartItems();

	void checkNetwork(); 

	void checkCerts();

	void checkFilePermissions();

	void checkSchTasks();

	void postResults();

private:
	std::map<std::string, LPTSTR> m_filePermissionStorage;
	std::vector<std::wstring> m_systemAccountStorage;
};
#endif //PSAT_AUDITOR_H
