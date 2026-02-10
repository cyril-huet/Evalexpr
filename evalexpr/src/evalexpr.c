#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct output
{
    int valeur;
    int num;
    char typeoperation;
    struct output *next;
};
struct resultat
{
    int valeur;
    struct resultat *next;
};
struct stack
{
    char typeoperation;
    struct stack *next;
};

static void freeresultat(struct resultat *resultat2)
{
    while (resultat2)
    {
        struct resultat *temp = resultat2;
        resultat2 = resultat2->next;
        free(temp);
    }
}

static void freestack(struct stack *stack2)
{
    while (stack2)
    {
        struct stack *temp = stack2;
        stack2 = stack2->next;
        free(temp);
    }
}

static void freeoutput(struct output *output2)
{
    while (output2)
    {
        struct output *temp = output2;
        output2 = output2->next;
        free(temp);
    }
}
static struct resultat *pushresultat(struct resultat *resultat2, int valeur2)
{
    struct resultat *res = malloc(sizeof(struct resultat));
    if (res == NULL)
    {
        return NULL;
    }
    res->valeur = valeur2;
    res->next = resultat2;
    return res;
}

static struct resultat *popresultat(struct resultat *resultat2, int *valeur2)
{
    if (resultat2 == NULL)
    {
        return NULL;
    }
    *valeur2 = resultat2->valeur;
    struct resultat *res = resultat2->next;
    free(resultat2);
    return res;
}

static struct stack *pushstack(struct stack *stack2, char typeoperation2)
{
    struct stack *res = malloc(sizeof(struct stack));
    if (res == NULL)
    {
        freestack(stack2);
        return NULL;
    }
    res->typeoperation = typeoperation2;
    res->next = stack2;
    return res;
}

static struct stack *popstack(struct stack *stack2, char *typeoperation2)
{
    if (stack2 == NULL)
    {
        return NULL;
    }
    *typeoperation2 = stack2->typeoperation;
    struct stack *res = stack2->next;
    free(stack2);
    return res;
}

/*static struct output *popoutput(struct output *output2, struct output **res)
{
    if (output2 == NULL)
    {
        return NULL;
    }
    *res = output2;
    return output2->next;
}*/

static struct output *pushoutputnb(struct output *output2, int num2)
{
    struct output *res = malloc(sizeof(struct output));
    if (res == NULL)
    {
        return NULL;
    }
    res->valeur = num2;
    res->num = 1;
    res->typeoperation = 0;
    res->next = output2;
    return res;
}

static struct output *pushoutputoperator(struct output *output2, char operator2)
{
    struct output *res = malloc(sizeof(struct output));
    if (res == NULL)
    {
        return NULL;
    }
    res->valeur = 0;
    res->num = 0;
    res->typeoperation = operator2;
    res->next = output2;
    return res;
}

static int estnombre(char c)
{
    if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5'
        || c == '6' || c == '7' || c == '8' || c == '9')
    {
        return 1;
    }
    return 0;
}
/*static int my_atoi(const char *str)
{
    int res = 0;
    int index = 0;

    while (str[index] != '\0')
    {
        if (str[index] >= '0' && str[index] <= '9')
        {
            res = res * 10 + str[index] - '0';
        }
        index++;
    }
    int index2 = 0;
    while (str[index2] != '\0' && str[index2] == ' ')
    {
        if (str[index2] == '-')
        {
            res *= -1;
        }
        index2++;
    }

    return res;
}*/
static int resultatdunombre(char *expression, int index, int fin)
{
    int res = 0;
    while (index < fin)
    {
        res = res * 10 + (expression[index] - '0');
        index++;
    }
    return res;
}
static int nombre(char *expression, int *index)
{
    int debut = *index;
    while (estnombre(expression[*index]))
    {
        (*index)++;
    }
    return resultatdunombre(expression, debut, *index);
}
static int priorite(char c)
{
    if (c == '+')
    {
        return 1;
    }
    if (c == '-')
    {
        return 1;
    }
    if (c == '*')
    {
        return 2;
    }
    if (c == '/')
    {
        return 2;
    }
    if (c == '%')
    {
        return 2;
    }
    if (c == '^')
    {
        return 3;
    }
    return 0;
}

