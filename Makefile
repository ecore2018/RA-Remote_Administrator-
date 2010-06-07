# RA-Remote Administrator-

VERSION = 0.0.1

# includes and libs
LIBS = -lssl

# flags
CFLAGS = ${LIBS} -DVERSION=\"${VERSION}\" -I./include

SERVER = src/server.c src/util.c
BINS = RA_SERVER
CLIENT = src/client.c src/util.c
BINC = RA_CLIENT
MKACCESS = Mkaccess/RA_mkaccess.c src/util.c
BINM = mkaccess

all:
	gcc -o $(BINS) $(SERVER) $(CFLAGS)
	gcc -o $(BINC) $(CLIENT) $(CFLAGS)
#	gcc -o $(BINM) $(MKACCESS) $(CFLAGS)

clean:
	#rm -rf ~/.RA_Logging
	rm -rf $(BINS)
	rm -rf $(BINC)
	#rm -rf $(BINM)
	rm -rf /usr/local/bin/$(BINS)
	rm -rf /usr/local/bin/$(BINC)
	#rm -rf /usr/local/bin/$(BINM)


install: all
	cp -rf $(BINS) /usr/local/bin/
	cp -rf $(BINC) /usr/local/bin/
	#cp -rf $(BINM) /usr/local/bin/

#DO NOT DELETE!
