﻿// S004.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

int main()
{
    char s1[256];
    char s2[256];
    int strt;
    int lng;
    char f[] = "%s";
    char fd[] = "%d";
    _asm {
        //читаем первую строку
        lea ebx, s1
        push ebx
        lea ecx, f
        push ecx
        call scanf
        add esp, 8
        //читаем начало и длину 
        lea ebx, strt
        push ebx
        lea edx, fd
        push edx
        call scanf
        add esp, 8
        lea ebx, lng
        push ebx
        lea edx, fd
        push edx
        call scanf
        add esp, 8
        //подготовка к подсчету длины строки
        lea ebx, s1
        dec ebx
        mov ecx, -1
        //считаем длину строки
        b1:
        inc ecx
            inc ebx
            mov al, [ebx]
            cmp al, 0
            jnz b1
            //подготавливаемся к началу копирования
            lea edx, s2
            dec edx
            //проверка стартового индекса копирования
            mov eax, strt
            cmp eax, ecx
            jge end
            cmp eax, 0
            jg skip
            mov eax, 0 //если стартовый индекс меньше 0, помещаем 0

            skip:
        //подготовка к циклу
        lea ebx, s1
            sub ebx, 2
            mov ecx, lng
            inc eax
            //первая половина копирования: перемещение к стартовому индексу
            copy1 :
        inc ebx
            dec eax
            cmp eax, 0
            jnz copy1
            //вторая половина копирования: копируем нужное
            copy2 :
        inc ebx
            inc edx
            dec ecx
            mov al, [ebx]
            mov[edx], al
            cmp al, 0
            jz end
            cmp ecx, 0
            jnz copy2
            jmp end

            end :
        inc edx
            mov[edx], 0
            lea ebx, s2
            push ebx
            lea ecx, f
            push ecx
            call printf
            add esp, 8
    }
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
