#include <iostream>
#include <vector>
#include <cstdlib>
#include <queue>
#include <functional>
#include <ctime>
#include <cstdlib>

/* Klasa reprezentujaca wspolrzedne */
class Coords {
	int x;
	int y;

public:

	Coords(): x(-1), y(-1) {};
	Coords(int _x, int _y): x(_x), y(_y) {};
	~Coords() {};

	bool operator== (const Coords& _coords) const {return x == _coords.getX() && y == _coords.getY();}

	void setX(int _x) { x = _x;}
	void setY(int _y) {y = _y;}

	int getX() const {return x;}
	int getY() const {return y;}
};

/* Klasa reprezentujaca jednostke rastra */
class Field {
	/* Wspolrzedne pola */
	Coords coords;
	/* Informacja czy pole jest dozwolone do przejscia czy nie */
	bool allowed;
	/* G - długość (koszt) ścieżki prowadzącej z punktu startu do aktualnej, 
	rozpatrywanej pozycji w przestrzeni (jest to rzeczywista długość ścieżki, którą już wygenerowaliśmy) */
	unsigned G;
	/* H – szacunkowa długość ścieżki prowadząca z aktualnej pozycji do punktu docelowego; wartość H jest najczęściej 
	wyznaczana metodami heurystycznymi, gdyż z oczywistego względu nie znamy tej długości (gdyby tak było, użycie takiego 
	algorytmu byłoby niepotrzebne) */
	unsigned H;
	/* F = G+H – wartość równa sumie długości dwóch powyższych ścieżek */
	unsigned F;
	/* Wskaznik na rodzica */
	Field* parent;
public:

	Field(): allowed(true), G(0), H(0), F(0) {}
	Field(Coords _coords, bool _allowed): coords(_coords), allowed(_allowed), G(0), H(0), F(0), parent(NULL) {}
	~Field() {};

	void reset() { G = H = F = 0; parent = NULL;}

	bool operator== (const Field& _field) const {return coords == _field.getCoords() && allowed == _field.getAllowed();}
	bool operator!= (const Field& _field) const {return !(*this == _field);}

	void setCoords(Coords _coords) { coords.setX(_coords.getX()); coords.setY(_coords.getY());}
	void setAllowed(bool flag) {allowed = flag;}
	void setParent(Field *_parent) {parent = _parent;}

	void updateGHF(unsigned newG, unsigned newH) {G = newG; H = newH; F = newG + newH;}
	void updateGHF(unsigned newG) {G = newG; F = newG + H;}

	void updateGF(unsigned newG) {G = newG; F = newG;}

	Coords getCoords() const {return coords;}
	bool getAllowed() const {return allowed;}
	unsigned getF() const {return F;}
	unsigned getG() const {return G;}
	Field* getParent() {return parent;}
};

/* Klasa reprezentujaca raster */
class Raster {
	/* typ macierzy */
	typedef std::vector<std::vector<Field> > Matrix;
	/* ilosc wierszy */
	size_t M;
	/* ilosc kolumn */
	size_t N;
	/* macierz */
	Matrix matrix;
	/* wspolrzedne poczatku */
	Coords begin;
	/* wspolrzedne konca */
	Coords end;
	/* flaga oznaczajaca czy sciezka zostala znaleziona */
	bool pathFlag;
public:
	Raster(int _M, int _N, bool **_array, Coords _begin, Coords _end): M(_M), N(_N), begin(_begin), end(_end), pathFlag(false){
		matrix.reserve(M);
		std::vector<Field> line(N, Field());

		for(int l_idx = 0; l_idx < M; ++l_idx) {
			matrix.push_back(line);
		}

		for(int l_idx = 0; l_idx < M; ++l_idx) {
			for(int c_idx = 0; c_idx < N; ++c_idx) {
				if(!_array[l_idx][c_idx])
					matrix[l_idx][c_idx].setAllowed(false);
				matrix[l_idx][c_idx].setCoords(Coords(l_idx, c_idx));
			}
		}
	}

