CC := gcc
SRC := ./src
INC := ./inc
OUT := ./out

Cflags := -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -I$(INC)

OBJflags := -I$(SRC) -c
OBJS := $(addprefix $(OUT)/, country.o country_arr.o)

debug : Cflags += -g
debug : clean
debug : app.exe

app.exe : $(OBJS) $(addprefix $(OUT)/, main.o menu.o)
	$(CC) $^ -o $@

statistics.exe : $(OBJS) $(addprefix $(OUT)/, get_statistics.o)
	$(CC) $^ -o $@

$(OUT)/%.o : $(SRC)/%.c $(INC)/*.h
	mkdir $(OUT) 2> /dev/null || true
	$(CC) $(Cflags) $(OBJflags) $< -o $@

clean :
	rm -rf $(OUT) 2> /dev/null || true