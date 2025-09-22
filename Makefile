NAME     := webserv
CXX      := c++
CXXPATH	 := -I./include/
CXXFLAGS := -Wall -Wextra -Werror -std=c++98 $(CXXPATH)

SRC_DIR  := srcs
OBJ_DIR  := obj

SRCS     := ./scrs/main.cpp

OBJS     := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)
	@rm -f leaks.out

re: fclean all

leaks:
	$(CXX) $(CXXFLAGS) -fsanitize=address -g $(SRCS) -o leaks.out
	./leaks.out
