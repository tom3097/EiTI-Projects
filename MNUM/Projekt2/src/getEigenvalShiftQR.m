% funkcja wyznaczajaca wartosci wlasne macierzy symetrycznej i macierzy
% niesymetrycznej metoda QR z przecunieciami
% funkcja pobiera trzy argumenty: pierwszy argument (A) jest to macierz
% ktorej wartosci wlasne sa poszukiwane, drugi argument (precision) okresla
% precyzje z jaka wartosci wlasne maja zostac wyznaczone (czyli najwieksza
% dopuszczalna wartosc dla liczb lezacych pod i nad diagonala), trzeci
% argument (maxIterPer) okresla maksymalna liczbe iteracji, ktora moze zostac
% przeprowadzona w celu znalezienia pojedynczej wartosci wlasnej
% funkcja zwraca 4 argumenty: pierwszy (eval) to wartosci wlasne macierzy,
% drugi (iter) okresla wykonana liczbe iteracji, trzeci (prAch) okresla czy
% podana precyzja zostala osiagnieta, czwarty (time) to czas wykonania
% programu
function [eval,iter,prAch,time] = getEigenvalShiftQR(A,precision,maxIterPer)
    % zaczynam mierzyc czas wykonania
    tic;
    % inicjalizuje zmienna prAch na 1; wartosc 1 oznacza ze podana 
    % zostala osiagnieta, wartosc 0 ze nie zostala osiagnieta; dokonuje 
    % tutaj zalozenia ze podana precyzja zostanie osiagnieta, ewentualna 
    % korekta zostanie wykonana na koncu programu (mniejsza liczba skokow)
    prAch = 1;
    % inicjalizuje zmienna iter, okresla ona calkowita liczbe iteracji
    iter = 0;
    % odczytuje stopien macierzy kwadratowej A i zapisuje go w zmiennej n
    [n,~] = size(A);
    % alokuje pamiec na macierz wynikowa eval
    eval = zeros(n,1);
    % inicjalizuje macierz submatrixA, ktora przechowuje aktualna dla
    % kazdego kroku k podmacierz
    submatrixA = A;
    % petla zewnetrzna, w kazdym jej przebiegu wyznaczana jest kolejna
    % wartosc wlasna macierzy
    for k = n : -1 : 2
        % inicjalizuje zmienna AK na wartosc poczatkowa submatrixA
        AK = submatrixA;
        % inicjalizuje currIter
        currIter = 0;
        % petla wewnetrzna, dzialajaca do momentu wykonania maksymalnej 
        % mozliwej liczby iteracji lub do momentu otrzymania 
        % satysfakcjonujacej nas dokladnosci
        while currIter < maxIterPer && max(abs(AK(k,1:k-1))) > precision
            % wyznaczam wartosc przesuniecia jako wartosc wlasna
            % podmacierzy 2x2 z prawego dolnego rogu macierzy AK blizsza
            % wartosci o wspolrzednych (2,2) tej podmacierzy
            M2x2 = AK(k-1:k,k-1:k);
            EigenvalM = getEigenvalOf2x2Matrix(M2x2);
            % inicjalizuje zmienna shift pierwsza wartoscia wlasna, w razie
            % potrzeby zostanie ona skorygowana
            shift = EigenvalM(2);
            % koryguje wartosc shift gdy zachodzi taka koniecznosc
            if abs(EigenvalM(1) - M2x2(2,2))<abs(EigenvalM(2) - M2x2(2,2))
                shift = EigenvalM(1);
            end
            % wyznaczam macierz przesunieta
            AK = AK - eye(k)*shift;
            % wyznaczam rozklad QR macierzy AK (faktoryzacja)
            [Q,R] = getQRmodGramSchmidt(AK);
            % wyznaczam macierz przeksztalcona
            AK = R * Q + eye(k)*shift;
            % zwiekszam licznik iteracji
            currIter = currIter + 1;
            % zwiekszam ilosc wszystkich iteracji
            iter = iter + 1;
        end
        % koryguje zmienna prAch
        if prAch == 1 && max(abs(AK(k,1:k-1))) > precision
            prAch = 0;
        end
        % uzupelniam macierz eval o obliczona w tym kroku wartosc wlasna
        eval(k) = AK(k,k);
        % jesli stopien macierzy kwadratowej jest wiekszy od 2 to
        % opuszczamy ostatni wiersz i ostatnia kolumne (deflacja)
        if k > 2
            submatrixA = AK(1:k-1,1:k-1);
        % w przeciwnym wypadku byl to ostatni przebieg petli zewnetrznej,
        % a ostatnia poszukiwana wartosc wlasna znajduje sie w AK(1,1)
        else
            eval(1) = AK(1,1);
        end
    end
    % odczytuje czas wykonania
    time = toc;
end

