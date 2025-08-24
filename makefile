.PHONY: all clear

######################	Cap 1	######################
SRCS_cap1 := $(wildcard src/Cap1/*.c src/Cap1/*.cpp)

OBJS_cap1 := $(SRCS_cap1:.c=.o)
OBJS_cap1 := $(OBJS_cap1:.cpp=.o)
OBJS_cap1 := $(patsubst src/%.o,bin/%.o,$(OBJS_cap1))
.INTERMEDIATE: $(OBJS_cap1)

EXES_cap1 = bin/Cap1/listing1.1


all: $(EXES_cap1)

$(EXES_cap1): $(OBJS_cap1)
	g++ $(OBJS_cap1) -o $@

bin/%.o: src/%.c
	@mkdir -p $(dir $@)
	gcc -c $< -o $@

bin/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	g++ -c $< -o $@

clean:
	rm -rf bin/*






# bin/cap1/program: bin/cap1/program.o
# 	gcc bin/cap1/program.o -o bin/cap1/program
# 	rm -f bin/cap1/program.o

# bin/cap1/program.o: src/cap1/program1.c
# 	@mkdir -p $(dir $@)
# 	gcc -c $< -o $@

# SRCS := $(wildcard src/*/*.c)
# EXES := $(patsubst src/%/%.c,bin/%/%,$(SRCS))

# all: $(EXES)

# bin/%/%: src/%/%.c
# 	@mkdir -p $(dir $@)        
# 	gcc -c $< -o $@

