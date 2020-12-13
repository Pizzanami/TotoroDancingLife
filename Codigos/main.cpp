#include "Shell.cpp"

Window ventana("Totoro Dancing Life", 256, 144);

// colores
COLORREF rojo  = RGB(255,0,0);
COLORREF verde = RGB(0,255,0);
COLORREF azul  = RGB(0,0,255);

int main()
{
	int x=10, y=10, diam=5;
	COLORREF pixel_color;
	
	// dibuja un punto de diametro diam en las coordenas (x,y)
	ventana.PutPixel(x, y, diam, rojo);
	ventana.Paint();
	
	return MainLoop();
}

