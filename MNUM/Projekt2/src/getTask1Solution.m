% zadanie 1: glowna funkcja, zajmuje sie obliczaniem wynikow, ich
% prezentacja oraz zapisywaniem ich do pliku
function [ ] = getTask1Solution( )
    % otwieram plik do ktorego zapisze wyniki
    [id, kom] = fopen('wynikiTestowZad1P2.txt', 'wt');
    if id < 0
        disp(kom);
    end
    % wyznaczam srednie ilosci iteracji
    
    % SYMETRYCZNA, BEZ PRZESUNIEC
    % precyzja: 0.1
    [M5_1, M10_1, M20_1] = getAverageIterationsTime(30,1,0,0.1);
    % precyzja: 0.01
    [M5_2, M10_2, M20_2] = getAverageIterationsTime(30,1,0,0.01);
  
    % SYMETRYCZNA, Z PRZESUNIECIAMI
    % precyzja: 0.00001
    [M5_3, M10_3, M20_3] = getAverageIterationsTime(30,1,1,0.00001);
    % precyzja: 0.0000001
    [M5_4, M10_4, M20_4] = getAverageIterationsTime(30,1,1,0.0000001);
    
    % NIESYMETRYCZNA, Z PRZESUNIECIAMI
    % precyzja: 0.00001
    [M5_5, M10_5, M20_5] = getAverageIterationsTime(30,0,1,0.00001);
    % precyzja: 0.0000001
    [M5_6, M10_6, M20_6] = getAverageIterationsTime(30,0,1,0.0000001);
    
    
    % drukowanie wynikow na ekran (i do pliku)
    fprintf('--------------------------------------\n');
    fprintf('--------------------------------------\n');
    fprintf('MACIERZ SYMETRYCZNA, BEZ PRZESUNIEC\n');
    fprintf('--------------------------------------\n');
    fprintf('PRECYZJA: 0.1\n');
    fprintf('Macierze 5x5\n');
    fprintf('Srednia ilosc iteracji: %d\n', M5_1(1));
    fprintf('Sredni czas wykonania: %g\n', M5_1(2));
    fprintf('Macierze 10x10\n');
    fprintf('Srednia ilosc iteracji: %d\n', M10_1(1));
    fprintf('Sredni czas wykonania: %g\n', M10_1(2));
    fprintf('Macierze 20x20\n');
    fprintf('Srednia ilosc iteracji: %d\n', M20_1(1));
    fprintf('Sredni czas wykonania: %g\n', M20_1(2));
    fprintf('--------------------------------------\n');
    fprintf('PRECYZJA: 0.01\n');
    fprintf('Macierze 5x5\n');
    fprintf('Srednia ilosc iteracji: %d\n', M5_2(1));
    fprintf('Sredni czas wykonania: %g\n', M5_2(2));
    fprintf('Macierze 10x10\n');
    fprintf('Srednia ilosc iteracji: %d\n', M10_2(1));
    fprintf('Sredni czas wykonania: %g\n', M10_2(2));
    fprintf('Macierze 20x20\n');
    fprintf('Srednia ilosc iteracji: %d\n', M20_2(1));
    fprintf('Sredni czas wykonania: %g\n', M20_2(2));
    fprintf('--------------------------------------\n');
    fprintf('--------------------------------------\n');
    fprintf('MACIERZ SYMETRYCZNA, Z PRZESUNIECIEM\n');
    fprintf('--------------------------------------\n');
    fprintf('PRECYZJA: 0.00001\n');
    fprintf('Macierze 5x5\n');
    fprintf('Srednia ilosc iteracji: %d\n', M5_3(1));
    fprintf('Sredni czas wykonania: %g\n', M5_3(2));
    fprintf('Macierze 10x10\n');
    fprintf('Srednia ilosc iteracji: %d\n', M10_3(1));
    fprintf('Sredni czas wykonania: %g\n', M10_3(2));
    fprintf('Macierze 20x20\n');
    fprintf('Srednia ilosc iteracji: %d\n', M20_3(1));
    fprintf('Sredni czas wykonania: %g\n', M20_3(2));
    fprintf('--------------------------------------\n');
    fprintf('PRECYZJA: 0.0000001\n');
    fprintf('Macierze 5x5\n');
    fprintf('Srednia ilosc iteracji: %d\n', M5_4(1));
    fprintf('Sredni czas wykonania: %g\n', M5_4(2));
    fprintf('Macierze 10x10\n');
    fprintf('Srednia ilosc iteracji: %d\n', M10_4(1));
    fprintf('Sredni czas wykonania: %g\n', M10_4(2));
    fprintf('Macierze 20x20\n');
    fprintf('Srednia ilosc iteracji: %d\n', M20_4(1));
    fprintf('Sredni czas wykonania: %g\n', M20_4(2));
    fprintf('--------------------------------------\n');
    fprintf('--------------------------------------\n');
    fprintf('MACIERZ NIESYMETRYCZNA, Z PRZESUNIECIEM\n');
    fprintf('--------------------------------------\n');
    fprintf('PRECYZJA: 0.00001\n');
    fprintf('Macierze 5x5\n');
    fprintf('Srednia ilosc iteracji: %d\n', M5_5(1));
    fprintf('Sredni czas wykonania: %g\n', M5_5(2));
    fprintf('Macierze 10x10\n');
    fprintf('Srednia ilosc iteracji: %d\n', M10_5(1));
    fprintf('Sredni czas wykonania: %g\n', M10_5(2));
    fprintf('Macierze 20x20\n');
    fprintf('Srednia ilosc iteracji: %d\n', M20_5(1));
    fprintf('Sredni czas wykonania: %g\n', M20_5(2));
    fprintf('--------------------------------------\n');
    fprintf('PRECYZJA: 0.0000001\n');
    fprintf('Macierze 5x5\n');
    fprintf('Srednia ilosc iteracji: %d\n', M5_6(1));
    fprintf('Sredni czas wykonania: %g\n', M5_6(2));
    fprintf('Macierze 10x10\n');
    fprintf('Srednia ilosc iteracji: %d\n', M10_6(1));
    fprintf('Sredni czas wykonania: %g\n', M10_6(2));
    fprintf('Macierze 20x20\n');
    fprintf('Srednia ilosc iteracji: %d\n', M20_6(1));
    fprintf('Sredni czas wykonania: %g\n', M20_6(2));
    fprintf('--------------------------------------\n');
    
    if id > 0
        fprintf(id, '--------------------------------------\n');
        fprintf(id, '--------------------------------------\n');
        fprintf(id, 'MACIERZ SYMETRYCZNA, BEZ PRZESUNIEC\n');
        fprintf(id, '--------------------------------------\n');
        fprintf(id, 'PRECYZJA: 0.1\n');
        fprintf(id, 'Macierze 5x5\n');
        fprintf(id, 'Srednia ilosc iteracji: %d\n', M5_1(1));
        fprintf(id, 'Sredni czas wykonania: %g\n', M5_1(2));
        fprintf(id, 'Macierze 10x10\n');
        fprintf(id, 'Srednia ilosc iteracji: %d\n', M10_1(1));
        fprintf(id, 'Sredni czas wykonania: %g\n', M10_1(2));
        fprintf(id, 'Macierze 20x20\n');
        fprintf(id, 'Srednia ilosc iteracji: %d\n', M20_1(1));
        fprintf(id, 'Sredni czas wykonania: %g\n', M20_1(2));
        fprintf(id, '--------------------------------------\n');
        fprintf(id, 'PRECYZJA: 0.01\n');
        fprintf(id, 'Macierze 5x5\n');
        fprintf(id, 'Srednia ilosc iteracji: %d\n', M5_2(1));
        fprintf(id, 'Sredni czas wykonania: %g\n', M5_2(2));
        fprintf(id, 'Macierze 10x10\n');
        fprintf(id, 'Srednia ilosc iteracji: %d\n', M10_2(1));
        fprintf(id, 'Sredni czas wykonania: %g\n', M10_2(2));
        fprintf(id, 'Macierze 20x20\n');
        fprintf(id, 'Srednia ilosc iteracji: %d\n', M20_2(1));
        fprintf(id, 'Sredni czas wykonania: %g\n', M20_2(2));
        fprintf(id, '--------------------------------------\n');
        fprintf(id, '--------------------------------------\n');
        fprintf(id, 'MACIERZ SYMETRYCZNA, Z PRZESUNIECIEM\n');
        fprintf(id, '--------------------------------------\n');
        fprintf(id, 'PRECYZJA: 0.00001\n');
        fprintf(id, 'Macierze 5x5\n');
        fprintf(id, 'Srednia ilosc iteracji: %d\n', M5_3(1));
        fprintf(id, 'Sredni czas wykonania: %g\n', M5_3(2));
        fprintf(id, 'Macierze 10x10\n');
        fprintf(id, 'Srednia ilosc iteracji: %d\n', M10_3(1));
        fprintf(id, 'Sredni czas wykonania: %g\n', M10_3(2));
        fprintf(id, 'Macierze 20x20\n');
        fprintf(id, 'Srednia ilosc iteracji: %d\n', M20_3(1));
        fprintf(id, 'Sredni czas wykonania: %g\n', M20_3(2));
        fprintf(id, '--------------------------------------\n');
        fprintf(id, 'PRECYZJA: 0.0000001\n');
        fprintf(id, 'Macierze 5x5\n');
        fprintf(id, 'Srednia ilosc iteracji: %d\n', M5_4(1));
        fprintf(id, 'Sredni czas wykonania: %g\n', M5_4(2));
        fprintf(id, 'Macierze 10x10\n');
        fprintf(id, 'Srednia ilosc iteracji: %d\n', M10_4(1));
        fprintf(id, 'Sredni czas wykonania: %g\n', M10_4(2));
        fprintf(id, 'Macierze 20x20\n');
        fprintf(id, 'Srednia ilosc iteracji: %d\n', M20_4(1));
        fprintf(id, 'Sredni czas wykonania: %g\n', M20_4(2));
        fprintf(id, '--------------------------------------\n');
        fprintf(id, '--------------------------------------\n');
        fprintf(id, 'MACIERZ NIESYMETRYCZNA, Z PRZESUNIECIEM\n');
        fprintf(id, '--------------------------------------\n');
        fprintf(id, 'PRECYZJA: 0.00001\n');
        fprintf(id, 'Macierze 5x5\n');
        fprintf(id, 'Srednia ilosc iteracji: %d\n', M5_5(1));
        fprintf(id, 'Sredni czas wykonania: %g\n', M5_5(2));
        fprintf(id, 'Macierze 10x10\n');
        fprintf(id, 'Srednia ilosc iteracji: %d\n', M10_5(1));
        fprintf(id, 'Sredni czas wykonania: %g\n', M10_5(2));
        fprintf(id, 'Macierze 20x20\n');
        fprintf(id, 'Srednia ilosc iteracji: %d\n', M20_5(1));
        fprintf(id, 'Sredni czas wykonania: %g\n', M20_5(2));
        fprintf(id, '--------------------------------------\n');
        fprintf(id, 'PRECYZJA: 0.0000001\n');
        fprintf(id, 'Macierze 5x5\n');
        fprintf(id, 'Srednia ilosc iteracji: %d\n', M5_6(1));
        fprintf(id, 'Sredni czas wykonania: %g\n', M5_6(2));
        fprintf(id, 'Macierze 10x10\n');
        fprintf(id, 'Srednia ilosc iteracji: %d\n', M10_6(1));
        fprintf(id, 'Sredni czas wykonania: %g\n', M10_6(2));
        fprintf(id, 'Macierze 20x20\n');
        fprintf(id, 'Srednia ilosc iteracji: %d\n', M20_6(1));
        fprintf(id, 'Sredni czas wykonania: %g\n', M20_6(2));
        fprintf(id, '--------------------------------------\n');
    end
    
    % porownanie przykladowych wynikow
    A = getRandomMatrix(7,1);
    WA1 = getEigenvalNoShiftQR(A,0.00001,intmax);
    WA2 = eig(A);
    
    B = getRandomMatrix(7,1);
    WB1 = getEigenvalShiftQR(B,0.00001,intmax);
    WB2 = eig(B);
    
    C = getRandomMatrix(7,0);
    WC1 = getEigenvalShiftQR(C,0.00001,intmax);
    WC2 = eig(C);
    
    fprintf('--------------------------------------\n');
    fprintf('--------------------------------------\n');
    fprintf('POROWNANIE WYNIKOW LOSOWYCH MACIERZY:\n');
    fprintf('--------------------------------------\n');
    fprintf('Macierz symetryczna, bez przesuniec\n');
    fprintf('Wynik zaimplementowanej funkcji:\n');
    s = size(WA1,1);
    for i = 1 : s
        fprintf('%f\t',WA1(i));
    end
    fprintf('\nWynik wywolania eig:\n');
    s = size(WA2,1);
    for i = 1 : s
        fprintf('%f\t',WA2(i));
    end
    fprintf('\n--------------------------------------\n');
    fprintf('Macierz symetryczna, z przesunieciami\n');
    fprintf('Wynik zaimplementowanej funkcji:\n');
    s = size(WB1,1);
    for i = 1 : s
        fprintf('%f\t',WB1(i));
    end
    fprintf('\nWynik wywolania eig:\n');
    s = size(WB2,1);
    for i = 1 : s
        fprintf('%f\t',WB2(i));
    end
    fprintf('\n--------------------------------------\n');
    fprintf('Macierz niesymetryczna, z przesunieciami\n');
    fprintf('Wynik zaimplementowanej funkcji:\n');
    s = size(WC1,1);
    for i = 1 : s
        fprintf('%f\t',WC1(i));
    end
    fprintf('\nWynik wywolania eig:\n');
    s = size(WC2,1);
    for i = 1 : s
        fprintf('%f\t',WC2(i));
    end
    fprintf('\n--------------------------------------\n');
    
    if id > 0
        fprintf(id, '--------------------------------------\n');
        fprintf(id, '--------------------------------------\n');
        fprintf(id, 'POROWNANIE WYNIKOW LOSOWYCH MACIERZY:\n');
        fprintf(id, '--------------------------------------\n');
        fprintf(id, 'Macierz symetryczna, bez przesuniec\n');
        fprintf(id, 'Wynik zaimplementowanej funkcji:\n');
        s = size(WA1,1);
        for i = 1 : s
            fprintf(id, '%f\t',WA1(i));
        end
        fprintf(id, '\nWynik wywolania eig:\n');
        s = size(WA2,1);
        for i = 1 : s
            fprintf(id, '%f\t',WA2(i));
        end
        fprintf(id, '\n--------------------------------------\n');
        fprintf(id, 'Macierz symetryczna, z przesunieciami\n');
        fprintf(id, 'Wynik zaimplementowanej funkcji:\n');
        s = size(WB1,1);
        for i = 1 : s
            fprintf(id, '%f\t',WB1(i));
        end
        fprintf(id, '\nWynik wywolania eig:\n');
        s = size(WB2,1);
        for i = 1 : s
            fprintf(id, '%f\t',WB2(i));
        end
        fprintf(id, '\n--------------------------------------\n');
        fprintf(id, 'Macierz niesymetryczna, z przesunieciami\n');
        fprintf(id, 'Wynik zaimplementowanej funkcji:\n');
        s = size(WC1,1);
        for i = 1 : s
            fprintf(id, '%f\t',WC1(i));
        end
        fprintf(id, '\nWynik wywolania eig:\n');
        s = size(WC2,1);
        for i = 1 : s
            fprintf(id, '%f\t',WC2(i));
        end
        fprintf(id, '\n--------------------------------------\n');
    end
    fclose(id);
end

