CC=g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR=build
TEMPLATE_DIR=.template

all: $(BUILD_DIR) utunes.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/handlers.o: handlers.cpp Exception.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp UTunes.hpp UTunes.cpp song.hpp playlist.hpp Exception.hpp user.hpp filter.hpp CSVReader.hpp recommendation.hpp
	$(CC) $(CF) -c handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/my_server.o: my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c my_server.cpp -o $(BUILD_DIR)/my_server.o

$(BUILD_DIR)/main.o: main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp Exception.hpp
	$(CC) $(CF) -c main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/CSVReader.o : CSVReader.hpp CSVReader.cpp 
	$(CC) -c CSVReader.cpp -o $(BUILD_DIR)/CSVReader.o

$(BUILD_DIR)/Exception.o : Exception.hpp Exception.cpp 
	$(CC) -c Exception.cpp -o $(BUILD_DIR)/Exception.o

$(BUILD_DIR)/song.o : song.hpp song.cpp Exception.hpp
	$(CC) -c song.cpp -o $(BUILD_DIR)/song.o

$(BUILD_DIR)/playlist.o : playlist.hpp playlist.cpp song.hpp Exception.hpp
	$(CC) -c playlist.cpp -o $(BUILD_DIR)/playlist.o

$(BUILD_DIR)/filter.o : filter.hpp filter.cpp song.hpp Exception.hpp
	$(CC) -c filter.cpp -o $(BUILD_DIR)/filter.o

$(BUILD_DIR)/user.o : user.hpp user.cpp song.hpp playlist.hpp Exception.hpp
	$(CC) -c user.cpp -o $(BUILD_DIR)/user.o

$(BUILD_DIR)/UTunes.o : UTunes.hpp UTunes.cpp song.hpp playlist.hpp Exception.hpp user.hpp filter.hpp CSVReader.hpp recommendation.hpp
	$(CC) -c UTunes.cpp -o $(BUILD_DIR)/UTunes.o

$(BUILD_DIR)/matrix.o : matrix.hpp matrix.cpp 
	$(CC) -c matrix.cpp -o $(BUILD_DIR)/matrix.o

$(BUILD_DIR)/recommendation.o : recommendation.cpp recommendation.hpp song.cpp user.hpp matrix.hpp
	$(CC) -c recommendation.cpp -o $(BUILD_DIR)/recommendation.o


utunes.out: $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/CSVReader.o $(BUILD_DIR)/Exception.o $(BUILD_DIR)/song.o $(BUILD_DIR)/playlist.o $(BUILD_DIR)/filter.o $(BUILD_DIR)/user.o $(BUILD_DIR)/UTunes.o $(BUILD_DIR)/recommendation.o $(BUILD_DIR)/matrix.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o
	$(CC) $(CF) $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/CSVReader.o $(BUILD_DIR)/Exception.o $(BUILD_DIR)/song.o $(BUILD_DIR)/playlist.o $(BUILD_DIR)/filter.o $(BUILD_DIR)/user.o $(BUILD_DIR)/UTunes.o $(BUILD_DIR)/recommendation.o $(BUILD_DIR)/matrix.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o -o utunes.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null
