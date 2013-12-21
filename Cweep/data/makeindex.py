from os import listdir
from os.path import isfile, join
from os import getcwd
import string

onlyfiles = sorted([ f for f in listdir(getcwd()) if isfile(join(getcwd(), f)) ])

index = open("index.lst", "w")

for myfile in onlyfiles:
    if( string.find(myfile, "txt") != -1 ):
	tmp = open(myfile, 'r')
	firstline = tmp.readline()
	if( string.find(firstline, "#") != -1 ):
	    print myfile + "\t" + firstline
	    index.write(myfile + "\t" + firstline)
	tmp.close()

index.close()
