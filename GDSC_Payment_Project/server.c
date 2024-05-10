//Include Section
#include <stdio.h>
#include <stdlib.h>
#include "server.h"
#include "types.h"
#include "card.h"
#include "terminal.h"

uint32_t SequenceNumber = 1000512;
uint16_t choosed_account;
struct ST_transaction_t transaction_data;

//Data base
ST_accountsDB_t Accounts[MAX_ACCOUNTS] =   {{2000.0,  RUNNING, "8989374615436851"},
                                            {3000.0,  BLOCKED, "8989374615436852"},
                                            {3000.0,  BLOCKED, "8989374615436853"},
                                            {15000.0, RUNNING, "8989374615436854"},
                                            {9000.0,  RUNNING, "8989374615436855"},
                                            {750.0,   RUNNING, "8989374615436856"},
                                            {4000.0,  BLOCKED, "8989374615436857"},
                                            {1500.0,  BLOCKED, "8989374615436858"},
                                            {800.0,   BLOCKED, "8989374615436859"},
                                            {30000.0, RUNNING, "8989374615436860"},
                                            {1900.0 , RUNNING, "8989374615436861"}};

ST_transaction_t transactions[MAX_TRANSACTIONS];




/** @brief  This function will take card data and validate if the account related to this card exists or not
 ** @param  (transData) The transdata structure (cardHolderData - terminalData - transState)
 ** @retval The state of the process
 **/
EN_transState_t recieveTransactionData(ST_transaction_t *transData){
    EN_transState_t state = INTERNAL_SERVER_ERROR;
    if(NULL == transData){

    }
    else{
        uint16_t counter;
        for(counter = 0; counter < MAX_ACCOUNTS; counter++){
            if(atoi(Accounts[counter].primaryAccountNumber) == atoi(transData ->cardHolderData.primaryAccountNumber)){
                state = APPROVED;
                break;
            }
            state = FRAUD_CARD;
        }

        choosed_account = counter;

        if(state == APPROVED){

            if(Accounts[choosed_account].state == BLOCKED){
                transData -> transState = DECLINED_STOLEN_CARD;
                EN_serverError_t save_state = saveTransaction(transData);
                state = DECLINED_STOLEN_CARD;
            }
            else{
                ST_terminalData_t *ptr = &(transData->terminalData);

                EN_terminalError_t check = isBelowMaxAmount(ptr);
                if(check == TERMINAL_OK){
                    if((transData->terminalData.transAmount) <= Accounts[choosed_account].balance){

                        transData -> transState = APPROVED;
                        EN_serverError_t save_state = saveTransaction(transData);
                        if(save_state == SERVER_OK){
                            state = APPROVED;
                        }
                        else{
                            state = INTERNAL_SERVER_ERROR;
                        }
                    }
                    else{
                        transData -> transState = DECLINED_INSUFFECIENT_FUND;
                        EN_serverError_t save_state = saveTransaction(transData);
                        state = DECLINED_INSUFFECIENT_FUND;
                    }
                }
                else{
                    transData -> transState = EXCEED_MAX_AMOUNT;
                    EN_serverError_t save_state = saveTransaction(transData);
                }
            }

        }
    }

    return state;
}


/** @brief  This function check if account exists or not
 ** @param  (cardData) The card data structure (Name - PAN number - Expiry date)
 ** @param  (accountRefrence) The whole accounts array
 ** @retval The state of the process
 **/
EN_serverError_t isValidAccount(ST_cardData_t cardData, ST_accountsDB_t accountRefrence){
    EN_serverError_t state = ACCOUNT_NOT_FOUND;

    uint16_t counter;
    for(counter = 0; counter < MAX_ACCOUNTS; counter++){
        if(atoi(Accounts[counter].primaryAccountNumber) == atoi(&(cardData.primaryAccountNumber))){
            state = SERVER_OK;
            break;
        }
        state = ACCOUNT_NOT_FOUND;
    }
    choosed_account = counter;


    return state;
}


/** @brief  This function check if account is blocked or not
 ** @param  (accountRefrence) The whole accounts array
 ** @retval The state of the process
 **/
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence){
    EN_serverError_t card_state = SERVER_OK;
    if(NULL == accountRefrence){

    }
    else{

        if(Accounts[choosed_account].state== BLOCKED){
            card_state = BLOCKED_ACCOUNT;
        }
    }
    return card_state;
}


/** @brief  This function will take terminal data and check if amount is available or not
 ** @param  (termData) The term data structure (transAmount - maxTransAmount - transactionDate)
 ** @retval The state of the process
 **/
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData){
    EN_serverError_t state = LOW_BALANCE;
    if(NULL == termData){

    }
    else{
        if((termData->transAmount) <= Accounts[choosed_account].balance){
                state = SERVER_OK;
            }
    }
    return state;
}


/** @brief  This function will store all transaction data in the transactions database.
 ** @param  (transData) The transdata structure (cardHolderData - terminalData - transState)
 ** @retval The state of the process
 **/
EN_serverError_t saveTransaction(ST_transaction_t *transData){
    EN_serverError_t state = SAVING_FAILED;
    if(NULL == transData){

    }
    else{
        Accounts[choosed_account].balance -= transData ->terminalData.transAmount;
        transactions[choosed_account].transactionSequenceNumber = SequenceNumber;  //gives a sequence number to a transaction so it will be saved in data base
        if(getTransaction(SequenceNumber, transactions) == SERVER_OK){
            //Check if the transaction is successfully saved in transactions DB
            state = SERVER_OK;
            SequenceNumber++;
        }
        else{
            //the transaction can't be saved in transactions DB (ex:Dropped Connection)
            state = SAVING_FAILED;
        }
    }

    return state;

}


/** @brief  This function search about the Transaction Sequence Number in transactions DB.
 ** @param  (transData) The transdata structure (cardHolderData - terminalData - transState)
 ** @retval The state of the process
 **/
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData){
    EN_serverError_t state = TRANSACTION_NOT_FOUND;
    if(NULL == transData){

    }
    else{

            if(transactionSequenceNumber == transactions[choosed_account].transactionSequenceNumber){
                state = SERVER_OK;
              transactions[choosed_account].cardHolderData = transData -> cardHolderData;
                transactions[choosed_account].terminalData = transData -> terminalData;
                transactions[choosed_account].transactionSequenceNumber = transData -> transactionSequenceNumber;
                transactions[choosed_account].transState = transData -> transState;

        }
    }

    return state;
}


/** @brief  This function return the user Balance.
 ** @param  None
 ** @retval None
 **/
void getBalanceValue(void){
    printf("Your Balance is: %.2f\n",Accounts[choosed_account].balance);
}
