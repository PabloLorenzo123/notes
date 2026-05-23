# The Network Core
In the first section we discussed about the edge, where we covered access and the different types of connection there exist to connect an access network to the head end. such as DSL (Direct Suscriber Line), Internet Cable, FTTH and Celullar.
We also concludes that the internet is the infraestructure that allow hosts (devices) to exchange data.

In this section we discuss what happens beyond the edge, how does this infraestructure create a network of networks. to explain this we first explore the different types of switching, such as packet switching and circuit switching. Then we discuss the internet architecture which consists of ISPS, Backbone ISPS, Pops, IXPs and CDNs.

## Packet Switching
Let's introduce router, this a networking device that receives packets and know in what link to send it, the internet consist of a mesh of these interconnected routers.
About is basic internal mechanisms, we should know that whenever a host needs to send a message to another hosts it does so by creating a packet, this packet contains the message and addressing information. this is sent as a stream of bytes theough the medium.
before the router can switch the packet, it first needs to receive all the bits of the packet this is done by buffering, then it does internal work to determine in what link to send the packet through, tough this is not inmediate if the tradfic is congestionated at the destination access link, the packet will wait on a queue, if the queue is full the packet or a packet in the queue may be dropped.

In packet switching the access links are determined on demand, they're no reserved. meaning at each hop the router will determine at ehich access link to forward the packet through.
In the book some math on message speed is discussed, if the router transmission rate is 100mb/s, and let's say host A needs to a 10mb packet to host B, with 2 hopes in between (2routers) then the total time the message will take to reach host B is (packet size) / (transmission rate ) * number-of-hops. which is 10mb / 100mb/s * 2 = 20s.
each hop will determine the best route by using an address table, whose values are filled statically or through a protocol such as OSPF or EIGRP.

## Circuit switching
Consists on coordinating the reservation of connection links that form a path from host a to host b. this path is reserved, this was common in the earlier eras of telephone, there are multiple ways to achieve this, and these are Frequency Division Multiplexing and Time Division Multiplexing.

### FDM
multiple channels in an access link are created by splitting the frequencies. a band of frequency is given to each channel, this is ehat radios do btw.
This way an access link can handle multiple connections. The disadvantage of this approach is that the bandwith is shared and therefore propagation speed is slower.

## TDM
Everyone gets the entire bandwith of the access link, but only at a certain intervable of time. for instance an access link may ne able to send 1 frame per second, and this frame can be divided in time slot, let's say 2, so each time slot is 0.5s. if host A needs to communicate with host b, host a may be given the session no2. meaning it can only send a certain amount of bits every 0.5s, when it get its turn. the disadvantes of this approach ars,
implementation difficulty, every hop needs to be coordinated including the hosts. and also the amount of sessions available in each access link is easily over demanded.

Circuit switching has the main disavantage that someone may have a session while staying idle, locking resources someone else may need.

today the internet use packet switching as it's easier to implement, most of the times offer better propagation speed, bandwith and use of shared resources.

finally i didn't go into much detail about this, but another circuit switching approach is to have multiple access links between nodes/hops, and dedicating the entire access link to a session.

## Internet Architecture
This chapter started up with an analogy, let's say you are in Punta Cana and needs to get to Downtown in Santo Domingo. You may ask someone in the gas station, in how to get there most likely the samaritan won't know the full route but it reada from your address destination you want to go to Sanro Dominfo, so he points you to the nearest highway that takes you to Santo Domingo. When you reach Santo Domingo, you again asks for Bella Vista, Downtown Center, this person won't know exactly how to take you to downtown center but knows that i you g doen the Nuñez avenue you will get to the Bella Vista Secto, finally in Bella Vista sector you ask for downrwon center, someone guides you there and finally you got to your destination.

no one, knew entirely how to get to your destination, but knows who you should ask next. the same happens with the internet.

long story short, At the lowest level we have our local isps, then we have our regional isos and then the backbone isos such as At&T. isps may share their infrastructure route at a 0 fee cost at IXPS (Internet exchange points), the backbone isps hace many Pops (point of presence), regional and local isps can connect to, and they pay a fee for traffic that gors through their network.
Content Delivery Netsorks such as Google, Cloudflars, hava servers all around the world, a huge private network that's connected through these IXPS, so their content are closer to the users, avoiding internet bacbone traffic.


