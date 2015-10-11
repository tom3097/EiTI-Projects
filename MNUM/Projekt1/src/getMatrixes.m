% funkcja zwracajaca macierze wspolczynnikow (A) i macierz wynikowa (b)
% utworzone wedlug jednego z 3 algorytmow podanych w tresci zadania
% laboratoryjnego
function [ A, b ] = getMatrixes( n, dataNumber )
    % uzupelniam obie macierze samymi zerami
    A = zeros(n, n);
    b = zeros(n, 1);
    switch dataNumber
        case 1
            % uzupelniam wektor A
            for i = 1: n
                A(i,i) = 7;
                if i < n
                    A(i,i+1) = 1;
                end
                if i > 1
                    A(i,i-1) = 1;
                end
            end
            % uzupelniam wektor b
            for i = 1: n
                b(i) = 1.4 + 0.6*i;
            end
        case 2
            % uzupelniam macierz A
            % najpierw uzupelniam wszystkie elementy macierzy w wierszu 
            % wedlug wzoru aij = 2*(i-j)+1, nastpenie element aii 
            % zastepuje 0.2 ilosc operacji wykonywanych w takim algorytmie
            % jest mniejsza niz gdyby za kazdym razem porownywac 
            % indeksy i oraz j
            for i = 1: n
                for j = 1: n
                    A(i,j) = 2*(i-j)+1;
                end
                A(i,i) = 0.2;
            end
            % uzupelniam macierz b
            for i = 1: n
                b(i) = 1 + 0.4*i;
            end
        case 3
            % uzupelniam wektor A
            for i = 1: n
                for j = 1: n
                    A(i,j) = 7/(9*(i+j+1));
                end
            end
            % uzupelniam wektor b
            for i = 2: 2: n
                b(i) = 7/(5*i);
            end
    end
end

