#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct date
{
    int day;
} DATE;

typedef struct goals_steps
{

    int achieved_steps;
    int total_steps;
    int complete;
    DATE date;
    struct goals_steps *next;

} GOALS_S;

typedef struct goals_hrs
{
    int achieved_hrs;
    int total_hrs;
    int complete;
    DATE date;
    struct goals_hrs *next;

} GOALS_H;

typedef struct workout_log
{
    DATE date;
    char workout_name[30];
    int hrs;
    struct workout_log *next;

} LOG;

typedef struct list
{
    GOALS_H *head_hr;
    GOALS_S *head_st;
} QUEUE;

typedef struct nutrition
{
    char breakfast[30];
    char lunch[30];
    char dinner[30];
    float calories;
    DATE date;
    struct nutrition *next;

} FOOD;

typedef struct health_metric
{
    float curr_weight;
    float curr_height;
    char gender;
    int age;
    char name[20];
} HM;

typedef struct tracking_parameters
{
    int height;
    int weight;
    int steps;
    int water;
    int calories;
    DATE date;
    struct tracking_parameters *next;

} TRACK;

typedef struct stack
{
    LOG *head_log;
    FOOD *head_food;
    TRACK *head_track;

} STACK;

void init_date(DATE *dt)
{
    dt->day = 0;
}

void init_queue(QUEUE *pl)
{
    pl->head_hr = NULL;
    pl->head_st = NULL;
}

void init_stack(STACK *pq)
{
    pq->head_log = NULL;
    pq->head_food = NULL;
    pq->head_track = NULL;
}

