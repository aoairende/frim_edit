#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <stdarg.h>
#include <signal.h>

/**
 * struct list_s - singly linked list
 * @str: string - (malloc'ed string)
 * @len: length of the string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct list_s
{
	char *str;
	unsigned int len;
	struct list_s *next;
} list_t;

/**
 * struct tokenize_cmd_ops - commands and logical ops tokens
 * @cmd_tokens: commands tokens
 * @ops_tokens: logical ops tokens
 */
typedef struct tokenize_cmd_ops
{
	char **cmd_tokens;
	char **ops_tokens;
} cmd_ops;

extern char **argvalues;
extern char **environ;
extern char *line;
int str_contains_log_operator(char *s);
void trunc_comment(char *s);
size_t print_list(const list_t *h);
size_t list_len(const list_t *h);
void _puts(char *s);
list_t *add_node(list_t **head, const char *str);
void newputs(char *s);
list_t *add_node_end(list_t **head, const char *str);
void free_list(list_t *head);
void free_linked_list_and_strings(list_t *head, char **s);
char *_getenv(const char *name);
list_t *path_list();
void print_dirs_in_path(void);
char **str_into_tokens(const char *s, char delim, list_t *head);
int is_key_same(char *s, const char *substr);
char *get_value(char *s);
unsigned int key_len(char *s);
int path_exist(const char *s);
int is_just_spaces(char *s);
int contains_forward_slash_at_end(char *s);
int contains_forward_slash(char *s);
char *check_builtin_cm_path(char *arg, char **dirs, list_t *head);
int _strlen(const char *s);
char *_strdup(const char *str);
char *_strcpy(char *dest, const char *src);
int _unsetenv(const char *name);
int _atoi(char *s);
void free_cmd_ops(cmd_ops *cm_struct);
int is_just_digits(char *s);
int _setenv(const char *name, const char *value, int overwrite);
char *_strncpy(char *dest, char *src, int n);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, char *src, int n);
int _strcmp(char *s1, char *s2);
void handle_signal(int signum);
int print_character(char c);
int built_in(char *s, char **builtin);
int str_count(char **s);
char *itostr(int n);
int num_of_digits(unsigned int num);
int calculate_power(int base, int exp);
char **store_str_ptrs(const list_t *h, char **ptrs_to_str);
void process_dollar_sign(char **s, int status);
void create_child_pid(int *status, char **arg);
void print_nonpath_error(char **arg, int *status);
void execute_builtin_cmd(char **argv, int *status,
			 list_t *head_argv, FILE *stream, char ***tokens);
void exec_cd_cmd(int argv_count, char **argv, int *status);
void handle_exit(int argv_count, char **argv,
		 list_t *head_argv, FILE *stream, char ***tokens);
void process_setenv(int argv_count, char **argv, int *status);
void process_unsetenv(int argv_count, char **argv, int *status);
void prompt_user(void);
void _free(char *s);
void free_resources(list_t *head_argv, char **arg, FILE *stream);
cmd_ops *parse_logical_ops(char *s);
int is_semicolon_prefix(char *s);
int is_semicolon_repeated(char *s);
char **parse_semicolon(char *s, list_t *head);
void handle_err(char *str_1, char *str_2, int *status);
void set_old_new_pwd(char *old_dir, char *new_dir, int *status);
void free_all(char **argv, list_t *head_argv, FILE *stream,
	      char ***tokens, int exit_code);
void handle_usage_err(char *str, int *status);
void custom_print(int fd, const char *const format, ...);
void free_strings(char **s);
int count_args(char **args);
void fetch_stream_line(char **line, FILE **stream, size_t *len, ssize_t *bytes);
void process_line_with_ops(char ***tokens, FILE *stream,
                        int *statusint, char *shell_name);
void handle_syntax_error(char *s, int *status);
void handle_parsed_cmd(char ***tokens, char *s, FILE *stream, int *status);
void execute_cmds_with_ops(cmd_ops *ptr_to_cmd_ops, FILE *stream, int *status);
char **argvalues;

#endif
