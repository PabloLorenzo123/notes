from socket import socket, AF_INET, SOCK_STREAM

serverSocket = socket(
    AF_INET, # IPV4
    SOCK_STREAM # TCP
)

serverSocket.bind(('', 12000))

serverSocket.listen(1)

while True:
    connection, _ = serverSocket.accept()
    
    request, _ = connection.recvfrom(2048)
    response = request.decode().upper()
    
    connection.send(response.encode())
