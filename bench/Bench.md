# Benchmark
I record it as a reference value for improving the compiler. 

## Hardware
Intel Icore5 2.9GHz Memroy 8GB

## OS
WSL on Windows10 Ubuntu

## derive
?- ['bench/derive.o'].
yes
?- measure(test).
Elapsed Time=0.029811 (second)  1744395(LIPS)
no
?- 

# devide10
?- ['bench/devide10.o'].
yes
?- measure(test).
Elapsed Time=0.013030 (second)  1688558(LIPS)
no
?- 

## nreverse
?- ['bench/nreverse.o'].
yes
?- measure(test).
Elapsed Time=0.162602 (second)  3068856(LIPS)
no
?- 

## qsort
no
?- ['bench/qsort.o'].
yes
?- measure(test).
Elapsed Time=0.199829 (second)  3022593(LIPS)
no
?- 

## queens
?- ['tests/queens.o'].
yes
?- measure(test16).
Elapsed Time=0.350892 (second)  6835936(LIPS)
no