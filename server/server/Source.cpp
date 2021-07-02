#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <string.h>
#include <time.h>

#pragma warning(disable: 4996)
//проерка числа на простоту
bool isPrime(int n) {
    for (int i = 2; i < n; i++) {
        if (n % i == 0) return false;

    }
    return true;
}

int main(int argc, char* argv[]) {
    int count = 0; // количесвто обработок
    int choose; // выбор в меню
    double srednee = 0; // среднее время
    clock_t start, stop;
    double time; //         время вычисления
    double all_time = 0; // и общее
    int num;  // число для обработки
    char a[256] = ""; //    переменная для перевода числа в char
    char mas[1000] = ""; // массив с результатом
    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData) != 0) {
        printf("Error");
        exit(1);
    }

    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1111);
    addr.sin_family = AF_INET;

    SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
    bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    listen(sListen, SOMAXCONN);

    SOCKET newConnection;
    newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

    if (newConnection == 0) {
        printf("Error #2\n");
    }
    else {
        printf("Client Connected!\n");
        while (true) {
            // принимаем выбор для отправки нужных запросов
            recv(newConnection, (char*)&choose, sizeof(choose), NULL);

            if (choose == 1) {

                recv(newConnection, (char*)&num, sizeof(num), NULL);
                start = clock();
                // вычисление простых чисел
                for (int i = 0; i <= num; i++) {
                    if (isPrime(i)) {
                        sprintf(a, "%d", i);
                        strcat(mas, a);
                        strcat(mas, " ");
                    }
                }
                stop = clock();
                count++;
                time = (double)(static_cast<__int64>(stop) - static_cast<__int64>(start)) / CLOCKS_PER_SEC;
                all_time += time;
                send(newConnection, mas, sizeof(mas), NULL);
                send(newConnection, (char*)&time, sizeof(time), NULL);

            }
            if (choose == 2) {
                srednee = all_time / count;
                send(newConnection, (char*)&count, sizeof(count), NULL);
                send(newConnection, (char*)&srednee, sizeof(srednee), NULL);
            }
        }
    }

    system("pause");
    return 0;
}
