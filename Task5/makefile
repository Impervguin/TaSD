CC := gcc
SRC := ./src
INC := ./inc
OUT := ./out

Cflags := -std=gnu99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -I$(INC)

OBJflags := -I$(SRC) -c
OBJS := $(addprefix $(OUT)/, static_queue.o randtimes.o list_queue.o io.o list.o)

debug : Cflags += -g
debug : clean
debug : app.exe

app.exe : $(OBJS) $(addprefix $(OUT)/, main.o)
	$(CC) $^ -o $@

statistics.exe : $(OBJS) $(addprefix $(OUT)/, get_statistics.o)
	$(CC) $^ -o $@

$(OUT)/%.o : $(SRC)/%.c $(INC)/*.h
	mkdir $(OUT) 2> /dev/null || true
	$(CC) -g $(Cflags) $(OBJflags) $< -o $@

clean :
	rm -rf $(OUT) 2> /dev/null || true