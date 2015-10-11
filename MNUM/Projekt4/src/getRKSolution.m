% funkcja wyznaczajaca przebieg trajektorii lotu
% PRZYJMOWANE ARGUMENTY:
% x - warunki poczatkowe
% step - staly krok
% timeInterval - gorna granice przedzialu
function [ T, X, E, ME ] = getRKSolution( x, step, timeInterval )
    % obliczam pomocnicze wartosci
    number = ceil(timeInterval/step)-1;
    % alokuje pamiec na wektory wynikow
    T = zeros(number,1);
    X = zeros(number,2);
    E = zeros(number,2);
    ME = zeros(number,2);
    % petla programu
    for i = 1 : number
        x = iter(x,step);
        % uaktualniam wektory wynikow
        T(i) = i*step;
        X(i,:) = x';
        % wyznaczam w celu obliczenia bledow
        xe = iter(x,step/2);
        xe = iter(xe,step/2);
        % wyznaczam blad
        E(i,:) = (((16/15)*(x - xe))');  
        ME(i,:) = abs(E(i,:));
    end
end

