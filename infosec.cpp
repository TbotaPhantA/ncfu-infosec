#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <dirent.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <random>
#include <cmath>
#include <algorithm> // for std::fill
#include <numeric>


using namespace std;

enum class Permission {
    READ,
    WRITE,
    GRANT
};

std::vector<Permission> get_random_permissions() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> size_dist(0, 3);

    int num_permissions = size_dist(gen);
    std::vector<Permission> permissions;
    for (int i = 0; i < num_permissions; ++i) {
        std::uniform_int_distribution<int> dist(1, static_cast<int>(Permission::GRANT));
        Permission permission(static_cast<Permission>(dist(gen)));
        if (std::any_of(permissions.begin(), permissions.end(),
            [&permission](const Permission& p) { return p == permission; })) {
            continue;
        }
        permissions.push_back(permission);
    }
    return permissions;
}

std::string permission_to_string(Permission permission) {
    switch (permission) {
		case Permission::READ:
			return "READ";
		case Permission::WRITE:
			return "WRITE";
		case Permission::GRANT:
			return "GRANT";
		default:
			return "UNKNOWN";
    }
}

bool hasPermission(const vector<Permission>& permissions, Permission permission) {
    return find(permissions.begin(), permissions.end(), permission) != permissions.end();
}

class User {
public:
    string username;
    vector<vector<Permission>> permissions;

    User(const string& username, bool isAdmin = false) : username(username) {
        permissions.resize(3);
        for (int i = 0; i < 3; ++i) {
            permissions[i].resize(3);
            if (isAdmin) {
				permissions[i] = { Permission::READ, Permission::WRITE, Permission::GRANT };
            } else {
				permissions[i] = get_random_permissions();
            }
        }
    }

    void print_permissions() const {
        std::cout << "User: " << username << std::endl;
        for (int i = 0; i < 3; ++i) {
            std::cout << "Object " << i + 1 << ": ";
			for (const auto& permission : permissions[i]) {
				std::cout << permission_to_string(permission) << " ";
			}
            std::cout << endl;
        }
    }
};

User* findUser(const string& username, vector<User>& users) {
    for (User& user : users) {
        if (user.username == username) {
            return &user;
        }
    }
    return nullptr;
}

int labrab6() {
    vector<User> users = { User("admin", true), User("user1"), User("user2") };

    string username;
    cout << "Login (username): ";
    cin >> username;

    User* currentUser = findUser(username, users);

    if (!currentUser) {
        cout << "Invalid username." << endl;
        return 1;
    }

    currentUser->print_permissions();

    int object, action;
    while (true) {
        cout << "\nChoose object (1-3) or 0 to exit: ";
        cin >> object;
        if (object == 0) {
            break;
        }
        else if (object < 1 || object > 3) {
            cout << "Invalid object number." << endl;
            continue;
        }

        cout << "Choose action (1 - read, 2 - write, 3 - grant): ";
        cin >> action;

        Permission permission;
        switch (action) {
        case 1:
            permission = Permission::READ;
            break;
        case 2:
            permission = Permission::WRITE;
            break;
        case 3:
            permission = Permission::GRANT;
            break;
        default:
            cout << "Invalid action number." << endl;
            continue;
        }

        if (hasPermission(currentUser->permissions[object - 1], permission)) {
            cout << "Permission granted for object " << object << endl;
        }
        else {
            cout << "Access denied for object " << object << endl;
        }
    }

    return 0;
}

int labrab7() {
    const int num_strings = 10;
    const int string_length = 7;
    std::string lowercase_letters("abcdefghijklmnopqrstuvwxyz");

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, lowercase_letters.size() - 1);

    for (int i = 0; i < num_strings; ++i) {
        std::string passwords;
        for (int j = 0; j < string_length; ++j) {
            int random_index = distribution(generator);
            passwords += lowercase_letters[random_index];
        }
        std::cout << passwords << std::endl;
    }
    return 0;
}

// ------------------------------------------------------
// ------------------------------------------------------
// ---------------------LABRAB 8-------------------------
// ------------------------------------------------------
// ------------------------------------------------------

#include<iostream>
#include<stdlib.h>
#include<math.h>
#include <string.h>
#include <fstream>
#include <iostream>

using namespace std;

int x, y, n, t, i, flag;
long int e[50], d[50], temp[50], j;
char en[50], m[50];
char msg[100];
int prime(long int);
void encryption_key();
long int cd(long int);
void encrypt();
void decrypt();

int labrab8()
{
    x = 7;
    y = 13;
    std::ifstream inputFile("text.txt");
    string line;
    std::getline(inputFile, line);
    for (int i = 0; i < line.size(); i++) {
        msg[i] = line[i];
    }

    for (i = 0; msg[i] != NULL; i++)
        m[i] = msg[i];
    n = x * y;
    t = (x - 1) * (y - 1);

    encryption_key();
    cout << "\nPOSSIBLE VALUES OF e AND d ARE\n";

    for (i = 0; i < j - 1; i++)
        cout << "\n" << e[i] << "\t" << d[i];

    encrypt();
    decrypt();
    return 0;
}

int prime(long int pr)
{
    int i;
    j = sqrt(pr);
    for (i = 2; i <= j; i++)
    {
        if (pr % i == 0)
            return 0;
    }
    return 1;
}

