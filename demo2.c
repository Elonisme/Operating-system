/*
The Author Is LiYILONG
STUDENT ID IS 3120190971352
WARING:Please respect the fruits of my labor and don't copy my code
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct PAG
{
    int ID;
    int ExchangeInID;
    int *paks;
    char ShortPage;
    int ExchangeOutPage;
    int *BeingTime;
    int Pagsnumbers;
    struct PAG *next;
} PAG;

PAG *CreatPAG(int numbers)
{
    PAG *Node = (PAG *)malloc(sizeof(PAG));
    Node->ID = 0;
    Node->ExchangeInID = 0;
    Node->paks = malloc(sizeof(int) * numbers);
    Node->BeingTime = malloc(sizeof(int) * numbers);
    Node->Pagsnumbers = numbers;
    for (int i = 0; i < numbers; i++)
    {
        Node->paks[i] = -1;
        Node->BeingTime[i] = 0;
    }
    Node->ShortPage = '-';
    Node->ExchangeOutPage = -1;
    Node->next = NULL;
    return Node;
}

void FreePAGS(PAG *Node)
{
    free(Node->paks);
    free(Node->BeingTime);
    free(Node);
}

void ShowPAKS(PAG *pags, const int numbers)
{
    PAG *head = NULL;
    head = pags;
    for (PAG *i = head; i != NULL; i = i->next)
    {
        printf("ID:%d\t", i->ID);
        printf("ExchangeInPage:%d\t", i->ExchangeInID);
        for (int j = 0; j < numbers; j++)
        {
            printf("NO.%dPAG:%d\t", j + 1, pags->paks[j]);
        }
        printf("ShortPage:%c\t", i->ShortPage);
        printf("ExchangeOutPage:%d\n", i->ExchangeOutPage);
    }
}

int FindMaxTime(PAG *pags)
{
    int *NodeTime = pags->BeingTime;
    int max = 0;
    for (int i = 1; i < pags->Pagsnumbers; i++)
    {
        if (NodeTime[max] < NodeTime[i])
        {
            max = i;
        }
    }
    return max;
}

int FindBeing(PAG *pags, int order)
{
    for (int i = 0; i < pags->Pagsnumbers; i++)
    {
        if (order == pags->paks[i])
        {
            return i;
        }
    }
    return -1;
}

int FindNull(PAG *ps)
{
    for (int i = 0; i < ps->Pagsnumbers; i++)
    {
        if (ps->paks[i] == -1)
        {
            return i;
        }
    }
    return -1;
}

int FindOrder(int x, int *order, int i, int length)
{
    for (int j = i; j < length; j++)
    {
        if (order[j] == x)
        {
            return j;
            break;
        }
    }
    return -1;
}

int FindReOrder(int x, int *order, int i)
{
    for (int j = i - 1; j > -1; j--)
    {
        if (order[j] == x)
        {
            return j;
            break;
        }
    }
    return -1;
}

void FIFO(PAG *pags, int *order, int length)
{
    int cn = 0;
    PAG *ps = pags;
    int max = 0;
    int s = -2;
    for (int i = 0; i < length; i++)
    {
        ps->ID++;
        ps->ExchangeInID = order[i];

        if (FindBeing(ps, order[i]) != -1)
        {
            for (int j = 0; j < ps->Pagsnumbers; j++)
            {
                ps->BeingTime[j]++;
            }
            ps->ShortPage = 'n';
            ps->ExchangeOutPage = -1;
            ShowPAKS(ps, ps->Pagsnumbers);
        }
        else
        {
            s = FindNull(ps);
            if (s != -1)
            {
                ps->paks[s] = order[i];
                ps->BeingTime[s] = 1;
                for (int j = 0; j < ps->Pagsnumbers; j++)
                {
                    if (j != s || j != -1)
                    {
                        ps->BeingTime[j]++;
                    }
                    else
                    {
                        continue;
                    }
                }
                ps->ShortPage = 'y';
                cn++;
                ps->ExchangeOutPage = -1;
                ShowPAKS(ps, ps->Pagsnumbers);
            }
            else
            {
                max = FindMaxTime(ps);
                ps->ExchangeOutPage = ps->paks[max];
                ps->paks[max] = order[i];
                ps->BeingTime[max] = 1;
                for (int j = 0; j < ps->Pagsnumbers; j++)
                {
                    if (j != max)
                    {
                        ps->BeingTime[j]++;
                    }
                    else
                    {
                        continue;
                    }
                }
                ps->ShortPage = 'y';
                cn++;
                ShowPAKS(ps, ps->Pagsnumbers);
            }
        };
    }
    printf("Page faults: %d\n", cn);
    float c = (float)cn / ps->ID;
    printf("Page fault rate:%.1f%%\n", c * 100);
}

void LRU(PAG *pags, int *order, int length)
{
    int cn = 0;
    PAG *ps = pags;
    int s = -2;
    int max = 0;
    int distance = 0;
    int Reorder = 0;
    int Lastdistance = 0;
    for (int i = 0; i < length; i++)
    {
        ps->ID++;
        ps->ExchangeInID = order[i];

        if (FindBeing(ps, order[i]) != -1)
        {
            for (int j = 0; j < ps->Pagsnumbers; j++)
            {
                ps->BeingTime[j]++;
            }
            ps->ShortPage = 'n';
            ps->ExchangeOutPage = -1;
            ShowPAKS(ps, ps->Pagsnumbers);
        }
        else
        {
            s = FindNull(ps);
            if (s != -1)
            {
                ps->paks[s] = order[i];
                ps->BeingTime[s] = 1;
                for (int j = 0; j < ps->Pagsnumbers; j++)
                {
                    if (j != s || j != -1)
                    {
                        ps->BeingTime[j]++;
                    }
                    else
                    {
                        continue;
                    }
                }
                ps->ShortPage = 'y';
                cn++;
                ps->ExchangeOutPage = -1;
                ShowPAKS(ps, ps->Pagsnumbers);
            }
            else
            {
                for (int k = 0; k < ps->Pagsnumbers; k++)
                {
                    Reorder = FindReOrder(ps->paks[k], order, i);
                    if (Reorder != -1)
                    {
                        distance = i - Reorder;
                    }
                    if (distance > Lastdistance)
                    {
                        Lastdistance = distance;
                        max = k;
                    }
                }
                ps->ExchangeOutPage = ps->paks[max];
                ps->paks[max] = order[i];

                ps->BeingTime[max] = 1;
                for (int j = 0; j < ps->Pagsnumbers; j++)
                {
                    if (j != max)
                    {
                        ps->BeingTime[j]++;
                    }
                    else
                    {
                        continue;
                    }
                }
                ps->ShortPage = 'y';
                cn++;
                ShowPAKS(ps, ps->Pagsnumbers);
                Lastdistance = 0;
                distance = 0;
            }
        };
    }
    printf("Page faults: %d\n", cn);
    float c = (float)cn / ps->ID;
    printf("Page fault rate:%.1f%%\n", c * 100);
}

void OPT(PAG *pags, int *order, int length)
{
    int cn = 0;
    PAG *ps = pags;
    int s = -2;
    int a = 0;
    int distance = 0;
    int Lastdistance = 0;
    int MaxOrder = 0;
    int runtime = 0;
    int LastRuntime = 0;
    for (int i = 0; i < length; i++)
    {
        ps->ID++;
        ps->ExchangeInID = order[i];

        if (FindBeing(ps, order[i]) != -1)
        {
            for (int j = 0; j < ps->Pagsnumbers; j++)
            {
                ps->BeingTime[j]++;
            }
            ps->ShortPage = 'n';
            ps->ExchangeOutPage = -1;
            ShowPAKS(ps, ps->Pagsnumbers);
        }
        else
        {
            s = FindNull(ps);
            if (s != -1)
            {
                ps->paks[s] = order[i];
                ps->BeingTime[s] = 1;
                for (int j = 0; j < ps->Pagsnumbers; j++)
                {
                    if (j != s || j != -1)
                    {
                        ps->BeingTime[j]++;
                    }
                    else
                    {
                        continue;
                    }
                }
                ps->ShortPage = 'y';
                cn++;
                ps->ExchangeOutPage = -1;
                ShowPAKS(ps, ps->Pagsnumbers);
            }
            else
            {
                for (int k = 0; k < ps->Pagsnumbers; k++)
                {
                    a = FindOrder(ps->paks[k], order, i, length);
                    if (a == -1)
                    {
                        distance = 99;
                        Lastdistance = distance;
                        runtime = ps->BeingTime[k];
                    }
                    else
                    {
                        distance = a - i;
                    }

                    if (distance > Lastdistance && distance != 99)
                    {
                        Lastdistance = distance;
                        MaxOrder = k;
                    }
                    else
                    {
                        if (runtime > LastRuntime)
                        {
                            LastRuntime = runtime;
                            MaxOrder = k;
                        }
                    }
                }

                if (distance != 0)
                {
                    ps->ExchangeOutPage = ps->paks[MaxOrder];
                    ps->paks[MaxOrder] = order[i];

                    ps->BeingTime[MaxOrder] = 1;
                    for (int j = 0; j < ps->Pagsnumbers; j++)
                    {
                        if (j != MaxOrder || j != -1)
                        {
                            ps->BeingTime[j]++;
                        }
                        else
                        {
                            continue;
                        }
                    }

                    distance = 0;
                    Lastdistance = 0;
                    runtime = 0;
                    LastRuntime = 0;
                }
                ps->ShortPage = 'y';
                cn++;
                ShowPAKS(ps, ps->Pagsnumbers);
            }
        };
    }
    printf("Page faults: %d\n", cn);
    float c = (float)cn / ps->ID;
    printf("Page fault rate:%.1f%%\n", c * 100);
}

void main()
{
    int myorder[13] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5, -1};
    const int Onenumbers = 3;
    const int Townumbers = 4;
    int length = sizeof(myorder) / sizeof(int) - 1;

    printf("--------------------------------------------------FIFO(3)---------------------------------------------\n");
    PAG *f3 = CreatPAG(Onenumbers);
    ShowPAKS(f3, Onenumbers);
    FIFO(f3, myorder, length);

    printf("--------------------------------------------------LRU(3)---------------------------------------------\n");
    PAG *u3 = CreatPAG(Onenumbers);
    ShowPAKS(u3, Onenumbers);
    LRU(u3, myorder, length);

    printf("--------------------------------------------------OPT(3)---------------------------------------------\n");
    PAG *o3 = CreatPAG(Onenumbers);
    ShowPAKS(o3, Onenumbers);
    OPT(o3, myorder, length);

    printf("--------------------------------------------------FIFO(4)---------------------------------------------\n");
    PAG *f4 = CreatPAG(Townumbers);
    ShowPAKS(f4, Townumbers);
    FIFO(f4, myorder, length);

    printf("--------------------------------------------------LRU(4)---------------------------------------------\n");
    PAG *u4 = CreatPAG(Townumbers);
    ShowPAKS(u4, Townumbers);
    LRU(u4, myorder, length);

    printf("--------------------------------------------------OPT(4)---------------------------------------------\n");
    PAG *o4 = CreatPAG(Townumbers);
    ShowPAKS(o4, Townumbers);
    OPT(o4, myorder, length);

    FreePAGS(f3);
    FreePAGS(u3);
    FreePAGS(o3);
    FreePAGS(f4);
    FreePAGS(u4);
    FreePAGS(o4);
}