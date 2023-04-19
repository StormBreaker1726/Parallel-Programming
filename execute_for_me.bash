#!/bin/bash

mpicc -o mpi_trap_heterogeneo_ciclico mpi_trap_heterogeneo_ciclico.c

clear

echo "Serial"

mpiexec -n 1 mpi_trap_heterogeneo_ciclico && mpiexec -n 1 mpi_trap_heterogeneo_ciclico && mpiexec -n 1 mpi_trap_heterogeneo_ciclico


echo "Processos = 2"

mpiexec -n 2 mpi_trap_heterogeneo_ciclico && mpiexec -n 2 mpi_trap_heterogeneo_ciclico && mpiexec -n 2 mpi_trap_heterogeneo_ciclico


echo "Processos = 4"

mpiexec -n 4 mpi_trap_heterogeneo_ciclico && mpiexec -n 4 mpi_trap_heterogeneo_ciclico && mpiexec -n 4 mpi_trap_heterogeneo_ciclico


echo "Processos = 8"

mpiexec -n 8 mpi_trap_heterogeneo_ciclico && mpiexec -n 8 mpi_trap_heterogeneo_ciclico && mpiexec -n 8 mpi_trap_heterogeneo_ciclico


echo "Processos = 16"

mpiexec --use-hwthread-cpus -n 16 mpi_trap_heterogeneo_ciclico && mpiexec --use-hwthread-cpus -n 16 mpi_trap_heterogeneo_ciclico && mpiexec --use-hwthread-cpus -n 16 mpi_trap_heterogeneo_ciclico
