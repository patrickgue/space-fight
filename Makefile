obj = keyboard.obj main.obj vga.obj sprite.obj text.obj log.obj menu.obj game.obj
bin = game.exe

CC = wcc
CFLAGS = -zq -ml -3
LD = wlink

$(bin): $(obj)
    $(LD) name $@ file { $(obj) }

.c.obj:
    $(CC) -fo=$@ $(CFLAGS) $<

clean: .symbolic
    del *.obj
    del $(bin)