void load_goals(QUEUE *pq, int hours, int step)
{
    // steps goals
    GOALS_H *new1 = malloc(sizeof(GOALS_H));
    new1->total_hrs = hours;
    new1->achieved_hrs = 0;
    new1->complete = 0;
    new1->date.day = 0;
    new1->next = pq->head_hr;
    pq->head_hr = new1;
    // hrs->next=NULL;

    // workout hrs goals
    GOALS_S *new2 = malloc(sizeof(GOALS_S));
    new2->total_steps = step;
    new2->achieved_steps = 0;
    new2->complete = 0;
    new2->date.day = 0;
    new2->next = pq->head_st;
    pq->head_st = new2;
}
//Tracks food for a particular day by considering Breakfast Lunch and Dinner
void nutrition_info(STACK *ps, int day)
{
    char breakfast[20], lunch[20], dinner[20];
    float calories;
    printf("What did you have for breakfast?: ");
    scanf("%s", breakfast);
    printf("What did you have for lunch?: ");
    scanf("%s", lunch);
    printf("What did you have for dinner?: ");
    scanf("%s", dinner);
    printf("How many calories did you consume?: ");
    scanf("%f", &calories);

    FOOD *nn = malloc(sizeof(FOOD));
    strcpy(nn->breakfast, breakfast);
    strcpy(nn->lunch, lunch);
    strcpy(nn->dinner, dinner);
    nn->date.day = day; 
    nn->calories = calories;

    nn->next = ps->head_food;
    ps->head_food = nn;
}
//Adds workout to the beginning of the stack
void add_workout(STACK *pq, int day, QUEUE *que)
{
    int wo;
    printf("\nChoose a Workout from the list \n\t1. Walking \n\t2. Running \n\t3. Cycling \n\t4. Yoga \n\t5. Tennis \n\t6. Others\n\n~");
    scanf("%d", &wo);

    LOG *x = malloc(sizeof(LOG));
    switch (wo)
    {
    case 1:
        strcpy(x->workout_name, "Walking");
        break;

    case 2:
        strcpy(x->workout_name, "Running");
        break;

    case 3:
        strcpy(x->workout_name, "Cycling");
        break;

    case 4:
        strcpy(x->workout_name, "Yoga");
        break;

    case 5:
        strcpy(x->workout_name, "Tennis");
        break;

    case 6:
        strcpy(x->workout_name, "Others");
        break;

    default:
        printf("Invalid Input! \n\n");
        return;
        break;
    }

    int hrs;
    printf("Enter hrs excercised - ");
    scanf("%d", &hrs);
    x->hrs = hrs;
    x->next = NULL;

    x->date.day = day;

    LOG *p = NULL;
    if (pq->head_log != NULL)
    {
        x->next = pq->head_log;
        pq->head_log = x;
    }
    else
    {
        pq->head_log = x;
    }

    GOALS_H *q = que->head_hr;
    for (; q != NULL; q = q->next)
    {
        if (q->date.day == day)
        {
            q->achieved_hrs += hrs;
        }
    }
}
//Adds information to the health matric
void data(HM *hm)
{
    printf("\nPlease enter your age - ");
    scanf("%d", &hm->age);
    getchar();
    printf("Please enter your Gender (F/M) - ");
    scanf("%c", &hm->gender);
    printf("Please enter your Weight(in kg) - ");
    scanf("%f", &hm->curr_weight);
    printf("Please enter your Height(in cm) - ");
    scanf("%f", &hm->curr_height);
    printf("\n");
}
//Anlyzez the Data according to the User Input and checks BMI and prints the apropriate result.
void analyze(STACK *ps, HM *ph, QUEUE *pq, int day)
{

    printf("\n\nHere is your analysis: ");
    double curr_bmi = (ph->curr_weight) / ((ph->curr_height / 100) * (ph->curr_height / 100));
    printf("Your BMI: %lf\n", curr_bmi);
    if (curr_bmi < 18.5)
    {
        printf("You're underweight range!\n\n");
    }
    else if (18.5 < curr_bmi < 24.9)
    {
        printf("You're in the healthy weight range !\n\n");
    }
    else if (25 < curr_bmi < 29.9)
    {
        printf("You're in the overweight range !\n\n");
    }
    else if (30 < curr_bmi)
    {
        printf("You're in the obese range !\n\n");
    }

    GOALS_H *p = pq->head_hr;
    GOALS_S *q = pq->head_st;
    int max1 = 0, max2 = 0;
    int avg1 = 0, avg2 = 0;
    int day1 = 0, day2 = 0;
    for (; p != NULL; p = p->next)
    {
        avg1 += p->achieved_hrs;
        if (p->achieved_hrs > max1)
        {
            max1 = p->achieved_hrs;
            day1 = p->date.day;
        }
    }
    printf("You worked out the most on day %d!\n", day1);
    for (; q != NULL; q = q->next)
    {
        avg2 += q->achieved_steps;
        if (q->achieved_steps > max2)
        {
            max2 = q->achieved_steps;
            day2 = q->date.day;
        }
    }
    printf("You drank the most on day %d!\n\n", day2);
}
//Keeps a track on yor health and fitness related information.
void tracking(int day, STACK *pl, QUEUE *pq)
{
    int wei, gow, hei, st, calo;
    printf("Enter your Weight(in kg) - ");
    scanf("%d", &wei);
    printf("Enter your Height(in cm) - ");
    scanf("%d", &hei);
    printf("Enter number of glasses of water - ");
    scanf("%d", &gow);
    printf("Enter number of Steps - ");
    scanf("%d", &st);
    printf("Enter Calories - ");
    scanf("%d", &calo);
    TRACK *nn = malloc(sizeof(TRACK));
    nn->weight = wei;
    nn->height = hei;
    nn->water = gow;
    nn->steps = st;
    nn->calories = calo;
    if (pl->head_track == NULL)
    {
        pl->head_track = nn;
    }
    else
    {
        nn->next = pl->head_track;
        pl->head_track = nn;
    }

    GOALS_S *q = pq->head_st;
    for (; q != NULL; q = q->next)
    {
        if (q->date.day == day)
        {
            q->achieved_steps += nn->steps;
        }
    }
}
//Displays Track function
void displayTrack(STACK *pl)
{
    if (pl->head_track == NULL)
        printf("Empty List\n");
    else
    {
        TRACK *p = pl->head_track;

        while (p != NULL)
        {
            printf("Weight : %d\n", p->weight);
            printf("Height : %d\n", p->height);
            printf("Number of Steps : %d\n", p->steps);
            printf("Glasses of Water : %d\n", p->water);
            printf("Calories : %d\n", p->calories);
            p = p->next;
        }
        printf("\n");
    }
}
//Displays workout
void display_workout(STACK *pq)
{
    LOG *x;
    
    if (pq->head_log == NULL)
    {
        printf("No Workouts Done");
        return;
    }

    int day = 0;
    for (x = pq->head_log; x != NULL; x = x->next)
    {
        if (day != x->date.day)
        {
            printf("\n\t~~~Day - %d~~~\n", x->date.day);
            day = x->date.day;
        }
        printf("Workout Name - %s\n", x->workout_name);
        printf("Hours - %d\n\n", x->hrs);
    }

}
//Displays User Info
void user_info(HM *hm, int day, QUEUE *pq)
{
    printf("Hello %s!\n", hm->name);
    printf("Age: %d\n", hm->age);
    printf("Gender: %c\n", hm->gender);
    printf("Weight: %f KG\n", hm->curr_weight);
    printf("Height: %f cm\n", hm->curr_height);

    GOALS_H *p = pq->head_hr;
    GOALS_S *q = pq->head_st;

    for (; p != NULL; p = p->next)
    {
        if (p->date.day == day)
        {
            if (p->complete)
            {
                printf("Goal (workout hours) Completed for today!\n");
                break;
            }
            else
            {
                printf("Goal (workout hours) for today not completed\n");
                break;
            }
        }
    }

    for (; q != NULL; q = q->next)
    {
        if (q->date.day == day)
        {
            if (q->complete)
            {
                printf("Goal (steps) Completed for today!\n");
                break;
            }
            else
            {
                printf("Goal (steps) for today not completed\n");
                break;
            }
        }
    }
}
// prints the total hrs excercised and total steps for the day
void goal_complete(QUEUE *pq, int day)
{
    GOALS_H *p = pq->head_hr;
    GOALS_S *q = pq->head_st;

    for (; p != NULL; p = p->next)
    {
        if (p->date.day == day)
        {
            printf("Achieved Hrs - %d\n", p->achieved_hrs);
        }
    }

    for (; q != NULL; q = q->next)
    {
        if (q->date.day == day)
        {
            printf("Achieved Steps - %d\n", q->achieved_steps);
        }
        
    }
}
// displays nutrition
void displayNutrition(STACK *ps)
{
    if (ps->head_food == NULL)
        printf("Empty Stack\n");
    else
    {
        FOOD *p = ps->head_food;

        while (p != NULL)
        {
            printf("Breakfast : %s\n", p->breakfast);
            printf("Lunch : %s\n", p->lunch);
            printf("Dinner : %s\n", p->dinner);
            printf("Calories : %f\n", p->calories);
            p = p->next;
        }
        printf("\n");
    }
}

