WINEDIR = /opt/wine-stable
WINELIB = $(WINEDIR)/lib/wine
WINEINC = $(WINEDIR)/include/wine

KARCH := $(shell uname -m)

FTD2XX_VER=1.4.34

ifeq ($(KARCH),aarch64)
	FTD2XX_TARBALL = libftd2xx-linux-arm-v8-$(FTD2XX_VER).tgz
	FTD2XX_DIR = linux-arm-v8
else ifeq ($(KARCH),x86_64)
	FTD2XX_TARBALL = libftd2xx-linux-x86_64-$(FTD2XX_VER).tgz
	FTD2XX_DIR = linux-x86_64
endif

WINE_INCLUDES = -I$(WINEINC)/windows -I$(WINEINC)/msvcrt -I$(shell dirname $(WINEINC)) -I$(FTD2XX_DIR)

LIBNAME = ftd2xx

UNIX_DIR = $(KARCH)-unix
CC = clang
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
    -L$(WINELIB)/$(UNIX_DIR) -l:ntdll.so

WIN_LIBS = -lwinecrt0 -lucrtbase -lkernel32 -lntdll

# For GCC
# -target i686-w64-mingw32
# remove --no-default-config
# remove -Wl,/safeseh:NO
i386_CC = clang
i386_CFLAGS = \
    -O2 \
    -D__STDC__ \
    -D__WINE_PE_BUILD \
    -D_UCRT \
    -D__WINESRC__ \
    -target i686-windows \
    -fuse-ld=lld \
    --no-default-config \
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
    -b i686-windows \
    -Wl,--wine-builtin \
    -Wl,/safeseh:NO \
    -shared \
    --no-default-config \
    -L$(WINELIB)/i386-windows $(WIN_LIBS)
i386_DIR = i386-windows

# For GCC
#  -target x86_64-w64-mingw32
# remove --no-default-config
x86_64_CC = clang
x86_64_CFLAGS = \
    -O2 \
    -D__STDC__ \
    -D__WINE_PE_BUILD \
    -D_UCRT \
    -D__WINESRC__ \
    -target x86_64-windows \
    -fuse-ld=lld \
    --no-default-config \
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
    -b x86_64-windows \
    -Wl,--wine-builtin \
    -shared \
    --no-default-config \
    -L$(WINELIB)/x86_64-windows $(WIN_LIBS)
x86_64_DIR = x86_64-windows

aarch64_CC = clang
aarch64_CFLAGS = \
    -O2 \
    -D__STDC__ \
    -D__WINE_PE_BUILD \
    -D_UCRT \
    -D__WINESRC__ \
    -target aarch64-windows \
    -fuse-ld=lld \
    --no-default-config \
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
    -mcmodel=small \
    $(WINE_INCLUDES)
aarch64_LDFLAGS = \
    -b aarch64-windows \
    -Wl,--wine-builtin \
    -shared \
    --no-default-config \
    -L$(WINELIB)/aarch64-windows $(WIN_LIBS)
aarch64_DIR = aarch64-windows

SRCS = ftd2xx.c

WIN_LIBS = -lwinecrt0 -lucrtbase -lkernel32 -lntdll

ifeq ($(KARCH),aarch64)
	KARCH_DIR = $(aarch64_DIR)
else ifeq ($(KARCH),x86_64)
	KARCH_DIR = $(x86_64_DIR)
endif

all: libs testapps defs

$(FTD2XX_TARBALL):
	wget https://ftdichip.com/wp-content/uploads/2025/11/$(FTD2XX_TARBALL)

libs: $(UNIX_DIR)/lib$(LIBNAME).so $(i386_DIR)/lib$(LIBNAME).dll $(KARCH_DIR)/lib$(LIBNAME).dll

defs: $(i386_DIR)/libftd2xx.def $(KARCH_DIR)/lib$(LIBNAME).def
testapps: $(i386_DIR)/testapp.exe $(KARCH_DIR)/testapp.exe
run_testapps:  $(i386_DIR)/testapp.exe $(KARCH_DIR)/testapp.exe $(i386_DIR)/lib$(LIBNAME).dll $(KARCH_DIR)/lib$(LIBNAME).dll
	wine $(i386_DIR)/testapp.exe
	wine $(KARCH_DIR)/testapp.exe

$(FTD2XX_DIR)/ftd2xx.h $(FTD2XX_DIR)/libftd2xx.a: $(FTD2XX_TARBALL)
	tar xzf $(FTD2XX_TARBALL)
	touch $(FTD2XX_TARBALL)

$(i386_DIR) $(KARCH_DIR) $(UNIX_DIR):
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
	#winebuild -w --implib -o $@ -b i686-w64-mingw32 --export $<
	winebuild -w --implib -o $@ -b i686-windows --export $<

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
	#winebuild -w --implib -o $@ -b x86_64-w64-mingw32 --export $<
	winebuild -w --implib -o $@ -b x86_64-windows --export $<

$(x86_64_DIR)/lib$(LIBNAME).dll: lib$(LIBNAME).spec $(addprefix $(x86_64_DIR)/, $(SRCS:.c=.o))
	winegcc -o $@ $^ $(x86_64_LDFLAGS)
	chmod -x $@
	winebuild --builtin $@

$(x86_64_DIR)/libftd2xx.def: lib$(LIBNAME).spec $(x86_64_DIR)/lib$(LIBNAME).dll
	winebuild -b x86_64-w64-mingw32 -w --def -o $@ --export lib$(LIBNAME).spec

