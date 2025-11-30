#!/bin/bash

# Скрипт для поиска Boost на Mac с Homebrew

# Проверяем стандартные пути Homebrew
if [ -d "/usr/local/Cellar/boost" ]; then
    # Находим последнюю версию Boost
    LATEST_BOOST=$(ls /usr/local/Cellar/boost | sort -V | tail -n1)
    if [ -n "$LATEST_BOOST" ]; then
        echo "/usr/local/Cellar/boost/$LATEST_BOOST/include"
        exit 0
    fi
fi

# Проверяем путь для Intel Mac
if [ -d "/usr/local/opt/boost/include" ]; then
    echo "/usr/local/opt/boost/include"
    exit 0
fi

# Проверяем путь для Apple Silicon Mac
if [ -d "/opt/homebrew/opt/boost/include" ]; then
    echo "/opt/homebrew/opt/boost/include"
    exit 0
fi

exit 1