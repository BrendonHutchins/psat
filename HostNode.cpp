#include "HostNode.h"


void HostNode::setAccountList(std::vector<std::wstring> m_systemAccountStorage) {
	// perform copy
	for (auto idx : m_systemAccountStorage) {
		m_userAccountList.push_back(idx);
	}
}

void HostNode::setFilePermissions() {

}

void HostNode::setSchTasks() {

}

void HostNode::setStartItems() {

}

void HostNode::printAccountList() {
	std::cout << "Printing current system users - ID: T1136" << std::endl;
	std::cout << "========================================\n" << std::endl;
	for (auto idx : m_userAccountList) {
		std::wcout << "-- " << idx << std::endl;
	}
	std::cout << std::endl;
}

void HostNode::printFilePermissions() {

}

void HostNode::printSchTasks() {

}


void HostNode::StartItems() {

}
