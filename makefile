CC          := gcc
DBG         := gdb -q
CFLAGS      := -Ofast
CDBGFLAGS   := -Wall -g -ggdb

LIB         := -lm# -lfl

SRCEXT      := c
OBJEXT      := o

SRC_DIR     := src
CSRC_DIR    := $(SRC_DIR)/csrc
BIN_DIR     := bin

TARGET      := $(BIN_DIR)/compiler
DBG_TARGET  := $(BIN_DIR)/compiler-dbg

LEXER 		:= $(SRC_DIR)/lexer.l.c
PARSER		:= $(SRC_DIR)/parser.y.c

SOURCES     := $(CSRC_DIR)/lexer.c $(CSRC_DIR)/parser.c
OBJDIRS     := $(patsubst $(CSRC_DIR)%, $(BIN_DIR)%, $(shell dirname $(SOURCES)))

## release build

OBJECTS     := $(patsubst $(CSRC_DIR)/%.$(SRCEXT), $(BIN_DIR)/%.$(OBJEXT), $(SOURCES))

all: mkdirp $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) $(LIB)

$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) -c $(patsubst $(BIN_DIR)/%.$(OBJEXT), $(CSRC_DIR)/%.$(SRCEXT), $@) -o $@

## debug build

DBG_OBJECTS  := $(patsubst $(CSRC_DIR)/%.$(SRCEXT), $(BIN_DIR)/%-dbg.$(OBJEXT), $(SOURCES))

dbg: mkdirp $(DBG_TARGET)

$(DBG_TARGET): $(DBG_OBJECTS)
	$(CC) $(CDBGFLAGS) $(DBG_OBJECTS) -o $(DBG_TARGET) $(LIB)

$(DBG_OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) -c $(patsubst $(BIN_DIR)/%-dbg.$(OBJEXT), $(CSRC_DIR)/%.$(SRCEXT), $@) -o $@

# flex and bison

$(SOURCES): $(LEXER) $(PARSER)
	flex -o $(CSRC_DIR)/lexer.c $(LEXER)
	bison -d -o $(CSRC_DIR)/parser.c $(PARSER)

## execution

run: $(TARGET)
	./$(TARGET)

rundbg: $(DBG_TARGET)
	gdb -q $(DBG_TARGET)

## mkdirp

mkdirp:
	@mkdir -p $(CSRC_DIR)
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJDIRS)

## Clean

clean:
	@rm -rf $(OBJECTS)
	@rm -rf $(DBG_OBJECTS)
	@rm -rf $(CSRC_DIR)/*

cleaner:
	@rm -rf $(CSRC_DIR)/*
	@rm -rf $(BIN_DIR)/*
