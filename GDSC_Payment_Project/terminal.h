#ifndef _TERMINAL_H
#define _TERMINAL_H

//Include Section
#include "types.h"
#include "card.h"
#define MAX_TRANS_AMOUNT 5000

//Typedef Section
typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
    TERMINAL_OK,
    WRONG_DATE,
    EXPIRED_CARD,
    INVALID_CARD,
    INVALID_AMOUNT,
    EXCEED_MAX_AMOUNT,
    INVALID_MAX_AMOUNT
}EN_terminalError_t;

//Functions Prototype Section
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);                    // Date from PC
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData);  // If card Expired
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData);                            // If PAN Valid

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);                  // Transaction Amount

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);                      // If below Max
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData);                          // Set Max Amount


#endif // _TERMINAL_H
