#ifndef _CARD_H
#define _CARD_H

//Include Section
#include "types.h"


//Typedef Section
typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
    CARD_OK,          // The process is successfully done
    WRONG_NAME,       // An issue in the Name
    WRONG_EXP_DATE,   // An issue in the Expiry date
    WRONG_PAN         // An issue in the PAN number
}EN_cardError_t;


//Functions Prototype Section
EN_cardError_t getCardHolderName(ST_cardData_t *cardData);    // User Name
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);    // Card Expiry Date
EN_cardError_t getCardPAN(ST_cardData_t *cardData);           // Card PAN

#endif // _CARD_H
