obj = keyboard.obj main.obj vga.obj sprite.obj
bin = game.exe

CC = wcc
CFLAGS = -zq -ml
LD = wlink

$(bin): $(obj)
    $(LD) name $@ file { $(obj) }

.c.obj:
    $(CC) -fo=$@ $(CFLAGS) $<

clean: .symbolic
    del *.obj
    del $(bin)
