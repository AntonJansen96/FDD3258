#!/bin/bash
#SBATCH --job-name=mod3_ex2_anton

#SBATCH --time 10:00:00
#SBATCH --nodes=2
#SBATCH -A edu20.FDD3258

#SBATCH --mail-type=ALL
#SBATCH --mail-user=anton.jansen@scilifelab.se

make -j

for opmode in 1 2 3 4 5; do 
    for node in 8 16 32 64 128; do
        echo "processes = $node and opmode = $opmode"
        time srun -n $node ./main $opmode
    done
done
