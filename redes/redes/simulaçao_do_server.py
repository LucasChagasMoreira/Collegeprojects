import socket
import time
import threading
from constantes import *

#objeto socket
#AF_INET especifica o tipo de endereço que o objeto ira receber
#SOCK_STREAM indica que o tipo de conexao do socket é sequencial
server = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

#Conecta o objeto socket "server" ao endereço
server.bind(ADDR)

conexoes = {}
nome_jogadores = []

def handle_client(connect,endereco,enderecos):

    enviar_mensagem(connect,"digite seu nome jogador")
    nome = receber_mensagem(connect)
    receber_mensagem(connect)

    enderecos.append((endereco,nome))
    




def conectar_jogadores():
    global conexoes
    start_time = time.time()
    enderecos = []
    lista_threads = []
    qtd_threads = 0
    while qtd_threads < 2 and time.time() - start_time < 30:
        threads_ativas = threading.active_count()-1
        #aceita conecçao com algum cliente
        connect,endereco = server.accept()
        conexoes[endereco] = connect

        #inicia um thread para cuidar do cliente atravez da funçao handle_cliente
        thread = threading.Thread(target=handle_client,args=(connect,endereco,enderecos))
        thread.start()
        lista_threads.append(thread)
        qtd_threads += 1
        print(f'[conecções ativas] {qtd_threads}')
        

    if qtd_threads >= 2:
        print("Número máximo de threads atingido.")
    else:
        print("Tempo limite atingido, encerrando a função.")

    # Esperar que todas as threads terminem
    for thread in lista_threads:
            thread.join()
    
    print(enderecos)
    return enderecos    

def envia_para_todos(mensagem,grupo_de_jogadores):
    global conexoes

    for endereco in grupo_de_jogadores:
        if endereco[0] in conexoes:
            cliente_socket = conexoes[endereco[0]]
            try:
                enviar_mensagem(cliente_socket,MENSAGEM_QUALQUER)
                enviar_mensagem(cliente_socket,mensagem)
            except:
                # Lidar com a exceção se a conexão estiver fechada ou ocorrer um erro de envio
                print(f"Erro ao enviar mensagem para {endereco}")
        else:
            print(f"Cliente {endereco} não encontrado.")
        

def funcao_de_encerramento(endereco):
    global conexoes

    if endereco in conexoes:
        cliente_socket = conexoes[endereco]
        try:
            enviar_mensagem(cliente_socket,"end")
        except:
            # Lidar com a exceção se a conexão estiver fechada ou ocorrer um erro de envio
            print(f"Erro ao enviar mensagem para {endereco}")
    else:
        print(f"Cliente {endereco} não encontrado.")
    
def requisita_jogada(endereco,nome):
    
    global conexoes

    if endereco in conexoes:
        cliente_socket = conexoes[endereco]
        try:
            enviar_mensagem(cliente_socket,JOGADA)
            enviar_mensagem(cliente_socket,f'jogador: {nome} diga sua jogada.')
            return receber_mensagem(cliente_socket)
        
        except:
            # Lidar com a exceção se a conexão estiver fechada ou ocorrer um erro de envio
            print(f"Erro ao enviar mensagem para {endereco}")
    else:
        print(f"Cliente {endereco} não encontrado.")
    
def rodada_jogadas(grupo_de_jogadores):
    relatorio = ""
    for i in grupo_de_jogadores:
        print("esperando jogada")
        escolha = requisita_jogada(i[0],i[1])
        relatorio =f'jogador: {i[1]}, fez {escolha}\n'
        envia_para_todos(relatorio,grupo_de_jogadores)
    for i in grupo_de_jogadores:
        funcao_de_encerramento(i[0])

    
def start(grupo_de_jogadores):
    relatorio = rodada_jogadas(grupo_de_jogadores)

def lobby():
    server.listen()
    print(f'[LISTENING] servidor escutando em {SERVER}')
    while True:
        print(f'preparando sala {threading.active_count()-1}')
        
        grupo_de_jogadores = conectar_jogadores()
        print(f'print do lobby {grupo_de_jogadores}')

        thread = threading.Thread(target=rodada_jogadas,args=(grupo_de_jogadores,))
        thread.start()
        print(f'[salas ativas] {threading.active_count()-1}')

    for thread in threading.enumerate():
        if thread != threading.current_thread():
            thread.join()

lobby()