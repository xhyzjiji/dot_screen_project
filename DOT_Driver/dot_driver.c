#include "stm32f10x.h"
#include "dot_driver.h"
#include "defined_type.h"
#include "stdio.h"

#define 	SET_As				GPIO_SetBits(DotCtrlPort, As)
#define 	RST_As				GPIO_ResetBits(DotCtrlPort, As)
#define 	SET_Bs 				GPIO_SetBits(DotCtrlPort, Bs)
#define 	RST_Bs				GPIO_ResetBits(DotCtrlPort, Bs)
#define 	SET_Cs 				GPIO_SetBits(DotCtrlPort, Cs)
#define 	RST_Cs				GPIO_ResetBits(DotCtrlPort, Cs)
#define 	SET_Ds 				GPIO_SetBits(DotCtrlPort, Ds)
#define 	RST_Ds				GPIO_ResetBits(DotCtrlPort, Ds)

#define 	RST_Green 			GPIO_SetBits(DotCtrlPort, Green)
#define 	SET_Green			GPIO_ResetBits(DotCtrlPort, Green)
#define 	RST_Red				GPIO_SetBits(DotCtrlPort, Red)
#define 	SET_Red				GPIO_ResetBits(DotCtrlPort, Red)

#define 	SET_SCLK			GPIO_SetBits(DotCtrlPort, SCLK)
#define 	RST_SCLK			GPIO_ResetBits(DotCtrlPort, SCLK)
#define 	SET_RCLK			GPIO_SetBits(DotCtrlPort, RCLK)
#define 	RST_RCLK			GPIO_ResetBits(DotCtrlPort, RCLK)
#define 	SET_OE				GPIO_SetBits(DotCtrlPort, OE)
#define 	RST_OE				GPIO_ResetBits(DotCtrlPort, OE)
#if	HCCLK_DELAY
	#define 	SCLK_DELAY			delayns(1)
	#define 	RCLK_DELAY			delayns(1)
#else
	#define 	SCLK_DELAY			
	#define 	RCLK_DELAY
#endif

void delayns(uint8_t time)
{
	for(; time>0; --time)
		__asm("nop");
}

void display_dot(bool status, dot_color color)
{
	if(status){
		RST_SCLK;
		switch(color){
			case ColorGreen:
				SET_Green;
				RST_Red;
				break;
			case ColorRed:
				SET_Red;
				RST_Green;
				break;
			case ColorOrange:
				SET_Green;
				SET_Red;
				break;
			default:
				RST_Green;
				RST_Red;
				break;
		}
		SET_SCLK;
	}
	else{
		RST_SCLK;
		RST_Green;
		RST_Red;
		SET_SCLK;
	}
}

extern const uint8_t brightness_level[];
void display_line(line_info *line)
{
	uint8_t i;
	for(i=0; i<screen_width; ++i){
		printf("dot status:%x, dot color:%x\n", line->dots[i].status, line->dots[i].color);
		display_dot((line->dots[i].status)?true:false, (dot_color)(line->dots[i].color));
	}
	RST_RCLK;
	SET_RCLK;
	RST_OE;
	delayns(brightness_level[line->brightness%brightness_level_length] + brightness_base_level);
	SET_OE;
}

void display_screen(screen_info *screen)
{
	uint8_t i;
	for(i=0; i<screen_height; ++i){
		display_line(screen->lines+i);
	}
}