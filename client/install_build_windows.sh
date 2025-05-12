#!/bin/bash

# Скрипт для сборки Qt проекта clientGui на Windows

echo "Этот скрипт поможет установить зависимости и собрать проект на Windows"
echo "Рекомендуется запускать в Git Bash или WSL"

# Проверяем, установлен ли CMake
if ! command -v cmake &> /dev/null; then
    echo "CMake не установлен. Пожалуйста, установите его вручную:"
    echo "1. Скачайте с https://cmake.org/download/"
    echo "2. Установите, выбрав опцию 'Add to PATH'"
    echo "3. Перезапустите терминал и снова запустите этот скрипт"
    exit 1
fi

# Проверяем, установлен ли Qt
if ! command -v qmake &> /dev/null; then
    echo "Qt не установлен. Пожалуйста, установите его:"
    echo "1. Скачайте онлайн-установщик с https://www.qt.io/download"
    echo "2. Выберите компоненты: Qt > Qt $QT_VERSION_MAJOR > MSVC или MinGW (в зависимости от вашего компилятора)"
    echo "3. Добавьте Qt в PATH во время установки"
    echo "4. Перезапустите терминал и снова запустите этот скрипт"
    exit 1
fi

# Проверяем, установлен ли компилятор
if ! command -v g++ &> /dev/null && ! command -v cl &> /dev/null; then
    echo "Компилятор не найден. Установите один из вариантов:"
    echo "1. MinGW-w64 (рекомендуется для простоты):"
    echo "   - Скачайте с https://winlibs.com/"
    echo "   - Распакуйте и добавьте bin/ в PATH"
    echo "2. Или Visual Studio с компонентом 'Desktop development with C++'"
    exit 1
fi

# Определяем генератор для CMake
if command -v g++ &> /dev/null; then
    GENERATOR="MinGW Makefiles"
    MAKE_CMD="mingw32-make"
elif command -v cl &> /dev/null; then
    GENERATOR="Visual Studio 17 2022"
    MAKE_CMD="cmake --build ."
else
    GENERATOR=""
fi

# Создаем директорию для сборки
mkdir -p build
cd build || exit

# Запускаем сборку проекта
echo "Запускаем сборку с генератором: $GENERATOR"
cmake -G "$GENERATOR" ..
$MAKE_CMD

echo ""
echo "Сборка завершена!"
if [ "$GENERATOR" == "MinGW Makefiles" ]; then
    echo "Исполняемый файл: build/clientGui.exe"
else
    echo "Исполняемый файл находится в build/Debug/ или build/Release/"
fi