CC := gcc
SRC := ./src
INC := ./inc
OUT := ./out

Cflags := -std=gnu99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -I$(INC)

OBJflags := -I$(SRC) -c
OBJS := $(addprefix $(OUT)/, static_stack.o list_stack.o operation.o io.o)

debug : Cflags += -g
debug : clean
debug : app.exe

app.exe : $(OBJS) $(addprefix $(OUT)/, main.o)
	$(CC) $^ -o $@

# statistics.exe : $(OBJS) $(addprefix $(OUT)/, get_statistics.o)
# 	$(CC) $^ -o $@

$(OUT)/%.o : $(SRC)/%.c $(INC)/*.h
	mkdir $(OUT) 2> /dev/null || true
	$(CC) $(Cflags) $(OBJflags) $< -o $@

clean :
	rm -rf $(OUT) 2> /dev/null || true