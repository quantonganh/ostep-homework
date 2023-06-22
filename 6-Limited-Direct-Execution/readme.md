Direct Execution Protocol:
- Create process entry
- Allocate memory
- Load program into memory
- Locate its entry point (`main()`)

- user mode: a process can't issue I/O requests
- kernel mode: the OS runs in

Cooperative approach:
- Processes transfer control of the CPU to the OS by making system call

Non-cooperative approach:
- OS takes control by using timer interrupt

baby proofing a room: locking cabinets containing the dangerous stuff and covering the electrical sockets.

OS "baby proofs" the CPU:
- setup the trap handler
- start an interrupt timer
- run processes in a restricted mode