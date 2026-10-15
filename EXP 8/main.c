#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUCTIONS 20
#define MAX_RULE_LENGTH 100
#define MAX_SET_SIZE 100

char production[MAX_PRODUCTIONS][MAX_RULE_LENGTH];
char first[26][MAX_SET_SIZE];
char follow[26][MAX_SET_SIZE];
int n;

int addToSet(char set[], char symbol)
{
    for (int i = 0; set[i] != '\0'; i++) {
        if (set[i] == symbol) {
            return 0;
        }
    }

    int length = strlen(set);
    if (length < MAX_SET_SIZE - 1) {
        set[length] = symbol;
        set[length + 1] = '\0';
        return 1;
    }

    return 0;
}

int isPresent(const char set[], char symbol)
{
    for (int i = 0; set[i] != '\0'; i++) {
        if (set[i] == symbol) {
            return 1;
        }
    }
    return 0;
}

/* Supports productions like A=... and A->... */
int getRhsStart(const char rule[])
{
    if (rule[1] == '-' && rule[2] == '>') {
        return 3;
    }
    return 2;
}

void findFirst(void)
{
    int changed;

    do {
        changed = 0;

        for (int p = 0; p < n; p++) {
            char lhs = production[p][0];
            char *rhs = production[p] + getRhsStart(production[p]);
            char *alternative = strtok(rhs, "|");

            while (alternative != NULL) {
                int nullable = 1;

                for (int i = 0; alternative[i] != '\0'; i++) {
                    char symbol = alternative[i];

                    if (symbol == '#') {
                        changed |= addToSet(first[lhs - 'A'], '#');
                        nullable = 0;
                        break;
                    }

                    if (!isupper((unsigned char)symbol)) {
                        changed |= addToSet(first[lhs - 'A'], symbol);
                        nullable = 0;
                        break;
                    }

                    const char *symbolFirst = first[symbol - 'A'];
                    for (int j = 0; symbolFirst[j] != '\0'; j++) {
                        if (symbolFirst[j] != '#') {
                            changed |= addToSet(first[lhs - 'A'], symbolFirst[j]);
                        }
                    }

                    if (!isPresent(symbolFirst, '#')) {
                        nullable = 0;
                        break;
                    }
                }

                if (nullable) {
                    changed |= addToSet(first[lhs - 'A'], '#');
                }

                alternative = strtok(NULL, "|");
            }
        }
    } while (changed);
}

void findFollow(void)
{
    addToSet(follow[production[0][0] - 'A'], '$');

    int changed;

    do {
        changed = 0;

        for (int p = 0; p < n; p++) {
            char lhs = production[p][0];
            char *rhs = production[p] + getRhsStart(production[p]);
            char *alternative = strtok(rhs, "|");

            while (alternative != NULL) {
                int length = strlen(alternative);

                for (int i = 0; i < length; i++) {
                    char current = alternative[i];

                    if (!isupper((unsigned char)current)) {
                        continue;
                    }

                    int suffixNullable = 1;

                    for (int j = i + 1; j < length; j++) {
                        char next = alternative[j];

                        if (next == '#') {
                            continue;
                        }

                        if (!isupper((unsigned char)next)) {
                            changed |= addToSet(follow[current - 'A'], next);
                            suffixNullable = 0;
                            break;
                        }

                        const char *nextFirst = first[next - 'A'];
                        for (int k = 0; nextFirst[k] != '\0'; k++) {
                            if (nextFirst[k] != '#') {
                                changed |= addToSet(follow[current - 'A'],
                                                    nextFirst[k]);
                            }
                        }

                        if (!isPresent(nextFirst, '#')) {
                            suffixNullable = 0;
                            break;
                        }
                    }

                    if (suffixNullable) {
                        const char *lhsFollow = follow[lhs - 'A'];
                        for (int k = 0; lhsFollow[k] != '\0'; k++) {
                            changed |= addToSet(follow[current - 'A'],
                                                lhsFollow[k]);
                        }
                    }
                }

                alternative = strtok(NULL, "|");
            }
        }
    } while (changed);
}

int isFirstOccurrence(int productionIndex)
{
    for (int i = 0; i < productionIndex; i++) {
        if (production[i][0] == production[productionIndex][0]) {
            return 0;
        }
    }
    return 1;
}

void printSets(const char *label, char sets[26][MAX_SET_SIZE])
{
    printf("\n%s:\n", label);

    for (int i = 0; i < n; i++) {
        char symbol = production[i][0];

        if (!isFirstOccurrence(i)) {
            continue;
        }

        printf("%s(%c) = { ", label, symbol);

        for (int j = 0; sets[symbol - 'A'][j] != '\0'; j++) {
            printf("%c ", sets[symbol - 'A'][j]);
        }

        printf("}\n");
    }
}

int main(void)
{
    printf("Enter number of productions: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_PRODUCTIONS) {
        printf("Enter between 1 and %d productions.\n", MAX_PRODUCTIONS);
        return 1;
    }

    printf("\nEnter productions (e.g. A=BC|a|# or A->BC|a|#):\n");

    for (int i = 0; i < n; i++) {
        if (scanf("%99s", production[i]) != 1 ||
            !isupper((unsigned char)production[i][0])) {
            printf("Invalid production. The left-hand side must be uppercase.\n");
            return 1;
        }
    }

    findFirst();
    findFollow();

    printSets("FIRST", first);
    printSets("FOLLOW", follow);

    return 0;
}