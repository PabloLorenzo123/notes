# Network Security

The internet is full of bad guys. The internet at first was intended to be a system in where we would only have mutual trusting participants. But that's not the case.

## DoS Attacks
These are denial of service attacks, attackers want to stop a service from functioning by either.

- Flooding the access link with packets: making legit clients experience huge delay.

- Creating multiple connections: a server can only handle so many connections.

If all this traffic come from one source, then it may be easy for a server to protect itself from them by adding rate limiting. But, there are more sophisticated cases.

### DDoS
Distributed Denial of service attacks, consist on having multiple clients (botnet) attack a service. An attacker can do this by infecting multiple clients with malware, and making them participate in the attack these group of affected clients is named a botnet.

## Packet Sniffing
Specially in wireless network, someone could have a passive device reading all the packets that flow through the medium and maybe capturing some sensitive data, wireshark is a packet sniffer!. This also happen in wired connections too, specially wired shared broadcasted connections.

## Ip Spoofing.
The attacker modifies the source ip field in the ip header so the packet appears to come fron another machine.
