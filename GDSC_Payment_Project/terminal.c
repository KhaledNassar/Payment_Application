
//Include Section
#include <stdio.h>
#include <stdlib.h>
#include <time.h>       // for Date
#include "types.h"
#include "terminal.h"
#include "card.h"


/** @brief  This function get the Transaction Date
 ** @param  (termData) The term data structure (transAmount - maxTransAmount - transactionDate)
 ** @retval The state of the process
 **/
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){
    EN_terminalError_t state = WRONG_DATE;
    if(NULL == termData){

    }
    else{
        state = TERMINAL_OK;
        time_t current_date = time(NULL);
        strftime(termData -> transactionDate, 11, "%d/%m/%Y", localtime(&current_date));
    }
    return state;
}


/** @brief  This function ask if the card is expired or not
 ** @param  (cardData) The card data structure (Name - PAN number - Expiry date)
 ** @param  (termData) The term data structure (transAmount - maxTransAmount - transactionDate)
 ** @retval The state of the process
 **/
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData){
    EN_terminalError_t state = EXPIRED_CARD;

    uint16_t expiration_year = atoi(&(cardData.cardExpirationDate[3]));
    uint16_t expiration_month = atoi(&(cardData.cardExpirationDate[0]));

    uint16_t transaction_year = atoi(&(termData.transactionDate[8]));
    uint16_t transaction_month = atoi(&(termData.transactionDate[3]));

    if(expiration_year > transaction_year){
        state = TERMINAL_OK;
    }
    else if(expiration_year == transaction_year){
        if(expiration_month > transaction_month){
            state = TERMINAL_OK;
        }
    }

    return state;
}


/** @brief  This function ask if the card PAN is valid or not
 ** @param  (cardData) The card data structure (Name - PAN number - Expiry date)
 ** @retval The state of the process
 **/
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData){
    EN_terminalError_t state = INVALID_CARD;
    if(NULL == cardData){

    }
    else{
        EN_cardError_t PAN_state = getCardPAN(cardData);
        if(CARD_OK == PAN_state){
            state = TERMINAL_OK;
        }
    }

    return state;
}


/** @brief  This function get Transaction Amount
 ** @param  (termData) The term data structure (transAmount - maxTransAmount - transactionDate)
 ** @retval The state of the process
 **/
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
    EN_terminalError_t state = INVALID_AMOUNT;
    if(NULL == termData){

    }
    else{
        fflush(stdin);
        printf("Enter The Transaction Amount: ");
        scanf("%f", &termData -> transAmount);

        if(termData -> transAmount > 0){
            state = TERMINAL_OK;
        }
    }

    return state;
}



/** @brief  This function ask if the transaction Amount is Below Max. Amount or not
 ** @param  (termData) The term data structure (transAmount - maxTransAmount - transactionDate)
 ** @retval The state of the process
 **/
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
    EN_terminalError_t state = EXCEED_MAX_AMOUNT;
    if(NULL == termData){

    }
    else{
        termData -> maxTransAmount = MAX_TRANS_AMOUNT;
        if((termData -> transAmount) <= (termData -> maxTransAmount)){
            state = TERMINAL_OK;
        }
    }
    return state;
}


/** @brief  This function sets the maximum allowed amount into terminal data
 ** @param  (termData) The term data structure (transAmount - maxTransAmount - transactionDate)
 ** @retval The state of the process
 **/
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData){
    EN_terminalError_t state = INVALID_MAX_AMOUNT;
    if(NULL == termData){

    }
    else{
        printf("Enter The Maximum Transaction Amount: ");
        scanf("%f", &termData -> maxTransAmount);

        if(termData -> maxTransAmount > 0){
            state = TERMINAL_OK;
        }
    }
    return state;
}

