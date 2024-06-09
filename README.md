![Dining Philosophers](https://res.cloudinary.com/practicaldev/image/fetch/s--UJiIzrz5--/c_imagga_scale,f_auto,fl_progressive,h_900,q_auto,w_1600/https://dev-to-uploads.s3.amazonaws.com/i/4mrdvbtfbv2ma2avpp8i.png)

# Dining Philosophers Problem

 The Philosophers Problem is a famous problem in computer science used to illustrate common problems in concurrent programming. It simulates a scenario in which a number of philosophers sit at a round table and eat, sleep and think respectively.

## Rules

- Philosophers can be in one of three states: eating, thinking, or sleeping.
- Philosophers must eat with two forks, one for each hand.
- Philosophers must never be starving, and every philosopher needs to eat.
- Philosophers don't speak with each other and don't know when another philosopher is about to die.
- The simulation stops when a philosopher dies.

## Program Arguments

Each program must have the following options:

- `number_of_philosophers`: The number of philosophers is also the number of forks.
- `time_to_die`: Time in milliseconds. If a philosopher does not start eating within `time_to_die` milliseconds after starting his last meal or after the start of the simulation, he dies.
- 'time_to_eat': Time in milliseconds. The time it takes for a philosopher to eat.
- `time_to_sleep`: Time in milliseconds. The time it takes for a philosopher to sleep.
- `[number_of_times_each_philosopher_must_eat]` (optional): If specified, the simulation will stop after all philosophers have eaten at least this many times. If not specified, the simulation will only stop on the death of a philosopher.

## Things to Know About the Project

### Mutex
A mutex is a synchronization policy used in concurrent programming to prevent multiple threads from simultaneously accessing shared resources (e.g. variables or data structures) that can lead to race conditions. In this project, mutexes are used to ensure that only one philosopher can access a fork at a time and to avoid conflicts.

### Threads
A thread is a unit of execution within a process. Unlike processes, which have their own memory space, threads share the same memory space and resources with their parent process. This makes threads lighter than processes and allows them to communicate more efficiently. In this project, multiple threads are used to simulate philosophers.

#### The Difference Between Threads and Processes
#### Threads:
Share the same memory space.
Lighter than processes.
Faster to create and manage.
They have less overhead for communication between them.

#### Processes:
Have their own memory space.
They are heavier and more resource intensive.
They have more overhead for communication between them.

#### Data Race
A data race occurs in concurrent programming when two or more threads or processes simultaneously access a shared resource (such as a variable) and at least one of them writes to it. This can lead to unpredictable behavior and errors. The use of mutexes in this project helps prevent data races by providing exclusive access to shared resources such as forks.

## Usage

### Clone the project
```
git clone https://github.com/whymami/philosophers.git
```
### Compile the program
```
cd philosophers
cd philo
make
```
### Run the program
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
