#include<stdio.h>
#include<string.h>
#include<ctype.h>

int n;
char prod[10000][10000];

void addc(char c, char result[]){
    int i = 0;

    for(i = 0; result[i] != '\0'; i++){
        if(result[i] == c)
            return;
    }

    result[i] = c;
    result[i+1] = '\0';
}

void FIRST(char c, char result[]){

    if(!isupper((unsigned char)c)){
        addc(c,result);
        return;
    }

    for(int i = 0; i < n; i++){

        if(prod[i][0] == c){

            int j = 2;

            if(prod[i][j] == '#'){
                addc('#',result);
                continue;
            }

            while(prod[i][j] != '\0'){

                char temp[10000] = "";

                FIRST(prod[i][j],temp);

                int epsi = 0;

                for(int k = 0; temp[k] != '\0'; k++){

                    if(temp[k] == '#')
                        epsi = 1;
                    else
                        addc(temp[k],result);
                }

                if(!epsi)
                    break;

                j++;
            }
        }
    }
}

void FOLLOW(char c, char result[]){

    if(c == prod[0][0])
        addc('$',result);

    for(int i = 0; i < n; i++){

        for(int j = 2; prod[i][j] != '\0'; j++){

            if(prod[i][j] == c){

                int k = j + 1;
                int epsilon = 1;

                while(prod[i][k] != '\0' && epsilon){

                    char temp[10000] = "";

                    FIRST(prod[i][k],temp);

                    epsilon = 0;

                    for(int p = 0; temp[p] != '\0'; p++){

                        if(temp[p] == '#')
                            epsilon = 1;
                        else
                            addc(temp[p],result);
                    }

                    k++;
                }

                if(epsilon && prod[i][0] != c){

                    char tempw[10000] = "";

                    FOLLOW(prod[i][0],tempw);

                    for(int p = 0; tempw[p] != '\0'; p++)
                        addc(tempw[p],result);
                }
            }
        }
    }
}

int main(){

    char temp[10000];
    char upper[10000] = "";

    printf("Enter the number of production rules: ");
    scanf("%d",&n);

    printf("Enter the production rules:\n");

    for(int i = 0; i < n; i++)
        scanf("%s",prod[i]);


    for(int i = 0; i < n; i++){

        for(int j = 0; prod[i][j] != '\0'; j++){

            if(j == 1)
                continue;

            if(prod[i][j] != '#')
                addc(prod[i][j],upper);
        }
    }

    // FIRST sets
    printf("\nFIRST SETS:\n");

    for(int i = 0; upper[i] != '\0'; i++){

        temp[0] = '\0';

        FIRST(upper[i],temp);

        printf("FIRST(%c) = { ",upper[i]);

        for(int j = 0; temp[j] != '\0'; j++)
            printf("%c ",temp[j]);

        printf("}\n");
    }

    upper[0] = '\0';

    for(int i = 0; i < n; i++)
        addc(prod[i][0],upper);

    printf("\nFOLLOW SETS:\n");

    for(int i = 0; upper[i] != '\0'; i++){

        temp[0] = '\0';

        FOLLOW(upper[i],temp);

        printf("FOLLOW(%c) = { ",upper[i]);

        for(int j = 0; temp[j] != '\0'; j++)
            printf("%c ",temp[j]);

        printf("}\n");
    }

    return 0;
}
