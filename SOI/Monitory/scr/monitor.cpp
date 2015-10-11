#include "monitor.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <queue>
#include <sstream>

#define BUFFER_SIZE 5

template <class T>
std::string toString(T var)
{
    std::stringstream buf;
    buf<<var;
    return buf.str();
}

class Message: public Monitor
{
public:

	void print(std::string str)
	{
		enter();
		std::cout<<str;
		leave();
	}
} Msg;

class UpdateProd: public Monitor
{
public:
	UpdateProd(): progressFactor(0) {};
	int increase(void)
	{
		int x;
		enter();
		x = progressFactor;
		progressFactor = (progressFactor + 1) % 10;
		leave();
		return x;
	}

private:
	int progressFactor;
};

UpdateProd facX, facY, facZ;

class Buffer: public Monitor
{
private:
	std::string name;
	int count;
	char buffer[BUFFER_SIZE];
	Condition full, empty;
	int first_full;
	int first_empty;
public:
	Buffer(std::string bufName): name(bufName), count(0), first_full(0), first_empty(0) {};

	void put(char item, int putTime)
	{
		enter();

		while(count == BUFFER_SIZE)
			wait(full);

		sleep(putTime);
		buffer[first_empty] = item;
		first_empty = (first_empty + 1) % BUFFER_SIZE;
		++count;

		std::string msg = "Element: " + toString(item) + " zostal wlozony do: " + toString(name) + ".\n";
		Msg.print(msg);

		if(count == 1)
			signal(empty);
		leave();
	} 

	char get()
	{
		char item;
		enter();

		while(count == 0)
			wait(empty);

		item = buffer[first_full];
		first_full = (first_full + 1) % BUFFER_SIZE;
		--count;

		std::string msg = "Element: " + toString(item) + " zostal wyjety z: " + toString(name) + ".\n";
		Msg.print(msg);

		if(count == BUFFER_SIZE - 1)
			signal(full);
		leave();
		return item;
	}
};

Buffer bufferX("buforX");
Buffer bufferY("buforY");
Buffer bufferZ("buforZ");

const bool PRODUCTION = true;

const int productX = 48;
const int productY = 97;
const int productZ = 48;

int maxTimeX;
int maxTimeY;
int maxTimeZ;

void * robotX(void *);
void * robotY(void *);
void * robotZ(void *);
void * robotCreator(void *);

int main(int argc, char* argv[])
{
	int requiredProducts = 10;

	int numberRobotX;
	int numberRobotY;
	int numberRobotZ;

	//setbuf(stdout, NULL);

	if(argc != 7)
	{
		std::cerr<<"Liczba argumentow jest niepoprawna.\n";
		return EXIT_FAILURE;
	}
	numberRobotX = atoi(argv[1]);
	numberRobotY = atoi(argv[2]);
	numberRobotZ = atoi(argv[3]);
	maxTimeX = atoi(argv[4]);
	maxTimeY = atoi(argv[5]);
	maxTimeZ = atoi(argv[6]);

	pthread_t tid[numberRobotX+numberRobotY+numberRobotZ+1];

	srand(time (NULL));

	for(int i = 0; i < numberRobotX; ++i)
	{
		int seed = rand()%1000;
		pthread_create(&(tid[i]), NULL, robotX, (void*) seed);
	}

	for(int i = numberRobotX; i < numberRobotX+numberRobotY; ++i)
	{
		int seed = rand()%1000;
		pthread_create(&(tid[i]), NULL, robotY, (void*) seed);
	}

	for(int i = numberRobotX+numberRobotY; i < numberRobotX+numberRobotY+numberRobotZ; ++i)
	{
		int seed = rand()%1000;
		pthread_create(&(tid[i]), NULL, robotZ, (void*) seed);
	}

	pthread_create(&(tid[numberRobotX+numberRobotY+numberRobotZ]), NULL, robotCreator, (void *) requiredProducts);


	pthread_join(tid[numberRobotX+numberRobotY+numberRobotZ], (void **)NULL);


	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

	std::cout<<"PRODUKCJA ZAKONCZONA\n";

	for(int i = 0; i < numberRobotX+numberRobotY+numberRobotZ; ++i)
		pthread_cancel(tid[i]);


	for(int i = 0; i < numberRobotX+numberRobotY+numberRobotZ; ++i)
		pthread_join(tid[i], (void **)NULL);

	return EXIT_SUCCESS;
}

void * robotX(void * data)
{
	char charProduct;
	int progressFactorX = 0;
	int seed = *((int*)(&data));

	srand(seed);

	while(PRODUCTION)
	{
		charProduct = (char)(productX + facX.increase());
		int time = 1 + rand()%maxTimeX;

		bufferX.put(charProduct, time);
		sleep(1);
	}
	return EXIT_SUCCESS;
}

void * robotY(void * data)
{
	char charProduct;
	int progressFactorY = 0;
	int seed = *((int*)(&data));

	srand(seed);

	while(PRODUCTION)
	{
		charProduct = (char)(productY + facY.increase());
		int time = 1 + rand()%maxTimeY;

		bufferY.put(charProduct, time);
		sleep(1);
	}
	return EXIT_SUCCESS;
}

void * robotZ(void * data)
{
	char charProduct;
	int progressFactorZ = 0;
	int seed = *((int*)(&data));

	srand(seed);

	while(PRODUCTION)
	{
		charProduct = (char)(productZ + facZ.increase());
		int time = 1 + rand()%maxTimeZ;

		bufferZ.put(charProduct, time);
		sleep(1);
	}
	return EXIT_SUCCESS;
}

void * robotCreator(void * data)
{
	char str[4];
	int d = *((int*)(&data));

	for(int i = 0; i < d; ++i)
	{
		str[0] = bufferX.get();
		str[1] = bufferY.get();
		str[2] = bufferZ.get();
		str[3] = '\0';

		std::string msg = "Wyprodukowano: " + toString(str) + ".\n";
		Msg.print(msg);
	}
	return EXIT_SUCCESS;
}
