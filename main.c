#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>

int main() {
    int i;
    char y, z;
    short int x, v, v_c, v_as;
    setlocale(LC_ALL, "rus");

    printf("Введите номер теста\n");
    scanf("%d", &i);
    switch (i) {
    case 1:
        x = 0x2; y = -0x3; z = 0x6; v = 0x1;
        break;
    case 2:
        x = 0x7be; y = 0x7e; z = -0x7e; v = 0x7cd;
        break;
    }

    v_c = (3 - x * (y + 2)) / (z - 1);

    __asm {
        ; числитель
        mov al, y; al = y
        cbw; Расширяем al до ax(преобразуем байт в слово со знаком)
        add ax, 2; ax = y + 2 
        imul x; Умножаем ax(y + 2) на x(16 - битное число со знаком)
        ; результат: dx:ax = x * (y + 2)
        ; dx - старшие 16 бит, ax - младшие 16 бит двойного слова

        mov bx, 3; bx = 3 (младшая часть числа 3)
        mov cx, 0; cx = 0 (старшая часть числа 3)
        ;  cx : bx представляет число 3 (cx старшие биты, bx младшие биты)
        sub bx, ax;вчитаем младшую часть : bx = bx - ax
        sbb cx, dx; вычитаем старшую часть с учетом заема : cx = cx - dx
        

        ; знаменатель
        mov al, z; al = z
        cbw; Расширяем al до ax(преобразуем байт z в слово со знаком) ax = z
        dec ax; ax = ax - 1 

        ; деление
        xchg ax, bx; меняем местами ax и bx,чтобы можно было делить
        mov dx, cx; dx = cx старшая часть числителя, теперь dx : ax = полное значение числителя(32 бита) 
        idiv bx; делим dx:ax на bx
        mov v_as, ax; Сохраняем полученное частное в переменную v_as
    }

    printf("Результат на ассемблере: \n int %d, hex %hx\n", v_as, v_as);
    printf("Результат на С: \n int %d, hex %hx\n", v_c, v_c);
    printf("Заданные значения V: \n int %d, hex %hx\n", v, v);
    return 0;
}