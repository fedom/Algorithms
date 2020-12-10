CC = g++
RM = rm

CXXFLAGS = -g -Wall -std=c++11 -MMD -I../../
LDFLAGS =
LIBS = 

SRCS = $(wildcard *.cpp ../../common/*.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SRCS))
DEPS = $(patsubst %.cpp, %.d, $(SRCS))

TARGET = test

.PHONY:all
all:$(TARGET)
	
$(TARGET) : $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

$(OBJS) : %.o : %.cpp
	$(CC) $(CXXFLAGS) -o $@ -c $<


.PHONY:clean
clean:
	@$(RM) -rf $(OBJS) $(TARGET) $(DEPS)

-include $(DEPS)
