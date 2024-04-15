#include <iostream>

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

enum class Permission { READ, WRITE, GRANT };

// Function to check if a permission exists in the list
bool hasPermission(const vector<Permission>& permissions, Permission permission) {
    return find(permissions.begin(), permissions.end(), permission) != permissions.end();
}

// User class to store username and permissions
class User {
public:
    string username;
    vector<vector<vector<Permission>>> permissions;

    User(const string& username, bool isAdmin = false) : username(username) {
        permissions.resize(3);
        for (int i = 0; i < 3; ++i) {
            permissions[i].resize(3);
            if (isAdmin) {
                for (int j = 0; j < 3; ++j) {
                    permissions[i][j] = { Permission::READ, Permission::WRITE, Permission::GRANT };
                }
            }
        }
    }
};

// Function to find the user object by username
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

        if (hasPermission(currentUser->permissions[object - 1][0], permission)) {
            cout << "Permission granted for object " << object << endl;
        }
        else {
            cout << "Access denied for object " << object << endl;
        }
    }

    return 0;
}

int main()
{
    return labrab6();
}
