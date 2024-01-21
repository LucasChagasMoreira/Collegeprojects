import socket
import threading
from constantes import ADDR, FORMAT, HEADER, DISCONECT, PORT, SERVER

client_socket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
client_socket.connect(ADDR)

while True:
    message = input("mensagem: ")
    client_socket.sendall(message.encode('utf-8'))
    if message.lower == 'exit':
        break

client_socket.close()