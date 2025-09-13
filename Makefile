NAME     := webserv
CXX      := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98

SRC_DIR  := srcs
OBJ_DIR  := obj

SRCS     := $(SRC_DIR)/main.cpp

OBJS     := $(OBJ_DIR)/main.o

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)
	@rm -f leaks.out

re: fclean all

leaks:
	$(CXX) $(CXXFLAGS) -fsanitize=address -g $(SRCS) -o leaks.out
	./leaks.out