% norma druga macierzy A jest to pierwiastek z najwiekszego modulu wartosci
% wlasnej macierzy powstalej z pomnozenia transponowanej macierzy 
% A przez macierz A
function [ norm2 ] = getNorm2( A )
    % pomocniczo wyznaczam macierz T dla ktorej bede liczyl wartosci
    % wlasne
    T = A' * A;
    % w zmiennej maxEig przechowuje najwieksza wartosc wlasna macierzy T
    maxEig = max(abs(eig(T)));
    % obliczam norme druga jako pierwiastek z najwiekszej wartosci wlasnej
    norm2 = sqrt(maxEig);
end

