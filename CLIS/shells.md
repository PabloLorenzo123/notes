# SHELLS

Shells are command line interpreter programs, meaning they are text-based interfaces whose job is to:

1 - Read commands as text.
2 - Parse the commands and arguments.
3 - Launch subprocesses/programs.

Examples of shells:

* `sh` (POSIX shell)
* `bash` (Bourne Again Shell)
* `zsh`
* `fish`

The shell itself does not execute machine code directly, instead it asks the kernel to create processes through system calls such as `execve()`.

Example:

```bash
node app.js
```

Execution flow:

```text
shell reads command
↓
shell parses arguments
↓
shell looks for executable in PATH
↓
shell calls execve("/usr/bin/node", ["node", "app.js"])
↓
kernel loads executable into memory
↓
new process starts
```

---

# POSIX

POSIX stands for:

```text
Portable Operating System Interface for UNIX
```

POSIX is a standard/specification which defines:

* Process APIs
* File APIs
* Shell behavior
* Standard utilities/commands

Examples of standardized utilities:

* `cd`
* `ls`
* `mkdir`
* `pwd`

UNIX-like operating systems usually implement most of the POSIX specification.

A POSIX shell is a shell implementation that follows the POSIX shell standard.

Usually:

```bash
sh
```

is considered the minimal POSIX shell.

---

# BASH

Bash (Bourne Again Shell) is a shell implementation compatible with POSIX, but with many extra features added on top.

Examples of Bash-only features:

* Arrays
* `[[ ]]` conditions
* Better scripting syntax
* History features
* Autocomplete

Important:

```text
bash = shell/interpreter
ls = utility/tool
docker = utility/tool
npm = utility/tool
```

Bash is not a CLI tool itself, it is the environment that launches CLI tools.

---

# SHELL SCRIPTS

A shell script is simply a text file containing shell commands.

Example:

```sh
echo hello
mkdir test
npm install
```

The kernel itself does NOT understand shell syntax.

The shell/interpreter understands shell syntax.

---

# SHEBANG

A shebang is the first line of a script:

```sh
#!/bin/sh
```

or:

```js
#!/usr/bin/env node
```

The shebang tells the kernel which interpreter should execute the file.

---

# WHY SHEBANGS EXIST

Suppose this file exists:

```sh
echo hello
```

Linux sees:

```text
This is just a text file.
What program should interpret it?
```

The shebang solves this problem.

---

# KERNEL VS SHELL RESPONSIBILITY

The shell:

* Parses shell syntax.
* Reads commands.
* Calls process APIs.

The kernel:

* Loads executables into memory.
* Creates processes.
* Reads shebangs.
* Launches interpreters.

The kernel does NOT understand shell syntax.

---

# EXECUTION FLOW OF A SCRIPT

Suppose:

```sh
#!/bin/sh

echo hello
```

and we execute:

```bash
./script.sh
```

Execution flow:

```text
shell calls execve("./script.sh")
↓
kernel reads first line:
#!/bin/sh
↓
kernel internally transforms execution into:
execve("/bin/sh", ["/bin/sh", "./script.sh"])
↓
/bin/sh starts
↓
sh interpreter reads script contents
↓
commands execute
```

---

# /usr/bin/env

Another common shebang is:

```js
#!/usr/bin/env node
```

Execution flow:

```text
kernel executes:
/usr/bin/env node script.js
↓
env searches PATH for executable named "node"
↓
env finds node executable
↓
env executes:
execve("/usr/bin/node", ["node", "script.js"])
```

This makes scripts more portable because the executable may exist in different locations across systems.

---

# LF VS CRLF

Linux line endings:

```text
LF = \n
```

Windows line endings:

```text
CRLF = \r\n
```

Many Linux interpreters/scripts expect LF endings.

Windows CRLF endings can sometimes corrupt shell scripts because hidden `\r` characters become part of the interpreted text.

---

# VALID SCRIPT EXAMPLES

POSIX shell script:

```sh
#!/bin/sh

echo hello
npm install
```

Node script:

```js
#!/usr/bin/env node

console.log("hello")
```
