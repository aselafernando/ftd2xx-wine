This is a Linux Wine dll that for FTDI's D2XX drivers.
It a wrapper layer between the FTDI's Linux D2XX drivers and 
Microsoft Windows apps running under Wine.

It has 64 bit and 32 bit support (WOW64).
32 bit applications running under Wine WOW64 can access FTDI devices without 
the need for multilib packages

Wine headers are required (assumed to be at /opt/wine-stable/include/wine)
Wine libraries assumed to be at /opt/wine-stable/lib/wine

Packages needed to build:
clang lld

Trace information is available under the channel ftd2xx ie WINEDEBUG=+ftd2xx

gen.py is a script used to help automate the creation of source code from 
the FTDI2XX headers. This does not normally need to be run and is not called
by the Makefile. It is only useful to add new functions (i.e. new driver versions)
