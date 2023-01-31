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

	// MUTATOR
	void setAccountList(std::vector<std::wstring>&);

private:
	std::vector<std::wstring> m_userAccountList;

};

