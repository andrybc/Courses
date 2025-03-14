#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Constants for maximum lengths
#define MAX_IDENTIFIER_LENGTH 11
#define MAX_NUMBER_LENGTH 5
#define MAX_BUFFER_SIZE 1024
#define MAX_SYMBOL_TABLE_SIZE 500
#define MAX_CODE_LENGTH 500

// Enumeration for token types
typedef enum
{
    oddsym = 1, // change skipsym to oddsym
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

typedef struct
{
    char *word;
    token_type type;
} ReservedWord;

ReservedWord reserved_words[] = {
    {"const", constsym}, {"var", varsym}, {"procedure", procsym}, {"call", callsym}, {"begin", beginsym}, {"end", endsym}, {"if", ifsym}, {"fi", fisym}, {"then", thensym}, {"else", elsesym}, {"while", whilesym}, {"do", dosym}, {"read", readsym}, {"write", writesym}, {"odd", oddsym}};

// Structure to hold a token
typedef struct
{
    token_type type;
    char value[MAX_IDENTIFIER_LENGTH + 1]; // For identifiers and numbers
    char error_message[MAX_BUFFER_SIZE];   // For error messages
} Token;

typedef struct
{
    int kind;                             // const = 1, var = 2, proc = 3
    char name[MAX_IDENTIFIER_LENGTH + 1]; // name up to 11 chars
    int val;                              // number (ASCII value) for constants
    int level;                            // L level
    int addr;                             // M address
    int mark;                             // to indicate unavailable or deleted
} symbol;

typedef struct
{
    int op; // Operation code
    int l;  // Lexicographical level
    int m;  // Modifier
} Instruction;

Instruction code[MAX_CODE_LENGTH];
int code_index = 0;

// Global buffer for source code and position tracking
char source_code[MAX_BUFFER_SIZE];
int current_position = 0;

// List to store tokens
Token tokens[MAX_BUFFER_SIZE];
int token_count = 0;

// Global string to store the token list
char token_list[MAX_BUFFER_SIZE * 2] = {0};

symbol symbol_table[MAX_SYMBOL_TABLE_SIZE];
int symbol_count = 0;
int current_token_index = 0;
int current_level = 0; // Track the current lexical level

// Opcode strings for printing
const char *opcode_strings[] = {
    "NOP", // 0 is not used
    "LIT", // 1
    "OPR", // 2
    "LOD", // 3
    "STO", // 4
    "CAL", // 5
    "INC", // 6
    "JMP", // 7
    "JPC", // 8
    "SYS"  // 9
};

// Function declarations
bool program();
bool block();
bool statement();
bool condition();
bool expression();
bool term();
bool factor();
bool const_declaration();
bool var_declaration();
bool procedure_declaration();
void errorMess(int errorCode, const char *message);
void errorMessWithToken(int errorCode, const char *message, const char *token);

// Function to read source code from a file
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

// Function to initialize the lexer state
void initialize_lexer()
{
    current_position = 0;
    token_count = 0;
    memset(tokens, 0, sizeof(tokens)); // Clear the token list
}

// Function to get the next character and advance the position
char get_next_character()
{
    if (source_code[current_position] == '\0')
    {
        return '\0'; // End of source code
    }
    return source_code[current_position++];
}

// Function to peek at the next character without advancing the position
char peek_next_character()
{
    if (source_code[current_position] == '\0')
    {
        return '\0'; // End of source code
    }
    return source_code[current_position];
}

// Function to skip comments, handling improperly enclosed comments
void skip_comment()
{
    if (source_code[current_position] == '*' && source_code[current_position + 1] == '/')
    {
        current_position += 2; // Advance to the next character
    }
    else
    {
        while (source_code[current_position] != '\0')
        {
            if (source_code[current_position] == '*' && source_code[current_position + 1] == '/')
            {
                current_position += 2; // Move past the end of the comment
                return;
            }
            current_position++;
        }
    }
}

// Function to check if the character is whitespace
bool is_whitespace(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r';
}

// Function to skip whitespace characters
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
    return identsym; // Return identsym if it's not a reserved word
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
            tokens[token_count].error_message[0] = '\0'; // No error message
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
                current_position++; // Skip the rest of the identifier
            }
            add_token(identsym, identifier, "Error: name too long");
            errorMess(2, "identifier name too long");
            return;
        }
    }

    identifier[length] = '\0'; // Null-terminate the identifier

    // Check if the identifier is a reserved word
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
                current_position++; // Skip the rest of the number
            }
            add_token(error, number, "Error: number too long");
            errorMess(401, "number too long");
            return;
        }
    }

    add_token(numbersym, number, NULL);
}

