g++ ./src/main.cpp ./src/implementation/*.cpp -DSFML_STATIC -I"C:/Program Files/SFML-2.5.1/include" -I"./src/include" -I"./src/headers" -o ./src/build/main -L"C:/Program Files/SFML-2.5.1/lib" -lsfml-graphics -lsfml-window -lsfml-system -mwindows
start ./src/build/main.exe
pause