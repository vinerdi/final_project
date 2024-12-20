#include <iostream> // Підключення бібліотеки для вводу/виводу
#include <fstream> // Підключення бібліотеки для роботи з файлами
#include <vector> // Підключення бібліотеки для використання векторів
#include <string> // Підключення бібліотеки для роботи з рядками
#include <ctime> // Підключення бібліотеки для роботи з часом
#include <cstdlib> // Підключення бібліотеки для генерації випадкових чисел
#include <algorithm> // Підключення бібліотеки для використання алгоритмів STL

class Hangman {
private:
    std::vector<std::string> words; // Вектор для зберігання слів
    std::string currentWord; // Змінна для зберігання поточного слова
    std::string guessedWord; // Змінна для зберігання вгаданого слова
    std::vector<char> guessedLetters; // Вектор для зберігання вгаданих літер
    int attempts; // Кількість спроб
    time_t startTime; // Час початку гри

    void loadWords(const std::string& filename) {
        std::ifstream file(filename); // Відкриття файлу для читання
        std::string word;
        while (file >> word) { // Читання слів з файлу
            words.push_back(word); // Додавання слова до вектора
        }
    }

    void chooseWord() {
        if (words.empty()) { // Перевірка, чи завантажені слова
            std::cerr << "Error: No words loaded from file." << std::endl; // Виведення помилки, якщо слова не завантажені
            exit(1); // Завершення програми з кодом помилки
        }
        srand(static_cast<unsigned int>(time(0))); // Ініціалізація генератора випадкових чисел
        currentWord = words[rand() % words.size()]; // Вибір випадкового слова з вектора
        guessedWord = std::string(currentWord.size(), '_'); // Ініціалізація вгаданого слова підкресленнями
    }

    void displayStatus() {
        std::cout << "Word: " << guessedWord << std::endl; // Виведення вгаданого слова
        std::cout << "Attempts left: " << attempts << std::endl; // Виведення кількості залишених спроб
        std::cout << "Guessed letters: "; // Виведення вгаданих літер
        for (char c : guessedLetters) {
            std::cout << c << ' '; // Виведення кожної вгаданої літери
        }
        std::cout << std::endl;
    }

    bool isWordGuessed() {
        return guessedWord == currentWord; // Перевірка, чи вгадане слово повністю
    }

public:
    Hangman(const std::string& filename) : attempts(6) { // Конструктор класу, ініціалізація кількості спроб
        loadWords(filename); // Завантаження слів з файлу
        chooseWord(); // Вибір випадкового слова
        startTime = time(0); // Збереження часу початку гри
    }

    void play() {
        while (attempts > 0 && !isWordGuessed()) { // Цикл гри, поки є спроби і слово не вгадане
            displayStatus(); // Виведення статусу гри
            char guess;
            std::cout << "Enter a letter: "; // Запит на введення літери
            std::cin >> guess; // Введення літери
            guessedLetters.push_back(guess); // Додавання літери до вектора вгаданих літер

            if (currentWord.find(guess) != std::string::npos) { // Перевірка, чи є літера в слові
                for (size_t i = 0; i < currentWord.size(); ++i) {
                    if (currentWord[i] == guess) { // Якщо літера є в слові, замінити підкреслення на літеру
                        guessedWord[i] = guess;
                    }
                }
            } else {
                --attempts; // Якщо літери немає в слові, зменшити кількість спроб
            }
        }

        time_t endTime = time(0); // Збереження часу закінчення гри
        double duration = difftime(endTime, startTime); // Обчислення тривалості гри

        if (isWordGuessed()) {
            std::cout << "Congratulations! You guessed the word: " << currentWord << std::endl; // Виведення повідомлення про виграш
        } else {
            std::cout << "Game over! The word was: " << currentWord << std::endl; // Виведення повідомлення про програш
        }

        std::cout << "Time taken: " << duration << " seconds" << std::endl; // Виведення тривалості гри
        std::cout << "Attempts: " << 6 - attempts << std::endl; // Виведення кількості використаних спроб
        std::cout << "Guessed letters: "; // Виведення вгаданих літер
        for (char c : guessedLetters) {
            std::cout << c << ' '; // Виведення кожної вгаданої літери
        }
        std::cout << std::endl;
    }
};

int main() {
    Hangman game("words.txt"); // Створення об'єкта гри з файлом слів
    game.play(); // Запуск гри
    return 0; // Завершення програми
}
