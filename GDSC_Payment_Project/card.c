
//Include Section
#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "card.h"


/** @brief  This function get the user name
 ** @param  (cardData) The card data structure (Name - PAN number - Expiry date)
 ** @retval The state of the process
 **/
EN_cardError_t getCardHolderName(ST_cardData_t *cardData){
    EN_cardError_t state = WRONG_NAME;
    if(NULL == cardData){

    }
    else{
        fflush(stdin);
        printf("Enter the Card Holder Name    : ");
        gets(cardData -> cardHolderName);

        uint8_t size = -1;
        while(cardData -> cardHolderName[++size]);

        if(size < 20 || size > 24){

        }
        else{
            state = CARD_OK;
        }
    }
    return state;
}


/** @brief  This function get the Card Expiry Date
 ** @param  (cardData) The card data structure (Name - PAN number - Expiry date)
 ** @retval The state of the process
 **/
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData){
    EN_cardError_t state = WRONG_EXP_DATE;
    if(NULL == cardData){

    }
    else{
        fflush(stdin);
        printf("Enter Card Expiry Date (MM/YY): ");
        gets(cardData -> cardExpirationDate);
        uint8_t size = -1;
        while(cardData ->cardExpirationDate[++size]);

        if((size == 5)
           &&(cardData -> cardExpirationDate[0] == '0' || cardData -> cardExpirationDate[0] == '1')
           &&(cardData -> cardExpirationDate[1] >= '0' && cardData -> cardExpirationDate[1] <= '9')
           &&(cardData -> cardExpirationDate[2] == '/')
           &&(cardData -> cardExpirationDate[3] >= '0' && cardData -> cardExpirationDate[3] <= '9')
           &&(cardData -> cardExpirationDate[4] >= '0' && cardData -> cardExpirationDate[4] <= '9')
           )
        {
            if((cardData -> cardExpirationDate[0] == '0' && cardData -> cardExpirationDate[1] == '0')
               ||(cardData -> cardExpirationDate[3] == '0' && cardData -> cardExpirationDate[4] == '0')
               ||(cardData -> cardExpirationDate[0] == '1' && cardData -> cardExpirationDate[1] > '2'))
            {

            }
            else{   //All Cases is right
                state = CARD_OK;
            }
        }

    }

    return state;
}


/** @brief  This function get the PAN Number
 ** @param  (cardData) The card data structure (Name - PAN number - Expiry date)
 ** @retval The state of the process
 **/
EN_cardError_t getCardPAN(ST_cardData_t *cardData){
    EN_cardError_t state = WRONG_PAN;
    if(NULL == cardData){

    }
    else{
        fflush(stdin);
        printf("Enter Primary Account Number  : ");
        gets(cardData -> primaryAccountNumber);
        uint8_t size = -1;
        while(cardData -> primaryAccountNumber[++size]);

        if(size < 16 || size > 19){

        }
        else{
            state = CARD_OK;
        }
    }

    return state;
}

