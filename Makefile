PREFIX?=/usr/local
BINDIR?=${PREFIX}/bin
LIBDIR?=${PREFIX}/lib

CC?=gcc

all: lear

lear: lear.c
	${CC} -o lear -DLEARPATH=\"${LIBDIR}/lear\" lear.c

clean:
	rm lear

install: lear
	install -Dm 755 lear ${DESTDIR}${BINDIR}/lear
	install learlines ${DESTDIR}${LIBDIR}/lear

uninstall:
	rm ${DESTDIR}${BINDIR}/lear
	rm ${DESTDIR}${LIBDIR}/lear
