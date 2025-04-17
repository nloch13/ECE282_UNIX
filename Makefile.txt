#
# Makefile for Pong Game
#
# Type 'make' to compile the pong game.
#

all: pong

pong: pong.c
	gcc -o pong pong.c -lncurses

clean:
	rm -f pong