	void reset() {
		for(int l_idx = 0; l_idx < M; ++l_idx) {
			for(int c_idx = 0; c_idx < N; ++c_idx) {
				matrix[l_idx][c_idx].reset();
			}
		}
	}

	Field& getField(int _x, int _y) { return matrix[_x][_y]; }
	Field& getBegin() {return matrix[begin.getX()][begin.getY()];}
	Field& getEnd() {return matrix[end.getX()][end.getY()];}
	size_t getM() {return M;}
	size_t getN() {return N;}
	bool getPathFlag() {return pathFlag;}

	bool setPathFlag(bool flag) {pathFlag = flag;}

	void printMap() {
		for(int l_idx = 0; l_idx < M; ++l_idx) {
			for(int c_idx = 0; c_idx < N; ++c_idx) {
				if(matrix[l_idx][c_idx] == getBegin()) {std::cout<<"1 "; continue;}
				if(matrix[l_idx][c_idx] == getEnd()) {std::cout<<"2 "; continue;}
				std::cout<<(matrix[l_idx][c_idx].getAllowed() ? "W " : "B ");
			}
			std::cout<<std::endl;
		}
	}

	void printWayMap() {
		if(!pathFlag)
			return;

		unsigned wayMap[M][N];
		for(int l_idx = 0; l_idx < M; ++l_idx)
			for(int c_idx = 0; c_idx < N; ++c_idx)
				wayMap[l_idx][c_idx] = 0;

		Field *f = &getEnd();
		while(*f  != getBegin()) {
		 	wayMap[f->getCoords().getX()][f->getCoords().getY()] = 1;
		 	f = f->getParent();
		}

		wayMap[getBegin().getCoords().getX()][getBegin().getCoords().getY()] = 2;
		wayMap[getEnd().getCoords().getX()][getEnd().getCoords().getY()] = 2;

		for(int l_idx = 0; l_idx < M; ++l_idx) {
			for(int c_idx = 0; c_idx < N; ++c_idx) {
				if(wayMap[l_idx][c_idx] == 2) {std::cout<<"@ "; continue;}
				if(wayMap[l_idx][c_idx] == 1) {std::cout<<"# "; continue;}
				std::cout<<". ";
			}
			std::cout<<std::endl;
		}
	}
};

bool ** get2Darray(size_t M, size_t N) {
	bool** arr = new bool*[M];
	for(int l_idx = 0; l_idx < M; ++l_idx)
    	arr[l_idx] = new bool[N];

    for(int l_idx = 0; l_idx < M; ++l_idx)
    	for(int c_idx = 0; c_idx < N; ++c_idx)
    		arr[l_idx][c_idx] = true;
    return arr;
}

/* Funkcja heurystyczna przewidujaca odleglosc od celu. Ma ona wlasnosci niedoszacowujace,
dlatego zapewnia optymalne rozwiazanie */
unsigned calculateManhattanH(const Field& from, const Field& to)
{
	return std::abs(from.getCoords().getX() - to.getCoords().getX()) + std::abs(from.getCoords().getY() - to.getCoords().getY());
}

/* Klasa z odpowiednio przeciazonym operatorem (), wykorzystywana przez kolejke priorytetowa */
class CompareFields {
public:
	bool operator() (const Field& field1, const Field& field2) {
		return field1.getF() > field2.getF();
	}
};


