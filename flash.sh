#!/bin/bash

# Проверка, что передано имя проекта
if [ -z "$1" ]; then
    echo "Ошибка: Укажи имя проекта."
    echo "Использование: ./flash.sh <ИмяПроекта>"
    echo "Пример: ./flash.sh Blink"
    exit 1
fi

PROJECT_NAME=$1
PROJECT_DIR="./$PROJECT_NAME"

# Проверка, существует ли папка проекта
if [ ! -d "$PROJECT_DIR" ]; then
    echo "Ошибка: Папка '$PROJECT_DIR' не найдена."
    exit 1
fi

# Автоматический поиск порта (первый найденный ttyUSB или ttyACM)
PORT=$(ls /dev/ttyUSB* /dev/ttyACM* 2>/dev/null | head -n 1)

if [ -z "$PORT" ]; then
    echo "Ошибка: Не найден подключенный порт (ttyUSB или ttyACM)."
    echo "Проверь, подключена ли плата."
    exit 1
fi

echo "--- Прошивка проекта: $PROJECT_NAME ---"
echo "--- Используемый порт: $PORT ---"

# Сама команда прошивки
arduino-cli compile --fqbn arduino:avr:uno --port "$PORT" --upload "$PROJECT_DIR"

# Проверка результата
if [ $? -eq 0 ]; then
    echo "--- Успешно! Скетч залит. ---"
else
    echo "--- Ошибка при компиляции или прошивке. ---"
fi
