function [  ] = getTask2bMM1Sol(  )
   iter = 10;
   xl1 = -8;
   xm1 = 7;
   xr1 = 14;
   [x1r,y1r,t1r] = getMM1Sol(@f2,xl1,xm1,xr1,iter);
   xl2 = -5;
   xm2 = 3;
   xr2 = 10;
   [x2r,y2r,t2r] = getMM1Sol(@f2,xl2,xm2,xr2,iter);
   xl3 = -10;
   xm3 = -2;
   xr3 = 3;
   [x3r,y3r,t3r] = getMM1Sol(@f2,xl3,xm3,xr3,iter);
   
   fprintf('xl = -8, xm = 7, xr = 14\n');
   for i = 1 : iter
       fprintf('Iteracja: %d\n', i);
       fprintf('Miejsce zerowe: %s\n', num2str(x1r(i)));
       fprintf('Wartosc funkcji: %s\n',num2str(y1r(i)));        
       fprintf('Czas: %g\n',t1r(i));
   end
   fprintf('\n');
   fprintf('xl = -5, xm = 3, xr = 10\n');
   for i = 1 : iter
       fprintf('Iteracja: %d\n', i);
       fprintf('Miejsce zerowe: %s\n', num2str(x2r(i)));
       fprintf('Wartosc funkcji: %s\n',num2str(y2r(i)));
       fprintf('Czas: %g\n',t2r(i));
   end
   fprintf('\n');
   fprintf('xl = -10, xm = -2, xr = 3\n');
   for i = 1 : iter
       fprintf('Iteracja: %d\n', i);
       fprintf('Miejsce zerowe: %s\n', num2str(x3r(i)));
       fprintf('Wartosc funkcji: %s\n',num2str(y3r(i)));
       fprintf('Czas: %g\n',t3r(i));
   end
   fprintf('\n');
end

