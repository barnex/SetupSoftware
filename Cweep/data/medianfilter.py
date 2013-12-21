import csv
import sys
import numpy as np

if( len(sys.argv) == 1 ):
    print "Please specify input file"
else:
    f = []
    noise = []
    mainPeak = []
    leftPeak = []
    rightPeak = []
    with open(sys.argv[1], 'rb') as csvfile:
	filereader = csv.reader(csvfile, delimiter='\t')
	for row in filereader:
	    try:
		f.append(float(row[0]))
		noise.append(float(row[1]))
		mainPeak.append(float(row[3]))
		leftPeak.append(float(row[5]))
		rightPeak.append(float(row[7]))
	    except:
		pass

    noise = np.array(noise)
    mainPeak = np.array(mainPeak)
    leftPeak = np.array(leftPeak)
    rightPeak = np.array(rightPeak)
    filename = "".join([sys.argv[1], ".filtered"])
    fileout = open(filename, 'w')
    for i in range(1, len(f)-1):
	noiseFiltered = np.median( noise[i-1:i+2] )
	mainPeakFiltered = np.median( mainPeak[i-1:i+2] )
	leftPeakFiltered = np.median( leftPeak[i-1:i+2] )
	rightPeakFiltered = np.median( rightPeak[i-1:i+2] )
	outstr = str(f[i]) + '\t' + str(noiseFiltered) + '\t' +\
	    str(mainPeakFiltered) + '\t' +\
	    str(leftPeakFiltered) + '\t' +\
	    str(rightPeakFiltered) + '\n'
	fileout.write(outstr)
    fileout.close()

