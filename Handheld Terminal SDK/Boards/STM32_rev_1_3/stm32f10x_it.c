
#define __STM_IT_C
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"


#define  USART_IT_ALL (USART_IT_CTS || USART_IT_TC)

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static unsigned int  mSec_Cnt = 0;
static unsigned char Sec_Cnt  = 0;
static unsigned char Min_Cnt  = 0;
static unsigned char Hour_Cnt = 0;

u8 tmp_rec_flag	= 0;
u8 tmp_ack_flag = 0;

vu8 RTC_TimeUpdate;

//u8 Menu_Flag;
/* Private function prototypes -----------------------------------------------*/
static void GSM_Isr(void);

/* Private functions ---------------------------------------------------------*/
void Init_ISR()
{
}
/*******************************************************************************
* Function Name  : DataUpdate
* Description    : This function updates date.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DateUpdate(void)
{
	u8  t_dd, t_mm;
	u16 t_yy;

	t_mm = BKP_ReadBackupRegister(BKP_DR2);
	t_dd = BKP_ReadBackupRegister(BKP_DR3);
	t_yy = BKP_ReadBackupRegister(BKP_DR4);

	if(t_mm == 1 || t_mm == 3 || t_mm == 5 || t_mm == 7 ||
		t_mm == 8 || t_mm == 10 || t_mm == 12)
	{
		if(t_dd < 31)
		{
			t_dd++;
		}
		else
		{
			if(t_mm != 12)
			{
				t_mm++;
				t_dd = 1;
			}
			else
			{
				t_mm = t_dd = 1;
				t_yy++;
			}
		}
	}
	else if(t_mm == 4 || t_mm == 6 || t_mm == 9 || t_mm == 11)
	{
		if(t_dd < 30)
		{
			t_dd++;
		}
		else
		{
			t_mm++;
			t_dd = 1;
		}
	}
	else if(t_mm == 2)
	{
		if(t_dd < 28)
		{
			t_dd++;
		}
		else
		{
			if((t_yy % 400) == 0 || (t_yy % 100) == 0 || (t_yy % 4) == 0)
			{
				t_dd++;
			}
			else
			{
				t_mm++;
				t_dd = 1;
			}
		}
	}
	/* Allow access to BKP Domain */
	PWR_BackupAccessCmd(ENABLE);
	BKP_WriteBackupRegister(BKP_DR2,t_mm);

	PWR_BackupAccessCmd(ENABLE);
	BKP_WriteBackupRegister(BKP_DR3,t_dd);

	PWR_BackupAccessCmd(ENABLE);
	BKP_WriteBackupRegister(BKP_DR4,t_yy);
}

/*******************************************************************************
* Function Name  : GSM_Isr
* Description    : This function handles GSM Reception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GSM_Isr(void)
{
	static u8 GSM_Rx_Char, GSM_Prev_Char;

	GSM_Rx_Char = USART_ReceiveData(GSM_PORT);	/* Storing The Received Data in Buffer.. */

	if((GSM_Prev_Char == '\n' && GSM_Rx_Char == '\r'))
		GSM_Rx_Cnt = 0;
	if((GSM_Prev_Char == '\r' && GSM_Rx_Char == 'S') && GSM_Check_SendOk == 1)
		GSM_Rx_Cnt = 0;

	if(GSM_Rx_Cnt < (GSM_RX_SIZE-2))
	{
		GSM_Rx_Buffer[GSM_Rx_Cnt++] = GSM_Rx_Char;   /* storing GSM response data */
	}
	else
	{
		GSM_Rx_Buffer[GSM_Rx_Cnt] = GSM_Rx_Char;
		GSM_Rx_Cnt = 0;
	}
	GSM_Prev_Char = GSM_Rx_Char;
}

