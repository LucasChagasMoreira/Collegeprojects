import socket
import threading
from constantes import ADDR, FORMAT, HEADER, DISCONECT, PORT, SERVER

#objeto socket
#AF_INET especifica o tipo de endereço que o objeto ira receber
#SOCK_STREAM indica que o tipo de conexao do socket é sequencial
server = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

#Conecta o objeto socket "server" ao endereço
server.bind(ADDR)

conexoes = {}

#função que lida com mensagens recebidas por um cliente conectado
def handle_client(connect, endereco):
    print(f'[NEW CONNECTION] {endereco} conectou')
    global conexoes
    
    conexoes[endereco] = connect
    
    connect.send("digite seu nome".encode(FORMAT))
    connect.recv(1024).decode(FORMAT)

    print("thread encerrada")

    #finaliza a conecçao
    #connect.close()

#funçao responsavel por iniciar o servidor
def start():
    #faz com que o servidor fique disponivel a conecções
    conneccoes_ativas = []
    server.listen()
    print(f'[LISTENING] servidor escutando em {SERVER}')
    while len(conneccoes_ativas) < 3:
        #aceita conecçao com algum cliente
        connect,endereco = server.accept()
        #salvando o endereço em um vetor
        conneccoes_ativas.append(endereco)
        #inicia um thread para cuidar do cliente atravez da funçao handle_cliente
        thread = threading.Thread(target=handle_client,args=(connect,endereco))
        thread.start()
        print(f'[conecções ativas] {threading.active_count()-1}')
    
    #enviando mensagem para cada cliente conectado.
    for i in range(len(conneccoes_ativas)):
        enviar_mensagem_para_cliente(conneccoes_ativas[i], "\o/")


def enviar_mensagem_para_cliente(endereco, mensagem):
    global conexoes
    if endereco in conexoes:
        cliente_socket = conexoes[endereco]
        try:
            cliente_socket.sendall(mensagem.encode(FORMAT))
        except:
            # Lidar com a exceção se a conexão estiver fechada ou ocorrer um erro de envio
            print(f"Erro ao enviar mensagem para {endereco}")
    else:
        print(f"Cliente {endereco} não encontrado.")



print("[INICIANDO O SERVIDOR]")
start()