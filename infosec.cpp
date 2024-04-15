#include <iostream>

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <random>

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

int main()
{
    return labrab6();
}
