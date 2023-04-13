#!/bin/bash
#SBATCH --job-name=generate_layout_csv_format    # Job name
#SBATCH --mail-type=END,FAIL          # Mail events (NONE, BEGIN, END, FAIL, ALL)
#SBATCH --mail-user=as8hu@virginia.edu  # Where to send mail	
#SBATCH --ntasks=4                   # Run on a single CPU
#SBATCH --mem=50gb                     # Job memory request
#SBATCH --time=24:00:00               # Time limit hrs:min:sec
#SBATCH --output=%x_%j.log   # Standard output and error log

hostnamectl | grep -i "Static hostname"; 
pwd; date

echo 
echo "--------------> Starting job <-------------- "
echo

source ../.venv/bin/activate
python --version

time python 02_generate_datasets.py

echo 
echo "--------------> Ending job <-------------- "
hostnamectl | grep -i "Static hostname"
date

sleep 10