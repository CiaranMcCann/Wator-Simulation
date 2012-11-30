
for GRID in  16 128 512 2048 4096;
do
	for THREAD in 1 2 4 8;
	do
		python write_global.py $GRID $THREAD
		sh run.sh
	done
done