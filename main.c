#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Variables
char e[10000][10000]; //ALL WE SEE!
int lP[1000000], cP[1000000]; //Polices place.
int lD, cD; //Thief place.
int n, m, np; //Information.
int q, w; //It's for counting the number of the movements; q for the thief and w for polices.
int olD, ocD; //It helps seeing function; old lD and old cD.
int a; //It helps counting movements.


//at BEGINNING********************************************************

//THIEF
void place_D()
{
    lD=10000; cD=10000;

    if(lD==10000) //lines
    {
        while(lD>=n)
        {
            lD= rand();
        }
    }

    if(cD==10000) //cols
    {
        while(cD>=m)
        {
            cD= rand();
        }
    }
}

//POLICES
void place_Ps()
{
    int i, j;

    //lines**************************************
    for(j=0; j<np; j++)
    {
        lP[j]=10000;
    }

    for(i=0; i<np; i++)
    {
        while(lP[i]>=n)
        {
            lP[i]= rand();
        }
    }

    //cols***************************************
    for(j=0; j<np; j++)
    {
        cP[j]=10000;
    }

    for(i=0; i<np; i++)
    {
        while(cP[i]>=m)
        {
            cP[i]= rand();
        }
    }
}


void Consider() //to consider being the polices in same places at start and change it if it is and do it for the thief too.
{
    int i, j;
    int k, l;
    int z=0; //It helps to break loops.

    //for polices********************************
    for(i=0; i<np-1; i++)
    {
        for(j=i+1; j<np; )
        {
            if(z==1)
            {
                z=0;
                break;
            }

            if(lP[i]==lP[j] && cP[i]==cP[j]) //finding wrong situation.
            {
                for(k=0; k<n; k++)
                {
                    for(l=0; l<m; l++)
                    {
                        if(e[k][l]=='*') //finding an empty place
                        {
                            e[k][l]='P';
                            lP[i]=k;
                            cP[i]=l;
                            z=1; //It helps to break loops.
                            break;
                        }
                    }

                    if(z==1)
                        break;
                }
            }

            else
                j++;
        }
    }

    //for thief*********************************
    for(i=0; i<np; i++)
    {
        if(lP[i]==lD && cP[i]==cD) //finding wrong situation.
        {
            z=0;

            for(k=0; k<n; k++)
            {
                for(l=0; l<m; l++)
                {
                    if(e[k][l]=='*')
                    {
                        e[k][l]='D';
                        lD=k;
                        cD=l;
                        z=1; //It helps to break loops.
                        break;
                    }
                }

                if(z==1)
                    break;
            }
        }

        if(z==1)
            break;
    }
}
//at BEGINNING END***************************************************


//CONTINUATION*******************************************************

//POLICES
void seeing_P() //when the polices see the thief or when they do not see him/her.
{
    int i;
    int dl, dc; //difference between lines and cols.
    int z=0; //It helps to function to find out the thief is seen.

    for(i=0; i<np; i++) //to check the thief is seen or not
    {
        dl= lP[i]-olD;
        dc= cP[i]-ocD;

        if(dl>=-2 && dl<=2 && dc>=-2 && dc<=2)
        {
            z=1; //the thief is seen.
            break;
        }
    }


    if(z==1) //the thief is seen*****************
    {
        for(i=0; i<np; i++)
        {
            dl= lP[i]-olD;
            dc= cP[i]-ocD;

            if(dl>0)
                lP[i]-=1;
            else if(dl<0)
                lP[i]+=1;
            else if(dl==0)
                lP[i]+=0;

            if(dc>0)
                cP[i]-=1;
            else if(dc<0)
                cP[i]+=1;
            else if(dc==0)
                cP[i]+=0;
        }

        w+= np; //because we sure all of the polices will move.
    }

    else if(z==0) //the thief is not seen*****************
    {
        int r;

        for(i=0; i<np; ) //lines*************************
        {
            r= (rand()%3)-1;

            if(lP[i]+r < n && lP[i]+r>=0)
            {
                lP[i]+= r;
                i++;
            }
        }

        a=0; //It helps counting the movements.
        if(r!=0)
        {
            w++;
            a=1;
        }


        for(i=0; i<np; ) //cols**************************
        {
            r= (rand()%3)-1;

            if(cP[i]+r < m && cP[i]+r>=0)
            {
                cP[i]+= r;
                i++;
            }
        }

        if(a==0 && r!=0) //It's for counting the movements.
            w++;
    }
}

