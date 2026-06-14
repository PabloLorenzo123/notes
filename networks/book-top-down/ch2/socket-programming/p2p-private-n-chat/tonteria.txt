from socket import socket, AF_INET, SOCK_STREAM, SOCK_DGRAM, SOL_SOCKET, SO_BROADCAST
import threading, time

def get_local_ip():
    s = socket(AF_INET, SOCK_DGRAM)
    try:
        s.connect(("8.8.8.8", 80))
        ip, _ = s.getsockname()
    except Exception:
        ip = "127.0.0.1"
    finally:
        s.close()
    return ip

APP_PORT = 12000
LOCAL_IP = get_local_ip()

BROADCAST_IP = '255.255.255.255'

connection_established = False
connection_attempt_in_progress = False

broadcast_socket = socket(
    AF_INET,    # IPV 4
    SOCK_DGRAM  # UDP
)
broadcast_socket.setsockopt(SOL_SOCKET, SO_BROADCAST, 1)
broadcast_socket.bind(('', APP_PORT))

listen_connection_socket = socket(
    AF_INET,
    SOCK_STREAM
)
listen_connection_socket.bind(('', APP_PORT))
listen_connection_socket.listen(1)

connect_connection_socket = socket(
    AF_INET,
    SOCK_STREAM
)

chat_connection = None
chatting_with = None

users_in_private_network = {}

def main():
    username = input('username: ')
    
    t1 = threading.Thread(target=broadcast_client, args=(username,), daemon=True)
    t2 = threading.Thread(target=find_users_in_local_network, daemon=True)
    t3 = threading.Thread(target=prompt_to_connect, daemon=True)
    t4 = threading.Thread(target=listen_for_connection, daemon=True)
    t5 = threading.Thread(target=chat_process, daemon=True)
    
    t1.start()
    t2.start()
    t3.start()
    t4.start()
    t5.start()
    
    # Blocks the main thread until these threads exit.
    t1.join()
    t2.join()
    t3.join()
    t4.join()
    t5.join()

    
def broadcast_client(username: str):
    while True:
        if connection_established or connection_attempt_in_progress:
            continue
        broadcast_msg = f"Hi i'm {username}, reach me at {LOCAL_IP} {APP_PORT}"
        broadcast_socket.sendto(
            broadcast_msg.encode(),
            (BROADCAST_IP, APP_PORT)
        )
        time.sleep(5)

        
def find_users_in_local_network():
    print("listening for users in this network....")
    
    while True:
        if not connection_established and not connection_attempt_in_progress:
            data, _ = broadcast_socket.recvfrom(2048)
            broadcast_msg = data.decode()
            
            if not connection_established and not connection_attempt_in_progress:
                print(broadcast_msg)

            username = broadcast_msg.split(" ")[2].strip(',')
            ip = broadcast_msg.split(" ")[-2]
            port = int(broadcast_msg.split(" ")[-1])

            if username not in users_in_private_network:
                users_in_private_network[username] = [ip, port]


def prompt_to_connect():
    global connection_established
    global connection_attempt_in_progress
    global chat_connection
    global chatting_with
    
    time.sleep(5)
    
    while True:
        if not connection_established and not connection_attempt_in_progress and len(users_in_private_network.keys()) > 1:
            connection_attempt_in_progress = True
            username = input("Who do you wanna chat with? (n) if you don't wanna chat anyone: ")
            
            if username.upper() == 'N':
                connection_attempt_in_progress = False
                time.sleep(5)
                continue
            
            if username not in users_in_private_network:
                print("This user is not connected in the network.")
                connection_attempt_in_progress = False
                continue
            
            address, port = users_in_private_network[username]
            connect_connection_socket.connect((address, port))
            
            response, _ = connect_connection_socket.recvfrom(2048)
            if response.decode() == "CONNECTION ACCEPTED":
                chat_connection = connect_connection_socket
                chatting_with = username
                connection_established = True
                connection_attempt_in_progress = False
        

def listen_for_connection():
    global connection_established
    global connection_attempt_in_progress
    global chat_connection
    global chatting_with
    
    while True:
        if connection_established or connection_attempt_in_progress:
            continue
        
        chat_connection, address = listen_connection_socket.accept()
        connection_attempt_in_progress = True
        
        asker = find_user_with_address(address[0])
                
        if input(f"{asker} wants to start a chat with you. Do you accept? (y): ").upper() == 'Y':
            chat_connection.send("CONNECTION ACCEPTED".encode())
            connection_established = True
            connection_attempt_in_progress = False
            chatting_with = asker
        else:
            chat_connection.send("CONNECTION REJECTED".encode())
            chat_connection.close()
            chat_connection = None
            connection_established = False
            connection_attempt_in_progress = False

      
def find_user_with_address(address: str):
    for user in users_in_private_network:
        if users_in_private_network[user][0] == address:
            return user
    
    return "unknown"


        
def chat_process():
    while True:
        if not connection_established or connection_attempt_in_progress:
            continue
        
        print()
        print("\nYou can now start chatting")
        t1 = threading.Thread(target=receive_messages)
        t2 = threading.Thread(target=send_messages)
        
        t1.start()
        t2.start()
        
        t1.join()
        t2.join()


def receive_messages():
    global connection_established
    while True:
        if not connection_established:
            continue
        res, _ = chat_connection.recvfrom(2048)
        print(f"{chatting_with}: {res.decode()}")


def send_messages():
    global connection_established
    
    while True:
        if not connection_established:
            continue
        msg = input()
        chat_connection.send(msg.encode())
    
if __name__ == '__main__':
    main()
