FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y \
    build-essential \
    cmake \
    libgtk-3-dev \
    wget \
    bzip2 \
    && rm -rf /var/lib/apt/lists/*

# Baixa e instala wxWidgets a partir do código fonte
RUN wget https://github.com/wxWidgets/wxWidgets/releases/download/v3.2.6/wxWidgets-3.2.6.tar.bz2 && \
    tar -xjf wxWidgets-3.2.6.tar.bz2 && \
    cd wxWidgets-3.2.6 && \
    mkdir build-gtk && cd build-gtk && \
    ../configure --disable-shared --enable-unicode && \
    make && make install && \
    cd ../.. && rm -rf wxWidgets-3.2.1 wxWidgets-3.2.1.tar.bz2

WORKDIR /app

COPY /map/. .

# RUN g++ main.cpp graph.cpp -o main $(wx-config --cxxflags --libs)

# CMD ["./main"]

CMD g++ main.cpp graph.cpp -o main $(wx-config --cxxflags --libs) && ./main
