src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)
trg = lib.a
MCU=atmega324pa
OPTLEVEL=s

CC=avr-gcc
CFLAGS=-I. -I/usr/include/simavr  -MMD $(INC) -g -mmcu=$(MCU) -O$(OPTLEVEL) \
	-std=c++14 -fpack-struct -fshort-enums             \
	-funsigned-bitfields -funsigned-char    \
	-Wall                                        

# Flags pour le compilateur en C++
CXXFLAGS=-fno-exceptions   

all:$(trg)
$(trg):$(obj)
	ar -crs $(trg) $(obj)

%.o: %.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $<

clean:
	rm -f *.o
	rm -f *.a
	rm -f *.d

var:
	@echo "src = $(src)"
	@echo "obj = $(obj)"
	@echo "trg = $(trg)"
