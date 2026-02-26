#include <iostream>
#include <Windows.h>
#include <conio.h>

int main()
{
    setlocale(LC_ALL, "ru");
    std::cout << "Клиент" << std::endl;
    HANDLE OpenMutexPrinter = OpenMutex(NULL, FALSE, L"PrinterMutex");
    if (OpenMutexPrinter == NULL) {
        std::cout << "Принтер не найден" << std::endl;
    }
    else {
        WaitForSingleObject(OpenMutexPrinter, INFINITE);
        std::cout << "Задание отправлено на печать" << std::endl;
        ReleaseMutex(OpenMutexPrinter);
        std::cout << "Печать завершена" << std::endl;
    }
    _getch();

}
