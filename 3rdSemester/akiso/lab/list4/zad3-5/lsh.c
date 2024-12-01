#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
#include <linux/limits.h>
#include <signal.h>

#define LSH_RL_BUFSIZE 1024
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\n\r\a"

char *lsh_read_line() {
    int bufsize = LSH_RL_BUFSIZE;
    char *buffer = malloc(sizeof(char) * bufsize); 
    int position = 0;
    int c; // we use int because EOF is an int

    // allocation failure
    if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }
    
    while(1) {
        c = getchar();

        // return on hitting EOF
        if (c == EOF) {
            printf("\n");
            exit(EXIT_SUCCESS);
        } else if (c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }

        position++;

        // reallocate memory if we exceeded the buffer
        if (position >= bufsize) {
            bufsize += LSH_RL_BUFSIZE;
            // TODO: check
            buffer = realloc(buffer, bufsize); 
            if (!buffer) {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

char **lsh_split_line(char *line) {
    int bufsize = LSH_TOK_BUFSIZE;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;
    int position = 0;

    // allocation failure
    if (!tokens) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, LSH_TOK_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += LSH_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        
        // TODO: check
        token = strtok(NULL, LSH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

int lsh_launch(char **args) {
    pid_t pid, wpid; 
    int status;
    int position = 0;
    int wait = 1;

    // get last position
    while (args[position] != NULL) {
        position++;
    }
    position = position - 1;

    if (strcmp(args[position], "&") == 0) {
        args[position] = NULL;
        wait = 0;
    }
    
    pid = fork();
    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            perror("lsh");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Forking error
        perror("lsh");
    } else {
        // Parent process
        if (wait) {
            do {
                wpid = waitpid(pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }
    }
    
    return 1;
}

// declarations of built-in functions 
int lsh_cd(char **args);
int lsh_exit(char **args);

char *builtin_str[] = {
    "cd",
    "exit"
};

int (*builtin_func[]) (char **) = {
    &lsh_cd,
    &lsh_exit
};

int lsh_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

int lsh_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "lsh: expected argument for cd\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("lsh");
        }
    }
    return 1;
}

int lsh_exit(char **args) {
    return 0;
}

// handle terminated child processes
void CHLDhandler(int sig) {
    (void)sig;
    while (waitpid(-1, NULL, WNOHANG) > 0) {
        
    }
}

int lsh_execute(char **args) {
    int i;

    if (args[0] == NULL) {
        // empty command
        return 1;        
    }
    
    for (i = 0; i < lsh_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }
    
    return lsh_launch(args);
}

char *lsh_cut_cwd(char *cwd) {
    // char *directory;
    int position = 0;
    int last_dir_pos;

    if (cwd[0] != '/') {
        perror("lsh path error");
        exit(EXIT_FAILURE);
    } else if (cwd[1] == '\0') {
        return cwd;
    }

    while (cwd[position] != '\0') {
        if (cwd[position] == '/') {
            last_dir_pos = position;
        }
        position++;
    }

    // strcpy(directory, cwd + last_dir_pos);
    // return directory;
    return cwd + last_dir_pos + 1;
}

void lsh() {
    char cwd[PATH_MAX];
    char *cwd_short;
    char *line;
    char **args;
    int status;

    do {
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            cwd_short = lsh_cut_cwd(cwd);
            printf("lsh %s> ", cwd_short);
            line = lsh_read_line();
            args = lsh_split_line(line);
            status = lsh_execute(args);

            free(line);
            free(args);
        } else {
            perror("lsh getcwd() error");
            exit(EXIT_FAILURE);
        }
    } while (status);
}

int main() {
    signal(SIGCHLD, CHLDhandler);

    lsh();

    return 0;
}