# 64 bit ARM
$(aarch64_DIR)/%.o: %.c $(FTD2XX_DIR)/ftd2xx.h | $(aarch64_DIR)
	$(aarch64_CC) -c -o $@ $< $(aarch64_CFLAGS)

$(aarch64_DIR)/lib$(LIBNAME).a: lib$(LIBNAME).spec
	winebuild -w --implib -o $@ -b aarch64-windows --export $<

$(aarch64_DIR)/lib$(LIBNAME).dll: lib$(LIBNAME).spec $(addprefix $(aarch64_DIR)/, $(SRCS:.c=.o))
	winegcc -o $@ $^ $(aarch64_LDFLAGS)
	chmod -x $@
	winebuild --builtin $@

$(aarch64_DIR)/libftd2xx.def: lib$(LIBNAME).spec $(aarch64_DIR)/lib$(LIBNAME).dll
	winebuild -b aarch64-windows -w --def -o $@ --export lib$(LIBNAME).spec

# Test applications
$(i386_DIR)/testapp.exe: testapp.c  $(i386_DIR) $(i386_DIR)/lib$(LIBNAME).a
	winegcc --target=i686-windows $< -o $@ -L$(i386_DIR) -l$(LIBNAME) -Wl,/safeseh:NO
	#winegcc --target=i686-w64-mingw32 $< -o $@ -L$(i386_DIR) -l$(LIBNAME)
	#i686-w64-mingw32-gcc $< -o $@ -L$(i386_DIR) -l$(LIBNAME)

$(x86_64_DIR)/testapp.exe: testapp.c $(x86_64_DIR) $(x86_64_DIR)/lib$(LIBNAME).a
	winegcc --target=x86_64-windows $< -o $@ -L$(x86_64_DIR) -l$(LIBNAME) -Wl,/safeseh:NO
	#winegcc --target=x86_64-w64-mingw32 $< -o $@ -L$(x86_64_DIR) -l$(LIBNAME)
	#x86_64-w64-mingw32-gcc $< -o $@ -L$(x86_64_DIR) -l$(LIBNAME)

$(aarch64_DIR)/testapp.exe: testapp.c $(aarch64_DIR) $(aarch64_DIR)/lib$(LIBNAME).a
	winegcc --target=aarch64-windows $< -o $@ -L$(aarch64_DIR) -l$(LIBNAME) -Wl,/safeseh:NO

install:: $(i386_DIR)/lib$(LIBNAME).dll $(KARCH_DIR)/lib$(LIBNAME).dll $(UNIX_DIR)/lib$(LIBNAME).so
	install -m 644 $(INSTALL_PROGRAM_FLAGS) $(i386_DIR)/lib$(LIBNAME).dll $(DESTDIR)$(WINELIB)/i386-windows/lib$(LIBNAME).dll
	winebuild --builtin $(DESTDIR)$(WINELIB)/i386-windows/lib$(LIBNAME).dll

	#install -m 644 $(INSTALL_PROGRAM_FLAGS) x86_64-windows/lib$(LIBNAME).dll $(DESTDIR)$(WINELIB)/x86_64-windows/lib$(LIBNAME).dll
	#winebuild --builtin $(DESTDIR)$(WINELIB)/x86_64-windows/lib$(LIBNAME).dll

	install -m 644 $(INSTALL_PROGRAM_FLAGS) $(KARCH_DIR)/lib$(LIBNAME).dll $(DESTDIR)$(WINELIB)/$(KARCH)-windows/lib$(LIBNAME).dll
	winebuild --builtin $(DESTDIR)$(WINELIB)/$(KARCH)-windows/lib$(LIBNAME).dll

	install $(INSTALL_PROGRAM_FLAGS) $(UNIX_DIR)/lib$(LIBNAME).so $(DESTDIR)$(WINELIB)/$(UNIX_DIR)/lib$(LIBNAME).so

	install -m 644 $(INSTALL_PROGRAM_FLAGS) $(i386_DIR)/lib$(LIBNAME).dll $(WINEPREFIX)/drive_c/windows/syswow64/lib$(LIBNAME).dll
	#install -m 644 $(INSTALL_PROGRAM_FLAGS) x86_64-windows/lib$(LIBNAME).dll $(WINEPREFIX)/drive_c/windows/system32/lib$(LIBNAME).dll
	install -m 644 $(INSTALL_PROGRAM_FLAGS) $(KARCH_DIR)/lib$(LIBNAME).dll $(WINEPREFIX)/drive_c/windows/system32/lib$(LIBNAME).dll

uninstall::
	rm $(WINEPREFIX)/drive_c/windows/system32/lib$(LIBNAME).dll
	rm $(WINEPREFIX)/drive_c/windows/syswow64/lib$(LIBNAME).dll
	rm $(DESTDIR)$(WINELIB)/i386-windows/lib$(LIBNAME).dll
	rm $(DESTDIR)$(WINELIB)/$(KARCH)-windows/lib$(LIBNAME).dll
	rm $(DESTDIR)$(WINELIB)/$(UNIX_DIR)/lib$(LIBNAME).so

clean::
	rm -rf $(i386_DIR) $(x86_64_DIR) $(aarch64_DIR) $(UNIX_DIR) $(FTD2XX_DIR)
	#rm $(FTD2XX_TARBALL)
