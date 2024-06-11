#include "systemcalls.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * @param cmd the command to execute with system()
 * @return true if the command in @param cmd was executed
 *   successfully using the system() call, false if an error occurred,
 *   either in invocation of the system() call, or if a non-zero return
 *   value was returned by the command issued in @param cmd.
*/
bool do_system(const char *cmd)
{
    int ret = system(cmd);
    if (ret == -1 || ret != 0)
    {
        return false;
    }
    return true;
}

/**
* @param count -The numbers of variables passed to the function. The variables are command to execute.
*   followed by arguments to pass to the command
*   Since exec() does not perform path expansion, the command to execute needs
*   to be an absolute path.
* @param ... - A list of 1 or more arguments after the @param count argument.
*   The first is always the full path to the command to execute with execv()
*   The remaining arguments are a list of arguments to pass to the command in execv()
* @return true if the command @param ... with arguments @param arguments were executed successfully
*   using the execv() call, false if an error occurred, either in invocation of the
*   fork, waitpid, or execv() command, or if a non-zero return value was returned
*   by the command issued in @param arguments with the specified arguments.
*/

bool do_exec(int count, ...)
{
    va_list args;
    va_start(args, count);
    char *command[count + 1];
    for (int i = 0; i < count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;
    va_end(args);

    pid_t pid = fork();
    if (pid == -1)
    {
        // Fork failed
        return false;
    }
    else if (pid == 0)
    {
        // Child process
        execv(command[0], command);
        // If execv returns, it must have failed
        exit(EXIT_FAILURE);
    }
    else
    {
        // Parent process
        int status;
        if (waitpid(pid, &status, 0) == -1)
        {
            // waitpid failed
            return false;
        }
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
        {
            // Child exited normally with status 0
            return true;
        }
        else
        {
            // Child exited with an error
            return false;
        }
    }
}