/*******************************************************************************
* Function Name  : print_seq
* Description    : This function gives printer drives.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void print_seq(void)
{
	if(PrintOv_Flag == 0 && PrintStart_Flag == 1)
	{
		switch(Print_Sol_State)
		{
		case  0:
			SET_PORT_PIN(PRN_STB1_PORT, PRN_STB1);
			Print_Sol_State++;
			break;
		case  1:
			SET_PORT_PIN(PRN_STB2_PORT, PRN_STB2);
			Print_Sol_State++;
			break;
		case  2:
			CLR_PORT_PIN(PRN_STB1_PORT, PRN_STB1);
			SET_PORT_PIN(PRN_STB3_PORT, PRN_STB3);
			Print_Sol_State++;
			break;
		case  3:
			CLR_PORT_PIN(PRN_STB2_PORT, PRN_STB2);
			SET_PORT_PIN(PRN_STB4_PORT, PRN_STB4);
			Print_Sol_State++;
			break;
		case  4:
			CLR_PORT_PIN(PRN_STB3_PORT, PRN_STB3);
			SET_PORT_PIN(PRN_STB5_PORT, PRN_STB5);
			Print_Sol_State++;
			break;
		case  5:
			CLR_PORT_PIN(PRN_STB4_PORT, PRN_STB4);
			SET_PORT_PIN(PRN_STB6_PORT, PRN_STB6);
			Print_Sol_State++;
			break;
		case  6:
			CLR_PORT_PIN(PRN_STB5_PORT, PRN_STB5);
			Print_Sol_State++;
			break;
		case  7:
			CLR_PORT_PIN(PRN_STB6_PORT, PRN_STB6);
			SET_PORT_PIN(PRN_STB1_PORT, PRN_STB1);
			Print_Sol_State++;
			break;
		case  8:
			SET_PORT_PIN(PRN_STB2_PORT, PRN_STB2);
			Print_Sol_State++;
			break;
		case  9:
			CLR_PORT_PIN(PRN_STB1_PORT, PRN_STB1);
			SET_PORT_PIN(PRN_STB3_PORT, PRN_STB3);
			Print_Sol_State++;
			break;
		case 10:
			CLR_PORT_PIN(PRN_STB2_PORT, PRN_STB2);
			SET_PORT_PIN(PRN_STB4_PORT, PRN_STB4);
			Print_Sol_State++;
			break;
		case 11:
			CLR_PORT_PIN(PRN_STB3_PORT, PRN_STB3);
			SET_PORT_PIN(PRN_STB5_PORT, PRN_STB5);
			Print_Sol_State++;
			break;
		case 12:
			CLR_PORT_PIN(PRN_STB4_PORT, PRN_STB4);
			SET_PORT_PIN(PRN_STB6_PORT, PRN_STB6);
			Print_Sol_State++;
			break;
		case 13:
			CLR_PORT_PIN(PRN_STB5_PORT, PRN_STB5);
			Print_Sol_State++;
			break;
		case 14:
			CLR_PORT_PIN(PRN_STB6_PORT, PRN_STB6);
			Print_Sol_State++;
			break;
		case 15:
			PrintOv_Flag = 1;
			break;
		default:
			break;

		}
		switch(MotorSteps_state)
		{
		case 0: /* PRN_MOT1=1, PRN_MOT2=0, PRN_MOT3=0, PRN_MOT4=1 */
			SET_PORT_PIN(PRN_MOT1_PORT, PRN_MOT1);
			CLR_PORT_PIN(PRN_MOT2_PORT, PRN_MOT2);
			CLR_PORT_PIN(PRN_MOT3_PORT, PRN_MOT3);
			SET_PORT_PIN(PRN_MOT4_PORT, PRN_MOT4);
			MotorSteps_state++;
			break;
		case 4: /* PRN_MOT1=0, PRN_MOT2=0, PRN_MOT3=0, PRN_MOT4=1 */
			CLR_PORT_PIN(PRN_MOT1_PORT, PRN_MOT1);
			CLR_PORT_PIN(PRN_MOT2_PORT, PRN_MOT2);
			CLR_PORT_PIN(PRN_MOT3_PORT, PRN_MOT3);
			SET_PORT_PIN(PRN_MOT4_PORT, PRN_MOT4);
			MotorSteps_state++;
			break;
		case 8: /* PRN_MOT1=0, PRN_MOT2=1, PRN_MOT3=0, PRN_MOT4=1 */
			CLR_PORT_PIN(PRN_MOT1_PORT, PRN_MOT1);
			SET_PORT_PIN(PRN_MOT2_PORT, PRN_MOT2);
			CLR_PORT_PIN(PRN_MOT3_PORT, PRN_MOT3);
			SET_PORT_PIN(PRN_MOT4_PORT, PRN_MOT4);
			MotorSteps_state++;
			break;
		case 12:/* PRN_MOT1=0, PRN_MOT2=1, PRN_MOT3=0, PRN_MOT4=0 */
			CLR_PORT_PIN(PRN_MOT1_PORT, PRN_MOT1);
			SET_PORT_PIN(PRN_MOT2_PORT, PRN_MOT2);
			CLR_PORT_PIN(PRN_MOT3_PORT, PRN_MOT3);
			CLR_PORT_PIN(PRN_MOT4_PORT, PRN_MOT4);
			MotorSteps_state++;
			break;
		case 16:/* PRN_MOT1=0, PRN_MOT2=1, PRN_MOT3=1, PRN_MOT4=0 */
			CLR_PORT_PIN(PRN_MOT1_PORT, PRN_MOT1);
			SET_PORT_PIN(PRN_MOT2_PORT, PRN_MOT2);
			SET_PORT_PIN(PRN_MOT3_PORT, PRN_MOT3);
			CLR_PORT_PIN(PRN_MOT4_PORT, PRN_MOT4);
			MotorSteps_state++;
			break;
		case 20:/* PRN_MOT1=0, PRN_MOT2=0, PRN_MOT3=1, PRN_MOT4=0 */
			CLR_PORT_PIN(PRN_MOT1_PORT, PRN_MOT1);
			CLR_PORT_PIN(PRN_MOT2_PORT, PRN_MOT2);
			SET_PORT_PIN(PRN_MOT3_PORT, PRN_MOT3);
			CLR_PORT_PIN(PRN_MOT4_PORT, PRN_MOT4);
			MotorSteps_state++;
			break;
		case 24:/* PRN_MOT1=0, PRN_MOT2=0, PRN_MOT3=1, PRN_MOT4=0 */
			CLR_PORT_PIN(PRN_MOT1_PORT, PRN_MOT1);
			CLR_PORT_PIN(PRN_MOT2_PORT, PRN_MOT2);
			SET_PORT_PIN(PRN_MOT3_PORT, PRN_MOT3);
			CLR_PORT_PIN(PRN_MOT4_PORT, PRN_MOT4);
			MotorSteps_state++;
			break;
		case 28:/* PRN_MOT1=1, PRN_MOT2=0, PRN_MOT3=0, PRN_MOT4=0 */
			SET_PORT_PIN(PRN_MOT1_PORT, PRN_MOT1);
			CLR_PORT_PIN(PRN_MOT2_PORT, PRN_MOT2);
			CLR_PORT_PIN(PRN_MOT3_PORT, PRN_MOT3);
			CLR_PORT_PIN(PRN_MOT4_PORT, PRN_MOT4);
			MotorSteps_state++;
			break;
		case 31:
			if(PrintAbort == 1)
			{
				PrintAbort = 0;
				StopPrint = 1;
			}
			MotorSteps_state = 0;
			break;
		default:
			MotorSteps_state++;
			break;
		}
	}
}