void process_special_symbol()
{
    char ch = source_code[current_position++];
    char token_value[2] = {ch, '\0'}; // Single character symbols

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
            errorMessWithToken(403, "invalid character", token_value);
        }
        break;
    default:
        add_token(error, token_value, "Error: invalid character");
        errorMessWithToken(403, "invalid character", token_value);
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
            current_position += 2; // Move past the start of the comment
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
    case oddsym:
        return "oddsym";
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

void advance_token()
{
    if (current_token_index < token_count)
    {
        current_token_index++;
    }
}

Token *get_current_token()
{
    if (current_token_index < token_count)
    {
        return &tokens[current_token_index];
    }
    return NULL;
}

void errorMess(int errorCode, const char *message)
{
    printf("Error  %d: %s\n", errorCode, message);
    exit(EXIT_FAILURE);
}

void errorMessWithToken(int errorCode, const char *message, const char *token)
{
    printf("Error  %d: %s %s\n", errorCode, message, token);
    exit(EXIT_FAILURE);
}

void add_symbol(int kind, const char *name, int val, int level, int addr)
{
    if (symbol_count < MAX_SYMBOL_TABLE_SIZE)
    {
        for (int i = 0; i < symbol_count; i++)
        {
            if (strcmp(symbol_table[i].name, name) == 0 && symbol_table[i].level == level && symbol_table[i].mark == 0)
            {
                errorMess(408, "symbol name has already been declared");
            }
        }
        symbol_table[symbol_count].kind = kind;
        strncpy(symbol_table[symbol_count].name, name, MAX_IDENTIFIER_LENGTH);
        symbol_table[symbol_count].name[MAX_IDENTIFIER_LENGTH] = '\0'; // Ensure null-termination
        symbol_table[symbol_count].val = val;
        symbol_table[symbol_count].level = level;
        symbol_table[symbol_count].addr = addr;
        symbol_table[symbol_count].mark = 0;

        symbol_count++;
    }
    else
    {
        errorMess(3, "Symbol table overflow");
    }
}

int find_symbol(const char *name, int level)
{
    for (int i = symbol_count - 1; i >= 0; i--)
    {
        if (strcmp(symbol_table[i].name, name) == 0 && symbol_table[i].level <= level && symbol_table[i].mark == 0)
        {
            return i;
        }
    }
    return -1;
}

void emit_instruction(int op, int l, int m)
{
    if (code_index >= MAX_CODE_LENGTH)
    {
        errorMess(500, "Code size exceeds maximum length");
    }
    else
    {
        code[code_index].op = op;
        code[code_index].l = l;
        if (op == 7 || op == 8) // JMP, JPC
        {
            if (m != 0)
            {
                code[code_index].m = m * 3 + 10; // Multiply by 3 and apply memory offset
                printf("old memory : %d vs new memory: %d\n", m, m * 3 + 10);
            }
        }
        else if (op == 5) // CAL
        {
            code[code_index].m = m; // Apply memory offset
        }
        else
        {
            code[code_index].m = m;
        }
        code_index++;
    }
}

bool term()
{
    if (!factor())
    {
        return false;
    }
    while (get_current_token()->type == multsym || get_current_token()->type == slashsym)
    {
        if (get_current_token()->type == multsym)
        {
            advance_token();
            if (!factor())
            {
                return false;
            }
            emit_instruction(2, 0, 3); // MUL instruction
        }
        else
        {
            advance_token();
            if (!factor())
            {
                return false;
            }
            emit_instruction(2, 0, 4); // DIV instruction
        }
    }
    return true;
}

