################################################################################
### Compilers ##################################################################
################################################################################
	
INCLUDEPATH=
LIBS=-lpthread -L/usr/lib/mysql -lmysqlclient -shared
	
CC=gcc -c $(INCLUDEPATH) -W -Wall -Wpointer-arith -pipe -D_REENTRANT -O3 -o
CC_DEBUG=gcc -g -c $(INCLUDEPATH) -W -Wall -Wpointer-arith -pipe -D_REENTRANT -o
CC_LINKER=gcc $(INCLUDEPATH) -W -Wall -Wpointer-arith -pipe -D_REENTRANT -O3 -o
CC_LINKER_DEBUG=gcc -g $(INCLUDEPATH) -W -Wall -Wpointer-arith -pipe -D_REENTRANT -o
	
CPP=g++ -c $(INCLUDEPATH) -W -Wall -Wpointer-arith -pipe -D_REENTRANT -O3 -o
CPP_DEBUG=g++ -g -c $(INCLUDEPATH) -W -Wall -Wpointer-arith -pipe -D_REENTRANT -o
CPP_LINKER=g++ $(INCLUDEPATH) -W -Wall -Wpointer-arith -pipe -D_REENTRANT -O3 -o
CPP_LINKER_DEBUG=g++ -g $(INCLUDEPATH) -W -Wall -Wpointer-arith -pipe -D_REENTRANT -o
	
AR=ar  cqs
AR_DEBUG=ar  cqs
	
################################################################################
### Generated object files #####################################################
################################################################################
	
OBJECTS=\
	ky_reactor.o\
	ky_thread.o\
	ky_time.o\
	ky_file.o\
	ky_mysql.o\
	ky_string.o\
	ky_cmp.o\
	ky_sqlite3.o\
	ky_socket.o\
	ky_rbtree.o\
	ky_stack.o\
	ky_ini.o\
	ky_avltree.o\
	ky_udt.o\
	ky_opt.o\
	ky_progress.o\
	ky_tool.o\
	ky_linklist.o\
	ky_log.o\
	
OBJECTS_DEBUG=\
	ky_reactor.od\
	ky_thread.od\
	ky_time.od\
	ky_file.od\
	ky_mysql.od\
	ky_string.od\
	ky_cmp.od\
	ky_sqlite3.od\
	ky_socket.od\
	ky_rbtree.od\
	ky_stack.od\
	ky_ini.od\
	ky_avltree.od\
	ky_udt.od\
	ky_opt.od\
	ky_progress.od\
	ky_tool.od\
	ky_linklist.od\
	ky_log.od\
	
################################################################################
### Project Files ##############################################################
################################################################################
	
all: $(OBJECTS)
	$(CPP_LINKER) libky.so $(OBJECTS) $(LIBS)
ky_reactor.o: ./ky_reactor.c\
	./ky_cmp.h\
	./ky_reactor.h\
	./ky_map.h\
	./ky_rbtree.h\
	./ky_socket.h\
	./ky_linklist.h\
	./ky_avltree.h
	$(CC) ky_reactor.o ./ky_reactor.c
ky_thread.o: ./ky_thread.c
	$(CC) ky_thread.o ./ky_thread.c
ky_time.o: ./ky_time.c\
	./ky_time.h
	$(CC) ky_time.o ./ky_time.c
ky_file.o: ./ky_file.c\
	./ky_file.h\
	./ky_string.h
	$(CC) ky_file.o ./ky_file.c
ky_mysql.o: ./ky_mysql.c\
	./ky_mysql.h\
	./ky_map.h\
	./ky_rbtree.h\
	./ky_cmp.h\
	./ky_avltree.h\
	./ky_string.h\
	./ky_log.h
	$(CC) ky_mysql.o ./ky_mysql.c
ky_string.o: ./ky_string.c\
	./ky_string.h
	$(CC) ky_string.o ./ky_string.c
ky_cmp.o: ./ky_cmp.c\
	./ky_cmp.h
	$(CC) ky_cmp.o ./ky_cmp.c
ky_sqlite3.o: ./ky_sqlite3.c\
	./ky_log.h
	$(CC) ky_sqlite3.o ./ky_sqlite3.c
ky_socket.o: ./ky_socket.c\
	./ky_socket.h\
	./ky_log.h
	$(CC) ky_socket.o ./ky_socket.c
ky_rbtree.o: ./ky_rbtree.c\
	./ky_rbtree.h\
	./ky_math.h
	$(CC) ky_rbtree.o ./ky_rbtree.c
ky_stack.o: ./ky_stack.c
	$(CC) ky_stack.o ./ky_stack.c
ky_ini.o: ./ky_ini.c\
	./ky_ini.h
	$(CC) ky_ini.o ./ky_ini.c
