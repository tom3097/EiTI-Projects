% funkcja zwraca blad rozwiazania dla danego wielomianu aproksymujacego
% podany zestaw danych
function [ error ] = getLZNKSolutionError( X, Y, Coeff)
    % obliczam wartosci Y dla argumentow X dla funkcji wielomianowej
    % okreslonej przez wspolczynniki przy odpowiednich potegach (Coeff)
    auxY = polyval(Coeff,X);
    % obliczam residuum
    residuum = auxY - Y;
    % obliczam blad jako norme residuum
    error = norm(residuum);
end

