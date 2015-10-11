function [ ] = getTask2Solution( )
    % ZADANIE 2
    % otwieram plik do ktorego zapisze wyniki
    [id, kom] = fopen('wynikiTestowZad2.txt', 'wt');
    if id < 0
        disp(kom);
    end
    % inicjuje zmienna okreslajaca ilosc prob
    numberOfAttempts = 8;
    % wywoluje testy dla wszystkich danych
    [n1, e1, t1] = testZad2(numberOfAttempts, 1);
    [n2, e2, t2] = testZad2(numberOfAttempts, 2);
    [n3, e3, t3] = testZad2(numberOfAttempts, 3);
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
    % wykres bledu od n dla danych 1
    subplot(3,1,1);
    plot(n1,e1,'r.');
    title('Dane 1');
    xlabel('Wymiar macierzy');
    ylabel('Blad');
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
    % wykres bledu od n dla danych 2
    subplot(3,1,2);
    plot(n2,e2,'m.');
    title('Dane 2');
    xlabel('Wymiar macierzy');
    ylabel('Blad');
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
    % wykres bledu od n dla danych 3
    subplot(3,1,3);
    plot(n3,e3,'b.');
    title('Dane 3');
    xlabel('Wymiar macierzy');
    ylabel('Blad');
    fclose(id);
end

