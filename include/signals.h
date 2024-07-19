#ifndef SIGNALS_H
# define SIGNALS_H

# define S_BASE     20  // Init signall
# define S_HEREDOC   21  // SIGINT
# define S_HEREDOC_END  22  //Command execution
# define S_SIGINT  23  //Heredoc
# define S_SIGINT_CMD  24  //End of a herdoc
# define S_CMD  25  //Heredoc
# define S_CANCEL_EXEC  26  //End of a herdoc
# define S_SIZE  27  //Heredoc

#endif