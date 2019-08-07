#########################################################################################
###### Reads the uncalibrated beam energy for each run in the energyuncalibrated txt file
###### applies the correction factors and creates a new_db_run data file that has the energy corrected
#########################################################################################


#!/usr/bin/python

import matplotlib.pyplot as plt
import numpy as np
import math
#import ROOT as R

dir='db_run.dat'
outdir='new_db_run.dat'

run=[]; energy=[];
dir2='energyuncalibrated.txt'

with open(dir2) as events:
        for line in events:
                data = line.split('  ')
                #print data[1]
                run.append(int(data[0]))
                print(data[1])
                if (float(data[1]) < 93150): 
                        energy.append((1.002*float(data[1]))/1000)
                else:	
                        energy.append((1.0025*float(data[1]))/1000)
#run = np.array(run)
test = 0
print(run)
#R = map(tuple,run)
file=open(outdir,'w')
with open(dir) as events:
        for line in events:
                data = line.split(' ')
                if (len(data))==6:
			#print data[5]
                        r = int(data[5])
                        print(r)
                        if r in run:
                                print('This is: ' + data[5])
                                x = run.index(r)
                                test = 1
                if data[0] == 'ebeam' and test == 1: 		
                        file.write('ebeam = %f \n'  % energy[x])
                        test =0
                else:
                        file.write(line)

file.close()
