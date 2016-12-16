#-----------------------
# IMPORTANTE: Los valores de los parametros de los ejercicio?_test deben ajustarse.
# Se asume que los ficheros fuente se llaman ejercicio1.c, ejercicio2.c,...,ordenar.h
#-----------------------

CC = gcc -ansi -pedantic
#CFLAGS = -Wall -O3
CFLAGS = -Wall -g
EXE = ejercicio1 ejercicio2

all : $(EXE)

.PHONY : clean
clean :
	rm -f *.o core $(EXE)

%.o: %.c *.h
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

$(EXE) : % : %.o busqueda.o ordenacion.o permutaciones.o tiempos.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -o $@ $@.o busqueda.o ordenacion.o permutaciones.o tiempos.o
