
#define  __GSM_C

#include "pc_gsm.h"



u8 GSM_Init;
/*-*-*-*-*-*-*-*-*-*-*- Sending Data to GSM *-*-*-*-*-*-*-*-*-*-*-
Function:    Send_DataTo_GSM
Description: Used to send a command/string to GSM
Input:       String that is tobe passed to GSM
Return:      --None--
Note:        --None--
----------------------------------------------------------------*/
void Send_DataTo_GSM(u8 Str[])
{
	int ii;
	for(ii= 0; Str[ii] != '\0'; ii++)
	{
		USART_SendChar(GSM_PORT, Str[ii]);
	}
	USART_SendChar(GSM_PORT, '\r');
}

/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*
* Function Name  :
* Description    :
* Input          : Delay desired in milliseconds (1sec = 1000ms).
* Return         : None
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/
static void GSM_Tmr_Delay(u32 M_Sec)
{
	Delay_mSec((u16)(M_Sec));

}

/*-*-*-*-*-*-*-*-*-*-*-*- Set_GSM_Reset -*-*-*-*-*-*-*-*-*-*-*-*-
Function:    Set_GSM_Reset
Description: Used to Generate Reset Pulse to GSM Module.
Input:       --None--
Return:      --None--
Note:        --None--
----------------------------------------------------------------*/
static void Set_GSM_Reset(void)
{
	GSM_PWR_KEY_OFF();	 /* Clear module pin float */
	GSM_Tmr_Delay(550);	 /* Delay for 550 msec     */

	GSM_PWR_KEY_ON();		 /* set module pin float   */
	GSM_Tmr_Delay(2320); /* Delay for 2Sec,320mSec */

	GSM_PWR_KEY_OFF();   /* Clear module pin float */
}

/*-*-*-*-*-*-*-*-*-*-*-*- Set-Up GSM -*-*-*-*-*-*-*-*-*-*-*-*-*-*-
Function:    Setup_GSM_Modem
Description:
Input:       --None--
Return: Returns 0 on success, and >0 on failure
Note:   This should be called at the power on for 1 time
----------------------------------------------------------------*/
static s8 Setup_GSM_Modem(void)
{
	s16 cnt = 0;

	/* GSM Initializations -*-*-*-*-*-*-*-*-*-*-*-*/
	GSM_Rx_Cnt = 0;

	Send_DataTo_GSM(AT_COMMAND);
	GSM_Tmr_Delay(500);

	if(Strncmp((uc8 *)(GSM_Rx_Buffer+(GSM_Rx_Cnt-4)),"OK",2) != 0)
	{
		GSM_Tmr_Delay(1000);
		Send_DataTo_GSM(AT_COMMAND);
		GSM_Tmr_Delay(200);

		if(Strncmp((uc8 *)(GSM_Rx_Buffer+(GSM_Rx_Cnt-4)),"OK",2) != 0)
		{
			GSM_Tmr_Delay(1000);
			Send_DataTo_GSM(AT_COMMAND);
			GSM_Tmr_Delay(200);

			if(Strncmp((uc8 *)(GSM_Rx_Buffer+(GSM_Rx_Cnt-4)),"OK",2) != 0)
			{
				Set_GSM_Reset();
				return 1;  /* Return error code that module is not ok */
			}
		}
	}
	GSM_Tmr_Delay(5000);

	Send_DataTo_GSM(SET_BAUD_9600);
	GSM_Tmr_Delay(200);

	Send_DataTo_GSM(STOP_US_RESP);
	GSM_Tmr_Delay(200);

	Send_DataTo_GSM(SAVE_PARA);
	GSM_Tmr_Delay(200);

	Send_DataTo_GSM(CHK_SIM_STS);
	GSM_Tmr_Delay(200);

	Send_DataTo_GSM(SET_SMS_TO_TEXT);
	GSM_Tmr_Delay(200);

	Send_DataTo_GSM(STOP_SMS_INDCAT);
	GSM_Tmr_Delay(200);

	Send_DataTo_GSM(SET_CRC);
	GSM_Tmr_Delay(200);

	Send_DataTo_GSM(SET_CLIP);
	GSM_Tmr_Delay(200);

	while(Check_Network() != 0)
	{
		cnt++;
		GSM_Tmr_Delay(4000);
		if(cnt >= 15)
		{
			return 2;  /* Return registration error */
		}
	}
	Send_DataTo_GSM(CHK_SIGNAL);
	GSM_Tmr_Delay(10);
	return 0;   /* Return success message to caller */
}

