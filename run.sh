# Just makes continually cleaning, building and running the project simpler.
# To use this:
# On first run type "chmod 755 run.sh" into the shell, to give the file permissions.
# Thereafter just type "./run.sh" into the shell.

make clean
make
./Wator
cat Performance_data.log