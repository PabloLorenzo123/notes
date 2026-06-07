# Linux User and Groups
Linux is a **multi-user operating system**.

Meaning:
- Many users can exist in the same machine.
- Each user can have different permissions.
- Files/processes belong to users.

At its core Linux constantly asks:
```
Who is this?
What is this user allowed to do?
```

## Users
A user is simply an identity inside the operating system.

examples:
```
pablo
root
nginx
mysql
ubuntu
```

Users are used for:
- logging in.
- owning files.
- running processes.
- controlling permissions.

Users are not just humans, they are applications, services, daemons. they exist so programs run with isolated permissions.

### ROOT USER
linux has a super user called ```root```, this user can do about everything:
- read everything.
- modify everything.
- kill every process.
- install software.
- change ownership.
- destroy the system.

### USER IDs (UID)
Users are identifies by uids. but these are reserverd:
0 - rooot.
1 - 999 -> sstem/service users.
1000+ -> normal human users.

Note: Processes run as users, programs run as users too. ex nginx run as: www-data, mysql runs as: mysql.

## Groups
A group is a collection of users, built with the purpose of simplifyng permissions management. instead of giving permission to each user, add permision to groups, and user to groups.

Each user belongs to one primary group.
```
uid=1000(pablo) gid=1000(pablo) groups=1000(pablo),27(sudo)
```

here the primary group is palo, and additional group is sudo.

## Files and Ownership
Every file has a owner user, owner group and permissions.

## Linux Phiosophy
Linux security is heavily based on: users, groups, permissions. everything builds on top of this:
- files.
- processes.
- sockets.
- docker.
- nginx.
- ssh.
- databases.

## Some commands
- whoami
- id
- cat /etc/passwd - prints all users.
- groups
- cat /etc/group - prints all groups.
- sudo useradd pablo - adds an users
- sudo groupadd developers - create a group.
- sudo usermod -aG developers pablo - add pablo to group developers a is for append and g for groups.

Processes are workers acting on behalf of users.