void timer_interrupt()
{
//	if(!tout_err)
//	{
//
//		tout += 1;
//		if(tout>499)
//			tout_err = 1;
//	}
//	if(!half_sec)
//	{
//		half_sec_cnt += 1;
//		if(half_sec_cnt>99)
//		{
//			half_sec_cnt = 0;
//			half_sec = 1;
//		}
//	}
}


void set_PC_flags()
{
//	if(tmp_rec_flag)
//	{
//		rec_flag = 1;
//		tmp_rec_flag = 0;
//	}
//
//	if(tmp_ack_flag)
//	{
//		ack_flag = 1;
//		tmp_ack_flag = 0;
//	}
}
/*******************************************************************************
* Function Name  : NMIException
* Description    : This function handles NMI exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NMIException(void)
{
}

/*******************************************************************************
* Function Name  : HardFaultException
* Description    : This function handles Hard Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void HardFaultException(void)
{

	while (1)
	{
	}
}

/*******************************************************************************
* Function Name  : MemManageException
* Description    : This function handles Memory Manage exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MemManageException(void)
{

	while (1)
	{
	}
}

/*******************************************************************************
* Function Name  : BusFaultException
* Description    : This function handles Bus Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BusFaultException(void)
{

	while (1)
	{
	}
}

/*******************************************************************************
* Function Name  : UsageFaultException
* Description    : This function handles Usage Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UsageFaultException(void)
{

	while (1)
	{
	}
}

/*******************************************************************************
* Function Name  : DebugMonitor
* Description    : This function handles Debug Monitor exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DebugMonitor(void)
{
}

/*******************************************************************************
* Function Name  : SVCHandler
* Description    : This function handles SVCall exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SVCHandler(void)
{
}

/*******************************************************************************
* Function Name  : PendSVC
* Description    : This function handles PendSVC exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PendSVC(void)
{
}

/*******************************************************************************
* Function Name  : SysTickHandler
* Description    : This function handles SysTick Handler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SysTickHandler(void)
{
}

/*******************************************************************************
* Function Name  : WWDG_IRQHandler
* Description    : This function handles WWDG interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void WWDG_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : PVD_IRQHandler
* Description    : This function handles PVD interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PVD_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TAMPER_IRQHandler
* Description    : This function handles Tamper interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TAMPER_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : RTC_IRQHandler
* Description    : This function handles RTC global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RTC_IRQHandler(void)
{
	RTC_ClearITPendingBit(RTC_IT_SEC);


	/* Wait until last write operation on RTC registers is terminated */
	RTC_WaitForLastTask();

	if(RTC_GetCounter() >= 86400) /* Seconds Per Day = 86400*/
	{
		/* Wait until last write operation on RTC registers has finished */
		RTC_WaitForLastTask();
		/* Sets Counter value to 0x00 */
		RTC_SetCounter(0x00);
		/* Wait until last write operation on RTC registers has finished */
		RTC_WaitForLastTask();

		/* Increment the date */
		DateUpdate();
	}
}

