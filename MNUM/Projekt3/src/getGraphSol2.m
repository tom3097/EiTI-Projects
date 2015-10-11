function [] = getGraphSol2()
    x = -2 : 0.1 : 7;
    y = zeros(1,size(x,2));
    for i = 1 : size(x,2)
        y(1,i) = f2(x(1,i));
    end
    z1 = -1.2445;
    z2 = 5.4142;
    plot(x,y,z1,0,'rs',z2,0,'rs');
end

