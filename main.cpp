#include <allegro.h>
#include <math.h>
#include <cstdlib>
#include <cstdio>
int mapa[11][8];
int lvl = 1;

void printmapa(BITMAP *bobbles[], BITMAP *buffer);
int colision(int, int, int);
void crash(int,int,int);

class Canion{
	private: 
		int angle;
		int resta;
		int nv;
		float px;
		float py;
		BITMAP *bobbles[9];	
	public:
		Canion(){
			this->angle=0;
			this->resta=M_PI_2;
			nv=1;
			srand(time(NULL));
			bobbles[1]=load_bitmap("sprites/bobble1.bmp",NULL);
			bobbles[2]=load_bitmap("sprites/bobble2.bmp",NULL);
			bobbles[3]=load_bitmap("sprites/bobble3.bmp",NULL);
			bobbles[4]=load_bitmap("sprites/bobble4.bmp",NULL);
			bobbles[5]=load_bitmap("sprites/bobble5.bmp",NULL);
			bobbles[6]=load_bitmap("sprites/bobble6.bmp",NULL);
		}
		int Flecha(){
			if (key[KEY_LEFT]){
	            angle-=resta;
            }else if(key[KEY_RIGHT]){
            	angle+=resta;
			}
			if(angle>50)	return 50;
			else if	(angle<-50)	return -50;
			else	return this->angle;
		}
		int Bobbles(){
			if(lvl==1 ||  lvl==3)	nv=1;
			else if(lvl==2)	nv=3;
			int r=nv+rand()%4;	
			return r;
		}
		void sw(int &al, int &a){
			int aux;
			aux=al;
			al=a;
			a=aux;
		}	
		void move(int &c, BITMAP *buffer,int angle, BITMAP *flecha, BITMAP *fondo, int a){
			float x,y,m,angulo=angle;
			angulo*=-1;
			angulo+=90;
			px=470;
			py=570;	
			if(angulo>=80 && angulo<=100){
				rest(100);
				x=0;
				y=1;
			}	
			else{
				angulo*=M_PI;
				angulo/=180;
				m=tan(angulo);
				if(m<0){
					y=m*(-1);
					x=-2;
				}else{
					y=m;x=2;
				}
			}
			while(py>=73){
				px+=x;
				py-=y;
				if(px<=300 || px>=640)	x*=-1;
				blit(fondo,buffer,0,0,0,0,1000,700);
				pivot_sprite(buffer, flecha, 500, 600, 45,110, itofix( (angle > 0) ? angle : 256 + angle ));
				masked_blit(bobbles[a],buffer,0,0,360,620,60,60);
				printmapa(bobbles,buffer);
				draw_sprite(buffer, bobbles[c], px, py);
				textprintf_centre_ex(buffer,font,490,690, 0xffffff,-1, "ROUND %d",lvl);
				masked_blit(buffer,screen,0,0,0,0,1000,700);
				py=colision(px,py,c);
				if(key[KEY_ESC])	break;
			}
		}
};
int main()
{	
	allegro_init();
	install_keyboard();
	install_timer();										//Instala los temporizadores del allegro.
	install_mouse();										//Instalación de periféricos(mouse).
	
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1000, 700, 0, 0);
	
	BITMAP *buffer = create_bitmap(1000, 700);				//Declaración e inicialización del Buffer.
	BITMAP *fondo = load_bitmap("sprites/Puzzle Bobbles Fondo.bmp",NULL);	//Bitmap con los fondos.
	BITMAP *menu1 = load_bitmap("sprites/Menu1.bmp",NULL);
	BITMAP *menu1_1 = load_bitmap("sprites/Menu1-1.bmp",NULL);
	BITMAP *menu2 = load_bitmap("sprites/Menu2.bmp",NULL);
	BITMAP *menu2_1 = load_bitmap("sprites/Menu2-1.bmp",NULL);
	BITMAP *flecha = load_bitmap("sprites/flecha.bmp",NULL);
    BITMAP *mouse = load_bitmap("cursores/mouse.bmp",NULL);	//Cursores empleados.
    BITMAP *mouse2 = load_bitmap("cursores/mousema.bmp",NULL);
    
    BITMAP *bobbles[9];	
    bobbles[1]=load_bitmap("sprites/bobble1.bmp",NULL);
	bobbles[2]=load_bitmap("sprites/bobble2.bmp",NULL);
	bobbles[3]=load_bitmap("sprites/bobble3.bmp",NULL);
	bobbles[4]=load_bitmap("sprites/bobble4.bmp",NULL);
	bobbles[5]=load_bitmap("sprites/bobble5.bmp",NULL);
	bobbles[6]=load_bitmap("sprites/bobble6.bmp",NULL);
    int op,b1=0;											//Variables para el menú.
    
	FILE *pf;
	if(lvl==1){
		pf = fopen ( "lvl1.txt", "r" );
	}else if(lvl==2){
		pf = fopen ( "lvl2.txt", "r" );
	}else if(lvl==3){
		pf = fopen ( "lvl3.txt", "r" );
	}
	for(int i=0; i<11; i++)
		for(int j=0; j<8; j++)	mapa[i][j]=0;
	char s;
	for(int i=0; i<11; i++){
		for (int j=0; j<8; j++){
			if(i%2!=0 && j==7){
				mapa[i][j]=10;	
			}else{
				s=getc(pf);	
				if(s>='1' && s<='6')	mapa[i][j]=s-48;
			}
		}
	}

	while(!key[KEY_ESC]){										//CICLO DEL MENÚ.
        
		if(mouse_x >=353 && mouse_x<=715 && mouse_y >550 && mouse_y<650){		//Cuestiona si el cursor está colocado sobre la primer opción del menú.
            if(mouse_b &1){														//condicional que determina si se ha dado click izquierdo.
            	remove_mouse();													//Desintala el mouse.
            	op=1;															//selecciona opción.			
            	break;															//Rompe el ciclo para que salga del menú.
			}
			if(b1==0){
        		blit(menu2,buffer,0,0,0,0,1000,700);
        		rest(180);
        		b1=1;
			}else{
				blit(menu2_1,buffer,0,0,0,0,1000,700);
				rest(180);
        		b1=0;
			}
            masked_blit(mouse2,buffer,0,0,mouse_x,mouse_y,13,18);				//cambia el cursor.
        }else{																	//si no se encuentra en ninguna de las posiciones antes mencionadas.
            if(b1==0){
        		blit(menu1,buffer,0,0,0,0,1000,700);
        		rest(180);
        		b1=1;
			}else{
				blit(menu1_1,buffer,0,0,0,0,1000,700);
        		rest(180);
        		b1=0;
			}
            masked_blit(mouse,buffer,0,0,mouse_x,mouse_y,13,18);				//cambia el cursor.
        }
	    blit(buffer,screen,0,0,0,0,1000,700);									//imprime el buffer a la pantalla.
	}
	
	int angle,al,a,aux;
	Canion *c = new Canion();
	al=c->Bobbles();
	a=c->Bobbles();
	if(al>4)	al-=4;
	if(op==1){
		while(!key[KEY_ESC]){
			textprintf_centre_ex(buffer,font,455,0, 0xffffff, 0xc000c0, "ROUND %d\n",1);
			blit(fondo,buffer,0,0,0,0,1000,700);
			printmapa(bobbles,buffer);
			angle=c->Flecha();
		    pivot_sprite(buffer, flecha, 500, 600, 45,110, itofix(angle /*(angle > 0) ? angle : 256 + angle*/ ));
			if(key[KEY_UP] || key[KEY_SPACE]){
				rest(150);
				aux=al;
				al=a;
				a=c->Bobbles();
				c->move(aux,buffer,angle,flecha,fondo,a);
			}else if(key[KEY_X] || key[KEY_DOWN]){
				rest(150);
				c->sw(al,a);
			}
			textprintf_centre_ex(buffer,font,455,0, 0xffffff, 0xc000c0, " %d\n",angle);
			textprintf_centre_ex(buffer,font,490,690, 0xffffff,-1, "ROUND %d",lvl);
			masked_blit(bobbles[al],buffer,0,0,470,570,60,60);
			masked_blit(bobbles[a],buffer,0,0,360,620,60,60);
			blit(buffer,screen,0,0,0,0,1000,700);
			
		}		
	}else{
		exit(1);
	}

	
	destroy_bitmap(buffer);
	
	return 0;
}
END_OF_MAIN();

