ECHO := @

CC := $(ECHO)g++
CFLINKS := -pthread -lgdi32 -luser32 -lpthread
CEFLAGS_DEBUG := -pthread -mwindows -lm -std=c++11 -O2 -Wall -W -Wextra -Wdouble-promotion -pedantic -Wmissing-include-dirs -Wunused -Wuninitialized -Wextra -Wstrict-overflow=3 -Wtrampolines -Wfloat-equal -Wconversion -Wmissing-field-initializers -Wno-multichar -Wpacked -Winline -Wshadow
CEFLAGS_RELEASE := -pthread -mwindows -lm -std=c++11 -O3 -w
CEFLAGS := $(CEFLAGS_RELEASE)
EXAMPLES_FILES := $(wildcard ./examples/src/*.cpp)
EXAMPLES_FILES_LIST := $(addprefix ,$(notdir $(EXAMPLES_FILES:.cpp=)))
EXAMPLES_OBJ_FILES := $(addprefix ./examples/bin/,$(notdir $(EXAMPLES_FILES:.cpp=.o)))
EXAMPLES_EXE_FILES := $(addprefix ./examples/bin/,$(notdir $(EXAMPLES_FILES:.cpp=.exe)))
EXAMPLES_BUILT_FILES := $(addprefix ./examples/bin/,$(notdir $(wildcard ./examples/bin/*)))
EXAMPLES_NUMBER := $(words $(EXAMPLES_FILES))
EXAMPLES_MADE_NUMBER := %

CC_FLAGS=-I./include $(CEFLAGS)
LF_FLAGS=$(CFLINKS)

ifneq (,$(findstring run-example-,$(MAKECMDGOALS)))
RUN_EXAMPLE_NAME=$(subst run-example-,,$(MAKECMDGOALS))
RUN_EXAMPLE_PATH=./examples/bin/$(RUN_EXAMPLE_NAME).exe
ifneq ("$(wildcard $(RUN_EXAMPLE_PATH))","")
else
$(error Cannot run an example if the examples weren't built. Run 'make examples' command firstly)
endif
endif

ifneq (,$(filter clean clean-all,$(MAKECMDGOALS)))
ifeq (,$(EXAMPLES_BUILT_FILES))
$(error Directory is clean)
endif
endif


help:
	$(info WACCGL - Windows Advanced Console Componental Graphics Library)
	$(info Makefile)
	$(info To compile all examples use 'make all' or 'make examples' command)
	$(info To get list of all available examples use 'make run-example' command)
	$(info To run the specified example use 'make run-example-NAME' e.g. 'make run-example-demo')
	$(info To clean project use 'make clean' command)

clean: clean-all
	$(info Project cleaned. Done)

clean-all: clean-examples

all: examples

examples: examples_ $(EXAMPLES_OBJ_FILES) $(EXAMPLES_EXE_FILES) clean-examples-build
	$(info Examples compiled. Done)

examples_:
	$(info $(EXAMPLES_NUMBER) examples are available)

run-example:
	$(info All available examples: $(EXAMPLES_FILES_LIST))

run-example-%:
	$(ECHO)./examples/bin/$*.exe

clean-examples:
	$(ECHO)rm $(EXAMPLES_BUILT_FILES)

clean-examples-build:
	$(info Cleaning build)
	$(ECHO)rm $(EXAMPLES_OBJ_FILES)

./examples/bin/%.exe: ./examples/bin/%.o
	$(CC) $(LF_FLAGS) -o $@ $<

./examples/bin/%.o: ./examples/src/%.cpp
	$(info Compiling example: $<)
	$(CC) $(CC_FLAGS) -c -o $@ $<
