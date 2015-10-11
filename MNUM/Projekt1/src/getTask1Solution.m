function [ ] = getTask1Solution( )
    % ZADANIE 1
    % algorytm oparty jest bezposrednio na definicji dokladnosci maszynowej:
    % dokladnosc maszynowa jest najmniejsza liczba wieksza od 0 ktora
    % dodana do jednosci daje wynik wiekszy od jednosci
    % otwieram plik do ktorego zapisze wynik
    [id, kom] = fopen('wynikZad1.txt', 'wt');
    if id < 0
        disp(kom);
    end
    x = 1.0;
    % petla dzialajaca dopoki wynik jest wiekszy od jednosci
    while 1.0 + x > 1.0
        myEps = x;
        x = x/2;
    end
    % w tym momencie myEps przechowuje najmniejsza liczbe ktora dodana do
    % jednosci daje wynik wiekszy od jednosci
    fprintf('Dokladnosc maszynowa komputera wynosi: %g\n', myEps);
    if id > 0
        fprintf(id, 'Dokladnosc maszynowa komputera wynosi: %g\n', myEps);
    end
    fclose(id);
    % wynik myEps obliczony w tym programi zgadza sie z wartoscia eps ktora
    % otrzymamy po wpisaniu do matlaba 'eps' lub 'eps(1)'
end

