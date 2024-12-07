#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <linux/limits.h>
#include <signal.h>
#include <fcntl.h>

#define LSH_RL_BUFSIZE 1024
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\n\r\a"
#define LSH_MAX_JOBS 255

void remove_element(char **array, int index, int array_length) {
    int i;
    for (i = 0; i < array_length; i++) {
        array[i] = array[i + 1];
    }
    
}

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
            buffer = realloc(buffer, sizeof(char) * bufsize); 
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
        
        token = strtok(NULL, LSH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

int lsh_launch(char **args, int in, int out, int err) {
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
        if (in != -1) {
            if (dup2(in, 0) != 0) {
                perror("lsh: dup2 in");
                exit(1);
            }
            close(in);        
        }
        
        if (out != -1) {
            if (dup2(out, 1) != 1) {
                perror("lsh: dup2 out");
                exit(1);
            }
            close(out);
        }

        if (err != -1) {
            if (dup2(err, 2) != 2) {
                perror("lsh: dup2 err");
                exit(1);
            }
            close(err);
        }
        
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

void INThandler(int sig) {
    (void)sig;
}

void TSTPhandler(int sig) {
    (void)sig;
}

int lsh_execute(char **args) {
    int t1, t2, i;
    int position = 0;
    int pipefd[2];
    int piped = 0;
    int in = -1, out = -1, err = -1;

    if (args[0] == NULL) {
        // empty command
        return 1;        
    }

    while (args[position] != NULL && !piped) {
        if (strcmp(args[position], "|") == 0) {
            piped = 1;
            args[position] = NULL;

            if (pipe(pipefd) < 0) {
                perror("lsh: pipe");
                exit(1);
            }

            if (fork() == 0) {
                if (dup2(pipefd[1], 1) != 1) {
                    perror("lsh: dup2(pipefd[1])");
                    exit(1);
                }

                close(pipefd[1]);
                close(pipefd[0]);

                lsh_launch(args, in, out, err);
                exit(1);
            } else if (fork() == 0) {
                if (dup2(pipefd[0], 0) != 0) {
                    perror("lsh: dup2(pipefd[0])");
                    exit(1);
                }

                close(pipefd[1]);
                close(pipefd[0]);

                lsh_execute(args + position + 1);
                exit(1);
            } else {
                close(pipefd[1]);
                close(pipefd[0]);

                wait(&t1);
                wait(&t2);
            }
        } else if (strcmp(args[position], "<") == 0 || strcmp(args[position], ">") == 0 || strcmp(args[position], "2>") == 0) {
                char *filename = args[position + 1];

                if (filename == NULL) {
                    fprintf(stderr, "lsh: missing file name");
                    exit(EXIT_FAILURE);
                }

                if (strcmp(args[position], "<") == 0) {
                    args[position] = NULL;
                    in = open(filename, O_RDONLY);
                } else if (strcmp(args[position], ">") == 0) {
                    args[position] = NULL;
                    out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                } else if (strcmp(args[position], "2>") == 0) {
                    args[position] = NULL;
                    err = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                }            
            }

        position++;
    }    

    if (!piped) {
        for (i = 0; i < lsh_num_builtins(); i++) {
            if (strcmp(args[0], builtin_str[i]) == 0) {
                return (*builtin_func[i])(args);
            }
        }

        return lsh_launch(args, in, out, err);
    }

    return 1;
}

// for displaying cwd
char *lsh_cut_cwd(char *cwd) {
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

    return cwd + last_dir_pos + 1;
}

void lsh() {
    char cwd[PATH_MAX];
    char *cwd_short;
    char *line;
    char **args;
    int status;
    int max_jobs = LSH_MAX_JOBS;
    int *jobs = malloc(sizeof(int) * max_jobs);


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
    signal(SIGINT, INThandler);
    signal(SIGTSTP, TSTPhandler);

    lsh();

    return 0;
}
