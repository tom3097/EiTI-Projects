% funkcja wyznaczajaca pierwiastek rownania metoda bisekcji
% PARAMETRY:
% f - zadana funkcja
% xl - lewa granica przedzialu
% xr - prawa granica przedzialu
% iterMax - zadana liczba iteracji
function [ x, y, t ] = getBisMethSol( f, xl, xr, iterMax )
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
    if fa * fb > 0
        fprintf('Nie ma gwarancji ze w podanym przedziale jest miejsce zerowe');
        return
    end
    % glowna petla algorytmu, w kazdej iteracji polozenie miejsca
    % zerowego jest poprawiane
    for i = 1 : iterMax
        xm = a + 0.5*(b-a);
        fm = f(xm);
        % uaktualniam zmienne
        if fa * fm < 0
            b = xm;
            fb = fm;
        elseif fm * fb < 0
            a = xm;
            fa = fm;
        end
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

