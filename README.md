Minishell

Minishell is a project from 42 School that consists in building a simplified version of a Unix shell. The goal is to reproduce core behaviors of standard shells such as bash, while understanding process management, redirections, pipes, environment variables, and memory handling at a low level.
🔧 Features :

✅ Built-in Commands Supported

- cd

- echo (with and without -n)

- env

- exit

- export

- pwd

- unset

🧩 Shell Behavior

Execution of commands (built-ins and binaries) with or without absolute/relative paths.

Pipe management (|) between commands.

Redirections:
- Input: <
- Output: >
- Append: >>
- Here-document: << (with signal support inside the here_doc).

Environment variable expansion ($USER, $HOME, etc.).

Signal handling:

- Ctrl + C → interrupt current input.
- Ctrl + \ → ignored.
- Ctrl + D → exits the shell (if input is empty).

    Error management:

    - Unclosed quotes are caught and reported (but don’t cause a crash).
    - Invalid commands or redirections are properly handled.
  

🧠 Architecture

The core of the shell is built around a chained list structure called t_cmd, where each node represents a command block separated by a pipe (|).

Each t_cmd node contains:

- A list of input redirections (t_redir *infile)

- A list of output redirections (t_redir *outfile)

This structure allows:

Unlimited redirections per command

Clean separation of parsing and execution stages

Easier memory management and debugging


⚙️ Memory and Leak Management

Minishell includes tools to ensure leak-free and proper resource management:
.valgrindrc

This configuration file allows you to run valgrind with all the necessary flags to track:

- Memory leaks
- File descriptor (close/open)
- Leaks in child processes
- Proper closure of all allocated resources

To use:

valgrind ./minishell

(assuming the .valgrindrc is in your home directory or properly referenced)
std.supp

A custom suppression file used to filter out:

- Leaks caused by the readline library (known and not fixable)
- Leaks coming from system commands executed via /bin/ls, /bin/echo, etc.

This keeps your valgrind output clean and focused on issues within your codebase, not external libraries.

⚠️ Notes

While certain behaviors are not required by the subject (such as fully managing invalid syntax like unclosed quotes or unfinished pipes), it's still important to avoid crashes and leaks. For example:

- Unclosed quotes should return a proper error message.
- Invalid redirections should be handled gracefully.

Additional features (such as signal handling inside here_doc) are implemented beyond the strict requirements for better user experience and robustness.

🧪 Testing

- Extensive testing with both built-ins and system binaries.
- Comparison with bash behavior for edge cases.
- Memory and file descriptor checks using Valgrind and custom suppression rules.
