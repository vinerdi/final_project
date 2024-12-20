#include <iostream> // ϳ��������� �������� ��� �����/������
#include <fstream> // ϳ��������� �������� ��� ������ � �������
#include <vector> // ϳ��������� �������� ��� ������������ �������
#include <string> // ϳ��������� �������� ��� ������ � �������
#include <ctime> // ϳ��������� �������� ��� ������ � �����
#include <cstdlib> // ϳ��������� �������� ��� ��������� ���������� �����
#include <algorithm> // ϳ��������� �������� ��� ������������ ��������� STL

class Hangman {
private:
    std::vector<std::string> words; // ������ ��� ��������� ���
    std::string currentWord; // ����� ��� ��������� ��������� �����
    std::string guessedWord; // ����� ��� ��������� ��������� �����
    std::vector<char> guessedLetters; // ������ ��� ��������� �������� ����
    int attempts; // ʳ������ �����
    time_t startTime; // ��� ������� ���

    void loadWords(const std::string& filename) {
        std::ifstream file(filename); // ³������� ����� ��� �������
        std::string word;
        while (file >> word) { // ������� ��� � �����
            words.push_back(word); // ��������� ����� �� �������
        }
    }

    void chooseWord() {
        if (words.empty()) { // ��������, �� ���������� �����
            std::cerr << "Error: No words loaded from file." << std::endl; // ��������� �������, ���� ����� �� ����������
            exit(1); // ���������� �������� � ����� �������
        }
        srand(static_cast<unsigned int>(time(0))); // ����������� ���������� ���������� �����
        currentWord = words[rand() % words.size()]; // ���� ����������� ����� � �������
        guessedWord = std::string(currentWord.size(), '_'); // ����������� ��������� ����� �������������
    }

    void displayStatus() {
        std::cout << "Word: " << guessedWord << std::endl; // ��������� ��������� �����
        std::cout << "Attempts left: " << attempts << std::endl; // ��������� ������� ��������� �����
        std::cout << "Guessed letters: "; // ��������� �������� ����
        for (char c : guessedLetters) {
            std::cout << c << ' '; // ��������� ����� ������� �����
        }
        std::cout << std::endl;
    }

    bool isWordGuessed() {
        return guessedWord == currentWord; // ��������, �� ������� ����� �������
    }

public:
    Hangman(const std::string& filename) : attempts(6) { // ����������� �����, ����������� ������� �����
        loadWords(filename); // ������������ ��� � �����
        chooseWord(); // ���� ����������� �����
        startTime = time(0); // ���������� ���� ������� ���
    }

    void play() {
        while (attempts > 0 && !isWordGuessed()) { // ���� ���, ���� � ������ � ����� �� �������
            displayStatus(); // ��������� ������� ���
            char guess;
            std::cout << "Enter a letter: "; // ����� �� �������� �����
            std::cin >> guess; // �������� �����
            guessedLetters.push_back(guess); // ��������� ����� �� ������� �������� ����

            if (currentWord.find(guess) != std::string::npos) { // ��������, �� � ����� � ����
                for (size_t i = 0; i < currentWord.size(); ++i) {
                    if (currentWord[i] == guess) { // ���� ����� � � ����, ������� ����������� �� �����
                        guessedWord[i] = guess;
                    }
                }
            } else {
                --attempts; // ���� ����� ���� � ����, �������� ������� �����
            }
        }

        time_t endTime = time(0); // ���������� ���� ��������� ���
        double duration = difftime(endTime, startTime); // ���������� ��������� ���

        if (isWordGuessed()) {
            std::cout << "Congratulations! You guessed the word: " << currentWord << std::endl; // ��������� ����������� ��� ������
        } else {
            std::cout << "Game over! The word was: " << currentWord << std::endl; // ��������� ����������� ��� �������
        }

        std::cout << "Time taken: " << duration << " seconds" << std::endl; // ��������� ��������� ���
        std::cout << "Attempts: " << 6 - attempts << std::endl; // ��������� ������� ������������ �����
        std::cout << "Guessed letters: "; // ��������� �������� ����
        for (char c : guessedLetters) {
            std::cout << c << ' '; // ��������� ����� ������� �����
        }
        std::cout << std::endl;
    }
};

int main() {
    Hangman game("words.txt"); // ��������� ��'���� ��� � ������ ���
    game.play(); // ������ ���
    return 0; // ���������� ��������
}
