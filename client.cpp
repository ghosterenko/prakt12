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
 
    HANDLE OpenMutexPrinter = OpenMutex(MUTANT_ALL_ACCESS, FALSE, L"PrinterMutex");
    if (OpenMutexPrinter == NULL) {
        std::cout << "Принтер не найден" << std::endl;
        return 0;
    }


    while (true)
    {
        std::cout << "Ожидание" << std::endl;
        DWORD wait = WaitForSingleObject(OpenMutexPrinter, INFINITE);
        std::cout << "Подключен - нажмите на любую клавишу чтобы отправить задание" << std::endl;
        
        if (std::cin.get()) {
            if (wait == WAIT_OBJECT_0) {

                std::cout << "Задание отправлено на печать" << std::endl;
                ReleaseMutex(OpenMutexPrinter);

                WaitForSingleObject(OpenMutexPrinter, INFINITE);
                ReleaseMutex(OpenMutexPrinter);
                std::cout << "Печать завершена" << std::endl;
            }
        }
    }
    CloseHandle(OpenMutexPrinter);
    return 0;
}
