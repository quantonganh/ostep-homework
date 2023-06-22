Time sharing:
- run one process
- stop it
- run another

Space sharing:
- a resource is divided among those who wish to use it (disk space)

Process API:
- create:
	- load its code into memory
	- allocate memory for stack, heap
	- I/O (file descriptor)
	- start the program running at the entry point -> OS transfers control of the CPU to the newly created process
- destroy
- wait
- suspend/resume
- status

