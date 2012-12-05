
for GRID in 8192;
do
	for THREAD in 1;
	do
		python write_global.py $GRID $THREAD
		sh run.sh
	done
done