#include "Auditor.h"

void Auditor::checkSystemAccount() {
    //=========================== Define attributes for NetUserEnum function
    LPUSER_INFO_1 pBuf = NULL;
    LPUSER_INFO_1 pTmpBuf;
    DWORD dwLevel = 1;
    DWORD dwPrefMaxLen = MAX_PREFERRED_LENGTH;
    DWORD dwEntriesRead = 0;
    DWORD dwTotalEntries = 0;
    DWORD dwResumeHandle = 0;
    DWORD i;
    DWORD dwTotalCount = 0;
    NET_API_STATUS nStatus;
    LPTSTR pszServerName = NULL;
    //===========================

    nStatus = NetUserEnum((LPCWSTR)pszServerName,
        dwLevel,
        FILTER_NORMAL_ACCOUNT, // global users
        (LPBYTE*)&pBuf,
        dwPrefMaxLen,
        &dwEntriesRead,
        &dwTotalEntries,
        &dwResumeHandle);

    if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA)) {
        if ((pTmpBuf = pBuf) != NULL)
        {
            //
            // Loop through the entries.
            //
        //std::cout << "Printing current system users - ID: T1136" << std::endl;
        //std::cout << "========================================\n" << std::endl;
            for (i = 0; (i < dwEntriesRead); i++)
            {
                assert(pTmpBuf != NULL);

                if (pTmpBuf == NULL)
                {
                    fprintf(stderr, "An access violation has occurred\n");
                    break;
                }
                //  Print the name of the user account.
                //wprintf(L"\t-- %s\n", pTmpBuf->usri1_name);
                m_systemAccountStorage.push_back(pTmpBuf->usri1_name);
                pTmpBuf++;
                dwTotalCount++;
            }
        }
    }
};

void Auditor::checkFireWall() {

}

void Auditor::checkStartItems() {

    //std::cout << "Printing Startup Items - ID: T1037.005" << std::endl;
    //std::cout << "========================================\n" << std::endl;
    try {
        std::string path = "C:\\Users\\User\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup";

        for (const auto& entry : fs::directory_iterator(path))
            std::cout << entry.path() << std::endl;
            std::cout << std::endl;
    }
    catch(std::exception& e) {
        std::cout << e.what();
        std::cout << std::endl << std::endl;
    }

}

void Auditor::checkNetwork() {

}

void Auditor::checkCerts() {

}

void Auditor::checkSchTasks() {
    std::cout << "Printing Scheduled Tasks - ID: T1053" << std::endl;
    std::cout << "========================================\n" << std::endl;
    try {
        system(" schtasks.exe /query /FO Table ");
        std::cout << std::endl;
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;

    }
}

void::Auditor::checkFilePermissions() {
    std::cout << "Printing File Permissions - ID: T1222.001" << std::endl;
    std::cout << "========================================\n" << std::endl;
    try{
    // Define stuff
    DWORD dwRtnCode = 0;
    PSID pSidOwner = NULL;
    BOOL bRtnBool = TRUE;
    LPTSTR AcctName = NULL;
    LPTSTR DomainName = NULL;
    DWORD dwAcctName = 1, dwDomainName = 1;
    SID_NAME_USE eUse = SidTypeUnknown;
    HANDLE hFile; 
    PSECURITY_DESCRIPTOR pSD = NULL;

    // Get the handle of the file object.
hFile = CreateFile(
    TEXT("example.txt"),
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

// Check GetLastError for CreateFile error code.
if (hFile == INVALID_HANDLE_VALUE) {
        DWORD dwErrorCode = 0;
        dwErrorCode = GetLastError();
        _tprintf(TEXT("CreateFile error = %d\n"), dwErrorCode);
        std::cout << "ERROR -1 HANDLE FAILED: " << std::endl << std::endl;
    }


dwRtnCode = GetSecurityInfo(
    hFile,
    SE_FILE_OBJECT,
    OWNER_SECURITY_INFORMATION,
    &pSidOwner,
    NULL,
    NULL,
    NULL,
    &pSD);

bRtnBool = LookupAccountSid(
    NULL,           // local computer
    pSidOwner,
    AcctName,
    (LPDWORD)&dwAcctName,
    DomainName,
    (LPDWORD)&dwDomainName,
    &eUse);

AcctName = (LPTSTR)GlobalAlloc(
    GMEM_FIXED,
    dwAcctName * sizeof(wchar_t));

DomainName = (LPTSTR)GlobalAlloc(
    GMEM_FIXED,
    dwDomainName * sizeof(wchar_t));

    bRtnBool = LookupAccountSid(
        NULL,                   // name of local or remote computer
        pSidOwner,              // security identifier
        AcctName,               // account name buffer
        (LPDWORD)&dwAcctName,   // size of account name buffer 
        DomainName,             // domain name
        (LPDWORD)&dwDomainName, // size of domain name buffer
        &eUse);                 // SID type

    // Print the account name.
    _tprintf(TEXT("Account owner = %s\n"), AcctName);
    m_filePermissionStorage["example.txt"] = AcctName;
    std::cout << std::endl;
    }
    catch (std::exception& e) {
        std::cout << e.what();
    }
}

void Auditor::postResults() {
HostNode hostInstance;
std::vector<HostNode> globalStorage; globalStorage.reserve(50);
    hostInstance.setAccountList(m_systemAccountStorage);
    hostInstance.setFilePermissions();
    hostInstance.setSchTasks();
    hostInstance.setStartItems();
    
    globalStorage.push_back(hostInstance);
    globalStorage[0].printAccountList();

}