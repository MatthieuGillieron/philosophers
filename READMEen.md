# Philosophers – Project 42 - English

[![English](https://img.shields.io/badge/English-blue.svg)](./READMEen.md)   [![Français](https://img.shields.io/badge/Français-gray.svg)](./README.md)

This project explores the challenges of **thread synchronization**, **mutexes**, and **concurrency issues** through an implementation of the **Dining Philosophers problem**.

<br>

## 🧠 Project Description

The **Philosophers** project simulates a table of philosophers who alternate between **thinking**, **eating**, and **sleeping**, while sharing a limited number of resources: forks.

This project covers important concepts such as:
- **Multithreaded programming** with `pthread`
- Proper use of **mutexes** to avoid race conditions
- Fine-grained timing control (`usleep`, `gettimeofday`) to achieve a real-time simulation

The goal is to prevent:
- **Starvation** (a philosopher dying of hunger)
- **Deadlocks** (threads blocking each other)
- **Race conditions** (concurrent access to shared resources)

<br>

## 🔧 How to Run the Project

### 1. Clone the repository

```bash
git clone https://github.com/matthieugillieron/philosophers.git
cd philosophers
```

### 2. Compile the project

```bash
make
```

### 3. Run the executable

```bash
./philo <nbr_philo> <time_to_die> <time_to_eat> <time_to_sleep> [optional: must_eat]
```

For example:

```bash
./philo 5 800 200 200
```

This starts a simulation with 5 philosophers, each having:
- 800 ms before dying if they don’t eat
- 200 ms to eat
- 200 ms to sleep

Add a fifth parameter (e.g., `5`) to stop the simulation once each philosopher has eaten 5 times.
