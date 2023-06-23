Scheduler:
- FIFO (First In First Out)
- SJF (Shortest Job First)
- RR (Round Robin)

```
turnaround = completion - arrival

arrival = 0 -> turnaround = completion
```

```
response = firstrun - arrival
```

```
./scheduler.py -p SJF -l 200,200,200
```

1. Compute the response time and turnaround time when running three jobs of length 200 with the SJF and FIFO schedulers.

```
0: run job 0 for 200 secs (done at 200)
200: run job 1 for 200 secs (done at 400)
400: run job 2 for 200 secs (done at 600)

job 0: response: 0, turnaround: 200, wait: 0
job 1: response: 200, turnaround: 400, wait: 200
job 2: response: 400, turnaround: 600, wait: 200

Average -- response: 200, turnaround: 400, wait: 200
```

```
$ ./scheduler.py -p SJF -l 200,200,200 -c
ARG policy SJF
ARG jlist 200,200,200

Here is the job list, with the run time of each job:
  Job 0 ( length = 200.0 )
  Job 1 ( length = 200.0 )
  Job 2 ( length = 200.0 )


** Solutions **

Execution trace:
  [ time   0 ] Run job 0 for 200.00 secs ( DONE at 200.00 )
  [ time 200 ] Run job 1 for 200.00 secs ( DONE at 400.00 )
  [ time 400 ] Run job 2 for 200.00 secs ( DONE at 600.00 )

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 200.00  Wait 0.00
  Job   1 -- Response: 200.00  Turnaround 400.00  Wait 200.00
  Job   2 -- Response: 400.00  Turnaround 600.00  Wait 400.00

  Average -- Response: 200.00  Turnaround 400.00  Wait 200.00
```

2. Now do the same but with jobs of different lengths: 100, 200, and 300.

```
0: run job 0 for 100 (done at 100)
100: run job 1 for 200 (done at 300)
300: run job 2 for 300 (done at 600)

job 0 -- response: 0, turnaround: 100, wait: 0
job 1 -- response: 100, turnaround: 300, wait: 100
job 2 -- response: 300, turnaround: 600, wait: 300

Average -- response: 133, Turnaround: 333, wait: 133
```

```
$ ./scheduler.py -p FIFO -l 100,200,300 -c
ARG policy FIFO
ARG jlist 100,200,300

Here is the job list, with the run time of each job:
  Job 0 ( length = 100.0 )
  Job 1 ( length = 200.0 )
  Job 2 ( length = 300.0 )


** Solutions **

Execution trace:
  [ time   0 ] Run job 0 for 100.00 secs ( DONE at 100.00 )
  [ time 100 ] Run job 1 for 200.00 secs ( DONE at 300.00 )
  [ time 300 ] Run job 2 for 300.00 secs ( DONE at 600.00 )

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 100.00  Wait 0.00
  Job   1 -- Response: 100.00  Turnaround 300.00  Wait 100.00
  Job   2 -- Response: 300.00  Turnaround 600.00  Wait 300.00

  Average -- Response: 133.33  Turnaround 333.33  Wait 133.33
```