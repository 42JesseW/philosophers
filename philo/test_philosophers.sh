#!/bin/bash

# 	- DEATH during SLEEPING state.
#         - "> ./philo 2 800 400 900"
#   - DEATH while waiting for fork
#         - "> ./philo 2 800 900 750"
#         - "> ./philo 4 310 200 100"
# 	- DEATH during EATING state, can not die.
#         - timeout check if "> ./philo 5 800 200 200"
#         - timeout check if "> ./philo 4 410 200 200"
# 	- {number_of_philosophers} is 1, which means there's only 1 fork
# 	  and the philosopher will always die because it can't lock two forks.
#         - "> ./philo 1 800 200 200" should not start eating and should die
# 	- {number_of_times_each_philosopher_must_eat} is not reached
# 	  by all philosophers at the same time.
#         - "> ./philo 5 800 200 200 7 > eat.out"
#         - make sure all "> grep "{x} is eating" | wc -l" is bigger then 7
#           - "> for (( i=1; i<6; i++ )) do cat eat.out | grep "$i is eating" | wc -l; done"
#         - make sure no philosopher dies
#   - forever eating because everyone gets their fork on time
#         - "> ./philo 5 800 200 200
#   - A death delayed by more than 10 ms is unacceptable
#         - "> ./philo 1 800 400 900"
#         - [0] 1 has taken a fork
#           [0] 1 has taken a fork
#           [0] 1 is eating
#           [402] 1 is sleeping   -> EATING takes 400 ms
#           [1203] 1 died         -> SLEEPING takes 900 ms but after 800 ms the philo dies because {time_to_die} = 800

TIMEOUT=5
SIGSEG=139
SIGTIME=124

R=$(tput setaf 1)
G=$(tput setaf 2)
Y=$(tput setaf 3)

U=$(tput smul)
N=$(tput sgr0)

arg_check_ms="1 800 400 900"
arg_check_eat_times="5 800 200 200 7"

printf "${U}[No death]${N}\n"
ARGS_TIMEOUT=("5 800 200 200"
              "4 410 200 200")
IFS=""
for args in "${ARGS_TIMEOUT[@]}"
do
  printf "%-40s" "${U}[$args]${N}"
  IFS=" "
  timeout $TIMEOUT ./philo $args > out_${args:0:1}
  exit_code="$?"
  if [[ exit_code -eq $SIGSEG ]]; then
    printf "%-20s" "${R}SEGFAULT${N}"
  else
    if [[ exit_code -ne $SIGTIME ]]; then
      printf "%-20s" "${R}PHILO DIED${N}"
    else
      printf "%-20s" "${G}PASSED${N}"
    fi
  fi
  rm out_${args:0:1}
  echo
  IFS=""
done
echo

printf "${U}[Deaths]${N}\n"
ARGS_DEATH=("2 800 400 900"
            "2 800 900 750"
            "4 310 200 100"
            "1 800 200 200")
IFS=""
for args in "${ARGS_DEATH[@]}"
do
  printf "%-40s" "${U}[$args]${N}"
  IFS=" "
  timeout $TIMEOUT ./philo $args > out_${args:0:1}
  exit_code="$?"
  if [[ exit_code -eq $SIGTIME ]]; then
    printf "%-20s" "${R}NO PHILO DIED${N}"
  elif [[ exit_code -eq $SIGSEG ]]; then
    printf "%-20s" "${R}SEGFAULT${N}"
  else
    if [[ $(grep "died" out_${args:0:1} | wc -l | tr -d '[:space:]') -ne 1 ]]; then
      printf "%-20s" "${R}WRITE LOCK${N}"
    else
      printf "%-20s" "${G}PASSED${N}"
    fi
  fi
  rm out_${args:0:1}
  echo
  IFS=""
done
echo
