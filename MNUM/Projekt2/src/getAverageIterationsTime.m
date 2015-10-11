% funkcja zwracajaca srednia liczbe iteracji i sredni czas obliczen
% funkcja pobiera trzy argumenty: pierwszy (numbOfTests) okresla ilosc
% testow ktore nalezy wykonac, drugi (sym) okresla czy testowane macierze
% maja byc symetryczne czy nie ( sym == 0: macierz jest niesymetryczna),
% trzeci (shift) okresla czy obliczenia wykonywane sa za pomoca metody z
% przesunieciami czy bez przesuniec (shift == 0: bez przesuniec)
% funkcja zwraca trzy macierze: pierwsza okresla srednia liczbe iteracji i
% sredni czas dla macierzy 5x5, druga dla macierzy 10x10 i trzecia dla
% macierzy 20x20
function [M5,M10,M20] = getAverageIterationsTime(nmbOfTests,sym,shift,prec)
    % alokuje pamiec na macierze M5, M10, M20
    M5 = zeros(2,1);
    M10 = zeros(2,1);
    M20 = zeros(2,1);
    % petla odliczajaca liczbe testow
    for i = 1 : nmbOfTests
        A5 = getRandomMatrix(5,sym);
        A10 = getRandomMatrix(10,sym);
        A20 = getRandomMatrix(20,sym);
        if shift == 0
            [~,iter5,~,time5] = getEigenvalNoShiftQR(A5,prec,intmax);
            [~,iter10,~,time10] = getEigenvalNoShiftQR(A10,prec,intmax);
            [~,iter20,~,time20] = getEigenvalNoShiftQR(A20,prec,intmax);
        else
            [~,iter5,~,time5] = getEigenvalShiftQR(A5,prec,intmax);
            [~,iter10,~,time10] = getEigenvalShiftQR(A10,prec,intmax);
            [~,iter20,~,time20] = getEigenvalShiftQR(A20,prec,intmax);
        end
        % sumuje ogolna liczbe iteracji i ogolny czas
        M5(1) = M5(1) + iter5;
        M5(2) = M5(2) + time5;
        M10(1) = M10(1) + iter10;
        M10(2) = M10(2) + time10;
        M20(1) = M20(1) + iter20;
        M20(2) = M20(2) + time20;
    end
    % wyznaczam srednia dzielac przez liczbe testow
    M5 = M5 / nmbOfTests;
    M10 = M10 / nmbOfTests;
    M20 = M20 / nmbOfTests;           
end

