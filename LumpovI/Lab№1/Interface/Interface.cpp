#include <iostream>
#include "tbitfield.h"
#include "tset.h"
#include <windows.h>

void clearInput() {
    std::cin.clear();
    std::cin.ignore(1000000, '\n');
}

/*
 * Безопасный ввод целого числа с проверкой диапазона.
 */
int readInt(const char* prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            clearInput();
            std::cerr << "Ошибка: введите целое число!\n";
            continue;
        }

        clearInput();

        if (value < minVal || value > maxVal) {
            std::cerr << "Ошибка: значение должно быть от " << minVal
                << " до " << maxVal << "!\n";
            continue;
        }

        return value;
    }
}

/*
 * Вывод разделителя.
 */
void printSeparator() {
    std::cout << "----------------------------------------\n";
}

// ============================================================
// МЕНЮ ДЛЯ TBitField
// ============================================================

void bitFieldMenu() {
    std::cout << "\n=== Работа с битовым полем ===\n";
    int len = readInt("Введите длину битового поля: ", 1, 10000);

    TBitField bf(len);

    int choice;
    do {
        printSeparator();
        std::cout << "Текущее поле: " << bf << "\n";
        std::cout << "Длина: " << bf.GetLength() << " бит\n";
        printSeparator();
        std::cout << "1. Установить бит\n";
        std::cout << "2. Очистить бит\n";
        std::cout << "3. Получить значение бита\n";
        std::cout << "4. Вывести поле\n";
        std::cout << "5. Операция ИЛИ с другим полем\n";
        std::cout << "6. Операция И с другим полем\n";
        std::cout << "7. Отрицание (NOT)\n";
        std::cout << "8. Сравнить с другим полем\n";
        std::cout << "9. Скопировать поле\n";
        std::cout << "10. Ввести поле с клавиатуры\n";
        std::cout << "0. Назад\n";
        std::cout << "Выбор: ";

        std::cin >> choice;
        if (std::cin.fail()) {
            clearInput();
            continue;
        }
        clearInput();

        switch (choice) {
        case 1: {
            int n = readInt("Номер бита: ", 0, bf.GetLength() - 1);
            bf.SetBit(n);
            std::cout << "Бит " << n << " установлен.\n";
            break;
        }
        case 2: {
            int n = readInt("Номер бита: ", 0, bf.GetLength() - 1);
            bf.ClrBit(n);
            std::cout << "Бит " << n << " очищен.\n";
            break;
        }
        case 3: {
            int n = readInt("Номер бита: ", 0, bf.GetLength() - 1);
            std::cout << "Бит " << n << " = " << bf.GetBit(n) << "\n";
            break;
        }
        case 4:
            std::cout << "Поле: " << bf << "\n";
            break;
        case 5: {
            int len2 = readInt("Длина второго поля: ", 1, 10000);
            TBitField bf2(len2);
            std::cout << "Введите биты второго поля (0/1 через пробел): ";
            std::cin >> bf2;
            if (std::cin.fail()) {
                clearInput();
                std::cerr << "Ошибка ввода!\n";
                break;
            }
            TBitField result = bf | bf2;
            std::cout << "Результат ИЛИ: " << result << "\n";
            break;
        }
        case 6: {
            int len2 = readInt("Длина второго поля: ", 1, 10000);
            TBitField bf2(len2);
            std::cout << "Введите биты второго поля (0/1 через пробел): ";
            std::cin >> bf2;
            if (std::cin.fail()) {
                clearInput();
                std::cerr << "Ошибка ввода!\n";
                break;
            }
            TBitField result = bf & bf2;
            std::cout << "Результат И: " << result << "\n";
            break;
        }
        case 7: {
            TBitField result = ~bf;
            std::cout << "Отрицание: " << result << "\n";
            break;
        }
        case 8: {
            int len2 = readInt("Длина второго поля: ", 1, 10000);
            TBitField bf2(len2);
            std::cout << "Введите биты второго поля (0/1 через пробел): ";
            std::cin >> bf2;
            if (std::cin.fail()) {
                clearInput();
                std::cerr << "Ошибка ввода!\n";
                break;
            }
            std::cout << "Поля " << (bf == bf2 ? "равны" : "не равны") << "\n";
            break;
        }
        case 9: {
            TBitField copy(bf);
            std::cout << "Копия: " << copy << "\n";
            break;
        }
        case 10: {
            std::cout << "Введите " << bf.GetLength()
                << " битов через пробел: ";
            std::cin >> bf;
            if (std::cin.fail()) {
                clearInput();
                std::cerr << "Ошибка ввода!\n";
            }
            break;
        }
        case 0:
            break;
        default:
            std::cout << "Неверный выбор.\n";
        }
    } while (choice != 0);
}

// ============================================================
// МЕНЮ ДЛЯ TSet
// ============================================================

