#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<stdbool.h>
#include<time.h>

static void stopwatch() {
    int hr,min,sec;
    scanf("%d:%d:%d",&hr,&min,&sec);
    system("cls");

    while (1) {
        printf("%02d:%02d:%02d\n",hr,min,sec);
        fflush(stdout);
        Sleep(1000);
        system("cls");

        sec--;
        if (sec<0) {
            if (min>0) {
                sec+=60;
                min--;
            }
            else if (min==0) {
                if (hr>0) {
                    min--;
                    min+=60;
                    hr--;
                    sec+=60;
                }
                else if (hr==0) {
                    printf("Time is over!");
                    getch();
                    break;
                }
            }
        }
        if (kbhit()) {
            char dummy= getch();
            printf("%02d:%02d:%02d\n",hr,min,sec);
            printf("Paused!\nWant to continue? (y or n):  ");
            fflush(stdout);
            char choice=getche();
            if (choice=='y' || choice=='Y') {
                system("cls");
                printf("Resuming....\n");
                fflush(stdout);
                continue;
            }
            else if (choice=='n' || choice=='N') {
                system("cls");
                printf("Exiting...\n");
                fflush(stdout);
                Sleep(1000);
                break;
            }
            else {
                system("cls");
                printf("Invalid option. Resuming...\n");
                fflush(stdout);
            }
        }
    }
}

bool is_leap_year(int year) {
    if (year%400==0)
        return true;
    if (year%4==0 && year%100!=0) {
        return true;
    }
    return false;
}

int daycode(int year) {
    return (year+(int)((year-1.0)/4)-(int)((year-1.0)/100)+(int)((year-1.0)/400))%7;
}

