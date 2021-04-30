#!make

TARGETS = assoc clist clsid generated istream ordinal path shreg string thread url defines
TEST_OUTPUT = shlwapi-test-output.txt
PATCH_FILE = shlwapi.h.patch

SRCS = assoc.c clist.c clsid.c generated.c istream.c ordinal.c path.c shreg.c string.c thread.c url.c defines.c
OBJS = $(SRCS:.c=.o)
EXES = $(TARGETS:=.exe)

CFLAGS = -g -Wall -D_WIN32_IE=0x0700 -D_WIN32_WINNT=0x602 -DSTANDALONE -DTEST_SHLWAPI_H -I.
LDFLAGS = -user32 -lkernel32 -lgdi32 -lole32 -loleaut32 -luuid -lshlwapi

all:  $(TARGETS)

$(TARGETS): % : %.o shlwapi.h wine/debug.h wine/test.h
	$(CC) -o $@ $< $(LDFLAGS)

.PHONY: clean test patch

test:
	@(printf "Run C89 syntax check for shlwapi.h:\n"; \
	gcc $(CFLAGS) -s -Wall -Wextra -std=c89 -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition shlwapi.h; \
	printf "finished syntax check\n\n";)
	@(printf "DEFINES:\n"; ./defines; printf "\n"; \
	printf "ASSOC:\n"; ./assoc; printf "\n"; \
	printf "CLIST:\n"; ./clist; printf "\n"; \
	printf "CLSID:\n"; ./clsid; printf "\n"; \
	printf "GENERATED:\n"; ./generated; printf "\n"; \
	printf "ISTREAM:\n"; ./istream; printf "\n"; \
	printf "ORDINAL:\n"; ./ordinal; printf "\n"; \
	printf "PATH:\n"; ./path; printf "\n"; \
	printf "SHREG:\n"; ./shreg; printf "\n"; \
	printf "STRING:\n"; ./string; printf "\n"; \
	printf "THREAD:\n"; ./thread; printf "\n"; \
	printf "URL:\n"; ./url; printf "\n"; \
	printf "\n";)

patch:
	@(diff -uw doc/mingw64-shlwapi.h shlwapi.h >$(PATCH_FILE); \
	printf "Patch created in file $(PATCH_FILE)\n")

clean:
	@rm -f $(OBJS) $(EXES) $(PATCH_FILE) shlwapi.h.gch

