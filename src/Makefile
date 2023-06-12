.PHONY: all build install uninstall rebuild dist test gcov_report clean
OS :=$(shell uname -s)
GC=gcc
CFLAGS=-std=c11 -Wall -Wextra -Werror -g
TEST=Tests/test
SPEC=special
GCOV=--coverage
SANI=-fsanitize=address -g
#  цвета
BLUE=\033[96m
RED=\033[91m
END=\033[0m

ifeq ($(OS), Darwin)
	FLAGS_PLATFORM =-lcheck
else
	FLAGS_PLATFORM =-lcheck -lsubunit -lrt -lm -lpthread -g
endif

all : clean viewer.a

install: clean viewer.a
ifeq ("", "$(wildcard Build)")
	@mkdir Build
else
	@rm -rf Build/*
endif
	@echo "$(BLUE)-----------------INSTALL-----------------$(END)"
	@cd Front/3D_Viewer && qmake && make &> /dev/null && make clean &> /dev/null && rm Makefile && cd ../../ && mv Front/3D_Viewer/3D_Viewer.app Build
	@echo "$(BLUE)-----------------------------------------$(END)"

uninstall: 
	@echo "$(BLUE)----------------UNINSTALL----------------$(END)"
	@make clean &> /dev/null
	@rm -rf Build
	@echo "$(BLUE)-----------------------------------------$(END)"

clean :
	@echo "$(BLUE)------------------CLEAN------------------$(END)"
	@rm -rf *.{a,o,dSYM,out,g*} */*.{a,o,dSYM,out,g*} report test.info gcov f test main

dist: install
	@echo "$(BLUE)--------------DISTRIBUTIVE---------------$(END)"
ifeq ("", "$(wildcard Dist_3D_Viewer)")
	@rm -rf Dist_3D_Viewer/
endif
	@mkdir Dist_3D_Viewer/
	@mkdir Dist_3D_Viewer/src
	@mv ./Build/3D_Viewer.app Dist_3D_Viewer/src/
	@tar cvzf Dist_3D_Viewer.tgz Dist_3D_Viewer/ &>/dev/null
	@rm -rf Dist_3D_Viewer/
	@rmdir Build
	@echo "$(BLUE)-----------------------------------------$(END)"

# dvi: 
# 	@echo "$(BLUE)-------------------DVI-------------------$(END)"
# 	@open README.txt
# 	@echo "$(BLUE)-----------------------------------------$(END)"

test : clean viewer.a $(TEST).o
	@echo "$(BLUE)--------------RUNNING TESTS--------------$(END)"
	@$(GC) $(CFLAGS) $(TEST).o -l check -L. viewer.a $(FLAGS_PLATFORM) -o test
	@./test 
	@echo "$(BLUE)-----------------------------------------$(END)"

$(TEST).o : $(TEST).c
	@$(GC) $(CFLAGS) -c $(TEST).c -o $(TEST).o

# библиотека для теста

viewer.a : modules/*.c 
	@echo "$(BLUE)---------------JUST LIBRARY--------------$(END)"
	@$(GC) -g -c modules/*.c 
	@ar rc viewer.a *.o
	@ranlib viewer.a

#gcov
gcov_report : clean lcov $(TEST).o gviewer.a
	@echo "$(BLUE)---------------GCOV REPORT---------------$(END)"
	@$(GC) $(CFLAGS) $(GCOV) $(TEST).o -l check -L. viewer.a $(FLAGS_PLATFORM) -o gcov
	@./gcov gviewer.a 
	@gcov gviewer.a
# ~/goinfre/homebrew/bin/
	@lcov -t "test" -o test.info -c -d . 
	@genhtml -o report test.info 
	@open report/index.html 
	@echo "$(BLUE)-----------------------------------------$(END)"

# библиотека для отчета
gviewer.a : modules/*.c
	@echo "$(BLUE)---------------JUST LIBRARY--------------$(END)"
	@$(GC) $(GCOV) -g -c modules/*.c
	@ar rc viewer.a *.o
	@ranlib viewer.a

# проверки lcov и brew
lcov:
ifeq ("", "$(wildcard ~/goinfre/homebrew/bin/lcov)")
	$(error Need to install lcov: make lcov_install)
endif

lcov_install :  brew
	@brew install lcov

brew:
ifeq ("", "$(wildcard ~/goinfre/homebrew)")
	@git clone https://github.com/Homebrew/brew ~/goinfre/homebrew
	@echo "$(RED)Выполните eval \"\$$(/opt/goinfre/*/homebrew/bin/brew shellenv)\"$(END)"
#   curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
endif

valgrind: clean f
	@echo "$(BLUE)----------------VALGRIND-----------------$(END)"
	@CK_FORK=no valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose --log-file=valgrind.txt ./main
	@echo "$(BLUE)-----------------------------------------$(END)"

check: 
	@echo "$(BLUE)------------------CHECK------------------$(END)"
	@cp ../materials/linters/.clang-format .clang-format && cp ../materials/linters/.clang-format ../tests/.clang-format
#	@clang-format -style=Google -i *.h *.c ../tests/*.c
	@clang-format -style=Google -n *.h *.c ../Tests/*.c
	@rm .clang-format && rm ../Tests/.clang-format
	@echo "$(BLUE)-----------------------------------------$(END)"

out: main
	@echo "$(BLUE)----------------EXECUTING----------------$(END)"
	@./main 1>1.txt # 2>2.txt
	@echo "$(BLUE)-----------------------------------------$(END)"

# мой мейник
main : clean main.o viewer.a
	@echo "$(BLUE)---------------COMPILATION---------------$(END)"
	@$(GC) $(CFLAGS) $(SANI) main.o -L. viewer.a  $(FLAGS_PLATFORM) -o main

main.o : main.c
	@$(GC) $(CFLAGS) $(SANI) -c main.c

