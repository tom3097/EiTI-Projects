% funkcja generujaca macierz o losowych wartosciach
% funkcja przyjmuje dwa argumenty: pierwszy (n) okresla stopien macierzy
% kwadratowej ktora ma zostac wygenerowana, drugi (flag) okresla czy
% macierz ma byc symetryczna czy niesymetryczna; gdy flag wynosi 0
% generowana jest macierz niesymetryczna, w przeciwnym przypadku zostaje
% stworzona macierz symetryczna
function [ M ] = getRandomMatrix( n, flag )
    % generuje losowa macierz M
    M = randi([-2,1],n,n) + rand(n,n);
    % w razie potrzeby przeksztalcam ja do macierzy symetrycznej
    if flag ~= 0
        M = M + M';
    end
end

