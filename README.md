# port-scanner

## Запуск

### Шаг 1.

Создадим пустую директорию для временных файлов и перейдём туда

```bash
    mkdir tmp && cd ./tmp
```

### Шаг 2.

Запустим `cmake`. Передадим в `cmake` путь к директории с исходниками

```bash
    cmake ~/port-scanner
```

### Шаг 3.

Соберем проект при помощи `make`

```bash
    make
```

### Шаг 4.

Запустим программу

```bash
    ./main <IP> <MIN_POST> <MAX_POST>
```

Пример

```bash
    ./main scanme.nmap.org 1 1000
```