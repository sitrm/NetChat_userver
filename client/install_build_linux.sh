#!/bin/bash

# Скрипт для сборки Qt проекта clientGui для начинающих пользователей

# Проверяем, установлен ли CMake
if ! command -v cmake &> /dev/null; then
    echo "CMake не установлен. Устанавливаем..."
    
    # Определяем дистрибутив Linux
    if [ -f /etc/debian_version ]; then
        # Debian/Ubuntu
        sudo apt-get update
        sudo apt-get install -y cmake
    elif [ -f /etc/redhat-release ]; then
        # CentOS/RHEL
        sudo yum install -y cmake
    elif [ -f /etc/arch-release ]; then
        # Arch Linux
        sudo pacman -Sy --noconfirm cmake
    else
        echo "Не удалось определить дистрибутив Linux. Установите CMake вручную."
        exit 1
    fi
fi

# Проверяем, установлен ли Qt
if ! command -v qmake &> /dev/null; then
    echo "Qt не установлен. Устанавливаем Qt и необходимые компоненты..."
    
    # Определяем дистрибутив Linux
    if [ -f /etc/debian_version ]; then
        # Debian/Ubuntu
        sudo apt-get install -y qtbase5-dev qt5-qmake qttools5-dev-tools libqt5websockets5-dev
    elif [ -f /etc/redhat-release ]; then
        # CentOS/RHEL
        sudo yum install -y qt5-qtbase-devel qt5-qmake qt5-qtwebsockets-devel
    elif [ -f /etc/arch-release ]; then
        # Arch Linux
        sudo pacman -Sy --noconfirm qt5-base qt5-tools qt5-websockets
    else
        echo "Не удалось определить дистрибутив Linux. Установите Qt вручную."
        exit 1
    fi
fi

# Создаем директорию для сборки
mkdir -p build
cd build || exit

# Запускаем сборку проекта
cmake ..
make

echo ""
echo "Сборка завершена!"
echo "Исполняемый файл находится в папке build/"