/*-*-*-*-*-*-*-*-*-*-*-*- Initialize GSM -*-*-*-*-*-*-*-*-*-*-*-*-
Function:    Init_GSM
Description: Used to initialize the GSM
Input:       --None--
Return: Returns 0 on success, and >0 on failure
Note:   This should be called at the power on for 1 time
----------------------------------------------------------------*/
void Init_GSM(void)
{
	GSM_PWR_ENABLE();
	GSM_GSM_DTR_OFF();
	GSM_Tmr_Delay(1000);

	if(Setup_GSM_Modem() == 0)
	{
		GSM_Init = 0; /* GSM Init. Ok Indicator */

		/* Load IP Details */
		Strcpy(IP_Details.APN, "airtelgprs.com");        /* Fill APN */
		Strcpy(IP_Details.USER, "admin");                /* Fill User Name */
		Strcpy(IP_Details.PASSWD, "admin");              /* Fill Password */
		Strcpy(IP_Details.IP_ADDR, "061.017.249.055");   /* Fill IP Address */
		Strcpy(IP_Details.PORT, "01010");
	}
	else
	{
		GSM_Init = 1;
		GSM_READY = 0;
	}

}
/*-*-*-*-*-*-*-*-*-*-*-*- Checking Network -*-*-*-*-*-*-*-*-*-*-*-
Function:    Check_Network
Description: Used to check the registration status of GSM
Input:       --None--
Return:      Returns 0 on success, and >0 on failure
Note:        --None--
----------------------------------------------------------------*/
s8 Check_Network(void)
{
	static s8 No_NetWK = 0;
	s8     TOD_4_while = 0;

	Strnset((u8 *)GSM_Rx_Buffer, '\0', 100);
	GSM_Rx_Cnt = 0;
	Send_DataTo_GSM(CHK_NETWORK);
	GSM_Tmr_Delay(600);

	if(GSM_Rx_Buffer[18] == '0' && (GSM_Rx_Buffer[20] == '1' || GSM_Rx_Buffer[20] == '5'))   /* Net work Available and In roaming */
	{
		No_NetWK  = 0;
		GSM_READY = 1;
		return 0; /* Return success message to caller */
	}
	else if(GSM_Rx_Buffer[18] == '0' && GSM_Rx_Buffer[20] == '2')
	{
		No_NetWK++;
		GSM_READY = 0;
		if(No_NetWK >= 20)
		{
			No_NetWK = 0;
			Send_DataTo_GSM(RESET_NW);
			GSM_Tmr_Delay(3000);
			TOD_4_while = 0;
			while(TOD_4_while < 10 && GSM_Rx_Buffer[12] != '+')
			{
				GSM_Tmr_Delay(100);
				TOD_4_while++;
			}
			GSM_Tmr_Delay(100);
			Send_DataTo_GSM(SET_NW);
			GSM_Tmr_Delay(2000);
			GSM_Init = 1;
		}
		return 1; /* Return Searching status to Caller */
	}
	else
	{
		No_NetWK++;
		GSM_READY = 0;
		if(No_NetWK >= 5)
		{
			No_NetWK = 0;
			Send_DataTo_GSM(RESET_NW);
			GSM_Tmr_Delay(500);
			TOD_4_while = 0;
			while(TOD_4_while < 10 && GSM_Rx_Buffer[12] != '+')
			{
				GSM_Tmr_Delay(100);
				TOD_4_while++;
			}
			GSM_Tmr_Delay(100);
			Send_DataTo_GSM(SET_NW);
			GSM_Tmr_Delay(2000);
			GSM_Init = 1;
		}
		return 2; /* Return NoResponse condition to Caller */
	}
}

