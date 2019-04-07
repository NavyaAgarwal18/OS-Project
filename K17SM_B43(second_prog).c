#include<stdio.h>
#include<conio.h>
 
void main()
{
    int bt[20],p[20],wt[20],tat[20],i,j,n=10,total=0,pos,temp;
    float avg_wt,avg_tat;
   
    
    printf("\n\nEnter Number of Gifts each Student picks:\n\n");
    for(i=0;i<n;i++)
    {
	printf("p%d:",i+1);
    scanf("%d",&bt[i]);
    p[i]=i+1;           
    }
 
   
    for(i=0;i<n;i++)
    {
        pos=i;
        for(j=i+1;j<n;j++)
        {
            if(bt[j]>bt[pos])
                pos=j;
        }
 
        temp=bt[i];
        bt[i]=bt[pos];
        bt[pos]=temp;
 
        temp=p[i];
        p[i]=p[pos];
        p[pos]=temp;
    }
 
    wt[0]=0;            
    for(i=1;i<n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]+=bt[j];
 
        total+=wt[i];
    }
 
    avg_wt=(float)total/n;      
    total=0;
 
    printf("\nProcess\t\t\t    NO of Gifts    \tTheir Waiting Time\tTheir Turnaround Time");
    for(i=0;i<n;i++)
    {
        tat[i]=bt[i]+wt[i];     
        total+=tat[i];
        printf("\n\np%d\t\t\t  %d\t\t    %d\t\t\t%d",p[i],bt[i],wt[i],tat[i]);
    }
 
    
    
    
   
printf("\n\n\n\n\t\t\t\t\t\t      BILLING ORDER:\n\n");  
    
printf("\t\tCounter");
    for(i=0;i<n; i++)
    {
        for(j=0;j<4;j++)
        {
            printf("-");
        }
        printf("p%d",p[i]);
    }
    printf("\n");  
    

getch();

}

