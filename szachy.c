#include <stdio.h>
#include <stdlib.h>
#define ROZMIAR 8

void ustawienie (int tab [][ROZMIAR]);
void wyswietlanie (int tab [][ROZMIAR]);
void ruch (int tab [][ROZMIAR], int *w, int *x);
int sprawdzenie_pozycji (int tab [][ROZMIAR], int *w, int *x, int c);
int warunek_konca (int tab [][ROZMIAR]);
int sprawdzenie_pionek (int tab [][ROZMIAR], int *w, int *x, int c);
int sprawdzenie_wieza (int tab [][ROZMIAR], int *w, int *x, int c);
int sprawdzenie_kon (int tab [][ROZMIAR], int *w, int *x, int c);
int sprawdzenie_goniec (int tab[][ROZMIAR], int *w, int *x, int c);
int sprawdzenie_krol (int tab[][ROZMIAR], int *w, int *x, int c);
int sprawdzenie_hetman (int tab[][ROZMIAR], int *w, int *x, int c);
int zamiana_pionek (int tab[][ROZMIAR], int c);

int main()
{
    int szachownica [ROZMIAR][ROZMIAR];
    int z, na, licznik=0, x, n, m, b; //z - pole początkowe [wiersz][kolumna]; na - pole końcowe [wiersz][kolumna]
    //licznik - ktory ruch minus 1; x - indeks wiersza pola początkowego; n - indeks kolumny pola początkowego; m - rodzaj pionka

    printf("Witam, jestem programem do gry w szachy!.\n\nAby wykonac ruch wpisz liczbe dwucyfrowa.\nCyfra dziesiatek tej liczby to wiersz, a cyfra jednosci to kolumna, z ktorych chcesz sie ruszyc.\nNastepnie zatwierdz wpisana liczbe klawiszem enter.\nKolejno wpisz analogicznie liczbe, symbolizujaca pole, na ktore chcesz sie ruszyc.\nTa liczbe rowniez zatwierdz klawiszem Enter.\nZycze milej gry!\n\n");
    printf("Aby rozpoczac gre wcisnij dowolna liczbe na klawiaturze, i zatwierdz ja klawiszem enter.\nAby zamknac gre wcisnij dowolna litere lub znak i rowniez zatwierdz Enterem.\n");

    if(scanf("%d", &b)==1)
    {
       system("cls");
       ustawienie(szachownica); //ustawienie początkowe pionków na szachownicy
       wyswietlanie(szachownica); //wyświetlenie początkowego stanu
    }
    else
        return 0;


    while (warunek_konca(szachownica)==1)
    {
        if (licznik%2 == 0)
           printf("\nRuch gracza nr 1 (biale): \n");
        else
           printf("\nRuch gracza nr 2 (czarne): \n");

        if (((scanf("%d", &z) + scanf("%d", &na))==2) && (z>10) && (na>10) && (z<89) && (na<89) && (z!=na) && (z%10<9) && (na%10<9) && (z%10>0) && (na%10>0) )  //z-pole z ktorego sie ruszamy, na-pole na ktore sie ruszamy, wpisywane jako liczba dwucyfrowa
        {                                                                                                  //pierwsza cyfra to wiersz, a druga to kolumna, wpisujemy od 1, a nie jak w macierzy od 0
            x= z/10 -1;
            n= z%10 -1;
            m= (szachownica[x][n])%10;  //sprawdza na podstawie wag, jaka figura jest na wybranym przez nas polu


           if ((sprawdzenie_pozycji(szachownica, &z, &na, licznik))==0)           //sprawdzamy czy wybralismy nasza figure, i czy na polu na, ktore sie ruszamy nie ma naszej
                 continue;                                                       //jesli jest gdzies nasza figura to wraca nas do wpisywania od nowa, komunikat o bledzie jest w funkcji
           else
            {
             switch (m)                                                            //osobne wywolania dla kazdej figury
              {
                case 1:
                  if ((sprawdzenie_pionek(szachownica, &z, &na, licznik))==1)
                     {
                        system("cls");
                        ruch (szachownica, &z, &na);
                        wyswietlanie (szachownica);
                        if (zamiana_pionek(szachownica, licznik)==1)
                            {
                                wyswietlanie (szachownica);
                            }
                        licznik++;
                        break;
                     }
                     else
                     {
                         printf ("Ruch nieprawidlowy \n");
                         break;
                     }

                case 2:
                    if ((sprawdzenie_wieza(szachownica, &z, &na, licznik))==1)
                    {
                        system("cls");
                        ruch (szachownica, &z, &na);
                        wyswietlanie (szachownica);
                        licznik++;
                        break;
                    }
                    else
                        break;

                case 3:
                    if ((sprawdzenie_kon(szachownica, &z, &na, licznik))==1)
                    {
                        system("cls");
                        ruch (szachownica, &z, &na);
                        wyswietlanie (szachownica);
                        licznik++;
                        break;
                    }
                    else
                        break;

                 case 4:
                    if ((sprawdzenie_goniec(szachownica, &z, &na, licznik))==1)
                    {
                        system("cls");
                        ruch (szachownica, &z, &na);
                        wyswietlanie (szachownica);
                        licznik++;
                        break;
                    }
                    else
                        break;

                 case 5:
                    if ((sprawdzenie_hetman(szachownica, &z, &na, licznik))==1)
                    {
                        system("cls");
                        ruch (szachownica, &z, &na);
                        wyswietlanie (szachownica);
                        licznik++;
                        break;
                    }
                    else
                        break;

                case 6:
                    if ((sprawdzenie_krol(szachownica, &z, &na, licznik))==1)
                    {
                        system("cls");
                        ruch (szachownica, &z, &na);
                        wyswietlanie (szachownica);
                        licznik++;
                        break;
                    }
                    else
                        break;

                default:
                    printf("Wybrano niewlasciwe pole\n");
                }
          }//if
        }
        else
        {
            fflush(stdin);
            printf("Wpisano zle wartosci\n");
            continue;
        }
    }//while
    return 0;
}

