#include "Shell.cpp"
#define V_REC -30
#define N_F 27
#define VEL 150
#define DIF 0
#define TAM_S 100
#define VAL_I 5
#define WX 220
#define WY 510
Window ventana("Totoro Dancing Life", 500, 550);

typedef struct{
	COLORREF** imagen;
	int nr, nc;
}Image;

Image FramesTotoro[N_F];
Image FramesIntro[2];
Image FramesFinal[2];
int secuencia[100];

Image createImage(char *name);
void freeImage(Image *img);
void secuenciaSalida();
int intro();
void brinco1();
void brinco2();
void brinco3();
void fallaste();
void cleanLinea(int y);
int perdiste(int score);
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
	
	for(i = 0; i < 2; i++){
		char name[100];
		sprintf(name, "Intro0%d.bmp", i);

		// memoria para la imagen i
		FramesIntro[i] = createImage(name);
		
		// leemos en bmp
		LeeBmpColor(FramesIntro[i].imagen, name);
	}
	for(i = 0; i < 2; i++){
		char name[100];
		sprintf(name, "Final0%d.bmp", i);

		// memoria para la imagen i
		FramesFinal[i] = createImage(name);
		
		// leemos en bmp
		LeeBmpColor(FramesFinal[i].imagen, name);
	}
	ventana.printf(180, WY+20, "PULSA X PARA SALIR");
	i = 0;
	unsigned int key = 9;
	int game = -1, score = 0;
	iniciaSecuencia();
	if(!intro())
		return 0;
	while(1){
		// Kbhit() regresa 1 si el usuario presiono una tecla en el teclado, regresa 0 si no presiono nada
		// guarda la tecla presionada en la variable key
		int resultado = (int) Kbhit(&key);
		if (key== 88){
			secuenciaSalida();
			return 0;
		}
		if (resultado == 1){
			game =1;
		}
		if(game){
			repiteSecuencia(score);
			game = 0;
		}
		else{
			int k = revisaSecuencia(score);
			if(k==-1)
				return 0;
			else if(k == 0){
				if(!perdiste(score)){
					return 0;
				}
				else{
					score = 0;
					iniciaSecuencia();
					game = 1;
				}
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
	for(i = 0; i < 0; i++)
		freeImage(&FramesIntro[i]);
	for(i = 0; i < 0; i++)
		freeImage(&FramesFinal[i]);	
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
	int i;
	cleanLinea(WY);
	i = 26;
	ventana.printf(150, WY, "Atencion! Memoriza la secuencia");
	ventana.PlotCBitmap(FramesTotoro[i].imagen, FramesTotoro[i].nr, FramesTotoro[i].nc, V_REC, 0, 1.0);
	ventana.PlotCBitmap(FramesTotoro[i].imagen, FramesTotoro[i].nr, FramesTotoro[i].nc, 500+V_REC, 0, 1.0);
	Sleep(1000);
	
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
		cleanLinea(WY);
		ventana.printf(WX, WY, "Paso 1");
		Sleep(VEL - DIF);
	}
}

void brinco2(){
	int i;
	for(i = 13; i < 18; i++){
		ventana.PlotCBitmap(FramesTotoro[i].imagen, FramesTotoro[i].nr, FramesTotoro[i].nc, V_REC, 0, 1.0);
		ventana.PlotCBitmap(FramesTotoro[i].imagen, FramesTotoro[i].nr, FramesTotoro[i].nc, 500+V_REC, 0, 1.0);
		cleanLinea(WY);
		ventana.printf(WX, WY, "Paso 2");
		Sleep(VEL - DIF);
	}
}

void brinco3(){
	int i;
	for(i = 14; i < 18; i++){
		ventana.PlotCBitmap(FramesTotoro[i].imagen, FramesTotoro[i].nr, FramesTotoro[i].nc, V_REC, 0, 1.0);
		ventana.PlotCBitmap(FramesTotoro[i].imagen, FramesTotoro[i].nr, FramesTotoro[i].nc, 500+V_REC, 0, 1.0);
		cleanLinea(WY);
		ventana.printf(WX, WY, "Paso 3");
		Sleep(VEL - DIF);
	}
}

void fallaste(){
	int i;
	for(i = 18; i < 27; i++){
		ventana.PlotCBitmap(FramesTotoro[i].imagen, FramesTotoro[i].nr, FramesTotoro[i].nc, V_REC, 0, 1.0);
		ventana.PlotCBitmap(FramesTotoro[i].imagen, FramesTotoro[i].nr, FramesTotoro[i].nc, 500+V_REC, 0, 1.0);
		cleanLinea(WY);
		ventana.printf(WX, WY, "Fallastee!");
		Sleep(VEL - DIF);
	}
}

void secuenciaSalida(){
	int i;
	for(i = 0; i < N_F; i++)
		freeImage(&FramesTotoro[i]);
	for(i = 0; i < 0; i++)
		freeImage(&FramesIntro[i]);
	for(i = 0; i < 0; i++)
		freeImage(&FramesFinal[i]);
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

int perdiste(int score){
	int hScore = 0;
	int record = 0;//para decirte si eres la persona con el nuevo highscore
	FILE *highscore = fopen("highscore.bin", "rb");
	if(highscore = NULL){
		record = 1;
		hScore = score;
		ventana.printf(120, 200, "No puedo leer el archivo de highscores");
		Sleep(20000);
		FILE *newhighscore = fopen("highscore.bin", "wb");
		fwrite(&score,sizeof(int),1, newhighscore);
		fclose(newhighscore);
	}
	else{
		fread(&hScore, sizeof(int), 1, highscore);
		fclose(highscore);
		if(hScore < score){
			record = 1;
			FILE *newhighscore = fopen("highscore.bin", "wb");
			fwrite(&score,sizeof(int),1, newhighscore);
			fclose(newhighscore);
		}
	}
	int resultado = 0;
	int i = 0;
	unsigned int key;
	while(!resultado){
		resultado = (int) Kbhit(&key);
		ventana.PlotCBitmap(FramesFinal[i].imagen, FramesFinal[i].nr, FramesFinal[i].nc, V_REC, 0, 1.0);
		ventana.PlotCBitmap(FramesFinal[i].imagen, FramesFinal[i].nr, FramesFinal[i].nc, 500+V_REC, 0, 1.0);
		ventana.printf(160, 220, "Tu puntuacion final es %d", score);
		if(record){
			ventana.printf(120, 240, "Conseguiste la puntuacion mas alta!");
		}
		else{
			ventana.printf(150, 240, "La puntuacion mas alta es %d", hScore);
		}
		i = (i+1)%2;
		if(key==88){
			secuenciaSalida();
			return 0;
		}
		ventana.printf(100, WY, "PULSA CUALQUIER TECLA PARA VOLVER A JUGAR");
		Sleep(300);
	}
	cleanLinea(WY);
	return 1;
}

int intro(){
	int resultado = 0;
	int i = 0;
	unsigned int key;
	while(!resultado){
		resultado = (int) Kbhit(&key);
		ventana.PlotCBitmap(FramesIntro[i].imagen, FramesIntro[i].nr, FramesIntro[i].nc, V_REC, 0, 1.0);
		ventana.PlotCBitmap(FramesIntro[i].imagen, FramesIntro[i].nr, FramesIntro[i].nc, 500+V_REC, 0, 1.0);
		i = (i+1)%2;
		if(key==88){
			secuenciaSalida();
			return 0;
		}
		ventana.printf(100, WY, "PULSA CUALQUIER TECLA PARA CONTINUAR");
		Sleep(300);
	}
	cleanLinea(WY);
	return 1;
}

void cleanLinea(int y){
	ventana.printf(0, y, "                                                                                                                                                       ");
}
