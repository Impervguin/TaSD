CC := gcc
SRC := ./src
INC := ./inc
OUT := ./out

Cflags := -std=gnu99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -I$(INC)

OBJflags := -I$(SRC) -c
OBJS := $(addprefix $(OUT)/, matrix.o vector.o multiplication.o std_matrix.o std_vector.o io.o)

debug : Cflags += -g
debug : clean
debug : app.exe

app.exe : $(OBJS) $(addprefix $(OUT)/, main.o matrix.o vector.o multiplication.o std_matrix.o std_vector.o io.o)
	$(CC) $^ -o $@

statistics.exe : $(addprefix $(OUT)/, get_statistics.o) $(OBJS)
	$(CC) $^ -o $@

$(OUT)/%.o : $(SRC)/%.c $(INC)/*.h
	mkdir $(OUT) 2> /dev/null || true
	$(CC) $(Cflags) $(OBJflags) $< -o $@

clean :
	rm -rf $(OUT) 2> /dev/null || true
