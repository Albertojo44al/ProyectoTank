#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <list>

 
#define ARRIBA 72
#define ABAJO 80
#define IZQUIERDA 75
#define DERECHA 77

using namespace std;
int diref;
int falb = 0;
int xb, yb=0;

void gotoxy(int x, int y)
{

	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;

	SetConsoleCursorPosition(hCon, dwPos);

}

void OcultarCursor() {
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 2;
	cci.bVisible = false;
	SetConsoleCursorInfo(hCon, &cci);
}
void pintar_limites() {
	for (int x = 2; x < 200; x++) {
		gotoxy(x, 3); printf("%c", 205);
		gotoxy(x, 50); printf("%c", 205);
	}
	for (int x = 4; x < 50; x++) {
		gotoxy(2, x); printf("%c", 186);
		gotoxy(200, x); printf("%c", 186);
	}
	gotoxy(2, 3); printf("%c", 201);
	gotoxy(2, 50); printf("%c", 200);
	gotoxy(200, 3); printf("%c", 187);
	gotoxy(200, 50); printf("%c", 188);
}
class Tank
{
	int x, y;
	int corazones;
public:
	Tank(int _x, int _y, int _corazones) :x(_x), y(_y), corazones(_corazones) {};
	int X() { return x; }
	int Y() { return y; }
	void COR() { corazones--; }//funcion el atributo corazones decrezca en uno
	void pintarAr();
	void pintarAb();
	void pintarD();
	void pintarI();
	

	void moverp1();
	void moverp2();
	void borrarIz();
	void borrarAr();
	void borrarAb();
	void borrarDr();
	void mover();
	void choque(Tank &N);//fiuncion que detecte la colision (se crea una estructura de la clase nave)
	void pintar_corazones();
	void bala();
};

void Tank::pintarAr() {
	gotoxy(x, y); printf(" %c ", 95);
	gotoxy(x, y - 1); printf("%c%c%c", 177, 82, 177);
	gotoxy(x, y - 2); printf(" %c ", 94);
}
void Tank::pintarAb() {
	gotoxy(x, y); printf("%c%c%c", 177, 220, 177);
	gotoxy(x, y - 1); printf("%c%c%c", 220, 82, 220);
	gotoxy(x, y + 1); printf(" %c ", 118);
}
void Tank::pintarD() {
	gotoxy(x, y); printf("%c%c%c", 220, 220, 220);
	gotoxy(x, y - 1); printf("%c%c%c", 220, 220, 220);
	gotoxy(x + 3, y); printf("%c", 62);
}
void Tank::pintarI() {
	gotoxy(x, y); printf("%c%c%c", 220, 220, 220);
	gotoxy(x, y - 1); printf("%c%c%c", 220, 220, 220);
	gotoxy(x - 3, y); printf("%c", 60);
}
void Tank::borrarAr() {
	gotoxy(x, y); printf("   ");
	gotoxy(x, y - 1); printf("   ");
	gotoxy(x, y - 2); printf("   ");
}
void Tank::borrarAb() {
	gotoxy(x, y); printf("   ");
	gotoxy(x, y - 1); printf("   ");
	gotoxy(x, y + 1); printf("   ");

}
void Tank::borrarDr() {
	gotoxy(x, y); printf("   ");
	gotoxy(x, y - 1); printf("   ");
	gotoxy(x + 3, y); printf("   ");
}
void Tank::borrarIz() {
	gotoxy(x, y); printf("   ");
	gotoxy(x, y - 1); printf("   ");
	gotoxy(x - 3, y); printf("    ");
}
void Tank::moverp1() {
	if (_kbhit()) {
		char tecla = _getch();

		if (tecla == IZQUIERDA && x - 2 > 4)
		{
			borrarIz();
			borrarAr();
			borrarAb();
			borrarDr();
			x--;
			pintarI();
		}
		if (tecla == DERECHA && x + 6 < 150)
		{
			borrarIz();
			borrarAr();
			borrarAb();
			borrarDr();
			x++;
			pintarD();
		}
		if (tecla == ARRIBA && y - 2 > 6)
		{
			borrarIz();
			borrarAr();
			borrarAb();
			borrarDr();
			y--;
			pintarAr();
		}
		if (tecla == ABAJO && y + 3 < 53)
		{
			borrarIz();
			borrarAr();
			borrarAb();
			borrarDr();
			y++; pintarAb();
		}

	}
}
void Tank::bala() {
	 {
		gotoxy(xb, yb); printf("*");
		if (falb == 1 && xb < 93 && xb > 4 && yb > 4 && yb < 43) {
			if (diref == 0) {
				xb++;
			}
			else {
				if (diref == 1) {
					xb--;
				}
			}
			if (diref == 2) {
				yb--;
			}
			else {
				if (diref == 3) {
					yb++;
				}
			}
			gotoxy(xb, yb); printf("%c", 169);
		}
		else {
			falb = 0;
		}
	}
}
void Tank::moverp2() {
	if (_kbhit()) {
		char tecla = _getch();
		if (tecla == 'a'&& x - 2 > 4)
		{
			borrarIz();
			borrarAr();
			borrarAb();
			borrarDr();
			x--;
			pintarI();

		}
		if (tecla == 'd' && x + 6 < 150)
		{
			borrarIz();
			borrarAr();
			borrarAb();
			borrarDr();
			x++;
			pintarD();

		}
		if (tecla == 'w'&& y - 2 > 6)
		{
			borrarIz();
			borrarAr();
			borrarAb();
			borrarDr();
			y--;
			pintarAr();

		}
		if (tecla == 's' && y + 3 < 53)
		{
			borrarIz();
			borrarAr();
			borrarAb();
			borrarDr();
			y++;
			pintarAb();

		}
		if (tecla == ' ') {
			if (diref == 0) {
				xb = x + 5;
				yb = y + 1;
			}
			else {
				if (diref == 1) {
					xb = x - 1;
					yb = y + 1;
				}
			}
			if (diref == 2) {
				xb = x + 2;
				yb = y - 1;
			}
			else {
				if (diref == 3) {
					xb = x + 2;
					yb = y + 3;
				}
			}
			falb = 1;

		}
	}
}
void clean() {
	gotoxy(50, 24); printf("                     ");
	gotoxy(50, 25); printf("                     ");
	gotoxy(50, 26); printf("                     ");
	gotoxy(50, 27); printf("                     ");
	gotoxy(50, 28); printf("                     ");
}

int main() {
	char tecla;
	do {
		pintar_limites();
		gotoxy(50, 24); printf("TANK GAME ");
		gotoxy(50, 25); printf("1. Player vs CPU");
		gotoxy(50, 26); printf("2. Player vs Player");
		gotoxy(50, 27); printf("3. STATS");
		gotoxy(50, 28); printf("4. SALIR");

		tecla = _getch();
		if (tecla == '1')
		{
			clean();
			OcultarCursor();
			pintar_limites();
			Tank T(7, 7, 3);



			bool game_over = false;
			T.pintarAr();
			while (!game_over) {



				T.moverp2();
				T.bala();
				Sleep(30);
			}
			return 0;

		}
		if(tecla=='2'){
			clean();
			OcultarCursor();
			pintar_limites();

			bool gameover = false;
			Tank T1(50, 30, 2);
			Tank T2(10, 20, 3);
			T1.pintarAr();
			T2.pintarAb();

			while (!gameover) {
				T1.moverp1();
				Sleep(20);
				T2.moverp2();
				Sleep(20);
			}
		}

	} while (tecla != '4');

	

}