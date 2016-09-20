# Makefile to generate MSP430 binary
PROGRAM=ComputerLEDController
CC:=$(MSP430_UTILS)/msp430-gcc
DEBUG:=$(MSP430_UTILS)/mspdebug

# Directories
OBJ_DIR=$(BUILD_DIR)/obj
BIN_DIR=$(BUILD_DIR)/bin
W_OBJ_DIR=$(BUILD_DIR)\obj
W_BIN_DIR=$(BUILD_DIR)\bin
BUILD_DIR=build
SRC_DIR=src
INC_DIR=include
SUPPORT_DIR=support_files

# Flags
ifeq ($(OS),Windows_NT)
	CFLAGS:= -mmcu=msp430g2553 -c -O0 -g3 -ggdb -gdwarf-2 -Wall -Werror -Wextra -Wshadow -std=gnu90 -MMD -I$(INC_DIR)
	LDFLAGS:= -mmcu=msp430g2553
else
	CFLAGS:= -mmcu=msp430g2553 -c -O0 -g3 -ggdb -gdwarf-2 -Wall -Werror -Wextra -Wshadow -std=gnu90 -MMD -I$(INC_DIR) -I$(SUPPORT_DIR)
	LDFLAGS:= -L $(SUPPORT_DIR) -mmcu=msp430g2553
endif

# Files
SRC:=$(wildcard $(SRC_DIR)/*.c)
OBJ:=$(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRC)))
ELF:=$(BIN_DIR)/$(PROGRAM).elf
DEP:=$(OBJ:.o=.d)

# Rules
.PHONY: setup
ifeq ($(OS),Windows_NT)
setup:
	if not exist $(W_OBJ_DIR) mkdir $(W_OBJ_DIR)
	if not exist $(W_BIN_DIR) mkdir $(W_BIN_DIR)
else
setup:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)
endif

.PHONY: all
all: setup $(ELF)

$(ELF): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

-include $(DEPS)

.PHONY: debug
ifeq ($(OS),Windows_NT)
debug:
	$(DEBUG) tilib
else
debug:
	mspdebug rf2500
endif
