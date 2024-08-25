#include <iostream>
#include <string>
#include <dirent.h> // For POSIX directory handling
#include <sys/stat.h> // For mkdir
#include <unistd.h> // For chdir, getcwd

void listFiles() {
    DIR* dir;
    struct dirent* entry;
    std::string path = "."; // Current directory

    std::cout << "Listing files in: " << path << "\n";
    dir = opendir(path.c_str());

    if (dir == NULL) {
        std::cerr << "Error opening directory.\n";
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        std::cout << entry->d_name << "\n";
    }

    closedir(dir);
}

void createDirectory() {
    std::string dirName;
    std::cout << "Enter the name of the directory to create: ";
    std::cin >> dirName;

    if (mkdir(dirName.c_str(), 0755) == 0) {
        std::cout << "Directory created successfully.\n";
    } else {
        std::cerr << "Failed to create directory. It may already exist or there was an error.\n";
    }
}

void changeDirectory() {
    std::string path;
    std::cout << "Enter the path of the directory to change to: ";
    std::cin >> path;

    if (chdir(path.c_str()) == 0) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            std::cout << "Directory changed to: " << cwd << "\n";
        } else {
            std::cerr << "Error getting current directory.\n";
        }
    } else {
        std::cerr << "Error: Unable to change directory.\n";
    }
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    int choice;

    do {
        clearScreen();
        std::cout << "Directory Management System\n";
        std::cout << "1. List files in current directory\n";
        std::cout << "2. Create a new directory\n";
        std::cout << "3. Change current directory\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            listFiles();
            break;
        case 2:
            createDirectory();
            break;
        case 3:
            changeDirectory();
            break;
        case 4:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }

        if (choice != 4) {
            std::cout << "Press Enter to continue...";
            std::cin.ignore(); // Ignore any leftover newline characters in the input buffer
            std::cin.get(); // Wait for user input
        }

    } while (choice != 4);

    return 0;
}

