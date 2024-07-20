
/*
Andry Canel
HW1
COP3402
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Include this for strcpy

#define ARRAY_SIZE 500
#define BASE_STACK_SIZE 100

int baseP, stackP, PC;
int HALT = 0;
char OPString[4];
int basePStack[BASE_STACK_SIZE];
int basePStackTop = -1; // Initialize the top of the base pointer stack to -1

typedef struct
{ // struct to store new Instructions from the P CODE
    int OP;
    int M;
    int L;
} InstructCode;

int PAS[ARRAY_SIZE];
InstructCode IR;

void load_instructions(const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int i = PC; // start storing instructions at PC (initially 10)
    while (fscanf(file, "%d %d %d", &PAS[i], &PAS[i + 1], &PAS[i + 2]) != EOF)
    {
        i += 3; // next OP will be in this spot
    }

    fclose(file);
}

void load_instructions_from_console() // helper function to load in the input from the console instead of a file at first
{
    int op, l, m;
    int i = PC; // \start storing instructions at PC (initially 10)
    printf("Enter instructions (OP L M). Type -1 to stop.\n");

    while (1)
    {
        // printf("Instruction %d: ", (i - PC) / 3 + 1);
        scanf(" %d", &op);
        if (op == -1)
            break;
        scanf(" %d %d", &l, &m);
        PAS[i] = op;
        PAS[i + 1] = l;
        PAS[i + 2] = m;
        i += 3; // next OP will be in this spot
    }
}
void print_pas() // something to test to make sure i was loading in the input correctly
{
    for (int i = 10; i < ARRAY_SIZE && PAS[i] != 0; i += 3)
    {
        printf("Instruction at %d: OP=%d, L=%d, M=%d\n", i, PAS[i], PAS[i + 1], PAS[i + 2]);
    }
}
void printIR() // something to test to make sure i was loading in the input correctly
{
    printf("/t%s %d/t%d", OPString, IR.L, IR.M);
}

void push_baseP(int value) // helper function to store the history of basepointers into a stack
{
    if (basePStackTop < BASE_STACK_SIZE - 1)
    {
        basePStack[++basePStackTop] = value;
    }
    else
    {
        printf("Base pointer stack overflow\n");
        exit(EXIT_FAILURE);
    }
}

int pop_baseP() // helper function to store the history of basepointers into a stack
{
    if (basePStackTop >= 0)
    {
        return basePStack[basePStackTop--];
    }
    else
    {
        printf("Base pointer stack underflow\n");
        exit(EXIT_FAILURE);
    }
}

void print_stack() // function that prints out the PAS/stack in the format the guidelines wanted
{
    int tempBaseP = baseP;
    int tempStackP = stackP;
    printf("  %s %d %d\t%d\t%d\t%d\t", OPString, IR.L, IR.M, PC, baseP, stackP);
    for (int i = ARRAY_SIZE - 1; i >= stackP; i--)
    {
        for (int j = 0; j <= basePStackTop; j++)
        {
            if (i == basePStack[j] && i != 499)
            {
                printf("| ");
                break;
            }
        }
        printf("%d ", PAS[i]);
    }
    printf("\n");
}

// helper function that helped me keep track of the base Pointer
void printBasePstack()
{
    printf("Base Pointer stack [");
    for (int i = 0; i < 10; i++)
    {

        printf(" %d, ", basePStack[i]);
    }
    printf("]");
}

int base(int BP, int L)
{
    int arb = BP; // arb = activation record base
    while (L > 0) // find base L levels down
    {
        arb = PAS[arb];
        L--;
    }
    return arb;
}

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        fprintf(stderr, "How to use: %s <input file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    // intitialize the P MACHINE
    baseP = 499;
    stackP = 500;
    PC = 10;
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        PAS[i] = 0; // Initializing instruction memory
    }

    // load instructions into PAS
    load_instructions(argv[1]);
    //  load_instructions_from_console();
    // print_pas();
    printf("\t\tPC\tBP\tSP\tstack\n");
    printf("Initial values:\t%d\t%d\t%d\n", PC, baseP, stackP);
    printf("\n");
    while (!HALT)
    {

        IR.OP = PAS[PC];
        IR.L = PAS[PC + 1];
        IR.M = PAS[PC + 2];
        PC += 3;

        // find out which OP is being executed  and manipulate the stack based on the OPcode....printStack does not implement any of the instructions...just there to print the stack
        switch (IR.OP)
        {
        case 1: // LIT 0, M
            stackP--;
            PAS[stackP] = IR.M;
            strcpy(OPString, "LIT");
            print_stack();
            break;
        case 2: // OPR 0, M
            switch (IR.M)
            {
            case 0: // RTN
                stackP = baseP + 1;
                baseP = PAS[stackP - 2];
                PC = PAS[stackP - 3];
                strcpy(OPString, "RTN");
                print_stack();

                break;
            case 1: // ADD
                PAS[stackP + 1] += PAS[stackP];
                stackP++;
                strcpy(OPString, "ADD");
                print_stack();
                break;
            case 2: // SUB
                PAS[stackP + 1] -= PAS[stackP];
                stackP++;
                strcpy(OPString, "SUB");
                print_stack();
                break;
            case 3: // MUL
                PAS[stackP + 1] *= PAS[stackP];
                stackP++;
                strcpy(OPString, "MUL");
                print_stack();
                break;
            case 4: // DIV
                PAS[stackP + 1] /= PAS[stackP];
                stackP++;
                strcpy(OPString, "DIV");
                print_stack();
                break;
            case 5: // EQL
                PAS[stackP + 1] = PAS[stackP + 1] == PAS[stackP];
                stackP++;
                strcpy(OPString, "EQL");
                print_stack();
                break;
            case 6: // NEQ
                PAS[stackP + 1] = PAS[stackP + 1] != PAS[stackP];
                stackP++;
                strcpy(OPString, "NEQ");
                print_stack();
                break;
            case 7: // LSS
                PAS[stackP + 1] = PAS[stackP + 1] < PAS[stackP];
                stackP++;
                strcpy(OPString, "LSS");
                print_stack();
                break;
            case 8: // LEQ
                PAS[stackP + 1] = PAS[stackP + 1] <= PAS[stackP];
                stackP++;
                strcpy(OPString, "LEQ");
                print_stack();
                break;
            case 9: // GTR
                PAS[stackP + 1] = PAS[stackP + 1] > PAS[stackP];
                stackP++;
                strcpy(OPString, "GTR");
                print_stack();
                break;
            case 10: // GEQ
                PAS[stackP + 1] = PAS[stackP + 1] >= PAS[stackP];
                stackP++;
                strcpy(OPString, "GEQ");
                print_stack();
                break;

                // Other operations
            }
            break;
        case 3: // LOD L, M
            stackP--;
            PAS[stackP] = PAS[base(baseP, IR.L) - IR.M];
            strcpy(OPString, "LOD");
            print_stack();
            break;
        case 4: // STO L, M
            PAS[base(baseP, IR.L) - IR.M] = PAS[stackP];
            stackP++;
            strcpy(OPString, "STO");
            print_stack();
            break;
        case 5:
            // CAL L, M
            PAS[stackP - 1] = base(baseP, IR.L); // Static Link (SL)
            PAS[stackP - 2] = baseP;             // Dynamic Link (DL)
            PAS[stackP - 3] = PC;                // Return Address (RA)
            baseP = stackP - 1;
            PC = IR.M;
            strcpy(OPString, "CAL");
            print_stack();
            break;
        case 6: // INC 0, M
                // printf("here");
            push_baseP(baseP); // just puts the base pointer to stack that keeps track when to print '|'

            stackP -= IR.M;
            strcpy(OPString, "INC");
            print_stack();
            break;

        case 7: // JMP 0, M
            PC = IR.M;
            strcpy(OPString, "JMP");
            print_stack();
            break;
        case 8: // JPC 0, M
            if (PAS[stackP] == 0)
                PC = IR.M;
            stackP++;
            strcpy(OPString, "JPC");
            print_stack();
            break;
        case 9: // SYS 0, M
            switch (IR.M)
            {
            case 1: // write the top stack element to the screen
                printf("Output result is : %d\n", PAS[stackP]);
                stackP++;
                break;
            case 2: // read an input from the user and store it on top of the stack
                stackP--;
                printf("Please enter an integer: ");
                scanf("%d", &PAS[stackP]);
                break;
            case 3: // end  program
                HALT = 1;
                break;
            }
            strcpy(OPString, "SYS");
            print_stack();
            break;
        }

        // printf("\n");
        // printBasePstack();
        //  printf("\n\n");
    }

    return 0;
}
