# libsqlite for FF
# Simon Zolin, 2017

# The original ./configure script must run before using this makefile.
# ./configure script requires tclsh binary (e.g. tcl-8.6.6-2.fc26)

OPT := LTO3
DEBUG := 0
include $(FF3PT)/makeconf

CFLAGS += \
	-I$(FF3PT)/sqlite -I. -I./src -I./ext/rtree -I./ext/icu -I./ext/fts3 -I./ext/async -I./ext/session \
	-D_HAVE_SQLITE_CONFIG_H -DBUILD_sqlite -DNDEBUG -DSQLITE_THREADSAFE=1 -DSQLITE_TEMP_STORE=1 -DSQLITE_CORE \
	-fPIC -DPIC

ifeq ($(OS),win)
CFLAGS += -DSQLITE_OS_WIN=1
else
CFLAGS += -DSQLITE_OS_UNIX=1
LDFLAGS += -Wl,-no-undefined -ldl -lpthread
endif

OBJ := \
	src/alter.o \
	src/analyze.o \
	src/attach.o \
	src/auth.o \
	src/backup.o \
	src/bitvec.o \
	src/btmutex.o \
	src/btree.o \
	src/build.o \
	src/callback.o \
	src/complete.o \
	src/ctime.o \
	src/date.o \
	src/dbstat.o \
	src/delete.o \
	src/expr.o \
	src/fault.o \
	src/fkey.o \
	src/func.o \
	src/global.o \
	src/hash.o \
	src/insert.o \
	src/legacy.o \
	src/loadext.o \
	src/main.o \
	src/malloc.o \
	src/mem0.o \
	src/mem1.o \
	src/mem2.o \
	src/mem3.o \
	src/mem5.o \
	src/memjournal.o \
	src/mutex.o \
	src/mutex_noop.o \
	src/mutex_unix.o \
	src/mutex_w32.o \
	src/notify.o \
	src/os.o \
	src/os_unix.o \
	src/os_win.o \
	src/pager.o \
	src/pcache.o \
	src/pcache1.o \
	src/pragma.o \
	src/prepare.o \
	src/printf.o \
	src/random.o \
	src/resolve.o \
	src/rowset.o \
	src/select.o \
	src/status.o \
	src/table.o \
	src/threads.o \
	src/tokenize.o \
	src/treeview.o \
	src/trigger.o \
	src/update.o \
	src/utf.o \
	src/util.o \
	src/vacuum.o \
	src/vdbe.o \
	src/vdbeapi.o \
	src/vdbeaux.o \
	src/vdbeblob.o \
	src/vdbemem.o \
	src/vdbesort.o \
	src/vdbetrace.o \
	src/vtab.o \
	src/wal.o \
	src/walker.o \
	src/where.o \
	src/wherecode.o \
	src/whereexpr.o

OBJ += \
	ext/fts3/fts3.o \
	ext/fts3/fts3_aux.o \
	ext/fts3/fts3_expr.o \
	ext/fts3/fts3_hash.o \
	ext/fts3/fts3_icu.o \
	ext/fts3/fts3_porter.o \
	ext/fts3/fts3_snippet.o \
	ext/fts3/fts3_tokenize_vtab.o \
	ext/fts3/fts3_tokenizer.o \
	ext/fts3/fts3_tokenizer1.o \
	ext/fts3/fts3_unicode.o \
	ext/fts3/fts3_unicode2.o \
	ext/fts3/fts3_write.o

OBJ += \
	ext/icu/icu.o \
	ext/misc/json1.o \
	ext/rbu/sqlite3rbu.o \
	ext/rtree/rtree.o \
	ext/session/sqlite3session.o

OBJ += \
	fts5.o \
	parse.o \
	opcodes.o


%.o: %.c sqlite3.h $(wildcard ./*.h)
	$(C) $(CFLAGS) $<  -o$@

libsqlite3-ff.$(SO): $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) -shared -o$@

sqlite3.h:
	make -f main.mk lemon TOP=. BCC=gcc
	make -f main.mk parse.h TOP=.
	make -f main.mk opcodes.h TOP=.
	make -f main.mk opcodes.c TOP=.
	make -f main.mk keywordhash.h TOP=. BCC=gcc
	make -f main.mk fts5.c TOP=.
	make -f main.mk sqlite3.h TOP=.
	cat $(FF3PT)/sqlite/*.patch | patch

clean:
	rm -fv $(OBJ) libsqlite3-ff.$(SO)
