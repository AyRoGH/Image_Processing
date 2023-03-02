OUTDIR = out
LIBSDIR = $(OUTDIR)/libs
CC = gcc
CFLAGS = -Wall -Werror -Wextra -fsanitize=undefined -pedantic -g
LDFLAGS = -L$(LIBSDIR)
LDLIBS = -lbmp -lconvolution -limgdata -lfiles -lkernel

# all
all: $(LIBSDIR)/libbmp.so $(LIBSDIR)/libconvolution.so $(LIBSDIR)/libimgdata.so $(LIBSDIR)/libfiles.so $(LIBSDIR)/libkernel.so $(OUTDIR)/airi $(OUTDIR)/airi.sh

# *.o
$(LIBSDIR)/airi.o: airi.c | $(OUTDIR) $(LIBSDIR)
	$(CC) -c -g -o $@ $<

$(LIBSDIR)/bmp.o: bmp/bmp.c | $(OUTDIR) $(LIBSDIR)
	$(CC) -c -g -fPIC -o $@ $<

$(LIBSDIR)/convolution.o: convolution/convolution.c | $(OUTDIR) $(LIBSDIR)
	$(CC) -c -g -fPIC -o $@ $<

$(LIBSDIR)/imgdata.o: data/imgdata.c | $(OUTDIR) $(LIBSDIR)
	$(CC) -c -g -fPIC -o $@ $<

$(LIBSDIR)/files.o: files/files.c | $(OUTDIR) $(LIBSDIR)
	$(CC) -c -g -fPIC -o $@ $<

$(LIBSDIR)/kernel.o: kernel/kernel.c | $(OUTDIR) $(LIBSDIR)
	$(CC) -c -g -fPIC -o $@ $<

# exe
$(OUTDIR)/airi: $(LIBSDIR)/airi.o $(LIBSDIR)/libbmp.so $(LIBSDIR)/libconvolution.so $(LIBSDIR)/libimgdata.so $(LIBSDIR)/libfiles.so $(LIBSDIR)/libkernel.so
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) $(LDLIBS)
	rm -f $(LIBSDIR)/*.o

# *.so
$(LIBSDIR)/libbmp.so: $(LIBSDIR)/bmp.o $(LIBSDIR)/imgdata.o
	$(CC) -shared -o $@ $^

$(LIBSDIR)/libconvolution.so: $(LIBSDIR)/convolution.o
	$(CC) -shared -o $@ $<

$(LIBSDIR)/libimgdata.so: $(LIBSDIR)/imgdata.o
	$(CC) -shared -o $@ $<

$(LIBSDIR)/libfiles.so: $(LIBSDIR)/files.o
	$(CC) -shared -o $@ $<

$(LIBSDIR)/libkernel.so: $(LIBSDIR)/kernel.o
	$(CC) -shared -o $@ $<

# airi.sh
$(OUTDIR)/airi.sh: $(OUTDIR)/airi
	echo '#!/bin/sh' > $@
	echo 'export LD_LIBRARY_PATH=libs:$$LD_LIBRARY_PATH' >> $@
	echo './airi' >> $@
	chmod +x $@

# out & out/libs
$(OUTDIR):
	mkdir -p $(OUTDIR)

$(LIBSDIR):
	mkdir -p $(LIBSDIR)

# clean
clean:
	rm -rf $(LIBSDIR)/*.o $(LIBSDIR)/*.so $(OUTDIR)/airi $(OUTDIR)/*.sh
	rmdir $(LIBSDIR)
	rmdir $(OUTDIR)

.PHONY: all clean
