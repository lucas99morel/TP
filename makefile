.PHONY: all clear
.SILENT:
all: cap1 cap2 cap3 #make all

######################	Cap 1	######################
SRCS_cap1 := $(wildcard src/Cap1/*.c src/Cap1/*.cpp)

OBJS_cap1 := $(SRCS_cap1:.c=.o)
OBJS_cap1 := $(OBJS_cap1:.cpp=.o)
OBJS_cap1 := $(patsubst src/%.o,bin/%.o,$(OBJS_cap1))
.INTERMEDIATE: $(OBJS_cap1)

EXES_cap1 = bin/Cap1/listing1.1


cap1 listing1.1 listing1.2: $(EXES_cap1)

$(EXES_cap1): $(OBJS_cap1)
	g++ $(OBJS_cap1) -o $@

######################	Cap 2	######################
SRCS_cap2 := $(wildcard src/Cap2/*.c)
Cap2 := $(patsubst src/Cap2/%.c,%,$(SRCS_cap2))

cap2: $(Cap2)

listing2.%: bin/Cap2/listing2.%.o
	if [ "$@" != "listing2.7" ] && [ "$@" != "listing2.8" ]; then \
		exe_name=$$(basename $< .o); \
		gcc $< -o $(dir $<)/$$exe_name; \
	else \
		if [ "$@" = "listing2.7" ]; then \
			gcc -c src/Cap2/listing2.8.c -o $(dir $<)/listing2.8.o; \
		elif [ "$@" = "listing2.8" ]; then \
			gcc -c src/Cap2/listing2.7.c -o $(dir $<)/listing2.7.o; \
		fi; \
		ar cr $(dir $<)/libtest.a $(dir $<)/listing2.7.o $(dir $<)/listing2.8.o; \
		gcc -o $(dir $<)listing2.8 $(dir $<)listing2.8.o -L$(dir $<) -ltest; \
		rm -f $(dir $<)/*.o $(dir $<)/*.a; \
	fi

######################	Cap 3	######################
SRCS_cap3 := $(wildcard src/Cap3/*.c)
Cap3 := $(patsubst src/Cap3/%.c,%,$(SRCS_cap3))

cap3: $(Cap3)

listing3.%: bin/Cap3/listing3.%.o
	exe_name=$$(basename $< .o); \
	gcc $< -o $(dir $<)/$$exe_name

######################	ReglasGenerales	######################

bin/%.o: src/%.c
	@mkdir -p $(dir $@)
	gcc -c $< -o $@

bin/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	g++ -c $< -o $@

clean:
	rm -rf bin/*

