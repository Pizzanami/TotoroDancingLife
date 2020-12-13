#include "Shell.cpp"

Window ventana("Totoro Dancing Life", 500, 450);

typedef struct{
	COLORREF** imagen;
	int nr, nc;
}Image;

Image FramesTotoro[27];
Image createImage(char *name);
void freeImage(Image *img);
void secuenciaSalida();
void brinco1(unsigned int *key);
void brinco2(unsigned int *key);
void brinco3(unsigned int *key);

int main(){	
	int i;
	
	for(i = 0; i < 27; i++){
		char filename[100];
		
		if(i <10)
			sprintf(filename, "frames_24\\0%d.bmp", i);
		else
			sprintf(filename, "frames_24\\%d.bmp", i);
		
		// memoria para la imagen i
		FramesTotoro[i] = createImage(filename);
		
		// leemos en bmp
		LeeBmpColor(FramesTotoro[i].imagen, filename);
	}
	
	i = 0;
	unsigned int key = 9;
	while(1){
		
		// Kbhit() regresa 1 si el usuario presiono una tecla en el teclado, regresa 0 si no presiono nada
		// guarda la tecla presionada en la variable key
		int resultado = (int) Kbhit(&key);
		
		if (resultado == 1)
			ventana.PlotCBitmap(FramesTotoro[i].imagen, FramesTotoro[i].nr, FramesTotoro[i].nc, 0, 0, 1.0);
		if(key == 49 || key==70){
			brinco1(&key);
		}
		if(key == 50 || key==71){
			brinco2(&key);
		}
		if(key == 51 || key==72){
			brinco3(&key);
		}
		if (key== 88){
			secuenciaSalida();
			return 0;
		}
		i = (i+1)%27;
		
		int x = 10, y = 400;
	
		// imprime texto en la posicion (x,y) de la pantalla
		ventana.printf(x, y, "Hola mundo %i", key);
		Sleep(200);
	}
	
	for(i = 0; i < 27; i++)
		freeImage(&FramesTotoro[i]);
	
	return MainLoop();
}
void brinco1(unsigned int *key){
	*key = 0;
	int i;
	for(i = 4; i < 18; i++){
		ventana.PlotCBitmap(FramesTotoro[i].imagen, FramesTotoro[i].nr, FramesTotoro[i].nc, 0, 0, 1.0);
		Sleep(150);
	}
}

void brinco2(unsigned int *key){
	*key = 0;
	int i;
	for(i = 13; i < 18; i++){
		ventana.PlotCBitmap(FramesTotoro[i].imagen, FramesTotoro[i].nr, FramesTotoro[i].nc, 0, 0, 1.0);
		Sleep(150);
	}
}

void brinco3(unsigned int *key){
	*key = 0;
	int i;
	for(i = 14; i < 18; i++){
		ventana.PlotCBitmap(FramesTotoro[i].imagen, FramesTotoro[i].nr, FramesTotoro[i].nc, 0, 0, 1.0);
		Sleep(150);
	}
}
void secuenciaSalida(){
	return;
}

Image createImage(char *name){
	// memoria para la imagen de dimensiones nr por nc
	Image img;
	
	// leo dimensiones del bmp
	//DimensionesBmp(name, &img.nr, &img.nc);
	img.nr = 396;
	img.nc = 500;
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

