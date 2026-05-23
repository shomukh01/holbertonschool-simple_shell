# Simple Shell - Custom Linux Command Line Interpreter

A fully functional, minimalist Unix shell developed in C. This project is a foundational exploration into low-level system programming, process management, and memory allocation within the Linux operating system, strictly compliant with the **Ubuntu 20.04 LTS** environment and **Betty Coding Standards**.

---

## 🚀 Project Overview

The `hsh` executable mimics the essential behaviors of the standard `/bin/sh` shell. It interprets user commands, resolves paths dynamically, handles process lifecycles via system forks, and cleans up memory dynamically to prevent any leaks.

### Key Features
* **Dual Execution Modes:** Fully supports both interactive terminal input and non-interactive piping.
* **Smart Path Resolution:** Locates external binary commands globally using a custom environment parser.
* **Built-in Command Suite:** Native internal support for execution routing (`exit` and `env`).
* **Signal Interception:** Gracefully traps `Ctrl+C` (`SIGINT`) without breaking the shell instance.
* **Conditional Logic Chains:** Processes complex input strings structured with logical `&&` and `||` operators.

---

## 🛠️ System Calls & Functions Used

This shell architecture safely manages processes, inputs, and environments using the following interfaces:

| Component | Applied System Calls / Functions | Purpose |
| :--- | :--- | :--- |
| **Process Control** | `fork`, `execve`, `wait`, `waitpid` | Spawning and tracking child processes. |
| **Memory Management** | `malloc`, `free` | Handling dynamic string buffers cleanly. |
| **I/O Operations** | `write`, `getline`, `perror` | Reading prompts, capturing inputs, displaying text. |
| **Environment Check** | `stat`, `isatty` | Validating binary paths and stream status. |

---

## 💻 Compilation and Installation

Compile the source code using the strict flags required for low-level validation:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