static int lirenomb(char *expression, int *index)
{
    int signe = 1;
    while (expression[*index] == '-' || expression[*index] == '+')
    {
        if (expression[*index] == '-')
        {
            signe *= -1;
        }
        (*index)++;
    }

    return nombre(expression, index) * signe;
}
static int my_pow(int a, int b)
{
    if (b < 0)
    {
        exit(3);
    }

    if (b == 0)
    {
        return 1;
    }
    if (b % 2 == 0)
    {
        int res = my_pow(a, b / 2);
        return res * res;
    }
    return a * my_pow(a, b - 1);
}

static int operation3(char *expression, int index)
{
    return (expression[index] == '-' || expression[index] == '+')
        && (index == 0 || expression[index - 1] == '('
            || priorite(expression[index - 1]) != 0);
}

static struct output *nbr(char *expression, int *index,
                          struct output *output_shuting)
{
    if (operation3(expression, *index))
    {
        struct output *temp =
            pushoutputnb(output_shuting, lirenomb(expression, index));
        if (!temp)
        {
            freeoutput(output_shuting);
            return NULL;
        }
        output_shuting = temp;
        return output_shuting;
    }

    if (estnombre(expression[*index]))
    {
        struct output *temp =
            pushoutputnb(output_shuting, nombre(expression, index));
        if (!temp)
        {
            freeoutput(output_shuting);
            return NULL;
        }
        output_shuting = temp;
        return output_shuting;
    }

    return output_shuting;
}

static struct output *operation2(char *expression, int *index,
                                 struct stack **stack_shuting,
                                 struct output *output_shuting)
{
    char temps = expression[*index];

    while (*stack_shuting != NULL && (*stack_shuting)->typeoperation != '('
           && (priorite((*stack_shuting)->typeoperation) > priorite(temps)
               || (priorite((*stack_shuting)->typeoperation) == priorite(temps)
                   && temps != '^')))
    {
        char o2;
        *stack_shuting = popstack(*stack_shuting, &o2);
        struct output *temp = pushoutputoperator(output_shuting, o2);
        if (!temp)
        {
            freestack(*stack_shuting);
            freeoutput(output_shuting);
            return NULL;
        }
        output_shuting = temp;
    }

    *stack_shuting = pushstack(*stack_shuting, temps);
    (*index)++;
    return output_shuting;
}

static struct output *parenthese(char *expression, int *index,
                                 struct stack **stack_shuting,
                                 struct output *output_shuting)
{
    char temps = expression[*index];
    char o2;

    if (temps == '(')
    {
        *stack_shuting = pushstack(*stack_shuting, temps);
        (*index)++;
    }
    else if (temps == ')')
    {
        while (*stack_shuting && (*stack_shuting)->typeoperation != '(')
        {
            *stack_shuting = popstack(*stack_shuting, &o2);
            output_shuting = pushoutputoperator(output_shuting, o2);
        }
        if (!*stack_shuting)
        {
            freeoutput(output_shuting);
            exit(2);
        }
        *stack_shuting = popstack(*stack_shuting, &o2);
        (*index)++;
    }
    else if (temps == ',')
    {
        while (*stack_shuting && (*stack_shuting)->typeoperation != '(')
        {
            *stack_shuting = popstack(*stack_shuting, &o2);
            output_shuting = pushoutputoperator(output_shuting, o2);
        }
        (*index)++;
    }

    return output_shuting;
}

static struct output *pile(struct stack **stack_shuting,
                           struct output *output_shuting)
{
    char o2;
    while (*stack_shuting)
    {
        o2 = (*stack_shuting)->typeoperation;
        if (o2 == '(')
        {
            freeoutput(output_shuting);
            freestack(*stack_shuting);
            exit(2);
        }
        *stack_shuting = popstack(*stack_shuting, &o2);
        output_shuting = pushoutputoperator(output_shuting, o2);
    }
    return output_shuting;
}

struct output *shunting_yard(char *expression)
{
    struct stack *stack_shuting = NULL;
    struct output *output_shuting = NULL;
    int index = 0;

