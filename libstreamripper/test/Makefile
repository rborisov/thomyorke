
CFLAGS=$(shell pkg-config --cflags libstreamripper)
LDFLAGS=$(shell pkg-config --libs libstreamripper)

all: streamripper

streamripper: streamripper.c
	cc -c $(CFLAGS) streamripper.c
	cc -o streamripper streamripper.o $(LDFLAGS)

clean:
	rm -f *~
	rm -f streamripper
	rm -f test*.mp3
	rm -f test*.cue
	rm -rf incomplete

test: all
	LD_LIBRARY_PATH=/usr/local/lib ./streamripper http://icecast.omroep.nl/radio4-bb-mp3.m3u -a test-%d
	
	
	
	
