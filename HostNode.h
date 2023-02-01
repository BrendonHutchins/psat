#pragma once

#include <string>
#include <iostream>
#include <vector>

class HostNode
{
public:
	// default constrcutor 

	// overload constructor

	// ACCESSOR
	void printAccountList();
	void printFilePermissions();
	void printSchTasks();
	void StartItems();

	// MUTATOR
	void setAccountList(std::vector<std::wstring> m_systemAccountStorage);
	void setFilePermissions();
	void setSchTasks();
	void setStartItems();

private:
	std::vector<std::wstring> m_userAccountList;
	std::string m_filePermissions;
	std::string m_schTasks;
	std::string m_startupItems;
};