void ustawienie (int tab [][ROZMIAR])
{
    int i,j;

    for (i=1;i<ROZMIAR-1;i++)
    {
        for (j=0;j<ROZMIAR;j++)
        {
            if (i==1)
                tab[i][j]=21;
            else if (i==6)
                tab[i][j]=11; //1 - pionek
            else
                tab[i][j]=0;
        }//for
    }//for
     tab[0][0]=22;//2 - wieza
     tab[0][1]=23;//3 - skoczek
     tab[0][2]=24;//4 - goniec
     tab[0][3]=25;//5- hetman
     tab[0][4]=26;//6 - krol
     tab[0][5]=24;
     tab[0][6]=23;
     tab[0][7]=22;
     tab[7][0]=12;
     tab[7][1]=13;
     tab[7][2]=14;
     tab[7][3]=15;
     tab[7][4]=16;
     tab[7][5]=14;
     tab[7][6]=13;
     tab[7][7]=12;
}

void wyswietlanie (int tab [][ROZMIAR])
{
    int i, j;

    for (i=0;i<ROZMIAR;i++)
    {
        if (i>0)
          printf(" %d  ", i+1);

        if(i==0)
        {
            printf("      1    2    3    4    5    6    7    8");
            printf("\n\n 1  ");

        }

        for (j=0;j<ROZMIAR;j++)
        {
              switch (tab[i][j])                  //wyswietlanie nazw dla kazdej figury
            {
                case 11:
                    printf (" BP  ");
                    break;

                case 12:
                    printf (" BW  ");
                    break;

                case 13:
                    printf (" BS  ");
                    break;

                case 14:
                    printf (" BG  ");
                    break;

                case 15:
                    printf (" BH  ");
                    break;

                case 16:
                    printf (" BK  ");
                    break;

                case 21:
                    printf (" CP  ");
                    break;

                case 22:
                    printf (" CW  ");
                    break;

                case 23:
                    printf (" CS  ");
                    break;

                case 24:
                    printf (" CG  ");
                    break;

                case 25:
                    printf (" CH  ");
                    break;

                case 26:
                    printf (" CK  ");
                    break;

                default:
                    printf (" -   ");
            }
        }//for
        printf("\n\n");
    }//for
}

