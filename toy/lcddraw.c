/** \file lcddraw.c
 *  \brief Adapted from RobG's EduKit
 */
#include <lcdutils.h>
#include "lcddraw.h"


/** Draw single pixel at x,row 
 *
 *  \param col Column to draw to
 *  \param row Row to draw to
 *  \param colorBGR Color of pixel in BGR
 */
void drawPixel(char col, char row, int colorBGR) 
{
  lcd_setArea(col, row, col, row);
  lcd_writeColor(colorBGR);
}

/** Fill rectangle
 *
 *  \param colMin Column start
 *  \param rowMin Row start
 *  \param width Width of rectangle
 *  \param height height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void fillRectangle(char colMin, char rowMin, char width, char height, 
		   int colorBGR)
{
  char colLimit = colMin + width, rowLimit = rowMin + height;
  lcd_setArea(colMin, rowMin, colLimit - 1, rowLimit - 1);
  int total = width * height;
  int c = 0;
  while ((c++) < total) {
    lcd_writeColor(colorBGR);
  }
}

/** Clear screen (fill with color)
 *  
 *  \param colorBGR The color to fill screen
 */
void clearScreen(int colorBGR) 
{
  char w = screenWidth;
  char h = screenHeight;
  fillRectangle(0, 0, screenWidth, screenHeight, colorBGR);
}

/** 5x7 font - this function draws background pixels
 *  Adapted from RobG's EduKit
 *///char c is not U_
void drawChar5x7(char rcol, char rrow, char c, 
     int fgColorBGR, int bgColorBGR) 
{
  char col = 0;
  char row = 0;
  char bit = 0x01;
  char oc = c - 0x20;

  lcd_setArea(rcol, rrow, rcol + 4, rrow + 7); /* relative to requested col/row */ 
  while (row < 8) {
    while (col < 5) {
      int colorBGR = (font_5x7[oc][col] & bit) ? fgColorBGR : bgColorBGR;
      lcd_writeColor(colorBGR);
      col++;
    }
    col = 0;
    bit <<= 1;
    row++;
  }
}


// 8x12 font //CHAR C is NOT U
void drawChar8x12(char rcol, char rrow, char c, 
     int fgColorBGR, int bgColorBGR) 
{
  char col = 0;
  char row = 0;
  char bit = 0x01;
  char oc = c - 0x20;
  // +7 , +11
  lcd_setArea(rrow, rcol, rrow+7, rcol+11); /* relative to requested col/row */ 
  while (row < 13) {
    while (col < 8) {
     int colorBGR = (font_8x12[oc][col] & bit) ? fgColorBGR : bgColorBGR;
      lcd_writeColor(colorBGR);
      col++;
    }
    col= 0;
    bit <<= 1;
    row++;
  }
} 

/** Draw string at col,row
 *  Type:
 *  FONT_SM - small (5x8,) FONT_MD - medium (8x12,) FONT_LG - large (11x16)
 *  FONT_SM_BKG, FONT_MD_BKG, FONT_LG_BKG - as above, but with background color
 *  Adapted from RobG's EduKit
 *
 *  \param col Column to start drawing string
 *  \param row Row to start drawing string
 *  \param string The string
 *  \param fgColorBGR Foreground color in BGR
 *  \param bgColorBGR Background color in BGR
 */ // char *s IS NOT U
void drawString5x7(char col, char row, char *string,
		int fgColorBGR, int bgColorBGR)
{
  char cols = col;
  while (*string) {
    drawChar5x7(cols, row, *string++, fgColorBGR, bgColorBGR);
    cols += 6;
  }
}

// char *string IS NOT U
void drawString8x12(char col, char row, char *string,
		int fgColorBGR, int bgColorBGR)
{
  char cols = col;
  while (*string) {
    drawChar8x12(row, cols, *string++, fgColorBGR, bgColorBGR);
    cols += 11;
  }
} 


/** Draw rectangle outline
 *  
 *  \param colMin Column start
 *  \param rowMin Row start 
 *  \param width Width of rectangle
 *  \param height Height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void drawRectOutline(char colMin, char rowMin, char width, char height,
		     int colorBGR)
{
  /**< top & bot */
  fillRectangle(colMin, rowMin, width, 1, colorBGR);
  fillRectangle(colMin, rowMin + height, width, 1, colorBGR);

  /**< left & right */
  fillRectangle(colMin, rowMin, 1, height, colorBGR);
  fillRectangle(colMin + width, rowMin, 1, height, colorBGR);
}

void rightTriangle(char orientation,char heightOffset, char widthOffset,char width, int colorBGR){
  for(int i = 0; i < width; i++){
   for(int j = i; j < width;j++){
      if(orientation == 1)
      drawPixel(j+heightOffset,i+widthOffset,colorBGR);
      else
	drawPixel(i+heightOffset, j+widthOffset,colorBGR);
   }
  }
}

void vertTrapezoid(char heightOffset, char widthOffset, char width, char height, int colorBGR){

    for(int i=0; i< height; i++)
      for(int j = i; j < width; j++)
	drawPixel(widthOffset-j, i+heightOffset, colorBGR);

}
void equiTriangle(char orientation,char heightOffset, char widthOffset,char width, int colorBGR){

  for(int i = 0; i < width; i++){
    for(int j = i; j < width;j++){
      //drawPixel((j+10)-i,(j+20)-i,colorBGR);
      switch(orientation){
      case 0: drawPixel(screenWidth-(i+widthOffset)-j,(i+heightOffset)-j,colorBGR); break;
      case 1:drawPixel(screenWidth-(j+widthOffset)-i,(j+heightOffset)-i,colorBGR); break;
      case 2: drawPixel((i+widthOffset)-j,screenHeight-(i+heightOffset)-j,colorBGR); break;
      case 3:drawPixel((j+widthOffset)-i,screenHeight-(i+heightOffset)-j,colorBGR);  break;
      
      }
    }
  }
}
void vines(char height, char width, char spacing, int colorBGR){

    for(int k = 0; k < 10; k++){
      int repeat = k*spacing;  //controls spacing
   for(int i = k; i < 20; i++){
       for(int j = i; j < 15; j++){
	 //repeat+ height is heightOffset
       
	 int jHeight = j+repeat+height, iHeight = i+repeat+height,
	   jWidth = j+repeat+width-10, iWidth = i+repeat +width;

	 drawPixel(jHeight,iWidth,colorBGR);
	 drawPixel(iHeight,jWidth,colorBGR);	 
	 drawPixel(screenWidth-jHeight,iWidth,colorBGR);
	 drawPixel(screenWidth-iHeight,jWidth,colorBGR);
       }
       }
     }

}

void roses(char size, int colorBGR){
  
    equiTriangle(0, screenHeight/2+20,40,size,colorBGR);
      equiTriangle(1, screenHeight/2,40,size,colorBGR);
      equiTriangle(2, 45,screenWidth/2+10,size,colorBGR);
      equiTriangle(3, 45,screenWidth/2-10,size,colorBGR);  
}
