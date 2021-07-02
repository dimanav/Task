#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <locale.h>

#pragma warning(disable: 4996)

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Rus");
    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData) != 0) {
        printf("Error\n");
        exit(1);
    }

    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1111);
    addr.sin_family = AF_INET;

    SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
    if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
        printf("Error: failed connect to server.\n");
        return 1;
    }
    printf("Connected!\n");
    system("pause");
    system("cls");

    int num; // введённое число
    char mas[1000] = ""; // массив с результатом
    int choose; // выбор в меню
    int count; // количество обработок
    double srednee; // среднее время вычисления
    double time; // время вычисления
    while (true) {
        printf("1. Вычислить простые числа.\n2. Статистика.\n3. Выход. \n");
        printf("Выберите пункт: \n");
        scanf("%d", &choose);
        // отправляем на сервер выбранный вариант для отправки нужных запросов
        send(Connection, (char*)&choose, sizeof(choose), NULL);
        // вычисление
        if (choose == 1) {
            printf("Введите число: ");
            scanf("%d", &num);
            send(Connection, (char*)&num, sizeof(num), NULL);
            recv(Connection, mas, sizeof(mas), NULL);
            recv(Connection, (char*)&time, sizeof(time), NULL);
            printf(mas);
            printf("\nЗатраченное время: %.8f\n", time);

            system("pause");
            system("cls");
        }
        // статистика
        if (choose == 2) {
            recv(Connection, (char*)&count, sizeof(count), NULL);
            printf("Количество запростов: %d\n", count);
            recv(Connection, (char*)&srednee, sizeof(srednee), NULL);
            printf("Среднее время вычислений: %.8f\n", srednee);
            system("pause");
            system("cls");
        }
        // выход
        if (choose == 3) {
            break;
        }
    }
    return 0;
}

