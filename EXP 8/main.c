
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

char production[MAX][MAX];
char first[26][MAX];
char follow[26][MAX];
int n;

void addToSet(char set[], char symbol)
{
    int i;

    for (i = 0; set[i] != '\0'; i++)
    {
        if (set[i] == symbol)
            return;
    }

    set[i] = symbol;
    set[i + 1] = '\0';
}

int isPresent(char set[], char symbol)
{
    int i;

    for (i = 0; set[i] != '\0'; i++)
    {
        if (set[i] == symbol)
            return 1;
    }

    return 0;
}

int findFirst(char symbol)
{
    int i, j, changed = 0;
    char rhs[MAX];

    if (!isupper((unsigned char)symbol))
    {
        if (symbol == '#')
            return 0;

        addToSet(first[symbol - 'A'], symbol);
        return 0;
    }

    for (i = 0; i < n; i++)
    {
        if (production[i][0] != symbol)
            continue;

        strcpy(rhs, production[i] + 3);

        char *part = strtok(rhs, "|");

        while (part != NULL)
        {
            int epsilon = 1;

            for (j = 0; part[j] != '\0'; j++)
            {
                char current = part[j];

                if (current == '#')
                {
                    addToSet(first[symbol - 'A'], '#');
                    break;
                }

                if (!isupper((unsigned char)current))
                {
                    addToSet(first[symbol - 'A'], current);
                    epsilon = 0;
                    break;
                }

                findFirst(current);

                for (int k = 0;
                     first[current - 'A'][k] != '\0'; k++)
                {
                    char ch = first[current - 'A'][k];

                    if (ch != '#')
                        addToSet(first[symbol - 'A'], ch);
                }

                if (!isPresent(first[current - 'A'], '#'))
                {
                    epsilon = 0;
                    break;
                }
            }

            if (epsilon)
                addToSet(first[symbol - 'A'], '#');

            part = strtok(NULL, "|");
        }
    }

    return changed;
}

void findFollow(char symbol)
{
    int i, j, k;
    char rhs[MAX];

    for (i = 0; i < n; i++)
    {
        strcpy(rhs, production[i] + 2);

        char *part = strtok(rhs, "|");

        while (part != NULL)
        {
            for (j = 0; part[j] != '\0'; j++)
            {
                if (part[j] != symbol)
                    continue;

                if (part[j + 1] != '\0')
                {
                    char next = part[j + 1];

                    if (!isupper((unsigned char)next))
                    {
                        if (next != '#')
                            addToSet(follow[symbol - 'A'], next);
                    }
                    else
                    {
                        int epsilon = 1;

                        for (k = j + 1; part[k] != '\0'; k++)
                        {
                            char current = part[k];

                            if (!isupper((unsigned char)current))
                            {
                                if (current != '#')
                                    addToSet(
                                        follow[symbol - 'A'], current);

                                epsilon = 0;
                                break;
                            }

                            for (int x = 0;
                                 first[current - 'A'][x] != '\0'; x++)
                            {
                                char ch = first[current - 'A'][x];

                                if (ch != '#')
                                    addToSet(
                                        follow[symbol - 'A'], ch);
                            }

                            if (!isPresent(first[current - 'A'], '#'))
                            {
                                epsilon = 0;
                                break;
                            }
                        }

                        if (epsilon && production[i][0] != symbol)
                        {
                            for (k = 0;
                                 follow[production[i][0] - 'A'][k] != '\0';
                                 k++)
                            {
                                addToSet(
                                    follow[symbol - 'A'],
                                    follow[production[i][0] - 'A'][k]);
                            }
                        }
                    }
                }
                else if (production[i][0] != symbol)
                {
                    for (k = 0;
                         follow[production[i][0] - 'A'][k] != '\0';
                         k++)
                    {
                        addToSet(
                            follow[symbol - 'A'],
                            follow[production[i][0] - 'A'][k]);
                    }
                }
            }

            part = strtok(NULL, "|");
        }
    }
}

int main()
{
    int i, j, changed;

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (example: E->TR|#):\n");

    for (i = 0; i < n; i++)
        scanf("%19s", production[i]);

    for (i = 0; i < n; i++)
        findFirst(production[i][0]);

    /* Repeat FOLLOW calculation until sets stop changing */
    addToSet(follow[production[0][0] - 'A'], '$');

    do
    {
        changed = 0;

        for (i = 0; i < n; i++)
        {
            char lhs = production[i][0];
            char rhs[MAX];

            strcpy(rhs, production[i] + 2);
            char *part = strtok(rhs, "|");

            while (part != NULL)
            {
                for (j = 0; part[j] != '\0'; j++)
                {
                    if (isupper((unsigned char)part[j]))
                    {
                        char before[MAX];
                        strcpy(before, follow[part[j] - 'A']);

                        findFollow(part[j]);

                        if (strcmp(before, follow[part[j] - 'A']) != 0)
                            changed = 1;
                    }
                }

                part = strtok(NULL, "|");
            }

            (void)lhs;
        }
    } while (changed);

    printf("\nFIRST sets:\n");

    for (i = 0; i < 26; i++)
    {
        if (first[i][0] != '\0')
            printf("FIRST(%c) = { %s }\n", 'A' + i, first[i]);
    }

    printf("\nFOLLOW sets:\n");

    for (i = 0; i < 26; i++)
    {
        if (follow[i][0] != '\0')
            printf("FOLLOW(%c) = { %s }\n", 'A' + i, follow[i]);
    }

    return 0;
}