void setMenu() {
    std::cout << "\n=== Работа с множеством ===\n";
    int power = readInt("Введите максимальную мощность множества: ", 1, 10000);

    TSet s(power);

    int choice;
    do {
        printSeparator();
        std::cout << "Текущее множество: " << s << "\n";
        std::cout << "Мощность: " << s.GetMaxPower() << "\n";
        printSeparator();
        std::cout << "1. Добавить элемент\n";
        std::cout << "2. Удалить элемент\n";
        std::cout << "3. Проверить наличие элемента\n";
        std::cout << "4. Объединение с элементом\n";
        std::cout << "5. Разность с элементом\n";
        std::cout << "6. Объединение с другим множеством\n";
        std::cout << "7. Пересечение с другим множеством\n";
        std::cout << "8. Дополнение\n";
        std::cout << "9. Сравнить с другим множеством\n";
        std::cout << "10. Ввести множество с клавиатуры\n";
        std::cout << "0. Назад\n";
        std::cout << "Выбор: ";

        std::cin >> choice;
        if (std::cin.fail()) {
            clearInput();
            continue;
        }
        clearInput();

        switch (choice) {
        case 1: {
            int e = readInt("Элемент для добавления: ", 0, s.GetMaxPower() - 1);
            s.InsElem(e);
            std::cout << "Элемент " << e << " добавлен.\n";
            break;
        }
        case 2: {
            int e = readInt("Элемент для удаления: ", 0, s.GetMaxPower() - 1);
            s.DelElem(e);
            std::cout << "Элемент " << e << " удалён.\n";
            break;
        }
        case 3: {
            int e = readInt("Элемент для проверки: ", 0, s.GetMaxPower() - 1);
            std::cout << "Элемент " << e << " "
                << (s.IsMember(e) ? "принадлежит" : "не принадлежит")
                << " множеству.\n";
            break;
        }
        case 4: {
            int e = readInt("Элемент: ", 0, s.GetMaxPower() - 1);
            TSet result = s + e;
            std::cout << "Результат: " << result << "\n";
            break;
        }
        case 5: {
            int e = readInt("Элемент: ", 0, s.GetMaxPower() - 1);
            TSet result = s - e;
            std::cout << "Результат: " << result << "\n";
            break;
        }
        case 6: {
            TSet other(s.GetMaxPower());
            std::cout << "Введите второе множество (например, { 1, 2, 3 }): ";
            std::cin >> other;
            if (std::cin.fail()) {
                clearInput();
                std::cerr << "Ошибка ввода!\n";
                break;
            }
            TSet result = s + other;
            std::cout << "Объединение: " << result << "\n";
            break;
        }
        case 7: {
            TSet other(s.GetMaxPower());
            std::cout << "Введите второе множество (например, { 1, 2, 3 }): ";
            std::cin >> other;
            if (std::cin.fail()) {
                clearInput();
                std::cerr << "Ошибка ввода!\n";
                break;
            }
            TSet result = s * other;
            std::cout << "Пересечение: " << result << "\n";
            break;
        }
        case 8: {
            TSet result = ~s;
            std::cout << "Дополнение: " << result << "\n";
            break;
        }
        case 9: {
            TSet other(s.GetMaxPower());
            std::cout << "Введите второе множество: ";
            std::cin >> other;
            if (std::cin.fail()) {
                clearInput();
                std::cerr << "Ошибка ввода!\n";
                break;
            }
            std::cout << "Множества " << (s == other ? "равны" : "не равны") << "\n";
            break;
        }
        case 10: {
            std::cout << "Введите множество (например, { 1, 3, 5 }): ";
            std::cin >> s;
            if (std::cin.fail()) {
                clearInput();
                std::cerr << "Ошибка ввода!\n";
            }
            break;
        }
        case 0:
            break;
        default:
            std::cout << "Неверный выбор.\n";
        }
    } while (choice != 0);
}

// ============================================================
// ГЛАВНОЕ МЕНЮ
// ============================================================

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    int choice;
    do {
        std::cout << "\n========== БИТОВЫЕ ПОЛЯ И МНОЖЕСТВА ==========\n";
        std::cout << "1. Работа с TBitField (битовое поле)\n";
        std::cout << "2. Работа с TSet (множество)\n";
        std::cout << "0. Выход\n";
        std::cout << "==============================================\n";
        std::cout << "Выбор: ";

        std::cin >> choice;
        if (std::cin.fail()) {
            clearInput();
            continue;
        }
        clearInput();

        switch (choice) {
        case 1:
            bitFieldMenu();
            break;
        case 2:
            setMenu();
            break;
        case 0:
            std::cout << "До свидания!\n";
            break;
        default:
            std::cout << "Неверный выбор.\n";
        }
    } while (choice != 0);

    return 0;
}