import socket
import threading
from constantes import *


#objeto socket
#AF_INET especifica o tipo de endereço que o objeto ira receber
#SOCK_STREAM indica que o tipo de conexao do socket é sequencial
client = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
client.connect(ADDR)

def cadastro():
    print(receber_mensagem(client))
    nome = input()
    enviar_mensagem(client,nome)

    print("digite qualquer coisa para continuar")
    input()
    enviar_mensagem(client,'confirmado')
    

def envia_jogada():
    while True:

        primeiro_comando = receber_mensagem(client)
        if(primeiro_comando == JOGADA):
            print(receber_mensagem(client))

            escolha = input()
            enviar_mensagem(client,escolha)
        elif primeiro_comando == MENSAGEM_QUALQUER:
            print(receber_mensagem(client))
        elif primeiro_comando == "end":
            return
        else:
            print("algo de errado aconteceu")


cadastro()
envia_jogada()



client.close()