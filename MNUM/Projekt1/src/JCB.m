% funkcja do wyznaczania rozwiazania rownan liniowych metoda Jacobiego

% zalozenie: przekazywane macierze A i b maja odpowiednie wymiary
% pozwalajace wyznaczyc rozwiazania ukladu rownan, przy czym:
% A - macierz nieosobliwa n x n wspolczynnikow
% b - macierz n x 1 wynikow
% ponadto zakladam ze dla kazdego 'i' A(i,i) ~= 0
function [ x, time ] = JCB( A, b, maxIterations )
    % nie tworze oddzielnie macierzy L (poddiagonalna), D(diagonalna) i U
    % (naddiagonalna) aby niepotrzebnie nie marnowac pamieci, wszystkie
    % obliczenia beda wykonywane za pomoca macierzy A
   
    % ustawiam pomiar czasu wykonywania funkcji
    tic;
    % pobieram wymiar macierzy kwadratowej A
    [n,~] = size(A);
    % tworze macierz wynikowa uzupelniona samymi zerami: pierwsza kolumna
    % przechowuje najnowszy wektor x, druga kolumna przechowuje starszy
    % wektor x
    x = zeros(n, 2);
    % ustawiam poczatkowa wartosc parametru currentIter
    currentIter = 1;
    % dopoki liczba iteracji jest niewieksza od parametru maxIterations
    % w petli liczymy kolejne przyblizenia
    while currentIter <= maxIterations
        for i = 1: n
            sum = 0;
            % pierwszy etap obliczania sum
            for k = 1: n
                sum = sum + A(i,k) * x(k,2);
            end
            % drugi etap obliczania sum
            sum = sum - A(i,i) * x(i,2);
            sum = sum - b(i);
            x(i,1) = -1/A(i,i) * sum;
        end
        % po wyjsciu z petli for mam obliczone nowe wartosci macierzy x
        % aktualizuje currentIter
        currentIter = currentIter + 1;
        % uaktualniam druga kolumne wektora x aby gotowy byl do dalszej
        % iteracji
        x(:,2) = x(:,1);
    end
    % koryguje wektor x, usuwam niepotrzebna juz druga kolumne
    x(:,2) = [];
    % koncze pomiar czasu
    time = toc;
end

