#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Constants for maximum lengths
#define MAX_IDENTIFIER_LENGTH 11
#define MAX_NUMBER_LENGTH 5
#define MAX_BUFFER_SIZE 1024

// Enumeration for token types
typedef enum
{
    skipsym = 1,
    identsym,
    numbersym,
    plussym,
    minussym,
    multsym,
    slashsym,
    fisym,
    eqsym,
    neqsym,
    lessym,
    leqsym,
    gtrsym,
    geqsym,
    lparentsym,
    rparentsym,
    commasym,
    semicolonsym,
    periodsym,
    becomessym,
    beginsym,
    endsym,
    ifsym,
    thensym,
    whilesym,
    dosym,
    callsym,
    constsym,
    varsym,
    procsym,
    writesym,
    readsym,
    elsesym,
    error
} token_type;

typedef struct // identifier type for reserved words
{
    char *word;
    token_type type;
} ReservedWord;

ReservedWord reserved_words[] = {
    {"const", constsym}, {"var", varsym}, {"procedure", procsym}, {"call", callsym}, {"begin", beginsym}, {"end", endsym}, {"if", ifsym}, {"fi", fisym}, {"then", thensym}, {"else", elsesym}, {"while", whilesym}, {"do", dosym}, {"read", readsym}, {"write", writesym}};

// structure to hold a token
typedef struct
{
    token_type type;
    char value[MAX_IDENTIFIER_LENGTH + 1]; // for identifiers and numbers
    char error_message[MAX_BUFFER_SIZE];   // for error messages
} Token;

// global buffer for source code and position tracking
char source_code[MAX_BUFFER_SIZE];
int current_position = 0;

// list to store tokens
Token tokens[MAX_BUFFER_SIZE];
int token_count = 0;

