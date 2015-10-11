function [] = getComplexGraph2()
    rex1 = -1.24445;
    imx1 = 0;
    rex2 = 5.41415;
    imx2 = 0;
    rex3 = -0.08485;
    imx3 = 0.66186;
    rex4 = -0.08485;
    imx4 = -0.66186;
    plot(rex1,imx1,'rs',rex2,imx2,'rs',rex3,imx3,'rs',rex4,imx4,'rs');
    xlabel('real');
    ylabel('imaginary');
end

