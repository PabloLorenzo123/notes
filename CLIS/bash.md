# COMMANDS

## CHOWN

`chown` stands for:

```text
change owner
```

It changes the ownership metadata of files/directories.

In Linux, files are associated with:
1 - An owner user.
2 - An owner group.

Example:

```bash
ls -l
```

Output:

```text
-rw-r--r-- 1 pablo developers 1200 app.js
```

Meaning:

| Field        | Meaning     |
| ------------ | ----------- |
| `pablo`      | owner user  |
| `developers` | owner group |

---

### WHY OWNERSHIP EXISTS

Linux permissions are evaluated using:
1 - Owner permissions.
2 - Group permissions.
3 - Other/world permissions.

Execution flow:

```text
process tries to access file
↓
kernel checks process UID/GIDs
↓
kernel compares against file owner/group
↓
kernel decides whether operation is allowed
```

---

### BASIC SYNTAX

```bash
chown USER:GROUP FILE
```

Example:

```bash
chown pablo:developers app.js
```

Meaning:

```text
Change owner user to "pablo"
Change owner group to "developers"
```

---

### RECURSIVE OPTION

```bash
chown -R USER:GROUP DIRECTORY
```

`-R` means recursive.

Execution flow:

```text
kernel traverses directory tree
↓
ownership changes applied to:
- current directory
- child files
- child directories
- nested contents
```

Example:

```bash
chown -R pablo:developers my-project
```

---

### IMPORTANT

`chown` changes ownership metadata, NOT file permissions.

Permissions are changed with:

```bash
chmod
```

Example:

```bash
chmod 755 app.sh
```

---

### COMMON EXAMPLES

Change only owner user:

```bash
chown pablo file.txt
```

Change owner and group:

```bash
chown pablo:developers file.txt
```

Change only group:

```bash
chown :developers file.txt
```

Recursive ownership change:

```bash
chown -R www-data:www-data /var/www/html
```

Common in:

* Docker
* Nginx
* PHP/Laravel
* Linux web servers

## CHMOD