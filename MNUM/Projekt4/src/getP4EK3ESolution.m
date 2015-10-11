% funkcja wyznaczajaca przebieg trajektorii lotu
% PRZYJMOWANE ARGUMENTY:
% x - warunki poczatkowe
% step - staly krok
% timeInterval - gorna granice przedzialu
function [ T, X, E, ME ] = getP4EK3ESolution( x, step, timeInterval )
    % parametry k odczytuje z tabelki w podreczniku, skoro rzad wynosi 4
    % to wynosza one odpowiednio 4 i 3
    % stale uzywane do obliczen
    B1 = 55/24;
    B2 = -59/24;
    B3 = 37/24;
    B4 = -9/24;
    b0 = 9/24;
    b1 = 19/24;
    b2 = -5/24;
    b3 = 1/24;
    % obliczam pomocnicze wartosci
    number = ceil(timeInterval/step)-1;
    % alokuje pamiec na wektory wynikow
    T = zeros(number,1);
    X = zeros(number,2);
    E = zeros(number,2);
    ME = zeros(number,2);
    % wyznaczam k pierwszych wartosci potrzebnych do pierwszego 
    % zastosowania wlasciwego algorytmu P4EK4E
    % wartosci wyznaczam za pomoca algorytmu RK
    for i = 1 : 4
        x = iter(x,step);
        % uaktualniam wektory wynikow
        T(i) = i*step;
        X(i,:) = x';
    end
    % wlasciwa czesc algorytmu
    for i = 5 : number;
        % PE - predykcja, ewaluacja
        temp = X(i-1,:)'+step*(B1*xDot(0,X(i-1,:)')+B2*xDot(0,X(i-2,:)')+...
            B3*xDot(0,X(i-3,:)')+B4*xDot(0,X(i-4,:)'));
        % KE - korekta, ewaluacja
        aux = X(i-1,:)'+step*(b0*xDot(0,temp)+b1*xDot(0,X(i-1,:)')+...
            b2*xDot(0,X(i-2,:)')+b3*xDot(0,X(i-3,:)'));
        % uaktualniam wyniki i czasy
        T(i) = i*step;
        X(i,:) = aux';
        E(i,:) = ((-19/270)*(temp-aux))';
        ME(i,:) = abs(E(i,:));
    end
end

