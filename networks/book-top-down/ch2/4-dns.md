# DNS (Domain Name System)
Is a client-server UDP sometimes TCP based application protocol used to resolve ip addresses from hostnames. At its core it works as the biggest distributed database in the world. DNS is an application-layer protocol that primarily uses UDP over port 53, although TCP is also used in several scenarios. Its architecture is based on an hierarchichal structure which consists on the following components:

![alt text](image-2.png)

- Client: browser or device asking to resolve a hostname's ip address ```nslookup```.
- Resolver: Is in charge of iteratively finding the hostname's ip address.
- Root Server: Contains the NS records for the TLD (Top level domains servers) - There are 13 logical servers of these in the world, but hundred of replicated anycast instances worldwide. These map multiple TLD (.com, .org, .net, etc) with a list of TLD servers.
- TLD (Top Level Domain) Servers: Contains the NS records for the available Domains under the tld, and the A or AAA records for the Authorative Name Servers.
- Authorative Servers: These have the A, AAA, MX records of one or more zones, a zone is just the list of subdomains a domain has. For instance ns1.goddady.com can host the zones of multiple businesses, the reverse is also true a zone can be replicated in multiple authorative servers.
- Registar: An IANA (Internet Assigned Numbers Authority) accredited company, that sells Domain names, these validate domain uniqueness and are responsible for entering new entries in the TLD servers for the domains sold. E.G GoDaddy.

The Server hierachy is root server -> tld server -> authorative name server.

## Services Offered by DNS
1 - Name to Ip Address Mapping.
2 - Alias Name to Canonical Name mapping.
3 - Load Balancing: An authorative name server can have multiple entries for the same query, but it can send it in a rotated way, taking into account that the DNS clients usually picks the first result returned to it:

```
C:\Users\U1075>nslookup google.com ns1.google.com
Server:  ns1.google.com
Address:  216.239.32.10

Name:    google.com
Addresses:  2607:f8b0:4002:c2c::8a
          2607:f8b0:4002:c2c::8b
          2607:f8b0:4002:c2c::71
          2607:f8b0:4002:c2c::65
          142.251.15.102
          142.251.15.100
          142.251.15.139
          142.251.15.113
          142.251.15.138
          142.251.15.101


C:\Users\U1075>nslookup google.com ns1.google.com
Server:  ns1.google.com
Address:  216.239.32.10

Name:    google.com
Addresses:  2607:f8b0:4002:c2c::71
          2607:f8b0:4002:c2c::8a
          2607:f8b0:4002:c2c::66
          2607:f8b0:4002:c2c::64
          142.251.15.100
          142.251.15.101
          142.251.15.102
          142.251.15.139
          142.251.15.138
          142.251.15.113
```

see how the list of addresses have different order in both queries.

## Different Record Types
A record has the following structure (Name, Value, Type, TTL).
1 - A Records: the Name is the hostname, and the value is the IPV4 Address. These records live in the authorative servers.
2 - AAAA Records: the Name is the hostname and the value is an IPV6 Address. These records live in the authorative servers.
3 - CNAME Records: Name is an Alias, and Value is the real hostname, for instance Name could be UNIT.COM.DO and value app-unit-prod.azurewebsites.net.
4 - NS records: Name is a hostname, and Value is the authorative Server name, ex pablom.com IN NS ns1.cloudflare.com - Meaniing ask Cloudflares' DNS servers about this domain, these usually leave in the TLD servers and sometimes accompanied by a glue entry which consists on a A/AAA record where the Name is the DNS name, and the value the Ip of the authorative server, specially when the NS record Name and Value have the same domain ex: (lorenzo.com, dns.lorenzo.com, NS, TTL) glued by (dns.lorenzo.com, 111.111.111.111, A, TTL).
5 - MX: Name is the subdomain receiving mail, and value is the server, ex Name = @Unphu.edu.do, Value = mail.google.com.

## DNS in Action
Let's say you created a startup lorenzo-technologies, and want to register a domain, you'll visit a ```registar``` such as GoDaddy and buy the domain. there are two paths from here:

1 - GoDaddy can if you opt to host your zone in one of its NS servers. Goddady will enter NS record in the .COM TLD servers with your domain, If so the .com TLD server would look like
```
...
(pablolorenzo.com, ns1.godaddy.com, NS, TTL)
(ns1.godaddy.com, 1.2.3.4, A, TTL) // this is not necessary. if this server doesnt have this entry, the resolver needs to make another query to get the address of this ns server.
```

