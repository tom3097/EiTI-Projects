% funkcja pomocnicza do wyznaczania wartosci wlasnych macierzy kwadratowej
% stopnia 2
% wartosci wlasne sa wylicznane bezposrednio z definicji, czyli szukam
% takich x, ktore spelniaja rownania det(A-xI) = 0
% niech A = [A(1,1), A(1,2); A(2,1), A(2,2)]
% wtedy rownanie charakterystyczne jest postaci: 
% (A(1,1)-x) * (A(2,2)-x) - A(1,2) * A(2,1) = 0
% postac po przeksztalceniach:
% x^2 + x[-A(1,1)-A(2,2)] + [A(1,1)*A(2,2)-A(1,2)*A(2,1)]
% delta po przeksztalceniach:
% delta = A^2(1,1)+A^2(2,2)-2*A(1,1)*A(2,2)+4*A(1,2)*A(2,1)
% wartosci x1 i x2 po przeksztalceniach:
% x1 = [A(1,1)+A(2,2)-sqrt(delta)]/2
% x2 = [A(1,1)+A(2,2)+sqrt(delta)]/2
% funkcja pobiera jeden argument: maicerz kwadratowa stopnia 2 ktorej
% wartosci wlasne nalezy wyznaczyc
% funkcja zwraca macierz wyznaczonych wartosci wlasnych
function [ eval ] = getEigenvalOf2x2Matrix( A )
    % alokuje pamiec na macierz wynikowa eval
    eval = zeros(2,1);
    % obliczam delte rownania charakterystycznego
    delta = A(1,1)*A(1,1)+A(2,2)*A(2,2)-2*A(1,1)*A(2,2)+4*A(1,2)*A(2,1);
    % obliczam wartosci wlasne macierzy
    eval(1) = (A(1,1)+A(2,2)-sqrt(delta))/2;
    eval(2) = (A(1,1)+A(2,2)+sqrt(delta))/2;
end

