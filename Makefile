CFLAGS = /nologo

build: so-cpp.exe

so-cpp.exe: so-cpp.obj utilfunc.obj
	link /nologo /out:$@ $**

so-cpp.obj: so-cpp.c

utilfunc.obj: utilfunc.c

clean:
	del /Q /F *.obj so-cpp.exe