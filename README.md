# Philosophers – Projet 42

[![English](https://img.shields.io/badge/English-blue.svg)](./READMEen.md)   [![Français](https://img.shields.io/badge/Français-gray.svg)](./README.md)

Ce projet explore les problématiques de **synchronisation de threads**, de **mutex**, et de **conditions de concurrence** à travers une implémentation du **problème des philosophes**.

<br>

## 🧠 Description du projet

Le projet **Philosophers** a pour but de simuler une table avec plusieurs philosophes qui alternent entre **penser**, **manger**, et **dormir**, tout en partageant un nombre limité de ressources : les fourchettes.

Ce projet aborde des concepts importants comme :
- la **programmation multithread** avec `pthread`
- l'utilisation correcte des **mutex** pour éviter les conditions de course
- la gestion fine des **délais (usleep, gettimeofday)** pour coller à une simulation temps réel

L'objectif est d’éviter :
- les **conditions de famine** (qu’un philosophe meure de faim)
- les **deadlocks** (blocages mutuels entre threads)
- les **race conditions** (accès concurrent à des ressources partagées)

<br>

## 🔧 Comment exécuter le projet

### 1. Cloner le repository

```bash
git clone https://github.com/matthieugillieron/philosophers.git
cd philosophers
```

### 2. Compiler le projet

```bash
make
```

### 3. Lancer l'exécutable

```bash
./philo <nbr_philo> <time_to_die> <time_to_eat> <time_to_sleep> [optional: must_eat]
```

Par exemple :

```bash
./philo 5 800 200 200
```

Cela démarre une simulation avec 5 philosophes, chacun ayant :
- 800ms avant de mourir s’il ne mange pas
- 200ms pour manger
- 200ms pour dormir

Ajoutez un 5ème paramètre (ex: `5`) pour forcer l'arrêt une fois que chaque philosophe a mangé 5 fois.
