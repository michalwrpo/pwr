#include <signal.h>
#include <stdio.h>

int go = 1;

void handler(int sig) {
    printf("Sig: %d\n", sig);
    go = 0;

}

void sendSignals() {
    raise(SIGHUP);
    raise(SIGINT);
    raise(SIGQUIT);
    raise(SIGILL);
    raise(SIGTRAP);
    raise(SIGABRT);
    raise(SIGBUS);
    raise(SIGFPE);
    raise(SIGUSR1);
    raise(SIGSEGV);
    raise(SIGUSR2);
    raise(SIGPIPE);
    raise(SIGALRM);
    raise(SIGTERM);
    raise(SIGSTKFLT);
    raise(SIGCHLD);
    raise(SIGCONT);
    raise(SIGTSTP);
    raise(SIGTTIN);
    raise(SIGTTOU);
    raise(SIGURG);
    raise(SIGXCPU);
    raise(SIGXFSZ);
    raise(SIGVTALRM);
    raise(SIGPROF);
    raise(SIGWINCH);
    raise(SIGIO);
    raise(SIGPWR);
    raise(SIGSYS);
    raise(SIGRTMIN);
    raise(SIGRTMIN+1);
    raise(SIGRTMIN+2);
    raise(SIGRTMIN+3);
    raise(SIGRTMIN+4);
    raise(SIGRTMIN+5);
    raise(SIGRTMIN+6);
    raise(SIGRTMIN+7);
    raise(SIGRTMIN+8);
    raise(SIGRTMIN+9);
    raise(SIGRTMIN+10);
    raise(SIGRTMIN+11);
    raise(SIGRTMIN+12);
    raise(SIGRTMIN+13);
    raise(SIGRTMIN+14);
    raise(SIGRTMIN+15);
    raise(SIGRTMAX-14);
    raise(SIGRTMAX-13);
    raise(SIGRTMAX-12);
    raise(SIGRTMAX-11);
    raise(SIGRTMAX-10);
    raise(SIGRTMAX-9);
    raise(SIGRTMAX-8);
    raise(SIGRTMAX-7);
    raise(SIGRTMAX-6);
    raise(SIGRTMAX-5);
    raise(SIGRTMAX-4);
    raise(SIGRTMAX-3);
    raise(SIGRTMAX-2);
    raise(SIGRTMAX-1);
    raise(SIGRTMAX);
    raise(SIGSTOP);
    raise(SIGKILL);
}

int main() {
    signal(SIGHUP, handler);
    signal(SIGINT, handler);
    signal(SIGQUIT, handler);
    signal(SIGILL, handler);
    signal(SIGTRAP, handler);
    signal(SIGABRT, handler);
    signal(SIGBUS, handler);
    signal(SIGFPE, handler);
    signal(SIGKILL, handler);
    signal(SIGUSR1, handler);
    signal(SIGSEGV, handler);
    signal(SIGUSR2, handler);
    signal(SIGPIPE, handler);
    signal(SIGALRM, handler);
    signal(SIGTERM, handler);
    signal(SIGSTKFLT, handler);
    signal(SIGCHLD, handler);
    signal(SIGCONT, handler);
    signal(SIGSTOP, handler);
    signal(SIGTSTP, handler);
    signal(SIGTTIN, handler);
    signal(SIGTTOU, handler);
    signal(SIGURG, handler);
    signal(SIGXCPU, handler);
    signal(SIGXFSZ, handler);
    signal(SIGVTALRM, handler);
    signal(SIGPROF, handler);
    signal(SIGWINCH, handler);
    signal(SIGIO, handler);
    signal(SIGPWR, handler);
    signal(SIGSYS, handler);
    signal(SIGRTMIN, handler);
    signal(SIGRTMIN+1, handler);
    signal(SIGRTMIN+2, handler);
    signal(SIGRTMIN+3, handler);
    signal(SIGRTMIN+4, handler);
    signal(SIGRTMIN+5, handler);
    signal(SIGRTMIN+6, handler);
    signal(SIGRTMIN+7, handler);
    signal(SIGRTMIN+8, handler);
    signal(SIGRTMIN+9, handler);
    signal(SIGRTMIN+10, handler);
    signal(SIGRTMIN+11, handler);
    signal(SIGRTMIN+12, handler);
    signal(SIGRTMIN+13, handler);
    signal(SIGRTMIN+14, handler);
    signal(SIGRTMIN+15, handler);
    signal(SIGRTMAX-14, handler);
    signal(SIGRTMAX-13, handler);
    signal(SIGRTMAX-12, handler);
    signal(SIGRTMAX-11, handler);
    signal(SIGRTMAX-10, handler);
    signal(SIGRTMAX-9, handler);
    signal(SIGRTMAX-8, handler);
    signal(SIGRTMAX-7, handler);
    signal(SIGRTMAX-6, handler);
    signal(SIGRTMAX-5, handler);
    signal(SIGRTMAX-4, handler);
    signal(SIGRTMAX-3, handler);
    signal(SIGRTMAX-2, handler);
    signal(SIGRTMAX-1, handler);
    signal(SIGRTMAX, handler);


    sendSignals();
    // while (go) {
        
    // }
    

    return 0;
}