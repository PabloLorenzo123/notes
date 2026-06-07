# DNS (Domain Name System)
Is a client-server UDP sometimes TCP based application protocol used to resolve ip addresses from hostnames. At its core it works as the biggest distributed database in the world. DNS is an application-layer protocol that primarily uses UDP over port 53, although TCP is also used in several scenarios. Its architecture is based on an hierarchichal structure which consists on the following components:

![alt text](image-2.png)

- Client: browser or device asking to resolve a hostname's ip address.
- Resolver: Is in charge of recursively finding the hostname's ip address.
- Root Server: Contains the NS records for the TLD (Top level domains servers) - There are 13 logical servers of these in the world, but hundred of replicaed anycast instances worldwide. These know which server manage each top-level domain such as .com, .net, or .org.
- TLD (Top Level Domain) Servers: Contains the NS records for the available Authorative Servers.
- Authorative Servers: Contains the A, AAA, MX records for the hostnames that belong to this certain authorative server. e.g dns.google.com. they're the source of truth.

## Different Record Types
A record has the following structure (Name, Value, Type, TTL).
1 - A Records: the Name is the hostname, and the value is the IPV4 Address. These records live in the authorative servers.
2 - AAAA Records: the Name is the hostname and the value is an IPV6 Address. These records live in the authorative servers.
3 - CNAME Records: Name is an Alias, and Value is the real hostname,for instance Name could be UNIT.COM.DO and value app-unit-prod.azurewebsites.net.
4 - NS records: Name is a hostname, and Value is the authorative Server, ex pablom.com IN NS ns1.cloudflare.com - Meaniing ask Cloudflares' DNS servers about this domain.
5 - MX: Name is the domain receiving mail, and value is the server, ex Name = @Unphu.edu.do, Value = mail.google.com.

## Flow
Let's say you created a startup lorenzo-technologies, and want to register a domain, you'll visit a ```registar``` such as GoDaddy and buy the domain. GoDaddy wil take care of entering a CNAME record for (YourDomain, GoDaddyInternalsDomain, CNAME, TTL) and an A Record for (oDadyInternalsDomain, IPV4, A, TTL), this is done so your domain isn't attached to an ipv4 address but to an alias.

When an investor visit your startup, their DNS resolver will ask a root server for who knows about a server who saves the .com top level domains? this root server will respond with a list of NS records accompanied by their respective A record.

Then the resolver will ask the TLD servers, for who knows about lorenzo-technologies.com, the registar should have filled this tld servers with a NS record lorenzo-technologies.com IN dns.godaddy.com and an A record for dns.godaddy.com in x.x.x.x.

Finally the resolver will ask the go daddy authorative server for lorenzo-technologies.com, which will respond with a CNAME record an A record. The resolver has now found the ip address for the startup.

This approach is called the iterative approach. client -> resolver is recursive approach.

Note that there exist caching on all the levels. There are also internal comapnies dns server, and ISP dns servers, we have explored the benefits of web cache in this chapter previously.
