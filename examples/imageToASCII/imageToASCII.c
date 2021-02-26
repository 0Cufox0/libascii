#include <ascii/grid.h>
#include <ascii/color.h>
#include <gd.h>
#include <stdio.h>
#include <stdlib.h>
#define BRIGHTNESS 1.5
gdImagePtr image;
void error(const char* msg);
Color generate(Position pos, Dimention dim, Frame frame){
	int pixel = gdImageGetTrueColorPixel(image, pos.x, pos.y);
	int r = gdTrueColorGetRed(pixel);
	int g = gdTrueColorGetGreen(pixel);
	int b = gdTrueColorGetBlue(pixel);

	return colorCreate(r * BRIGHTNESS, g * BRIGHTNESS, b * BRIGHTNESS);
}


void error(const char* msg){
	fprintf(stderr, "-=-=-=ERROR=-=-=-\n%s\n", msg);
}

int main(int argc, const char* argv[]){
	if(argc < 4){
		error("please use this syntax:\nimageToASCII [inputFile] [fileType {1 for png} {2 for jpeg}] [outputFile]");
		return 1;
	}

	const char* inPath = argv[1];
	const char* imageType = argv[2];
	//const char* outPath = argv[3];
	int type = atoi(imageType);
	FILE* img = fopen(inPath, "rb");
	switch(type){
		case 1:
			image = gdImageCreateFromPng(img);
			break;
		case 2:
			image = gdImageCreateFromJpeg(img);
			break;
	}
	fclose(img);
    if(gridOpen(image->sx, image->sy, ASCII_FONT_TINY, NULL,  NULL , generate) != ASCII_GRID_SUCCESS){
		fprintf(stderr, "COULD'T OPEN GRID");    
		return 1;
	}
	gridSetMaxFrame(1);
	gridDraw(NULL);

	gridClose();
	gdImageDestroy(image);
	return 0;
}
