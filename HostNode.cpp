#include "HostNode.h"

void HostNode::setAccountList(std::vector<std::wstring>& users) {
	// perform copy
	for (auto idx : users) {
		m_userAccountList.push_back(idx);
	}
}

void HostNode::printAccountList() {
	for (auto idx : m_userAccountList) {
		std::wcout << "-- " << idx << std::endl;
	}
}