void printmapa(BITMAP *bobbles[], BITMAP *buffer){  
	for(int i=0; i<10; i++){
		for(int j=0; j<8; j++){
			if(mapa[i][j]>=1 && mapa[i][j]<=6){
				if(i%2==0){
					draw_sprite(buffer, bobbles[mapa[i][j]], j*50+297, i*45+73);
				}else{
					draw_sprite(buffer, bobbles[mapa[i][j]], j*50+327, i*45+73);
				}
			}	
		}
	}
}
int colision(int px, int py, int c){
	int i,j;
	i=py/60;
	j=px/120;
	if(mapa[i-1][j]>=1 && mapa[i-1][j]<=6){
		if(mapa[i][j]==0)	mapa[i][j]=c;
		return 72;
	}else{
		return py;
	}
	crash(i,j,c);	
}
void crash(int i,int j,int c){
	if(mapa[i-1][j]==c){
		if(mapa[i-2][j]==c){
			mapa[i-1][j]=0;mapa[i-2][j]=0;mapa[i][j]=0;
		}else if(mapa[i-1][j-1]==c){
			mapa[i-1][j]=0;mapa[i-1][j-1]=0;mapa[i][j]=0;
		}else if(mapa[i-1][j+1]==c){
			mapa[i-1][j]=0;mapa[i-1][j+1]=0;mapa[i][j]=0;
		}	
	}else if(mapa[i][j-1]==c){
		if(mapa[i-1][j-1]==c){
			mapa[i-1][j-1]=0;mapa[i][j-1]=0;mapa[i][j]=0;
		}else if(mapa[i][j-2]==c){
			mapa[i][j-1]=0;mapa[i][j-2]=0;mapa[i][j]=0;
		}
	}else if(mapa[i][j+1]==c){
		if(mapa[i-1][j+1]==c){
			mapa[i-1][j+1]=0;mapa[i][j+1]=0;mapa[i][j]=0;
		}else if(mapa[i][j+2]==c){
			mapa[i][j+1]=0;mapa[i][j+2]=0;mapa[i][j]=0;
		}
	}
}