/*******************************************************************************
* Function Name  : FLASH_IRQHandler
* Description    : This function handles Flash interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void FLASH_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : RCC_IRQHandler
* Description    : This function handles RCC interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI0_IRQHandler
* Description    : This function handles External interrupt Line 0 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI0_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI1_IRQHandler
* Description    : This function handles External interrupt Line 1 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI2_IRQHandler
* Description    : This function handles External interrupt Line 2 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI3_IRQHandler
* Description    : This function handles External interrupt Line 3 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI4_IRQHandler
* Description    : This function handles External interrupt Line 4 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI4_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA1_Channel1_IRQHandler
* Description    : This function handles DMA1 Channel 1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA1_Channel2_IRQHandler
* Description    : This function handles DMA1 Channel 2 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA1_Channel3_IRQHandler
* Description    : This function handles DMA1 Channel 3 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA1_Channel4_IRQHandler
* Description    : This function handles DMA1 Channel 4 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel4_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA1_Channel5_IRQHandler
* Description    : This function handles DMA1 Channel 5 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA1_Channel5_IRQHandler(void)
{
}



/*******************************************************************************
* Function Name  : ADC1_2_IRQHandler
* Description    : This function handles ADC1 and ADC2 global interrupts requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ADC1_2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : USB_HP_CAN_TX_IRQHandler
* Description    : This function handles USB High Priority or CAN TX interrupts
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_HP_CAN_TX_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : USB_LP_CAN_RX0_IRQHandler
* Description    : This function handles USB Low Priority or CAN RX0 interrupts
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_LP_CAN_RX0_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : CAN_RX1_IRQHandler
* Description    : This function handles CAN RX1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN_RX1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : CAN_SCE_IRQHandler
* Description    : This function handles CAN SCE interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN_SCE_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI9_5_IRQHandler
* Description    : This function handles External lines 9 to 5 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI9_5_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM1_BRK_IRQHandler
* Description    : This function handles TIM1 Break interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_BRK_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM1_UP_IRQHandler
* Description    : This function handles TIM1 overflow and update interrupt
*                  request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_UP_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM1_TRG_COM_IRQHandler
* Description    : This function handles TIM1 Trigger and commutation interrupts
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_TRG_COM_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM1_CC_IRQHandler
* Description    : This function handles TIM1 capture compare interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_CC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM2_IRQHandler
* Description    : This function handles TIM2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM2_IRQHandler(void)
{
  if((TIM2->SR & 0x0001) != 0)
   {
    if(++mSec_Cnt == 1000)       /* Check for 1 Second (1ms * 1000) */
     {
	    mSec_Cnt = 0;
      /* Task Events Here -*-*-*-*/
      //if(Get_KeyStatus() && Key_Flag == 0 && GSM_GetKey == 0)
      // {
      //   Get_key = 1;
      //   isr_evt_set(0x0003, t_key);
      // }
      /*-*-*- User Code Here -*-*-*/
      if(GSM_Tmr_Stat_Flg == 1)
       {
         if(GSM_Time_Delay-- == 0)
          {
           GSM_Tmr_OV_Flg = 1;    /* Set Timer Overflow */
           GSM_Tmr_Stat_Flg = 0;  /* Indicates User Timer delay is done */
          }
       }
      /*--------------------------*/

      if(++Sec_Cnt == 60)       /* Check for 1 Minute (1sec * 60) */
       {
        Sec_Cnt = 0;
//        if(Min_Cnt >= 1 && Menu_Flag == 0)
//          Menu_Flag = 1;

        if(++Min_Cnt == 60)     /* Check for 1 Hour (1min * 60)   */
         {
          Min_Cnt = 0;
          if(++Hour_Cnt == 24)  /* Check for 1 Day (1hour * 24) */
           {
            Hour_Cnt = 0;
           }
         }
       }
     }
    TIM2->SR &= ~(1<<0);   /* clear UIF flag */
   }
}

