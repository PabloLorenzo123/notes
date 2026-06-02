# SECTION 1.1 Internet definition

## R1. What is the difference between a host and an end system? List several different types of end systems. Is a Web server an end system?

A host an end system are the same thing. The different types of end systems are clients, and servers, the client and server role will depend on the type of communication, a client won't always be a client, neither a server will always be a server.

Yes a web server is an end sytem.

## R2. The word protocol is often used to describe diplomatic relations. How does Wikipedia describe diplomatic protocol?

Wikipedia describer diplomatic protocol as a system of rules, procedures and accepted behaviors governing diplomacy and state affairs. It includes matters of etiquette, precedence, and formal conduct between governments, diplomats, and heads of state.

## R3. Why are standards important for protocols?
As i see it, protocols are a group of standards. While protocols define a shared 'standarized' way of communication between hosts, it's the standards that define exactly how. For instance, web browsers and web clients follow the Http Protocol.

Because the web browser needs to follow the http protocol, when it makes a request it needs to include the 'host' header because the standard say it's mandatory. Now, the browser can parse the payload from any web browser correctly by following the http standards, and by 'protocol' it will return a response.

# SECTION 1.2 Access Network - READ AGAIN!
## R4. List four access technologies. Classify each one as home access, enterprise access, or wide-area wireless access.
- DSL: home access.
- Cable: home access.
- FTTH: home access.
- Wi-fi: home access, enterprise access.
- Ethernet: enterprise access.
- 4G/5G: wide-area wireless access.

## R5. Is HFC transmission rate dedicated or shared among users? Are collisions possible in a downstream HFC channel? Why or why not?
HFC architecture is a hybrid usage of fiber and coaxial cable (Hybrid Fiber Coaxial), the Cable Provider connects to multiple 'hubs' and these hubs have multiple coaxial cables connecting to the homes. When a packet comes from the internet to the CMTS (Cable Modem Termination System) at the isp's facility, this packet is forwarded to the correspoding neighborhood hub, and then broadcasted to all homes. Because of this the bandwith of the downstream is split between the homes, as packets destined for a certain home may be put on a queue causing a stastistical perceived lower transmission rate.

No, there can't be collisions on the downstream channel, because the coaxial cable has a downstream channel, and a upstream channel by using FDM (Frequency Division Multiplexing), and the only device that's sending downstream data is the neighborhood's hub.

## R6. List the available residential access technologies in your city. For each type of access, provide the advertised downstream rate, upstream rate, and monthly price.


## R7. What is the transmission rate of Ethernet LANs?
From 100mb/s (fastethernet), 1gb/s (gigaethernet) and 10gb/s.

## R8. What are some of the physical media that Ethernet can run over?
Ethernet can run over several types of physical media, including twisted-pair copper cables such as UTP and STP, coaxial cable in older Ethernet standards, and fiber-optic cable.

## R9. HFC, DSL, and FTTH are all used for residential access. For each of  these access technologies, provide a range of  transmission rates and comment on whether the transmission rate is shared or dedicated.

**HFC** Hybrid Fiber coaxial, provides an assymetric transmission rate where the downstream rate is higher than the upstream's. Even though the coaxial cables use FDM (Frequency Division Multiplexing), a bandwith can only be divided so many times, in most cases homes are sharing their bandwith with a neighbor. Let's remember that HFC is one type of cable network.

**DSL** Dynamic Subscriber Line, provides also provides an assymetric transmission rate, the bandwith is divided in a phone and data channel. It's not shared, the FDM is only used for splitting phone communication from data communication. This access technologie relies on the telephone companies infrastructure.

**FTTH** Fiber to the Home, usually fully symmetrical. and it's a shared medium.

# R10. Describe the most popular wireless Internet access technologies today. Compare and contrast them.
We have Wi-fi (WLAN) IEEE 802.11 and Cellular Networks (3g, 4g, 5g). Their main difference is that the former provides access at a shorter range, the signal is susceptible to loss due to physical objects and it' used mainly in home and enterprise networks. The latter provides way broader ranges - Wide Area Network, but lower speeds.

# SECTION 1.3
# R11. Suppose there is exactly one packet switch between a sending host and a  receiving host. The transmission rates between the sending host and the switch and between the switch and the receiving host are R1 and R2, respectively. Assuming that the switch uses store-and-forward packet switching,  what is the total end-to-end delay to send a packet of length L? (Ignore queuing, propagation delay, and processing delay.)

Let's say packet length is 100mb, and R1 and R2 is 100mbs.

From sending host to switch is 100mb / (100mb/s) = 1s
From middle switch to receiving host 100mb / (100mb/s) = 1s

1s + 1s = 2 seconds.

# R12. What advantage does a circuit-switched network have over a packet-switched network? What advantages does TDM have over FDM in a circuit-switched network.


# R13. Suppose users share a 2 Mbps link. Also suppose each user transmits continuously at 1 Mbps when transmitting, but each user transmits only 20 percent  of the time. (See the discussion of statistical multiplexing in Section 1.3.)

a. When circuit switching is used, how many users can be supported?

b. For the remainder of this problem, suppose packet switching is used. Why will there be essentially no queuing delay before the link if two or fewer  users transmit at the same time? Why will there be a queuing delay if  three users transmit at the same time?

c. Find the probability that a given user is transmitting.

d. Suppose now there are three users. Find the probability that at any given  time, all three users are transmitting simultaneously. Find the fraction of time during which the queue grows.
