c-lin = gcc
c-win = clang
f-com = -O3 -g0 -Wall -Wextra --pedantic
f-lin = $(f-com) #-DLINUX 
f-win = $(f-com) #-DWINDOWS


linux: linux.c
	$(c-lin) $(f-lin) linux.c -o hxd++

windows: windows.c
	$(c-win) $(f-win) windows.c -o hxd++.exe