void ruch(int tab [][ROZMIAR], int *w, int *x)    //wywolana w mainie jesli po sprawdzeniu okaze sie, ze mozemy sie ruszyc
{
    int a,b,wz,kz,wn,kn;

    a=*w;
    b=*x;

    wz= a/10 -1;   //wiersz z ktorego sie ruszamy, przedstawiony w notacji macierzowej
    kz= a%10 -1;   //kolumna z ktorej sie ruszamy -||-
    wn= b/10 -1;   // wiersz na ktory sie ruszamy -||-
    kn= b%10 -1;   //kolumna na ktora sie ruszamy -||-

    tab [wn][kn]= tab [wz][kz];               //wykonanie wskazanego ruchu
    tab [wz][kz]=0;
    }

int warunek_konca (int tab [][ROZMIAR])
{
  int i,j,suma1=0,suma2=0,suma3=0;

    for (i=0;i<ROZMIAR;i++)
    {
        for (j=0;j<ROZMIAR;j++)
        {
           if ((tab[i][j]%10==6)&&(tab[i][j]/10==1))
           {
               suma1=1;
               suma2++;
           }

           if ((tab[i][j]%10==6)&&(tab[i][j]/10==2))
           {
               suma3=1;
               suma2++;
           }

        }
    }

     if (suma2==2)
        return 1;
     else
       {
        if (suma1==0)
          {
            putchar('\n');
            printf("Rozgrywke wygrywa gracz nr 2 (czarne)");
            putchar('\n');
            return 0;
          }
        if (suma3==0)
          {
            putchar('\n');
            printf("Rozgrywke wygrywa gracz nr 1 (biale)");
            putchar('\n');
            return 0;
          }
       }
   return 1;
}

int sprawdzenie_pozycji (int tab [][ROZMIAR], int *w, int *x, int c)
{
    int a,b,wz,kz,wn,kn,licznik;

    a=*w; // pole początkowe
    b=*x; // pole końcowe
    licznik=c; //który ruch

    wz= a/10 -1; //wiersz początkowy
    kz= a%10 -1; //kolumna początkowa
    wn= b/10 -1; //wiersz końcowy
    kn= b%10 -1; //kolumna końcowa


     if(licznik%2 ==0)                                 //osobne dla obydwu graczy
     {
       if ((tab[wz][kz])/10==2)                        //czy wybralismy nasza figure
            {
            printf("Wybrana figura nie nalezy do ciebie\n");
            return 0;
            }

        if ((tab[wn][kn])/10==1)                      //czy na wskazanym polu nie ma naszej
            {
            printf("Na wskazanym polu znajduje sie twoja figura\n");
            return 0;
            }
     }
     else
     {
         if ((tab[wz][kz])/10==1)
            {
            printf("Wybrana figura nie nalezy do ciebie\n");
            return 0;
            }

         if ((tab[wn][kn])/10==2)
            {
            printf("Na wskazanym polu znajduje sie twoja figura\n");
            return 0;
            }
     }

        return 1;                      //zwraca 1 jesli wszystko jest ok
}

int sprawdzenie_pionek(int tab [][ROZMIAR], int *w, int *x, int c)
{
    int a,b,wz,kz,wn,kn,licznik;
    a=*w; // pole początkowe
    b=*x; // pole końcowe
    licznik=c; //który ruch

    wz= a/10 -1; //wiersz początkowy
    kz= a%10 -1; //kolumna początkowa
    wn= b/10 -1; //wiersz końcowy
    kn= b%10 -1; //kolumna końcowa

    if (licznik%2==0)                  //osobne sprawdzenie w zaleznosci od gracza
    {

        if ((wn==wz-1) && ((kn==kz+1)||(kn==kz-1)) && ((tab[wn][kn])/10==2))    //warunek dotyczacy bicia
            return 1;

        if ((wn==wz-1)&&(kn==kz)&&(tab[wn][kn]==0))                //warunek dotyczacy ruchu normalnego, do przodu i tylu
            return 1;

        if ((wz==6) && (wn==wz-2)&&(tab[wn][kn]==0) && (tab[wz-1][kn]==0) && (kn==kz)) //warunek dotyczacy ruchu z pozycji wyjsciowej
            return 1;

    }
    else             //wszystkie warunki analogiczne do tych dla gracza 1
        {

        if ((wn==wz+1) && ((kn==kz+1)||(kn==kz-1)) && ((tab[wn][kn])/10==1))
            return 1;

        if ((wn==wz+1) &&(kn==kz)&&(tab[wn][kn]==0))
            return  1;

        if ((wz==1) && (wn==wz+2) && (tab[wn][kn]==0) && (tab[wz+1][kn]==0) && (kn==kz))
            return 1;

        }
            return 0;
}

