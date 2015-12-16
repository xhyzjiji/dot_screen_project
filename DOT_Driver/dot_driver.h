#ifndef __DOT_DRIVER_H__
#define __DOT_DRIVER_H__

#include "stm32f10x.h"
#include "defined_type.h"
//#include "stdio.h"
//#include "stdlib.h"
//#include "string.h"

#define DotCtrlPort GPIOD
#define As 			GPIO_Pin_0
#define Bs 			GPIO_Pin_1
#define Cs			GPIO_Pin_2
#define Ds			GPIO_Pin_3
#define Green		GPIO_Pin_4		//�ڶ�Ƭ595���������
#define Red			GPIO_Pin_5		//��һƬ595���������
#define RCLK		GPIO_Pin_6		//595����ʱ��(������)
#define SCLK		GPIO_Pin_7		//595������λʱ��(������)
#define OE			GPIO_Pin_8	  //595���ʹ��(�͵�ƽ)  595 nCLR�������ã��ӵ�VCC
#define ABCDs		(As | Bs | Cs | Ds)

//����ÿ�������ǹ̶��ģ�ÿ������ɫ���Բ�ͬ��ÿ���������Ƕ�����
#define screen_height	16
#define screen_width	16
#define screen_line		screen_height
#define dots_bytes 		(screen_height*screen_width/8)
typedef enum {
	ColorGreen = 0x01,
	ColorRed = 0x02,
	ColorOrange = 0x04,
	ColorBlack = 0x00
}dot_color;
typedef struct {
	uint8_t status:4; 		//��λ
	uint8_t color:4;  		//��λ
}dot_info;
typedef struct {
	dot_info dots[screen_width];
	uint8_t brightness;
}line_info;
typedef struct {
	line_info lines[screen_height];			//���ػ���
}screen_info;

#define brightness_base_level			0
const uint8_t brightness_level[] = {
	0, 2, 4, 6, 8, 10, 12, 14, 16, 18,
	20, 22, 24, 26, 28, 30, 32, 34, 36, 38,
	40, 42, 44, 46, 48, 50, 52, 54, 56, 58,
	60, 62, 64, 66, 68, 70, 72, 74, 76, 78, 
	80, 82, 84, 86, 88, 90, 92, 94, 96, 98,
	100,
};  //OE ��Чʱ�������Ļ����
#define brightness_level_length	(sizeof(brightness_level)/sizeof(uint8_t))
	
#define screen_fresh_frequency			24  //��Ļˢ��Ƶ��Ϊ50��/��
#define keytrigger_reset_fresh_timer	false

void delayns(uint8_t time);
void display_dot(bool status, dot_color color);
void display_line(line_info *line);
void display_screen(screen_info *screen);

#endif