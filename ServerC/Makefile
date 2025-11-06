.PHONY: help

server: server.c
	gcc -o server server.c -lwebsockets

udp_server: udp_server.c
	gcc -o udp_server udp_server.c -lwebsockets

run_server: server
	./server

run_udp_server: udp_server
	./udp_server

help:
	@echo "Доступные команды:"
	@echo "  make run_udp_server      - собрать и запустить UDP сервер"
	@echo "  make run_server  		  - собрать и запустить TCP сервер"