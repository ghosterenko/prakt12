#include <iostream>
#include <Windows.h>
#include <conio.h>

int main()
{
    setlocale(LC_ALL, "ru");

    std::cout << "Выбирете процесс: " << std::endl;
    std::cout << "1. Фоновый: " << std::endl;
    std::cout << "2. Нормальный: " << std::endl;
    std::cout << "3. Высокий: " << std::endl;
    int n;
    std::cin >> n;
    switch (n) {
    case 1:
        SetPriorityClass(GetCurrentProcess(), IDLE_PRIORITY_CLASS);
        break;
    case 2:
        SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
        break;
    case 3:
        SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
        break;
    default:
        break;
    }
    // 1. Открывает иминованный мьютекс
    HANDLE OpenMutexPrinter = OpenMutexA(MUTANT_ALL_ACCESS, FALSE, "PrinterMutex");
    if (OpenMutexPrinter == NULL) {
        std::cout << "Принтер не найден" << std::endl;
        return 0;
    }
    // 2. Ожидает нажатие от пользователя
    std::cout << "Нажмите на любую клавишу" << std::endl;
    std::cin.get();

    // 3. Ожидание мьютекса
    DWORD wait = WaitForSingleObject(OpenMutexPrinter, INFINITE);
    // 4. При достпуности
    if (wait == WAIT_OBJECT_0) {
        // 4.1. захватывает мьютекса
        // 4.2. Задание отправлено
        std::cout << "Задание отправлено на печать" << std::endl;
        // 4.3. освобаждает мьютекса
        ReleaseMutex(OpenMutexPrinter);
        std::cout << "Печать завершена" << std::endl;
    }
    // 5. Ожидает захват мьютекса
    WaitForSingleObject(OpenMutexPrinter, INFINITE);
    // 6. Освобождает мьютекс и после
    ReleaseMutex(OpenMutexPrinter);
    // 6.1. Сообщает о завершении печати
    std::cout << "Печать завершена" << std::endl;

    CloseHandle(OpenMutexPrinter);
    return 0;
}
