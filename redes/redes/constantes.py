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