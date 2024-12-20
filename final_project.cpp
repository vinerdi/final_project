#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

class FileManager {
public:
    void showContents(const std::string& path) {
        for (const auto& entry : fs::directory_iterator(path)) {
            std::cout << entry.path() << std::endl;
        }
    }

    void createFile(const std::string& path) {
        std::ofstream file(path);
        if (file) {
            std::cout << "File created: " << path << std::endl;
        } else {
            std::cerr << "Failed to create file: " << path << std::endl;
        }
    }

    void createDirectory(const std::string& path) {
        if (fs::create_directory(path)) {
            std::cout << "Directory created: " << path << std::endl;
        } else {
            std::cerr << "Failed to create directory: " << path << std::endl;
        }
    }

    void deleteFileOrDirectory(const std::string& path) {
        if (fs::remove_all(path)) {
            std::cout << "Deleted: " << path << std::endl;
        } else {
            std::cerr << "Failed to delete: " << path << std::endl;
        }
    }

    void renameFileOrDirectory(const std::string& oldPath, const std::string& newPath) {
        fs::rename(oldPath, newPath);
        std::cout << "Renamed: " << oldPath << " to " << newPath << std::endl;
    }

    void copyFileOrDirectory(const std::string& source, const std::string& destination) {
        fs::copy(source, destination, fs::copy_options::recursive);
        std::cout << "Copied: " << source << " to " << destination << std::endl;
    }

    uintmax_t calculateSize(const std::string& path) {
        if (fs::is_directory(path)) {
            uintmax_t size = 0;
            for (const auto& entry : fs::recursive_directory_iterator(path)) {
                if (fs::is_regular_file(entry.path())) {
                    size += fs::file_size(entry.path());
                }
            }
            return size;
        } else if (fs::is_regular_file(path)) {
            return fs::file_size(path);
        }
        return 0;
    }

    void searchByMask(const std::string& path, const std::string& mask) {
        for (const auto& entry : fs::recursive_directory_iterator(path)) {
            if (entry.path().filename().string().find(mask) != std::string::npos) {
                std::cout << entry.path() << std::endl;
            }
        }
    }
};

int main() {
    FileManager fm;
    fm.showContents(".");
    fm.createFile("test.txt");
    fm.createDirectory("test_dir");
    fm.deleteFileOrDirectory("test.txt");
    fm.renameFileOrDirectory("test_dir", "new_test_dir");
    fm.copyFileOrDirectory("new_test_dir", "copy_test_dir");
    std::cout << "Size: " << fm.calculateSize("copy_test_dir") << " bytes" << std::endl;
    fm.searchByMask(".", "test");
    return 0;
}
