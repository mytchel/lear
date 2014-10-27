all: lear

lear: lear.c
	gcc lear.c -o lear

install:
	install -Dm 755 lear /usr/local/bin/lear
	cp learlines /lib/lear
