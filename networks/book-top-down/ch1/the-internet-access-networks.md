# Definition of the Internet
Internet is the infrastructure that allow user applications to use services. in my own words, this infrastructure allows end devices to exchange data. this end devices are known as hosts.

This infrastructure follows a hierarchical architecture, composed of many interconnected networks at each level of the hirearchy. 'The Edge' networks are the access networks, meaning the first level a host reaches when sending a packet and the last router that delivers the packets to the hosts, this consists of local ISPs (TIER 3), then we have national ISP (tier 2) in where the ISPs networks are interconnected in data centers named as 'internet exchange points' IXPS in this level we can also find CDNS (Content Delivery Networs - Servers that serve static content at the edge among other things - edge computing), and finally we have the international level (tier 1), in where the biggest isps share their infrastructure in IXPS, this allows global connection.

# Types of Network Connections

## DSL - Digital Subscriber Line
Most telcon companies offer telephone line and internet access to their customers, using the same infrastructure they used for the telephone line, this is achieved by using multiplexing, the frequencies of the telephone line are 0khz-4khz, downstream-data is 50hz to 100hz, and upstream-data 4khz-50hz, providers usually offer more downstream speed than upstream. At home the user will have a splitter, that will split the telephone line from the internet data line, and a modem which will demodule the high frequency internet data received from the head-end and transform it into data and at the same time transform user data into high frequency signals to put it in the dsl line back to the head-end.

At the head-end (telcon company), they'll have a DSLAM, which is a machine that demodules incoming internet data and then transmits it usually through an ethernet network to the internet network. Also de DSLAM differentiates telephone signal, from internet data.

## Cable Internet
Same as DSL, but with television cable infrastructure, which uses coaxial cable.
### HFC (Hybrid FIber-Coaxial)
Today most companies use a combination of fiber and coaxial, in where from the head-end to the neighborhodds access points there's fiber cable, and then from the access point to the homes there's coaxial cable.

Both in DSL and Coaxial, the bandwith is shared between homes.

## 4G/5G.
This is wireless network technology, use anthenas and have a broad reach and high internet speeds.

## Ethernet
this is the fastest one, most common used in lans. In home networks the connection between the head-end and home is usually DSL or by television cable, then at home a local network is created by using ethernet cables. For instance a home may have a wifi router wich is a wireless access point, connected through a modem via ethernet to be able to access the internet.


# AI CORRECTION

# Definition of the Internet

The Internet is a massive interconnection of networks that allows hosts around the world to exchange data using the TCP/IP protocol suite. In simpler terms, the Internet is the infrastructure that enables end devices to communicate with each other.

These end devices are known as **hosts**. Examples include computers, smartphones, servers, smart TVs, and IoT devices.

The Internet follows a hierarchical architecture composed of many interconnected networks.

At the edge of the Internet we have **access networks**, which are the first networks a host reaches when sending data and the last networks responsible for delivering data back to the host. These are usually local or regional ISPs.

Above them are larger regional and national ISPs, which interconnect their networks through facilities known as **Internet Exchange Points (IXPs)**. At this level we can also find **CDNs (Content Delivery Networks)**, which place servers closer to users in order to reduce latency and improve performance.

Finally, at the highest level, large global backbone providers interconnect continents and countries, enabling worldwide communication across the Internet.

---

# Types of Network Connections

## DSL - Digital Subscriber Line

Many telecommunication companies provide both telephone and Internet access using the same copper telephone line infrastructure. This is achieved through **Frequency Division Multiplexing (FDM)**, where different frequency ranges are reserved for voice and Internet data.

A simplified frequency division in ADSL may look like this:

* Voice calls: approximately `0 kHz - 4 kHz`
* Upstream data: approximately `25 kHz - 138 kHz`
* Downstream data: approximately `138 kHz - 1.1 MHz`

Providers usually offer more downstream bandwidth than upstream bandwidth because most users consume more data than they upload.

At home, the user typically has:

* A **splitter**, which separates telephone signals from Internet data signals.
* A **modem**, which modulates and demodulates data:

  * Converts digital user data into high-frequency electrical signals for transmission over the DSL line.
  * Converts incoming electrical signals back into digital data.

At the provider's side there is a device called a **DSLAM (Digital Subscriber Line Access Multiplexer)**. The DSLAM aggregates many customer DSL connections, separates voice traffic from data traffic, and forwards Internet traffic into the provider's network.

---

## Cable Internet

Cable Internet uses the same coaxial cable infrastructure originally designed for cable television.

The most common technology behind cable Internet is:

* DOCSIS

Unlike DSL, coaxial cable provides higher bandwidth and is less susceptible to electrical interference.

### HFC - Hybrid Fiber-Coaxial

Modern cable providers usually use an HFC architecture.

In this architecture:

* Fiber optic cables connect the provider's head-end to neighborhood distribution points.
* Coaxial cables then connect the neighborhood nodes to individual homes.

This design combines the high speed of fiber with the lower deployment cost of coaxial cable.

One important characteristic of both DSL and Cable Internet is that bandwidth is often shared among nearby homes.

---

## 4G / 5G

4G and 5G are wireless cellular network technologies.

Instead of using physical cables, devices communicate using radio waves with nearby cellular base stations (cell towers). The provider divides geographic regions into cells, each served by antennas operating on specific frequency ranges.

As users move, devices can transition between towers through a process called **handoff**.

5G improves upon 4G by offering:

* Lower latency
* Higher bandwidth
* Better support for large numbers of connected devices

---

## Ethernet

Ethernet is the most common wired LAN (Local Area Network) technology.

Ethernet is primarily used inside local networks such as homes, offices, and data centers.

In a typical home network:

1. The Internet connection arrives through DSL, Cable, Fiber, or Cellular infrastructure.
2. A modem connects the home to the ISP.
3. A router creates the local network.
4. Devices communicate locally through:

   * Ethernet cables (wired)
   * Wi-Fi (wireless)

For example, a Wi-Fi router usually acts as:

* A router
* A wireless access point
* A small Ethernet switch

The router itself is commonly connected to the modem through an Ethernet cable.
