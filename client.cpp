#include <iostream>
#include <Windows.h>
#include <conio.h>

int main()
{
    setlocale(LC_ALL, "ru");
    HANDLE OpenMutexPrinter = OpenMutexA(MUTANT_ALL_ACCESS, FALSE, "PrinterMutex");
    if (OpenMutexPrinter == NULL) {
        std::cout << "Принтер не найден" << std::endl;
        return 1;
    }
    WaitForSingleObject(OpenMutexPrinter, INFINITE);
    std::cout << "Клиент подключен" << std::endl;
    std::cin.get();
    std::cout << "Ожидание подключения к принтеру" << std::endl;
    ReleaseMutex(OpenMutexPrinter);
    std::cout << "Задание отправлено на печать" << std::endl;
    DWORD wait = WaitForSingleObject(OpenMutexPrinter, INFINITE);
    if (wait == WAIT_OBJECT_0) {
        ReleaseMutex(OpenMutexPrinter);
        std::cout << "Печать завершена" << std::endl;
    }
    WaitForSingleObject(OpenMutexPrinter, INFINITE);
    ReleaseMutex(OpenMutexPrinter);
    CloseHandle(OpenMutexPrinter);
    return 0;
}

