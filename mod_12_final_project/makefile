TARGET = bin/final
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

run: clean default
# 	./$(TARGET) -n -f ./magic_file
	./$(TARGET) -n -f ./magic_db.db 
	./$(TARGET) -f ./magic_db.db -a "Matthew_Roloff,1234_w_herc,47"
	./$(TARGET) -f ./magic_db.db -a "Bob Hercule,SW riley 4428,91"
	./$(TARGET) -f ./magic_db.db -r "Bob Hercule"
	./$(TARGET) -f ./magic_db.db -a "Ned Flanders,SW riley 4428,91"
	./$(TARGET) -f ./magic_db.db -r "Matthew_Roloff"
	./$(TARGET) -f ./magic_db.db -l

default: $(TARGET)

clean:
	rm -f obj/*.o
	rm -f bin/*
	rm -f *.db

$(TARGET): $(OBJ)
	gcc -o $@ $?

obj/%.o : src/%.c
	gcc -c $< -o $@ -Iinclude