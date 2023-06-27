#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Forr read/write buffers sections */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Forr command chaining sections */
#define CMD_NORM	0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN	3

/* Forr transform_num() sections */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* Forr 1 if using system getline() sections */
#define USE_GET_LINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct strlist – singly_linkd_list
 * @num: Num_field
 * @str: Strng
 * @next: Points to nxt_node
 */
typedef struct strlist
{
	int num;
	char *str;
	struct strlist *next;
} list_t;

/**
 * struct passtip – Struct holds pseudo_args to pass into a func,
 * allowng unifrm prototyp for func_pointr_struct
 * @arg: Strng genrtd frm getline containn args
 * @argv: Array_of_strngs genrtd_from_arg
 * @path: Strng_path for present_cmd
 * @argc: Arg_count
 * @lne_count: Err_count
 * @err_num: exit()s err_code
 * @lnecount_wave: if on_count this lne_of_input
 * @fname: Prog_filenme
 * @env: Linked_list local_cpy of environ
 * @environ: Custm_mod_copy of environ frm LL env
 * @history: Histry_node
 * @alias: Allias_node
 * @env_changed: On if environ_mod
 * @status: return stats of the last_exectd_cmd
 * @cmd_buf: Addy of pointer to cmd_buf, on if_chainng
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: fd from which lne_input is to be read
 * @histrycount: Histry_lne_num count
 */
typedef struct passtip
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int lne_count;
	int err_num;
	int lnecount_wave;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointr to cmd ; chain buff, for mem_mgt */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histrycount;
} tip_t;

#define TIP_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin – Struct holds builtin_strng nd relatd_func
 * @type: Builtin cmd_flag
 * @func: Func
 */
typedef struct builtin
{
	char *type;
	int (*func)(tip_t *);
} builtin_table;

/* Forr toem_shloop.c sections */
int hsh(tip_t *, char **);
int _find_builtin(tip_t *);
void _find_cmd(tip_t *);
void _fork_cmd(tip_t *);

/* Forr toem_parser.c sections */
int _is_cmd(tip_t *, char *);
char *_dup_chars(char *, int, int);
char *_find_path(tip_t *, char *, char *);

/* Forr loophsh.c sections */
int loophsh(char **);

/* Forr toem_errors.c sections */
void _eputs(char *);
int _eputchar(char);
int _putfd(char d, int fd);
int _putsfd(char *str, int fd);

/* Forr toem_string.c sections */
int str_len(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *str_cat(char *, char *);

/* Forr toem_string1.c sections */
char *str_cpy(char *, char *);
char *str_dup(const char *);
void _puts(char *);
int _putchar(char);

/* Forr toem_exits.c sections */
char *strn_cpy(char *, char *, int);
char *strn_cat(char *, char *, int);
char *str_chr(char *, char);

/* Forr toem_tokenizer.c sections  */
char **stritow(char *, char *);
char **stritow2(char *, char);

/* Forr toem_re_alloc.c sections */
char *_mem_set(char *, char, unsigned int);
void _ffree(char **);
void *_re_alloc(void *, unsigned int, unsigned int);

/* Forr toem_memory.c sections */
int bbfree(void **);

/* Forr toem_atoi.c sections */
int synergic(tip_t *);
int is_separ(char, char *);
int is_alpha(int);
int _atoi(char *);

/* Forr toem_errors1.c sections */
int _erratoi(char *);
void priint_error(tip_t *, char *);
int priint_dec(int, int);
char *transform_num(long int, int, int);
void rem_comments(char *);

/* Forr toem_builtin.c sections */
int _dexit(tip_t *);
int _ourcd(tip_t *);
int _myassist(tip_t *);

/* Forr toem_builtin1.c sections */
int _ourhistry(tip_t *);
int _ourallias(tip_t *);

/*Forr toem_getline.c sections */
ssize_t _get_input(tip_t *);
int _get_line(tip_t *, char **, size_t *);
void _sigintHandler(int);

/* Forr toem_getinfo.c sections */
void clear_tip(tip_t *);
void set_tip(tip_t *, char **);
void free_tip(tip_t *, int);

/* Forr toem_environ.c sections */
char *get_env(tip_t *, const char *);
int _ourenv(tip_t *);
int our_setenv(tip_t *);
int our_unsetenv(tip_t *);
int popult_env_list(tip_t *);

/* Forr toem_getenv.c sections */
char **_get_environ_(tip_t *);
int un_setenv(tip_t *, char *);
int _set_env(tip_t *, char *, char *);

/* Forr toem_history.c sections */
char *get_histry_fl(tip_t *tip);
int write_histry(tip_t *tip);
int read_histry(tip_t *tip);
int build_histry_list(tip_t *tip, char *buf, int lnecount);
int re_num_histry(tip_t *tip);

/* Forr toem_lists.c sections */
list_t *addd_nodde(list_t **, const char *, int);
list_t *addd_nodde_endd(list_t **, const char *, int);
size_t priint_list_str(const list_t *);
int del_node_at_indx(list_t **, unsigned int);
void _free_list(list_t **);

/* Forr toem_lists1.c sections */
size_t _list_len(const list_t *);
char **_list_to_strings(list_t *);
size_t priint_list(const list_t *);
list_t *_node_starts_with(list_t *, char *, char);
ssize_t _get_node_index(list_t *, list_t *);

/* Forr toem_vars.c sections */
int _is_chain(tip_t *, char *, size_t *);
void _check_chain(tip_t *, char *, size_t *, size_t, size_t);
int _replace_alias(tip_t *);
int _replace_vars(tip_t *);
int _replace_string(char **, char *);

#endif
