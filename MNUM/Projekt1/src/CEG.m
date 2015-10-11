% funkcja do rozwiazywania ukladu n rownan liniowych metoda:
% eliminacja Gaussa z czesciowym wyborem elementu podstawowego

% zalozenie: przekazywane macierze A i b maja odpowiednie wymiary
% pozwalajace wyznaczyc rozwiazania ukladu rownan, przy czym:
% A - macierz nieosobliwa n x n wspolczynnikow
% b - macierz n x 1 wynikow
function [ x, time ] = CEG(A, b)
    % ustawiam pomiar czasu wykonywania funkcji
    tic;
    % wczytuje rozmiar macierzy kwadratowej A
    [n,~] = size(A);
    % scalam macierze wspolczynnikow A i wynikowa B
    C = [A,b];
    % inicjuje glowna petle funkcji
    for k = 1: n
        % wybieram element o najwiekszym module w okreslonej kolumnie
        % zapisuje numer wiersza w ktorym sie znajduje w maxLine
        [~,maxLine] = max(abs(C(k:n,k)));
        % korygujw wartosc maxLine aby odnosila sie ona do macierzy C
        maxLine = maxLine + k -1;
        % podmieniam wiersze k-ty z numerem wiersza zapisanym w maxLine
        C([k,maxLine],:) = C([maxLine,k],:);
        % inicjuje petle ktora utworzy macierz trojkatna
        for t = k + 1: n
            C(t,k:n+1) = C(t,k:n+1) - C(t,k)/C(k,k) * C(k,k:n+1);
        end
    end
    % tworze pusta kolumne wynikowa x
    x = zeros(n, 1);
    % implementuje wzory:
    % xn = bn/ann
    % xk = (bk-suma:od j=k+1 do n(akj*xj))/akk, dla k = n-1, n-2,...,1
    x(n) = C(n,n+1)/C(n,n);
    for i = n-1:-1:1
        tmpSum = 0;
        for j= i+1:n
            tmpSum = tmpSum + C(i,j) * x(j);
        end
        x(i) = (C(i,n+1) - tmpSum)/C(i,i);
    end
    % koncze pomiar czasu
    time = toc;
% koncze wywolanie funkcji
end

