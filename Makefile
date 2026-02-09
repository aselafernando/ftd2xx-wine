WINEDIR = /opt/wine-stable
WINELIB = $(WINEDIR)/lib/wine
WINEINC = $(WINEDIR)/include/wine

FTD2XX_DIR = linux-x86_64
WINE_INCLUDES = -I$(WINEINC)/windows -I$(WINEINC)/msvcrt -I$(shell dirname $(WINEINC)) -I$(FTD2XX_DIR)
FTD2XX_VER=1.4.34
FTD2XX_TARBALL = libftd2xx-linux-x86_64-$(FTD2XX_VER).tgz

LIBNAME = ftd2xx

CC = gcc
CFLAGS = \
    -m64 \
    -O2 \
    -D__WINESRC__ \
    -DWINE_UNIX_LIB \
    -pipe \
    -fcf-protection=none \
    -fvisibility=hidden \
    -fno-stack-protector \
    -fno-strict-aliasing \
    -fPIC \
    -fasynchronous-unwind-tables \
    -Wall \
    -Wdeclaration-after-statement \
    -Wempty-body \
    -Wignored-qualifiers \
    -Winit-self \
    -Wstrict-prototypes \
    -Wtype-limits \
    -Wunused-but-set-parameter \
    -Wvla \
    -Wwrite-strings \
    -Wpointer-arith \
	-I$(FTD2XX_DIR)
LDFLAGS = \
    -shared \
    -Wl,-Bsymbolic \
    -Wl,-soname,lib$(LIBNAME).so \
    -Wl,-z,defs \
    -L$(WINELIB)/x86_64-unix -l:ntdll.so
UNIX_DIR = x86_64-unix

WIN_LIBS = -lwinecrt0 -lucrtbase -lkernel32 -lntdll

i386_CC = winegcc
i386_CFLAGS = \
    -O2 \
    -D__STDC__ \
    -D__WINE_PE_BUILD \
    -D_UCRT \
    -D__WINESRC__ \
    -target i686-w64-mingw32 \
    -fuse-ld=lld \
    -fno-strict-aliasing \
    -fno-omit-frame-pointer \
    -Wall \
    -Wdeclaration-after-statement \
    -Wempty-body \
    -Wignored-qualifiers \
    -Winit-self \
    -Wstrict-prototypes \
    -Wtype-limits \
    -Wunused-but-set-parameter \
    -Wvla \
    -Wwrite-strings \
    -Wpointer-arith \
    -Wabsolute-value \
    -Wenum-conversion \
    $(WINE_INCLUDES)
i386_LDFLAGS = \
    -b i686-w64-mingw32 \
    -Wl,--wine-builtin \
    -shared \
    -L$(WINELIB)/i386-windows $(WIN_LIBS)
i386_DIR = i386-windows

x86_64_CC = winegcc
x86_64_CFLAGS = \
    -O2 \
    -D__STDC__ \
    -D__WINE_PE_BUILD \
    -D_UCRT \
    -D__WINESRC__ \
    -target x86_64-w64-mingw32 \
    -fuse-ld=lld \
    -fno-strict-aliasing \
    -Wall \
    -Wdeclaration-after-statement \
    -Wempty-body \
    -Wignored-qualifiers \
    -Winit-self \
    -Wstrict-prototypes \
    -Wtype-limits \
    -Wunused-but-set-parameter \
    -Wvla \
    -Wwrite-strings \
    -Wpointer-arith \
    -Wabsolute-value \
    -Wenum-conversion \
    -Wformat-overflow \
    -Wnonnull \
    -mcx16 \
    -mcmodel=small \
    $(WINE_INCLUDES)
x86_64_LDFLAGS = \
    -b x86_64-w64-mingw32 \
    -Wl,--wine-builtin \
    -shared \
    -L$(WINELIB)/x86_64-windows $(WIN_LIBS)
x86_64_DIR = x86_64-windows

SRCS = ftd2xx.c

WIN_LIBS = -lwinecrt0 -lucrtbase -lkernel32 -lntdll

all: libs testapps defs run_testapps

$(FTD2XX_TARBALL):
	wget https://ftdichip.com/wp-content/uploads/2025/11/$(FTD2XX_TARBALL)
libs: $(UNIX_DIR)/lib$(LIBNAME).so $(i386_DIR)/lib$(LIBNAME).dll $(x86_64_DIR)/lib$(LIBNAME).dll
defs: $(i386_DIR)/libftd2xx.def $(x86_64_DIR)/lib$(LIBNAME).def
testapps: $(i386_DIR)/testapp.exe $(x86_64_DIR)/testapp.exe
run_testapps:  $(i386_DIR)/testapp.exe $(x86_64_DIR)/testapp.exe $(i386_DIR)/lib$(LIBNAME).dll $(x86_64_DIR)/lib$(LIBNAME).dll
	wine $(i386_DIR)/testapp.exe
	wine $(x86_64_DIR)/testapp.exe

$(FTD2XX_DIR)/ftd2xx.h $(FTD2XX_DIR)/libftd2xx.a: $(FTD2XX_TARBALL)
	tar xzf $(FTD2XX_TARBALL)
	touch $(FTD2XX_TARBALL)

$(i386_DIR) $(x86_64_DIR) $(UNIX_DIR):
	mkdir -p $@

