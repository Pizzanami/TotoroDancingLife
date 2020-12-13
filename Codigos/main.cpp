#include "Shell.cpp"

Window ventana("Totoro Dancing Life", 700, 500);

typedef struct{
	COLORREF** imagen;
	int nr, nc;
}Image;
//COLORREF** createImage(int nr, int nc);
Image createImage(char *name);
void freeImage(Image *img);

int main(){	
	Image FramesTotoro[27];
	int nr, nc, x=10,y=10;
	FramesTotoro[0] = createImage("01.bmp");
	// leemos en bmp
	LeeBmpColor(FramesTotoro[0].imagen, "01.bmp");
	
	// dibujamos el bmp en la posicion (x,y) con zoom=1.0
	ventana.PlotCBitmap(FramesTotoro[0].imagen, FramesTotoro[0].nr, FramesTotoro[0].nc, 0, 0, 1.0);
	
	freeImage(&FramesTotoro[0]);
	
	return MainLoop();
}

Image createImage(char *name){
	// memoria para la imagen de dimensiones nr por nc
	Image img;
	
	// leo dimensiones del bmp
	DimensionesBmp(name, &img.nr, &img.nc);
	int i;
	
	img.imagen = (COLORREF**) malloc(img.nr * sizeof(COLORREF*));
	for (i=0; i < img.nr; i++){
		img.imagen[i] = (COLORREF*) malloc(img.nc * sizeof(COLORREF));
	}
	
	return img;
}

void freeImage(Image *img){	
	int i;
	
	for (i=0; i < img->nr; i++){
		free(img->imagen[i]);
	}
	
	free(img->imagen);
}

