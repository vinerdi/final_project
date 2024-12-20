#include <iostream> // Підключення бібліотеки для роботи з введенням/виведенням
#include <filesystem> // Підключення бібліотеки для роботи з файловою системою
#include <fstream> // Підключення бібліотеки для роботи з файлами
#include <string> // Підключення бібліотеки для роботи з рядками

namespace fs = std::filesystem; // Створення псевдоніму для простору імен std::filesystem

class FileManager { // Оголошення класу FileManager
public:
    void showContents(const std::string& path) { // Метод для відображення вмісту директорії
        for (const auto& entry : fs::directory_iterator(path)) { // Ітерація по всіх елементах вказаної директорії
            std::cout << entry.path() << std::endl; // Виведення шляху кожного елемента
        }
    }

    void createFile(const std::string& path) { // Метод для створення файлу
        std::ofstream file(path); // Створення об'єкта ofstream для запису у файл
        if (file) { // Перевірка, чи файл успішно створений
            std::cout << "File created: " << path << std::endl; // Виведення повідомлення про успішне створення файлу
        } else {
            std::cerr << "Failed to create file: " << path << std::endl; // Виведення повідомлення про помилку створення файлу
        }
    }

    void createDirectory(const std::string& path) { // Метод для створення директорії
        if (fs::create_directory(path)) { // Перевірка, чи директорія успішно створена
            std::cout << "Directory created: " << path << std::endl; // Виведення повідомлення про успішне створення директорії
        } else {
            std::cerr << "Failed to create directory: " << path << std::endl; // Виведення повідомлення про помилку створення директорії
        }
    }

    void deleteFileOrDirectory(const std::string& path) { // Метод для видалення файлу або директорії
        if (fs::remove_all(path)) { // Видалення всіх елементів за вказаним шляхом
            std::cout << "Deleted: " << path << std::endl; // Виведення повідомлення про успішне видалення
        } else {
            std::cerr << "Failed to delete: " << path << std::endl; // Виведення повідомлення про помилку видалення
        }
    }

    void renameFileOrDirectory(const std::string& oldPath, const std::string& newPath) { // Метод для перейменування файлу або директорії
        fs::rename(oldPath, newPath); // Перейменування файлу або директорії
        std::cout << "Renamed: " << oldPath << " to " << newPath << std::endl; // Виведення повідомлення про успішне перейменування
    }

    void copyFileOrDirectory(const std::string& source, const std::string& destination) { // Метод для копіювання файлу або директорії
        fs::copy(source, destination, fs::copy_options::recursive); // Рекурсивне копіювання файлу або директорії
        std::cout << "Copied: " << source << " to " << destination << std::endl; // Виведення повідомлення про успішне копіювання
    }

    uintmax_t calculateSize(const std::string& path) { // Метод для обчислення розміру файлу або директорії
        if (fs::is_directory(path)) { // Перевірка, чи є шлях директорією
            uintmax_t size = 0; // Ініціалізація змінної для зберігання розміру
            for (const auto& entry : fs::recursive_directory_iterator(path)) { // Рекурсивна ітерація по всіх елементах директорії
                if (fs::is_regular_file(entry.path())) { // Перевірка, чи є елемент файлом
                    size += fs::file_size(entry.path()); // Додавання розміру файлу до загального розміру
                }
            }
            return size; // Повернення загального розміру
        } else if (fs::is_regular_file(path)) { // Перевірка, чи є шлях файлом
            return fs::file_size(path); // Повернення розміру файлу
        }
        return 0; // Повернення 0, якщо шлях не є файлом або директорією
    }

    void searchByMask(const std::string& path, const std::string& mask) { // Метод для пошуку файлів за маскою
        for (const auto& entry : fs::recursive_directory_iterator(path)) { // Рекурсивна ітерація по всіх елементах директорії
            if (entry.path().filename().string().find(mask) != std::string::npos) { // Перевірка, чи містить ім'я файлу маску
                std::cout << entry.path() << std::endl; // Виведення шляху файлу, що відповідає масці
            }
        }
    }
};

int main() { // Головна функція
    FileManager fm; // Створення об'єкта класу FileManager
    fm.showContents("."); // Відображення вмісту поточної директорії
    fm.createFile("test.txt"); // Створення файлу test.txt
    fm.createDirectory("test_dir"); // Створення директорії test_dir
    fm.deleteFileOrDirectory("test.txt"); // Видалення файлу test.txt
    fm.renameFileOrDirectory("test_dir", "new_test_dir"); // Перейменування директорії test_dir в new_test_dir
    fm.copyFileOrDirectory("new_test_dir", "copy_test_dir"); // Копіювання директорії new_test_dir в copy_test_dir
    std::cout << "Size: " << fm.calculateSize("copy_test_dir") << " bytes" << std::endl; // Виведення розміру директорії copy_test_dir
    fm.searchByMask(".", "test"); // Пошук файлів за маскою "test" в поточній директорії
    return 0; // Повернення 0, що означає успішне завершення програми
}
