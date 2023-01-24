#pragma once

#include <iostream>

#define RED			"\033[0;31m"
#define GREEN		"\033[0;32m"
#define YELLOW		"\033[0;33m"
#define BLUE		"\033[0;34m"
#define PURPLE		"\033[0;35m"
#define CYAN		"\033[0;36m"
#define WHITE		"\033[0;37m"
#define WHITE_END	"\033[0;37m\n"

#define Success		GREEN "Success: "
#define Warning		YELLOW "Warning: " 
#define Error		RED "Error: " 
#define Display		WHITE "Display: "

#define CONSOLE_LOG(color,message,...) printf(color message WHITE_END,__VA_ARGS__);

#define EXIT_SUCCESS 0
#define EXIT_FAILED -1