bool expression()
{
    Token *current_token = get_current_token();
    if (current_token->type == minussym)
    {
        advance_token();
        if (!term())
        {
            return false;
        }
        // emit_instruction(2, 0, 1); // NEG instruction
        while (get_current_token()->type == plussym || get_current_token()->type == minussym)
        {
            if (get_current_token()->type == plussym)
            {
                advance_token();
                if (!term())
                {
                    return false;
                }
                emit_instruction(2, 0, 1); // ADD instruction
            }
            else
            {
                advance_token();
                if (!term())
                {
                    return false;
                }
                emit_instruction(2, 0, 2); // SUB instruction
            }
        }
    }
    else
    {
        if (!term())
        {
            return false;
        }
        while (get_current_token()->type == plussym || get_current_token()->type == minussym)
        {
            if (get_current_token()->type == plussym)
            {
                advance_token();
                if (!term())
                {
                    return false;
                }
                emit_instruction(2, 0, 1); // ADD instruction
            }
            else
            {
                advance_token();
                if (!term())
                {
                    return false;
                }
                emit_instruction(2, 0, 2); // SUB instruction
            }
        }
    }
    return true;
}

bool factor()
{
    Token *current_token = get_current_token();
    if (current_token->type == identsym)
    {
        int sym_idx = find_symbol(current_token->value, current_level);
        if (sym_idx == -1)
        {
            errorMessWithToken(415, "undeclared identifier", current_token->value);
            return false;
        }
        if (symbol_table[sym_idx].kind == 1)
        {                                                      // const
            emit_instruction(1, 0, symbol_table[sym_idx].val); // LIT 0 value
        }
        else if (symbol_table[sym_idx].kind == 2)
        {                                                           // var
            emit_instruction(3, 0, symbol_table[sym_idx].addr - 1); // LOD 0 addr
        }
        else
        {
            errorMess(429, "Expression cannot contain a procedure identifier");
            return false;
        }
        advance_token();
    }
    else if (current_token->type == numbersym)
    {
        emit_instruction(1, 0, atoi(current_token->value)); // LIT 0 value
        advance_token();
    }
    else if (current_token->type == lparentsym)
    {
        advance_token();
        if (!expression())
        {
            return false;
        }
        if (get_current_token()->type != rparentsym)
        {
            errorMess(427, "right parenthesis must follow left parenthesis");
            return false;
        }
        advance_token();
    }
    else
    {
        errorMess(428, "arithmetic equations must contain operands, parentheses, numbers, or symbols");
        return false;
    }
    return true;
}

bool const_declaration()
{
    Token *current_token = get_current_token();
    if (current_token->type == constsym)
    {
        do
        {
            advance_token();
            current_token = get_current_token();
            if (current_token->type != identsym)
            {
                errorMess(405, "const keyword must be followed by identifier");
                return false;
            }
            char name[MAX_IDENTIFIER_LENGTH + 1];
            strcpy(name, current_token->value);

            advance_token();
            current_token = get_current_token();
            if (current_token->type != eqsym)
            {
                errorMess(406, "constants must be assigned with =");
                return false;
            }

            advance_token();
            current_token = get_current_token();
            if (current_token->type != numbersym)
            {
                errorMess(407, "constants must be assigned an integer value");
                return false;
            }
            int value = atoi(current_token->value);

            add_symbol(1, name, value, current_level, 0);

            advance_token();
            current_token = get_current_token();
        } while (current_token->type == commasym);

        if (current_token->type != semicolonsym)
        {
            errorMess(409, "constant declarations must be followed by a semicolon");
            return false;
        }

        advance_token();
    }
    return true;
}

