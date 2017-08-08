vpath %.c  = src
vpath %.so = lib

CPPFLAGS += -I inc/

LDFLAGS += -L lib/
LDFLAGS += -lsum
#ENVFLAGS += -Wl,-rpath=/mnt/hgfs/winshare/linux/project/lib

main:main.c libsum.so
	$(CC) $< -o $@ $(CPPFLAGS) $(LDFLAGS) $(ENVFLAGS)

libsum.so:
	$(MAKE) -C src install
			
clean:
	$(RM) main

distclean:clean
	$(RM) lib/libsum.so

.PHONY:clean distclean
