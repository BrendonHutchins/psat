#include <iostream>
#include <string>

#ifndef PSAT_AUDITOR_H
#define PSAT_AUDITOR_H
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
	void checkSystemAccount(std::vector<std::wstring>& systemAccountStorage);

	void checkFireWall();

	void checkStartItems();

	void checkNetwork(); 

	void checkCerts();

	void checkFilePermissions(); 

	void checkSchTasks();
};

#endif //PSAT_AUDITOR_H
