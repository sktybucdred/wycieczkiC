#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define str 51
#define mst 5
typedef struct miasto
{
    char nazwa[str + 1];
    struct miasto *nastepne;
} MIASTO;
typedef MIASTO *ADRESMIASTA;
typedef struct wycieczka
{
    char nazwa[str + 1];
    float cena;
    int liczba_dni;
    int liczba_miast;
    ADRESMIASTA pierwsze;
    struct wycieczka *nast;
} WYCIECZKA;
typedef WYCIECZKA *ADRES;
ADRES OdczytPliku(const char *nazwa)
{
    FILE *plik;
    plik = fopen(nazwa, "r");
    if (plik == NULL)
    {
        printf("Nie mozna otworzyc pliku '%s'\n", nazwa);
        return NULL;
    }
    ADRES pierwszy = NULL, ostatni;
    char nazwa1[str + 1];
    float cena1;
    int liczba_dni1, liczba_miast1;
    char nazwa_miasta[str + 1];
    int i;
    while (fscanf(plik, "%s %f %d %d ", nazwa1, &cena1, &liczba_dni1, &liczba_miast1) == 4)
    {
        ADRES nowy = (ADRES)malloc(sizeof(WYCIECZKA));
        strcpy(nowy->nazwa, nazwa1);
        nowy->cena = cena1;
        nowy->liczba_dni = liczba_dni1;
        nowy->liczba_miast = liczba_miast1;
        nowy->nast = NULL;
        nowy->pierwsze = NULL;
        ADRESMIASTA ostatnie_miasto = NULL;
        for (i = 0; i < liczba_miast1; i++)
        {
            fscanf(plik, "%s", nazwa_miasta);
            ADRESMIASTA nowe_miasto = (ADRESMIASTA)malloc(sizeof(MIASTO));
            strcpy(nowe_miasto->nazwa, nazwa_miasta);
            nowe_miasto->nastepne = NULL;
            if (nowy->pierwsze == NULL)
            {
                nowy->pierwsze = nowe_miasto;
                ostatnie_miasto = nowe_miasto;
            }
            else
            {
                ostatnie_miasto->nastepne = nowe_miasto;
                ostatnie_miasto = nowe_miasto;
            }
        }
        if (pierwszy == NULL)
        {
            pierwszy = nowy;
            ostatni = nowy;
        }
        else
        {
            ostatni->nast = nowy;
            ostatni = nowy;
        }
    }
    fclose(plik);
    return pierwszy;
}
void wypisanie(ADRES pierwszy)
{
    ADRES pom = pierwszy;
    while (pom != NULL)
    {
        printf("Nazwa: %s, Cena: %.2f, Ilosc dni: %d, Ilosc Miast: %d, Miasta:", pom->nazwa, pom->cena, pom->liczba_dni, pom->liczba_miast);
        ADRESMIASTA miasto = pom->pierwsze;
        while (miasto != NULL)
        {
            printf(" %s", miasto->nazwa);
            miasto = miasto->nastepne;
        }
        printf("\n");
        pom = pom->nast;
    }
}
void najczesciej(ADRES pierwszy)
{
    ADRES pom = pierwszy;
    int i = 0;
    int liczbawycieczek = 0;
    while (pom != NULL)
    {
        liczbawycieczek++;
        pom = pom->nast;
    }
    char **tab = malloc(liczbawycieczek * 5 * sizeof(char*));
    int *tab2 = malloc(liczbawycieczek * 5 * sizeof(int));
    pom = pierwszy;
    while (pom != NULL)
    {
        ADRESMIASTA miasto = pom->pierwsze;
        while (miasto != NULL)
        {
            tab[i] = miasto->nazwa;
            tab2[i] = 0;
            miasto = miasto->nastepne;
            i++;
        }
        pom = pom->nast;
    }
    int j, k, max = 0;
    for (j = 0; j < i; j++)
    {
        for (k = 0; k < i; k++)
        {
            if (strcmp(tab[j], tab[k]) == 0)
            {
                tab2[k]++;
                if (tab2[k] > max)
                {
                    max = tab2[k];
                }
                break;
            }
        }
    }
    printf("Najczesciej wystepujace miasta: \n");
    for (j = 0; j < i; j++)
    {
        if (tab2[j] == max)
        {
            printf("%s \n", tab[j]);
        }
    }

    free(tab);
    free(tab2);
}
void wypisznazwy(ADRES pierwszy)
{
    ADRES pom = pierwszy;
    int liczbawycieczek = 0;
    float suma = 0, sredniawycieczek;
    while (pom != NULL)
    {
        liczbawycieczek++;
        suma += pom->cena;
        pom = pom->nast;
    }
    sredniawycieczek = suma / liczbawycieczek;
    pom = pierwszy;
    while (pom != NULL)
    {
        if (pom->cena / pom->liczba_dni < sredniawycieczek / 5)
        {
            printf("%s \n", pom->nazwa);
        }
        pom = pom->nast;
    }
}
int main()
{
    ADRES pierwszy = NULL;
    pierwszy = OdczytPliku("wycieczki.txt");
    wypisanie(pierwszy);
    printf("\n");
    najczesciej(pierwszy);
    printf("\n");
    wypisznazwy(pierwszy);
    return 0;
}