/* Algorytm A-star wykorzystujacy metody heurystyczne - wyznaczanie drogi ktora zostala do przebucia */
void A_star(Raster& raster) {
	clock_t start = clock();

	typedef std::priority_queue<std::reference_wrapper<Field>, std::vector<std::reference_wrapper<Field> >, CompareFields> Queue;

	bool matOL[raster.getM()][raster.getN()];
	bool matCL[raster.getM()][raster.getN()];

	for(int l_idx = 0; l_idx < raster.getM(); ++l_idx) {
		for(int c_idx = 0; c_idx < raster.getN(); ++c_idx) {
			matOL[l_idx][c_idx] = false;
			matCL[l_idx][c_idx] = false;
		}
	}

	Queue queueOL;

	queueOL.push(std::ref(raster.getBegin()));
	matOL[raster.getBegin().getCoords().getX()][raster.getBegin().getCoords().getY()] = true;

	while(!queueOL.empty()) {
		std::reference_wrapper<Field> Q = queueOL.top();
		queueOL.pop();

		int xQ = Q.get().getCoords().getX();
		int yQ = Q.get().getCoords().getY();

		matOL[xQ][yQ] = false;
		matCL[xQ][yQ] = true;

		if(Q.get() == raster.getEnd())
		{
			raster.setPathFlag(true);
			std::cout<<clock() - start<<" milisekund"<<std::endl;
			return;
		}

		std::vector<Coords> neighbours;
		if(yQ-1 >= 0) neighbours.push_back(Coords(xQ, yQ-1));
		if(yQ+1 < raster.getN()) neighbours.push_back(Coords(xQ, yQ+1));
		if(xQ-1 >= 0) neighbours.push_back(Coords(xQ-1, yQ));
		if(xQ+1 < raster.getM()) neighbours.push_back(Coords(xQ+1, yQ));
		for(Coords ngb: neighbours) {
			std::reference_wrapper<Field> ngbField = raster.getField(ngb.getX(), ngb.getY());

			if(matCL[ngb.getX()][ngb.getY()] ||  !ngbField.get().getAllowed())
				continue;

			if(!matOL[ngb.getX()][ngb.getY()]) {
				ngbField.get().setParent(&(Q.get()));
				unsigned newG = Q.get().getG() + 1;
				unsigned newH = calculateManhattanH(ngbField.get(), raster.getEnd());
				ngbField.get().updateGHF(newG, newH);
				queueOL.push(ngbField);
				matOL[ngb.getX()][ngb.getY()] = true;
				continue;
			}

			unsigned newG = Q.get().getG() + 1;
			if(newG < ngbField.get().getG()) {
				ngbField.get().setParent(&(Q.get()));
				ngbField.get().updateGHF(newG);
			}
		}
	}
}

void Dijkstra(Raster& raster) {
	clock_t start = clock();

	std::vector<std::reference_wrapper<Field> > queue;
	bool mat[raster.getM()][raster.getN()];
	for(int l_idx = 0; l_idx < raster.getM(); ++l_idx) {
		for(int c_idx = 0; c_idx < raster.getN(); ++c_idx) {
			mat[l_idx][c_idx] = false;
		}
	}

	int max = raster.getM() * raster.getN() + 1;
	for(int m_idx = 0; m_idx < raster.getM(); ++m_idx) {
		for(int n_idx = 0; n_idx < raster.getN(); ++n_idx) {
			raster.getField(m_idx, n_idx).updateGF(max);
		}
	}
	raster.getBegin().updateGF(0);

	for(int m_idx = 0; m_idx < raster.getM(); ++m_idx) {
		for(int n_idx = 0; n_idx < raster.getN(); ++n_idx) {
			queue.push_back(std::ref(raster.getField(m_idx, n_idx)));
		}
	}
	std::make_heap(queue.begin(), queue.end(), CompareFields());

	for(int i = 0; i < queue.size(); ++i) {
		std::reference_wrapper<Field> Q = queue[i];

		int xQ = Q.get().getCoords().getX();
		int yQ = Q.get().getCoords().getY();
		mat[xQ][yQ] = true;

		if(!Q.get().getAllowed())
			continue;

		if(Q.get() == raster.getEnd()) {
			raster.setPathFlag(true);
			std::cout<<clock() - start<<" milisekund"<<std::endl;
			return;
		}

		std::vector<Coords> neighbours;
		if(yQ-1 >= 0) neighbours.push_back(Coords(xQ, yQ-1));
		if(yQ+1 < raster.getN()) neighbours.push_back(Coords(xQ, yQ+1));
		if(xQ-1 >= 0) neighbours.push_back(Coords(xQ-1, yQ));
		if(xQ+1 < raster.getM()) neighbours.push_back(Coords(xQ+1, yQ));

		for(Coords ngb: neighbours) {
			std::reference_wrapper<Field> ngbField = raster.getField(ngb.getX(), ngb.getY());

			if(mat[ngb.getX()][ngb.getY()] or not ngbField.get().getAllowed())
				continue;

			if(ngbField.get().getG() > Q.get().getG() + 1) {
				ngbField.get().updateGF(Q.get().getG() + 1);
				ngbField.get().setParent(&(Q.get()));
			}
		}
		std::make_heap(queue.begin() + i + 1, queue.end(), CompareFields() );
	}
	raster.setPathFlag(true);
}

