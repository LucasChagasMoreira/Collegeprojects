import socket
import threading
from constantes import ADDR, FORMAT, HEADER, DISCONECT, PORT, SERVER

import select

# Configurações do servidor
HOST = '127.0.0.1'
PORT = 12345

# Criação do socket do servidor
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(ADDR)
server_socket.listen()

print(f"Servidor ouvindo em {SERVER}:{PORT}")

# Lista de sockets para monitorar (incluindo o socket do servidor)
sockets_list = [server_socket]

while True:
    # Espera até que algum socket esteja pronto para leitura
    readable, _, _ = select.select(sockets_list, [], [])

    for s in readable:
        if s is server_socket:
            # Aceita uma nova conexão
            client_socket, client_address = s.accept()
            print(f"Conexão recebida de {client_address}")
            sockets_list.append(client_socket)
        else:
            # Recebe e imprime mensagens do cliente
            data = s.recv(1024).decode('utf-8')
            if not data:
                print(f"Conexão com {s.getpeername()} encerrada")
                s.close()
                sockets_list.remove(s)
            else:
                print(f"Cliente {s.getpeername()}: {data}")
