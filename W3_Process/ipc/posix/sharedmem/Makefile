all: producer consumer

CFLAGS=-Wall

producer: producer.o
	$(CC) -o producer -lrt producer.o

consumer: consumer.o
	$(CC) -o consumer -lrt consumer.o

clean:
	$(RM) consumer  consumer.o  producer  producer.o
