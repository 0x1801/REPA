# REPA
Функция на языке Си для конвертации строк из кодировки UTF-8 в Windows-1251 (CP1251)

Файл с функцией: https://github.com/0x1801/REPA/blob/main/utf8_2_win1251.c

* Поставляется в виде исходного кода.
* Написана на языке С.
* Может быть использована в программах на языке C++.
* Может применяться в программах для микроконтроллеров, т.к. не использует ни SIMD-инструкций, ни даже x64. 
* Использует очень мало памяти.
* Поддерживает символы utf8 до 4х байт (стандарт RFC 3629)
* Входной массив может совпадать с выходным: данные будут перезаписаны. 


Применение:

Вам ничего не понадобится, кроме текста функции и 3х макросов перед ней. Ни инклюдов и библиотек, ни массивов, никакого другого кода. Просто скопируйте ее в свой проект. 

ВНИМАНИЕ: Функция требует наличия 2х лишних выделенных байтов памяти за символом конца строки во входном массиве с символами utf8. В этих байтах может лежать любой мусор. Обычно, если в вашем проекте код написан оптимально, то вы не будете каждый раз выделять память под строку. Поэтому выделить 2 лишних байта - это не проблема. Но если в вашем проекте сложно это внедрить, то можете немного самостоятельно модифицировать код. 

Если есть желание проверить работу функции, можно написать тест самостоятельно или воспользоваться заготовкой из main.c: https://github.com/0x1801/REPA/blob/main/main.c

Больше main.c ни для чего не нужен. 

Связаться с автором:

Илья

chronosphere@mail.ru.
