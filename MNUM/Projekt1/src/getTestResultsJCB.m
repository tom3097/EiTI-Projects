% funkcja wywolujaca program dla okreslonego w dataNumber zestawu danych
% dla macierzy o wymiarach n1=10, n2=20 ... nx = 10* 2^(x-1), gdzie x
% okreslone jest przez parametr numberOfAttempts
function [ N, Err, TimeM] = getTestResultsJCB( numOfA, dataNr, maxIter)
    % tworze trzy puste macierze zawierajace odpowiednio wymiary
    % kolejnych macierzy, bledy rozwiazania oraz czasy rozwiazania
    N = zeros( numOfA, 1);
    Err = zeros( numOfA, 1);
    TimeM = zeros( numOfA, 1);
    % glowna petla programu
    for i = 1: numOfA
        % obliczam wymiar aktualnej macierzy
        tempN = 10*2^(i-1);
        % uzupelniam macierz wymiarow macierzy
        N(i) = tempN;
        % generuje odpowiednia macierz
        [A, b] = getMatrixes( tempN, dataNr);
        % wywoluje funkcje wyznaczajaca rozwiazanie ukladu rownan
        [x, time ] = JCB(A, b, maxIter);
        % uzupelniam macierz czasow wykonania
        TimeM(i) = time;
        % wyznaczam residuum
        residuum = A*x - b;
        % wyznaczam norme residuum
        residuumNorm = getNorm2(residuum);
        % uzupelniam macierz bledow rozwiazania
        Err(i) = residuumNorm;
    end
end