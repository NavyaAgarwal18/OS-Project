#include<stdio.h>
#define MAX_SIZE 110 

int N; 

struct data {
    int num;
    char id[5];
    int at;
    int bt;
    int p;
    int rt;
    int ft;
    int st;
    int wt;
    int trt;
};



int pqf = -1, pqr = -1;
int rqf = -1, rqr = -1;


struct data* priorityQueue[MAX_SIZE];
struct data* queue[MAX_SIZE];

void sort(struct data p[]) {
    int i, j;
    struct data tmp;

    for (i = 0; i < N; i++) {

        for (j = i; j >= 1; j--) {
            
            if (p[j].at < p[j - 1].at) {

                tmp = p[j - 1];
                p[j - 1] = p[j];
                p[j] = tmp;
            }
            else if (p[j].at == p[j - 1].at) {

                if (p[j].num < p[j].num) {

                    tmp = p[j - 1];
                    p[j - 1] = p[j];
                    p[j] = tmp;
                }
            }
        }
    }
}


int pqEmpty() {

    return (pqf == -1 && pqr == -1); 
}



struct data* pqTop() {

    return priorityQueue[pqf];
}



void check(struct data *x) {

    int i, j;

    for (i = 0; i <= pqr; i++) {

        if (x->p < priorityQueue[i]->p) {

            for (j = pqr + 1; j > i; j--) {

                priorityQueue[j] = priorityQueue[j - 1];
            }

            priorityQueue[i] = x;
            return;
        }
    }
    priorityQueue[i] = x;
}



void pqPush(struct data* x) {

    if (pqf == -1 && pqr == -1) { 

        pqf++; 
        pqr++;
        priorityQueue[pqr] = x; 
        return;
    }
    else {

        check(x); 
    }

    pqr++;
}



void pqPop() {

    int i;

    if (pqf == -1 && pqr == -1) {

        return;
    }
    for (i = 0; i < pqr; i++) {

        priorityQueue[i] = priorityQueue[i + 1];
    }

    pqr--;

    if (pqr == -1)
        pqf = -1;
}


int rqEmpty() {

    return (rqf == -1 && rqr == -1);
}



struct data* rqFront() {
    return queue[rqf];
}



void rqPush(struct data* x) {

    if (rqf == -1 && rqr == -1) {

        rqf++;
        rqr++;
        queue[rqr] = x;
        return;
    }
    else {

        rqr++;
    }

    queue[rqr] = x;
}



void rqPop() {

   int i;
    if (rqf == -1 && rqr == -1) {

        return;
    }

    for ( i = 0; i <= rqr; i++) {

        queue[i] = queue[i + 1];
    }

    rqr--;
    if (rqr == -1)
        rqf = -1;
}



void calculation(struct data p[], int g[], int n) {

    int i, j;
    float avgWt = 0, avgTrt = 0;

    for (i = 0; i < N; i++) {

        for (j = n; j >= 0; j--) {

            if (g[j] == i + 1) {

                p[i].ft = j + 1;
                break;
            }
        }
    }

    for (i = 0; i < N; i++) {

        for (j = 0; j < n; j++) {

            if (g[j] == i + 1) {

                p[i].st = j;
                break;
            }   
        }
    }

    for (i = 0; i < N; i++) {
        
        p[i].wt = p[i].ft - p[i].at - p[i].bt;
        p[i].trt = p[i].wt + p[i].bt;
        avgWt += p[i].wt;
        avgTrt += p[i].trt;
    }

    printf("Id \t ArrivalTime \t BurstTime \t WaitingTime \t TurnAroundTime \n");

    for (i = 0; i < N; i++) {

        printf("%d \t    %d \t\t    %d \t\t    %d \t\t    %d \n", p[i].num, p[i].at, p[i].bt, p[i].wt, p[i].trt);
    }

    avgWt /= N;
    avgTrt /= N;

    printf("\n\n");
    printf("Average Waiting Time %f\n\n", avgWt);
    printf("Average Turn Around Time %f\n\n",avgTrt);

    printf("\n");
	int tt = 0; 
    tt += p[0].at + p[0].bt;

    for ( i = 1; i < N; i++) {

}



void MLQ(struct data p[]) {

    int i,j;

        if (tt < p[i].at)
            tt = p[i].at;
        
        tt += p[i].bt;
    }

    int ghant[tt]; // Ghant Chart
    int cpu_state = 0; // Status of the CPU

    for (i = 0; i < tt; i++)
        ghant[i] = -1;
    
    struct data* current;
    int pq_process = 0; 
    int rq_process = 0; 
    int q = 2;
    
    for (i = 0; i < tt; i++) {

        for ( j = 0; j < N; j++) {

            if (i == p[j].at) {
                pqPush(&p[j]); 
            }
        }

        if (cpu_state == 0) { 

            if (!pqEmpty()) { 

                current = pqTop();
                pqPop();
                pq_process = 1;
                cpu_state = 1;
            }
            else if (!rqEmpty()) {

                current = rqFront();
                rqPop();
                rq_process = 1;
                q = 2;
                cpu_state = 1;
            }
        }
        else if (cpu_state == 1) {

            if (pq_process == 1 && !pqEmpty()) {

                if (pqTop()->p < current->p) {

                    rqPush(current);
                    current = pqTop();
                    pqPop();
                }
            }
            else if (rq_process == 1 && !pqEmpty()) {

                rqPush(current);
                current = pqTop();
                pqPop();
                rq_process = 0;
                pq_process = 1;
            }
        }

        if (cpu_state == 1) {

            if (pq_process == 1) {

                current->rt--;
                ghant[i] = current->num;

                if (current->rt == 0) {

                    cpu_state = 0;
                    pq_process = 0;
                }
            }
            else if (rq_process == 1) {

                current->rt--;
                q--;
                ghant[i] = current->num;

                if (current->rt == 0) {

                    cpu_state = 0;
                    rq_process = 0;
                }
                else if (q == 0) {

                    cpu_state = 0;
                    rq_process = 1;
                    rqPush(current);
                }
            }
        }
    }

    

    printf("\n\n");
    printf("Ghant Chart\n");
    for ( i = 0; i < tt; i++) {
        printf("%d ", ghant[i]);
    }

    printf("\n\n");

    calculation(p, ghant, tt);

}


int main() {

   int i;
    printf("Total Number of Process:\t");
	scanf("%d", &N);

    struct data p[N];

    for ( i = 0; i < N; i++) {
    	printf("Process Number:\t");
	    scanf("%d",&p[i].num);
	    printf("Enter the Arrival time:");
        scanf("%d", &p[i].at);
	    printf("Enter the Burst time:");
        scanf("%d", &p[i].bt);
        printf("Enter the priority:");
		scanf("%d",&p[i].p);
        
        p[i].rt = p[i].bt;
    }

    sort(p);   

    MLQ(p);

    return 0;
}

