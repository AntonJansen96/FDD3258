#!/bin/bash
#SBATCH --job-name=mod2_ex3

#SBATCH --time 02:00:00
#SBATCH --nodes=1
#SBATCH -A edu20.FDD3258

##SBATCH --mail-type=ALL
##SBATCH --mail-user=anton.jansen@scilifelab.se

make -j
srun main
