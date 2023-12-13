import socket
import threading
from constantes import ADDR, FORMAT, HEADER, DISCONECT, PORT, SERVER

#objeto socket
#AF_INET especifica o tipo de endereço que o objeto ira receber
#SOCK_STREAM indica que o tipo de conexao do socket é sequencial
server = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

#Conecta o objeto socket "server" ao endereço
server.bind(ADDR)

#função que lida com mensagens recebidas por um cliente conectado
def handle_client(connect, endereco):
    print(f'[NEW CONNECTION] {endereco} conectou')
    
    connected = True
    while connected:
        #recebe a primeira mensagem que ira definir o tamanho da mensagem_Final
        mensagem = connect.recv(HEADER).decode(FORMAT)
        #verifica se é uma mensagem valida
        if mensagem:
            #converte este tamanho para um numero inteiro
            mensagem = int(mensagem)
            #recebe a mensagem propriamente dita
            mensagem_final = connect.recv(mensagem).decode(FORMAT)
            #verificaçao para saber se o cliente quer se desconectar
            if mensagem_final == DISCONECT:
                connected = False

            print(f'[{endereco}] {mensagem_final}')
            connect.send("mensagem recebida".encode(FORMAT))

    #finaliza a conecçao
    connect.close()

#funçao responsavel por iniciar o servidor
def start():
    #faz com que o servidor fique disponivel a conecções
    server.listen()
    print(f'[LISTENING] servidor escutando em {SERVER}')
    while True:
        #aceita conecçao com algum cliente
        connect,endereco = server.accept()
        #inicia um thread para cuidar do cliente atravez da funçao handle_cliente
        thread = threading.Thread(target=handle_client,args=(connect,endereco))
        thread.start()
        print(f'[conecções ativas] {threading.active_count()-1}')


print("[INICIANDO O SERVIDOR]")
start()