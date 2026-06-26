*This project has been created as part of the 42 curriculum by adchebbi.*

# Philosophers

## Description

Philosophers is a 42 project about **multithreading** and **synchronization**. It implements
the classic *dining philosophers* problem.

One or more philosophers sit around a round table with a large bowl of spaghetti in the middle.
Each philosopher repeatedly **eats**, **sleeps** and **thinks**. There are as many **forks** as
philosophers, placed **between** each pair of neighbours, and a philosopher needs **two forks**
(the one on their left and the one on their right) to eat. Two neighbours can therefore never
eat at the same time, since they share a fork.

Philosophers do not talk to each other and do not know what the others are doing. A philosopher
who does not start eating in time **dies of starvation**. The goal of the program is to
**keep every philosopher alive** for as long as the timing values allow, and to report a death
immediately if one happens.

The simulation is built with the constraints of the subject in mind:

- each philosopher is a separate **thread**;
- each fork is protected by its own **mutex**;
- a dedicated **monitor** detects starvation;
- there are **no global variables**, no data races and no memory leaks.

## Instructions

### Build

```bash
make        # builds the "philo" executable
make clean  # removes the object files
make fclean # removes the object files and the executable
make re     # rebuilds everything from scratch
```

The project is compiled with `cc -Wall -Wextra -Werror -pthread`.

### Run

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

| Argument | Meaning |
|---|---|
| `number_of_philosophers` | Number of philosophers (and of forks). Must be between 1 and 200. |
| `time_to_die` (ms) | If a philosopher does not start eating within this delay since the start of their last meal (or since the start of the simulation), they die. |
| `time_to_eat` (ms) | Time a philosopher spends eating, holding both forks. |
| `time_to_sleep` (ms) | Time a philosopher spends sleeping. |
| `[number_of_times_each_philosopher_must_eat]` | Optional. When every philosopher has eaten at least this many times, the simulation stops. Otherwise it stops when a philosopher dies. |

### Examples

```bash
./philo 5 800 200 200        # 5 philosophers; runs until someone dies
./philo 5 800 200 200 7      # stops once every philosopher has eaten 7 times
./philo 1 800 200 200        # a single philosopher cannot eat and dies
./philo 4 410 200 200        # nobody should die with these values
```

### Output format

Every state change is printed as `timestamp_in_ms  philosopher_id  action`:

```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
810 3 died
```

State messages never overlap (they are protected by a mutex), and a death is announced **less
than 10 ms** after it actually happens.

## Project structure

```
rew_philo/
├── Makefile
├── README.md
├── test.sh
├── includes/
│   └── philo.h              # t_philo / t_table structures + prototypes
└── src/
    ├── main.c               # entry point: init, launch, monitor, cleanup
    ├── parsing/
    │   └── parse.c          # argument validation and parsing
    ├── init/
    │   ├── init.c           # allocation, mutex init, thread creation
    │   └── cleanup.c        # join threads, destroy mutexes, free memory
    ├── simulation/
    │   ├── routine.c        # a philosopher's life (eat / sleep / think)
    │   ├── forks.c          # taking and releasing forks (deadlock-free order)
    │   └── monitor.c        # death detection and meal counting
    └── utils/
        ├── time.c           # millisecond timestamps and precise sleep
        ├── state.c          # protected read/write of the stop flag
        └── log.c            # protected printing of states and deaths
```

## Technical choices

- **One thread per philosopher, one mutex per fork.** Taking a fork means locking its mutex,
  releasing it means unlocking it, so a fork is never held by two philosophers at once.
- **Deadlock prevention.** If every philosopher grabbed their left fork at the same time, each
  would wait forever for the right one. To break this circular wait, the locking order depends on
  parity: **even** philosophers take their **right** fork first, **odd** philosophers take their
  **left** fork first. Two neighbours then compete for the same fork first, so the loser holds
  nothing and the waiting cycle can never form.
- **Independent monitor.** A busy philosopher cannot watch itself, so a separate monitor scans
  every philosopher every 0.5 ms and compares `now - last_meal` to `time_to_die`. This frequency
  guarantees a death is reported in well under 10 ms.
- **Protected shared data.** Mutexes guard the forks, the printing, the stop flag, and each
  philosopher's meal data (last-meal timestamp and meal count) which is written by the
  philosopher and read by the monitor.
- **Precise sleep.** `precise_sleep` sleeps in small steps while checking the real clock and the
  stop flag, instead of a single imprecise `usleep`.
- **Single philosopher.** With only one philosopher both forks are the same one, so this case is
  handled separately to avoid locking the same mutex twice; the philosopher dies as expected.
- **Robust shutdown.** `launched_count` records how many threads were actually created, so on a
  failed `pthread_create` only the existing threads are joined before mutexes are destroyed and
  memory is freed.

## Resources

Classic references about the topic:

- E. W. Dijkstra, *Hierarchical ordering of sequential processes* (the original dining
  philosophers problem).
- *The Dining Philosophers Problem* — Wikipedia: https://en.wikipedia.org/wiki/Dining_philosophers_problem
- POSIX threads manual pages: `man pthread_create`, `man pthread_mutex_init`,
  `man pthread_mutex_lock`, `man pthread_join`, `man gettimeofday`, `man usleep`.
- *POSIX Threads Programming* — LLNL tutorial:
  https://hpc-tutorials.llnl.gov/posix/

### Use of AI

An AI assistant (Claude) was used as a **learning and pair-programming tool** while building this
project. Specifically, it was used to:

- **understand the concepts**: threads, mutexes, data races, deadlocks, and the dining
  philosophers problem itself;
- **design the architecture**: the thread-per-philosopher / mutex-per-fork model, the separate
  monitor, and the split of the code into `parsing`, `init`, `simulation` and `utils`;
- **reason about correctness**: the deadlock-free fork-locking order, the protection of the
  shared meal data, and the single-philosopher edge case;
- **write and review the C code**, and **interpret the results** of `valgrind` (memory leaks)
  and `valgrind --tool=helgrind` (data races).

Every function and every design decision was explained, reviewed and understood by me before
being kept, so that the whole project can be defended line by line.
