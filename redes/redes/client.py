import socket
import threading
from constantes import ADDR, FORMAT, HEADER, DISCONECT, PORT, SERVER


#objeto socket
#AF_INET especifica o tipo de endereço que o objeto ira receber
#SOCK_STREAM indica que o tipo de conexao do socket é sequencial
client = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
client.connect(ADDR)

print(client.recv(2048).decode(FORMAT))
def send(client,msg):
    #realiza o encode para binario da mensagem
    mensagem = msg.encode(FORMAT)
    #obtem o inteiro referente ao tamanho da mensagem em binario 
    msg_len = len(mensagem)
    #transforma o inteiro referente ao tamanho em string, e realiza o encode sobre ele
    send_len = str(msg_len).encode(FORMAT)
    #se a mensagem for menor que 64 bits, adiciona o restante dos bits em espaços em branco
    send_len += b' ' * (HEADER - len(send_len))
    #enviando o tamanho da mensagem
    client.send(send_len)
    #enviando a mensagem
    client.send(mensagem)

    #print(client.recv(2048).decode(FORMAT))


client.close()