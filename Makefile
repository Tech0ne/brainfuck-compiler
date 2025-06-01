################
 #
 #    @
 #      @
 #  @ @ @
 #
 ################

SRC_DIR			=	./src/
OBJ_DIR			=	./obj/

HDR_DIR			=	./hdr/

BIN				=	brainfuck

BLACKLIST		=	wip todo

SRC				=	$(shell find $(SRC_DIR) $(foreach dir, $(BLACKLIST), -path "$(SRC_DIR)$(dir)/*" -prune -o) -type f -name '*.c' -print)
OBJ				=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

CC				=	gcc

CFLAGS			?=	-Wall -Wextra -Werror
CPPFLAGS		?=	-D_GNU_SOURCE -I$(HDR_DIR)

DEBUG_FLAGS		=	-O3 -g3

.PHONY:	all
all:	$(BIN)

.PHONY: dev
dev:
	@echo "[+] Starting dev session"
	@echo Makefile $(SRC) $(HDR) | tr ' ' '\n' | entr bash -c 'clear && echo "[+] Change detected, recompiling" && make --no-print-directory debug'

.PHONY: debug
debug:
	@make --no-print-directory CLAGS="$(CFLAGS) $(DEBUG_FLAGS)"

$(BIN):	$(OBJ)
	@echo "[+] Compiling $@"
	@$(CC) $(LDFLAGS) $(CPPFLAGS) $(CFLAGS) $(OBJ) -o $@

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c $(HDR)
	@mkdir -p $(@D)
	@echo ">> Compiling C object $@"
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

.PHONY:	clean
clean:
	@echo "[-] Clearing project"
	@rm -rf $(OBJ_DIR)
	@rm -f vgcore*
	@rm -f *.swp
	@rm -f *~

.PHONY:	fclean
fclean:	clean
	@echo "[-] Purging project"
	@rm -f $(PACK_FILE)
	@rm -f $(BIN)
