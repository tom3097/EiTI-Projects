% funkcja do wyznaczania rozkladu QR waskiego zmodyfikowanym algorytmem 
% Gram'a Schmidt'a; standardowy algorytm Gram'a Schmidt'a ma niekorzystne
% wlasnosci numeryczne, w zmodyfikowanym algorytmie proces ortogonalizacji
% przeprowadzany jest w innej kolejnosci; standardowy algorytm
% ortogonalizuje kolumny macierzy po kolei, w algorytmie zmodyfikowanym po
% wyznaczeniu kolejnej kolumny ortogonalnej od razu ortogonalizuje sie
% wobec niej wszystkie nastepne kolumny
% algorytm dziala dla macierzy o pelnym rzedzie i wyznacza rozklad QR waski
function [ Q, R ] = getQRmodGramSchmidt( A )
    % odczytuje wymiary macierzy
    [m,n] = size(A);
    % alokuje pamiec na macierz Q
    Q = zeros(m,n);
    % alokuje pamiec na macierz R
    R = zeros(n,n);
    % alokuje pamiec na pomocnicza macierz AUX
    AUX = zeros(1,n);
    % petla zewnetrzna programu
    for i = 1 : n
        Q(:,i) = A(:,i);
        R(i,i) = 1;
        AUX(i) = Q(:,i)' * Q(:,i);
        % petla wewnetrzna programu
        for j = i + 1 : n
            R(i,j) = (Q(:,i)' * A(:,j))/AUX(i);
            A(:,j) = A(:,j) - R(i,j) * Q(:,i);
        end
    end
    % normowanie rozkladu
    for i = 1: n
        norm2 = norm(Q(:,i));
        Q(:,i) = Q(:,i)/norm2;
        R(i,i:n) = R(i,i:n) * norm2;
    end
end

