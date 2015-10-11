;	Przygotowal: Tomasz Bocheński	;
;	void UnconditionalDrawPoint(float a, float b, float time)	;

section	.data
	A:		dq	0.4
	B:		dq	0.2
	PointSize:	dd	2.0
	RedCo:		dd	1.0
	GreenCo:	dd	0.698
	BlueCo:		dd	0.4
	P_PI:		dq	3.141592
	M_PI:		dq	-3.141592
	PI_D		dq	1.570796
	corr:		dq	0.3
	ONE		dq	1.0
	M_ONE		dq	-1.0

section	.text
global UnconditionalDrawPoint

extern glColor3f
extern glPointSize
extern glBegin
extern glVertex3d
extern glEnd
extern glFlush
extern glutSwapBuffers


UnconditionalDrawPoint:

	push	rbp			; na stos trafia aktualny wskaznik ramki
	mov	rbp,	rsp 		; ustawiam nowy wskaznik ramki

; callee saved registers ;
	push	rbx
	push	r12
	push	r13
	push	r14
	push	r15

; konwertuje argumenty do double ;
	cvtss2sd	xmm0,	xmm0	; a = (double)a
	cvtss2sd	xmm1,	xmm1	; b = (double)b
	cvtss2sd	xmm2,	xmm2	; time = (double)time

; obliczam argumenty funkcji sin ;
	movsd	xmm3,	xmm0		; xmm3 = a
	mulsd	xmm3,	xmm2		; xmm3 = a*t
	movsd	xmm4,	xmm1		; xmm4 = b
	mulsd	xmm4,	xmm2		; xmm4 = b*t

; przed wywolaniem funkcji odkladam wszystko na stos ;
	sub	rsp,	8
	movsd	[rsp],	xmm3		; odkladam a*t
	sub	rsp,	8
	movsd	[rsp],	xmm4		; odkladam b*t

; laduje argument funkcji sin ;
	movsd	xmm0,	xmm3		; argument funkcji

; obliczam sin(a*t) ;
	call	Sin

; zdejmuje b*t, a*t ze stosu ;
	movsd	xmm4,	[rsp]		; xmm4 = b*t	
	add	rsp,	8
	movsd	xmm3,	[rsp]		; xmm3 = a*t
	add	rsp,	8

; odkladam na stos sin(a*t), b*t ;
	sub	rsp,	8
	movsd	[rsp],	xmm0		; odkladam na stos wynik sin(a*t)
	sub	rsp,	8
	movsd	[rsp],	xmm4		; odkladam na stos b*t

; laduje argument funkcji sin ;
	movsd	xmm5,	[PI_D]		; xmm5 = pi/2
	addsd	xmm3,	xmm5		; xmm3 = a*t + pi/2
	movsd	xmm0,	xmm3		; argument funkcji

; obliczam cos(a*t) ;
	call	Sin

; zdejmuje b*t ze stosu ;
	movsd	xmm4,	[rsp]		; xmm4 = b*t	
	add	rsp,	8

; odkladam na stos cos(a*t), b*t ;
	sub	rsp,	8
	movsd	[rsp],	xmm0		; odkladam na stos wynik cos(a*t)
	sub	rsp,	8
	movsd	[rsp],	xmm4		; odkladam na stos b*t

; laduje argument funkcji sin ;
	movsd	xmm0,	xmm4		; argument funkcji

; obliczam sin(b*t) ;
	call	Sin

; zdejmuje b*t ze stosu ;
	movsd	xmm4,	[rsp]		; xmm4 = b*t	
	add	rsp,	8

; odkladam sin(b*t) na stos ;
	sub	rsp,	8
	movsd	[rsp],	xmm0		; odkladam na stos wynik sin(b*t)

; laduje argument operacji ;
	movsd	xmm5,	[PI_D]		; xmm5 = pi/2
	addsd	xmm4,	xmm5		; xmm4 = b*t + pi/2
	movsd	xmm0,	xmm4		; argument funkcji

