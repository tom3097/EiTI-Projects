function [ ] = CompMM2andNewton( )
    iter = 10;
    x1 = 20;
    [x1r, y1r, t1r] = getNewtonMethSol(@f2,@df2,x1,iter);
    [x2r, y2r, t2r] = getMM2Sol(@f2,@df2,@ddf2,x1,iter);

    fprintf('Metoda Newtona\n');
    for i = 1 : iter
        fprintf('Iteracja: %d\n', i);
        fprintf('Miejsce zerowe: %s\n', num2str(x1r(i)));
        fprintf('Wartosc funkcji: %s\n',num2str(y1r(i)));
        fprintf('Czas: %g\n',t1r(i));
    end
    fprintf('\n');
    fprintf('Metoda MM2\n');
    for i = 1 : iter
        fprintf('Iteracja: %d\n', i);
        fprintf('Miejsce zerowe: %s\n', num2str(x2r(i)));
        fprintf('Wartosc funkcji: %s\n',num2str(y2r(i)));
        fprintf('Czas: %g\n',t2r(i));
    end
    fprintf('\n');
end

