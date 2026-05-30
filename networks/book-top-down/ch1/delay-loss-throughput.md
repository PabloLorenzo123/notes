# Delay, Packet Loss And Throughput in Packet Switched Networks
Packet switched networks suffer from delay, packet loss and have variables throughputs due to the physical limitations of our world. In an ideal world, packets would arrive to end hosts instantenously. We define delay as the time taken for a message to get from source to destiny, packet loss occur when a router's queue is full (more on that later), and finally throughput is the amount of bits per second getting from source to destiny.

## Understanding how packets travel.
In the network core, we have multiple interconnected routers. Router receive packets and forward them through one of its interfaces - access links, the access link to forward is decided by an address table which can be configured manually or can be filled via routing protocols.

When a router receives a packet, it firt needs to get all the bits of the packet first before deciding in what interface to route it to, and this take time. Once the router has the full packet, it need to process it - read the src and dest address and decide where to forward the packet, finally it needs to put the packet bits in the destination access link one bit at a time, but only if there are no packets currently being proccessed in the router. Because a router can only send one packet a time, if the packets finds itself with more packets then i needs to wait in a **queue** which is another delay.

## Delays
As we have just read, delays in network have many culprits, but the ones related to the internet infrastructure are:

- Propagation Delay: is the delay the bit takes to get from a router to another router via an access link. The speed as with the bit moves through to the media is close to the speed of light and it will depend in the type of media.

- Queue Delay: the time a packet needs to wait in a queue, in order to be processed and then forwarded, if the queue is empty then there's no delay queue.

- Processing Delay: the time the router takes to read the packet and decide where to forward it to.

- Transmission Rate / Bandwith: the speed at which the router can place the bits of the packet on the wire, measured in bits per second.

The author used the following analogy, suppose a bit is a car and a caravan of 10 cars is a packet, and there's a tollbooth (router) every 100km. Suppose that cars travel at 100m/s, and a toolboth can proccess 4 cars per second. The speed the cars travel at is the propagation delay, the time a tollboth takes to dispatch a card is the transmission rate.

So if we have a destiny, and our path to it has two tollboths between them, and we will send a caravan, the total delay will be = 3 * [(100^3m) / 100m/s] + 2 * [10 cars / 4 cars/second]

## Packet Loss
We can calculate the traffic as La/R where L is the amount of packet, a bits per packet and R is the transmission rate. if La/R > 1 it means there's more bits coming to the router, than ones getting out which is bad the queue will infinitely get longer and longer resulting in **packet loss**. We should aim for La/R < 1.

## Throughput
See the access link as pipes, if the pipes are big enough, and you're pushing a current from one side, then most likely the current will go continously so the throughput of water will be equal to the current. But, if we find a narrow pipe, then the speed (current) of water flowing thorugh the entire path will be as fast as the current that pipe can handle.

The same happens with the internet, in practice throughput will be the minimun transmission rate speed of the access links across the path. Although if there are multiple clients in our network, it won't always be the lowest tranmission rate link our bottleneck but maybe the most congested access link because when there are multiple connections going through a link the transmission rate / bandwith is statiscally shared.

For instance, let's say we have Server X, and we have clients Y and Z. both connected all conected to the same router.

```

Y --[10mb packet]--|
                router --R=10mbps-- Server
Z --[10mb packet]--|

```

For client Y, its experience transmission rate will feel like 5mbps, because let's say client Z sent its packet first though experienced no delay its packet will be sent intatenously in 1 second, but client Y will wait on a queue for client Z packet to be done transmitting, sitting for 1 second, and then taking 1 second for client Y to be transmitted when he gets its turn.

Client Y's packet will take 2 seconds to be sent, though experiencing a transmission rate of '5mbps'. Because we can't guarantee client z will always get first on the queue or client y will, we say that both clients are experiencing a 5mbps transmission rate and also 5mbps throughput in this case


## Traceroute
With traceroute we can see the hops or packet take along a path, this protocol works by sending 3 messages (roundtrips). The terminal will show a table of the routers in the path, including their names, ip address and each roundtrip delay.

