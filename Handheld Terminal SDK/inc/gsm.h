
#ifndef __GSM_H
#define __GSM_H

#ifdef  __GSM_C
#define GSM_SCOPE
#else
#define GSM_SCOPE extern
#endif

typedef struct   /* GPRS Usage Structure */
{
	u8 APN[31];
	u8 USER[11];
	u8 PASSWD[11];
	u8 IP_ADDR[16];
	u8 PORT[6];
} GPRS_DETAILS;

GSM_SCOPE GPRS_DETAILS IP_Details;

GSM_SCOPE  void Init_GSM(void);
GSM_SCOPE  void Set_GSM_Reset(void);
GSM_SCOPE  void GSM_Tmr_Delay(u32 M_Sec);
GSM_SCOPE  void Send_DataTo_GSM(u8 Str[]);

GSM_SCOPE  s8 Setup_GSM_Modem(void);
GSM_SCOPE  s8 Check_GPRSNwk(void);
GSM_SCOPE  s8 Check_Network(void);
GSM_SCOPE  s8 Send_SMS(s8 Num[], s8 Msg[]);
GSM_SCOPE  s8 Establish_Connection(GPRS_DETAILS IP_Details);
GSM_SCOPE  s8 Connect_To_TCP_UDP(u8 Udp_Tcp_Id, GPRS_DETAILS IP_Details, u8 *GPRS_Test_Msg);

#endif

