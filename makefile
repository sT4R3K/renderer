SYSCONF_LINK = g++
CPPFLAGS     =
LDFLAGS      =
LIBS         =

TEST_DIR = test/
SRC_DIR = src/
BUILD_DIR = build/
DEST_DIR = bin/
TARGET  = a.out

OBJECTS := $(patsubst $(SRC_DIR)%.cpp,%.o,$(wildcard $(SRC_DIR)*.cpp))
DIR_OBJECTS := $(addprefix $(BUILD_DIR), $(OBJECTS))

export

OBJS: $(TARGET)

$(TARGET): $(OBJECTS)
	$(SYSCONF_LINK) -Wall $(LDFLAGS) -o $(DEST_DIR)$(TEST_FILE).out $(DIR_OBJECTS) $(BUILD_DIR)$(TEST_FILE).o $(LIBS)

$(OBJECTS): %.o: $(SRC_DIR)%.cpp
	$(SYSCONF_LINK) -Wall $(CPPFLAGS) -c $(CFLAGS) $< -o $(BUILD_DIR)$@

ifneq ($(MAKECMDGOALS),OBJS)
%::
		$(SYSCONF_LINK) -Wall $(CPPFLAGS) -c $(CFLAGS) $(TEST_DIR)$*.cpp -o $(BUILD_DIR)$*.o
		$(eval TEST_FILE = $*)
		@$(MAKE) --no-print-directory OBJS
endif

clean:
	-rm -f $(BUILD_DIR)*.o
	-rm -f $(DEST_DIR)*.out