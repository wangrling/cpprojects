add_executable(windows windows.cpp glad.c)
target_link_libraries(windows -lglfw3 -ldl -lGL -lX11 -lpthread -lm)