/*******************************************************************************
* Function Name  : TIM3_IRQHandler
* Description    : This function handles TIM3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM3_IRQHandler(void)
{
	if((TIM3->SR & 0x0001) != 0)
	{
		print_seq();
		TIM3->SR &= ~(1<<0);   /* clear UIF flag */
	}
}

/*******************************************************************************
* Function Name  : TIM4_IRQHandler
* Description    : This function handles TIM4 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM4_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : I2C1_EV_IRQHandler
* Description    : This function handles I2C1 Event interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C1_EV_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : I2C1_ER_IRQHandler
* Description    : This function handles I2C1 Error interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C1_ER_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : I2C2_EV_IRQHandler
* Description    : This function handles I2C2 Event interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C2_EV_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : I2C2_ER_IRQHandler
* Description    : This function handles I2C2 Error interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C2_ER_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : SPI1_IRQHandler
* Description    : This function handles SPI1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : SPI2_IRQHandler
* Description    : This function handles SPI2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : USART1_IRQHandler
* Description    : This function handles USART1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART1_IRQHandler(void)
{
  u8 chr;
  if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET)
   {
    if(PC_Rx_Flag == 0)
     {
       if((chr = USART_ReceiveData(USART1)) == 'C')
        {
         PC_Rx_Cnt  = 0;
         PC_Buffer[PC_Rx_Cnt++] = chr;
        }
       else
        {
         PC_Buffer[PC_Rx_Cnt++] = chr;
         if(chr == '\r' || chr == '\n' || chr == 'Z')
          {
           PC_Buffer[PC_Rx_Cnt] = '\0';
           PC_Rx_Cnt = 0;
           PC_Rx_Flag = 1;
          }
         else if(PC_Rx_Cnt >= PC_RX_SIZE)
           PC_Rx_Cnt = 0;
        }
     }
    else
     {
      USART_ClearITPendingBit(USART1, USART_IT_RXNE);
     }
   }
  else
   {
     USART_ClearITPendingBit(USART1, USART_IT_ALL);
   }
}

/*******************************************************************************
* Function Name  : USART2_IRQHandler
* Description    : This function handles USART2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART2_IRQHandler(void)
{
	if(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) != RESET)
	{
		GSM_Isr();
	}
	else
	{
		USART_ClearITPendingBit(USART2, USART_IT_ALL);
	}
}

/*******************************************************************************
* Function Name  : USART3_IRQHandler
* Description    : This function handles USART3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/


void USART3_IRQHandler(void)
{
	static volatile unsigned char i = 0;
	volatile u8 rec;
	static u8 start = 0;
	if(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) != RESET)
	{
		rec = USART_ReceiveData(USART3);

		SMRTCARD_Buffer[smrt_cnt++]=rec;

		if(!rec_flag_rfid)
		{
			if((rec == STRCHR) && (!start))
			{
				start = 1;
				i = 0;
			}
			else if(start)
			{
//				if(i != BUF_LEN)
//					membuf[i++] = rec;
				if(rec == ENDCHR)
				{
					start = 0;
					rec_flag_rfid = 1;
					//membuf[i - 1] = '\0';
					SMRTCARD_Buffer[smrt_cnt++]='\0';
				}
			}
		}

	}
	else
	{
		USART_ClearITPendingBit(USART3, USART_IT_ALL);
	}
}

/*******************************************************************************
* Function Name  : EXTI15_10_IRQHandler
* Description    : This function handles External lines 15 to 10 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI15_10_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : RTCAlarm_IRQHandler
* Description    : This function handles RTC Alarm interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RTCAlarm_IRQHandler(void)
{
	/* Wait until last write operation on RTC registers is terminated */
	RTC_WaitForLastTask();
	/* Sets RTC Counter value to 0x00 */
	RTC_SetCounter(0x00);
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();

	/* Increment the date */
	DateUpdate();

	RTC_ClearITPendingBit(RTC_IT_ALR);

}

