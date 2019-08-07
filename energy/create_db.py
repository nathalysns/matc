##############################################################
#### Read the DB file and finds what runs are missing 
#### Read  the Start of Run files and finds the parameters to cread the DB information
##### creates a temp file with the information needed to put in the DB run file for the missing run numbers
##############################################################


#!/usr/bin/python

import matplotlib.pyplot as plt
import numpy as np
import math
#import ROOT as R

dir='db_run.dat'
outdir='temp.dat'

run=[]; energy=[];
dir2='energyuncalibrated.txt'

with open(dir2) as events:
        for line in events:
                data = line.split('  ')
                run.append(int(data[0]))
                if (float(data[1]) < 93150): 
                        energy.append((1.002*float(data[1]))/1000)
                else:	
                        energy.append((1.0025*float(data[1]))/1000)
#run = np.array(run)
test = 0
rundb=[];

file=open(outdir,'w')
with open(dir) as events:
        for line in events:
                data = line.split(' ')
                if (len(data))==6:
                        r = int(data[5])
                        rundb.append(int(r))
file.close()

#print(rundb)

i=0
runnotdb=[]
runindb=[]
while i < len(run):
        if run[i] in rundb:
                runindb.append(run[i])
        else:
                runnotdb.append(run[i])
                #print( str(run[i]) + 'is not in the db_run') 
        i=i+1

file=open(outdir,'w')

print(runnotdb)

j=0
while j < len(runnotdb):
        print(runnotdb[j])
	ln = 0
        with open('/work/halla/triton/nathaly/epics/Start_of_Run_'+str(runnotdb[j])+'.epics') as events:
                for line in events:
                        if ln ==0:
                                data=line.split('Dec ')
                                file.write('--------[ 2017-12-' + data[1]) 
                                ln=1
	
        mom = '0'
        angle = '0'
        ener = '0' 
        with open('/work/halla/triton/nathaly/epics/End_of_Run_'+str(runnotdb[j])+'.epics') as events:
                for line in events:
                        data=line.split(' : ')
                        if data[0] == 'Tiefenbach 6GeV Beam energy (MeV)':
                                ener = float(data[1])/1000
                        if data[0] == 'Left arm angle':    
                                angle = data[1]
                        if data[0] == 'Left arm momentum':    
                                mom = data[1]	
        file.write('# parameters from EPICS run ' + str(runnotdb[j]) + '\n')
        file.write('ebeam = ' + str(ener) + '\n')
        file.write('L.theta = ' + angle)
        file.write('L.pcentral = ' + mom)
        file.write('FbusL.theta = ' + angle)
        file.write('FbusL.pcentral = ' + mom)
        file.write('OldTrackL.theta = ' + angle)
        file.write('OldTrackL.pcentral = ' + mom)
        file.write(' \n ')
        j=j+1