int sprawdzenie_wieza(int tab [][ROZMIAR], int *w, int *x, int c)
{
    int a,b,i,j,wz,kz,wn,kn,licznik,q,r;

    a=*w;
    b=*x;
    licznik=c;

    wz= a/10 -1;
    kz= a%10 -1;
    wn= b/10 -1;
    kn= b%10 -1;

     if ((wn!=wz) && (kn!=kz))                   //warunek, ze moze sie ruszac tylko w pionie lub poziomie
        {
            printf("Ruch nieprawidlowy\n");
            return 0;
        }


    if (wn>wz)                 //umowne wartosci, zeby bylo wiadomo, w ktora strone ma przeszukiwac szachownice, zeby sprawdzic czy na drodze nie ma innych pionkow
        q=0;
    else if (wn<wz)
        q=1;

    if (kn>kz)
        r=0;
    else if (kn<kz)
        r=1;

    if (licznik%2==0)
    {
        if(((wn==wz+1)||(wn==wz-1)) && (kn==kz) && ((tab[wn][kn]/10==2)||(tab[wn][kn]==0)))    //osobne warunki gdy rusza sie o jedno pole tylko
            return 1;                                                                          //w zaleznosci czy w pionie czy w poziomie

        if(((kn==kz+1)||(kn==kz-1)) && (wn==wz) && ((tab[wn][kn]/10==2)||(tab[wn][kn]==0)))
            return 1;


        if (q==0)                         //przeszukuje droge ruchu w poszukiwaniu innych figur
        {
            for (i=wz+1;i<wn;i++)
            {
                if ((tab[i][kn])/10==2)
                {
                    printf("Ruch nieprawidlowy- po drodze napotkano figure przeciwnika. \n");
                    return 0;
                }
                else if ((tab[i][kn])/10==1)
                {
                    printf("Ruch nieprawidlowy- po drodze napotkano twoja figure. \n");
                    return 0;
                }
            }
         return 1;         //jesli nie znajdzie innych figur to ruch sie wykonuje
        }


        if (q==1)        //analogicznie do poprzedniej tylko dla ruchu w dol
        {
            for (i=wz-1;i>wn;i--)
            {
                if ((tab[i][kn])/10==2)
                {
                    printf("Ruch nieprawidlowy, po drodze napotkano figure przeciwnika. \n");
                    return 0;
                }
                else if ((tab[i][kn])/10==1)
                {
                    printf("Ruch nieprawidlowy, po drodze napotkano twoja figure. \n");
                    return 0;
                }
            }
            return 1;
        }

        if (r==0)    //dla ruchu w prawo
        {
            for (j=kz+1;j<kn;j++)
            {
                if ((tab[wn][j])/10==2)
                {
                    printf("Ruch nieprawidlowy, po drodze napotkano figure przeciwnika. \n");
                    return 0;
                }
                else if ((tab[wn][j])/10==1)
                {
                   printf("Ruch nieprawidlowy, po drodze napotkano twoja figure. \n");
                   return 0;
                }
            }
           return 1;
        }

        if (r==1)     //dla ruchu w lewo
        {
            for (j=kz-1;j>kn;j--)
            {
                if ((tab[wn][j])/10==2)
                {
                    printf("Ruch nieprawidlowy, po drodze napotkano figure przeciwnika. \n");
                    return 0;
                }
                else if ((tab[wn][j])/10==1)
                {
                   printf("Ruch nieprawidlowy, po drodze napotkano twoja figure. \n");
                   return 0;
                }
            }
           return 1;
        }

    }
    else         //wszystko analogicznie jak dla gracza nr 1
    {
        if(((wn==wz+1)||(wn==wz-1)) && (kn==kz) &&((tab[wn][kn]/10==1)||(tab[wn][kn]==0)))
            return 1;

        if(((kn==kz+1)||(kn==kz-1)) && (wn==wz) && ((tab[wn][kn]/10==1)||(tab[wn][kn]==0)))
            return 1;

        if (q==0)
        {
            for (i=wz+1;i<wn;i++)
            {
                if ((tab[i][kn])/10==1)
                {
                    printf("Ruch nieprawidlowy, po drodze napotkano figure przeciwnika. \n");
                    return 0;
                }
                else if ((tab[i][kn])/10==2)
                {
                   printf("Ruch nieprawidlowy, po drodze napotkano twoja figure. \n");
                   return 0;
                }
            }
          return 1;
        }

        if (q==1)
        {
            for (i=wz-1;i>wn;i--)
            {
                if ((tab[i][kn])/10==1)
                {
                    printf("Ruch nieprawidlowy, po drodze napotkano figure przeciwnika. \n");
                    return 0;
                }
                else if ((tab[i][kn])/10==2)
                {
                   printf("Ruch nieprawidlowy, po drodze napotkano twoja figure. \n");
                   return 0;
                }
            }
          return 1;
        }

        if (r==0)
        {
            for (j=kz+1;j<kn;j++)
            {
                if ((tab[wn][j])/10==1)
                {
                    printf("Ruch nieprawidlowy, po drodze napotkano figure przeciwnika. \n");
                    return 0;
                }
                else if ((tab[wn][j])/10==2)
                {
                   printf("Ruch nieprawidlowy, po drodze napotkano twoja figure. \n");
                   return 0;
                }
            }
          return 1;
        }

        if (r==1)
        {
            for (j=kz-1;j>kn;j--)
            {
                if ((tab[wn][j])/10==1)
                {
                    printf("Ruch nieprawidlowy, po drodze napotkano figure przeciwnika. \n");
                    return 0;
                }
                else if ((tab[wn][j])/10==2)
                {
                   printf("Ruch nieprawidlowy, po drodze napotkano twoja figure. \n");
                   return 0;
                }
            }
          return 1;
        }

    }
          return 0;
}

