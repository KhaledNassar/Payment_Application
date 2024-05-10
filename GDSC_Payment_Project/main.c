#include <stdio.h>
#include <stdlib.h>
#include "main.h"


int main()
{
    appStart();

    return 0;
}

void appStart(void){
    uint16_t counter = 3;

        uint16_t getName = 1;
        counter = 3;
        while(1 == getName && counter){
            CardError_state = getCardHolderName(user_ptr);
            if(CARD_OK == CardError_state){
                getName = 0;

                uint16_t getExpDate = 1;
                counter = 3;
                while(1 == getExpDate && counter){
                    CardError_state = getCardExpiryDate(user_ptr);
                    if(CARD_OK == CardError_state){
                        getExpDate = 0;

                        uint16_t getPAN = 1;
                        counter = 3;
                        while(1 == getPAN && counter){
                            CardError_state = getCardPAN(user_ptr);
                            if(CARD_OK == CardError_state){
                                getPAN = 0;

                                //Clear screen and go to second stage
                                system("cls");
                                secondStage();
                            }
                            else{
                                printf("An error in the entered PAN, please try again !! \n");
                                printf("1- Try again\n");
                                printf("2- Exit\n");
                                printf("\n");
                                uint16_t c;
                                printf("Your choice: ");
                                scanf(" %d", &c);
                                if(1 == c){
                                    getPAN = 1;
                                    counter --;
                                }
                                else{
                                    getPAN = 0;
                                }
                            }
                        }
                    }
                    else{
                        printf("An error in the entered Expiry date, please try again !! \n");
                        printf("1- Try again\n");
                        printf("2- Exit\n");
                        printf("\n");
                        uint16_t c;
                        printf("Your choice: ");
                        scanf(" %d", &c);
                        if(1 == c){
                            getExpDate = 1;
                            counter --;
                        }
                        else{
                            getExpDate = 0;
                        }
                    }
                }
            }
            else{
                printf("An error in the entered Name, please try again !! \n");
                printf("1- Try again\n");
                printf("2- Exit\n");
                printf("\n");
                uint16_t c;
                printf("Your choice: ");
                scanf(" %d", &c);
                if(1 == c){
                    getName = 1;
                    counter --;
                }
                else{
                    getName = 0;
                }
            }

        }

        sleep(3);
        system("cls");
        //Sleep("Thank you For using our System. \n");
        printf("Thank you For using our System. \n");
        sleep(3);
        system("cls");

}

void secondStage(void){
    uint16_t counter = 3;

    //Call The user
    printf("Welcome, ");
    uint8_t *token = strtok(user1.cardHolderName, " ");
    if (token != NULL) {
        printf("%s\n", token);
    }
    printf("\n");

    TerminalError_state = getTransactionDate(terminal_ptr);
    if(TERMINAL_OK == TerminalError_state){
        TerminalError_state = isCardExpired(user1, terminal1);
        if(TERMINAL_OK == TerminalError_state){

            uint16_t return_program = 1;
            while(1 == return_program){
                //Two ways(Transaction - Balance inquiry)
                printf("Which service do you want?\n");
                printf("1-   Transaction\n");
                printf("2-   Balance inquiry \n");
                printf("N/A- Exit \n\n");
                printf("Your choice: ");

                uint16_t service;
                scanf("%d", &service);

                if(1 == service){
                    system("cls");
                    uint16_t getAmount = 1;
                    counter = 3;
                    while(1 == getAmount && counter){
                        TerminalError_state = getTransactionAmount(terminal_ptr);
                        if(TERMINAL_OK == TerminalError_state){
                            getAmount = 0;
                            TerminalError_state = isBelowMaxAmount(terminal_ptr);
                            if(TERMINAL_OK == TerminalError_state){
                                system("cls");
                                thirdStageTrans();
                            }
                            else{
                                system("cls");
                                printf("Sorry, This Amount Exceed the Daily Transaction value!!\n");
                            }
                        }
                        else{
                            printf("An error in the entered Amount, please try again !! \n");
                            printf("1- Try again\n");
                            printf("2- Exit\n");

                            uint16_t c;
                            printf("Your choice: ");
                            scanf(" %d", &c);
                            if(1 == c){
                                getAmount = 1;
                                counter --;
                            }
                            else{
                                getAmount = 0;
                            }
                        }
                    }
                }
                else if(2 == service){
                    system("cls");
                    thirdStageBalance();
                }
                else{
                    system("cls");
                    break;
                }

                sleep(3);
                system("cls");
                printf("Do you want other services? \n");
                printf("1- Yes\n2- No\n\n");

                uint16_t c;
                printf("Your choice: ");
                scanf(" %d", &c);
                if(1 == c){
                    return_program = 1;
                    system("cls");
                }
                else{
                    return_program = 0;
                }

            }

        }
        else{
            printf("Sorry, This card is Expired. \nPlease contact us on 19015!! \n");
        }

    }
}

void thirdStageTrans(void){
    ServerError_state = isValidAccount(user1, accountRefrence);
    if(SERVER_OK == ServerError_state){
        ServerError_state = isBlockedAccount(&accountRefrence);
        if(SERVER_OK == ServerError_state){
            ServerError_state = isAmountAvailable(terminal_ptr);
            if(SERVER_OK == ServerError_state){
                transaction.cardHolderData = user1;
                transaction.terminalData = terminal1;
                ServerError_state = saveTransaction(trans_ptr);
                if(SERVER_OK == ServerError_state){
                    printf("The Process has successfully done\n");
                }
                else{
                    printf("Sorry, This is a Server Error.\n");
                }
            }
            else{
                printf("Sorry, This Amount is Unavailable in your balance.\n");
            }
        }
        else{
            printf("This Account is Blocked, Are you the Thief?!\n");
        }

    }
    else{
        printf("Sorry, This Account is invalid. \nPlease contact us on 19015!! \n");
    }
}

void thirdStageBalance(void){
    ServerError_state = isValidAccount(user1, accountRefrence);
    if(SERVER_OK == ServerError_state){
        ServerError_state = isBlockedAccount(&accountRefrence);
        if(SERVER_OK == ServerError_state){
            getBalanceValue();
        }
        else{
            printf("This Account is Blocked, Are you the Thief?!\n");
        }

    }
    else{
        printf("Sorry, This Account is invalid. \nPlease contact us on 19015!! \n");
    }
}