; obliczam cos(b*t) ;
	call	Sin

; odkladam na stos cos(b*t) ;
	sub	rsp,	8
	movsd	[rsp],	xmm0		; odkladam na stos wynik cos(b*t)

; w tej chwili mam na stosie wszystkie obliczone sin i cos ;

; zdejmuje wszystkie obliczone wartosci i umieszczam je w odpowiednich rejestrach ;	
	movsd	xmm0,	[rsp]		; xmm0 = cos(b*t)	
	add	rsp,	8
	movsd	xmm1,	[rsp]		; xmm1 = sin(b*t)	
	add	rsp,	8
	movsd	xmm2,	[rsp]		; xmm2 = cos(a*t)	
	add	rsp,	8
	movsd	xmm3,	[rsp]		; xmm3 = sin(a*t)	
	add	rsp,	8

; obliczam x = A * cos(t*a) + B * cos(t*b) ;
	movsd	xmm4,	[A]		; xmm4 = A
	mulsd	xmm4,	xmm2		; xmm4 = A * cos(t*a)
	movsd	xmm5,	[B]		; xmm5 = B
	mulsd	xmm5,	xmm0		; xmm5 = B * cos(t*b)
	addsd	xmm4,	xmm5		; xmm4 = A * cos(t*a) + B * cos(t*b) = x

; obliczam y = A * sin(t*a) + B * sin(b*t) ;
	movsd	xmm6,	[A]		; xmm6 = A
	mulsd	xmm6,	xmm3		; xmm6 = A * sin(t*a)
	movsd	xmm7,	[B]		; xmm7 = B
	mulsd	xmm7,	xmm1		; xmm7 = B * sin(b*t)
	addsd	xmm6,	xmm7		; xmm6 = A * sin(t*a) + B * sin(b*t) = y

; odkladam na stos obliczone wartosci x i y ;	
	sub	rsp,	8
	movsd	[rsp],	xmm4		; x na stos
	sub	rsp,	8
	movsd	[rsp],	xmm6		; y na stos

; wywolywanie funkcji z biblioteki GL ;

; glColor3f - przygotowanie do wywolania ;
	movss	xmm0,	[RedCo]
	movss	xmm1,	[GreenCo]
	movss	xmm2,	[BlueCo]
; glColor3f - koniec przygotowan ;

; wywolanie funkcji glColor3f ;
	call	glColor3f

; glPointSize - przygotowanie do wywolania ;
	movss	xmm0,	[PointSize]	; wstawiam rozmiar punktow	
; glPointSize - koniec przygotowan ;
	
; wywolanie funkcji glPointSize ;
	call	glPointSize

; glBegin - przygotowanie do wywolania ;
	xor	rdi,	rdi		; rdi = 0
; glBegin - koniec przygotowan ;
	
; wywolanie funkcji glBegin ;
	call	glBegin

; glVertex3d - przygotowanie do wywolania ;
	movsd	xmm1,	[rsp]		; zdejmuje ze stosu y
	add	rsp,	8	
	movsd	xmm0,	[rsp]		; zdejmuje ze stosu x
	add	rsp,	8
	movsd	xmm3,	[corr]		; laduje korekte
	subsd	xmm1,	xmm3		; odejmuje poprawke
	xorpd	xmm2,	xmm2		; xmm2 = 0.0, trzeci argument funkcji
; glVertex3d - koniec przygotowan ;

; wywolanie funkcji glVertex3d ;
	call	glVertex3d

; wywolanie funkcji glEnd ;
	call	glEnd

; wywolanie funkcji glFlush ;
	call	glFlush

; wywolanie funkcji glutSwapBuffers ;
	call glutSwapBuffers

; callee saved registers ;
	pop	r15
	pop	r14
	pop	r13
	pop	r12
	pop	rbx

	mov	rsp,	rbp		; wskaznik stosu wraca w polozenie wskaznika ramki
	pop	rbp			; ustawiam poprzedni wskaznik stosu
	ret


