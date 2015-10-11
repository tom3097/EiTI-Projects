function [ ] = getTask3Solution( )
    % ZADANIE 3
    % otwieram plik do ktorego zapisze wyniki
    [id, kom] = fopen('wynikiTestowZad3.txt', 'wt');
    if id < 0
        disp(kom);
    end
    % inicjuje zmienna okreslajaca maksymalna ilosc iteracji
    maxIter = 100;
    fprintf('\tILOSC ITERACJI: %d\n', maxIter);
    if id > 0
        fprintf(id, '\tILOSC ITERACJI: %d\n', maxIter);
    end
    % uklad rownan podany w otrzymanym zadaniu
    A = [ 15 3 -2 -8; 3 -12 -1 9; 7 3 35 18; 1 1 1 5];
    b = [ 5; -2; 29; 10];
    [x,~] = JCB(A, b, maxIter );
    % wyznaczam residuum
    residuum = A*x - b;
    % wyznaczam norme residuum
    residuumNorm = norm(residuum);
    fprintf('--------------------------\n');
    fprintf('Rozwiazanie ukladu rownan podanego w zadaniu:\n');
    fprintf('x1 = %f, x2 = %f, x3 = %f, x4 = %f\n', x(1),x(2),x(3),x(4));
    fprintf('Blad rozwiazania ukladu rownan podanego w zadaniu:\n');
    fprintf('blad = %g\n\n', residuumNorm);
    fprintf('--------------------------\n');
    if id > 0
        fprintf(id, '--------------------------\n');
        fprintf(id, 'Rozwiazanie ukladu rownan podanego w zadaniu:\n');
        fprintf(id, 'x1 = %f, x2 = %f, x3 = %f, x4 = %f\n', x(1),x(2),x(3),x(4));
        fprintf(id, 'Blad rozwiazania ukladu rownan podanego w zadaniu:\n');
        fprintf(id, 'blad = %g\n\n', residuumNorm);
        fprintf(id, '--------------------------\n');
    end
    % rysuje wykres zaleznosci bledu rozwiazania od ilosci iteracji dla
    % ukladu rownan podanego w otrzymanym zadaniu
    [I,E] = getDataForGraphJCB(A,b,15);
    plot(I,E,'r.');
    title('Wykres zaleznosci bledu od liczby iteracji');
    xlabel('Liczba iteracji');
    ylabel('Blad');
    % inicjuje zmienna okreslajaca ilosc prob
    numberOfAttempts = 10;
    % wywoluje testy dla wszystkich danych
    [n1, e1, t1] = testZad3(numberOfAttempts, 1, maxIter);
    [n2, e2, t2] = testZad3(numberOfAttempts, 2, maxIter);
    [n3, e3, t3] = testZad3(numberOfAttempts, 3, maxIter);
    % wyniki testow dla danych 1
    fprintf('\tDANE 1:\n');
    if id > 0
        fprintf(id, '\tDANE 1:\n');
    end
    for i = 1: numberOfAttempts
        fprintf('--------------------------\n');
        fprintf('Wymiar macierzy: %d\n', n1(i));
        fprintf('Blad rozwiazania: %e\n', e1(i));
        fprintf('Czas rozwiazania: %f\n', t1(i));
        if id > 0
            fprintf(id, '--------------------------\n');
            fprintf(id, 'Wymiar macierzy: %d\n', n1(i));
            fprintf(id, 'Blad rozwiazania: %e\n', e1(i));
            fprintf(id, 'Czas rozwiazania: %f\n', t1(i));
        end
    end
    % wyniki testow dla danych 2
    fprintf('\tDANE 2:\n');
    if id > 0
        fprintf(id, '\tDANE 2:\n');
    end
    for i = 1: numberOfAttempts
        fprintf('--------------------------\n');
        fprintf('Wymiar macierzy: %d\n', n2(i));
        fprintf('Blad rozwiazania: %e\n', e2(i));
        fprintf('Czas rozwiazania: %f\n', t2(i));
        if id > 0
            fprintf(id, '--------------------------\n');
            fprintf(id, 'Wymiar macierzy: %d\n', n2(i));
            fprintf(id, 'Blad rozwiazania: %e\n', e2(i));
            fprintf(id, 'Czas rozwiazania: %f\n', t2(i));
        end
    end
    % wyniki testow dla danych 3
    fprintf('\tDANE 3:\n');
    if id > 0
        fprintf(id, '\tDANE 3:\n');
    end
    for i = 1: numberOfAttempts
        fprintf('--------------------------\n');
        fprintf('Wymiar macierzy: %d\n', n3(i));
        fprintf('Blad rozwiazania: %e\n', e3(i));
        fprintf('Czas rozwiazania: %f\n', t3(i));
        if id > 0
            fprintf(id, '--------------------------\n');
            fprintf(id, 'Wymiar macierzy: %d\n', n3(i));
            fprintf(id, 'Blad rozwiazania: %e\n', e3(i));
            fprintf(id, 'Czas rozwiazania: %f\n', t3(i));
        end
    end
    fclose(id);
end

