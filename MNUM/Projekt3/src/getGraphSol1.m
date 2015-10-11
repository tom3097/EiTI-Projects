% funkcja rysujaca wykres wraz z miejscami zerowymi dla zad I
function [] = getGraphSol1()
    x = -0.5 : 0.1 : 12.5;
    y = f(x);
    z1 = 7.379;
    z2 = 8.704;
    pp1 = 4.46;
    fpp1 = f(pp1);
    kp1 = 8.01;
    fkp1 = f(kp1);
    pp2 = 0;
    fpp2 = f(pp2);
    kp2 = 8.2;
    fkp2 = f(kp2);
    pd1 = 8.04;
    fpd1 = f(pd1);
    kd1 = 10.7;
    fkd1 = f(kd1);
    pd2 = 7.5;
    fpd2 = f(pd2);
    kd2 = 12.1;
    fkd2 = f(kd2);
    % rysowanie wykresu
    plot(x,y,z1,0,'rs',z2,0,'rs',pp1,fpp1,'bo',kp1,fkp1,'bo',pd1,fpd1,'mo',kd1,fkd1,'mo',pp2,fpp2,'rd',kp2,fkp2,'rd',pd2,fpd2,'kh',kd2,fkd2,'kh');
end

