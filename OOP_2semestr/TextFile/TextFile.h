#ifndef TEXTFILE_H
#define TEXTFILE_H

#include <vector>
#include <filesystem>
#include <string>
#include <fstream>
#include <iostream>
#include <set>

namespace fs = std::filesystem;

template <class T> class TextFile{

    void readFromFile(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) return;

        std::string line;
        while (std::getline(file, line)) {
            data.push_back(T(line.c_str()));
        }
        file.close();
    }
public:
    std::vector<T> data;   
    TextFile() = default;

    TextFile(const std::string& path, bool readMode = true) {
        if (readMode) {
            readFromFile(path);
        } else {

        }
    }

    TextFile(const std::string& dirPath, const std::string& extension) {
        if (!fs::exists(dirPath) || !fs::is_directory(dirPath)) {
            return; // Если директории нет просто выходим
        }

        // Идем по всем файлам в папке
        for (const auto& entry : fs::directory_iterator(dirPath)) {
            // Проверяем что это обычный файл и его расширение совпадает с маской
            if (entry.is_regular_file() && entry.path().extension() == extension) {
                readFromFile(entry.path().string());
            }
        }
    }

    TextFile(const TextFile<T>& other) {
        this->data = other.data;
    }

    // Берет содержимое file2 и дописывает его в конец file1
    static void appendFileToFile(const std::string& file2Path, const std::string& file1Path) {
        // Открываем файл2 для чтения
        std::ifstream file2(file2Path);
        if (!file2.is_open()) {
            std::cerr << "Error with file: " << file2Path << std::endl;
            return;
        }

        // Открываем файл1 в режиме дописывания (std::ios::app)
        std::ofstream file1(file1Path, std::ios::app);
        if (!file1.is_open()) {
            std::cerr << "Error with file: " << file1Path << std::endl;
            file2.close();
            return;
        }

        // Построчно переливаем данные из file2 в конец file1
        std::string line;
        while (std::getline(file2, line)) {
            file1 << line << "\n";
        }

        file2.close();
        file1.close();
    }

    static void createUniqueRowsFile(const std::vector<std::string>& filesToRead, const std::string& outputFile) {
        std::set<T> uniqueRows;

        for (const auto& filePath : filesToRead) {
            // Используем конструктор для чтения файла
            TextFile<T> tempFile(filePath);
            for (const auto& row : tempFile.data) {
                uniqueRows.insert(row); // Если строка уже есть, она просто не добавится
            }
        }

        // Записываем результат в итоговый файл
        std::ofstream out(outputFile);
        if (!out.is_open()) {
            std::cerr << "Error opening output file: " << outputFile << std::endl;
            return;
        }

        for (const auto& row : uniqueRows) {
            out << row << "\n"; 
        }
        out.close();
    }

    static void createCommonRowsFile(const std::vector<std::string>& filesToRead, const std::string& outputFile) {
        if (filesToRead.empty()) return;

        // Загружаем первый файл во множество как стартовую базу для сравнения
        std::set<T> commonRows;
        {
            TextFile<T> firstFile(filesToRead[0]);
            for (const auto& row : firstFile.data) {
                commonRows.insert(row);
            }
        }

        // Для каждого следующего файла оставляем только те элементы, которые в нем тоже есть
        for (size_t i = 1; i < filesToRead.size(); ++i) {
            std::set<T> currentFileRows;
            TextFile<T> tempFile(filesToRead[i]);
            for (const auto& row : tempFile.data) {
                currentFileRows.insert(row);
            }

            // Оставляем только пересечение
            std::set<T> intersection;
            for (const auto& row : commonRows) {
                if (currentFileRows.count(row)) { // Если строка есть и в новом файле
                    intersection.insert(row);
                }
            }
            commonRows = std::move(intersection); // Обновляем базу общих строк
        }

        // Записываем результат
        std::ofstream out(outputFile);
        if (!out.is_open()) {
            std::cerr << "Error opening output file: " << outputFile << std::endl;
            return;
        }

        for (const auto& row : commonRows) {
            out << row << "\n";
        }
        out.close();
    }
};

#endif