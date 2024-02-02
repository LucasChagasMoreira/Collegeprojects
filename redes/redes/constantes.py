import socket
#tamanho da primeira mensagem que todo cliente envia para o servidor
HEADER = 64
#porta da rede
PORT = 5050

#funçao para adquirir o endereço ip da maquina local
SERVER = socket.gethostbyname(socket.gethostname())

#Tupla contendo o endereço ip e a porta
ADDR = (SERVER,PORT)
# formato de decodificaçao
FORMAT = 'utf-8'
#mensagem para desconectar o cliente
DISCONECT = "/DISCONECT"

JOGADA = "JOGADA"

MENSAGEM_QUALQUER = "MENSAGEM_QUALQUER"


def enviar_mensagem(socket,mensagem):
    socket.send(mensagem.encode(FORMAT))

    confirmaçao_de_chegada = socket.recv(1024).decode(FORMAT)
    if(confirmaçao_de_chegada == "confirmado"):
        return
    else:
        print("algo de errado esta acontecendo")
        print(f"esperava \"confimado\" entretanto foi recebido {confirmaçao_de_chegada}")
        return

def receber_mensagem(socket):
    dado = socket.recv(1024).decode(FORMAT)
    socket.send("confirmado".encode(FORMAT))
    return dado
    
    