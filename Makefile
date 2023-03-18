NAME		=	ft_containers
STD_NAME	=	std_containers

CXX			=	c++
CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98

SRC_DIR			=	tests
INC_DIR			=	includes
OBJ_DIR			=	objs
DEPS_DIR		=	deps

RAW_SRCS	=	MyClass.cpp main.cpp map/map_tests.cpp randomValue.cpp stack/stack_tests.cpp vector/vector_tests.cpp
SRCS		=	$(addprefix $(SRC_DIR)/,$(RAW_SRCS))
FT_OBJS		=	$(addprefix	$(OBJ_DIR)/,$(subst /,.,$(RAW_SRCS:.cpp=.o)))
STD_OBJS	=	$(addprefix	$(OBJ_DIR)/,$(subst /,.,$(RAW_SRCS:.cpp=.std.o)))
# OBJS		=	$(addprefix	$(OBJ_DIR)/,$(FT_OBJS)) $(addprefix	$(OBJ_DIR)/,$(STD_OBJS))
# FT_DEPS		=	$(addprefix $(DEPS_DIR)/,$(subst /,.,$(SRCS:.cpp=.d)))
FT_DEPS		=	$(addprefix $(DEPS_DIR)/,$(subst /,.,$(SRCS:.cpp=.d)))
STD_DEPS	=	$(addprefix $(DEPS_DIR)/,$(subst /,.,$(SRCS:.cpp=.std.d)))
DEPS		=	$(FT_DEPS) $(STD_DEPS)

define COMPILE
	$(foreach source,$(filter-out %.hpp,$^), \
	$(CXX) -I $(INC_DIR) $(CXXFLAGS) -c $(source) -o $(addprefix $(OBJ_DIR)/,$(subst /,.,$(subst $(SRC_DIR)/,,$(source:.cpp=.o)))))
endef

define COMPILE_STD
	$(foreach source,$(filter-out %.hpp,$^), \
	$(CXX) -I $(INC_DIR) $(CXXFLAGS) -D USING_STD -c $(source) -o $(addprefix $(OBJ_DIR)/,$(subst /,.,$(subst $(SRC_DIR)/,,$(source:.cpp=.std.o)))))
endef

all: $(NAME) $(STD_NAME)

include $(DEPS_DIR)/dependencies.d

$(NAME) : $(OBJ_DIR) $(FT_OBJS)
	$(CXX) -I $(INC_DIR) $(CXXFLAGS) $(FT_OBJS) -o $(NAME)

$(STD_NAME) : $(OBJ_DIR) $(STD_OBJS)
	$(CXX) -I $(INC_DIR) $(CXXFLAGS) -D USING_STD $(STD_OBJS) -o $(STD_NAME)

$(DEPS_DIR)/dependencies.d: $(DEPS_DIR)
	$(foreach source, $(SRCS), echo -n $(subst $(SRC_DIR).,,$(subst /,.,$(subst $(notdir $(source)),,$(source)))) > $(addprefix $(DEPS_DIR)/,$(subst /,.,$(source:.cpp=.d))) && $(CXX) $(CXXFLAGS) -I $(INC_DIR) -MM $(source) >> $(addprefix $(DEPS_DIR)/,$(subst /,.,$(source:.cpp=.d)));)
	$(foreach source, $(SRCS), echo -n $(subst $(SRC_DIR).,,$(subst /,.,$(subst $(notdir $(source)),,$(source)))) > $(addprefix $(DEPS_DIR)/,$(subst /,.,$(source:.cpp=.std.d))) && $(CXX) $(CXXFLAGS) -I $(INC_DIR) -D USING_STD -MM $(source) | sed s/\\.o/\\.std.o/g >> $(addprefix $(DEPS_DIR)/,$(subst /,.,$(source:.cpp=.std.d)));)
	$(foreach deps, $(FT_DEPS), echo -n $(OBJ_DIR)/ >> $(DEPS_DIR)/dependencies.d && cat $(deps) >> $(DEPS_DIR)/dependencies.d && echo \\t\$$\(COMPILE\)\\n >> $(DEPS_DIR)/dependencies.d;)
	$(foreach deps, $(STD_DEPS), echo -n $(OBJ_DIR)/ >> $(DEPS_DIR)/dependencies.d && cat $(deps) >> $(DEPS_DIR)/dependencies.d && echo \\t\$$\(COMPILE_STD\)\\n >> $(DEPS_DIR)/dependencies.d;)

$(DEPS_DIR):
	mkdir -p $(DEPS_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -f $(FT_OBJS) $(STD_OBJS)

fclean: clean
	rm -rf $(DEPS_DIR)
	rm -f $(NAME) $(STD_NAME)

re: fclean all

.PHONY: all clean fclean re