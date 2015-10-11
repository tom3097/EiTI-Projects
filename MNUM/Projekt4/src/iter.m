function [xk] = iter( xp, step )
    % obliczam nowe wspolrzedne x
    k1 = xDot(0, xp);
    k2 = xDot(0, xp+(step/2)*k1);
    k3 = xDot(0, xp+(step/2)*k2);
    k4 = xDot(0, xp+step*k3);
    xk = xp+(step/6)*(k1+2*k2+2*k3+k4);    
end

