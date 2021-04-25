#!make

TARGETS = assoc clist clsid generated istream ordinal path shreg string thread url defines
TEST_OUTPUT = shlwapi-test-output.txt

SRCS = assoc.c clist.c clsid.c generated.c istream.c ordinal.c path.c shreg.c string.c thread.c url.c defines.c
OBJS = $(SRCS:.c=.o)
EXES = $(TARGETS:=.exe)

CFLAGS = -g -Wall -D_WIN32_IE=0x0700 -D_WIN32_WINNT=0x602 -DSTANDALONE -DTEST_SHLWAPI_H
LDFLAGS = -user32 -lkernel32 -lgdi32 -lole32 -loleaut32 -luuid -lshlwapi

all:  $(TARGETS)

$(TARGETS): % : %.o
	$(CC) -o $@ $< $(LDFLAGS)

.PHONY: clean test

test:
	(printf "ASSOC\n"; ./assoc; printf "\n"; \
	printf "CLIST\n"; ./clist; printf "\n"; \
	printf "CLSID\n"; ./clsid; printf "\n"; \
	printf "GENERATED\n"; ./generated; printf "\n"; \
	printf "ISTREAM\n"; ./istream; printf "\n"; \
	printf "ORDINAL\n"; ./ordinal; printf "\n"; \
	printf "PATH\n"; ./path; printf "\n"; \
	printf "SHREG\n"; ./shreg; printf "\n"; \
	printf "STRING\n"; ./string; printf "\n"; \
	printf "THREAD\n"; ./thread; printf "\n"; \
	printf "URL\n"; ./url; printf "\n"; \
	printf "\n";)

clean:
	@rm -f $(OBJS) $(EXES)