$(UNIX_DIR)/unixlib.o: unixlib.c $(FTD2XX_DIR)/ftd2xx.h | $(UNIX_DIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(UNIX_DIR)/lib$(LIBNAME).so: $(UNIX_DIR)/unixlib.o $(FTD2XX_DIR)/libftd2xx.a
	$(CC) -o $@ $^ $(LDFLAGS)

# Windows libraries
# 32 bit
$(i386_DIR)/%.o: %.c $(FTD2XX_DIR)/ftd2xx.h | $(i386_DIR)
	$(i386_CC) -c -o $@ $< $(i386_CFLAGS)

$(i386_DIR)/lib$(LIBNAME).a: lib$(LIBNAME).spec
	winebuild -w --implib -o $@ -b i686-w64-mingw32 --export $<

$(i386_DIR)/lib$(LIBNAME).dll: lib$(LIBNAME).spec $(addprefix $(i386_DIR)/, $(SRCS:.c=.o))
	winegcc -o $@ $^ $(i386_LDFLAGS)
	chmod -x $@
	winebuild --builtin $@

$(i386_DIR)/libftd2xx.def: lib$(LIBNAME).spec $(i386_DIR)/lib$(LIBNAME).dll
	winebuild -b i686-w64-mingw32 -w --def -o $@ --export lib$(LIBNAME).spec

# 64 bit
$(x86_64_DIR)/%.o: %.c $(FTD2XX_DIR)/ftd2xx.h | $(x86_64_DIR)
	$(x86_64_CC) -c -o $@ $< $(x86_64_CFLAGS)

$(x86_64_DIR)/lib$(LIBNAME).a: lib$(LIBNAME).spec
	winebuild -w --implib -o $@ -b x86_64-w64-mingw32 --export $<

$(x86_64_DIR)/lib$(LIBNAME).dll: lib$(LIBNAME).spec $(addprefix $(x86_64_DIR)/, $(SRCS:.c=.o))
	winegcc -o $@ $^ $(x86_64_LDFLAGS)
	chmod -x $@
	winebuild --builtin $@

$(x86_64_DIR)/libftd2xx.def: lib$(LIBNAME).spec $(x86_64_DIR)/lib$(LIBNAME).dll
	winebuild -b x86_64-w64-mingw32 -w --def -o $@ --export lib$(LIBNAME).spec

# Test applications
$(i386_DIR)/testapp.exe: testapp.c  $(i386_DIR) $(i386_DIR)/lib$(LIBNAME).a
	winegcc --target=i686-w64-mingw32 $< -o $@ -L$(i386_DIR) -l$(LIBNAME)
	#i686-w64-mingw32-gcc $< -o $@ -L$(i386_DIR) -l$(LIBNAME)

$(x86_64_DIR)/testapp.exe: testapp.c $(x86_64_DIR) $(x86_64_DIR)/lib$(LIBNAME).a
	winegcc --target=x86_64-w64-mingw32 $< -o $@ -L$(x86_64_DIR) -l$(LIBNAME)
	#x86_64-w64-mingw32-gcc $< -o $@ -L$(x86_64_DIR) -l$(LIBNAME)

install:: $(i386_DIR)/lib$(LIBNAME).dll $(x86_64_DIR)/lib$(LIBNAME).dll $(UNIX_DIR)/lib$(LIBNAME).so
	install -m 644 $(INSTALL_PROGRAM_FLAGS) i386-windows/lib$(LIBNAME).dll $(DESTDIR)$(WINELIB)/i386-windows/lib$(LIBNAME).dll
	winebuild --builtin $(DESTDIR)$(WINELIB)/i386-windows/lib$(LIBNAME).dll
	install -m 644 $(INSTALL_PROGRAM_FLAGS) x86_64-windows/lib$(LIBNAME).dll $(DESTDIR)$(WINELIB)/x86_64-windows/lib$(LIBNAME).dll
	winebuild --builtin $(DESTDIR)$(WINELIB)/x86_64-windows/lib$(LIBNAME).dll
	install $(INSTALL_PROGRAM_FLAGS) $(UNIX_DIR)/lib$(LIBNAME).so $(DESTDIR)$(WINELIB)/$(UNIX_DIR)/lib$(LIBNAME).so

	install -m 644 $(INSTALL_PROGRAM_FLAGS) i386-windows/lib$(LIBNAME).dll $(WINEPREFIX)/drive_c/windows/syswow64/lib$(LIBNAME).dll
	install -m 644 $(INSTALL_PROGRAM_FLAGS) x86_64-windows/lib$(LIBNAME).dll $(WINEPREFIX)/drive_c/windows/system32/lib$(LIBNAME).dll

uninstall::
	rm $(WINEPREFIX)/drive_c/windows/system32/lib$(LIBNAME).dll
	rm $(WINEPREFIX)/drive_c/windows/syswow64/lib$(LIBNAME).dll
	rm $(DESTDIR)$(WINELIB)/i386-windows/lib$(LIBNAME).dll
	rm $(DESTDIR)$(WINELIB)/x86_64-windows/lib$(LIBNAME).dll
	rm $(DESTDIR)$(WINELIB)/$(UNIX_DIR)/lib$(LIBNAME).so

clean::
	rm -rf $(i386_DIR) $(x86_64_DIR) $(UNIX_DIR) $(FTD2XX_DIR)
    #rm $(FTD2XX_TARBALL)
