#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>
#include <pthread.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define true 1
#define false 0
#define bool int

char prompt_string = ':';
const char *cmd_delim = " ";

void prompt_and_read(char *buffer);

int main(int argc, char *argv[])
{

    int null_file = open("/dev/null", O_WRONLY);
    char cwd[2048];
    pid_t background_processes[512];
    int background_process_index = 0;
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        fprintf(stderr, "Couldn't read current working directory.");
        fflush(stderr);
    }
    int last_status = 0;
    char *command = malloc(sizeof(char) * 2048);
    char *tokenizer_buffer = malloc(sizeof(char) * 2048);

    while (true)
    {
        memset(command, '\0', sizeof(command));
        memset(tokenizer_buffer, '\0', sizeof(tokenizer_buffer));

        prompt_and_read(command);

        printf("Input: '%s'\n", command); fflush(stdout);
        char *program_name = strtok_r(command, cmd_delim, &tokenizer_buffer);
        printf("Program Name: '%s'\n", program_name); fflush(stdout);

        if (strcmp(program_name, "exit") == 0)
        {
            exit(0);
        }
        else if (strcmp(program_name, "cd") == 0)
        {
            char *dir = (char*) strtok_r(NULL, cmd_delim, &tokenizer_buffer);

            if (dir == NULL)
            {
                char *home_dir = getenv("HOME");
                chdir(home_dir);
                strcpy(cwd, home_dir);
            }
            else if (dir[0] == '/')
            {
                chdir(dir);
                strcpy(cwd, dir);
            }
            else
            {
                if (strcmp(dir, "..") == 0)
                {
                    for (int i = strlen(cwd) - 1; i >= 0; i--)
                    {
                        if (cwd[i] == '/')
                        {
                            cwd[i] = '\0';
                            break;
                        }
                    }
                }
                else if (strcmp(dir, ".") != 0)
                {
                    strcat(cwd, "/");
                    strcat(cwd, dir);
                }
                chdir(cwd);
            }
        }
        else if (strcmp(program_name, "status") == 0)
        {
            printf("CWD: %s\n", cwd);
            fflush(stdout);
            printf("Last Exited Status: %d\n", last_status);
            fflush(stdout);
        }
        else if (program_name[0] != '#')
        {
            printf("Getting PID\n"); fflush(stdout);
            pid_t parent = getpid();

            char *token;
            char *args[512];
            memset(args, '\0', 512);
            printf("Memset the Args\n"); fflush(stdout);
            int arg_index = 0;
            args[arg_index++] = program_name;

            char pid_token[8];
            memset(pid_token, '\0', 8);

            printf("Memset PID_token\n"); fflush(stdout);

            while (token = (char*) strtok_r(NULL, cmd_delim, &tokenizer_buffer))
            {
                if (strcmp(token, args[arg_index - 1]) == 0)
                {
                    continue;
                }
                if (strcmp(token, "$$") == 0)
                {
                    sprintf(pid_token, "%d", parent);
                    args[arg_index++] = pid_token;
                }
                else
                {
                    args[arg_index++] = token;
                }
            }

            pid_t child = fork();

            if (child == -1)
            {
                fprintf(stderr, "Failed to start file.");
                fflush(stderr);
            }
            else if (child > 0)
            {
                //In the parent
                if (args[arg_index - 1][0] != '&') {
                    waitpid(child, &last_status, 0);
                }
                else {
                    background_processes[background_process_index++] = child;

                    printf("Backgrounded Process: %d\n", child); fflush(stdout);

                    // Redirect stdin and stdout to /dev/null for background processes
                    // dup2(null_file, 1);
                    // dup2(null_file, 0);

                    for(int i = 0; i < background_process_index; i++) {

                        pid_t result = waitpid(background_processes[i], &last_status, WNOHANG);
                        if (result == 0) {

                            printf("Process Completed: %d\n", background_processes[i]); fflush(stdout);
                            for(int x = i; x < background_process_index - 1; x++) {
                                background_processes[x] = background_processes[x + 1];
                            }

                            background_processes[background_process_index - 2] = 0;
                        }
                    }
                }
            }
            else
            {
                //In the child
                if (args[arg_index - 1][0] == '&') {
                    args[--arg_index] = NULL;
                }
                // printf("Program Name: '%s'\n", program_name);

                // for(int i = 0; i < arg_index; i++)
                //     printf("Arg: '%s'\n", args[i]);

                int result = execvp(program_name, args);
                printf("Command ran: %d\n", result);
            }
        }
    }

    free(command);
    free(tokenizer_buffer);

    return 0;
}

void prompt_and_read(char *buffer)
{

    printf("%c ", prompt_string);
    fflush(stdout);

    fgets(buffer, 2048, stdin);

    char *newpos = strchr(buffer, '\n');
    *newpos = '\0';
}
