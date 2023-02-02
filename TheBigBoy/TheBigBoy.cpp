// Made by AC //


#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <sstream>
#include <Windows.h>
#include <iostream> 
#include <string> 
#include <unordered_map> 
#include <vector> 
#include <algorithm> 
#include <tcpmib.h>

#pragma comment(lib, "Ws2_32.lib") 
using namespace std;

DWORD dwNumEntries;
MIB_TCPROW_OWNER_PID table[ANY_SIZE];
/*vector<std::tuple<string, int, string>> getConnectionsList()
{
    vector<std::tuple<string, int, string>> connections;

    // Client functions
    SOCKET s = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);
    if (s == SOCKET_ERROR)
        throw std::runtime_error("Error in creating client socket");


    struct in_addr interfaceAddr;
    interfaceAddr.s_addr = INADDR_ANY;

    // Set the interface address 
    if (setsockopt(s, IPPROTO_IP, IP_MULTICAST_IF, (char*)&interfaceAddr, sizeof(interfaceAddr)) == SOCKET_ERROR) {
        closesocket(s);
        throw std::runtime_error("Error setting socket interface");
    }

    int level = 0;

    // Allocate the request buffer 
    DWORD optlen = 16384;
    char* buf = (char*)malloc(optlen);
    if (buf == NULL)
        return connections;

    // Get the list of TCP connections 
    level = SOL_IP;
    MIB_TCPTABLE_OWNER_PID* tcp_table;
    if (getsockopt(s, level, TCP_TABLE_OWNER_PID_ALL, (char*)tcp_table, &optlen) == SOCKET_ERROR)
    {
        free(buf);
        closesocket(s);
        return connections;
    }

    // Loop through the connection table 
    for (int i = 0; i < tcp_table->dwNumEntries; i++)
    {
        string ip = inet_ntoa(*((struct in_addr*)&tcp_table->table[i].dwRemoteAddr));
        int port = htons(tcp_table->table[i].dwRemotePort);
        string proto = (tcp_table->table[i].dwState == MIB_TCP_STATE_ESTAB) ? "TCP" : "UDP";

        connections.push_back(std::make_tuple(ip, port, proto));
    }

    return connections;
}*/

std::vector<int> getPhoneNumber()
{
    std::vector<int> num;

    const int newNumIdx = rand() % 12;
    int nums[]{ 310, 312, 313, 314, 315, 316, 317, 318, 319, 321, 323, 325 };

    num.push_back(nums[newNumIdx] * 10000000 + rand() % 10000000);

    return num;
}

std::vector<std::string> generateCreditCardNumber()
{
    std::vector<std::string> cards;

    int first = (rand() % 2) + 4;
    cards.push_back(std::to_string(first));

    for (int i = 0; i < 15; ++i)
    {
        int n = rand() % 10;
        cards.push_back(std::to_string(n));
    }

    return cards;
}


BOOL SetHardwareInfo(OSVERSIONINFOEXW* osvie, char* biosName, char* cpuName, char* netAdptName, char* uuid) {
    HANDLE hProcess;
    HMODULE hLib;
    BOOL bResult = FALSE;
    FARPROC lpSetHardwareInfo;

    // Load kernel32.dll
    hLib = LoadLibrary("kernel32.dll");
    if (hLib == NULL)
        return bResult;

    // Get the address of SetHardwareInfo()
    lpSetHardwareInfo = GetProcAddress(hLib, "SetHardwareInfo");
    if (lpSetHardwareInfo == NULL) {
        FreeLibrary(hLib);
        return bResult;
    }

    // Open a handle to the current process
    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_WRITE, FALSE, GetCurrentProcessId());
    if (hProcess == NULL) {
        FreeLibrary(hLib);
        return bResult;
    }

    bResult = ((BOOL(__stdcall*)(HANDLE, OSVERSIONINFOEXW*, char*, char*, char*, char*))lpSetHardwareInfo)(hProcess, osvie, biosName, cpuName, netAdptName, uuid);

    // Close the handle
    CloseHandle(hProcess);
    FreeLibrary(hLib);

    return bResult;
}

