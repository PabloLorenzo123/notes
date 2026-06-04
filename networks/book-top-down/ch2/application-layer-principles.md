# Principles
Application layer is the top most layer in the OSI layer architecture, this layer runs inside processes themselves, as you may know a program and a proccess are not the same thing, in computing terms a process is the active execution of a program in an computer which is handled by the operating system, a computer can have multiple programs running.

For networking to be useful, we need services that rely on networks, if not everything is useless. This most top layer, refers to the protocols that proccesses running on different machines use to exchange data.

## Network Application Architectures.

### Client-Server Architecture.
The most widely used and most common application architecture developers use is the client-server architecture. In this in a connection proccesses have different roles, the client is usually the one that begins the connection and ask for things, while the server is the one who handles request and execute application logic. Examples are the Web and Email.

This architecture doesn't self scale unlike P2P, if there are multiple clients and a few servers, the servers can get overloaded making the application unusable. But these applications are usually more secure, because important application operations are executed on a hosted server.

### P2P - Peer to Peer.
In this architecture, a process is a client and a server at the same time. Example with File Transfer Protocol (FTP).

Its main advantage is that there is no intermediary between clients, and applications built on this architecture auto-scale.

## Proccess Communication (Sockets)
As i said earlier process live in a host computer, and this host can have multiple proccesses running at at time. The operating offer a tool/abstraction to process to allow for Inter Proccess Communication (IPC) to a remote Process, this abstraction is called a 'Socket'.

With a socket the programmer indicates, where it needs to send the information to, and this socket handles the transport layer concerns. See this as the adapter between the process and the transport layer. A process is like a home, and a socket is like a door, whatever comes from outside enter through this door, and whatever needs to be sent from this home goes out of that door.

Note: the socket interface can be used to exchange data between remote processes, and processes running on the same machine.

A socket can be attached to an internet interface (by its ip) and a logical port. e.g a server can have a mail service, and a web app running both reachable through the same IP, but running at different ports.

In POSIX, the socket programming interface is defined.

TODO: C, Sockets demonstration.

## Transport Services Available to Applications.
These are reliable data transfer, througput, and security.

### Reliable Data Transfer
A transport service that fulfills this service, almost guarantees to the application that the each bit of the message will be received by the receiver process. TCP is an example of a service that accomplishes this, through acknowledgements.

### Throughput
The ideal transport service, would allow the application to adjust throughput, as we defined in chapter 1 throughput is the amount of bit per seconds the receiver is receiving. This service is important for streaming services, in where the data encoding must closely match the output, e.g VoIp, if the data encoding rate (converting voice, into a bit stream) is processed at a higher rate than the link throughput, the quality of service will be bad, the receiver will hear the voice breaking (because some packets are being held in a router queue) up, and then speeding up.

Because the internet is decentralized, throughput is constrained by the network state, and no application can control that, because this infrastructure is shared. Programmers work around this by adjusting the bit rate of their programs to match the throughput. Nonetheless Transport protocols such as TCP can 'control throughput' if they realize that there are many packet losses (meaning there's no acknowledgement responses from the receiver) it will lower its throughput - remember, when throughput is higher than the transmision rate queues inevitably form, leading to pcket loss.
Also tcp can speed up its throughput overtime in the connection if it notices that it doesn't result in packet loss.

This happens all the time, when you're watching youtube, and the network gets slower, the video automatically adjust to a lower quality, and when the internet speeds up the resolution goes up too.

### Security
The ideal transport layer would offer security around its message. protecting it from eaves droppers (with encryption), forgering and spoofing (through signing for instance). As of now, no transport layer protocol offer this by default, instead this details are handled in the application layer. Tough this can be also seen as living in the transport layer, because for instance with TLS sockets may already provide this functionality. 

```
We emphasize that TLS is not a third Internet transport protocol, on the same
level as TCP and UDP, but instead is an enhancement of TCP, with the enhancements
being implemented in the application layer. In particular, if an application wants to
use the services of TLS, it needs to include TLS code (existing, highly optimized librar-
ies and classes) in both the client and server sides of the application. TLS has its own
socket API that is similar to the traditional TCP socket API. When an application uses
TLS, the sending process passes cleartext data to the TLS socket; TLS in the sending
host then encrypts the data and passes the encrypted data to the TCP socket. The
encrypted data travels over the Internet to the TCP socket in the receiving process.
The receiving socket passes the encrypted data to TLS, which decrypts the data.
Finally, TLS passes the cleartext data through its TLS socket to the receiving process.
```

## Transport services the Internet offers.
### TCP
TCP offers reliable data transfer, throughput and security (with TLS/SSL). This is ideal for applications that require complete message receiving, some throughput control and security, such as web servers and email servers. The PDU of tcp are named ```segments```.

### UDP
UDP, doesn't offer realiable data transfer, but may offer throughput and security. Ideal for applications that emphasize throughput, such as streaming applications. But this doesn't mean UDP can't be reliable, applications may run on UDP, but the application layer itself could deal with reliability in their own way. PDUS of the transport layer when using udp is named ```datagram```.
