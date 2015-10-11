% funkcja wyznaczajaca pierwiastek rownania metoda Newtona
% PARAMETRY:
% f - zadana funkcja
% fp - pochodna zadanej funkcji
% xb - pierwsze przyblizenie pierwiastka
% iterMax - zadana liczba iteracji
function [ x, y, t ] = getNewtonMethSol( f, fp, xb, iterMax )
    tic;
    % wyznaczam wartosci poczatkowe zmiennych a, fa, fpa
    a = xb;
    fa = f(a);
    fpa = fp(a);
    % alokuje pamiec na wektory rozwiazan
    x = zeros(iterMax, 1);
    y = zeros(iterMax, 1);
    t = zeros(iterMax, 1);
    % glowna petla algorytmu, w kazdej iteracji polozenie miejsca
    % zerowego jest poprawiane
    for i = 1 : iterMax
        c = a - fa/fpa;
        % uaktualniem zmienne
        a = c;
        fa = f(a);
        fpa = fp(a);
        % uzupelniam wektor wynikow
        x(i,1) = a;
        y(i,1) = fa;
        t(i,1) = toc;
    end
end

