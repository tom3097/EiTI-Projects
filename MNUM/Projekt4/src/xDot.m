% funkcja wyznaczajaca nowe wartosci x
% PRZYJMOWANE ARGUMENTY:
% t - czas
% x - ostatnio wyznaczone wartosci
function [ dx ] = xDot( t, x )
    % wyznaczanie nowych wartosci x
    dx = zeros(2,1);
    dx(1,1) = x(2,1)+x(1,1)*(0.2-x(1,1)*x(1,1)-x(2,1)*x(2,1));
    dx(2,1) = -x(1,1)+x(2,1)*(0.2-x(1,1)*x(1,1)-x(2,1)*x(2,1));
end

