#include "main.h"

void search_for_ops(char curr_ch, char next_ch, int *found, char *op);
void add_token_op_to_list(char *token_buf, list_t **tokens_h,
			  list_t **ops_h, char *op, int *buf_index, int *started, int *found);
void add_token_to_list(char curr_ch, char *token_buf, list_t **tokens_h,
		       int *buf_index, int *started);

/**
 * parse_logical_ops_r - tokenize string by && and ||
 *
 * @s: pointer to string to tokenize.
 *
 * Return: pointer to tokenized string.
*/

cmd_ops *parse_logical_ops(char *s)
{
	int op_found = 0, token_started = 0, buffer_index = 0;
	int i = 0, tokens_list_len = 0, ops_list_len = 0;
	char op_str[3] = {0};
	char token_buffer[1024] = {0};
	list_t *tokens_head = NULL;
	list_t *ops_head = NULL;
	char **ptr_to_cmd_tokens = NULL;
	char **ptr_to_ops_tokens = NULL;
	cmd_ops *ptr_to_cmd_and_ops = NULL;

	while (s[i] != '\0')
	{
		/* Search for logical operators in the string. */
		search_for_ops(s[i], s[i + 1], &op_found, op_str);

		if ((op_found && !token_started) || (op_found && s[i + 2] == '\0'))
		{
			/* If an operator is found at an unexpected position, */
			/* free linked-list and return NULL. */
			if (tokens_head)
				free_list(tokens_head);
			if (ops_head)
				free_list(ops_head);

			return (NULL);
		}

		else if (op_found && token_started && s[i + 2] != '\0')
		{
			/* If an operator is found, add the earlier token and */
			/* operator to the linked-list. */
			add_token_op_to_list(token_buffer, &tokens_head, &ops_head,
					     op_str, &buffer_index, &token_started, &op_found);
			i += 2;
		}

		else if (token_started && !op_found && s[i + 1] == '\0')
		{
			add_token_to_list(s[i], token_buffer, &tokens_head,
					  &buffer_index, &token_started);
			i++;
		}

		else if (token_started && !op_found && s[i + 1] != '\0')
		{
			token_buffer[buffer_index] = s[i];
			buffer_index++;
			i++;
		}

		else
		{
			token_started = 1;
			token_buffer[buffer_index] = s[i];
			buffer_index++;
			i++;
		}
	}

	/* Memory allocation. */
	ptr_to_cmd_and_ops = malloc(sizeof(cmd_ops));

	tokens_list_len = list_len(tokens_head);
	ops_list_len = list_len(ops_head);

	ptr_to_cmd_tokens = malloc(sizeof(char *) * (tokens_list_len + 1));
	ptr_to_ops_tokens = malloc(sizeof(char *) * (ops_list_len + 1));
	ptr_to_cmd_and_ops->cmd_tokens = store_str_ptrs(tokens_head,
							ptr_to_cmd_tokens);
	ptr_to_cmd_and_ops->ops_tokens = store_str_ptrs(ops_head, ptr_to_ops_tokens);

	free_list(tokens_head);
	free_list(ops_head);

	return (ptr_to_cmd_and_ops);
}

/**
 * search_for_ops - Finds and stores logical operators in a string.
 *
 * @curr_ch: current character been analyzed.
 * @next_ch: next character in the string.
 * @found: operator found flag.
 * @op: array to store the found operator.
*/

void search_for_ops(char curr_ch, char next_ch, int *found, char *op)
{
	/* Check for the logical operator '&&'. */
	if (curr_ch == '&' && next_ch == '&')
	{
		*found = 1;
		_strcpy(op, "&&");
	}
	/* Check for the logical operator '||'. */
	else if (curr_ch == '|' && next_ch == '|')
	{
		*found = 1;
		_strcpy(op, "||");
	}
}

/**
 * add_token_and_op_to_list - Add a token and and an operator to their
 * respective linked-list.
 *
 * @token_buf: a buffer containing the token.
 * @tokens_h: pointer to the head of the linked list storing tokens.
 * @ops_h: pointer to the head of the linked-list storing operators.
 * @op: operator to be added to the 'ops_h' linked list.
 * @buf_index: pointer to the index used for token buffer.
 * @started: token started flag.
 * @found: operator found flag.
*/

void add_token_op_to_list(char *token_buf, list_t **tokens_h, list_t **ops_h,
			  char *op, int *buf_index, int *started, int *found)
{
	/* Terminate the token buffer with a null-terminator. */
	token_buf[*buf_index] = '\0';

	/*Add the token to the end of the 'tokens_h' linked-list. */
	add_node_end(tokens_h, token_buf);

	/* Add the operator 'op' to the end of the 'ops_h' linked list. */
	add_node_end(ops_h, op);

	/* Reset the 'started' and 'found' pointers to 0. */
	*started = 0;
	*found = 0;

	/* Reset the buffer index 'buf_index' to 0. */
	*buf_index = 0;
}

/**
 * add_token_to_list - Add a token and to their respective linked list.
 *
 * @curr_ch: current character being analyzed.
 * @token_buf: buffer containing the parsed token.
 * @tokens_h: pointer to the head of the linked list storing tokens.
 * @buf_index: pointer to the index used for token buffer.
 * @started: token started flag
*/

void add_token_to_list(char curr_ch, char *token_buf, list_t **tokens_h,
		       int *buf_index, int *started)
{
	/* Append the current character to the token buffer. */
	token_buf[*buf_index] = curr_ch;

	/* Increment the buffer index. */
	(*buf_index)++;

	token_buf[*buf_index] = '\0';

	/* Add th token to the end of the 'tokens_h' linked list. */
	add_node_end(tokens_h, token_buf);

	/* Reset the 'started' pointer to 0. */
	*started = 0;

	/* Reset the buffer index 'buf_index' to 0. */
	*buf_index = 0;
}

/**
 * parse_semicolon - tokenize string by ';'
 *
 * @s: pointer to string to tokenize.
 * @head: pointer to linked list.
 *
 * Return: pointer to tokenized string.
*/

char **parse_semicolon(char *s, list_t *head)
{

	if (s == NULL)
		return (NULL);

	if (is_semicolon_prefix(s) || is_semicolon_repeated(s))
		return (NULL);

	return (str_into_tokens(s, ';', head));
}
