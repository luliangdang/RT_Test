#include <rtthread.h>

/* 定时器的控制块 */
static rt_timer_t timer1;
static rt_timer_t timer2;
static int cnt = 0;

/* 定时器1超时函数 */
static void timeout1(void *parameter)
{
    rt_kprintf("periodic timer is timeout %d\n", cnt);

    /* 运行5次后，停止周期定时器 */
    if (cnt++ >= 4)
    {
        rt_timer_stop(timer1);
        rt_kprintf("periodic timer was stopped! \n");
    }
}

/* 定时器2超时函数 */
static void timeout2(void *parameter)
{
    rt_kprintf("one shot timer is timeout\n");
}


int timer_sample(void)
{
    /* 创建定时器1  周期定时器 */
    timer1 = rt_timer_create("timer1", timeout1,
                             RT_NULL, 5,
                             RT_TIMER_FLAG_PERIODIC);

    /* 启动定时器1 */
    if (timer1 != RT_NULL) rt_timer_start(timer1);

    /* 创建定时器2 单次定时器 */
    timer2 = rt_timer_create("timer2", timeout2,
                             RT_NULL,  15,
                             RT_TIMER_FLAG_ONE_SHOT);

    /* 启动定时器2 */
    if (timer2 != RT_NULL) rt_timer_start(timer2);
    return 0;
}

/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(timer_sample, timer sample);


