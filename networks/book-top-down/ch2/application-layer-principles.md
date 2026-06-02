# Principles
Application layer is the top most layer in the OSI layer architecture, this layer runs inside processes themselves, as you may know a program and a proccess are not the same thing, in computing terms a process is the active execution of a program in an computer which is handled by the operating system, a computer can have multiple programs running.

For networking to be useful, we need services that rely on networks, if not everything is useless. This most top layer, refers to the protocols that proccesses that live in different machine use to exchange data.

## Network Application Architectures.

### Client-Server Architecture.
The most widely used and most common application architecture developers use is the client-server architecture. In this in a connection proccesses have different roles, the client is usually the one that begins the connection and ask for things, while the server is the one who handles request and execute application logic. Examples are the Web and Email.

This architecture doesn't self scale unlike P2P, if there are multiple clients and a few servers, the servers can get overloaded making the application unusable. But these applications are usually more secure, because important application operations are executed on a hosted server.

### P2P - Peer to Peer.
In this architecture, a process is a client and a server at the same time. Example with File Transfer Protocol (FTP).

Its main advantage is that there are no intermediary between two clients, and applications built on this architecture auto-scale.

## Proccess Comunicating
As i said earlier process live in a host computer, and this host can have multiple proccesses running at at time. The operating offer a tool/abstraction to process to allow for Inter Proccess Communication (IPC) to a remote Process, this abstraction is called a 'Socket'.

With a socket the programmer indicates, where it needs to send the information to, and this socket handles the transport layer concerns. See this as the adapter between the process and the transport layer. A process is like a home, and a socket is like a door, whatever comes from outside enter through this door, and whatever needs to be sent from this home goes out of that door.

In POSIX, the socket programming interface is defined.

## Transport Services Available to Applications.
These are reliable data transfer, througput, and security.

## Transport services the Internet offers.
