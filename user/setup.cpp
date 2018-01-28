#include "setup.hpp"

void RCC_Setup(){
	{//初始化时钟
		rcc::Init(9);//系统时钟设置(HSE 9倍频)
		//SystemInit();
		RCC->AHBENR |= 1;//DMA1
		RCC->APB2ENR|= 1;//AF
	}
	rcc::Cmd(2, APB2_GPIOA, ENABLE);
	rcc::Cmd(2, APB2_GPIOB, ENABLE);
}
void NVIC_Setup(){
	nvic::GroupConfig(2);//2抢占2响应
}
void GPIO_Setup(){
	{//模拟输入，低功耗
		RCC->APB2ENR |= 0x1fc;
		GPIOA->CRL=0;
		GPIOA->CRH=0;
		GPIOB->CRL=0;
		GPIOB->CRH=0;
		GPIOC->CRL=0;
		GPIOC->CRH=0;
		GPIOD->CRL=0;
		GPIOD->CRH=0;
		RCC->APB2ENR &= ~0x1fc;
	}
	gpio(PA,0).Config(P_AIN);
}
void Other_Setup(){
	map::JTAG(1);
}
void COM_Setup(){
	usart1.Config(1500000,0x00,0x0A);
	//i2c2.Config();
	//spi2.Config();
}
void setup(){
	flash::Read(FLASH_START_ADDR, &me, sizeof(me));//读取设备信息
	if(me.status[0]!=0x67){//设备初始化
		u8 ID_def[8]={0x11,0x01,0x00,0x00,0x00,0x00,0x00,0x01};//设备ID
		std::memcpy(me.ID, ID_def, 8);
		me.status[0]=0x67;
		flash::Write(FLASH_START_ADDR, &me, sizeof(me));
	}
	
	adc1.Init();
	rcc::Cmd(1, APB1_TIM3, ENABLE);
	tim3.BaseConfig(7200, 10000, 1);
	tim3.Cmd(DISABLE);
}
void loop(){
	pwr::Sleep(1);//休眠
}