;...:::funkcja pomocnicza - Sin:::...;

Sin:
	push	rbp			; na stos trafia aktualny wskaznik ramki
	mov	rbp,	rsp		; ustawiam nowy wskaznik ramki

; callee saved registers ;
	push	rbx
	push	r12
	push	r13
	push	r14
	push	r15

; koryguje wartosc argumentu ;
correct_loop:
	ucomisd	xmm0,	[P_PI]		; xmm - PI
	ja	Minus2Pi		; jesli >0 odejmuje 2 * PI
	ucomisd	xmm0,	[M_PI]		; xmm + PI
	jb	Plus2Pi			; jesli <0 dodaje 2 * PI
	jmp	correct_end
Plus2Pi:
	addsd	xmm0,	[P_PI]		; xmm0 = xmm0 + PI
	addsd	xmm0,	[P_PI]		; xmm0 = xmm0 + PI
	jmp	correct_loop

Minus2Pi:
	subsd	xmm0,	[P_PI]		; xmm0 = xmm0 - PI
	subsd	xmm0,	[P_PI]		; xmm0 = xmm0 - PI
	jmp	correct_loop

; teraz w xmm0 znajduje sie nowa wartosc x z zakresu [-PI, PI] ;
correct_end:

; uzupelniam poczatkowe wartosci rejestrow wykorzystywanych przy liczeniu sin ;
	movsd	xmm1,	xmm0		; xmm1 = xmm0, tu trzymamy x
	movsd	xmm2,	xmm0		; xmm2 = xmm0, tu trzymamy wynik
	movsd	xmm3,	[ONE]		; xmm3 = 1, zmienna s
	movsd	xmm4,	xmm0		; xmm4 - aktualna potega x
	movsd	xmm5,	[ONE]		; xmm5 = 1, aktualna wartosc silni
	movsd	xmm6,	[M_ONE]		; xmm6 = -1, stala -1

; rejestry pomocnicze w realizacji petli ;
	mov	rax,	3		; rax = 3
	mov	rcx,	100		; rcx = 100

sin_loop:
	cmp	rax,	rcx		; rax - rcx
	jg	sin_end			; zakoncz liczenie sinusa

; korekta potegi x ;
	mulsd	xmm4,	xmm1
	mulsd	xmm4,	xmm1

; korekta silni ;
	cvtsi2sd	xmm7,	eax
	mulsd	xmm5,	xmm7		; xmm5 = xmm5 * xmm7
	addsd	xmm7,	xmm6		; xmm7 = zmm7 + (-1)
	mulsd	xmm5,	xmm7		; xmm5 = xmm5 * xmm7

; korekta s ;
	mulsd	xmm3,	xmm6		; xmm3(s) = xmm3(s) * xmm6(-1)

; majac wszystkie dane koryguje aktualny wynik sinusa ;
	movsd	xmm7,	xmm4		; xmm7 = xmm4	
	divsd	xmm7,	xmm5		; wynik dzialania Pow/Fact umieszczam w xmm7
	mulsd	xmm7,	xmm3		; xmm7 = xmm7(pow/fact) * xmm3(s)
	addsd	xmm2,	xmm7		; xmm2(wynik) = xmm2(wynik) + s*(pow/fact)

; aktualizacja licznika petli ;
	add	rax,	2		; zwiekszam i o 2

; skacze do poczatku petli ;
	jmp	sin_loop

sin_end:
; wynik sinusa odkladamy do rejestru xmm0 ;
	movsd	xmm0,	xmm2

; callee saved registers ;
	pop	r15
	pop	r14
	pop	r13
	pop	r12
	pop	rbx
	
	mov	rsp,	rbp	; przywracamy wskaznik stosu
	pop	rbp		; przywracamy wskaznik ramki
	ret