/*******************************************************************************
* Function Name  : USBWakeUp_IRQHandler
* Description    : This function handles USB WakeUp interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USBWakeUp_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM8_BRK_IRQHandler
* Description    : This function handles TIM8 Break interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM8_BRK_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM8_UP_IRQHandler
* Description    : This function handles TIM8 overflow and update interrupt
*                  request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM8_UP_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM8_TRG_COM_IRQHandler
* Description    : This function handles TIM8 Trigger and commutation interrupts
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM8_TRG_COM_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM8_CC_IRQHandler
* Description    : This function handles TIM8 capture compare interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM8_CC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : ADC3_IRQHandler
* Description    : This function handles ADC3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ADC3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : FSMC_IRQHandler
* Description    : This function handles FSMC global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void FSMC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : SDIO_IRQHandler
* Description    : This function handles SDIO global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SDIO_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM5_IRQHandler
* Description    : This function handles TIM5 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM5_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : SPI3_IRQHandler
* Description    : This function handles SPI3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : UART4_IRQHandler
* Description    : This function handles UART4 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART4_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : UART5_IRQHandler
* Description    : This function handles UART5 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART5_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM6_IRQHandler
* Description    : This function handles TIM6 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM6_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM7_IRQHandler
* Description    : This function handles TIM7 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM7_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA2_Channel1_IRQHandler
* Description    : This function handles DMA2 Channel 1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA2_Channel1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA2_Channel2_IRQHandler
* Description    : This function handles DMA2 Channel 2 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA2_Channel2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA2_Channel3_IRQHandler
* Description    : This function handles DMA2 Channel 3 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA2_Channel3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA2_Channel4_5_IRQHandler
* Description    : This function handles DMA2 Channel 4 and DMA2 Channel 5
*                  interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA2_Channel4_5_IRQHandler(void)
{
}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