bool var_declaration()
{
    Token *current_token = get_current_token();
    if (current_token->type == varsym)
    {
        do
        {
            advance_token();
            current_token = get_current_token();
            if (current_token->type != identsym)
            {
                errorMess(410, "var keyword must be followed by identifier");
                return false;
            }
            char name[MAX_IDENTIFIER_LENGTH + 1];
            strcpy(name, current_token->value);

            add_symbol(2, name, 0, current_level, symbol_count + 3);

            advance_token();
            current_token = get_current_token();
        } while (current_token->type == commasym);

        if (current_token->type != semicolonsym)
        {
            errorMess(411, "variable declarations must be followed by a semicolon");
            return false;
        }

        advance_token();
    }
    return true;
}
bool procedure_declaration()
{
    Token *current_token = get_current_token();
    while (current_token->type == procsym)
    {
        advance_token();
        current_token = get_current_token();
        if (current_token->type != identsym)
        {
            errorMess(412, "procedure keyword must be followed by identifier");
            return false;
        }
        char name[MAX_IDENTIFIER_LENGTH + 1];
        strcpy(name, current_token->value);

        add_symbol(3, name, 0, current_level, code_index);

        advance_token();
        current_token = get_current_token();
        if (current_token->type != semicolonsym)
        {
            errorMess(413, "semicolon missing after procedure declaration");
            return false;
        }

        advance_token();
        current_level++; // Increment level for procedure block

        int tx0 = symbol_count - 1; // Index of the current procedure in symbol table
        int cx0 = code_index;       // Current code index

        emit_instruction(7, 0, 0); // Placeholder JMP instruction

        if (!block())
        {
            return false;
        }

        code[symbol_table[tx0].addr].m = code_index * 3 + 10; // Fix the JMP instruction

        emit_instruction(2, 0, 0); // OPR 0 0 (RTN instruction for returning from the procedure)
        current_level--;           // Decrement level after procedure block

        if (get_current_token()->type != semicolonsym)
        {
            errorMess(414, "semicolon expected after procedure block");
            return false;
        }
        advance_token();

        current_token = get_current_token();
    }
    return true;
}

bool condition()
{
    Token *current_token = get_current_token();
    if (current_token->type == oddsym)
    {
        advance_token();
        if (!expression())
        {
            return false;
        }
        emit_instruction(2, 0, 11); // OPR 0 11 for ODD
    }
    else
    {
        if (!expression())
        {
            return false;
        }
        current_token = get_current_token();
        if (current_token->type == eqsym)
        {
            advance_token();
            if (!expression())
            {
                return false;
            }
            emit_instruction(2, 0, 5); // EQL instruction
        }
        else if (current_token->type == neqsym)
        {
            advance_token();
            if (!expression())
            {
                return false;
            }
            emit_instruction(2, 0, 6); // NEQ instruction
        }
        else if (current_token->type == lessym)
        {
            advance_token();
            if (!expression())
            {
                return false;
            }
            emit_instruction(2, 0, 7); // LSS instruction
        }
        else if (current_token->type == leqsym)
        {
            advance_token();
            if (!expression())
            {
                return false;
            }
            emit_instruction(2, 0, 8); // LEQ instruction
        }
        else if (current_token->type == gtrsym)
        {
            advance_token();
            if (!expression())
            {
                return false;
            }
            emit_instruction(2, 0, 9); // GTR instruction
        }
        else if (current_token->type == geqsym)
        {
            advance_token();
            if (!expression())
            {
                return false;
            }
            emit_instruction(2, 0, 10); // GEQ instruction
        }
        else
        {
            errorMess(426, "condition must contain comparison operator");
            return false;
        }
    }
    return true;
}