/*-*-*-*-*-*-*-*-*-*-*-*- Checking Network -*-*-*-*-*-*-*-*-*-*-*-
Function:    Check_GPRSNwk
Description: Used to check the GPRS registration status of GSM
Input:       --None--
Return:      Returns 0 on success, and >0 on failure
Note:        --None--
----------------------------------------------------------------*/
s8 Check_GPRSNwk(void)
{
	static u8 No_GPRSNWK = 0, TOD_4_while, Module_Reset;

	GSM_Rx_Cnt = 0;
	Send_DataTo_GSM(CHK_GPRSNWK);
	GSM_Tmr_Delay(100);

	if(GSM_Rx_Buffer[20] == '0' && GSM_Rx_Buffer[22] == '1')    /* Process for GPRS Status */
	{
		No_GPRSNWK = 0;
		return 0;
	}
	else
	{
		No_GPRSNWK++;
		if(No_GPRSNWK >= 5)
		{
			No_GPRSNWK = 0;
			TOD_4_while = 0;
			if(2 >= ++Module_Reset)
			{
				Send_DataTo_GSM(RESET_NW);
				GSM_Tmr_Delay(500);

				while(TOD_4_while < 10 && GSM_Rx_Buffer[12] != '+')
				{
					GSM_Tmr_Delay(100);
					TOD_4_while++;
				}
				GSM_Tmr_Delay(100);
				Send_DataTo_GSM(SET_NW);
			}
			else
			{
				Send_DataTo_GSM("AT+CPOWD=1");
				GSM_Tmr_Delay(2000);
			}
			GSM_Tmr_Delay(500);
			No_GPRSNWK = 0;
			GSM_READY  = 0;
			GSM_Init = 1;
		}
		return 1;	  //GPRS feature to SIM CARD Not Enabled
	}
}

/*-*-*-*-*-*-*-*-*-*-*-*- Sending SMS Here -*-*-*-*-*-*-*-*-*-*-*-
Function:    Send_SMS
Description: Used to send an SMS to the said number
Input:       Num ----- The phone number that is to receive the SMS
Msg ----- The message tobe sent
Return:      Returns 0 on success, and >0 on failure
Note:        --None--
----------------------------------------------------------------*/
s8 Send_SMS(s8 Num[], s8 Msg[])
{
	u16 cnt = 0;
	u8 Temp_Buf[30];

	GSM_Rx_Cnt = 0;
	Strnset(Temp_Buf, '\0', 30);

	Strcpy(Temp_Buf, SEND_SMS);
	cnt = Strlen(SEND_SMS);
	Strcpy(Temp_Buf+cnt, (u8 *)Num);
	cnt = Strlen(Temp_Buf);
	Temp_Buf[cnt++] = '"';
	Temp_Buf[cnt++] = '\0';

	if(Check_Network() != 0) /* Check for GSM network */
		return 1;   /* No registration to sending SMS */

	Strnset((u8 *)GSM_Rx_Buffer, '\0', 100);

	Send_DataTo_GSM(Temp_Buf);	/* AT+CMGS="<Phone Number>" */
	GSM_Tmr_Delay(600);

	Strcpy((u8 *)GSM_Tx_Buffer, (uc8 *)Msg);
	cnt = Strlen((uc8 *)GSM_Tx_Buffer);

	if(cnt >= GSM_TX_SIZE)
		cnt = GSM_TX_SIZE-3;
	GSM_Tx_Buffer[cnt++] = 0x1A;
	GSM_Tx_Buffer[cnt++] = '\0';
	Send_DataTo_GSM((u8 *)GSM_Tx_Buffer);     /* Pushing Message to GSM */

	GSM_Tmr_Delay(800);
	cnt = 0;
	while(1)
	{
		GSM_Tmr_Delay(2000);
		if(Strncmp((uc8 *)(GSM_Rx_Buffer+2),"OK",2) == 0) /* SMS successfully sent */
		{
			Send_DataTo_GSM(AT_COMMAND);
			GSM_Tmr_Delay(500);
			cnt = 0;
			return 0; /* Return Success Msg to Caller */
		}
		cnt++;
		if(cnt >= 10)
			break;
	}
	if(cnt >= 10)
		return 1;
	else
		return 0;
}

