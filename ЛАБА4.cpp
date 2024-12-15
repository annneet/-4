// ЛАБА4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

void DeleteProbels(char* str) {
    int l = strlen(str);
    if (l == 0) return;
    char* result = new char[l + 1];
    int j = 0;
    bool probel = false;
    for (int i = 0; i < l; ++i) {
        if (str[i] == ' ') {
            if (!probel) {
                result[j++] = ' '; // Добавляем один пробел
                probel = true; // Устанавливаем флаг, что мы в пробеле
            }
        }
        else {
            result[j++] = str[i]; // Добавляем текущий символ
            probel = false; // Сбрасываем флаг
        }
    }
    if (j > 0 && result[0] == ' ') {
        std::memmove(result, result + 1, j - 1); // Удаляем пробел в начале
        --j; // Уменьшаем длину результирующей строки
    }
    if (j > 0 && result[j - 1] == ' ') {
        --j; // Удаляем пробел в конце
    }
    result[j] = '\0'; 
    strcpy_s(str, l+1,  result);
    delete[] result;
}

bool Sign(char c) {
    return (c == '!' || c == '?' || c == '.' || c == ',' || c == ';' || c == ':');
}

void RemoveSigns(const char* input, char* output) {
    bool last_was_punct = false;
    bool last_was_ellipsis = false;
    int output_index = 0;
    int length = strlen(input);

    for (int i = 0; i < length; ++i) {
        char current = input[i];
        // Проверяем, является ли текущий символ знаком препинания
        if (Sign(current)) {
            // Проверяем, не является ли это многоточием
            if (current == '.' && i + 1 < length && input[i + 1] == '.' && i + 2 < length && input[i + 2] == '.') {
                // Если предыдущий символ не был многоточием, добавляем его
                if (!last_was_ellipsis) {
                    output[output_index++] = '.';
                    output[output_index++] = '.';
                    output[output_index++] = '.';
                    last_was_ellipsis = true;
                    i += 2; // Пропускаем следующие два символа
                }
            }
            else {
                // Если это не многоточие и предыдущий символ также был знаком препинания
                if (!last_was_punct) {
                    output[output_index++] = current; // Добавляем текущий знак
                    last_was_punct = true; // Устанавливаем флаг
                }
            }
        }
        else {
            output[output_index++] = current; // Добавляем обычный символ
            last_was_punct = false; // Сбрасываем флаг
            last_was_ellipsis = false; // Сбрасываем флаг для многоточия
        }
    }
    output[output_index] = '\0'; // Завершаем строку нулем
}

void Register(char* input) {
    if (input[0] == '\0')
        return;
    input[0] = toupper(input[0]);
    for (size_t i = 1; input[i] != '\0'; ++i) {
        input[i] = tolower(input[i]);
    }
}

void NoNumbers(const char* str) {
    const char* start = str;
    const char* end;
    while (*start) {
        // Пропускаем пробелы
        while (*start == ' ') {
            start++;
        }
        // Если достигнут конец строки, выходим из цикла
        if (*start == '\0') {
            break;
        }
        // Находим конец слова
        end = start;
        while (*end != ' ' && *end != '\0') {
            end++;
        }
        // Проверяем слово на наличие цифр
        bool yesNumbers= false;
        for (const char* символ = start; символ < end; символ++) {
            if (isdigit(*символ)) {
                yesNumbers = true;
                break;
            }
        }
        // Если слово не содержит цифр, выводим его
        if (!yesNumbers) {
            for (const char* символ = start; символ < end; символ++) {
                cout << *символ;
            }
            cout << ' ';
        }
        // Переходим к следующему слову
        start = end;
    }
}

void NumberOfLetters(const char* str) {
    const char* start = str;
    const char* end;

    while (*start) {
        // Пропускаем пробелы
        while (*start == ' ') {
            start++;
        }
        // Если достигнут конец строки, выходим из цикла
        if (*start == '\0') {
            break;
        }
        // Находим конец слова
        end = start;
        while (*end != ' ' && *end != '\0') {
            end++;
        }
        // Подсчитываем количество букв в слове
        int number = 0;
        for (const char* symbol = start; symbol < end; symbol++) {
            if (isalpha(*symbol)) { // Проверяем, является ли символ буквой
                number++;
            }
        }
        // Выводим количество букв в слове
        cout << "Количество букв в слове \"";
        for (const char* symbol = start; symbol < end; symbol++) {
            cout << *symbol;
        }
        cout << "\": " << number << endl;
        // Переходим к следующему слову
        start = end;
    }
}

void LinearSearch(const char* str, const char* substr) { //    Ф У Н К Ц И Я  Д Л Я  Л И Н Е Й Н О Г О  П О И С К А
    int lengthStr = strlen(str);
    int lengthSubstr = strlen(substr);
    bool bober = false;
    // Линейный поиск подстроки
    for (int i = 0; i <= lengthStr - lengthSubstr; i++) {
        int j;
        for (j = 0; j < lengthSubstr; j++) {
            if (str[i + j] != substr[j]) {
                break;
            }
        }
        if (j == lengthSubstr) { // Если мы нашли подстроку
            cout << i << ' ';
            bober = true;
        }
    }
    if (!bober) {
        cout << "Подстрока не найдена." << endl;
    }
}

void PrefixFunction(const char* substr, vector<int>& prefix) {
    int lengthSubstr = strlen(substr);
    prefix.resize(lengthSubstr);
    prefix[0] = 0; // Начальное значение префикса
    int j = 0; // Длина предыдущего префикса
    for (int i = 1; i < lengthSubstr; ++i) {
        while (j > 0 && substr[i] != substr[j]) {
            j = prefix[j - 1]; // Переход к предыдущему префиксу
        }
        if (substr[i] == substr[j]) {
            ++j; // Увеличиваем длину префикса
        }
        prefix[i] = j; // Устанавливаем значение префикса
    }
}

// Функция для поиска подстроки с использованием алгоритма КМП
void АлгоритмКМП(const char* str, const char* substr) {
    int lengthStr = strlen(str);
    int lengthSubstr = strlen(substr);

    vector<int> prefix;
    PrefixFunction(substr, prefix);

    int j = 0; // Индекс для подстроки
    for (int i = 0; i < lengthStr; ++i) {
        while (j > 0 && str[i] != substr[j]) {
            j = prefix[j - 1]; // Переход к предыдущему префиксу
        }
        if (str[i] == substr[j]) {
            ++j; // Увеличиваем длину совпадения
        }
        if (j == lengthSubstr) {
            cout << i - j + 1 << ' ';
            j = prefix[j - 1]; // Продолжаем поиск
        }
    }
}

int main()
{
    setlocale(0, "");
    const int n = 501;
    char str0[n], str[n], substr[n];
    cout <<"Введите строку: " ;
    cin.getline(str0, 501);
    cout << "Отформатированная строка: ";
    DeleteProbels(str0);
    RemoveSigns(str0, str);
    Register(str);
    cout << str << endl << "\nСлова последовательности, не содержащие цифр: ";
    NoNumbers(str);
    cout << endl << "Кол-во символов в каждом слове исходной последовательности" << endl;
    NumberOfLetters(str);
    cout << endl << "ПОИСК ПОДСТРОКИ В СТРОКЕ" << endl << "Введите подстроку: ";
    cin.getline(substr, 501);
    cout << "Подстрока найдена в позиции: ";
    АлгоритмКМП(str, substr);
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
