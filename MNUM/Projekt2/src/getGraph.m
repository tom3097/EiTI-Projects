% funkcja rysujaca wykres zadanego zestawu danych oraz aproksymujacej go
% funkcji wielomianowej
% funkcja przyjmuje trzy argumenty: pierwszy (x) okresla wspolrzedne punktow
% na osi x, drugi (y) oznacza wspolrzedne punktow na osi y, trzeci (Coeff)
% okresla wspolczynniki wielomianu aproksymujacego zadany zestaw danych
function [ graph ] = getGraph( X, Y, Coeff )
    % wyznaczam stopien wielomianu aproksymujacego
    polyDegree = size(Coeff,1)-1;
    % wyznaczam okres probkowania danych
    dataPeriod = (max(X) - min(X))/(size(X,1)-1);
    % wyznaczam okres probkowania rysowanej funkcji
    fPeriod = dataPeriod / 10;
    % wyznaczam pomocnicza macierz auxX
    auxX = min(X)-dataPeriod : fPeriod : max(X)+dataPeriod;
    % wyznaczam pomocniczo macierz auxY
    auxY = polyval(Coeff, auxX);
    % rysuje wykres
    graph = plot(auxX, auxY, 'b', X, Y, 'rs');
    % ustawiam parametry
    set(graph(1),'linewidth',1.25);
    set(graph(2),'linewidth',1);
    title(['Stopien wielomianu = ', num2str(polyDegree)]);
    xlabel('os X');
    ylabel('os Y'); 
end

