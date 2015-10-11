% glowna funkcja obliczajaca pierwiastki
function [ ] = getTask1Sol( )
    iter = 15;
    % ** DLA PRZEDZIALOW MONOTONICZNYCH **
    % przedzial dla pierwszego pierwiastka
    xl1 = 4.46;
    xr1 = 8.01;
    % przedzial dla drugiego pierwiastka
    xl2 = 8.04;
    xr2 = 10.7;
    % PIERWSZY PIERWIASTEK
    % metoda bisekcji
    [b1x, b1y, b1t] = getBisMethSol(@f,xl1,xr1,iter);
    % metoda siecznych
    [s1x, s1y, s1t] = getSecantMethSol(@f,xl1,xr1,iter);
    % DRUGI PIERWIASTEK
    % metoda bisekcji
    [b2x, b2y, b2t] = getBisMethSol(@f,xl2,xr2,iter);
    % metoda siecznych
    [s2x, s2y, s2t] = getSecantMethSol(@f,xl2,xr2,iter);
    % ** DLA MAKSYMALNYCH PRZEDZIALOW W KTORYCH OBA SPOSOBY ZBIEGAJA DO
    % ROZWIAZANIA **
    % przedzial dla pierwszego pierwiastka
    xxl1 = 0;
    xxr1 = 8.2;
    % przedzial dla drugiego pierwiastka
    xxl2 = 7.5;
    xxr2 = 12.1;
    % PIERWSZY PIERWIASTEK
    % metoda bisekcji
    [bb1x, bb1y, bb1t] = getBisMethSol(@f,xxl1,xxr1,iter);
    % metoda siecznych
    [ss1x, ss1y, ss1t] = getSecantMethSol(@f,xxl1,xxr1,iter);
    % DRUGI PIERWIASTEK
    % metoda bisekcji
    [bb2x, bb2y, bb2t] = getBisMethSol(@f,xxl2,xxr2,iter);
    % metoda siecznych
    [ss2x, ss2y, ss2t] = getSecantMethSol(@f,xxl2,xxr2,iter);
    
    fprintf('PIERWSZY PIERWIASTEK - PRZEDZIAL (4.46;8.01)\n');
    fprintf('\n');
    fprintf('metoda bisekcji\n');
    for i = 1 : iter
        fprintf('Iteracja: %d\n', i);
        fprintf('Miejsce zerowe: %g\n', b1x(i));
        fprintf('Wartosc funkcji: %g\n',b1y(i));
        fprintf('Czas: %g\n',b1t(i));
    end
    fprintf('\n');
    fprintf('metoda siecznych\n');
    for i = 1 : iter
        fprintf('Iteracja: %d\n', i);
        fprintf('Miejsce zerowe: %g\n', s1x(i));
        fprintf('Wartosc funkcji: %g\n',s1y(i));
        fprintf('Czas: %g\n',s1t(i));
    end
    fprintf('\n');
    fprintf('DRUGI PIERWIASTEK - PRZEDZIAL (8.04;10.7)\n');
    fprintf('\n');
    fprintf('metoda bisekcji\n');
    for i = 1 : iter
        fprintf('Iteracja: %d\n', i);
        fprintf('Miejsce zerowe: %g\n', b2x(i));
        fprintf('Wartosc funkcji: %g\n',b2y(i));
        fprintf('Czas: %g\n',b2t(i));
    end
    fprintf('\n');
    fprintf('metoda siecznych\n');
    for i = 1 : iter
        fprintf('Iteracja: %d\n', i);
        fprintf('Miejsce zerowe: %g\n', s2x(i));
        fprintf('Wartosc funkcji: %g\n',s2y(i));
        fprintf('Czas: %g\n',s2t(i));
    end
    fprintf('PIERWSZY PIERWIASTEK - PRZEDZIAL (0;8.2)\n');
    fprintf('\n');
    fprintf('metoda bisekcji\n');
    for i = 1 : iter
        fprintf('Iteracja: %d\n', i);
        fprintf('Miejsce zerowe: %g\n', bb1x(i));
        fprintf('Wartosc funkcji: %g\n',bb1y(i));
        fprintf('Czas: %g\n',bb1t(i));
    end
    fprintf('\n');
    fprintf('metoda siecznych\n');
    for i = 1 : iter
        fprintf('Iteracja: %d\n', i);
        fprintf('Miejsce zerowe: %g\n', ss1x(i));
        fprintf('Wartosc funkcji: %g\n',ss1y(i));
        fprintf('Czas: %g\n',ss1t(i));
    end
    fprintf('\n');
    fprintf('DRUGI PIERWIASTEK - PRZEDZIAL (7.5;12.1)\n');
    fprintf('\n');
    fprintf('metoda bisekcji\n');
    for i = 1 : iter
        fprintf('Iteracja: %d\n', i);
        fprintf('Miejsce zerowe: %g\n', bb2x(i));
        fprintf('Wartosc funkcji: %g\n',bb2y(i));
        fprintf('Czas: %g\n',bb2t(i));
    end
    fprintf('\n');
    fprintf('metoda siecznych\n');
    for i = 1 : iter
        fprintf('Iteracja: %d\n', i);
        fprintf('Miejsce zerowe: %g\n', ss2x(i));
        fprintf('Wartosc funkcji: %g\n',ss2y(i));
        fprintf('Czas: %g\n',ss2t(i));
    end
end

