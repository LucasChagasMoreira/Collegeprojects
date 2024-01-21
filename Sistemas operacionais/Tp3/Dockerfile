# Use a imagem base do Ubuntu
FROM ubuntu:latest

# Atualiza os pacotes existentes e instala o GCC
RUN apt-get update && \
    apt-get install -y gcc

# Cria um diretório dentro do contêiner
WORKDIR /myapp

# Copia os arquivos fork.c, threads.c e condiçaodecorrida.c para o diretório no contêiner
COPY tp3.cpp /myapp/

# Define o comando padrão a ser executado quando o contêiner for iniciado
CMD ["/bin/bash"]

