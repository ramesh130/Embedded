#ifndef __GSM_Commands_H
#define __GSM_Commands_H

#ifdef  __GSM_C
#define GSM_SCOPE
#else
#define GSM_SCOPE extern
#endif

//#include "stm32f10x_type.h"
#include "stm32f10x.h"

/*--*--*--*--*--*--*--*-- AT Commands --*--*--*--*--*--*--*--*/
#define AT_COMMAND      (u8 *)"AT"
#define ATZ_COMMAND     (u8 *)"ATZ"
#define SET_BAUD_4800   (u8 *)"AT+IPR=4800"
#define SET_BAUD_9600   (u8 *)"AT+IPR=9600"
#define SET_BAUD_115200 (u8 *)"AT+IPR=115200"
#define SET_SMS_TO_TEXT (u8 *)"AT+CMGF=1"
#define SET_COLP        (u8 *)"AT+COLP=1"
#define SAVE_PARA       (u8 *)"AT&W"
#define ECHO_ON         (u8 *)"ATE1"
#define ECHO_OFF        (u8 *)"ATE0"
#define SET_MIC_VOL     (u8 *)"AT+CMIC=0,6"
#define SET_SPK_VOL     (u8 *)"AT+CLVL=99"
#define SET_CRC         (u8 *)"AT+CRC=1"
#define SET_CLIP        (u8 *)"AT+CLIP=1"
#define CHK_NETWORK     (u8 *)"AT+CREG?"
#define CHK_SIGNAL      (u8 *)"AT+CSQ"
#define CHK_SIM_STS     (u8 *)"AT+CPIN?"
#define DIAL_COMMAND    (u8 *)"ATD"
#define ANSWER_INCALL   (u8 *)"ATA"
#define DISCONNECT_CALL (u8 *)"ATH"
#define STOP_SMS_INDCAT (u8 *)"AT+CNMI=1,0,0,0"
#define STOP_US_RESP    (u8 *)"AT+CIURC=0"
#define READ_ONE_SMS    (u8 *)"AT+CMGR="
#define READ_ALL_SMS    (u8 *)"AT+CMGL=\"ALL\""
#define READ_RD_SMS     (u8 *)"AT+CMGL=\"REC READ\""
#define READ_URD_SMS    (u8 *)"AT+CMGL=\"REC UNREAD\""
#define DEL_ONE_SMS     (u8 *)"AT+CMGD="
#define DEL_RD_SMS      (u8 *)"AT+CMGD=\"DEL READ\""
#define DEL_URD_SMS     (u8 *)"AT+CMGD=\"DEL UNREAD\""
#define DEL_ALL_SMS     (u8 *)"AT+CMGDA=\"DEL ALL\""
#define SEND_SMS        (u8 *)"AT+CMGS=\""
#define SET_SPKR        (u8 *)"AT+CHFA=1"
#define ETONE           (u8 *)"AT+STTONE=1,2,15300000"
#define NOTONE          (u8 *)"AT+STTONE=0"
#define RESET_NW        (u8 *)"AT+CFUN=0"
#define SET_NW          (u8 *)"AT+CFUN=1"
#define PHONE_BOOK1     (u8 *)"AT+CPBR=1"
/*--*--*--*--*--*--*--*- GPRS Commands -*--*--*--*--*--*--*--*/
#define ENABLE_GPRS     (u8 *)"AT+CGATT=1"
#define CHK_GPRSNWK     (u8 *)"AT+CGREG?"
#define SET_USER        (u8 *)"AT+CSTT=\""
#define CHECK_STATUS    (u8 *)"AT+CIPSTATUS"
#define CHECK_ACTIVE    (u8 *)"AT+CIICR"
#define CHECK_SELF_IP   (u8 *)"AT+CIFSR"
#define TCP_SEND        (u8 *)"AT+CIPSEND"
#define ACK_DEACT       (u8 *)"AT+CIPSPRT=2"
#define TCP_CLOSE       (u8 *)"AT+CIPCLOSE"
#define IP_SHUT_DOWN    (u8 *)"AT+CIPSHUT"
#define SET_TO_CONNECT  (u8 *)"AT+CIPSTART=\"TCP\",\"000.000.000.000\",\"00000\""
#define SET_AIRTEL_USER (u8 *)"AT+CSTT=\"AIRTELGPRS.COM\",\"internet\",\"internet\""
/*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*/

#endif