bool statement()
{
    Token *current_token = get_current_token();
    if (!current_token)
    {
        printf("Unexpected end of input in statement");
        return false;
    }

    if (current_token->type == identsym)
    {
        int sym_idx = find_symbol(current_token->value, current_level);
        if (sym_idx == -1)
        {
            errorMessWithToken(415, "undeclared identifier", current_token->value);
            return false;
        }
        if (symbol_table[sym_idx].kind == 1 || symbol_table[sym_idx].kind == 3)
        {
            errorMess(430, "assignment to constant or procedure is not allowed");
            return false;
        }
        if (symbol_table[sym_idx].kind != 2)
        {
            errorMess(416, "only variable values may be altered");
            return false;
        }
        advance_token();
        current_token = get_current_token();

        if (!current_token || current_token->type != becomessym)
        {
            errorMess(417, "assignment statements must use :=");
            return false;
        }
        advance_token();
        if (!expression())
        {
            return false;
        }
        emit_instruction(4, current_level - symbol_table[sym_idx].level, symbol_table[sym_idx].addr - 1); // STO l, m
    }
    else if (current_token->type == callsym)
    {
        advance_token();
        current_token = get_current_token();
        if (!current_token || current_token->type != identsym)
        {
            errorMess(423, "call must be followed by an identifier (procedure name)");
            return false;
        }
        int sym_idx = find_symbol(current_token->value, current_level);
        if (sym_idx == -1)
        {
            errorMessWithToken(415, "undeclared identifier", current_token->value);
            return false;
        }
        if (symbol_table[sym_idx].kind != 3)
        { // Not a procedure
            errorMess(503, "call of a constant or variable is meaningless");
            return false;
        }
        emit_instruction(5, current_level - symbol_table[sym_idx].level, symbol_table[sym_idx].addr * 3 + 10); // CAL L M
        advance_token();
    }

    else if (current_token->type == beginsym)
    {

        do
        {
            advance_token();
            if (!statement())
            {
                return false;
            }
            current_token = get_current_token();
            if (!current_token)
            {
                errorMess(506, "Unexpected end of input in begin-end block");
            }
        } while (current_token->type == semicolonsym);

        if (current_token->type == endsym)
        {
            advance_token();
        }
        else
        {
            errorMess(418, "begin must be followed by end");
            return false;
        }
    }

    else if (current_token->type == ifsym)
    {
        advance_token();
        if (!condition())
        {
            return false;
        }
        int jpc_idx = code_index;
        emit_instruction(8, 0, 0); // JPC 0 M
        current_token = get_current_token();

        if (!current_token || current_token->type != thensym)
        {
            errorMess(419, "if must be followed by then");
            return false;
        }
        advance_token();
        if (!statement())
        {
            return false;
        }
        code[jpc_idx].m = code_index * 3 + 10; // Fix JPC instruction (adjust for offset and multiplication)
        current_token = get_current_token();

        if (!current_token || current_token->type != fisym)
        {
            errorMess(420, "if statement must be closed with fi");
            return false;
        }
        advance_token();
    }
    else if (current_token->type == whilesym)
    {
        int loop_idx = code_index;
        advance_token();
        if (!condition())
        {
            return false;
        }
        int jpc_idx = code_index;
        emit_instruction(8, 0, 0); // JPC 0 M
        current_token = get_current_token();

        if (!current_token || current_token->type != dosym)
        {
            errorMess(421, "while must be followed by do");
            return false;
        }
        advance_token();
        if (!statement())
        {
            return false;
        }
        emit_instruction(7, 0, loop_idx);      // JMP 0 loop_idx (adjust for offset and multiplication)
        code[jpc_idx].m = code_index * 3 + 10; // Fix JPC instruction (adjust for offset and multiplication)
    }
    else if (current_token->type == readsym)
    {
        advance_token();
        current_token = get_current_token();

        if (!current_token || current_token->type != identsym)
        {
            errorMess(422, "read must be followed by identifier");
            return false;
        }
        int sym_idx = find_symbol(current_token->value, current_level);
        if (sym_idx == -1)
        {
            errorMessWithToken(415, "undeclared identifier", current_token->value);
            return false;
        }
        if (symbol_table[sym_idx].kind != 2)
        {
            errorMess(416, "only variable values may be altered");
            return false;
        }
        emit_instruction(9, 0, 2);                                                                        // SYS 0 2
        emit_instruction(4, current_level - symbol_table[sym_idx].level, symbol_table[sym_idx].addr - 1); // STO l, m
        advance_token();
    }
    else if (current_token->type == writesym)
    {
        advance_token();
        current_token = get_current_token();

        if (!expression())
        {
            printf("not expression\n");
            return false;
        }
        emit_instruction(9, 0, 1); // SYS 0 1
    }
    else
    {
        // printf("landed in no valid statement found\n");
    }
    return true;
}

