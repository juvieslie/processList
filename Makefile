#MakeFile to build and deploy the Sample US CENSUS Name Data using ajax
# For CSC3004 Software Development

# Put your user name below:
USER= riveraj

CC= g++

#For Optimization
#CFLAGS= -O2
#For debugging
CFLAGS= -g

RM= /bin/rm -f

all: activeClient testClient PutCGI PutHTML

testClient.o: testClient.cpp fifo.h
	$(CC) -c $(CFLAGS) testClient.cpp

activeClient.o: activeClient.cpp fifo.h pstream.h
	$(CC) -c $(CFLAGS) activeClient.cpp

testClient: testClient.o fifo.o
	$(CC) testClient.o -o testClient

activeClient: activeClient.o 
	$(CC) activeClient.o  -o activeClient -L/usr/local/lib -lcgicc

PutCGI: activeClient
	chmod 757 activeClient
	cp activeClient /usr/lib/cgi-bin/$(USER)_activeClient.cgi 

	echo "Current contents of your cgi-bin directory: "
	ls -l /usr/lib/cgi-bin/

PutHTML:
	cp active.html /var/www/html/class/softdev/$(USER)
	cp active.css /var/www/html/class/softdev/$(USER)
	cp active.js /var/www/html/class/softdev/$(USER)

	echo "Current contents of your HTML directory: "
	ls -l /var/www/html/class/softdev/$(USER)

clean:
	rm -f *.o activeClient testServer
