CC = gcc
CFLAGS = -Wall -Wextra -g -pedantic-errors -O3 -g

# Default target: Build both programs
all: converter aggregator

# -------- Rules for Converter --------
# Build the `converter` executable
converter: converter.o auxiliar.o converter_no_forks.o converter_with_forks.o converter_wf_fifo.o
	$(CC) $(CFLAGS) -o converter converter.o auxiliar.o converter_no_forks.o converter_with_forks.o converter_wf_fifo.o

# Compile `converter_with_forks.c`
converter_with_forks.o: converter_with_forks.c auxiliar_c.h converter_with_forks.h
	$(CC) $(CFLAGS) -c converter_with_forks.c

# Compile `converter_wf_fifo.c`
converter_wf_fifo.o: converter_wf_fifo.c auxiliar_c.h converter_wf_fifo.h
	$(CC) $(CFLAGS) -c converter_wf_fifo.c

# Compile `converter_no_forks.c`
converter_no_forks.o: converter_no_forks.c auxiliar_c.h
	$(CC) $(CFLAGS) -c converter_no_forks.c

# Compile `converter.c`
converter.o: converter.c auxiliar_c.h converter_no_forks.h converter_with_forks.h converter_wf_fifo.h
	$(CC) $(CFLAGS) -c converter.c

# Compile the shared `auxiliar.c`
auxiliar.o: auxiliar.c auxiliar_c.h
	$(CC) $(CFLAGS) -c auxiliar.c

# -------- Rules for Aggregator --------
# Build the `aggregator` executable
aggregator: aggregator.o auxiliar_g.o auxiliar_g_fifo.o
	$(CC) $(CFLAGS) -o aggregator aggregator.o auxiliar_g.o auxiliar_g_fifo.o

# Compile `aggregator.c`
aggregator.o: aggregator.c auxiliar_g.h auxiliar_g_fifo.h
	$(CC) $(CFLAGS) -c aggregator.c

# Compile `auxiliar_g.c`
auxiliar_g.o: auxiliar_g.c auxiliar_g.h
	$(CC) $(CFLAGS) -c auxiliar_g.c

# Compile `auxiliar_g_fifo.c`
auxiliar_g_fifo.o: auxiliar_g_fifo.c auxiliar_g_fifo.h
	$(CC) $(CFLAGS) -c auxiliar_g_fifo.c

# -------- Clean-up Rule --------
clean:
	rm -f *.o converter aggregator
