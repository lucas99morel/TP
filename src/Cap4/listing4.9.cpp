#include <pthread.h>

class ThreadExitException{
    public:
    /* Create an exception-signaling thread exit with RETURN_VALUE. */
    ThreadExitException(void* return_value): thread_return_value_(return_value){
    
    }
/* Actually exit the thread, using the return value provided in the
constructor. */
    void* DoThreadExit(){
        pthread_exit(thread_return_value_);
    }
    private:
    /* The return value that will be used when exiting the thread. */
    void* thread_return_value_;
};

bool should_exit_thread_immediately() {
    return false;
}

void do_some_work (){
    while(1) {
        /* Do some useful things here... */
        if(should_exit_thread_immediately()){
            throw ThreadExitException (/* thread’s return value = */ NULL);
        }
    }
}


void* thread_function(void*){
    try {
        do_some_work();
    }
    catch(ThreadExitException ex) {
    /* Some function indicated that we should exit the thread. */
        ex.DoThreadExit();
    }
    return NULL;
}

#include <pthread.h>

int main() {
    pthread_t t;
    pthread_create(&t, nullptr, thread_function, nullptr);
    pthread_join(t, nullptr);
    return 0;
}
