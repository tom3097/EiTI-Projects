% funkcja wyznaczajaca pierwiastek rownania metoda Mullera MM2
% PARAMETRY:
% f - zadana funkcja
% df - pierwsza pochodna zadane funkcji
% ddf - druga pochodna zadanej funkcji
% xb - pierwsze przyblizenie pierwiastka
% iterMax - zadana liczba iteracji
function [ x, y, t ] = getMM2Sol( f, df, ddf, xb, iterMax)
    tic;
    % wyznaczam wartosci poczatkowe zmiennych
    a = xb;
    fa = f(a);
    dfa = df(a);
    ddfa = ddf(a);
    % alokuje pamiec na wektory rozwiazan
    x = zeros(iterMax, 1);
    y = zeros(iterMax, 1);
    t = zeros(iterMax, 1);
    % glowna petla algorytmu, w kazdej iteracji polozenie miejsca
    % zerowego jest poprawiane
    for i = 1 : iterMax
        z1 = -2*fa / ( dfa + sqrt(dfa^2 - 2*fa*ddfa));
        z2 = -2*fa / ( dfa - sqrt(dfa^2 - 2*fa*ddfa));
        % wybieram pierwiastek zmin
        if abs(dfa + sqrt(dfa^2 - 2*fa*ddfa)) >= abs(dfa - sqrt(dfa^2 - 2*fa*ddfa))
            zmin = z1;
        else
            zmin = z2;
        end
        % uaktualniam zmienne
        a = a + zmin;
        fa = f(a);
        dfa = df(a);
        ddfa = ddf(a);
        % uzupelnienie wektora wynikow
        x(i,1) = a;
        y(i,1) = fa;
        t(i,1) = toc;
    end
end