//THIEF
void seeing_D() //when the thief see the polices or when he/she does not see them. (By this function, the thief reaches to an almost good intelligence (as I suppose of course! :D  ).)
{
    int i, dl, dc;
    int tob=0, lor=0; //top+ or button-, left+ or right-
    int z=0; //It helps counting the movements.

    for(i=0; i<np; i++)
    {
        dl= lD-lP[i];
        dc= cD-cP[i];

        if((dl==2 || dl==1) && (dc==2 || dc==1)) //top-left of the D
        {
            tob--; lor--;
        }
        else if((dl==2 || dl==1) && (dc==-2 || dc==-1)) //top-right of the D
        {
            tob--; lor++;
        }
        else if((dl==-2 || dl==-1) && (dc==2 || dc==1)) //button-left of the D
        {
            tob++; lor--;
        }
        else if((dl==-2 || dl==-1) && (dc==-2 || dc==-1)) //button-right of the D
        {
            tob++; lor++;
        }
        else if((dl==0) && (dc==2 || dc==1)) //left of the D
        {
            lor--;
        }
        else if((dl==0) && (dc==-2 || dc==-1)) //right of the D
        {
            lor++;
        }
        else if((dl==2 || dl==1) && (dc==0)) //top of the D
        {
            tob--;
        }
        else if((dl==-2 || dl==-1) && (dc==0)) //button of the D
        {
            tob++;
        }
    }


    //decision to go to top or button************
    if(tob>0)
    {
        if(lD-1 >= 0)
            lD-=1; //go to top
        else if(lor==0)
        {
            lD+=0; //don't go to top or button

            if(cD-1 >= 0) //go to left
                cD-=1;
            else if(cD+1 < m) //go to right
                cD+=1;
            else
            {
                cD+=0; //do nothing
                z=1;
            }
        }
    }
    else if(tob<0)
    {
        if(lD+1 < n)
            lD+=1; //go to button
        else if(lor==0)
        {
            lD+=0; //don't go to top or button

            if(cD-1 >= 0) //go to left
                cD-=1;
            else if(cD+1 < m) //go to right
                cD+=1;
            else
            {
                cD+=0; //do nothing
                z=1;
            }
        }
    }
    else if(tob==0 && lor==0)
    {
        lD+=0; //don't go to top or button

        if(cD-1 >= 0) //go to left
            cD-=1;
        else if(cD+1 < m) //go to right
            cD+=1;
        else
        {
            cD+=0; //do nothing
            z=1;
        }
    }

    //decision to go to left or right************
    if(lor>0)
    {
        if(cD-1 >= 0)
            cD-=1; //go to left
        else if(tob==0)
        {
            cD+=0; //don't go to left or right

            if(lD-1 >= 0) //go to top
                lD-=1;
            else if(lD+1 < n) //go to button
                lD+=1;
            else
            {
                lD+=0; //do nothing
                z=1;
            }
        }
    }
    else if(lor<0)
    {
        if(cD+1 < m)
            cD+=1; //go to right
        else if(tob==0)
        {
            cD+=0; //don't go to left or right

            if(lD-1 >= 0) //go to top
                lD-=1;
            else if(lD+1 < n) //go to button
                lD+=1;
            else
            {
                lD+=0; //do nothing
                z=1;
            }
        }
    }
    else if(lor==0 && tob==0)
    {
        cD+=0; //don't go to left or right

        if(lD-1 >= 0) //go to top
            lD-=1;
        else if(lD+1 < n) //go to button
            lD+=1;
        else
        {
            lD+=0; //do nothing
            z=1;
        }
    }


    if(z!=1)
        q++; //for counting the movements.
}
//CONTINUATION END***************************************************


void print_e() //printing e!
{
    int i, j;
    for(i=0; i<n; i++)
    {
        for(j=0; j<m; j++)
        {
            printf("%2c", e[i][j]);
        }
        printf("\n");
    }
}


int main()
{
    scanf("%d %d %d", &n, &m, &np); //information

    int i, j, b=0; //b helps to do different works at beginning.

    time_t t= time(NULL); //for random place
    srand(t);
    //***************************************************************

    int lp, cp; //they take the amount of lP and cP.

    while(1)
    {
        for(i=0; i<n; i++) //fixing e********************************
        {
            for(j=0; j<m; j++)
            {
                e[i][j]='*';
            }
        }

        //fixing places of Thief and Polices*************************

        if(b==0) //at beginning
        {
            place_D();
            place_Ps();
        }

        if(b!=0)
        {
            seeing_D();

            for(i=0; i<np; i++) //to check coming the thief into the bosom of the polices!
            {
                if(lD==lP[i] && cD==cP[i])
                {
                    e[lD][cD]= 'D';
                    for(i=0; i<np; i++)
                    {
                        lp= lP[i]; cp= cP[i];
                        e[lp][cp]= 'P';
                    }

                    print_e();

                    printf("\n\nBOSOM mode occurred.");
                    printf("\nThe number of the movements of the Thief is %d and the total movements of the Polices is %d.\n", q, w);
                    return 0; //end of the program.
                }
            }

            seeing_P();
        }


        e[lD][cD]= 'D';

        for(i=0; i<np; i++)
        {
            lp= lP[i]; cp= cP[i];
            e[lp][cp]= 'P';
        }

        if(b==0)
            Consider();
        //***********************************************************

        print_e();

        if(b!=0)
        {
            for(i=0; i<np; i++) // to check being thief in a same place a police is.
            {
                if(lD==lP[i] && cD==cP[i])
                {
                    printf("\n\nCATCHING mode occurred.");
                    printf("\nThe number of the movements of the Thief is %d and the total movements of the Polices is %d.\n", q, w);
                    return 0; //end of the program.
                }
            }
        }

        olD=lD; ocD=cD; //It helps seeing_P function.
        b=1;

        //waiting and cleaning***************************************
        system("timeout /t 1"); //instead of Sleep function; it waits for 1 second.
        system("cls");
    }

    return 0; //to not warn by compiler.
}
