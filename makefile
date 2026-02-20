exe = calcul
cc = gcc
arg = -Wall -Wfatal-errors 
src = calcul.c 

all: $(exe)

$(exe):
	$(cc) $(arg) -o $(exe) $(src)