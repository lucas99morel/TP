#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

float* account_balances;

int process_transaction(int from_acct, int to_acct, float  dollars){
    int old_cancel_state;

    if(account_balances[from_acct] < dollars){
        return 1;
    }

    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,&old_cancel_state);
    
    account_balances[to_acct] += dollars;
    account_balances[from_acct] -= dollars;

    pthread_setcancelstate(old_cancel_state,NULL);

    return 0;
}

int main(){
    int num_accounts = 3;
    account_balances = malloc(sizeof(float) * num_accounts);

    account_balances[0] = 100.0;
    account_balances[1] = 200.0;
    account_balances[2] = 300.0;

    printf("Saldos iniciales:\n");
    for(int i=0; i<num_accounts; ++i){
        printf("Cuenta %d: %.2f\n", i, account_balances[i]);
    }

    if(process_transaction(0, 1, 50.0) == 0){
        printf("\nTransacción realizada con éxito.\n");
    } else {
        printf("\nFondos insuficientes.\n");
    }

    printf("Saldos después de la transacción:\n");
    for(int i=0; i<num_accounts; ++i){
        printf("Cuenta %d: %.2f\n", i, account_balances[i]);
    }

    free(account_balances);
    return 0;
}