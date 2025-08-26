.PHONY: all clear
all: cap1 cap2 #make all

######################	Cap 1	######################
SRCS_cap1 := $(wildcard src/Cap1/*.c src/Cap1/*.cpp)

OBJS_cap1 := $(SRCS_cap1:.c=.o)
OBJS_cap1 := $(OBJS_cap1:.cpp=.o)
OBJS_cap1 := $(patsubst src/%.o,bin/%.o,$(OBJS_cap1))
.INTERMEDIATE: $(OBJS_cap1)

EXES_cap1 = bin/Cap1/listing1.1


cap1 listing1.1.c listing1.2.cpp: $(EXES_cap1)

$(EXES_cap1): $(OBJS_cap1)
	g++ $(OBJS_cap1) -o $@

######################	Cap 2	######################
SRCS_cap2 := $(wildcard src/Cap2/*.c)

OBJS_cap2 := $(SRCS_cap2:.c=.o)
OBJS_cap2 := $(patsubst src/%.o,bin/%.o,$(OBJS_cap2))
.INTERMEDIATE: $(OBJS_cap2)

Cap2 := $(patsubst src/Cap2/%,%,$(SRCS_cap2))

cap2: $(Cap2)

listing2.%.c: bin/Cap2/listing2.%.o
	if [ "$@" != "listing2.7.c" ] && [ "$@" != "listing2.8.c" ]; then \
		exe_name=$$(basename $< .o); \
		gcc $< -o $(dir $<)/$$exe_name; \
	else \
		if [ "$@" = "listing2.7.c" ]; then \
			gcc -c src/Cap2/listing2.8.c -o $(dir $<)/listing2.8.o; \
		elif [ "$@" = "listing2.8.c" ]; then \
			gcc -c src/Cap2/listing2.7.c -o $(dir $<)/listing2.7.o; \
		fi; \
		ar cr $(dir $<)/libtest.a $(dir $<)/listing2.7.o $(dir $<)/listing2.8.o; \
		gcc -o $(dir $<)listing2.8 $(dir $<)listing2.8.o -L$(dir $<) -ltest; \
		rm -f $(dir $<)/*.o $(dir $<)/*.a; \
	fi

######################	ReglasGenerales	######################

bin/%.o: src/%.c
	@mkdir -p $(dir $@)
	gcc -c $< -o $@

bin/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	g++ -c $< -o $@

clean:
	rm -rf bin/*

