# C++ Async Tasks makefile
# Link: 
CC=cl
#CFLAGS=/c /EHsc
#Compile with debug info
CFLAGS=/c /EHsc /Zi
LINK=link
#LFLAGS=
#Link with debug info
LFLAGS= /DEBUG
ODIR=bin
EXE=AsyncTasks.exe

all: $(ODIR)\$(EXE)

.cpp{$(ODIR)}.obj: 
	$(CC) $(CFLAGS) $** /Fo$@

$(ODIR)\$(EXE): $(ODIR)\main.obj $(ODIR)\asyncTasks.obj $(ODIR)\elapsedTimer.obj
	$(LINK) $** $(LFLAGS) /out:$@

clean:
	@IF EXIST *.pdb (del *.pdb)
	@IF EXIST bin\*.obj (del bin\*.obj)
	@IF EXIST bin\*.pdb (del bin\*.pdb)
	@IF EXIST bin\*.exe (del bin\*.exe)
	@IF EXIST bin\*.asm (del bin\*.asm)
	@IF EXIST bin\*.ilk (del bin\*.ilk)