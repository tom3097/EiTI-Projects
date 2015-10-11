/// Przygotowal: Tomasz Bochenski

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

const int WIDTH = 1000;
const int HEIGHT = 1000;

float Xcoordinate;
float Ycoordinate;
float time;

float maxFrameTime;
float currentFrameTime;
float increaseFrameTime;

float a,b;

/// UnconditionalDrawPoint zrobione w x86-64

extern void UnconditionalDrawPoint(float a, float b, float time);


void ConditionalDrawPoint(void)
{
    if(currentFrameTime < maxFrameTime)
        currentFrameTime = currentFrameTime + increaseFrameTime;
    else
    {
        currentFrameTime = 0.0;
        time  = time + 0.0015;

        UnconditionalDrawPoint(a,b,time);
    }
}

void Draw(int progressTime)
{
        ConditionalDrawPoint(); ///wyznaczamy wspolrzedne

        glutTimerFunc(progressTime, Draw, progressTime); /// rekursywne wywolanie timer_func
}

void Reshape( int width, int height )
{
    /// kolor tła - zawartość bufora koloru
    glClearColor( 0.0, 0.0, 0.0, 0.0 );         ///red - 0, green -0, blue - 0 czyli kolor czarny

    /// czyszczenie bufora koloru
    glClear( GL_COLOR_BUFFER_BIT );
    ConditionalDrawPoint();
}

void Keyboard( unsigned char key, int x, int y)
{
    if( key == '1')
        a += 0.2;
    else if( key == '2')
        a -= 0.2;
    else if( key == '3')
        b += 0.2;
    else if( key == '4')
        b -= 0.2;

    Reshape( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
}

/// stałe do obsługi menu podręcznego
enum
{
    EXIT /// wyjście
    ,CLEAR /// wyczysc ekran
    ,SHOW_PARAMETERS    /// wyswietl parametry
    ,SHOW_INSTRUCTION   /// wyswietl instrukcje
};

/// obsługa menu podręcznego
void Menu( int value )
{
    switch( value )
    {
        /// wyjście
        case EXIT:
            exit( 0 ); break;
        case CLEAR:
            /// kolor tła - zawartość bufora koloru
            glClearColor( 0.0, 0.0, 0.0, 0.0 );         ///red - 0, green -0, blue - 0 czyli kolor czarny

            /// czyszczenie bufora koloru
            glClear( GL_COLOR_BUFFER_BIT );
            ConditionalDrawPoint(); break;
        case SHOW_PARAMETERS:
            /// wypisywanie parametrow
            printf("-----------------------------------------------------------------\n");
	    printf("x = A * cos(a*t) + B * cos(b*t)	y = A * sin(a*t) + B * sin(b*t)\n");
            printf("Parametr A: 0.4\n");
            printf("Parametr B: 0.2\n");
            printf("Parametr a: %.1f\n", a);
            printf("Parametr b: %.1f\n", b);
            printf("-----------------------------------------------------------------\n");
            break;
        case SHOW_INSTRUCTION:
            /// a - predkosc katowa wokol dereferentu
            /// b - predkosc katowa wokol epicyklu
            printf("-----------------------------------------------------------------\n");
	    printf("x = A * cos(a*t) + B * cos(b*t)	y = A * sin(a*t) + B * sin(b*t)\n");
            printf("1 - zwieksz parametr a o 0.2\n");
            printf("2 - zmniejsz parametr a o 0.2\n");
            printf("3 - zwieksz parametr b o 0.2\n");
            printf("4 - zmniejsz parametr b o 0.2\n");
            printf("-----------------------------------------------------------------\n");
            break;
    }
}


int main( int argc, char * argv[] )
{
    a = 13;
    b = 35;
	

    /// ustawiam poczatkowe wspolrzedne
    Xcoordinate = Ycoordinate = 0;
    time = 0.0;

    maxFrameTime = 0.1;     /// 3.0 calkiem spoko
    currentFrameTime = 0.0;
    increaseFrameTime = 0.1;

    /// inicjalizacja biblioteki GLUT
    glutInit( & argc, argv );

    /// inicjalizacja bufora ramki
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );

    /// rozmiary głównego okna programu
    glutInitWindowSize( WIDTH, HEIGHT );

    /// utworzenie głównego okna programu
    glutCreateWindow( "PlanetTrajectory" );

    /// kolor tła - zawartość bufora koloru
    glClearColor( 0.0, 0.0, 0.0, 0.0 );         ///red - 0, green -0, blue - 0 czyli kolor czarny

    /// czyszczenie bufora koloru
    glClear( GL_COLOR_BUFFER_BIT );

    /// dołączenie funkcji generującej scenę 3D
    glutDisplayFunc( ConditionalDrawPoint );

    /// dołączenie funkcji wywoływanej przy zmianie rozmiaru okna
    glutReshapeFunc( Reshape );

    /// dolaczenie obslugi klawiatury
    glutKeyboardFunc( Keyboard );

    /// utworzenie menu podręcznego
    glutCreateMenu( Menu );

    /// dodatnie pozycji do menu podręcznego
    glutAddMenuEntry( "Wyjscie", EXIT );

    /// dodanie pozycji do menu podrecznego
    glutAddMenuEntry( "Wyczysc", CLEAR );

    /// dodanie pozycji do menu podrecznego
    glutAddMenuEntry( "Pokaz parametry", SHOW_PARAMETERS );

    /// dodanie pozycji do menu podrecznego
    glutAddMenuEntry( "Wyswietl instrukcje", SHOW_INSTRUCTION );

    /// określenie przycisku myszki obsługującej menu podręczne
    glutAttachMenu( GLUT_LEFT_BUTTON );

    Draw(1);              ///timer na 1ms

    glutMainLoop();

    return 0;
}

