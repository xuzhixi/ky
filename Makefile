################################################################################
### Compilers ##################################################################
################################################################################
	
INCLUDEPATH=
LIBS=-lpthread -shared
	
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
	ky_malloc.o\
	ky_cmp.o\
	ky_core.o\
	ky_rbtree.o\
	ky_socket.o\
	ky_avltree.o\
	ky_udt.o\
	ky_stack.o\
	ky_progress.o\
	ky_linklist.o\
	ky_log.o\
	
OBJECTS_DEBUG=\
	ky_reactor.od\
	ky_thread.od\
	ky_time.od\
	ky_malloc.od\
	ky_cmp.od\
	ky_core.od\
	ky_rbtree.od\
	ky_socket.od\
	ky_avltree.od\
	ky_udt.od\
	ky_stack.od\
	ky_progress.od\
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
	./ky_types.h\
	./ky_map.h\
	./ky_rbtree.h\
	./ky_socket.h\
	./ky_linklist.h\
	./ky_malloc.h
	$(CC) ky_reactor.o ./ky_reactor.c
ky_thread.o: ./ky_thread.c
	$(CC) ky_thread.o ./ky_thread.c
ky_time.o: ./ky_time.c\
	./ky_types.h\
	./ky_time.h
	$(CC) ky_time.o ./ky_time.c
ky_malloc.o: ./ky_malloc.c\
	./ky_malloc.h
	$(CC) ky_malloc.o ./ky_malloc.c
ky_cmp.o: ./ky_cmp.c\
	./ky_cmp.h\
	./ky_types.h
	$(CC) ky_cmp.o ./ky_cmp.c
ky_core.o: ./ky_core.c\
	./ky_types.h\
	./ky_core.h
	$(CC) ky_core.o ./ky_core.c
ky_rbtree.o: ./ky_rbtree.c\
	./ky_types.h\
	./ky_malloc.h\
	./ky_rbtree.h\
	./ky_math.h
	$(CC) ky_rbtree.o ./ky_rbtree.c
ky_socket.o: ./ky_socket.c\
	./ky_socket.h\
	./ky_types.h\
	./ky_log.h
	$(CC) ky_socket.o ./ky_socket.c
ky_avltree.o: ./ky_avltree.c\
	./ky_types.h\
	./ky_malloc.h\
	./ky_avltree.h\
	./ky_math.h
	$(CC) ky_avltree.o ./ky_avltree.c
ky_udt.o: ./ky_udt.c\
	./ky_udt.h\
	./ky_map.h\
	./ky_rbtree.h\
	./ky_socket.h\
	./ky_types.h\
	./ky_log.h
	$(CC) ky_udt.o ./ky_udt.c
ky_stack.o: ./ky_stack.c
	$(CC) ky_stack.o ./ky_stack.c
ky_progress.o: ./ky_progress.c\
	./ky_progress.h
	$(CC) ky_progress.o ./ky_progress.c
ky_linklist.o: ./ky_linklist.c\
	./ky_linklist.h\
	./ky_types.h\
	./ky_malloc.h
	$(CC) ky_linklist.o ./ky_linklist.c
ky_log.o: ./ky_log.c\
	./ky_types.h\
	./ky_time.h\
	./ky_log.h
	$(CC) ky_log.o ./ky_log.c
	
debug: $(OBJECTS_DEBUG)
	$(CPP_LINKER_DEBUG) libky.so $(OBJECTS_DEBUG) $(LIBS)
ky_reactor.od: ./ky_reactor.c\
	./ky_cmp.h\
	./ky_reactor.h\
	./ky_types.h\
	./ky_map.h\
	./ky_rbtree.h\
	./ky_socket.h\
	./ky_linklist.h\
	./ky_malloc.h
	$(CC_DEBUG) ky_reactor.od ./ky_reactor.c
ky_thread.od: ./ky_thread.c
	$(CC_DEBUG) ky_thread.od ./ky_thread.c
ky_time.od: ./ky_time.c\
	./ky_types.h\
	./ky_time.h
	$(CC_DEBUG) ky_time.od ./ky_time.c
ky_malloc.od: ./ky_malloc.c\
	./ky_malloc.h
	$(CC_DEBUG) ky_malloc.od ./ky_malloc.c
ky_cmp.od: ./ky_cmp.c\
	./ky_cmp.h\
	./ky_types.h
	$(CC_DEBUG) ky_cmp.od ./ky_cmp.c
ky_core.od: ./ky_core.c\
	./ky_types.h\
	./ky_core.h
	$(CC_DEBUG) ky_core.od ./ky_core.c
ky_rbtree.od: ./ky_rbtree.c\
	./ky_types.h\
	./ky_malloc.h\
	./ky_rbtree.h\
	./ky_math.h
	$(CC_DEBUG) ky_rbtree.od ./ky_rbtree.c
ky_socket.od: ./ky_socket.c\
	./ky_socket.h\
	./ky_types.h\
	./ky_log.h
	$(CC_DEBUG) ky_socket.od ./ky_socket.c
ky_avltree.od: ./ky_avltree.c\
	./ky_types.h\
	./ky_malloc.h\
	./ky_avltree.h\
	./ky_math.h
	$(CC_DEBUG) ky_avltree.od ./ky_avltree.c
ky_udt.od: ./ky_udt.c\
	./ky_udt.h\
	./ky_map.h\
	./ky_rbtree.h\
	./ky_socket.h\
	./ky_types.h\
	./ky_log.h
	$(CC_DEBUG) ky_udt.od ./ky_udt.c
ky_stack.od: ./ky_stack.c
	$(CC_DEBUG) ky_stack.od ./ky_stack.c
ky_progress.od: ./ky_progress.c\
	./ky_progress.h
	$(CC_DEBUG) ky_progress.od ./ky_progress.c
ky_linklist.od: ./ky_linklist.c\
	./ky_linklist.h\
	./ky_types.h\
	./ky_malloc.h
	$(CC_DEBUG) ky_linklist.od ./ky_linklist.c
ky_log.od: ./ky_log.c\
	./ky_types.h\
	./ky_time.h\
	./ky_log.h
	$(CC_DEBUG) ky_log.od ./ky_log.c
	
install:
	echo 'install command not set'
	
clean:
	rm -f libky.so libky.so
	rm -rf *.o *.od
