#include <stdio.h>
#include "lib_ppm.h"

static int verify_color(int color, int *vet);
int main(void)
{
	struct image_s data;
	struct image_s *image = &data;
  struct image_s data_new;
	struct image_s *image_new = &data_new;
	int i, j, r;
	
	int height = 0, width = 0;

	r = read_ppm("lena.ppm", image);
  

  new_ppm(image_new, image->width * 3, image->height * 3);

	if (r == 0) {
		for (j = 0; j < image->height; j++) {
			for (i = 0; i < image->width; i++) {
        int red = image->pix[j * image->width + i].r;
        int green = image->pix[j * image->width + i].g;
        int blue = image->pix[j * image->width + i].b;

        int vet_red[3];
        int vet_green[3];
        int vet_blue[3];
        verify_color(red, vet_red);
        verify_color(green, vet_green);
        verify_color(blue, vet_blue);
        
        image_new->pix[height * image_new->width + width].r = vet_red[0];
        image_new->pix[(height + 1) * image_new->width + width].r = vet_red[1];
        image_new->pix[(height + 2) * image_new->width + width].r = vet_red[2];

        image_new->pix[height * image_new->width + (width+1)].g = vet_green[0];
        image_new->pix[(height + 1) * image_new->width + (width + 1)].g = vet_green[1];
        image_new->pix[(height + 2) * image_new->width + (width + 1)].g = vet_green[2];

        image_new->pix[height * image_new->width + (width+2)].b = vet_blue[0];
        image_new->pix[(height + 1) * image_new->width + (width + 2)].b = vet_blue[0];
        image_new->pix[(height + 2) * image_new->width + (width + 2)].b = vet_blue[0];
        
        width = width + 3;
			}
      width = 0;
      height = height + 3;
		}
		
		
		write_ppm("lena_zoom.ppm", image_new);
	
	}
	
	return 0;
}


int verify_color(int color, int *vet) {
   
    if(color <= 74) {
      vet[0] = 0;
      vet[1] = 0;
      vet[2] = 0;
      return 0;
    }
    if(color <= 134) {
      vet[0] = 0;
      vet[1] = 255;
      vet[2] = 0;
      return 0;
    }
    if(color <= 179) {
      vet[0] = 255;
      vet[1] = 0;
      vet[2] = 255;
      return 0;
    }
    vet[0] = 255;
    vet[1] = 255;
    vet[2] = 255;
    return 0;
}