// function to read source code from a file
void read_source_code(const char *file_name)
{
    FILE *file = fopen(file_name, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    size_t length = fread(source_code, sizeof(char), MAX_BUFFER_SIZE, file);
    if (length == 0 && !feof(file))
    {
        perror("Error reading file");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    source_code[length] = '\0'; // Null-terminate the source code string
    fclose(file);
}

// function to initialize the lexer state
void initialize_lexer()
{
    current_position = 0;
    token_count = 0;
    memset(tokens, 0, sizeof(tokens)); // Clear the token list
}

// function to get the next character and advance the position
char get_next_character()
{
    if (source_code[current_position] == '\0')
    {
        return '\0'; // end of source code
    }
    return source_code[current_position++];
}

// function to peek at the next character without advancing the position
char peek_next_character()
{
    if (source_code[current_position] == '\0')
    {
        return '\0';
    }
    return source_code[current_position];
}

// function to skip comments, handling improperly enclosed comments
void skip_comment()
{
    // checking if the next characters are `*` and `/`
    if (peek_next_character() == '*')
    {
        current_position++;
        while (source_code[current_position] != '\0')
        {
            // checking  for the end of comment
            if (source_code[current_position] == '*' && source_code[current_position + 1] == '/')
            {
                current_position += 2; // move past the end of the comment
                return;
            }
            current_position++;
        }
    }
}

// function to check if the character is whitespace
bool is_whitespace(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r';
}

// function to skip whitespace characters
void skip_whitespace()
{
    while (is_whitespace(peek_next_character()))
    {
        current_position++;
    }
}

token_type get_reserved_word_type(const char *identifier)
{
    for (int i = 0; i < sizeof(reserved_words) / sizeof(ReservedWord); i++)
    {
        if (strcmp(reserved_words[i].word, identifier) == 0)
        {
            return reserved_words[i].type;
        }
    }
    return identsym; // return identsym if it's not a reserved word
}

void add_token(token_type type, const char *value, const char *error_message)
{
    if (token_count < MAX_BUFFER_SIZE)
    {
        tokens[token_count].type = type;
        strncpy(tokens[token_count].value, value, MAX_IDENTIFIER_LENGTH);
        tokens[token_count].value[MAX_IDENTIFIER_LENGTH] = '\0';

        if (error_message)
        {
            strncpy(tokens[token_count].error_message, error_message, MAX_BUFFER_SIZE - 1);
            tokens[token_count].error_message[MAX_BUFFER_SIZE - 1] = '\0';
        }
        else
        {
            tokens[token_count].error_message[0] = '\0'; // no error message
        }

        token_count++;
    }
    else
    {
        printf("Error: Token buffer overflow\n");
        exit(EXIT_FAILURE);
    }
}

bool is_letter(char ch)
{
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

bool is_digit(char ch)
{
    return ch >= '0' && ch <= '9';
}

void process_identifier()
{
    char identifier[MAX_IDENTIFIER_LENGTH + 1] = {0};
    int length = 0;

    while (is_letter(source_code[current_position]) || is_digit(source_code[current_position]))
    {
        if (length < MAX_IDENTIFIER_LENGTH)
        {
            identifier[length++] = source_code[current_position++];
        }
        else
        {
            while (is_letter(source_code[current_position]) || is_digit(source_code[current_position]))
            {
                current_position++; // skipping the rest of the identifier
            }
            add_token(identsym, identifier, "Error: name too long");
            return;
        }
    }

    identifier[length] = '\0'; // Null-terminate the identifier

    // checking if the identifier is a reserved word
    token_type type = get_reserved_word_type(identifier);
    add_token(type, identifier, NULL);
}

void process_number()
{
    char number[MAX_NUMBER_LENGTH + 1] = {0};
    int length = 0;

    while (is_digit(source_code[current_position]))
    {
        if (length < MAX_NUMBER_LENGTH)
        {
            number[length++] = source_code[current_position++];
        }
        else
        {
            while (is_digit(source_code[current_position]))
            {
                current_position++; // skip the rest of the number
            }
            add_token(numbersym, number, "Error: number too long");
            return;
        }
    }

    add_token(numbersym, number, NULL);
}

void process_special_symbol()
{
    char ch = source_code[current_position++];
    char token_value[2] = {ch, '\0'}; // single character symbols

    switch (ch)
    {
    case '+':
        add_token(plussym, token_value, NULL);
        break;
    case '-':
        add_token(minussym, token_value, NULL);
        break;
    case '*':
        add_token(multsym, token_value, NULL);
        break;
    case '/':
        add_token(slashsym, token_value, NULL);
        break;
    case '(':
        add_token(lparentsym, token_value, NULL);
        break;
    case ')':
        add_token(rparentsym, token_value, NULL);
        break;
    case '=':
        add_token(eqsym, token_value, NULL);
        break;
    case '<':
        if (source_code[current_position] == '>')
        {
            current_position++;
            add_token(neqsym, "<>", NULL);
        }
        else if (source_code[current_position] == '=')
        {
            current_position++;
            add_token(leqsym, "<=", NULL);
        }
        else
        {
            add_token(lessym, token_value, NULL);
        }
        break;
    case '>':
        if (source_code[current_position] == '=')
        {
            current_position++;
            add_token(geqsym, ">=", NULL);
        }
        else
        {
            add_token(gtrsym, token_value, NULL);
        }
        break;
    case ',':
        add_token(commasym, token_value, NULL);
        break;
    case ';':
        add_token(semicolonsym, token_value, NULL);
        break;
    case '.':
        add_token(periodsym, token_value, NULL);
        break;
    case ':':
        if (source_code[current_position] == '=')
        {
            current_position++;
            add_token(becomessym, ":=", NULL);
        }
        else
        {
            add_token(error, token_value, "Error: invalid character");
        }
        break;
    default:
        add_token(error, token_value, "Error: invalid character");
    }
}

void process_token()
{
    char ch = peek_next_character();
    if (is_letter(ch))
    {
        process_identifier();
    }
    else if (is_digit(ch))
    {
        process_number();
    }
    else
    {
        process_special_symbol();
    }
}

void lexer_process()
{
    while (source_code[current_position] != '\0')
    {
        if (is_whitespace(peek_next_character()))
        {
            skip_whitespace();
        }
        else if (source_code[current_position] == '/' && source_code[current_position + 1] == '*')
        {
            current_position += 2; // move past the start of the comment
            skip_comment();
        }
        else if (is_letter(peek_next_character()))
        {
            process_identifier();
        }
        else if (is_digit(peek_next_character()))
        {
            process_number();
        }
        else
        {
            process_special_symbol();
        }
    }
}

const char *get_token_type_string(token_type type)
{
    switch (type)
    {
    case skipsym:
        return "skipsym";
    case identsym:
        return "identsym";
    case numbersym:
        return "numbersym";
    case plussym:
        return "plussym";
    case minussym:
        return "minussym";
    case multsym:
        return "multsym";
    case slashsym:
        return "slashsym";
    case fisym:
        return "fisym";
    case eqsym:
        return "eqsym";
    case neqsym:
        return "neqsym";
    case lessym:
        return "lessym";
    case leqsym:
        return "leqsym";
    case gtrsym:
        return "gtrsym";
    case geqsym:
        return "geqsym";
    case lparentsym:
        return "lparentsym";
    case rparentsym:
        return "rparentsym";
    case commasym:
        return "commasym";
    case semicolonsym:
        return "semicolonsym";
    case periodsym:
        return "periodsym";
    case becomessym:
        return "becomessym";
    case beginsym:
        return "beginsym";
    case endsym:
        return "endsym";
    case ifsym:
        return "ifsym";
    case thensym:
        return "thensym";
    case whilesym:
        return "whilesym";
    case dosym:
        return "dosym";
    case callsym:
        return "callsym";
    case constsym:
        return "constsym";
    case varsym:
        return "varsym";
    case procsym:
        return "procsym";
    case writesym:
        return "writesym";
    case readsym:
        return "readsym";
    case elsesym:
        return "elsesym";
    default:
        return "unknown";
    }
}

void print_tokens()
{
    for (int i = 0; i < token_count; i++)
    {
        printf("Token Type: %d, Value: %s\n", tokens[i].type, tokens[i].value);
    }
}
void print_token_list()
{
    printf("Token List:\n");
    for (int i = 0; i < token_count; i++)
    {
        if (tokens[i].type == identsym || tokens[i].type == numbersym)
        {
            printf("%d %s ", tokens[i].type, tokens[i].value);
        }
        else
        {
            printf("%d ", tokens[i].type);
        }
    }
    printf("\n");
}

void print_lexeme_table()
{
    printf("Lexeme Table:\n");
    printf("lexeme  token type\n");
    for (int i = 0; i < token_count; i++)
    {
        if (tokens[i].error_message[0] != '\0')
        {
            printf("%-15s\t\t%s\n", tokens[i].value, tokens[i].error_message);
        }
        else
        {
            printf("%-15s\t\t%-15d\n", tokens[i].value, tokens[i].type);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "How to use: %s <input file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // initialize lexer
    initialize_lexer();

    // read source code from file
    read_source_code(argv[1]);

    // process the source code to tokenize it
    lexer_process();

    printf("Source Program:\n%s\n\n", source_code);

    print_lexeme_table();

    print_token_list();
    return EXIT_SUCCESS;
}
