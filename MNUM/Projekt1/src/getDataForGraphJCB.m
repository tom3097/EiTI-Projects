% funkcja zwracajaca dwie macierze: Iter przechowuje kolejne liczby
% iteracji, Errors przechowuje kolejne bledy rozwiazania. Na podstawie tych
% informacji utworzony zostanie wykres bledu rozwiazania od liczby iteracji
% funkcja pobiera trzy argumenty: macierz wspolczynnikow A, macierz
% wynikowa b oraz liczbe iteracji dla ktorych nalezy obliczyc blad
function [Iter, Errors] = getDataForGraphJCB( A, b, numbOfIter )
    % alokuje pamiec na macierz Errors
    Errors = zeros(numbOfIter,1);
    % poniewaz od razu wiem jak bedzie wygladala macierz Iter uzupelniam ja
    Iter = 1 : numbOfIter;
    % glowna petla okreslajaca liczbe iteracji
    for i = 1: numbOfIter
        % wyznaczam rozwiazanie ukladu dla liczby iteracji i
        [x,~] = JCB(A, b, i);
        % wyznaczam residuum
        residuum = A*x - b;
        % wyznaczam norme residuum
        residuumNorm = getNorm2(residuum);
        % uzupelniam macierz Errors
        Errors(i) = residuumNorm;
    end
end

