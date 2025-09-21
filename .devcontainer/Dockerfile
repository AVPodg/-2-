# Используем официальный образ Ubuntu с последней LTS версией
FROM ubuntu:22.04

# Устанавливаем переменные окружения для предотвращения интерактивных запросов
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Europe/Moscow

# Обновляем пакеты и устанавливаем необходимые инструменты
RUN apt-get update && apt-get install -y \
    # Основные инструменты разработки
    build-essential \
    cmake \
    make \
    git \
    curl \
    wget \
    vim \
    nano \
    # C++ компиляторы и инструменты
    gcc \
    g++ \
    gdb \
    valgrind \
    # Дополнительные утилиты
    tree \
    htop \
    unzip \
    # Инструменты для отладки
    strace \
    ltrace \
    # Очистка кэша
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Создаем пользователя vscode
RUN groupadd --gid 1000 vscode \
    && useradd --uid 1000 --gid vscode --shell /bin/bash --create-home vscode \
    && echo "vscode ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

# Переключаемся на пользователя vscode
USER vscode

# Устанавливаем рабочую директорию
WORKDIR /workspace

# Настраиваем bash для пользователя vscode
RUN echo 'export PS1="\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ "' >> ~/.bashrc \
    && echo 'alias ll="ls -la"' >> ~/.bashrc \
    && echo 'alias la="ls -A"' >> ~/.bashrc \
    && echo 'alias l="ls -CF"' >> ~/.bashrc

# Устанавливаем переменные окружения для компилятора
ENV CC=gcc
ENV CXX=g++

# Устанавливаем права на выполнение для скриптов
RUN sudo chmod +x /workspace

# Команда по умолчанию
CMD ["/bin/bash"]
