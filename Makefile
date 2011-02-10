# RA-Remote Administrator-

VERSION = "1.0 Beta"

# flags
CFLAGS = ${LIBS} -DVERSION=\"${VERSION}\" -I./include -lssl

SERVER = src/server.c src/util.c
BINS = RA_SERVER
#MKACCESS = Mkaccess/RA_mkaccess.c src/util.c
#BINM = mkaccess

all:
	gcc -o $(BINS) $(SERVER) $(CFLAGS)
#	gcc -o $(BINM) $(MKACCESS) $(CFLAGS)

clean:
	#rm -rf ~/.RA_Logging
	rm -rf $(BINS)
	#rm -rf $(BINM)
	rm -rf /usr/local/bin/$(BINS)
	#rm -rf /usr/local/bin/$(BINM)


install: all
	cp -rf $(BINS) /usr/local/bin/
	#cp -rf $(BINM) /usr/local/bin/

#DO NOT DELETE!