int main()
{
    char name[20];
    QUEUE qobj;
    STACK obj;
    HM hobj;

    init_stack(&obj);
    init_queue(&qobj);
    // init_hm(&hobj);

    printf("Please enter your name - ");
    scanf("%s", name);
    strcpy(hobj.name, name);

    printf("\n\n\t\t-------------------------\n\t\t\tWelcome %s !!\n", name);
    data(&hobj);

    int level;
    printf("\nChoose Difficulty Level - \n1.Beginner \n2.Intermidiate \n3.Advanced\n ~");
    scanf("%d", &level);

    switch (level)
    {
    case 1:
        printf("Here in beginner");
        printf("\nYour goal is to achieve 5K steps daily!\n");
        printf("\nYour goal is to achieve 1 hour of workout daily!\n");
        load_goals(&qobj, 1, 5000);
        break;

    case 2:
        printf("Here in Intermidiate");
        printf("\nYour goal is to achieve 10K steps daily!\n");
        printf("\nYour goal is to achieve 2 hour of workout daily!\n");
        load_goals(&qobj, 2, 10000);
        break;

    case 3:
        printf("Here in Advanced");
        printf("\nYour goal is to achieve 15K steps daily!\n");
        printf("\nYour goal is to achieve 3 hour of workout daily!\n");
        load_goals(&qobj, 3, 15000);
        break;

    default:
        break;
    }

    int day = 1;
    qobj.head_hr = malloc(sizeof(GOALS_H));
    qobj.head_hr->date.day = 1;
    qobj.head_hr->next = NULL;
    qobj.head_st = malloc(sizeof(GOALS_S));
    qobj.head_st->date.day = 1;
    qobj.head_st->next = NULL;

    printf("\n\t\t~~~~~~~~~~Welcome To Day 1~~~~~~~~~~\n");
    int choice = 0;
    while (choice < 7)
    {
        printf("\nChoose -\n1.Input workout log \n2.Track Parameters \n3.Nutrition info \n4.Analyse \n5.Display Info \n6.Next Day \n7.Exit\n\n Enter choice -");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("\nWorkout Log Input\n\n");
            add_workout(&obj, day, &qobj);
            break;

        case 2:
            printf("\nTrack\n");
            tracking(day, &obj, &qobj);
            break;

        case 3:
            printf("\nYour Nutition Info\n");
            nutrition_info(&obj,day);
            break;

        case 4:
            printf("\nAnalyse\n");
            analyze(&obj, &hobj, &qobj, day);
            break;

        case 5:
            printf("\nDisplay\n");

            int dis;
            printf("1. Workout Log \n2. Nutrition \n3. Tracked Parameters \n4. User Info\n\n~"); scanf("%d", &dis);

            switch (dis)
            {
            case 1:
                display_workout(&obj);
                break;

            case 2:
                displayNutrition(&obj);
                break;

            case 3:
                displayTrack(&obj);
                break;

            case 4:
                user_info(&hobj, day, &qobj);
                break;

            default:
                break;
            }
            break;

        case 6:
            goal_complete(&qobj, day);

            if (day < 7)
            {
                day++;

                GOALS_H *ght;
                GOALS_S *gst;

                GOALS_H *gh = malloc(sizeof(GOALS_H));
                gh->date.day = day;
                gh->next = NULL;
                for (ght = qobj.head_hr; ght->next != NULL; ght = ght->next);
                ght->next = gh;

                GOALS_S *gs = malloc(sizeof(GOALS_S));
                gs->date.day = day;
                gs->next = NULL;
                for (gst = qobj.head_st; gst->next != NULL; gst = gst->next);
                gst->next = gs;

                if (level == 1)
                {
                    gh->total_hrs = 1;
                    gh->achieved_hrs = 0;
                    gs->total_steps = 5000;
                    gs->achieved_steps = 0;
                }
                else if (level == 2)
                {
                    gh->total_hrs = 3;
                    gh->achieved_hrs = 0;
                    gs->total_steps = 10000;
                    gs->achieved_steps = 0;
                }
                else if (level == 3)
                {
                    gh->total_hrs = 5;
                    gh->achieved_hrs = 0;
                    gs->total_steps = 15000;
                    gs->achieved_steps = 0;
                }
                

                printf("\t\t~~~~~~~~~~Welcome To Day %d~~~~~~~~~~\n", day);
            }
            else
            {
                printf("\nLast Day\n");
                printf("Free Trial Over \nExiting Program");
                choice = 7;
            }

        default:
            break;
        }
    }
}
