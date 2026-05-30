1. Run the program with the following flags: ./process-run.py-l 5:100,5:100. What should the CPU utilization be (e.g., the percent of time the CPU is in use?) Why do you know this? Use the -c and -p plags to see if you were right.

The cpu time should be 100%, i know this because there are not I/O operations.

result:
```
Time    PID: 0    PID: 1       CPU       IOs
  1    RUN:cpu     READY         1          
  2    RUN:cpu     READY         1          
  3    RUN:cpu     READY         1          
  4    RUN:cpu     READY         1          
  5    RUN:cpu     READY         1          
  6       DONE   RUN:cpu         1          
  7       DONE   RUN:cpu         1          
  8       DONE   RUN:cpu         1          
  9       DONE   RUN:cpu         1          
 10       DONE   RUN:cpu         1          

Stats: Total Time 10
Stats: CPU Busy 10 (100.00%)
Stats: IO Busy  0 (0.00%)

```

2. Now run with these flags: ./process-run.py-l 4:100,1:0.
These flags specify one process with 4 instructions (all to use the
CPU), and onet that simply issues an I/O and waits for it to be done.
How long does it take to complete both processes? Use-c and-p
to find out if you were right.

6 clock ticks. 4 cpu instructions for the first, process, 1 clock tick for one i/o instruction of the second process and another to finish the second process.

```

Time    PID: 0    PID: 1       CPU       IOs
  1    RUN:cpu     READY         1          
  2    RUN:cpu     READY         1          
  3    RUN:cpu     READY         1          
  4    RUN:cpu     READY         1          
  5       DONE    RUN:io         1          
  6       DONE   WAITING                   1
  7       DONE   WAITING                   1
  8       DONE   WAITING                   1
  9       DONE   WAITING                   1
 10*      DONE      DONE         1

Stats: Total Time 10
Stats: CPU Busy 6 (60.00%)
Stats: IO Busy  4 (40.00%)
````
my idea was correct, but not the result, i was expecting the io operation to take just 1 time.

3. Now switch the order of the processes: ./process-run.py -l
1:0,4:100. What happens now? Does switching the order matter? Why? (As always, use-c and-p to see if you were right)

No, because the scheduler will chose any process randomly.

result:
```
python process-run.py -l 1:0,4:100 -c -p 
Time    PID: 0    PID: 1       CPU       IOs
  1     RUN:io     READY         1          
  2    WAITING   RUN:cpu         1         1
  3    WAITING   RUN:cpu         1         1
  4    WAITING   RUN:cpu         1         1
  5    WAITING   RUN:cpu         1         1
  6*      DONE      DONE         1

Stats: Total Time 6
Stats: CPU Busy 6 (100.00%)
Stats: IO Busy  4 (66.67%)
```

i was wrong, i didn't take into consideration the schedulers policy. which will only switch on an IO operation, if the the former process were to be place first the scheduler would have execute all its instructions and then move on the 4:0 process. But in this case because the 4:0 process was placed first, it inmediately hit an I/O instruction, and while this process was waiting for the I/O instruction to be completed the 5:100 process was running.

4. We’ll now explore some of the other flags. One important flag is-S,
which determines how the system reacts when a process issues an
I/O. With the flag set to SWITCH ON END, the system will NOT switch to another process while one is doing I/O, instead waiting until the process is completely finished.

What happens when you run the following two processes, one doing I/O and the other doing
CPU work? (-l 1:0,4:100 -c -S SWITCH
ON END)

Then here it would take a total of 10 seconds. as the 4:100 process won't be executing while 1:0 is waiting. CPU utilization will also be lower.

result:
```
Time    PID: 0    PID: 1       CPU       IOs
  1     RUN:io     READY         1          
  2    WAITING     READY                   1
  3    WAITING     READY                   1
  4    WAITING     READY                   1
  5    WAITING     READY                   1
  6*      DONE   RUN:cpu         1          
  7       DONE   RUN:cpu         1          
  8       DONE   RUN:cpu         1          
  9       DONE   RUN:cpu         1          

