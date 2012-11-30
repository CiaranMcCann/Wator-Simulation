import sys

GRID_SIZE = sys.argv[1]
THREADS = sys.argv[2]
NSHARKS = GRID_SIZE
NFISH = str(int(GRID_SIZE)*10)


f = open('/home/lab422/dev/Wator-Simulation/Globals.h','r')
fwrite = open('/home/lab422/dev/Wator-Simulation/Globals.h','w')

fwrite.write(str('#ifndef GLOBALS_H')+'\n')
fwrite.write(str('#define GLOBALS_H')+'\n'+'\n')

fwrite.write(str('float const WindowHeight = 800.0f;')+'\n')
fwrite.write(str('float const WindowWidth = 800.0f;')+'\n'+'\n')	

fwrite.write(str('int numThreads = ')+ THREADS+';\n'+'\n');	

fwrite.write(str('#define NUMBER_OF_RUNS 10')+'\n')		

fwrite.write(str('#define GRID_ROWS ')+ GRID_SIZE +'\n')		
fwrite.write(str('#define GRID_COLUMNS ')+ GRID_SIZE+'\n')
fwrite.write(str('#define CYCLES_PER_FRAME 1')+'\n'+'\n')

fwrite.write(str('#define N_SHARKS ')+NSHARKS +'\n')
fwrite.write(str('#define N_FISH ')+ NFISH +'\n')
fwrite.write(str('#define FISH_SPAWNRATE 3')+'\n')
fwrite.write(str('#define SHARK_SPAWNRATE 7')+'\n')
fwrite.write(str('#define SHARK_STARVERATE 6')+'\n'+'\n')
fwrite.write(str('#define SIMULATION_LENGTH 20')+'\n'+'\n')	

fwrite.write(str('#define DRAW_GRID 0')+'\n'+'\n')


fwrite.write(str('#endif'))

	
f.close()
fwrite.close()


