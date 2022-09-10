# directories

SRCEXT      := c
OBJEXT      := o
HEADEREXT   := h

SRC_DIR     := src
BIN_DIR     := bin
EXAMPLE_DIR := examples

INCLUDE_DIR := $(SRC_DIR)/include
CSRC_DIR    := $(SRC_DIR)/csrc
YACC_DIR    := $(SRC_DIR)/yacc

TARGET      := $(BIN_DIR)/exe
DBG_TARGET  := $(BIN_DIR)/exe-dbg

LEXER       := $(SRC_DIR)/main.lex.c
PARSER      := $(SRC_DIR)/parser.yac.c

YACC_SRC    := $(YACC_DIR)/parser.c $(YACC_DIR)/lexer.c
CSOURCES    := $(shell find $(CSRC_DIR) | grep '\.'$(SRCEXT))

OBJDIRS     := $(patsubst $(CSRC_DIR)%, $(BIN_DIR)%, $(shell dirname $(CSOURCES))) $(BIN_DIR)/yacc

# compiler options

CC          := gcc
DBG         := gdb -q
CFLAGS      := -Ofast
CDBGFLAGS   := -Wall -g -ggdb

LIB         := -lm #-lfl

## release build

YACC_OBJ    := $(BIN_DIR)/yacc/lexer.o $(BIN_DIR)/yacc/parser.o
OBJECTS     := $(patsubst $(CSRC_DIR)/%.$(SRCEXT), $(BIN_DIR)/%.$(OBJEXT), $(CSOURCES))

all: mkdirp $(TARGET)

$(TARGET): $(OBJECTS) $(YACC_OBJ)
	$(CC) $(CFLAGS) $(OBJECTS) $(YACC_OBJ) -o $(TARGET) $(LIB)

$(OBJECTS): $(CSOURCES)
	$(CC) $(CFLAGS) -c $(patsubst $(BIN_DIR)/%.$(OBJEXT), $(CSRC_DIR)/%.$(SRCEXT), $@) -o $@

$(YACC_OBJ): $(YACC_SRC)
	$(CC) $(CFLAGS) -c $(patsubst $(BIN_DIR)/yacc/%.$(OBJEXT), $(YACC_DIR)/%.$(SRCEXT), $@) -o $@

## debug build

YACC_DBG_OBJ := $(BIN_DIR)/yacc/lexer-dbg.o $(BIN_DIR)/yacc/parser-dbg.o
DBG_OBJECTS  := $(patsubst $(CSRC_DIR)/%.$(SRCEXT), $(BIN_DIR)/%-dbg.$(OBJEXT), $(CSOURCES))

dbg: mkdirp $(DBG_TARGET)

$(DBG_TARGET): $(DBG_OBJECTS) $(YACC_DBG_OBJ)
	$(CC) $(CDBGFLAGS) $(DBG_OBJECTS) $(YACC_DBG_OBJ) -o $(DBG_TARGET) $(LIB)

$(DBG_OBJECTS): $(CSOURCES)
	$(CC) $(CDBGFLAGS) -c $(patsubst $(BIN_DIR)/%-dbg.$(OBJEXT), $(CSRC_DIR)/%.$(SRCEXT), $@) -o $@

$(YACC_DBG_OBJ): $(YACC_SRC)
	$(CC) $(CDBGFLAGS) -c $(patsubst $(BIN_DIR)/yacc/%-dbg.$(OBJEXT), $(YACC_DIR)/%.$(SRCEXT), $@) -o $@

# flex and bison

$(YACC_SRC): $(LEXER) $(PARSER)
	flex -o $(YACC_DIR)/lexer.c $(LEXER)
	bison -d -o $(YACC_DIR)/parser.c $(PARSER)

## execution

run: $(TARGET)
	./$(TARGET)

rundbg: $(DBG_TARGET)
	gdb -q $(DBG_TARGET)

## mkdirp

mkdirp:
	@mkdir -p $(YACC_DIR)
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJDIRS)

## Clean

clean:
	@rm -rf $(OBJECTS)
	@rm -rf $(YACC_OBJ)
	@rm -rf $(DBG_OBJECTS)
	@rm -rf $(YACC_DBG_OBJ)

cleaner:
	@rm -rf $(BIN_DIR)/*
	@rm -rf $(YACC_DIR)/*$(SRCEXT)
	@rm -rf $(YACC_DIR)/*$(HEADEREXT)