ky_avltree.o: ./ky_avltree.c\
	./ky_avltree.h\
	./ky_math.h
	$(CC) ky_avltree.o ./ky_avltree.c
ky_udt.o: ./ky_udt.c\
	./ky_udt.h\
	./ky_map.h\
	./ky_rbtree.h\
	./ky_socket.h\
	./ky_avltree.h\
	./ky_log.h
	$(CC) ky_udt.o ./ky_udt.c
ky_opt.o: ./ky_opt.c\
	./ky_opt.h
	$(CC) ky_opt.o ./ky_opt.c
ky_progress.o: ./ky_progress.c\
	./ky_progress.h
	$(CC) ky_progress.o ./ky_progress.c
ky_tool.o: ./ky_tool.c
	$(CC) ky_tool.o ./ky_tool.c
ky_linklist.o: ./ky_linklist.c\
	./ky_linklist.h
	$(CC) ky_linklist.o ./ky_linklist.c
ky_log.o: ./ky_log.c\
	./ky_time.h\
	./ky_log.h
	$(CC) ky_log.o ./ky_log.c
	
debug: $(OBJECTS_DEBUG)
	$(CPP_LINKER_DEBUG) libky.so $(OBJECTS_DEBUG) $(LIBS)
ky_reactor.od: ./ky_reactor.c\
	./ky_cmp.h\
	./ky_reactor.h\
	./ky_map.h\
	./ky_rbtree.h\
	./ky_socket.h\
	./ky_linklist.h\
	./ky_avltree.h
	$(CC_DEBUG) ky_reactor.od ./ky_reactor.c
ky_thread.od: ./ky_thread.c
	$(CC_DEBUG) ky_thread.od ./ky_thread.c
ky_time.od: ./ky_time.c\
	./ky_time.h
	$(CC_DEBUG) ky_time.od ./ky_time.c
ky_file.od: ./ky_file.c\
	./ky_file.h\
	./ky_string.h
	$(CC_DEBUG) ky_file.od ./ky_file.c
ky_mysql.od: ./ky_mysql.c\
	./ky_mysql.h\
	./ky_map.h\
	./ky_rbtree.h\
	./ky_cmp.h\
	./ky_avltree.h\
	./ky_string.h\
	./ky_log.h
	$(CC_DEBUG) ky_mysql.od ./ky_mysql.c
ky_string.od: ./ky_string.c\
	./ky_string.h
	$(CC_DEBUG) ky_string.od ./ky_string.c
ky_cmp.od: ./ky_cmp.c\
	./ky_cmp.h
	$(CC_DEBUG) ky_cmp.od ./ky_cmp.c
ky_sqlite3.od: ./ky_sqlite3.c\
	./ky_log.h
	$(CC_DEBUG) ky_sqlite3.od ./ky_sqlite3.c
ky_socket.od: ./ky_socket.c\
	./ky_socket.h\
	./ky_log.h
	$(CC_DEBUG) ky_socket.od ./ky_socket.c
ky_rbtree.od: ./ky_rbtree.c\
	./ky_rbtree.h\
	./ky_math.h
	$(CC_DEBUG) ky_rbtree.od ./ky_rbtree.c
ky_stack.od: ./ky_stack.c
	$(CC_DEBUG) ky_stack.od ./ky_stack.c
ky_ini.od: ./ky_ini.c\
	./ky_ini.h
	$(CC_DEBUG) ky_ini.od ./ky_ini.c
ky_avltree.od: ./ky_avltree.c\
	./ky_avltree.h\
	./ky_math.h
	$(CC_DEBUG) ky_avltree.od ./ky_avltree.c
ky_udt.od: ./ky_udt.c\
	./ky_udt.h\
	./ky_map.h\
	./ky_rbtree.h\
	./ky_socket.h\
	./ky_avltree.h\
	./ky_log.h
	$(CC_DEBUG) ky_udt.od ./ky_udt.c
ky_opt.od: ./ky_opt.c\
	./ky_opt.h
	$(CC_DEBUG) ky_opt.od ./ky_opt.c
ky_progress.od: ./ky_progress.c\
	./ky_progress.h
	$(CC_DEBUG) ky_progress.od ./ky_progress.c
ky_tool.od: ./ky_tool.c
	$(CC_DEBUG) ky_tool.od ./ky_tool.c
ky_linklist.od: ./ky_linklist.c\
	./ky_linklist.h
	$(CC_DEBUG) ky_linklist.od ./ky_linklist.c
ky_log.od: ./ky_log.c\
	./ky_time.h\
	./ky_log.h
	$(CC_DEBUG) ky_log.od ./ky_log.c
	
install:
	echo 'install command not set'
	
clean:
	rm -f libky.so libky.so
	rm -rf *.o *.od
