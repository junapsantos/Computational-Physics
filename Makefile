# Makefile

BINDIR := bin
LIBDIR := lib

CCFLAGS := -pedantic

CC := g++ -std=c++11 

# src/ (declarcaoes de funcoes, de calsses + codigo)
# main/ (programas principais)
# bin/ (temporarios, .o, .exe)
# lib/ (bibliotecas) biblioteca FC

# making library
# - static: .a
# - shareable: .so

VPATH = main:src

ROOTLIB := $(shell root-config --libs)
ROOTINC := $(shell root-config --incdir)

SRC := $(wildcard src/*.C)
OBJ := $(patsubst %.C, $(BINDIR)/%.o, $(notdir $(SRC)))
INC := $(wildcard src/*.h)

lib: $(LIBDIR)/libFC.a

$(LIBDIR)/libFC.a: $(OBJ) 
	@echo make lib...
	ar ruv $@ $^
	ranlib $@

let_total: let.exe let1.exe

let_CAMPO_MAG: let1.exe let2.exe

1: let1.exe

2: let.exe

3: let2.exe

4: let3.exe



%.exe: $(BINDIR)/%.o $(LIBDIR)/libFC.a 
	@echo compilink and linking... 
	$(CC) -I src $< -o $(BINDIR)/$@ -L lib -l FC $(ROOTLIB)

$(BINDIR)/%.o: %.C | $(INC)
	@echo compiling... $<
	$(CC) -I src -I $(ROOTINC) -c $< -o $@


######### clean

tilde := $(wildcard */*~) $(wildcard *~)
exe := $(wildcard */*.exe) $(wildcard *.exe)
obj := $(wildcard */*.o) $(wildcard *.o) $(wildcard */*.so) $(wildcard */*.pcm) $(wildcard */*.d)

clean:
	@echo cleaning dir...
	rm -f $(exe) $(obj) $(tilde)