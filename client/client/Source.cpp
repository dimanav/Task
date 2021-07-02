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

    int num; // �������� �����
    char mas[1000] = ""; // ������ � �����������
    int choose; // ����� � ����
    int count; // ���������� ���������
    double srednee; // ������� ����� ����������
    double time; // ����� ����������
    while (true) {
        printf("1. ��������� ������� �����.\n2. ����������.\n3. �����. \n");
        printf("�������� �����: \n");
        scanf("%d", &choose);
        // ���������� �� ������ ��������� ������� ��� �������� ������ ��������
        send(Connection, (char*)&choose, sizeof(choose), NULL);
        // ����������
        if (choose == 1) {
            printf("������� �����: ");
            scanf("%d", &num);
            send(Connection, (char*)&num, sizeof(num), NULL);
            recv(Connection, mas, sizeof(mas), NULL);
            recv(Connection, (char*)&time, sizeof(time), NULL);
            printf(mas);
            printf("\n����������� �����: %.8f\n", time);

            system("pause");
            system("cls");
        }
        // ����������
        if (choose == 2) {
            recv(Connection, (char*)&count, sizeof(count), NULL);
            printf("���������� ���������: %d\n", count);
            recv(Connection, (char*)&srednee, sizeof(srednee), NULL);
            printf("������� ����� ����������: %.8f\n", srednee);
            system("pause");
            system("cls");
        }
        // �����
        if (choose == 3) {
            break;
        }
    }
    return 0;
}

