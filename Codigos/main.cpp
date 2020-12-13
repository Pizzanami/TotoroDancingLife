#include "Shell.cpp"

Window ventana("Totoro Dancing Life", 700, 500);

COLORREF** createImage(int nr, int nc);
void freeImage(COLORREF** imagen, int nr);

int main()
{	
	int nr, nc, x=10,y=10;
	COLORREF** imagen;
	
	// leo dimensiones del bmp
	DimensionesBmp("01.bmp", &nr, &nc); // solo bmp de 24 bits
	
	// memoria para la imagen
	imagen = createImage(nr, nc);
	
	// leemos en bmp
	LeeBmpColor(imagen, "01.bmp");
	
	// dibujamos el bmp en la posicion (x,y) con zoom=1.0
	ventana.PlotCBitmap(imagen, nr, nc, x, y, 1.0);
	
	freeImage(imagen, nr);
	
	return MainLoop();
}

COLORREF** createImage(int nr, int nc)
{
	// memoria para la imagen de dimensiones nr por nc
	int i;
	COLORREF** imagen;
	
	imagen = (COLORREF**) malloc(nr * sizeof(COLORREF*));
	for (i=0; i < nr; i++){
		imagen[i] = (COLORREF*) malloc(nc * sizeof(COLORREF));
	}
	
	return imagen;
}

void freeImage(COLORREF** imagen, int nr)
{	
	int i;
	
	for (i=0; i < nr; i++){
		free(imagen[i]);
	}
	
	free(imagen);
}