void encryption_key()
{
    int k;
    k = 0;
    for (i = 2; i < t; i++)
    {
        if (t % i == 0)
            continue;
        flag = prime(i);
        if (flag == 1 && i != x && i != y)
        {
            e[k] = i;
            flag = cd(e[k]);
            if (flag > 0)
            {
                d[k] = flag;
                k++;
            }
            if (k == 99)
                break;
        }
    }
}

long int cd(long int a)
{
    long int k = 1;
    while (1)
    {
        k = k + t;
        if (k % a == 0)
            return(k / a);
    }
}

void encrypt()
{
    long int pt, ct, key = e[0], k, len;
    i = 0;
    len = strlen(msg);

    while (i != len)
    {
        pt = m[i];
        pt = pt - 96;
        k = 1;
        for (j = 0; j < key; j++)
        {
            k = k * pt;
            k = k % n;
        }
        temp[i] = k;
        ct = k + 96;
        en[i] = ct;
        i++;
    }
    en[i] = -1;
    string encrypted_str;
    for (i = 0; en[i] != -1; i++)
        encrypted_str.push_back(en[i]);
    std::ofstream outputFile1("encrypted_text.txt");
    outputFile1 << encrypted_str << endl;
}

void decrypt()
{
    long int pt, ct, key = d[0], k;
    i = 0;
    while (en[i] != -1)
    {
        ct = temp[i];
        k = 1;
        for (j = 0; j < key; j++)
        {
            k = k * ct;
            k = k % n;
        }
        pt = k + 96;
        m[i] = pt;
        i++;
    }
    m[i] = -1;
    string decrypted_str;
    for (i = 0; m[i] != -1; i++)
        decrypted_str.push_back(m[i]);
    std::ofstream outputFile2("decrypted_text.txt");
    outputFile2 << decrypted_str << endl;
}

// -----------------------LABRAB 9-------------------------------------
#include <stdio.h>
#include <Windows.h>
#include <Iphlpapi.h>
#include <Assert.h>
#pragma comment(lib, "iphlpapi.lib")

string getMAC() {
    PIP_ADAPTER_INFO AdapterInfo;
    DWORD dwBufLen = sizeof(IP_ADAPTER_INFO);
    char* mac_addr = (char*)malloc(18);

    AdapterInfo = (IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));
    if (AdapterInfo == NULL) {
        // printf("Error allocating memory needed to call GetAdaptersinfo\n");
        free(mac_addr);
        return NULL; // it is safe to call free(NULL)
    }

    // Make an initial call to GetAdaptersInfo to get the necessary size into the dwBufLen variable
    if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == ERROR_BUFFER_OVERFLOW) {
        free(AdapterInfo);
        AdapterInfo = (IP_ADAPTER_INFO*)malloc(dwBufLen);
        if (AdapterInfo == NULL) {
            // printf("Error allocating memory needed to call GetAdaptersinfo\n");
            free(mac_addr);
            return NULL;
        }
    }

    if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == NO_ERROR) {
        // Contains pointer to current adapter info
        PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;
        do {
            // technically should look at pAdapterInfo->AddressLength
            //   and not assume it is 6.
            sprintf(mac_addr, "%02X:%02X:%02X:%02X:%02X:%02X",
                pAdapterInfo->Address[0], pAdapterInfo->Address[1],
                pAdapterInfo->Address[2], pAdapterInfo->Address[3],
                pAdapterInfo->Address[4], pAdapterInfo->Address[5]);
            // printf("Address: %s, mac: %s\n", pAdapterInfo->IpAddressList.IpAddress.String, mac_addr);
            // print them all, return the last one.
            // return mac_addr;

            // printf("\n");
            pAdapterInfo = pAdapterInfo->Next;
        } while (pAdapterInfo);
    }
    free(AdapterInfo);
    return (string)mac_addr; // caller must free.
}

int getDiskSerialNumber() {
    TCHAR szVolName[256];
    DWORD currentDiskSerialNumber;
    DWORD dwMaxComSize;
    DWORD dwFlags;
    TCHAR szFS[256];
    BOOL bRes;
    string volumeStr = "c:\\";
    std::wstring stemp = std::wstring(volumeStr.begin(), volumeStr.end());
    LPCWSTR volume = stemp.c_str();
    bRes = GetVolumeInformation(volume, szVolName, sizeof(szVolName), &currentDiskSerialNumber,
        &dwMaxComSize, &dwFlags, szFS, sizeof(szFS));
    return currentDiskSerialNumber;
}

int labrab9()
{

    int allowedDiskSerialNumber = 12341234;
    int currentDiskSerialNumber = getDiskSerialNumber();

    string allowedMacAdress = "A5:D7:F9:B9:C9:44";
    string currentMacAddress = getMAC();

    bool canExecute =
        allowedMacAdress == currentMacAddress &&
        allowedDiskSerialNumber == currentDiskSerialNumber;

    if (!canExecute) {
        cout << "Cannot execute the program..." << endl;
    }

    cout << "Executing the program" << endl;

    return 0;
}


int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // return labrab6();
    // return labrab7();
    // return labrab8();
    return labrab9();
}
