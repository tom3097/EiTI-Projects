% funkcja wyznaczajaca wartosci wlasne macierzy symetrycznej metoda QR bez
% przesuniec
% funkcja pobiera trzy argumenty: pierwszy argument (A) jest to macierz
% ktorej wartosci wlasne sa poszukiwane, drugi argument (precision) okresla
% precyzje z jaka wartosci wlasne maja zostac wyznaczone (czyli najwieksza
% dopuszczalna wartosc dla liczb lezacych pod i nad diagonala), trzeci
% argument (maxIter) okresla maksymalna liczbe iteracji, ktora moze zostac
% przeprowadzona w celu znalezienia wartosci wlasnych
% funkcja zwraca 4 argumenty: pierwszy (eval) to wartosci wlasne macierzy,
% drugi (iter) okresla wykonana liczbe iteracji, trzeci (prAch) okresla czy
% podana precyzja zostala osiagnieta, czwarty (time) to czas wykonania
% programu
function [eval,iter,prAch,time]=getEigenvalNoShiftQR(A,precision,maxIter)
    % zaczynam mierzyc czas wykonania
    tic;
    % inicjalizuje zmienna prAch na 1; wartosc 1 oznacza ze podana 
    % zostala osiagnieta, wartosc 0 ze nie zostala osiagnieta; dokonuje 
    % tutaj zalozenia ze podana precyzja zostanie osiagnieta, ewentualna 
    % korekta zostanie wykonana na koncu programu (mniejsza liczba skokow)
    prAch = 1;
    % inicjalizuje zmienna currIter
    currIter = 0;
    % petla dzialajaca do momentu wykonania maksymalnej mozliwej liczby
    % iteracji lub do momentu otrzymania satysfakcjonujacej nas dokladnosci
    while currIter < maxIter && max(max(abs(A - diag(diag(A)))))>precision
        % wyznaczam rozklad QR macierzy A (faktoryzacja)
        [Q,R] = getQRmodGramSchmidt(A);
        % wyznaczam macierz przeksztalcona
        A = R * Q;
        % zwiekszam licznik iteracji
        currIter = currIter + 1;
    end
    % zapamietuje w zmiennej eval wyznaczone wartosci wlasne
    eval = diag(A);
    % ustawiam wartosc iter
    iter = currIter;
    % sprawdzam czy po wyjsciu z petli osiagnelismy podana precyzje,
    % koryguje zmienna precisionAchieved
    if max(max(abs(A- diag(diag(A))))) > precision
        prAch = 0;
    end
    % odczytuje czas wykonania
    time = toc;
end