2 - You only use GoDaddy to buy the domain, and insert it into the TLD servers. You should then not only pass godaddy your domain name but also the ips and names of your primary and secondary authorative name servers, as these authorative name servers are handled by a provider such as cloudflare or even yourself.
```
...
(pablolorenzo.com, ns1.cloudflare.com, NS, TTL)
```

Another case is if you have your own authorative server then the registar should not only get your domain in the tld server, but also a glue entry.
```
...
(pablolorenzo.com, ns1.pablolorenzo.com, NS, TTL)
(ns1.ppablolorenzo.com, 1.2.3.4, A, TTL) // this is necessary, if not you create an infinite loop.
```

At this point you have your domain registered, and have your authorative name servers running. In your authorative name servers you need to configure the DNS server application such as BIND, in where you enter your DNS records in case you opted to manage your own servers, or should fill the config for the provider who is hosting your zone. Let's suppose for now you only have an email and web service, you shall configure the following entries.

```
(Name=@, Value=1.2.3.4, Type=A, TTL) // the apex lorenzo.com.
(Name=www, Value=1.2.3.4, Type=A, TTL) // the web service www.lorenzo.com.
(Name=@, Value=10 aspmx.l.google.com, Type=MX, TTL) // the email service.
```

In case your website or server is hosted by a cloud provider, you should create cname entries for your web server instead of an A entry. And in your cloud provider app configuration, add your custom domain, so it knows what 'host' (http header) to accept and the corresponding content to serve.

Great, you now have your domain, and servers available to the world.

When an investor visit your startup, their DNS resolver will ask a root server for who knows about a server who saves the .com top level domains? this root server will respond with a list of NS records accompanied by their respective A/AAA record.

Then the resolver will ask the TLD servers, for who knows about lorenzo-technologies.com, the registar should have filled this tld servers with a NS record lorenzo-technologies.com IN ns.godaddy.com and an A record for ns.godaddy.com in x.x.x.x.

Finally the resolver will ask the go daddy authorative server for lorenzo-technologies.com, which will respond with a CNAME record OR an A record. The resolver has now found the ip address for the startup.

This approach taken by the resolver is called the iterative approach. and the approach taking by the dns client to its local dns server is a recursive approach.

Note that there exist caching on all the levels. There are also internal companies dns server, and ISP dns servers, we have explored the benefits of web cache and caching in this chapter previously.

## DNS IN Action (GPT)
# DNS in Action

Let's say you create a startup called Lorenzo Technologies and want to register a domain name. You'll visit a registrar such as GoDaddy and purchase a domain, for example:

```text
pablolorenzo.com
```

A registrar's job is to verify the uniqueness of the domain, register ownership of the domain, and configure which authoritative DNS servers are responsible for answering queries about that domain.

There are several possible setups.

## Option 1 - GoDaddy Hosts Your DNS Records

You may choose to use GoDaddy's DNS hosting service. In this case, GoDaddy will host the DNS records for your domain on one or more of its authoritative name servers.

The registrar will update the `.com` TLD servers so they know which authoritative servers are responsible for your domain.

Conceptually, the `.com` TLD servers will contain something similar to:

```text
pablolorenzo.com. NS ns1.godaddy.com.
pablolorenzo.com. NS ns2.godaddy.com.
```

Notice that the `.com` servers do not store your website records. They only know which authoritative servers should be queried next.

No glue records are required because `ns1.godaddy.com` belongs to another domain and can be resolved independently.

## Option 2 - A Third Party Hosts Your DNS Records

You may purchase the domain through GoDaddy but delegate DNS hosting to another provider such as Cloudflare.

The `.com` TLD servers would then contain:

```text
pablolorenzo.com. NS ns1.cloudflare.com.
pablolorenzo.com. NS ns2.cloudflare.com.
```

Again, no glue records are required because the resolver can independently resolve `cloudflare.com`.

## Option 3 - You Host Your Own Authoritative DNS Server

You may operate your own DNS infrastructure.

Suppose your authoritative DNS server is:

```text
ns1.pablolorenzo.com
```

In this case the `.com` TLD servers need both the NS record and a glue record:

