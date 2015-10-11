% funkcja wyznaczajaca pierwiastek rownania metoda siecznych
% PARAMETRY:
% f - zadana funkcja
% xl - lewa granica przedzialu
% xr - prawa granica przedzialu
% iterMax - zadana liczba iteracji
function [ x, y, t ] = getSecantMethSol( f, xl, xr, iterMax)
    tic;
    % wyznaczam wartosci poczatkowe zmiennych a, b, fa, fb
    a = xl;
    b = xr;
    fa = f(a);
    fb = f(b);
    % alokuje pamiec na wektory rozwiazan
    x = zeros(iterMax, 1);
    y = zeros(iterMax, 1);
    t = zeros(iterMax, 1);
    % glowna petla algorytmu, w kazdej iteracji polozenie miejsca
    % zerowego jest poprawiane
    if fa * fb > 0
        fprintf('Nie ma gwarancji ze w podanym przedziale jest miejsce zerowe');
        return
    end
    for i = 1 : iterMax
        c = b - ((fb * (b-a))/(fb - fa));
        fc = f(c);
        % uaktualniam zmienne
        a = b;
        fa = fb;
        b = c;
        fb = fc;
        % uzupelnienie wektora wynikow
        if abs(fa) < abs(fb)
            x(i,1) = a;
            y(i,1) = fa;
        else
            x(i,1) = b;
            y(i,1) = fb;
        end
        t(i,1) = toc;
    end
end

