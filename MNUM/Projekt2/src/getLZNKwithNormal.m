% funkcja wyznaczajaca wspolczynniki wielomianu najlepiej aproksymujacego
% podany zestaw danych
% funkcja pobiera trzy argumenty: pierwszy (x) okresla wspolrzedne punktow
% na osi x, drugi (y) oznacza wspolrzedne punktow na osi y, trzeci
% (polyDegree) okresla stopien wielomianu ktorym podany zestaw danych
% bedzie aproksymowany
function [ coeff, time ] = getLZNKwithNormal( X, Y, polyDegree )
    % zaczynam mierzyc czas wykonania
    tic;
    % odczytuje liczbe wartosci podanych w macierzy X, wynik zapisuje w
    % zmiennej valNumber
    [valNumber,~] = size(X);
    % alokuje pamiec na macierz A
    A = zeros(valNumber,polyDegree+1);
    % wypelniam macierz A odpowiednimi potegami odpowiednich wartosci X
    for i = 1 : valNumber
        auxVal = 1;
        for j = polyDegree+1 : -1 : 1
            A(i,j) = auxVal;
            auxVal = auxVal * X(i);
        end
    end
    % obliczam poszukiwane wartosci wspolczynnikow
    coeff = (A'*A) \ (A'*Y);
    % odczytuje czas wykonania
    time = toc;
end

