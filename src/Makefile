.PHONY: all clean style install uninstall

all: usbinfo

main.o: main.c
	gcc -c -std=c11 -Wall -Wextra -Werror main.c

info.o: info.c
	gcc -c -std=c11 -Wall -Wextra -Werror info.c

usbinfo: main.o info.o
	gcc main.o info.o -lusb-1.0 -o usbinfo

clean:
	rm -f *.o usbinfo

style:
	clang-format -i -style=Google *.c *.h

install: all
	install -m 755 ./usbinfo /usr/local/bin

uninstall:
	rm -f /usr/local/bin/usbinfo