#include "Shell.cpp"
#define V_REC -30
#define N_F 27
#define VEL 150
#define DIF 0
#define TAM_S 100
#define VAL_I 5
#define WX 200
#define WY 510
Window ventana("Totoro Dancing Life", 500, 550);

typedef struct{
	COLORREF** imagen;
	int nr, nc;
}Image;

Image FramesTotoro[N_F];
int secuencia[100];

Image createImage(char *name);
void freeImage(Image *img);
void secuenciaSalida();
void brinco1();
void brinco2();
void brinco3();
void fallaste();
void perdiste(int score);
void repiteSecuencia(int score);
int revisaSecuencia(int score);
void iniciaSecuencia();

int main(){	
	srand(time(NULL));
	int i;
	
	for(i = 0; i < N_F; i++){
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
	int game = -1, score = 0;
	iniciaSecuencia();
	while(1){
		// Kbhit() regresa 1 si el usuario presiono una tecla en el teclado, regresa 0 si no presiono nada
		// guarda la tecla presionada en la variable key
		int resultado = (int) Kbhit(&key);
		if (key== 88){
			secuenciaSalida();
			for(i = 0; i < N_F; i++)
				freeImage(&FramesTotoro[i]);
			return 0;
		}
		if (resultado == 1){
			game =1;
		}
		if(game){
			i = 26;
			ventana.PlotCBitmap(FramesTotoro[i].imagen, FramesTotoro[i].nr, FramesTotoro[i].nc, V_REC, 0, 1.0);
			ventana.PlotCBitmap(FramesTotoro[i].imagen, FramesTotoro[i].nr, FramesTotoro[i].nc, 500+V_REC, 0, 1.0);
			Sleep(200);
			repiteSecuencia(score);
			game = 0;
		}
		else{
			int k = revisaSecuencia(score);
			if(k==-1)
				return 0;
			else if(k == 0){
				perdiste(score);
			}
			else{
				secuencia[score+VAL_I] = rand()%3;
				score++;
				game = 1;
			}
		}
		
		Sleep(200);
	}
	
	for(i = 0; i < N_F; i++)
		freeImage(&FramesTotoro[i]);
	
	return MainLoop();
}

int revisaSecuencia(int score){
	unsigned int key;
	int i = 0;
	int control;
	for(i = 0; i < score+VAL_I;){
		int resultado = (int) Kbhit(&key);
		if(resultado){
		if (key== 88){
			secuenciaSalida();
			for(i = 0; i < N_F; i++)
				freeImage(&FramesTotoro[i]);
			return -1;
		}
		if(key == 49 || key==70){
			control = 0;
			key = 0;
		}
		else if(key == 50 || key==71){
			control = 1;
			key = 0;
		}
		else if(key == 51 || key==72){
			control = 2;
			key = 0;
		}
		else{
			key = -1;
		}
		if(control != secuencia[i])
			control = -1;
		switch(control){
			case 0:
				brinco1();
				break;
			case 1:
				brinco2();
				break;
			case 2:
				brinco3();
				break;
			default:
				fallaste();
				return 0;
		}
		i++;
		}
	}
	return 1;
}

void repiteSecuencia(int score){
	ventana.printf(15, 200, "Hola mundo");
	int i;
	for(i = 0; i < score+VAL_I; i++){
		switch(secuencia[i]){
			case 0:
				brinco1();
				break;
			case 1:
				brinco2();
				break;
			case 2:
				brinco3();
				break;
		}
	}
}

void iniciaSecuencia(){
	int i, n;
	for(i = 0; i < TAM_S; i++){
		if(i < VAL_I)
			n = rand()%3;
		else
			n = -1;
		secuencia[i] = n;
	}
}

void brinco1(){
	int i;
	for(i = 4; i < 18; i++){
		ventana.PlotCBitmap(FramesTotoro[i].imagen, FramesTotoro[i].nr, FramesTotoro[i].nc, V_REC, 0, 1.0);
		ventana.PlotCBitmap(FramesTotoro[i].imagen, FramesTotoro[i].nr, FramesTotoro[i].nc, 500+V_REC, 0, 1.0);
		ventana.printf(WX, WY, "Paso 1");
		Sleep(VEL - DIF);
	}
}

void brinco2(){
	int i;
	for(i = 13; i < 18; i++){
		ventana.PlotCBitmap(FramesTotoro[i].imagen, FramesTotoro[i].nr, FramesTotoro[i].nc, V_REC, 0, 1.0);
		ventana.PlotCBitmap(FramesTotoro[i].imagen, FramesTotoro[i].nr, FramesTotoro[i].nc, 500+V_REC, 0, 1.0);
		ventana.printf(WX, WY, "Paso 2");
		Sleep(VEL - DIF);
	}
}

void brinco3(){
	int i;
	for(i = 14; i < 18; i++){
		ventana.PlotCBitmap(FramesTotoro[i].imagen, FramesTotoro[i].nr, FramesTotoro[i].nc, V_REC, 0, 1.0);
		ventana.PlotCBitmap(FramesTotoro[i].imagen, FramesTotoro[i].nr, FramesTotoro[i].nc, 500+V_REC, 0, 1.0);
		ventana.printf(WX, WY, "Paso 3");
		Sleep(VEL - DIF);
	}
}

void fallaste(){
	int i;
	for(i = 18; i < 27; i++){
		ventana.PlotCBitmap(FramesTotoro[i].imagen, FramesTotoro[i].nr, FramesTotoro[i].nc, V_REC, 0, 1.0);
		ventana.PlotCBitmap(FramesTotoro[i].imagen, FramesTotoro[i].nr, FramesTotoro[i].nc, 500+V_REC, 0, 1.0);
		ventana.printf(WX, WY, "Fallastee!");
		Sleep(VEL - DIF);
	}
}

void secuenciaSalida(){
	return;
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

void perdiste(int score){
	int i;
	for(i = 18; i < 27; i++){
		ventana.PlotCBitmap(FramesTotoro[i].imagen, FramesTotoro[i].nr, FramesTotoro[i].nc, V_REC, 0, 1.0);
		ventana.PlotCBitmap(FramesTotoro[i].imagen, FramesTotoro[i].nr, FramesTotoro[i].nc, 500+V_REC, 0, 1.0);
		ventana.printf(WX, WY, "Perdiste! Tu puntuacion final es %d", score);
		Sleep(VEL - DIF);
	}
}