```text
pablolorenzo.com. NS ns1.pablolorenzo.com.
ns1.pablolorenzo.com. A 1.2.3.4
```

The second record is called a **glue record**.

Without the glue record, the resolver would need to resolve `ns1.pablolorenzo.com` before it could query it, creating a circular dependency.

## Configuring DNS Records

Once the domain has been delegated to your authoritative DNS servers, you can configure DNS records.

If you manage your own DNS servers, you would use software such as BIND.

If you use a DNS provider such as GoDaddy or Cloudflare, you would configure the records through their dashboard.

For a simple website and email setup:

```text
@       A       1.2.3.4
www     A       1.2.3.4
@       MX      10 aspmx.l.google.com
```

Meaning:

```text
pablolorenzo.com      -> 1.2.3.4
www.pablolorenzo.com  -> 1.2.3.4
```

and email for the domain is handled by Google's mail servers.

## Cloud Hosted Applications

If your application is hosted by a cloud provider such as Azure, you often create a CNAME record:

```text
www     CNAME   my-app.azurewebsites.net
```

instead of directly pointing to an IP address.

Additionally, the cloud provider must be configured to recognize your custom domain. This allows the provider to route requests based on the HTTP `Host` header.

## DNS Resolution

Suppose an investor visits:

```text
https://pablolorenzo.com
```

Their machine sends a recursive query to a DNS resolver (typically operated by an ISP, company, or public provider).

The resolver performs an iterative lookup.

### Step 1 - Ask a Root Server

The resolver asks:

```text
A pablolorenzo.com
```

The root server does not know the answer, but it knows who manages `.com`.

It responds with NS records for the `.com` TLD servers, often accompanied by glue records.

### Step 2 - Ask a `.com` TLD Server

The resolver asks:

```text
A pablolorenzo.com
```

The `.com` server does not know the answer either, but it knows which authoritative servers are responsible for the domain.

For example:

```text
pablolorenzo.com. NS ns1.godaddy.com.
pablolorenzo.com. NS ns2.godaddy.com.
```

### Step 3 - Ask the Authoritative DNS Server

The resolver asks:

```text
A pablolorenzo.com
```

The authoritative server is the source of truth for the domain and responds with the requested record:

```text
pablolorenzo.com. A 1.2.3.4
```

or

```text
pablolorenzo.com. CNAME my-app.azurewebsites.net
```

The resolver now has the information necessary to reach the web server.

## Recursive vs Iterative Queries

The communication between:

```text
Client -> Resolver
```

is usually recursive.

The client expects the resolver to return the final answer.

The communication between:

```text
Resolver -> Root
Resolver -> TLD
Resolver -> Authoritative Server
```

is iterative.

Each server either returns the answer or points the resolver to another server that is closer to the answer.

## Caching

DNS caching exists at multiple levels:

* Browser cache
* Operating system cache
* Company DNS servers
* ISP DNS servers
* Public DNS resolvers

Caching reduces latency and prevents the root, TLD, and authoritative servers from being queried for every DNS lookup.


### NS LOOKUP
Look for the Authorative Name Server of Unit.com.do
```
>nslookup -type=ns unit.com.do
Server:  GU00NAPDC.seguros.local
Address:  172.16.101.22

Non-authoritative answer:
unit.com.do     nameserver = ns1-03.azure-dns.com
unit.com.do     nameserver = ns2-03.azure-dns.net
unit.com.do     nameserver = ns3-03.azure-dns.org
unit.com.do     nameserver = ns4-03.azure-dns.info

ns1-03.azure-dns.com    internet address = 13.107.236.3
```

Azure is the authorative name server for unit.

```
C>nslookup unit.com.do ns1-03.azure-dns.com
Server:  UnKnown
Address:  13.107.236.3

Name:    unit.com.do
Addresses:  13.107.226.41
          13.107.253.41
```

Unit only has two ip addresses.

### THE DNS CLIENT MESSAGE FORMAT.
It has a header with some fields, first an identifier field, because DNS runs on UDP and doesn't build connections like TCP, it adds a unique identifier to every query the DNS resolver makes, so when it receives a response (which will include the same identifier) it can identify to which query the respond is for, though this design makes DNS susceptible to DNS poisoning.

Then it has a questions field, where the queries questions are sent in, and answer field where the answers are sent. Another field which is number of questions, and a number of answers field.