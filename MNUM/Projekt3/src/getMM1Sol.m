% funkcja wyznaczajaca pierwiastek rownania metoda Mullera MM1
% PARAMETRY:
% f - zadana funkcja
% x1 - pierwszy argument
% x2 - drugi argument
% x3 - trzeci argument, pierwsze przyblizenie miejsca zerowego
% iterMax - zadana liczba iteracji
function [ x, y, t ] = getMM1Sol( f, x1, x2, x3, iterMax )
    tic;
    % wyznaczam wartosci poczatkowe zmiennych
    % c - aktualne przyblizenie miejsca zerowego
    a = x1;
    b = x2;
    c = x3;
    fa = f(a);
    fb = f(b);
    fc = f(c);
    % alokuje pamiec na wektory rozwiazan
    x = zeros(iterMax, 1);
    y = zeros(iterMax, 1);
    t = zeros(iterMax, 1);
    % glowna petla algorytmu, w kazdej iteracji polozenie miejsca
    % zerowego jest poprawiane
    for i = 1 : iterMax
        coefA1 = (a - c) * (a - c);
        coefB1 = (a - c);
        coefA2 = (b - c) * (b - c);
        coefB2 = (b - c);
        res1 = fa - fc;
        res2 = fb - fc;
        % wyznaczam wspolczynniki ukladu rownan
        A = (coefB2*res1 - res2*coefB1)/(coefA1*coefB2 - coefB1*coefA2);
        B = (coefA1*res2 - res1*coefA2)/(coefA1*coefB2 - coefB1*coefA2);
        C = fc;
        % wyznaczam rozwiazania ukladu rownan
        z1 = -2*C/(B + sqrt(B^2 - 4*A*C));
        z2 = -2*C/(B - sqrt(B^2 - 4*A*C));
        % wybieram pierwiastek zmin
        if abs(B + sqrt(B^2 - 4*A*C)) >= abs (B - sqrt(B^2 - 4*A*C))
            zmin = z1;
        else
            zmin = z2;
        end
        % wyznaczam aktualne przyblizenie miejsca zerowego 
        d = c + zmin;
        % uaktualniam zmienne
        % odrzucam punkt polozony najdalej od ostatniego wyznaczonego
        % przyblizenia, czyli d
        if abs(d-a) > abs(d-b) && abs(d-a) > abs(d-c)
            a = c;
            fa = fc;
        elseif abs(d-b) > abs(d-a) && abs(d-b) > abs(d-c)
            b = c;
            fb = fc;
        end
        c = d;
        fc = f(c);
        % uzupelnienie wektora wynikow
        x(i,1) = c;
        y(i,1) = fc;
        t(i,1) = toc;
    end
end

