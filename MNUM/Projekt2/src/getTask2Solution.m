% zadanie 2: glowna funkcja, zajmuje sie obliczaniem wynikow, ich
% prezentacja oraz zapisywaniem ich do pliku
function [] = getTask2Solution( )
    % otwieram plik do ktorego zapisze wyniki
    [id, kom] = fopen('wynikiTestowZad2P2.txt', 'wt');
    if id < 0
        disp(kom);
    end
    % tworze macierze X i Y z wartosciami podanymi w tresci zadania
    X = [ -5; -4; -3; -2; -1; 0; 1; 2; 3; 4; 5 ];
    Y = [ 63.6802; 33.2744; 16.1215; 4.7061; 0.2707; -0.1198; -0.0597;
        -0.0080; 3.4085; 12.0457; 25.2401 ];
    
    % wyznaczam funkcje aproksymujace dla wielomianow roznych rzedow na dwa
    % sposoby: za pomoca ukladu rownan normalnyvh oraz za pomoca ukladu
    % rownan liniowych z macierza R wynikaaca z rozkladu QR macierzy ukladu
    % rownan problemu:
    
    % dla wielomianu stopnia 1:
    % aproksymacja, wyznaczanie czasu oraz bledu rozwiazania
    [NormalSt1Coeff, NormalSt1Time] = getLZNKwithNormal(X,Y,1);
    [QRSt1Coeff, QRSt1Time] = getLZNKwithQR(X,Y,1);
    NormalSt1Err = getLZNKSolutionError(X,Y,NormalSt1Coeff);
    QRSt1Err = getLZNKSolutionError(X,Y,QRSt1Coeff);
    % drukowanie na ekran (i do pliku)
    fprintf('Stopien wielomianu: 1\n');
    fprintf('UKLAD ROWNAN NORMALNYCH:\n');
    fprintf('Blad rozwiazania: %e\n', NormalSt1Err);
    fprintf('Czas rozwiazania: %g\n', NormalSt1Time);
    fprintf('UKLAD ROWNAN Z MACIERZA R:\n');
    fprintf('Blad rozwiazania: %e\n', QRSt1Err);
    fprintf('Czas rozwiazania: %g\n', QRSt1Time);
    fprintf('------------------------------------\n');
    if id > 0
        fprintf(id, 'Stopien wielomianu: 1\n');
        fprintf(id, 'UKLAD ROWNAN NORMALNYCH:\n');
        fprintf(id, 'Blad rozwiazania: %e\n', NormalSt1Err);
        fprintf(id, 'Czas rozwiazania: %g\n', NormalSt1Time);
        fprintf(id, 'UKLAD ROWNAN Z MACIERZA R:\n');
        fprintf(id, 'Blad rozwiazania: %e\n', QRSt1Err);
        fprintf(id, 'Czas rozwiazania: %g\n', QRSt1Time);
        fprintf(id, '------------------------------------\n');
    end
    % generowanie wykresow
    getGraph(X,Y,NormalSt1Coeff);
    print('NormalStopien1','-dpng');
    getGraph(X,Y,QRSt1Coeff);
    print('QRStopien1','-dpng');
    
    % dla wielomianu stopnia 2:
    % aproksymacja, wyznaczanie czasu oraz bledu rozwiazania
    [NormalSt2Coeff, NormalSt2Time] = getLZNKwithNormal(X,Y,2);
    [QRSt2Coeff, QRSt2Time] = getLZNKwithQR(X,Y,2);
    NormalSt2Err = getLZNKSolutionError(X,Y,NormalSt2Coeff);
    QRSt2Err = getLZNKSolutionError(X,Y,QRSt2Coeff);
    % drukowanie na ekran (i do pliku)
    fprintf('Stopien wielomianu: 2\n');
    fprintf('UKLAD ROWNAN NORMALNYCH:\n');
    fprintf('Blad rozwiazania: %e\n', NormalSt2Err);
    fprintf('Czas rozwiazania: %g\n', NormalSt2Time);
    fprintf('UKLAD ROWNAN Z MACIERZA R:\n');
    fprintf('Blad rozwiazania: %e\n', QRSt2Err);
    fprintf('Czas rozwiazania: %g\n', QRSt2Time);
    fprintf('------------------------------------\n');
    if id > 0
        fprintf(id, 'Stopien wielomianu: 2\n');
        fprintf(id, 'UKLAD ROWNAN NORMALNYCH:\n');
        fprintf(id, 'Blad rozwiazania: %e\n', NormalSt2Err);
        fprintf(id, 'Czas rozwiazania: %g\n', NormalSt2Time);
        fprintf(id, 'UKLAD ROWNAN Z MACIERZA R:\n');
        fprintf(id, 'Blad rozwiazania: %e\n', QRSt2Err);
        fprintf(id, 'Czas rozwiazania: %g\n', QRSt2Time);
        fprintf(id, '------------------------------------\n');
    end
    % generowanie wykresow
    getGraph(X,Y,NormalSt2Coeff);
    print('NormalStopien2','-dpng');
    getGraph(X,Y,QRSt2Coeff);
    print('QRStopien2','-dpng');
    
    
    % dla wielomianu stopnia 3:
    % aproksymacja, wyznaczanie czasu oraz bledu rozwiazania
    [NormalSt3Coeff, NormalSt3Time] = getLZNKwithNormal(X,Y,3);
    [QRSt3Coeff, QRSt3Time] = getLZNKwithQR(X,Y,3);
    NormalSt3Err = getLZNKSolutionError(X,Y,NormalSt3Coeff);
    QRSt3Err = getLZNKSolutionError(X,Y,QRSt3Coeff);
    % drukowanie na ekran (i do pliku)
    fprintf('Stopien wielomianu: 3\n');
    fprintf('UKLAD ROWNAN NORMALNYCH:\n');
    fprintf('Blad rozwiazania: %e\n', NormalSt3Err);
    fprintf('Czas rozwiazania: %g\n', NormalSt3Time);
    fprintf('UKLAD ROWNAN Z MACIERZA R:\n');
    fprintf('Blad rozwiazania: %e\n', QRSt3Err);
    fprintf('Czas rozwiazania: %g\n', QRSt3Time);
    fprintf('------------------------------------\n');
    if id > 0
        fprintf(id, 'Stopien wielomianu: 3\n');
        fprintf(id, 'UKLAD ROWNAN NORMALNYCH:\n');
        fprintf(id, 'Blad rozwiazania: %e\n', NormalSt3Err);
        fprintf(id, 'Czas rozwiazania: %g\n', NormalSt3Time);
        fprintf(id, 'UKLAD ROWNAN Z MACIERZA R:\n');
        fprintf(id, 'Blad rozwiazania: %e\n', QRSt3Err);
        fprintf(id, 'Czas rozwiazania: %g\n', QRSt3Time);
        fprintf(id, '------------------------------------\n');
    end
    % generowanie wykresow
    getGraph(X,Y,NormalSt3Coeff);
    print('NormalStopien3','-dpng');
    getGraph(X,Y,QRSt3Coeff);
    print('QRStopien3','-dpng');
    
    % dla wielomianu stopnia 4:
    % aproksymacja, wyznaczanie czasu oraz bledu rozwiazania
    [NormalSt4Coeff, NormalSt4Time] = getLZNKwithNormal(X,Y,4);
    [QRSt4Coeff, QRSt4Time] = getLZNKwithQR(X,Y,4);
    NormalSt4Err = getLZNKSolutionError(X,Y,NormalSt4Coeff);
    QRSt4Err = getLZNKSolutionError(X,Y,QRSt4Coeff);
    % drukowanie na ekran (i do pliku)
    fprintf('Stopien wielomianu: 4\n');
    fprintf('UKLAD ROWNAN NORMALNYCH:\n');
    fprintf('Blad rozwiazania: %e\n', NormalSt4Err);
    fprintf('Czas rozwiazania: %g\n', NormalSt4Time);
    fprintf('UKLAD ROWNAN Z MACIERZA R:\n');
    fprintf('Blad rozwiazania: %e\n', QRSt4Err);
    fprintf('Czas rozwiazania: %g\n', QRSt4Time);
    fprintf('------------------------------------\n');
    if id > 0
        fprintf(id, 'Stopien wielomianu: 4\n');
        fprintf(id, 'UKLAD ROWNAN NORMALNYCH:\n');
        fprintf(id, 'Blad rozwiazania: %e\n', NormalSt4Err);
        fprintf(id, 'Czas rozwiazania: %g\n', NormalSt4Time);
        fprintf(id, 'UKLAD ROWNAN Z MACIERZA R:\n');
        fprintf(id, 'Blad rozwiazania: %e\n', QRSt4Err);
        fprintf(id, 'Czas rozwiazania: %g\n', QRSt4Time);
        fprintf(id, '------------------------------------\n');
    end
    % generowanie wykresow
    getGraph(X,Y,NormalSt4Coeff);
    print('NormalStopien4','-dpng');
    getGraph(X,Y,QRSt4Coeff);
    print('QRStopien4','-dpng');
    
    % dla wielomianu stopnia 5:
    % aproksymacja, wyznaczanie czasu oraz bledu rozwiazania
    [NormalSt5Coeff, NormalSt5Time] = getLZNKwithNormal(X,Y,5);
    [QRSt5Coeff, QRSt5Time] = getLZNKwithQR(X,Y,5);
    NormalSt5Err = getLZNKSolutionError(X,Y,NormalSt5Coeff);
    QRSt5Err = getLZNKSolutionError(X,Y,QRSt5Coeff);
    % drukowanie na ekran (i do pliku)
    fprintf('Stopien wielomianu: 5\n');
    fprintf('UKLAD ROWNAN NORMALNYCH:\n');
    fprintf('Blad rozwiazania: %e\n', NormalSt5Err);
    fprintf('Czas rozwiazania: %g\n', NormalSt5Time);
    fprintf('UKLAD ROWNAN Z MACIERZA R:\n');
    fprintf('Blad rozwiazania: %e\n', QRSt5Err);
    fprintf('Czas rozwiazania: %g\n', QRSt5Time);
    fprintf('------------------------------------\n');
    if id > 0
        fprintf(id, 'Stopien wielomianu: 5\n');
        fprintf(id, 'UKLAD ROWNAN NORMALNYCH:\n');
        fprintf(id, 'Blad rozwiazania: %e\n', NormalSt5Err);
        fprintf(id, 'Czas rozwiazania: %g\n', NormalSt5Time);
        fprintf(id, 'UKLAD ROWNAN Z MACIERZA R:\n');
        fprintf(id, 'Blad rozwiazania: %e\n', QRSt5Err);
        fprintf(id, 'Czas rozwiazania: %g\n', QRSt5Time);
        fprintf(id, '------------------------------------\n');
    end
    % generowanie wykresow
    getGraph(X,Y,NormalSt5Coeff);
    print('NormalStopien5','-dpng');
    getGraph(X,Y,QRSt5Coeff);
    print('QRStopien5','-dpng');
    
    % dla wielomianu stopnia 6:
    % aproksymacja, wyznaczanie czasu oraz bledu rozwiazania
    [NormalSt6Coeff, NormalSt6Time] = getLZNKwithNormal(X,Y,6);
    [QRSt6Coeff, QRSt6Time] = getLZNKwithQR(X,Y,6);
    NormalSt6Err = getLZNKSolutionError(X,Y,NormalSt6Coeff);
    QRSt6Err = getLZNKSolutionError(X,Y,QRSt6Coeff);
    % drukowanie na ekran (i do pliku)
    fprintf('Stopien wielomianu: 6\n');
    fprintf('UKLAD ROWNAN NORMALNYCH:\n');
    fprintf('Blad rozwiazania: %e\n', NormalSt6Err);
    fprintf('Czas rozwiazania: %g\n', NormalSt6Time);
    fprintf('UKLAD ROWNAN Z MACIERZA R:\n');
    fprintf('Blad rozwiazania: %e\n', QRSt6Err);
    fprintf('Czas rozwiazania: %g\n', QRSt6Time);
    fprintf('------------------------------------\n');
    if id > 0
        fprintf(id, 'Stopien wielomianu: 6\n');
        fprintf(id, 'UKLAD ROWNAN NORMALNYCH:\n');
        fprintf(id, 'Blad rozwiazania: %e\n', NormalSt6Err);
        fprintf(id, 'Czas rozwiazania: %g\n', NormalSt6Time);
        fprintf(id, 'UKLAD ROWNAN Z MACIERZA R:\n');
        fprintf(id, 'Blad rozwiazania: %e\n', QRSt6Err);
        fprintf(id, 'Czas rozwiazania: %g\n', QRSt6Time);
        fprintf(id, '------------------------------------\n');
    end
    % generowanie wykresow
    getGraph(X,Y,NormalSt6Coeff);
    print('NormalStopien6','-dpng');
    getGraph(X,Y,QRSt6Coeff);
    print('QRStopien6','-dpng');
    
    % dla wielomianu stopnia 7:
    % aproksymacja, wyznaczanie czasu oraz bledu rozwiazania
    [NormalSt7Coeff, NormalSt7Time] = getLZNKwithNormal(X,Y,7);
    [QRSt7Coeff, QRSt7Time] = getLZNKwithQR(X,Y,7);
    NormalSt7Err = getLZNKSolutionError(X,Y,NormalSt7Coeff);
    QRSt7Err = getLZNKSolutionError(X,Y,QRSt7Coeff);
    % drukowanie na ekran (i do pliku)
    fprintf('Stopien wielomianu: 7\n');
    fprintf('UKLAD ROWNAN NORMALNYCH:\n');
    fprintf('Blad rozwiazania: %e\n', NormalSt7Err);
    fprintf('Czas rozwiazania: %g\n', NormalSt7Time);
    fprintf('UKLAD ROWNAN Z MACIERZA R:\n');
    fprintf('Blad rozwiazania: %e\n', QRSt7Err);
    fprintf('Czas rozwiazania: %g\n', QRSt7Time);
    fprintf('------------------------------------\n');
    if id > 0
        fprintf(id, 'Stopien wielomianu: 7\n');
        fprintf(id, 'UKLAD ROWNAN NORMALNYCH:\n');
        fprintf(id, 'Blad rozwiazania: %e\n', NormalSt7Err);
        fprintf(id, 'Czas rozwiazania: %g\n', NormalSt7Time);
        fprintf(id, 'UKLAD ROWNAN Z MACIERZA R:\n');
        fprintf(id, 'Blad rozwiazania: %e\n', QRSt7Err);
        fprintf(id, 'Czas rozwiazania: %g\n', QRSt7Time);
        fprintf(id, '------------------------------------\n');
    end
    % generowanie wykresow
    getGraph(X,Y,NormalSt7Coeff);
    print('NormalStopien7','-dpng');
    getGraph(X,Y,QRSt7Coeff);
    print('QRStopien7','-dpng');
    
    % dla wielomianu stopnia 8:
    % aproksymacja, wyznaczanie czasu oraz bledu rozwiazania
    [NormalSt8Coeff, NormalSt8Time] = getLZNKwithNormal(X,Y,8);
    [QRSt8Coeff, QRSt8Time] = getLZNKwithQR(X,Y,8);
    NormalSt8Err = getLZNKSolutionError(X,Y,NormalSt8Coeff);
    QRSt8Err = getLZNKSolutionError(X,Y,QRSt8Coeff);
    % drukowanie na ekran (i do pliku)
    fprintf('Stopien wielomianu: 8\n');
    fprintf('UKLAD ROWNAN NORMALNYCH:\n');
    fprintf('Blad rozwiazania: %e\n', NormalSt8Err);
    fprintf('Czas rozwiazania: %g\n', NormalSt8Time);
    fprintf('UKLAD ROWNAN Z MACIERZA R:\n');
    fprintf('Blad rozwiazania: %e\n', QRSt8Err);
    fprintf('Czas rozwiazania: %g\n', QRSt8Time);
    fprintf('------------------------------------\n');
    if id > 0
        fprintf(id, 'Stopien wielomianu: 8\n');
        fprintf(id, 'UKLAD ROWNAN NORMALNYCH:\n');
        fprintf(id, 'Blad rozwiazania: %e\n', NormalSt8Err);
        fprintf(id, 'Czas rozwiazania: %g\n', NormalSt8Time);
        fprintf(id, 'UKLAD ROWNAN Z MACIERZA R:\n');
        fprintf(id, 'Blad rozwiazania: %e\n', QRSt8Err);
        fprintf(id, 'Czas rozwiazania: %g\n', QRSt8Time);
        fprintf(id, '------------------------------------\n');
    end
    % generowanie wykresow
    getGraph(X,Y,NormalSt8Coeff);
    print('NormalStopien8','-dpng');
    getGraph(X,Y,QRSt8Coeff);
    print('QRStopien8','-dpng');
    
    % dla wielomianu stopnia 9:
    % aproksymacja, wyznaczanie czasu oraz bledu rozwiazania
    [NormalSt9Coeff, NormalSt9Time] = getLZNKwithNormal(X,Y,9);
    [QRSt9Coeff, QRSt9Time] = getLZNKwithQR(X,Y,9);
    NormalSt9Err = getLZNKSolutionError(X,Y,NormalSt9Coeff);
    QRSt9Err = getLZNKSolutionError(X,Y,QRSt9Coeff);
    % drukowanie na ekran (i do pliku)
    fprintf('Stopien wielomianu: 9\n');
    fprintf('UKLAD ROWNAN NORMALNYCH:\n');
    fprintf('Blad rozwiazania: %e\n', NormalSt9Err);
    fprintf('Czas rozwiazania: %g\n', NormalSt9Time);
    fprintf('UKLAD ROWNAN Z MACIERZA R:\n');
    fprintf('Blad rozwiazania: %e\n', QRSt9Err);
    fprintf('Czas rozwiazania: %g\n', QRSt9Time);
    fprintf('------------------------------------\n');
    if id > 0
        fprintf(id, 'Stopien wielomianu: 9\n');
        fprintf(id, 'UKLAD ROWNAN NORMALNYCH:\n');
        fprintf(id, 'Blad rozwiazania: %e\n', NormalSt9Err);
        fprintf(id, 'Czas rozwiazania: %g\n', NormalSt9Time);
        fprintf(id, 'UKLAD ROWNAN Z MACIERZA R:\n');
        fprintf(id, 'Blad rozwiazania: %e\n', QRSt9Err);
        fprintf(id, 'Czas rozwiazania: %g\n', QRSt9Time);
        fprintf(id, '------------------------------------\n');
    end
    % generowanie wykresow
    getGraph(X,Y,NormalSt9Coeff);
    print('NormalStopien9','-dpng');
    getGraph(X,Y,QRSt9Coeff);
    print('QRStopien9','-dpng');
    
    % dla wielomianu stopnia 10:
    % aproksymacja, wyznaczanie czasu oraz bledu rozwiazania
    [NormalSt10Coeff, NormalSt10Time] = getLZNKwithNormal(X,Y,10);
    [QRSt10Coeff, QRSt10Time] = getLZNKwithQR(X,Y,10);
    NormalSt10Err = getLZNKSolutionError(X,Y,NormalSt10Coeff);
    QRSt10Err = getLZNKSolutionError(X,Y,QRSt10Coeff);
    % drukowanie na ekran (i do pliku)
    fprintf('Stopien wielomianu: 10\n');
    fprintf('UKLAD ROWNAN NORMALNYCH:\n');
    fprintf('Blad rozwiazania: %e\n', NormalSt10Err);
    fprintf('Czas rozwiazania: %g\n', NormalSt10Time);
    fprintf('UKLAD ROWNAN Z MACIERZA R:\n');
    fprintf('Blad rozwiazania: %e\n', QRSt10Err);
    fprintf('Czas rozwiazania: %g\n', QRSt10Time);
    fprintf('------------------------------------\n');
    if id > 0
        fprintf(id, 'Stopien wielomianu: 10\n');
        fprintf(id, 'UKLAD ROWNAN NORMALNYCH:\n');
        fprintf(id, 'Blad rozwiazania: %e\n', NormalSt10Err);
        fprintf(id, 'Czas rozwiazania: %g\n', NormalSt10Time);
        fprintf(id, 'UKLAD ROWNAN Z MACIERZA R:\n');
        fprintf(id, 'Blad rozwiazania: %e\n', QRSt10Err);
        fprintf(id, 'Czas rozwiazania: %g\n', QRSt10Time);
        fprintf(id, '------------------------------------\n');
    end
    % generowanie wykresow
    getGraph(X,Y,NormalSt10Coeff);
    print('NormalStopien10','-dpng');
    getGraph(X,Y,QRSt10Coeff);
    print('QRStopien10','-dpng');
    fclose(id);
end

