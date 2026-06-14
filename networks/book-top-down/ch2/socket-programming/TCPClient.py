from socket import socket, AF_INET, SOCK_STREAM

clientSocket = socket(
    AF_INET, # IPV 4
    SOCK_STREAM # STREAM - TCP TRANSPORT LAYER
)

ServerAdd, ServerPort = "127.0.0.1", 12000

clientSocket.connect((ServerAdd, ServerPort))

message = input("message: ")

clientSocket.send(message.encode())

response, _ = clientSocket.recvfrom(2048)

print(response.decode())

clientSocket.close()
