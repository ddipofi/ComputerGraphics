

//number 1a
void SysTick_Wait1ms()
{
    NVIC_ST_RELOAD = 50000;
    NVIC_ST_CURRENT = 0;

    while (NVIC_ST_CTRL & 0x00010000 == 0) {}
}

void SysTick_Wait1ms(void)
{
    volatile uint32_t elapsedTime;
    uint32_t startTime = NVIC_ST_CURRENT_R;

    do
    {
        elapsedTime = (startTime - NVIC_ST_CURRENT_R) & 0x00FFFFFF;
    }
    while (elapsedTime <= 50000);
}

//number 1b
void SysTick_Interupt100us(void)
{
    NVIC_ST_CTRL_R = 0;
    NVIC_ST_RELOAD_R = 7999;
    NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x00FFFFFF) | 0x20000000;
    NVIC_ST_CURRENT_R = 0;
    NVIC_ST_CTRL_R = 0x07;
    EnableInterrupts();
}

//number 3
#define SIZE 64

struct Student
{
    unsigned long id;
    unsigned long score;
    unsigned char grade; // you will enter ‘P’ or ‘F’
};

typedef struct Student STyp;

unsigned long Grades(STyp class[SIZE])
{
    unsigned long classAverage = 0;

    for (int i = 0; i < SIZE; i++)
    {
        classAverage += class[i].score;

        //part a
        if (class[i].score < 75)
        {
            //F
            class[i].grade = 0x46;
        }
        else
        {
            //P
            class[i].grade = 0x50;
        }
    }

    //part b
    return classAverage /= SIZE;
}

//number 4
Const struct State
{
    uint32_t out;
    uint32_t wait;
    uint32_t next[2];
};

typedef const struct State State_t;
uint32_t s;

#define Check 0
#define PaceIt 1

STyp FSM[2] =
{
{0, 990, { Wait, Check}},
{1, 10, { PaceIt, Check}}
};

//OR!!!!!!!!!!!

#define Beating 0
#define Wait 1
#define Pace 2
STyp FSM[3] =
{
{0, 10, { Wait, Beating}},
{0, 980, { Pace, Beating}},
{1, 10, {Beating, Beating}}
};

void main(void) {

    PORTB_Init();
    SysTick_Init();
    s = Check;   //Specify the initial state here

    while (1) {
        GPIO_PORTB_DATA_R = FSM[s].out;
        SysTick_Wait1ms(FSM[s].wait);
        Input = (GPIO_PORTB_DATA_R & 0x02) >> 1;
        s = FSM[s].next[Input];
    }
}
