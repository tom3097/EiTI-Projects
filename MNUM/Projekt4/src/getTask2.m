function [] = getTask2()
    %       dla punktu a)
    % ode45
    [Ta1,Xa1] = ode45(@xDot,[0 20],[8 7]);
    % 0.022 - rozbiezne
    [Ta2,Xa2,Ea2,MEa2] = getP4EK3ESolution([8 7]',0.022,20);
    % 0.020 - dokladne
    [Ta3,Xa3,Ea3,MEa3] = getP4EK3ESolution([8 7]',0.020,20);

    %       dla punktu b)
    % ode45
    [Tb1,Xb1] = ode45(@xDot,[0 20],[0 0.4]);
    % 1.034 - rozbiezne
    [Tb2,Xb2,Eb2,MEb2] = getP4EK3ESolution([0 0.4]',1.034,20);
    % 1.000 - znieksztalcone
    [Tb3,Xb3,Eb3,MEb3] = getP4EK3ESolution([0 0.4]',1.000,20);
    % 0.300 - dokladne
    [Tb4,Xb4,Eb4,MEb4] = getP4EK3ESolution([0 0.4]',0.300,20);

    %       dla punktu c)
    % ode45
    [Tc1,Xc1] = ode45(@xDot,[0 20],[5 0]);
    % 0.097 - rozbiezne
    [Tc2,Xc2,Ec2,MEc2] = getP4EK3ESolution([5 0]',0.097,20);
    % 0.090 - dokladne
    [Tc3,Xc3,Ec3,MEc3] = getP4EK3ESolution([5 0]',0.090,20);
    

    %       dla punktu d)
    % ode45
    [Td1,Xd1] = ode45(@xDot,[0 20],[0.01 0.001]);
    % 1.220 - rozbiezne
    [Td2,Xd2,Ed2,MEd2] = getP4EK3ESolution([0.01 0.001]',1.220,20);
    % 1.000 - znieksztalcone
    [Td3,Xd3,Ed3,MEd3] = getP4EK3ESolution([0.01 0.001]',1.000,20);
    % 0.004 - dokladne
    tic;
    [Td4,Xd4,Ed4,MEd4] = getP4EK3ESolution([0.01 0.001]',0.004,20);
    toc;
    
    
    %rysowanie i zapisywanie wykresow
    plot(Ta1,Xa1(:,1),'-',Ta1,Xa1(:,2),'-.');
    print('2aODE45X','-dpng');
    
    plot(Ta2,Xa2(:,1),'-',Ta2,Xa2(:,2),'-.');
    print('2a0022X','-dpng');
    
    plot(Ta2,Ea2(:,1),'-',Ta2,Ea2(:,2),'-.');
    print('2a0022E','-dpng');
    
    plot(Ta2,MEa2(:,1),'-',Ta2,MEa2(:,2),'-.');
    print('2a0022ME','-dpng');
    
    plot(Ta3,Xa3(:,1),'-',Ta3,Xa3(:,2),'-.');
    print('2a0020X','-dpng');
    
    plot(Ta3,Ea3(:,1),'-',Ta3,Ea3(:,2),'-.');
    print('2a0020E','-dpng');
    
    plot(Ta3,MEa3(:,1),'-',Ta3,MEa3(:,2),'-.');
    print('2a0020ME','-dpng');
    
    plot(Tb1,Xb1(:,1),'-',Tb1,Xb1(:,2),'-.');
    print('2bODE45X','-dpng');
    
    plot(Tb2,Xb2(:,1),'-',Tb2,Xb2(:,2),'-.');
    print('2b1034X','-dpng');
    
    plot(Tb2,Eb2(:,1),'-',Tb2,Eb2(:,2),'-.');
    print('2b1034E','-dpng');
    
    plot(Tb2,MEb2(:,1),'-',Tb2,MEb2(:,2),'-.');
    print('2b1034ME','-dpng');
    
    plot(Tb3,Xb3(:,1),'-',Tb3,Xb3(:,2),'-.');
    print('2b1000X','-dpng');
    
    plot(Tb3,Eb3(:,1),'-',Tb3,Eb3(:,2),'-.');
    print('2b1000E','-dpng');
    
    plot(Tb3,MEb3(:,1),'-',Tb3,MEb3(:,2),'-.');
    print('2b1000ME','-dpng');
    
    plot(Tb4,Xb4(:,1),'-',Tb4,Xb4(:,2),'-.');
    print('2b0300X','-dpng');
    
    plot(Tb4,Eb4(:,1),'-',Tb4,Eb4(:,2),'-.');
    print('2b0300E','-dpng');
    
    plot(Tb4,MEb4(:,1),'-',Tb4,MEb4(:,2),'-.');
    print('2b0300ME','-dpng');
    
    plot(Tc1,Xc1(:,1),'-',Tc1,Xc1(:,2),'-.');
    print('2cODE45X','-dpng');
    
    plot(Tc2,Xc2(:,1),'-',Tc2,Xc2(:,2),'-.');
    print('2c0097X','-dpng');
    
    plot(Tc2,Ec2(:,1),'-',Tc2,Ec2(:,2),'-.');
    print('2c0097E','-dpng');
    
    plot(Tc2,MEc2(:,1),'-',Tc2,MEc2(:,2),'-.');
    print('2c0097ME','-dpng');
    
    plot(Tc3,Xc3(:,1),'-',Tc3,Xc3(:,2),'-.');
    print('2c0090X','-dpng');
    
    plot(Tc3,Ec3(:,1),'-',Tc3,Ec3(:,2),'-.');
    print('2c0090E','-dpng');
    
    plot(Tc3,MEc3(:,1),'-',Tc3,MEc3(:,2),'-.');
    print('2c0090ME','-dpng');
    
    plot(Td1,Xd1(:,1),'-',Td1,Xd1(:,2),'-.');
    print('2dODE45X','-dpng');
    
    plot(Td2,Xd2(:,1),'-',Td2,Xd2(:,2),'-.');
    print('2d1220X','-dpng');
    
    plot(Td2,Ed2(:,1),'-',Td2,Ed2(:,2),'-.');
    print('2d1220E','-dpng');
    
    plot(Td2,MEd2(:,1),'-',Td2,MEd2(:,2),'-.');
    print('2d1220ME','-dpng');
    
    plot(Td3,Xd3(:,1),'-',Td3,Xd3(:,2),'-.');
    print('2d1000X','-dpng');
    
    plot(Td3,Ed3(:,1),'-',Td3,Ed3(:,2),'-.');
    print('2d1000E','-dpng');
    
    plot(Td3,MEd3(:,1),'-',Td3,MEd3(:,2),'-.');
    print('2d1000ME','-dpng');
    
    plot(Td4,Xd4(:,1),'-',Td4,Xd4(:,2),'-.');
    print('2d0004X','-dpng');
    
    plot(Td4,Ed4(:,1),'-',Td4,Ed4(:,2),'-.');
    print('2d0004E','-dpng');
    
    plot(Td4,MEd4(:,1),'-',Td4,MEd4(:,2),'-.');
    print('2d0004ME','-dpng');   
end