    while (expression[index] != '\0')
    {
        char temps = expression[index];
        if (temps == ' ')
        {
            index++;
            continue;
        }

        struct output *tmp = nbr(expression, &index, output_shuting);
        if (tmp != output_shuting)
        {
            output_shuting = tmp;
            continue;
        }

        if (priorite(temps) != 0)
        {
            output_shuting =
                operation2(expression, &index, &stack_shuting, output_shuting);
            continue;
        }

        output_shuting =
            parenthese(expression, &index, &stack_shuting, output_shuting);

        if (expression[index] != '\0' && expression[index] == temps)
        {
            freeoutput(output_shuting);
            freestack(stack_shuting);
            exit(1);
        }
    }

    output_shuting = pile(&stack_shuting, output_shuting);
    return output_shuting;
}
static int operation(int a, int b, char type)
{
    if (type == '+')
    {
        return a + b;
    }
    if (type == '-')
    {
        return a - b;
    }
    if (type == '*')
    {
        return a * b;
    }
    if (type == '/')
    {
        if (b == 0)
        {
            exit(3);
        }
        return a / b;
    }
    if (type == '^')
    {
        return my_pow(a, b);
    }
    if (type == '%')
    {
        if (b == 0)
        {
            exit(3);
        }
        return a % b;
    }
    return -1;
}

static struct output *reverse(struct output *output2)
{
    struct output *avt = NULL;
    struct output *mtn = output2;
    struct output *apr = NULL;

    while (mtn)
    {
        apr = mtn->next;
        mtn->next = avt;
        avt = mtn;
        mtn = apr;
    }
    return avt;
}

static int resultat(struct output *output2)
{
    struct resultat *resultat2 = NULL;
    struct output *parcours = reverse(output2);
    int resultatfinal = 0;
    while (parcours)
    {
        struct output *temps = parcours;
        if (parcours->num)
        {
            resultat2 = pushresultat(resultat2, parcours->valeur);
            parcours = parcours->next;
            free(temps);
            continue;
        }
        int val1;
        int val2;
        resultat2 = popresultat(resultat2, &val2);
        resultat2 = popresultat(resultat2, &val1);
        int resultat = operation(val1, val2, parcours->typeoperation);
        resultat2 = pushresultat(resultat2, resultat);
        parcours = parcours->next;
        free(temps);
    }
    resultat2 = popresultat(resultat2, &resultatfinal);
    freeresultat(resultat2);
    return resultatfinal;
}

static struct output *rpnenoutput(char *expression)
{
    struct output *output2 = NULL;
    int index = 0;
    while (expression[index])
    {
        char temps = expression[index];
        if (temps == ' ')
        {
            index++;
            continue;
        }
        if (estnombre(temps) == 1)
        {
            int nombre = 0;
            while (estnombre(expression[index]) == 1)
            {
                nombre = nombre * 10 + (expression[index] - '0');
                index++;
            }
            output2 = pushoutputnb(output2, nombre);
            index++;
            continue;
        }
        if (priorite(expression[index]) != 0)
        {
            output2 = pushoutputoperator(output2, expression[index]);
            index++;
            continue;
        }
        freeoutput(output2);
        return NULL;
    }
    return output2;
}

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        exit(4);
    }
    if (argc == 2 && strcmp(argv[1], "-rpn") != 0)
    {
        exit(4);
    }
    char buffer[1024];
    size_t index = 0;
    while (index < sizeof(buffer) - 1 && fread(&buffer[index], 1, 1, stdin) > 0)
    {
        index++;
    }
    buffer[index] = '\0';
    if (index == 0)
    {
        return 4;
    }
    if (buffer[index - 1] == '\n')
    {
        buffer[index - 1] = '\0';
    }
    if (index == 0 || buffer[0] == '\0')
    {
        return 0;
    }
    if (argc > 2)
    {
        return 4;
    }
    if (argc == 2)
    {
        if (strcmp(argv[1], "-rpn") == 0)
        {
            struct output *resultat4 = rpnenoutput(buffer);
            int resultat5 = resultat(resultat4);
            printf("%d\n", resultat5);
            //           struct output *inverse = reverse(resultat4);
            // freeoutput(inverse);
        }
        else
        {
            return 4;
        }
    }
    else
    {
        struct output *resultat2 = shunting_yard(buffer);
        int resultat3 = resultat(resultat2);
        printf("%d\n", resultat3);
        // struct output *inverse = reverse(resultat2);
        // freeoutput(inverse);
    }
    return 0;
}
