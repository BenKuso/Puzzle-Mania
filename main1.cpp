#include <allegro.h>
#include <math.h>
#include <cstdlib>

int main() 
{	
	allegro_init();
	install_keyboard();
	install_timer();										//Instala los temporizadores del allegro.
	install_mouse();										//Instalación de periféricos(mouse).
	
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1000, 700, 0, 0);
	
	BITMAP *buffer = create_bitmap(1000, 700);				//Declaración e inicialización del Buffer.
	BITMAP *fondo = load_bitmap("mapas/Puzzle Bobbles Fondo.bmp",NULL);	//Bitmap con los fondos.
	BITMAP *menu1 = load_bitmap("mapas/Menu1.bmp",NULL);
	BITMAP *menu1_1 = load_bitmap("mapas/Menu1-1.bmp",NULL);
	BITMAP *menu2 = load_bitmap("mapas/Menu2.bmp",NULL);
	BITMAP *menu2_1 = load_bitmap("mapas/Menu2-1.bmp",NULL);
	BITMAP *flecha = load_bitmap("mapas/flecha.bmp",NULL);
    BITMAP *mouse = load_bitmap("cursores/mouse.bmp",NULL);	//Cursores empleados.
    BITMAP *mouse2 = load_bitmap("cursores/mousema.bmp",NULL);
    
    int op,b1=0,c=0;											//Variables para el menú.
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
	
	int angle = 0;
	int resta = M_PI_2;
	
	if(op==1){
		while(!key[KEY_ESC]){
			textprintf_centre_ex(buffer,font,455,490, 0xffffff, 0xc000c0, "ROUND %d\n",1);
			blit(fondo,buffer,0,0,0,0,1000,700);

		    if (key[KEY_LEFT]){
	            angle-=resta;
            }else if(key[KEY_RIGHT]){
            	angle+=resta;
			}
			pivot_sprite(buffer, flecha, 500, 600, 45,110, itofix( (angle > 0) ? angle : 256 + angle ));
			blit(buffer,screen,0,0,0,0,1000,700);
		}		
	}else{
		exit(1);
	}

	
	destroy_bitmap(buffer);
	
	return 0;
}
END_OF_MAIN();
