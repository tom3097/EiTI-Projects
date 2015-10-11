function [ ] = getTask2aSol( )
    iter = 10;
    % PIERWSZY PIERWIASTEK
    x1 = -20;
    [x1r, y1r, t1r] = getNewtonMethSol(@f2,@df2,x1,iter);
    x2 = -10;
    [x2r, y2r, t2r] = getNewtonMethSol(@f2,@df2,x2,iter);
    x3 = 0;
    [x3r, y3r, t3r] = getNewtonMethSol(@f2,@df2,x3,iter);
    % DRUGI PIERWIASTEK
    x4 = 10;
    [x4r, y4r, t4r] = getNewtonMethSol(@f2,@df2,x4,iter);
    x5 = 20;
    [x5r, y5r, t5r] = getNewtonMethSol(@f2,@df2,x5,iter);
    x6 = 30;
    [x6r, y6r, t6r] = getNewtonMethSol(@f2,@df2,x6,iter);
    
    fprintf('PIERWSZY PIERWIASTEK\n');
    
    fprintf('Punkt startowy x0 = -20\n');
    for i = 1 : iter
        fprintf('Iteracja: %d\n', i);
        fprintf('Miejsce zerowe: %g\n', x1r(i));
        display(x1r(i));
        fprintf('\n');
        fprintf('Wartosc funkcji: %g\n',y1r(i));
        fprintf('Czas: %g\n',t1r(i));
    end
    fprintf('\n');
    fprintf('Punkt startowy x0 = -10\n');
    for i = 1 : iter
        fprintf('Iteracja: %d\n', i);
        fprintf('Miejsce zerowe: %g\n', x2r(i));
        fprintf('Wartosc funkcji: %g\n',y2r(i));
        fprintf('Czas: %g\n',t2r(i));
    end
    fprintf('\n');
    fprintf('Punkt startowy x0 = 0\n');
    for i = 1 : iter
        fprintf('Iteracja: %d\n', i);
        fprintf('Miejsce zerowe: %g\n', x3r(i));
        fprintf('Wartosc funkcji: %g\n',y3r(i));
        fprintf('Czas: %g\n',t3r(i));
    end
    fprintf('\n');
    
    fprintf('DRUGI PIERWIASTEK\n');
   
    fprintf('Punkt startowy x0 = 10\n');
    for i = 1 : iter
        fprintf('Iteracja: %d\n', i);
        fprintf('Miejsce zerowe: %g\n', x4r(i));
        fprintf('Wartosc funkcji: %g\n',y4r(i));
        fprintf('Czas: %g\n',t4r(i));
    end
    fprintf('\n');
    fprintf('Punkt startowy x0 = 20\n');
    for i = 1 : iter
        fprintf('Iteracja: %d\n', i);
        fprintf('Miejsce zerowe: %g\n', x5r(i));
        fprintf('Wartosc funkcji: %g\n',y5r(i));
        fprintf('Czas: %g\n',t5r(i));
    end
    fprintf('\n');
    fprintf('Punkt startowy x0 = 30\n');
    for i = 1 : iter
        fprintf('Iteracja: %d\n', i);
        fprintf('Miejsce zerowe: %g\n', x6r(i));
        fprintf('Wartosc funkcji: %g\n',y6r(i));
        fprintf('Czas: %g\n',t6r(i));
    end
    fprintf('\n');
end

