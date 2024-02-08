#include "image.h"
#include "LCD_Test.h"
#include "LCD_1in28.h"
#include "DEV_Config.h"


void LCD_1in28_test()
{
	DEV_Module_Init();
  
	LCD_1IN28_SetBackLight(1000);
	LCD_1IN28_Init(VERTICAL);
 	LCD_1IN28_Clear(BLACK);
	
	Paint_NewImage(LCD_1IN28_WIDTH,LCD_1IN28_HEIGHT, 0, BLACK);

	Paint_SetClearFuntion(LCD_1IN28_Clear);
	Paint_SetDisplayFuntion(LCD_1IN28_DrawPaint);

	Paint_Clear(BLACK);
  DEV_Delay_ms(100);


	Paint_DrawCircle(120,120, 120, BLUE ,DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
  Paint_DrawLine  (120, 0, 120, 12,GREEN ,DOT_PIXEL_4X4,LINE_STYLE_SOLID);
  Paint_DrawLine  (120, 228, 120, 240,GREEN ,DOT_PIXEL_4X4,LINE_STYLE_SOLID);
  Paint_DrawLine  (0, 120, 12, 120,GREEN ,DOT_PIXEL_4X4,LINE_STYLE_SOLID);
  Paint_DrawLine  (228, 120, 240, 120,GREEN ,DOT_PIXEL_4X4,LINE_STYLE_SOLID);

  Paint_DrawString_EN(123, 123, "WAVESHARE",&Font16,  BLACK, GREEN);

	Paint_DrawLine  (120, 120, 70, 70,YELLOW ,DOT_PIXEL_3X3,LINE_STYLE_SOLID);
	Paint_DrawLine  (120, 120, 176, 64,BLUE ,DOT_PIXEL_3X3,LINE_STYLE_SOLID);
	Paint_DrawLine  (120, 120, 120, 210,RED ,DOT_PIXEL_2X2,LINE_STYLE_SOLID);
	DEV_Delay_ms(1000);

	DEV_Module_Exit();
  
}

