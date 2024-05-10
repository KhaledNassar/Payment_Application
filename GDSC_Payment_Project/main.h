#ifndef _MAIN_H
#define _MAIN_H

//Include Section
#include "types.h"
#include "card.h"
#include "terminal.h"
#include "server.h"
#include <windows.h>

//Global var section
    ST_cardData_t user1;
    ST_cardData_t *user_ptr = &user1;
    EN_cardError_t CardError_state;

    ST_terminalData_t terminal1;
    ST_terminalData_t *terminal_ptr = &terminal1;
    EN_terminalError_t TerminalError_state;

    ST_transaction_t transaction;
    ST_transaction_t *trans_ptr = &transaction;
    EN_transState_t TransError_state;

    EN_serverError_t ServerError_state;

    ST_accountsDB_t accountRefrence;

//Functions Prototype Section
void appStart(void);
void secondStage(void);
void thirdStageTrans(void);
void thirdStageBalance(void);

#endif // _MAIN_H