static void calender() {
    int y;
    scanf("%d",&y);
    system("cls");
    char month[12][20]={"January","February","March","April","May","June","July","August",
        "September","October","November","December"};
    int days_in_month[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    if (is_leap_year(y)) {
        days_in_month[1]++;
    }
    int dc_init=daycode(y);
    int dc=dc_init;
    for (int i=0; i<12; i++) {
        printf("%s\n",month[i]);
        printf("---------------------------\n");
        printf("Sun Mon Tue Wed Thu Fri Sat\n");
        for (int j=0; j<4*dc; j++) {
            printf(" ");
        }
        for (int j=0; j<days_in_month[i]; j++) {
            printf("%3d ",j+1);
            dc++;
            if (dc==7) {
                dc=0;
                printf("\n");
            }
        }
        printf("\n\n");
    }
    getch();
}

static void running_clock() {
    char month[12][20]={"January","February","March","April","May","June","July","August","September",
        "October","November","December"};
    char week[7][20]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
    while (1) {
        time_t raw;
        time(&raw);
        struct tm *t;
        t=localtime(&raw);
        int h,m,s,mo,md,wd,y;
        h=t->tm_hour;
        m=t->tm_min;
        s=t->tm_sec;
        mo=t->tm_mon;
        md=t->tm_mday;
        wd=t->tm_wday;
        y=t->tm_year;
        printf("%02d:%02d:%02d\n",h,m,s);
        printf("%02d %s, %d (%s)",md,month[mo],y+1900,week[wd]);
        fflush(stdout);
        Sleep(1000);
        system("cls");
    }
    // getch();
}

static void timer() {
    int h,m,s;
    h=m=s=0;
    while (1) {
        printf("%02d:%02d:%02d",h,m,s);
        Sleep(1000);
        system("cls");
        s++;
        if (s==60) {
            s=0;
            m++;
            if (m==60) {
                m=0;
                h++;
            }
        }
        if (kbhit()) {
            char dummy= getch();
            printf("%02d:%02d:%02d\n",h,m,s);
            printf("Paused!\nWant to continue? (y or n):  ");
            fflush(stdout);
            char choice=getche();
            if (choice=='y' || choice=='Y') {
                system("cls");
                printf("Resuming....\n");
                fflush(stdout);
                continue;
            }
            else if (choice=='n' || choice=='N') {
                system("cls");
                printf("Exiting...\n");
                fflush(stdout);
                Sleep(1000);
                break;
            }
            else {
                system("cls");
                printf("Invalid option. Resuming...\n");
                fflush(stdout);
            }
        }
    }
}

static void modify_time(long long t, int *ptr) {
    int yr,week,day,hr,min,sec;
    yr=t/(365*86400);
    t%=(365*86400);
    week=t/(7*86400);
    t%=(7*86400);
    day=t/86400;
    t%=86400;
    hr=t/3600;
    t%=3600;
    min=t/60;
    t%=60;
    sec=t;
    // printf("%d %d %d %d %d %d",yr,week,day,hr,min,sec);
    ptr[0]=yr;
    ptr[1]=week;
    ptr[2]=day;
    ptr[3]=hr;
    ptr[4]=min;
    ptr[5]=sec;
}

static void change(char *string) {
    int f,l;
    int n=strlen(string);
    for (int i=0; i<n; i++) {
        if (string[i]!=' ' && string[i]!='\t' && string[i]!='\n') {
            f=i;
            break;
        }
    }
    for (int i=n-1; i>=0; i--) {
        if (string[i]!=' ' && string[i]!='\t' && string[i]!='\n') {
            l=i;
            break;
        }
    }
    char new[50];
    for (int i=f; i<=l; i++) {
        if (string[i]>=65 && string[i]<=90) {
            string[i]+=32;
        }
        new[i-f]=string[i];
    }
    new[l-f+1]='\0';
    n=strlen(new);
    for (int i=0; i<=n; i++) {
        string[i]=new[i];
    }
    // printf("%s",string);
}

static void print_format(FILE *fp,int *ptr,char *str) {
    int idx=-1;
    for (int i=0; i<6; i++) {
        if (ptr[i]!=0) {
            idx=i;
            break;
        }
    }
    if (idx==0) {
        fprintf(fp,"%s - %d year %d week %d day %d hour %d min %d sec\n",
            str,ptr[0],ptr[1],ptr[2],ptr[3],ptr[4],ptr[5]);
    }
    else if (idx==1) {
        fprintf(fp,"%s - %d week %d day %d hour %d min %d sec\n",
            str,ptr[1],ptr[2],ptr[3],ptr[4],ptr[5]);
    }
    else if (idx==2) {
        fprintf(fp,"%s - %d day %d hour %d min %d sec\n",str,ptr[2],ptr[3],ptr[4],ptr[5]);
    }
    else if (idx==3) {
        fprintf(fp,"%s - %d hour %d min %d sec\n",str,ptr[3],ptr[4],ptr[5]);
    }
    else if (idx==4) {
        fprintf(fp,"%s - %d min %d sec\n",str,ptr[4],ptr[5]);
    }
    else if (idx==5) {
        fprintf(fp,"%s - %d sec\n",str,ptr[5]);
    }
}

static void time_tracker(FILE *fp) {
    char **list=NULL;
    long long *tot_time=NULL;
    int n=0;
        while (1) {
        int idx=-1;
        printf("Your task right now (or type 'exit' to finish) :  ");
        char *str=malloc(30);
        if (!str) {
            return;
        }
        fgets(str,30,stdin);
        str[strcspn(str,"\n")]='\0';
        if (strcmp(str,"exit") == 0) {
            free(str);
            break;
        }
        change(str);
        printf("\n");

        if (n==0) {
            for (int i=0; i<n; i++) {
                if (!strcmp(list[i],str)) {

                }
                else {
                    n++;
                }
            }
            n++;
        }
        else {
            int f=0;
            for (int i=0; i<n; i++) {
                if (!strcmp(list[i],str)) {
                    idx=i;
                    f=1;
                    break;
                }
            }
            if (!f)
                n++;
        }

        if (idx==-1) {
            idx=n-1;
            char **temp_list=realloc(list,n*sizeof(char*));
            long long *temp_time=realloc(tot_time,n*sizeof(long long));

            if (!temp_list || !temp_time) {
                free(str);
                return;
            }

            list=temp_list;
            tot_time=temp_time;
            tot_time[idx]=0;
            list[n-1]= malloc(30);
        }
        strcpy(list[idx],str);

        // long long start,end;
        // time(&start);

        int h,m,s;
        h=m=s=0;
        while (1) {
            printf("%02d:%02d:%02d",h,m,s);
            Sleep(1000);
            system("cls");
            s++;
            if (s==60) {
                s=0;
                m++;
                if (m==60) {
                    m=0;
                    h++;
                }
            }
            if (kbhit()) {
                char dummy= getch();
                // long long pause,resume;
                // time(&pause);
                printf("%02d:%02d:%02d\n",h,m,s);
                printf("Paused!\nWant to continue the task? (y or n):  ");
                fflush(stdout);
                char choice=getche();
                if (choice=='y' || choice=='Y') {
                    // time(&resume);
                    system("cls");
                    printf("Resuming....\n");
                    fflush(stdout);
                    continue;
                }
                else if (choice=='n' || choice=='N') {
                    // time(&resume);
                    // time(&end);
                    system("cls");
                    printf("Exiting...\n");
                    fflush(stdout);
                    Sleep(1000);
                    system("cls");
                    tot_time[idx]+=60*h+60*m+s;
                    // printf("%lld\n",tot_time[idx]);
                    break;
                }
                else {
                    // time(&resume);
                    system("cls");
                    printf("Invalid option. Resuming...\n");
                    Sleep(1000);
                    system("cls");
                    fflush(stdout);
                }
            }
        }
        free(str);
    }

    for (int i=0; i<n; i++) {
        printf("%s %lld\n",list[i],tot_time[i]);
        int *mthd=malloc(6*sizeof(int));
        modify_time(tot_time[i],mthd);
        print_format(fp,mthd,list[i]);
    }
    free(tot_time);
    free(list);
}

static void make_date_format(long long t,char *str) {
    char month[12][20]={"January","February","March","April","May","June","July","August","September",
        "October","November","December"};
    char week[7][20]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
    struct tm *ts;
    ts=localtime(&t);
    int h,m,s,mo,md,wd,y;
    h=ts->tm_hour;
    m=ts->tm_min;
    s=ts->tm_sec;
    mo=ts->tm_mon;
    md=ts->tm_mday;
    wd=ts->tm_wday;
    y=ts->tm_year;
    char tmp[100];
    sprintf(tmp,"%02d %s %d, %02d:%02d:%02d",md,month[mo],y+1900,h,m,s);
    strcpy(str,tmp);
}

static void activity_log(FILE *fp) {
    char **list=NULL;
    long long *tot_time=NULL;
    int n=0;
        while (1) {
        printf("Your task right now (or type 'exit' to finish) :  ");
        char *str=malloc(30);
        if (!str) {
            return;
        }
        fgets(str,30,stdin);
        str[strcspn(str,"\n")]='\0';
        if (strcmp(str,"exit") == 0) {
            free(str);
            break;
        }

        char *fmt=malloc(100);
        if (!fmt) {
            free(str);
            return;
        }
        long long start;
        time(&start);
        make_date_format(start,fmt);
        fprintf(fp,"%s\n",str);
        fprintf(fp,"----------------------------------\n");
        fprintf(fp,"Start-   %s\n",fmt);

        change(str);
        printf("\n");

        // if (n==0) {
        //     for (int i=0; i<n; i++) {
        //         if (!strcmp(list[i],str)) {
        //
        //         }
        //         else {
        //             n++;
        //         }
        //     }
        //     n++;
        // }
        // else {
        //     int f=0;
        //     for (int i=0; i<n; i++) {
        //         if (!strcmp(list[i],str)) {
        //             f=1;
        //             break;
        //         }
        //     }
        //     if (!f)
        //         n++;
        // }
        n++;

        char **temp_list=realloc(list,n*sizeof(char*));
        long long *temp_time=realloc(tot_time,n*sizeof(long long));

        if (!temp_list || !temp_time) {
            free(str);
            return;
        }

        list=temp_list;
        tot_time=temp_time;
        tot_time[n-1]=0;
        list[n-1]= malloc(30);
        strcpy(list[n-1],str);

        // long long start,end;
        // time(&start);

        int h,m,s;
        h=m=s=0;
        while (1) {
            printf("%02d:%02d:%02d",h,m,s);
            Sleep(1000);
            system("cls");
            s++;
            if (s==60) {
                s=0;
                m++;
                if (m==60) {
                    m=0;
                    h++;
                }
            }
            if (kbhit()) {
                char dummy= getch();
                long long pause,resume;
                time(&pause);
                printf("%02d:%02d:%02d\n",h,m,s);
                make_date_format(pause,fmt);
                fprintf(fp,"Paused-  %s\n",fmt);
                printf("Paused!\nWant to continue the task? (y or n):  ");
                fflush(stdout);
                char choice=getche();
                if (choice=='y' || choice=='Y') {
                    system("cls");
                    printf("Resuming....\n");
                    fflush(stdout);
                    Sleep(1000);
                    time(&resume);
                    fprintf(fp,"Resumed- %s\n",fmt);
                    continue;
                }
                else if (choice=='n' || choice=='N') {
                    // time(&resume);
                    // time(&end);
                    long long end;
                    time(&end);
                    make_date_format(end,fmt);
                    fprintf(fp,"End-     %s\n\n\n",fmt);
                    system("cls");
                    printf("Exiting...\n");
                    fflush(stdout);
                    Sleep(1000);
                    system("cls");
                    tot_time[n-1]+=60*h+60*m+s;
                    // printf("%lld\n",tot_time[idx]);
                    break;
                }
                else {
                    time(&resume);
                    fprintf(fp,"Resumed- %s\n",fmt);
                    system("cls");
                    printf("Invalid option. Resuming...\n");
                    Sleep(1000);
                    system("cls");
                    fflush(stdout);
                }
            }
        }
        free(str);
    }

    // for (int i=0; i<n; i++) {
    //     printf("%s %lld\n",list[i],tot_time[i]);
    //     int *mthd=malloc(6*sizeof(int));
    //     modify_time(tot_time[i],mthd);
    //     print_format(fp,mthd,list[i]);
    // }
    for (int i=0; i<n; i++) {
        printf("%s %lld\n",list[i],tot_time[i]);
        int *mthd=malloc(6*sizeof(int));
        modify_time(tot_time[i],mthd);
        print_format(fp,mthd,list[i]);
    }

    free(tot_time);
    free(list);
}

int main() {
    // stopwatch();
    // calender();
    // running_clock();
    // timer();
    FILE *fp=fopen("log.txt","w");
    if (!fp) {
        return 1;
    }
    // time_tracker(fp);
    // char str[50]="  Chess kheLmu  ";
    // change(str);
    // getch();
    // modify_time(4564584);
    activity_log(fp);
    fclose(fp);
    getch();
}