Stats: Total Time 9
Stats: CPU Busy 5 (55.56%)
Stats: IO Busy  4 (44.44%)
```

5. Now, run the same processes, but with the switching behavior set to switch to another process whenever one is WAITING for I/O(-l
1:0,4:100-c -S SWITCH_ON_IO). What happens now? Use -c and -p to confirm that you are right.

6 clock times, 1 to start the 1:0 process and then in the other 4 clicks the i/o will completed. and at click 5, both process will have ended.

result:
```
Time    PID: 0    PID: 1       CPU       IOs
  1     RUN:io     READY         1          
  2    WAITING   RUN:cpu         1         1
  3    WAITING   RUN:cpu         1         1
  4    WAITING   RUN:cpu         1         1
  5    WAITING   RUN:cpu         1         1
  6*      DONE      DONE         1

Stats: Total Time 6
Stats: CPU Busy 6 (100.00%)
Stats: IO Busy  4 (66.67%)

```

6. One other important behavior is what tod o when an I/O completes. With -I IO_RUN_LATER, when an I/O completes, the process that issued it is not necessarily run right awy; rather; whatever was running at the time keeps running. What ahppens when you run this combination of procsses? .process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_LATER -c -p

the first process 3:0 will start i/o, while it's waiting for its I/O response, 5:100 will run and finish, then 5:100 will run and finish, then 5:100 will run and finish. then the scheduler will get back to 3:0, because the policy is IO_RUN_LATER - the first process will run when it's its turn no when the I/O inmediately finishes. Finally the 3:0 process do two more I/O operations.

7. Now run the same processes, but with -I IO
RUN_IMMEDIATE set, which immediately runs the process that issued the I/O. How does
this behavior differ? Why might running a process that just completed an I/O again be a good idea?

result:
```
Time    PID: 0    PID: 1    PID: 2    PID: 3       CPU       IOs
  1     RUN:io     READY     READY     READY         1          
  2    WAITING   RUN:cpu     READY     READY         1         1
  3    WAITING   RUN:cpu     READY     READY         1         1
  4    WAITING   RUN:cpu     READY     READY         1         1
  5    WAITING   RUN:cpu     READY     READY         1         1
  6*    RUN:io     READY     READY     READY         1          
  7    WAITING   RUN:cpu     READY     READY         1         1
  8    WAITING      DONE   RUN:cpu     READY         1         1
  9    WAITING      DONE   RUN:cpu     READY         1         1
 10    WAITING      DONE   RUN:cpu     READY         1         1
 11*    RUN:io      DONE     READY     READY         1          
 12    WAITING      DONE   RUN:cpu     READY         1         1
 13    WAITING      DONE   RUN:cpu     READY         1         1
 14    WAITING      DONE      DONE   RUN:cpu         1         1
 15    WAITING      DONE      DONE   RUN:cpu         1         1
 16*      DONE      DONE      DONE   RUN:cpu         1          
 17       DONE      DONE      DONE   RUN:cpu         1          
 18       DONE      DONE      DONE   RUN:cpu         1          

Stats: Total Time 18
Stats: CPU Busy 18 (100.00%)
Stats: IO Busy  12 (66.67%)

```

It seems as a good idea, because as in if this case, if the process have multiple I/O operations, they can be triggered inmediately and the process will get back to a waiting state, while the scheduler executes the other active processes. Minimizing the execution time in some times.

8. Now run with some randomly generated processes, e.g.,-s 1 -l 3:50,3:50,-s 2 -l 3:50,3:50, -s 3 -l 3:50,3:50. See if you can predict how the trace will turn out. What happens when you use -I IO_RUN_IMMEDIATE vs. -I IO_RUN_LATER pens when you use -S SWITCH_ON_IO? What happens IO vs.-S SWITCH_ON_END?

On IO_RUN_INMEDIATE, as soon as one I/O is done the waiting process is run. and with -S SWITCH_ON_END and entire process needs to be done, before following with the next one.
