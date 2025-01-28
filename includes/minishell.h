/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:02:40 by kmoundir          #+#    #+#             */
/*   Updated: 2025/01/28 12:41:17 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libraries/libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

/* Forward declarations */
typedef struct s_token	t_token;

/* Signal handling */
void					handle_sigint(int sig);
void					handle_sigquit(int sig);

/* String utils */
char					*str_join_char(char *str, char c);
char					*str_join_free(char *s1, char *s2);
int						str_is_empty(char *str);
void					str_free_array(char **array);

/* Error utils */
void					*error_malloc(void);
void					print_error(char *msg);

/* Memory utils */
void					*safe_malloc(size_t size);
void					safe_free(void *ptr);
void					safe_free_array(char **array);

/* Global variables */
extern int				g_exit_status;

#endif