int main()
{
    std::cout << "Choose: \n";
    std::cout << "[1] Find Scammers\n";
    std::cout << "[2] Find scammers ip (SOON)\n";
    std::cout << "[3] Make a fake identity\n";
    std::cout << "[4] Make virtual machine look more real. (SOON)\n";
    std::cout << "You Choose?: \n";
    string choose;
    getline(cin, choose);
    if (choose == "1") {
        string website;
        cout << "What website do you want to open? (without the TLD): ";
        getline(cin, website);

        int amount;
        cout << "How many instances of this website do you want to open?: ";
        cin >> amount;

        cout << "Do you want to create a list of targeted websites and write them in a .txt file? (y/n): ";
        string answer;
        getline(cin, answer);

        if (answer == "y")
        {
            ofstream targetedFile;
            targetedFile.open("targeted.txt");
            string targetedWebsitesReq;
            cout << "What targeted websites do you want information about? ";
            getline(cin, targetedWebsitesReq);

            stringstream targetedWebsitesStream(targetedWebsitesReq);
            string website;
            while (getline(targetedWebsitesStream, website, ','))
            {
                string readWebsiteTxt = website + ".txt";
                ifstream websiteFile;
                websiteFile.open(readWebsiteTxt);
                string websiteContent;
                while (getline(websiteFile, websiteContent))
                {
                    targetedFile << websiteContent << "\n";
                }
            }
            cout << "Done!" << endl;
        }
        else
        {
            cout << "ok, proceeding with the application" << endl;
        }

        int hit = 0;
        int failed = 0;

        ifstream domainFile;
        domainFile.open("domains.txt");

        string domain;
        for (int i = 0; i < amount; i++)
        {
            while (domainFile >> domain && hit < amount)
            {
                string websiteWithDomain = website + domain;
                if (system(("start chromium --no-default-browser-check --no-first-run --no-sandbox --incognito  " + websiteWithDomain).c_str()))
                {
                    failed++;
                }
                else
                {
                    hit++;
                }
                //  system("xdg-settings set --auto-accept-security-settings true");
            }
        }

        cout << "\nHITS\033[1;32m " << hit << "\033[0m \nFAILED\033[1;31m " << failed << "\033[0m\n" << endl;

        cout << "Close all tabs we just opened? (y/n): ";
        string answerYesNo;
        getline(cin, answerYesNo);
        if (answerYesNo == "y")
        {
            system("taskkill /f /im chromium.exe");
        }
        else
        {
            cout << "ok, exiting without closing tabs" << endl;
        }
    }
    if (choose == "1") {
       
     /*  vector<std::tuple<string, int, string>> connections;

        try
        {
            connections = getConnectionsList();
        }
        catch (std::runtime_error& e)
        {
            cerr << e.what() << endl;
            return -1;
        }

        for (auto& conn : connections)
            cout << std::get<0>(conn) << ":" << std::get<1>(conn) << "(" << std::get<2>(conn) << ")" << endl;*/ 


        // SOON i promise :)
    }

    if (choose == "3") {
        srand(time(NULL));

        std::string firstNames[10] = { "julie", "bob", "eileen", "carl", "sam", "kathy", "dave", "bettie", "fran", "jimmy" };
        std::string lastNames[10] = { "smith", "williams", "gordon", "jones", "smithy", "oli", "roberts", "miller", "johnson", "simmons" };
        std::string domains[10] = { "gmail.com", "yahoo.com", "hotmail.com", "outlook.com", "aol.com", "live.com", "msn.com", "zebrawood.com", "ama.com", "tulips.com" };

        std::string firstName = firstNames[rand() % 10];
        std::string lastName = lastNames[rand() % 10];
        int age = (rand() % 60) + 18;
        std::string domain = domains[rand() % 10];
        std::string username = firstName + lastName;

        std::vector<int> phoneNumber = getPhoneNumber();

        std::vector<std::string> creditCard = generateCreditCardNumber();

     

            std::cout << "Fake Name: " << firstName << " " << lastName << std::endl;
        std::cout << "Fake Email: " << username << "@" << domain << std::endl;
        std::cout << "Fake Age: " << age << std::endl;
        std::cout << "Fake Phone Number: ";

        for (int i = 0; i < phoneNumber.size(); i++)
        {
            std::cout << phoneNumber[i];
        }

        std::cout << std::endl << "Fake Credit Card Number: ";
        for (int j = 0; j < creditCard.size(); j++)
        {
            std::cout << creditCard[j];
        }

    }
    if (choose == "4") {
        OSVERSIONINFOEXW osvie;
        char biosName[256], cpuName[256], netAdptName[256], uuid[256];

        // Set BIOS Name
        strcpy(biosName, "ASUS");

        // Set CPU Name
        strcpy(cpuName, "Intel Core i7-9700KF");

        // Set Network Adapter Name
        strcpy(netAdptName, "Intel Ethernet Connection (7) I219-V");

        // Set UUID
        strcpy(uuid, "HD09089-A2K8-916E-KD02-J7F076AL1U82");

        // Set OS Version Information
        ZeroMemory(&osvie, sizeof(OSVERSIONINFOEXW));
        osvie.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXW);
        osvie.dwMajorVersion = 10;
        osvie.dwMinorVersion = 0;
        osvie.dwBuildNumber = 17763;

        // Set hardware information
        if (SetHardwareInfo(&osvie, biosName, cpuName, netAdptName, uuid)) {
            std::cout << "Successfully set hardware information!" << std::endl;
        }

    }
    
    std::cin.ignore();
}