int sprawdzenie_kon (int tab [][ROZMIAR], int *w, int *x, int c)
{
    int a,b,wz,kz,wn,kn;

    a=*w;
    b=*x;

    wz= a/10 -1;
    kz= a%10 -1;
    wn= b/10 -1;
    kn= b%10 -1;

    if (((wn==wz-2)||(wn==wz+2))&&((kn==kz+1)||(kn==kz-1)))   //tylko dwa sprawdzenia, jesli ruszamy sie o dwa wiersze w przod lub tyl...
        return 1;                                             //... to pozniej mozemy tylko o kolumne w prawo lub lewo

    if (((wn==wz-1)||(wn==wz+1))&&((kn==kz+2)||(kn==kz-2)))   //analogicznie jesli o 2 kolumny w prawo lub lewo to pozniej tylko
        return 1;                                             //o jeden wiersz w dol lub gore

    printf("Ruch nieprawidlowy \n");
    return 0;

}

int sprawdzenie_goniec (int tab[][ROZMIAR], int *w, int *x, int c)
{
	int a, b, i, j, wz, kz, wn, kn, licznik, g, r;
	a=*w;
	b=*x;
	wz= a/10 -1;
	kz= a%10 -1;
	wn= b/10 -1;
    kn= b%10 -1;
    j=kz;
    licznik=c;

	if ((wn==wz) || (kn==kz))                   //warunek, ze goniec moze sie ruszac tylko po przekątnych
       {
            printf("Ruch nieprawidlowy\n");
            return 0;
       }

    if(((wn-wz)!=(kn-kz))&&((wn-wz)!=(kz-kn))) //warunek, zeby ruch byl po przekatnej
      {
         printf("Ruch nieprawidlowy\n");
         return 0;
      }


    if (wn>wz)                 //umowne wartosci, zeby bylo wiadomo, w ktora strone ma przeszukiwac szachownice, zeby sprawdzic czy na drodze nie ma innych pionkow
        g=0;
    else if (wn<wz)
        g=1;

    if (kn>kz)
        r=0;
    else if (kn<kz)
        r=1;

	if (licznik%2==0)
	{
		if((wn==wz+1) && ((kn==kz-1)||(kn==kz+1)) && ((tab[wn][kn]/10==2)||(tab[wn][kn]==0)))
            return 1;       //osobne warunki gdy rusza sie o jedno pole tylko w zaleznosci czy porusza się po przekątnych
                            //w dół czy w góre
        if(((kn==kz+1)||(kn==kz-1)) && (wn==wz-1) && ((tab[wn][kn]/10==2)||(tab[wn][kn]==0)))
            return 1;

	    if ((g==0) && (r==0))                         //przeszukuje droge ruchu w poszukiwaniu innych figur
         {                                            //idziemy od miejsca w którym znajduje się nasz pionek
            for (i=wz+1;i<wn;i++)	    	          //po przekątnej w prawo i w dół
            {
                j++;                                  //wykorzystujemy to, ze zeby ruch byl po przekatnej to kolumny musza sie
                                                      //zmieniac o tyle samo co wiersze
                if ((tab[i][j])/10==2)                //w dalszych warunkach jest analogicznie
                {
                    printf("Ruch nieprawidlowy- po drodze napotkano figure przeciwnika. \n");
                    return 0;
                }
                else if ((tab[i][j])/10==1)
                {
                    printf("Ruch nieprawidlowy- po drodze napotkano twoja figure. \n");
                    return 0;
                }

	        }
         return 1;         //jesli nie znajdzie innych figur to ruch sie wykonuje
        }


        if ((g==1) && (r==0))        //analogicznie do poprzedniej tylko dla ruchu w prawo i w górę
        {
            for (i=wz-1;i>wn;i--)
            {
                j++;

                if ((tab[i][j])/10==2)
                {
                    printf("Ruch nieprawidlowy- po drodze napotkano figure przeciwnika. \n");
                    return 0;
                }
                else if ((tab[i][j])/10==1)
                {
                    printf("Ruch nieprawidlowy- po drodze napotkano twoja figure. \n");
                    return 0;
                }
            }
            return 1;
        }

        if ((g==1) && (r==1))    //dla ruchu w lewo i w górę
        {
            for (i=wz-1;i>wn;i--)
            {
                j--;

                if ((tab[i][j])/10==2)
                {
                    printf("Ruch nieprawidlowy- po drodze napotkano figure przeciwnika. \n");
                    return 0;
                }
                else if ((tab[i][j])/10==1)
                {
                    printf("Ruch nieprawidlowy- po drodze napotkano twoja figure. \n");
                    return 0;
                }
            }
           return 1;
        }

        if ((g==0) && (r==1))     //dla ruchu w lewo i w dół
        {
            for (i=wz+1;i<wn;i++)
            {
               j--;

               if ((tab[i][j])/10==2)
                {
                    printf("Ruch nieprawidlowy- po drodze napotkano figure przeciwnika. \n");
                    return 0;
                }
                else if ((tab[i][j])/10==1)
                {
                    printf("Ruch nieprawidlowy- po drodze napotkano twoja figure. \n");
                    return 0;
                }
            }
           return 1;
        }
    }

	else

	{
	    if((wn==wz+1) && ((kn==kz-1)||(kn==kz+1)) && ((tab[wn][kn]/10==1)||(tab[wn][kn]==0)))
            return 1;                                                                          //osobne warunki gdy rusza sie o jedno pole tylko w zaleznosci czy porusza się po przekątnych
                                                                                               //w dół czy w góre
        if(((kn==kz+1)||(kn==kz-1)) && (wn==wz-1) && ((tab[wn][kn]/10==1)||(tab[wn][kn]==0)))
            return 1;


     if ((g==0) && (r==0))                         //przeszukuje droge ruchu w poszukiwaniu innych figur
        {					                //idziemy od miejsca w którym znajduje się nasz pionek
            for (i=wz+1;i<wn;i++)		        //po przekątnej w prawo i w dół
            {
                j++;

                if ((tab[i][j])/10==1)
                {
                    printf("Ruch nieprawidlowy- po drodze napotkano figure przeciwnika. \n");
                    return 0;
                }
                else if ((tab[i][j])/10==2)
                {
                    printf("Ruch nieprawidlowy- po drodze napotkano twoja figure. \n");
                    return 0;
	            }
	        }
         return 1;         //jesli nie znajdzie innych figur to ruch sie wykonuje
        }

        if ((g==1) && (r==0))        //analogicznie do poprzedniej tylko dla ruchu w prawo i w górę
        {
            for (i=wz-1;i>wn;i--)
            {
               j++;

               if ((tab[i][j])/10==1)
                {
                    printf("Ruch nieprawidlowy- po drodze napotkano figure przeciwnika. \n");
                    return 0;
                }
                else if ((tab[i][j])/10==2)
                {
                    printf("Ruch nieprawidlowy- po drodze napotkano twoja figure. \n");
                    return 0;
	            }
            }
            return 1;
        }

        if ((g==1) && (r==1))    //dla ruchu w lewo i w górę
        {
            for (i=wz-1;i>wn;i--)
            {
                j--;

                if ((tab[i][j])/10==1)
                {
                    printf("Ruch nieprawidlowy- po drodze napotkano figure przeciwnika. \n");
                    return 0;
                }
                else if ((tab[i][j])/10==2)
                {
                    printf("Ruch nieprawidlowy- po drodze napotkano twoja figure. \n");
                    return 0;
	            }
            }
           return 1;
        }

        if ((g==0) && (r==1))     //dla ruchu w lewo i w dół
        {
            for (i=wz+1;i<wn;i++)
            {
               j--;

               if ((tab[i][j])/10==1)
                {
                    printf("Ruch nieprawidlowy- po drodze napotkano figure przeciwnika. \n");
                    return 0;
                }
                else if ((tab[i][j])/10==2)
                {
                    printf("Ruch nieprawidlowy- po drodze napotkano twoja figure. \n");
                    return 0;
	            }
            }
           return 1;
        }
    }
return 0;

}
int sprawdzenie_krol (int tab[][ROZMIAR], int *w, int *x, int c)
{
    int a,b,wz,kz,wn,kn;

    a=*w;
    b=*x;

    wz= a/10 -1;
    kz= a%10 -1;
    wn= b/10 -1;
    kn= b%10 -1;

        if(((wn==wz+1)||(wn==wz-1)) && ((kn==kz)||(kn==kz+1)||(kn==kz-1)))    //osobne warunki gdy rusza sie o jedno pole tylko
            return 1;                                                                                                   //w zaleznosci czy w pionie czy w poziomie

        if(((kn==kz+1)||(kn==kz-1)) && (wn==wz))
            return 1;

        printf("Ruch nieprawidlowy \n");
        return 0;
}
int sprawdzenie_hetman (int tab[][ROZMIAR], int *w, int *x, int c)
{
    int a,b,wz,kz,wn,kn, licznik;

    a=*w;
    b=*x;
    licznik=c;

    wz= a/10 -1;
    kz= a%10 -1;
    wn= b/10 -1;
    kn= b%10 -1;

    if((wz==wn) || (kz==kn))
    {
        sprawdzenie_wieza(tab, w, x, licznik);
    }
    else
    {
        sprawdzenie_goniec(tab, w, x, licznik);
    }

}
int zamiana_pionek (int tab[][ROZMIAR], int c)
{
    int j, licznik;
    char m;
    licznik=c;

    for (j=0;j<ROZMIAR;j++)
      {
      if(licznik%2==0)
        {
         if ((tab[0][j]/10==1)&&(tab[0][j]%10==1))
          {
             printf("Na jaka figure chcesz zamienic swoj pionek: \n 1. Wieza \n 2. Skoczek \n 3. Goniec \n 4. Hetman \n\n");

             while(1)
             {
                 getchar();
                 m=getchar();
                 if(m>=49 && m<=52) break;
                 else printf("Wczytano zla wartosc\n");
             }
             switch (m)
             {
                case '1':
                  tab[0][j]=12;
                  break;

                case '2':
                    tab[0][j]=13;
                    break;

                case '3':
                    tab[0][j]=14;
                    break;

                case '4':
                    tab[0][j]=15;
                    break;
             }

            system("cls");
            return 1;
          }
        }

    if(licznik%2==1)
      {
        if ((tab[7][j]/10==2)&&(tab[7][j]%10==1))
          {
             printf("Na jaka figure chcesz zamienic swoj pionek: \n 1. Wieza \n 2. Skoczek \n 3. Goniec \n 4. Hetman \n\n");
             while(1)
             {
                 getchar();
                 m=getchar();
                 if(m>=49 && m<=52) break;
                 else printf("Wczytano zla wartosc\n");
             }
             switch (m)
             {
                case '1':
                  tab[7][j]=22;
                  break;

                case '2':
                    tab[7][j]=23;
                    break;

                case '3':
                    tab[7][j]=24;
                    break;

                case '4':
                    tab[7][j]=25;
                    break;
             }

            system("cls");
            return 1;
          }
        }
      }
  return 0;
}







