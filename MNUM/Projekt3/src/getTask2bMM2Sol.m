function [] = getTask2bMM2Sol( )
    iter = 10;
    % PIERWSZY PIERWIASTEK
    xb1 = -2;
    [x1r, y1r, t1r] = getMM2Sol(@f2,@df2,@ddf2,xb1,iter);
    xb2 = -1;
    [x2r, y2r, t2r] = getMM2Sol(@f2,@df2,@ddf2,xb2,iter);
    % DRUGI/TRZECI PIERWIASTEK
    xb3 = 0;
    [x3r, y3r, t3r] = getMM2Sol(@f2,@df2,@ddf2,xb3,iter);
    xb4 = 3;
    [x4r, y4r, t4r] = getMM2Sol(@f2,@df2,@ddf2,xb4,iter);
    % TRZECI/CZWARTY PIERWIASTEK
    xb5 = 4;
    [x5r, y5r, t5r] = getMM2Sol(@f2,@df2,@ddf2,xb5,iter);
    xb6 = 5;
    [x6r, y6r, t6r] = getMM2Sol(@f2,@df2,@ddf2,xb6,iter);
    
    % wypisywanie wynikow 
    fprintf('Punkt startowy x0 = -2\n');
    for i = 1 : iter
        fprintf('Iteracja: %d\n', i);
        fprintf('Miejsce zerowe: %s\n', num2str(x1r(i)));
        fprintf('Wartosc funkcji: %s\n',num2str(y1r(i)));
        fprintf('Czas: %g\n',t1r(i));
    end
    fprintf('\n');
    fprintf('Punkt startowy x0 = -1\n');
    for i = 1 : iter
        fprintf('Iteracja: %d\n', i);
        fprintf('Miejsce zerowe: %s\n', num2str(x2r(i)));
        fprintf('Wartosc funkcji: %s\n',num2str(y2r(i)));
        fprintf('Czas: %g\n',t2r(i));
    end
    fprintf('\n');
    fprintf('Punkt startowy x0 = 0\n');
    for i = 1 : iter
        fprintf('Iteracja: %d\n', i);
        fprintf('Miejsce zerowe: %s\n', num2str(x3r(i)));
        fprintf('Wartosc funkcji: %s\n',num2str(y3r(i)));
        fprintf('Czas: %g\n',t3r(i));
    end
    fprintf('\n');
    
    fprintf('Punkt startowy x0 = 3\n');
    for i = 1 : iter
        fprintf('Iteracja: %d\n', i);
        fprintf('Miejsce zerowe: %s\n', num2str(x4r(i)));
        fprintf('Wartosc funkcji: %s\n',num2str(y4r(i)));
        fprintf('Czas: %g\n',t4r(i));
    end
    fprintf('\n');
    fprintf('Punkt startowy x0 = 4\n');
    for i = 1 : iter
        fprintf('Iteracja: %d\n', i);
        fprintf('Miejsce zerowe: %s\n', num2str(x5r(i)));
        fprintf('Wartosc funkcji: %s\n',num2str(y5r(i)));
        fprintf('Czas: %g\n',t5r(i));
    end
    fprintf('\n');
    fprintf('Punkt startowy x0 = 5\n');
    for i = 1 : iter
        fprintf('Iteracja: %d\n', i);
        fprintf('Miejsce zerowe: %s\n', num2str(x6r(i)));
        fprintf('Wartosc funkcji: %s\n',num2str(y6r(i)));
        fprintf('Czas: %g\n',t6r(i));
    end
    fprintf('\n');
end