bool block()
{
    int prev_sym_count = symbol_count;
    int tx0 = symbol_count; // Store the current symbol count
    int cx0 = code_index;   // Store the current code index

    if (!const_declaration())
    {
        return false;
    }
    if (!var_declaration())
    {
        return false;
    }
    if (!procedure_declaration())
    {
        return false;
    }

    emit_instruction(6, 0, symbol_count - prev_sym_count + 3); // INC 0 M (Allocate space for variables)

    if (!statement())
    {
        return false;
    }

    code[symbol_table[tx0].addr].m = code_index * 3 + 10; // Fix the JMP instruction
    return true;
}

bool program()
{
    int jmp_index = code_index; // Save the index for the JMP instruction
    emit_instruction(7, 0, 0);  // Placeholder JMP instruction

    current_level = 0; // Start with level 0

    if (!block())
    {
        return false;
    }

    Token *current_token = get_current_token();
    if (!current_token || current_token->type != periodsym)
    {
        errorMess(4, "program must end with period");
        return false;
    }

    code[jmp_index].m = code_index / 3; // Set JMP to point to the start of the main block
    emit_instruction(9, 0, 3);          // SYS 0 3 (HALT instruction for the VM)
    return true;
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

void print_token_list()
{
    char token_entry[50]; // Temporary buffer for each token entry

    printf("Token List:\n");
    for (int i = 0; i < token_count; i++)
    {
        if (tokens[i].type != error)
        { // Exclude errors from the token list
            if (tokens[i].type == identsym || tokens[i].type == numbersym)
            {
                snprintf(token_entry, sizeof(token_entry), "%d %s ", tokens[i].type, tokens[i].value);
            }
            else
            {
                snprintf(token_entry, sizeof(token_entry), "%d ", tokens[i].type);
            }
            printf("%s", token_entry);
            strcat(token_list, token_entry); // Append to the token list string
        }
    }
    printf("\n");

    // Store token list in a file
    FILE *file = fopen("token_list.txt", "w");
    if (file == NULL)
    {
        perror("Error opening file to write token list");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s", token_list);
    fclose(file);
}

void print_assembly_code()
{
    printf("Line OP L M\n");
    for (int i = 0; i < code_index; i++)
    {
        printf("%d %s %d %d\n", i, opcode_strings[code[i].op], code[i].l, code[i].m);
    }
}

void print_symbol_table()
{
    printf("Symbol Table:\n");
    printf("Kind\t|\tName\t\t|\tValue\t|\tLevel\t|\tAddress\t|\tMark\n");
    printf("------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < symbol_count; i++)
    {
        printf("   %d\t|\t\t%s\t|\t%d\t|\t%d\t|\t%d\t|\t%d\n",
               symbol_table[i].kind,
               symbol_table[i].name,
               symbol_table[i].val,
               symbol_table[i].level,
               symbol_table[i].addr,
               symbol_table[i].mark);
    }
}

void write_elf_file(const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("Error opening file to write ELF");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < code_index; i++)
    {
        fprintf(file, "%d %d %d\n", code[i].op, code[i].l, code[i].m);
    }

    fclose(file);
}

void mark_symbols()
{
    for (int i = 0; i < symbol_count; i++)
    {
        symbol_table[i].mark = 1;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "How to use: %s <input file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Initialize lexer
    initialize_lexer();

    // Read source code from file
    read_source_code(argv[1]);

    // Display the input PL/0 program
    printf("Source Program:\n%s\n\n", source_code);

    // Process the source code to tokenize it
    lexer_process();

    // Initialize parser and symbol table
    current_token_index = 0;
    symbol_count = 0;
    code_index = 0;

    // Flag to track errors
    bool hasError = false;

    // Start parsing
    if (!program())
    {
        hasError = true;
    }

    if (!hasError)
    {
        // If no errors, display success message
        printf("No errors, program is syntactically correct\n\n");

        // Display the generated assembly code
        // printf("Generated Assembly Code:\n");
        print_assembly_code();

        // Write ELF file
        write_elf_file("elf.txt");
    }

    return EXIT_SUCCESS;
}
