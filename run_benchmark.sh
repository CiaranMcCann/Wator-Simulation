
for GRID in  512 2048 4096 8192;
do
	for THREAD in 1 2 4 8;
	do
		python write_global.py $GRID $THREAD
		sh run.sh
	done
done