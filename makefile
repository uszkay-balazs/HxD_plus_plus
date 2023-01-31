# Compiler on Linux
c-lin = gcc

# Compiler on Windows
c-win = clang

# Common flags
#f-com = -O3 -g0 -Wall -Wextra --pedantic -s  #release
f-com = -O0 -g3 -Wall -Wextra --pedantic #debug 

# Linux flags 
f-lin = $(f-com) -ggdb #-DLINUX 

# Windows flags
f-win = $(f-com) -glldb #-DWINDOWS


# $ make linux 
linux: linux.c
	$(c-lin) $(f-lin) linux.c -o hxd++

# $ make windows
windows: windows.c
	$(c-win) $(f-win) windows.c -o hxd++.exe