/*-*-*-*-*-*-*-*-*-*-*- Establish_Connection -*-*-*-*-*-*-*-*-*-*-*
Function:    Establish_Connection
Description: Used to bring up GPRS connection
Input:       IP_Details --- This is a structure, which consists the
details of the server to connect to.
Return:      Returns 0 on success, and >0 on failure
Note:
If return value is 1, check APN & GPRS service for SIM card.
If return value is 2, error occured while bringing wireless connection.
GSM is tobe initialized again, if return code is 2.
----------------------------------------------------------------*/
static s8 Establish_Connection(GPRS_DETAILS IP_Details)
{
	u8 cnt = 0, Ciicr_Cnt = 0, Tod_While = 0;

	Send_DataTo_GSM(ENABLE_GPRS);  /* Enable GPRS connection */
	GSM_Tmr_Delay(300);
	/* Read phone book to see if SIM parameters initialized */
	Send_DataTo_GSM(PHONE_BOOK1);
	GSM_Tmr_Delay(300);

	Send_DataTo_GSM(CHK_SIGNAL);    /* Check signal strength */
	GSM_Tmr_Delay(300);

	Send_DataTo_GSM(DISCONNECT_CALL);
	GSM_Tmr_Delay(50);

	GSM_Rx_Cnt = 0;
	Send_DataTo_GSM(CHECK_SELF_IP);		/* AT+CIFSR --- GET LOCAL IP ADDRESS */
	cnt = Strlen(CHECK_SELF_IP);
	GSM_Tmr_Delay(500);

	if(Strncmp((uc8 *)(GSM_Rx_Buffer+cnt+3),"ERROR",5) == 0)	  /* Check ERROR status */
	{
		Strnset((u8 *)GSM_Tx_Buffer, '\0', GSM_TX_SIZE);  /* Clear SMS_Buf */

		Strcpy((u8 *)GSM_Tx_Buffer, SET_USER);            /* Copy AT+CSTT */
		cnt = Strlen((uc8 *)GSM_Tx_Buffer);

		Strcpy((u8 *)(GSM_Tx_Buffer+cnt), IP_Details.APN);  /* Copy APN */
		cnt = Strlen((uc8 *)GSM_Tx_Buffer);

		Strcpy((u8 *)(GSM_Tx_Buffer+cnt), "\",\"");
		cnt = Strlen((uc8 *)GSM_Tx_Buffer);

		Strcpy((u8 *)(GSM_Tx_Buffer+cnt), IP_Details.USER); /* Copy User Name */
		cnt = Strlen((uc8 *)GSM_Tx_Buffer);

		Strcpy((u8 *)(GSM_Tx_Buffer+cnt), "\",\"");
		cnt = Strlen((uc8 *)GSM_Tx_Buffer);

		Strcpy((u8 *)(GSM_Tx_Buffer+cnt), IP_Details.PASSWD); /* Copy Password */
		cnt = Strlen((uc8 *)GSM_Tx_Buffer);
		GSM_Tx_Buffer[cnt++] = '\"';

		Send_DataTo_GSM((u8 *)GSM_Tx_Buffer); /* Send AT+CSTT command to GSM */
		GSM_Tmr_Delay(500);
		Send_DataTo_GSM(CHECK_STATUS);	/* Send "AT+CIPSTATUS". QUERY connection status */
		Tod_While = 0;

		while((Strncmp((uc8 *)(GSM_Rx_Buffer+2),"STATE:",6) != 0) && Tod_While <= 20)
		{
			GSM_Tmr_Delay(500);
			Tod_While++;
		}
		GSM_Tmr_Delay(100);
		if(Strncmp((uc8 *)(GSM_Rx_Buffer+(GSM_Rx_Cnt-17)),"STATE: IP START",15) == 0)
		{

			GSM_Rx_Cnt = 0;
			Send_DataTo_GSM(CHECK_ACTIVE); /* AT+CIICR  Bring up wireless connection */
			cnt = Strlen(CHECK_ACTIVE);
			Ciicr_Cnt = 0;
			while(Ciicr_Cnt < 30)
			{
				GSM_Tmr_Delay(2000);
				if(Strncmp((uc8 *)(GSM_Rx_Buffer+cnt+3),"OK",2)==0)
				{
					Send_DataTo_GSM(CHECK_STATUS);	/* Send "AT+CIPSTATUS". QUERY connection status */
					GSM_Tmr_Delay(500);

					GSM_Rx_Cnt = 0;
					Send_DataTo_GSM(CHECK_SELF_IP);	/* "AT+CIFSR"	--- Get Local IP Address */
					GSM_Tmr_Delay(500);
					Ciicr_Cnt = 0;
					cnt = Strlen(CHECK_SELF_IP);

					if(GSM_Rx_Buffer[cnt+3] >= '1'  && GSM_Rx_Buffer[cnt+3] <= '9')
						break;
					else
						Ciicr_Cnt = 30;
				}
				else if(Strncmp((uc8 *)(GSM_Rx_Buffer+cnt+3),"ERROR",5) == 0)
				{
					Ciicr_Cnt = 30;
				}
				Ciicr_Cnt++;
			}
			if(Ciicr_Cnt >= 30)
			{
				GSM_READY = 0;
				Send_DataTo_GSM("AT+CPOWD=1");  /* PowerDown GSM (Due to no response) */
				GSM_Init = 1;
				GSM_Tmr_Delay(6000);
				return 2;
			}
		}
		else
			return 1;
	}
	return 0;
}
/*-*-*-*-*-*-*-*-*-*-*- Connect to TCP/UDP -*-*-*-*-*-*-*-*-*-*-*
Function:    Connect_To_TCP_UDP
Description: Used to connect to UDP or TCP
Input:       Udp_Tcp_Id --- UDP/TCP indicator (0 - UDP, 1 - TCP).
IP_Details --- This is a structure, which consists the
details of the server to connect to.
Return:      Returns 0 on success, and >0 on failure
Note:
If return value is 1, check APN & GPRS service for SIM card.
If return value is 2, error occured while bringing wireless connection.
If return value is 3, IP connection failed with server
If return value is 4, GPRS Nwk fail/PDP DACT/No Response from GSM
If return value is 5, "SEND OK" response not received. Send Failed
----------------------------------------------------------------*/
s8 Connect_To_TCP_UDP(u8 Udp_Tcp_Id, GPRS_DETAILS IP_Details, u8 *GPRS_Test_Msg)
{
	u8 cnt, Tod_While, len, wait_flag;

	cnt = Establish_Connection(IP_Details);
	if(cnt != 0)
	{
		return cnt;  /* Error occured in establishing GPRS connection */
	}

	Send_DataTo_GSM(CHECK_STATUS);	/* Send "AT+CIPSTATUS". QUERY connection status */
	Tod_While = 0;
	while((Strncmp((uc8 *)(GSM_Rx_Buffer+2),"STATE:",6) != 0) && Tod_While <= 20)
	{
		GSM_Tmr_Delay(100);
		Tod_While++;
	}

	if(Strncmp((uc8 *)(GSM_Rx_Buffer+2),"STATE: CONNECT OK",17) != 0)
	{
		Strnset((u8 *)GSM_Tx_Buffer, '\0', GSM_TX_SIZE); /* Clear SMS_Buf */

		Strcpy((u8 *)GSM_Tx_Buffer, SET_TO_CONNECT);

		if(Udp_Tcp_Id == 0)
			Strncpy((u8 *)(GSM_Tx_Buffer+13),"UDP",3);

		Strncpy((u8 *)(GSM_Tx_Buffer+19),IP_Details.IP_ADDR,15);
		Strncpy((u8 *)(GSM_Tx_Buffer+37),IP_Details.PORT,5);
		GSM_Rx_Cnt = 0;
		Send_DataTo_GSM((u8 *)GSM_Tx_Buffer);

		cnt = Strlen(SET_TO_CONNECT);
		GSM_Tmr_Delay(5000);


		if(Strncmp((uc8 *)GSM_Rx_Buffer+cnt+3,"OK",2)==0)
		{
			Tod_While = 0;
			while((Strncmp((uc8 *)GSM_Rx_Buffer+10,"OK",2)!=0) &&
				(Strncmp((uc8 *)GSM_Rx_Buffer+10,"FAIL",4)!=0) && (Tod_While<20))
			{
				Tod_While++;
				GSM_Tmr_Delay(500);
			}
		}
		else if(Strncmp((uc8 *)GSM_Rx_Buffer+cnt+3,"CONNECT OK",10) == 0)
		{
			Send_DataTo_GSM(CHECK_STATUS);
			GSM_Tmr_Delay(200);
		}
		else
		{
			Send_DataTo_GSM(IP_SHUT_DOWN);
			GSM_Tmr_Delay(500);
			return 3;  /* IP Connection failed */
		}
	}
	/* Status indicates progress of connection */
	if((Strncmp((uc8 *)(GSM_Rx_Buffer+(GSM_Rx_Cnt-12)),"CONNECT OK",10)==0) ||
		(Strncmp((uc8 *)(GSM_Rx_Buffer+(GSM_Rx_Cnt-19)),"STATE: CONNECT OK",17)==0))
	{
		while(1)
		{
			len = 0;
			Strnset((u8 *)GSM_Tx_Buffer, '\0', GSM_TX_SIZE); /* Clear SMS_Buf */
			Strcpy((u8 *)GSM_Tx_Buffer, GPRS_Test_Msg);

			len = Strlen((uc8 *)GSM_Tx_Buffer);
			GSM_Tx_Buffer[len++] = 0x1A;

			if(Check_GPRSNwk() != 0)
			{
				Send_DataTo_GSM(IP_SHUT_DOWN);
				GSM_Tmr_Delay(500);
				return 4;  /* Return Error Code */
			}

			GSM_Rx_Cnt = 0;
			Send_DataTo_GSM(TCP_SEND);	/* AT+CIPSEND  Send data through TCP/UDP connection */
			if(Strncmp((uc8 *)(GSM_Rx_Buffer + (GSM_Rx_Cnt-7)), "ERROR", 5) == 0)
			{
				Send_DataTo_GSM(TCP_CLOSE);
				GSM_Tmr_Delay(200);
				return 4;
			}
			GSM_Tmr_Delay(200);
			GSM_Check_SendOk = 1;
			Send_DataTo_GSM((u8 *)GSM_Tx_Buffer);
			wait_flag = 0;
			while(1)
			{
				GSM_Tmr_Delay(1000);
				if(Strncmp((uc8 *)(GSM_Rx_Buffer + (GSM_Rx_Cnt-9)), "SEND OK", 7) == 0)
				{
					Send_DataTo_GSM(AT_COMMAND);
					GSM_Tmr_Delay(100);
					break;
				}
				wait_flag++;
				if( wait_flag >= 12)   /* Check, if 12 * 1 Sec (= 12 Sec) Timeout reached */
				{
					GSM_Check_SendOk = 0;
					Send_DataTo_GSM(TCP_CLOSE);
					GSM_Tmr_Delay(500);
					return 5;     /* "SEND OK" failed to the previous CIPSEND */
				}
			}
			GSM_Check_SendOk = 0;
			return 0; /* Return success code */
		}
	}
	else if(Strncmp((uc8 *)(GSM_Rx_Buffer+2),"STATE: PDP DEACT",16) ==0 )
	{
		Send_DataTo_GSM(IP_SHUT_DOWN);
		GSM_Tmr_Delay(100);
		return 4;   /* Return Error Code */
	}
	else
	{
		Send_DataTo_GSM(TCP_CLOSE);	/* Send_DataTo_GSM(IP_SHUT_DOWN); */
		GSM_Tmr_Delay(100);
		return 4;   /* Return Error Code */
	}
}

