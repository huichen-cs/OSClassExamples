all: producer consumer

CFLAGS=-Wall

producer: producer.o
	$(CC) -o producer producer.o -lrt 

consumer: consumer.o
	$(CC) -o consumer consumer.o -lrt

clean:
	$(RM) consumer  consumer.o  producer  producer.o
