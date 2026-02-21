*This project has been created as part of the 42 curriculum by mgumienn.*

# Philosophers

## Description

The **Philosophers** project is part of the 42 School Common Core curriculum. The goal of this project is to learn the basics of threading a process, how to create threads, and how to discover mutexes. It is based on the classic Dining 
Philosophers problem.  

One or more philosophers sit at a round table. There is a large bowl of spaghetti in the middle of the table. The philosophers alternatively eat, think, or sleep.
- While they are eating, they are not thinking nor sleeping.
- While thinking, they are not eating nor sleeping.
- And, of course, while sleeping, they are not eating nor thinking.

There are also forks on the table. There are as many forks as philosophers. Because serving and eating spaghetti with only one fork is very inconvenient, a philosopher takes their right and their left forks to eat, one in each hand.
When a philosopher has finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking again. The simulation stops when a philosopher dies of starvation.

Every philosopher needs to eat and should never starve. Philosophers don't speak with each other and don't know if another philosopher is about to die.

### Technical Requirements (Mandatory Part)

- The project must be written in **C**.
- The code must comply with the **42 Norm**.
- No memory leaks, no crashes, and **no data races** are tolerated.
- Global variables are forbidden.
- Each philosopher should be a **thread** (`pthread`).
- There is one fork between each pair of philosophers. Therefore, if there are several philosophers, each philosopher has a fork on their left side and a fork on their right side. If there is only one philosopher, there should be only one fork on the table.
- To prevent philosophers from duplicating forks, you should protect the forks state with a **mutex** (`pthread_mutex`) for each of them.
- The `Makefile` must compile the source files without relinking and must c ontain the rules: `NAME`, `all`, `clean`, `fclean`, and `re`.

## Instructions

To compile the project, navigate to the `philo` directory and run `make`:

```bash
cd philo
make
```

Run the program with the following arguments:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Arguments:

1. `number_of_philosophers`: The number of philosophers and also the number of forks.
2. `time_to_die` (in milliseconds): If a philosopher didn't start eating `time_to_die` milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
3. `time_to_eat` (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
4. `time_to_sleep` (in milliseconds): The time a philosopher will spend sleeping.
5. `number_of_times_each_philosopher_must_eat` (optional argument): If all philosophers have eaten at least `number_of_times_each_philosopher_must_eat` times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

### Log Format

Any state change of a philosopher must be formatted as follows:

- `timestamp_in_ms X has taken a fork`
- `timestamp_in_ms X is eating`
- `timestamp_in_ms X is sleeping`
- `timestamp_in_ms X is thinking`
- `timestamp_in_ms X died`

*(Where `timestamp_in_ms` is the current timestamp in milliseconds and `X` is the philosopher number from 1 to `number_of_philosophers`)*.

- A displayed state message should not be mixed up with another message.
- A message announcing a philosopher died should be displayed no more than 10 ms after the actual death of the philosopher.

## Resources

- [Dining philosophers problem - Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [Mutexes in C](https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/)

### AI Usage
AI was used to show examaple usage of functions included in pthread.
