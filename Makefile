all:
	g++ src/*.cpp src/*/*.cpp src/vendor/stb_image/*.cpp -o bin/main -lglfw -lGL -lGLEW -lX11 -lpthread -lXrandr -lXi
clean:
	rm ./bin/* 
