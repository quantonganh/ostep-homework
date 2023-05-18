1. Write a program that calls `fork()`. Before calling `fork()`, have the main process access a variable (e.g., `x`) and set its value to some- thing (e.g., `100`). What value is the variable in the child process? What happens to the variable when both the child and parent change the value of `x`?

Each process has its own separate copy of `x`:

```
$ ./variable-in-child
Parent process - x: 99
Child process - x: 101
```

2. Write a program that opens a file (with the `open()` system call) and then calls `fork()` to create a new process. Can both the child and parent access the file descriptor returned by `open()`? What happens when they are writing to the file concurrently, i.e., at the same time?

Yes, both the child and parent can access the file descriptor returned by `open()`.  However, concurrent writes from the parent and child processes can lead to the interleaved data in the file:

```
$ ./access-file-descriptor
writing from the parent
writing from the child

$ cat /tmp/file
from parent
from child
```

To ensure that the writes are cooperated and not interleaved:
- synchronization mechanism (locks)
- IPC (inter-process communication)

3. Write another program using `fork()`. The child process should print “hello”; the parent process should print “goodbye”. You should try to ensure that the child process always prints first; can you do this without calling `wait()` in the parent?

To ensure that the child process always prints first, we can leverage the synchronization of pipe communication between the parent and child processes:

child process:
- print "hello"
- send a signal to the parent process

parent process:
- wait to receive the signal
- print "goodbye"

```
$ ./ensure-child-first
hello
goodbye
```

4. Write a program that calls `fork()` and then calls some form of `exec()` to run the program `/bin/ls`. See if you can try all of the variants of `exec()`, including (on Linux) `execl()`, `execle()`, `execlp()`, `execv()`, `execvp()`, and `execvpe()`. Why do you think there are so many variants of the same basic call?

- `execv`: takes the program name and command-line arguments as an array of pointers
- `execvp`: searches for the program name in the `PATH` env
- `execl`: takes the program name and command-line arguments as separate parameters

5. Now write a program that uses `wait()` to wait for the child process to finish in the parent. What does `wait()` return? What happens if you use `wait()` in the child?

```
$ ./wait-in-child
Child process: my pid is 43702
wait() failed in child process: No child processes
error code: 10
Child process terminated with status: 1
```

```
$ awk '$3 == 10 { print }' (xcrun --show-sdk-path)/usr/include/sys/errno.h
#define ECHILD          10              /* No child processes */
```

6. Write a slight modification of the previous program, this time using `waitpid()`instead of `wait()`. When would `waitpid()` be useful?

```
$ ./waitpid
child process is still running at Fri Jun 23 11:01:02 2023
child process is still running at Fri Jun 23 11:01:03 2023
child process is still running at Fri Jun 23 11:01:04 2023
child process is still running at Fri Jun 23 11:01:05 2023
child process is still running at Fri Jun 23 11:01:06 2023
child process finished.
```

7. Write a program that creates a child process, and then in the child closes standard output (`STDOUT FILENO`). What happens if the child calls `printf()` to print some output after closing the descriptor?

The output will not be visible in the terminal:

```
$ ./print-after-closing-stdout
Child process: before closing STDOUT_FILENO
Parent process: child process completed
```

8. Write a program that creates two children, and connects the standard output of one to the standard input of the other, using the `pipe()` system call.

first process:
- redirect stdout to the write end of the pipe
- run `ls -l`

second process:
- redirect the stdin to the read end of the pipe
- run `wc -l`