void Bellman_Ford(Raster &raster) {
	clock_t start = clock();

	bool finish;

	int max = raster.getM() * raster.getN() + 1;

	for(int m_idx = 0; m_idx < raster.getM(); ++m_idx) {
		for(int n_idx = 0; n_idx < raster.getN(); ++n_idx) {
			raster.getField(m_idx, n_idx).updateGF(max);
		}
	}

	raster.getBegin().updateGF(0);
	
	for(int i_idx = 0; i_idx < raster.getN() * raster.getM() - 1; ++i_idx) {
		finish = true;

		for(int m_idx = 0; m_idx < raster.getM(); ++m_idx) {
			for(int n_idx = 0; n_idx < raster.getN(); ++n_idx) {
				std::reference_wrapper<Field> curr_field = raster.getField(m_idx, n_idx);
				if(!curr_field.get().getAllowed())
					continue;

				int xF = raster.getField(m_idx, n_idx).getCoords().getX();
				int yF = raster.getField(m_idx, n_idx).getCoords().getY();

				std::vector<Coords> neighbours;
				if(yF-1 >= 0) neighbours.push_back(Coords(xF, yF-1));
				if(yF+1 < raster.getN()) neighbours.push_back(Coords(xF, yF+1));
				if(xF-1 >= 0) neighbours.push_back(Coords(xF-1, yF));
				if(xF+1 < raster.getM()) neighbours.push_back(Coords(xF+1, yF));

				for(Coords ngb: neighbours) {
					std::reference_wrapper<Field> ngbField = raster.getField(ngb.getX(), ngb.getY());
					if(!ngbField.get().getAllowed())
						continue;

					if(ngbField.get().getG() > curr_field.get().getG() + 1) {
						finish = false;
						ngbField.get().updateGF(curr_field.get().getG() + 1);
						ngbField.get().setParent(&(curr_field.get()));
					}
				}
			}
		}
		if(finish)
			break;
	}
	raster.setPathFlag(true);
	std::cout<<clock() - start<<" milisekund"<<std::endl;
}

int main() {
	size_t M = 5;
	size_t N = 7;

	bool ** bTable = get2Darray(M,N);

	/* Zabronione punkty */
	bTable[3][0] = bTable[3][1] = bTable[3][2] =bTable[3][3] = bTable[3][4] = bTable[3][5] =  bTable[3][1] = false;
	bTable[1][3] = bTable[2][3] = false;

	Raster raster(M, N, bTable, Coords(1,2), Coords(0,6));
	raster.printMap();

	std::cout<<"Bellman_Ford\n";
	Bellman_Ford(raster);
	raster.printWayMap();

	raster.reset();
	std::cout<<"A_star\n";
	A_star(raster);
	raster.printWayMap();

	raster.reset();
	std::cout<<"Dijkstra\n";
	Dijkstra(raster);
	raster.printWayMap();

	return 0;
}