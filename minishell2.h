#include <sys/types.h>
#include <sys/stat.h>
#include "minishell.h"

int    exec(char *name, char **envp, char **split);