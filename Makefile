NAME			=	ft_containers

CXX				=	clang++
CXXFLAGS		=	-Wall -Werror -Wextra -std=c++98 -g #-fsanitize=address
LDFLAGS			=	

SRC_DIR			= 	tests
INC_DIR			=	includes
OBJ_DIR			=	objs
DEPS_DIR		=	deps
TESTS_OUTPUT	= 	bin

LIBS			=	

###############################################################################
##								Source files								 ##
###############################################################################

MAP					=	map_tests.cpp
MAP_SRCS			=   $(addprefix $(SRC_DIR)/map/, $(MAP))
MAP_OBJS			=   $(addprefix $(OBJ_DIR)/map., $(subst /,., $(MAP:.cpp=.o)))

STACK				=	stack_tests.cpp
STACK_SRCS			=   $(addprefix $(SRC_DIR)/stack/, $(STACK))
STACK_OBJS			=   $(addprefix $(OBJ_DIR)/stack., $(subst /,., $(STACK:.cpp=.o)))

VECTOR				=
VECTOR_SRCS			=   $(addprefix $(SRC_DIR)/vector/, $(VECTOR))
VECTPR_OBJS			=   $(addprefix $(OBJ_DIR)/vector., $(subst /,., $(VECTOR:.cpp=.o)))

UTILS				=	randomValue.cpp MyClass.cpp# utils.cpp 
UTILS_SRCS			=   $(addprefix $(SRC_DIR)/, $(UTILS))
UTILS_OBJS			=   $(addprefix $(OBJ_DIR)/, $(subst /,., $(UTILS:.cpp=.o)))

MAIN				=	main.cpp
MAIN_SRCS			=   $(addprefix $(SRC_DIR)/, $(MAIN))
MAIN_OBJS			=   $(addprefix $(OBJ_DIR)/, $(subst /,., $(MAIN:.cpp=.o)))

SRCS				=	$(MAIN_SRCS) $(MAP_SRCS) $(UTILS_SRCS) $(STACK_SRCS) $(VECTOR_SRCS)
OBJS				= 	$(MAIN_OBJS) $(MAP_OBJS) $(UTILS_OBJS) $(STACK_OBJS) $(VECTOR_OBJS)

###############################################################################
##							Color output char								 ##
###############################################################################
BLUE			=\033[0;34m
NC				=\033[0m
LIGHT_PURPLE	=\033[1;35m
GREEN			=\033[0;32m
RED				=\033[0;31m

###############################################################################
## 							Mandatory recipes								 ##
###############################################################################

all: $(NAME)

include $(DEPS_DIR)/dependencies.d

$(NAME): $(OBJ_DIR) $(LIBS) $(OBJS)
	printf "$(BLUE)Linking $(LIGHT_PURPLE)$(NAME) $(BLUE)executable$(NC)\n"
	$(CXX) -I $(INC_DIR) $(OBJS) $(LIBS) $(LDFLAGS) $(CXXFLAGS) -o $(NAME)
	printf "$(GREEN)Completed$(NC)\n"

clean:
	printf "$(RED)Removing objects files$(NC)\n"
	rm -rf objs
	rm -rf *.o;

fclean: clean
	printf "$(RED)Removing $(LIGHT_PURPLE)$(NAME) \
	$(RED)executable\nRemoving libraries$(NC)\n"	
	rm -rf $(NAME)
	rm -rf $(LIBS)

re: fclean
	make all

###############################################################################
## 								Extra recipes								 ##
###############################################################################

define COMPILE
	$(foreach source,$(filter-out %.hpp,$^), \
	printf "$(LIGHT_PURPLE)$(subst $(SRC_DIR)/,,$(source))\
$(NC)\n"; \
	$(CXX) -I $(INC_DIR) $(CXXFLAGS) -c $(source) -o \
$(addprefix $(OBJ_DIR)/, $(subst /,.,$(subst $(SRC_DIR)/,,$(source:.cpp=.o)))) ;)
endef

ffclean: fclean
	printf "$(RED)Removing $(LIGHT_PURPLE)dependencies$(NC)\n"
	rm -rf deps

$(SRCS): $(addprefix $(INC_DIR)/, $(HEADERS))

dependencies: $(DEPS_DIR)/dependencies.d

debug: CXXFLAGS = -std=c++98 -g 
debug: all

$(DEPS_DIR)/dependencies.d: $(SRCS)
	printf "$(GREEN)Generating $(LIGHT_PURPLE)dependencies$(GREEN) file$(NC)\n"
	mkdir -p $(DEPS_DIR)
	$(foreach source,$(SRCS),\
	echo "$(subst $(SRC_DIR).,$(OBJ_DIR)/,$(subst /,.,$(dir $(source))))`\
$(CXX) -I $(INC_DIR) $(CXXFLAGS) $(source) -MM`\n\t \$$(COMPILE)"\
	> $(DEPS_DIR)/$(subst /,.,$(subst srcs/,,$(source:.cpp=.d)));)
	cd $(DEPS_DIR)&& cat `ls | grep -v dependencies.d` > dependencies.d

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TESTS_OUTPUT):
	mkdir -p $(TESTS_OUTPUT)

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

map_test: CXXFLAGS+=-D STANDALONE -D BSTTEST
map_test: $(OBJ_DIR) $(TESTS_OUTPUT) $(UTILS_SRCS) $(UTILS_OBJS) $(MAP_SRCS) $(MAP_OBJS)
	printf "$(BLUE)Linking $(LIGHT_PURPLE)$@ $(BLUE)executable$(NC)\n"	
	$(CXX) -I $(INC_DIR) $(MAP_OBJS) $(UTILS_OBJS) $(LIBS) $(LDFLAGS) $(CXXFLAGS) -o $(TESTS_OUTPUT)/$@
	printf "$(GREEN)Completed$(NC)\n"

stack_test: CXXFLAGS+=-D STANDALONE
stack_test: $(OBJ_DIR) $(TESTS_OUTPUT) $(UTILS_SRCS) $(UTILS_OBJS) $(STACK_SRCS) $(STACK_OBJS)
	printf "$(BLUE)Linking $(LIGHT_PURPLE)$@ $(BLUE)executable$(NC)\n"
	$(CXX) -I $(INC_DIR) $(STACK_OBJS) $(UTILS_OBJS)  $(LIBS) $(LDFLAGS) $(CXXFLAGS) -o $(TESTS_OUTPUT)/$@
	printf "$(GREEN)Completed$(NC)\n"

vector_test: CXXFLAGS+=-D STANDALONE
vector_test: $(OBJ_DIR)  $(UTILS_SRCS) $(UTILS_OBJS) $(VECTOR_SRCS) $(VECTOR_OBJS)
	printf "$(BLUE)Linking $(LIGHT_PURPLE)$@ $(BLUE)executable$(NC)\n"
	$(CXX) -I $(INC_DIR) $(VECTOR_OBJS) $(LIBS) $(LDFLAGS) $(CXXFLAGS) -o $(TESTS_OUTPUT)/$@
	printf "$(GREEN)Completed$(NC)\n"

.PHONY: rbt_test
.SILENT:

commit_all_files: ffclean
	git add .
	git commit