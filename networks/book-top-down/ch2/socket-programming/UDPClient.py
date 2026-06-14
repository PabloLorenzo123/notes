from socket import AF_INET, SOCK_DGRAM, socket


serverName = '127.0.0.1' # hostname or ip, if a hostname is provided a DNS lookup is involved.
serverPort = 12000

clientSocket = socket(
    AF_INET, # IPV4
    SOCK_DGRAM # SOCKET DATAGRAM, IN OTHER WORDS A UDP.
)

# This message should end with a carriage return \r.
message = input('Input lowercase sentence:')

clientSocket.sendto(message.encode(), (serverName, serverPort))
modifiedMessage, serverAddress = clientSocket.recvfrom(2048)
print(modifiedMessage.decode())

clientSocket.close()
