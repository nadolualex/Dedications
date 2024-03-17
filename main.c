#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include <inttypes.h>
#include <stdbool.h>
int add_last(void **arr, int *len, data_structure *data)
{
    (*arr) = realloc(*arr,((*len)+1)*32); //realocam len+1 * (head + tip) memorie deoarece o dedicatie e 
    //formata din head si tip
    if(arr == NULL) {
        perror("eroare");
        return -1;
    }
    if(data->header->type == 1) {

        memmove(*arr+(*len)*32, data->header, 8); //plusam cu (*len)*32 pentru a adauga pe pozitia respectiva a vectorului exact 8 biti cat are headerul
        tip1 *tip = (tip1* )(data->data);
        memmove(*arr+(*len)*32 + 8, tip, 24);// plusam cu (*len)*32 + 8 pentru a trece la type-ul vectorului exact 24 biti cat are type-ul
    }
        else
            if(data->header->type == 2) {

                memmove(*arr+(*len)*32, data->header, 8);
                tip2 *tip = (tip2*)(data->data);
                memmove(*arr+(*len)*32 + 8, tip, 24);
            }
                else //nu stiu daca e nevoie de cele 3 cazuri, intrucat am observat ca testele trec si daca am doar o instructiune din if, fara cele 3 if-uri
                    if(data->header->type == 3) {

                        memmove(*arr+(*len)*32, data->header, 8);
                        tip3 *tip = (tip3*)(data->data);
                        memmove(*arr+(*len)*32 + 8, tip, 24);
                    }
        (*len)++;

    return 0;
}

void find(void *data_block, int len, int index)
{
    void *token = data_block;
    for(int i = 0; i < len; i++, token+=32) {
        head *aux = (head*)token;

        if(!aux)
            return;

        if(i == index) { //for the memes
            printf("Tipul ");
            printf("%hhd\n",aux->type); //din nou, nu stiu daca mai era necesar sa fac 3 cazuri deoarece testele dadeau si pe cazul general
            //indiferent de ce tip introduceam
             if(aux->type == 1) {
                tip1 *tip = (tip1*)(8 + data_block + (i * aux->len));
                printf("%s pentru %s\n",tip->cel_care_dedica,tip->celui_care_dedica);
                printf("%hhd\n",tip->prima);
                printf("%hhd\n",tip->doua);
                printf("\n");

            }
            else
                if(aux->type == 2) {
                    tip2 *tip = (tip2*)(8 + data_block + (i * aux->len));
                    printf("%s pentru %s\n",tip->cel_care_dedica,tip->celui_care_dedica);
                    printf("%hd\n",tip->prima);
                    printf("%d\n",tip->doua);
                    printf("\n");
                }
                else
                    if(aux->type == 3) {
                        tip3 *tip = (tip3*)(8 + data_block + (i * aux->len));
                        printf("%s pentru %s\n",tip->cel_care_dedica,tip->celui_care_dedica);
                        printf("%d\n",tip->prima);
                        printf("%d\n",tip->doua);
                        printf("\n");
                    }

        }
    }


}

void citire(data_structure *dedicatie) {
    scanf("%hhd",&dedicatie->header->type);
            if(dedicatie->header->type == 1) {
                tip1 *tip;
                tip = malloc(24); //aloc memorie sizeof(tip1) adica 24
                tip->cel_care_dedica = calloc(1,256);
                tip->celui_care_dedica = calloc(1,256);
               scanf("%s %hhd %hhd %s",tip->cel_care_dedica,&tip->prima,&tip->doua,tip->celui_care_dedica);
                dedicatie->header->len = 32; //actualizez marimea dedicatiei
                dedicatie->data = tip; //mut tipul in data

            } else
                if(dedicatie->header->type == 2) {
                    tip2 *tip;
                    tip = malloc(24);
                    tip->cel_care_dedica = calloc(1,256);
                    tip->celui_care_dedica = calloc(1,256);
                    scanf("%s %hd %d %s",tip->cel_care_dedica,&tip->prima,&tip->doua,tip->celui_care_dedica);

                    dedicatie->header->len = 32;
                    dedicatie->data = tip;

                }
                else
                    if(dedicatie->header->type == 3) {
                        tip3 *tip;
                        tip = malloc(24);
                        tip->cel_care_dedica = calloc(1,256);
                        tip->celui_care_dedica = calloc(1,256);
                        scanf("%s %d %d %s",tip->cel_care_dedica,&tip->prima,&tip->doua,tip->celui_care_dedica);
                        dedicatie->header->len = 32;
                        dedicatie->data = tip;

                    }
}
void print (void *arr, int len) //am modificat functia sa fie mai scurta odata cu implementarea find-ului
{
    for(int i = 0; i < len; i ++)
        find(arr, len, i);
}


int delete_at(void **arr, int *len, int index)
{
    int a = index * 32;
    int b = (index + 1) * 32;
    int c = (*len - index ) * 32;
    (*len)--;
    int d = (*len) * 32;
    memmove(*arr + a , *arr + b,c);
    //pur si simplu mutam fiecare element cu o pozitie la stanga

    (*arr) = realloc(*arr, d);
    //realocam memoria
    return 1;
}

int add_at(void **arr, int *len, data_structure *data, int index)
{
    if(index < 0){
        perror("eroare");
        return -1;
    }
    else
        if(index > *len)
            index = *len;

    int a = index * 32; //a = dedicatie de pe pozitia i
    int b = (index + 1) * 32; // b = dedicatia de pe pozitia i+1
    int c = (*len - index ) * 32;// c = numarul de dedicatii mutate
    (*len) ++;
    int d = (*len) * 32;
    (*arr) = realloc(*arr,d);

    memmove(*arr + b , *arr + a, c); //aici mutam elementele cu o pozitie la dreapta
    memmove(*arr + a, data->header, sizeof(head)); //mutam elementele din header si dupa aia pe cele din data
    memmove(*arr + a + sizeof(head*), data->data, 24); //am incercat mai intai sa le mut pe toate odata dar nu a mers si am ales sa
    //le mut pe rand

    return 1;
}

int main() {
    // the vector of bytes u have to work with
    // good luck :)
    void *arr = NULL;
    int n,n2,n3;
    int len = 0;
    char *s;
    s = malloc(256);
    arr = calloc(1,len);
    data_structure *dedicatie = malloc(sizeof(data_structure));
    dedicatie->header = malloc(8);
    data_structure *dedicatie2 = malloc(sizeof(data_structure));
    dedicatie2->header = malloc(8);
    while(scanf("%s",s)){
        if(strcmp(s,"insert") == 0){
                    citire(dedicatie);
                    add_last(&arr,&len,dedicatie);
                }
                else
                    if(strcmp(s,"print") == 0){
                        print(arr,len);
                    }
                    else
                        if(strcmp(s,"find") == 0){
                            scanf("%d",&n);
                            find(arr,len,n);
                        }
                        else
                            if(strcmp(s,"delete_at") == 0){
                                scanf("%d",&n2); //citire index
                                delete_at(&arr,&len,n2);
                            }
                                else
                                    if(strcmp(s,"insert_at") == 0){
                                        scanf("%d",&n3);
                                        citire(dedicatie);
                                        add_at(&arr,&len,dedicatie,n3);
                                    }
                                        if(strcmp(s,"exit") == 0){
                                            free(s);
                                            free(dedicatie->header);
                                            free(dedicatie);
                                            free(arr);
                                            break;
                                        }
            }

    return 0;
}
