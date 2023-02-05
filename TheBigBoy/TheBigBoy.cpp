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
/*static BOOL SetUserName(LPCTSTR szUsername)
{
    BOOL bReturn = FALSE;
    HKEY hKey;
    DWORD dwType = REG_SZ;
    TCHAR szCurrentUser[MAX_PATH + 1];
#define BUFF_LEN 256

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
        TEXT("Software\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon"),
        0, KEY_QUERY_VALUE | KEY_SET_VALUE, &hKey) == ERROR_SUCCESS)
    {
        DWORD dwSize = MAX_PATH;
        if (RegQueryValueEx(hKey, L"DefaultUserName", NULL, &dwType,
            (LPBYTE)szCurrentUser, &dwSize) == ERROR_SUCCESS)
        {
            if (dwType == REG_SZ &&
                strcmp(szUsername, szCurrentUser) != 0)
            {
                DWORD dwSize = (strlen(szUsername) + 1) * sizeof(TCHAR);
                if (RegSetValueEx(hKey, "DefaultUserName", NULL, dwType,
                    (LPBYTE)szUsername, dwSize) == ERROR_SUCCESS)
                {
                    bReturn = TRUE;
                }
            }
        }
    }
    RegCloseKey(hKey);
    return bReturn;
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

int main()
{
    std::cout << "Choose: \n";
    std::cout << "[1] Find Scammers\n";
    std::cout << "[2] Find scammers ip (SOON)\n";
    std::cout << "[3] Make a fake identity\n";
    std::cout << "[4] Make virtual machine look more real. \n";
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
     //   string newName;
       // cout << "Please enter a new username to use: ";
      //  cin >> newName;

     //   if (SetUserName(newName.c_str()) == true)
       // {
         //   cout << "Username successfully changed to " << newName << endl;
        //}
       // else
       // {
         //   cout << "Error changing the username" << endl;
        //}
        const wchar_t* procPath = L"Hardware\\Description\\System\\CentralProcessor\\0";
        HKEY hkey;
        LONG lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, procPath, 0, KEY_READ | KEY_WRITE, &hkey);
        if (lResult == ERROR_SUCCESS)
        {
            wchar_t regValue[MAX_PATH];
            DWORD dwSize = MAX_PATH;
            if (RegQueryValueEx(hkey, L"ProcessorNameString", NULL, NULL, (LPBYTE)regValue, &dwSize) == ERROR_SUCCESS)
            {
                string newName = "Intel Core i7";
                wstring newNameW(newName.begin(), newName.end());
                lResult = RegSetValueEx(hkey, L"ProcessorNameString", 0, REG_SZ, (LPBYTE)newNameW.c_str(), newNameW.length() * 2);
                if (newName != "")
                {
                    cout << "Registry key successfully changed to " << newName << endl;
                }
                else
                {
                    cout << "Error changing the registry key" << endl;
                }
            }
            else
            {
                cout << "Error reading registry key" << endl;
            }
        }
        else
        {
            cout << "Error opening registry key" << endl;
        }

        const wchar_t* sysPath = L"Hardware\\Description\\System";
        lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, sysPath, 0, KEY_READ | KEY_WRITE, &hkey);
        if (lResult == ERROR_SUCCESS)
        {
            wchar_t syslValue[MAX_PATH];
            DWORD dwSize = MAX_PATH;
            if (RegQueryValueEx(hkey, L"SystemBiosVersion", NULL, NULL, (LPBYTE)syslValue, &dwSize) == ERROR_SUCCESS)
            {
                string newName = "DELL E7240 1.0.0";
                wstring newNameW(newName.begin(), newName.end());
                lResult = RegSetValueEx(hkey, L"SystemBiosVersion", 0, REG_SZ, (LPBYTE)newNameW.c_str(), newNameW.length() * 2);
                if (newName != "")
                {
                    cout << "Registry key successfully changed to " << newName << endl;
                }
                else
                {
                    cout << "Error changing the registry key" << endl;
                }
            }
            else
            {
                cout << "Error reading registry key" << endl;
            }
        }
        else
        {
            cout << "Error opening registry key" << endl;
        }
        const wchar_t* monitorPath = L"Hardware\\DEVICEMAP\\Monitor";
        const wchar_t* edidPath = L"EDID_1F_0F_00";
        LONG lResulta = RegOpenKeyEx(HKEY_LOCAL_MACHINE, monitorPath, 0, KEY_READ | KEY_WRITE, &hkey);
        if (lResulta == ERROR_SUCCESS)
        {
            wchar_t lpData[MAX_PATH];
            DWORD lpType;
            DWORD lpcbData = MAX_PATH;
            if (RegQueryValueEx(hkey, edidPath, NULL, &lpType, (LPBYTE)lpData, &lpcbData) == ERROR_SUCCESS)
            {
                string newName = "hpz23X_3";
                wstring newNameW(newName.begin(), newName.end());
                lResult = RegSetValueEx(hkey, L"Device Parameters", 0, REG_SZ, (LPBYTE)newNameW.c_str(), newNameW.length() * 2);
                if (newName != "")
                {
                    cout << "Registry key successfully changed to " << newName << endl;
                }
                else
                {
                    cout << "Error changing the registry key" << endl;
                }

                string newName2 = "00FF003F00302D005955595249320A00127302578CA52C595195196E252150540000000101010101010101010101010101026711D077FCF807F00000000000000080000000000000001400000000000000000000000000000000030C00AC080A0703FF9060000068E010A202020202020000000FA00595531393832363832353957414C4954323333334A030323000001A000000FC004850205A32353F0A202020202020200001D021D716103A80D072382D40102C2580C11000001890A2020202020202020202000014000000FD00333C2E20197500F5302050208000A202020202020000000F106D02040001E08D0005000000000000010000001900000001";
                wstring newNameW2(newName2.begin(), newName2.end());
                lResult = RegSetValueEx(hkey, edidPath, 0, REG_BINARY, (LPBYTE)newNameW2.c_str(), newNameW2.length());
                if (newName2 != "")
                {
                    cout << "Registry EDID key successfully changed" << endl;
                }
                else
                {
                    cout << "Error changing the registry EDID key" << endl;
                }
            }
            else
            {
                cout << "Error reading registry key" << endl;
            }
        }
        else
        {
            cout << "Error opening registry key" << endl;
        }

        HKEY hkey_fw;
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\VMWare, Inc.", 0, KEY_QUERY_VALUE, &hkey_fw) == ERROR_SUCCESS)
        {
            cout << "This machine appears to be running VMWare." << endl;
        }
        else if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Oracle\\VirtualBox", 0, KEY_QUERY_VALUE, &hkey_fw) == ERROR_SUCCESS)
        {
            cout << "This machine appears to be running VirtualBox." << endl;
        }
        else if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\Hyper-V", 0, KEY_QUERY_VALUE, &hkey_fw) == ERROR_SUCCESS)
        {
            cout << "This machine appears to be running Hyper-V." << endl;
        }
        else
        {
            cout << "This machine does not appear to be running a virtual machine." << endl;
        }

      }

      if (system("del /F /S /Q %tmp%") == 0)
      {
          cout << "Successfully deleted temp files" << endl;
      }
      else
      {
          cout << "Error deleting temp files" << endl;
      }

    std::cin.ignore();
}
