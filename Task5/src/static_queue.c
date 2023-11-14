#include "static_queue.h"
#include "errs.h"
#include "randtimes.h"
#include "math.h"

void static_init(static_queue *q)
{
    q->end = q->arr + STATIC_QUEUE_SIZE;
    q->pin = q->arr;
    q->pout = q->arr;
    q->full = 0;
}

int static_add(static_queue *q, request_t *req)
{
    if (q->full)
        return ERR_QUEUE_OVERFLOW;

    if (q->pin >= q->end)
        q->pin = q->arr;

    *(q->pin) = *req;
    q->pin++;
    if (q->pin == q->pout)
        q->full = 1;
    return OK;
}

int static_pop(static_queue *q, request_t *req)
{
    if (q->pin == q->pout && !q->full)
        return ERR_EMPTY_QUEUE;
    
    if (q->pout >= q->end)
        q->pout = q->arr;

    *req = *(q->pout);
    q->pout++;
    if (q->full)
        q->full = 0;
    
    return OK;
}

void static_print(const static_queue *q)
{
    printf("Очередь: \n");
    request_t *now = q->pout;
    if (q->full)
    {
        printf("%lf\n", now->exec_time);
        now++;
    }
    for (request_t *now = q->pout; now < q->pin; now++)
    {
        printf("%lf\n", now->exec_time);
    }
}

size_t static_length(static_queue *q)
{
    if (q->pout < q->pin)
        return q->pin - q->pout;
    else if (q->pin < q->pout)
        return q->end - q->pout + q->pin - q->arr - 1;
    else if (q->full)
        return STATIC_QUEUE_SIZE;
    return 0;
}

double get_average_time(double time, static_queue *q)
{
    double sum = 0;
    size_t cnt = 0;
    if (q->pout < q->pin)
    {
        for (request_t *now = q->pout; now < q->pin; now++)
        {
            sum += time - now->crt_time;
            cnt++;
        }
    }
    else if (q->pin < q->pout || q->full)
    {
        for (request_t *now = q->pout; now < q->end; now++)
        {
            sum += time - now->crt_time;
            cnt++;
        }
        for (request_t *now = q->arr; now < q->pin; now++)
        {
            sum += time - now->crt_time;
            cnt++;
        }
    }
    if (cnt)
        return sum / cnt;
    return 0;
}

int static_sim(double t1_create_min, double t1_create_max, double t2_create_min, double t2_create_max, \
    double t1_ex_min, double t1_ex_max, double t2_ex_min, double t2_ex_max, size_t req_cnt, size_t *max_cnt, int verbose)
{
    static_queue q1, q2;
    static_init(&q1);
    static_init(&q2);
    size_t t1_done_cnt = 0;
    size_t t2_done_cnt = 0;
    size_t t1_ent_cnt = 0, t2_ent_cnt = 0;
    double t1_exec_sum = 0, t2_exec_sum = 0;
    size_t max1_cnt = 0, max2_cnt = 0;
    request_t tmp;
    // int rc;
    int now_type = 0;
    double wait_time = 0;
    double exec_time = 0;
    double time = 0;
    double start_exec_time = 0;
    double t1_time = randtime(t1_create_min, t1_create_max);
    double t2_time = randtime(t2_create_min, t2_create_max);
    int rc = OK;
    if (t1_time < t2_time)
    {
        now_type = 1;
        time = t1_time;
        t1_time += randtime(t1_create_min, t1_create_max);
        exec_time = time + randtime(t1_ex_min, t1_ex_max);
        start_exec_time = time;
    }
    else
    {
        now_type = 2;
        time = t2_time;
        t2_time += randtime(t2_create_min, t2_create_max);
        exec_time = time + randtime(t2_ex_min, t2_ex_max);
        start_exec_time = time;   
    }
    if (verbose)
        printf("----------------------------------------\n");
    while (t1_done_cnt < req_cnt)
    {
        if (exec_time < t1_time && exec_time < t2_time && now_type)
        {
            if (now_type == 1)
            {
                t1_done_cnt++;
                t1_exec_sum += exec_time - start_exec_time;
            }  
            else
            {
                t2_done_cnt++;
                t2_exec_sum += exec_time - start_exec_time;
            }
            time = exec_time;
            
            if (t1_done_cnt % 100 == 0 && verbose && now_type == 1)
            {
                printf("Статистика %zu-ой заявки:\n", t1_done_cnt);
                printf("Длина очереди заявок 1: %zu\n", static_length(&q1));
                printf("Длина очереди заявок 2: %zu\n", static_length(&q2));
                printf("Количество выполненных запросов 1: %zu\n", t1_done_cnt);
                printf("Количество выполненных запросов 2: %zu\n", t2_done_cnt);
                printf("Количество вошедших запросов 1: %zu\n", t1_ent_cnt);
                printf("Количество вошедших запросов 2: %zu\n", t2_ent_cnt);
                printf("Среднее время ожидания заявок 1: %lf\n", get_average_time(time, &q1));
                printf("Среднее время ожидания заявок 2: %lf\n", get_average_time(time, &q2));
                printf("----------------------------------------\n");

            }

            if (!static_pop(&q1, &tmp))
            {
                now_type = 1;
            }
            else if (!static_pop(&q2, &tmp))
            {
                now_type = 2;  
            }
            else
                now_type = 0;
            start_exec_time = time;
            exec_time = time + tmp.exec_time;
        }
        else if (t1_time < t2_time && (t1_time < exec_time || !now_type))
        {
            rand_req(&tmp, t1_ex_min, t1_ex_max);
            tmp.crt_time = t1_time;
            t1_ent_cnt++;
            if (max1_cnt < t1_ent_cnt - t1_done_cnt)
                max1_cnt = t1_ent_cnt - t1_done_cnt;
            if (now_type)
            {
                rc = static_add(&q1, &tmp);
                if (rc)
                    break;
            }    
            else
            {
                wait_time += t1_time - start_exec_time;
                now_type = 1;
                start_exec_time = t1_time;
                exec_time = t1_time + tmp.exec_time;
            }
            time = t1_time;
            t1_time = time + randtime(t1_create_min, t1_create_max);
        }
        else
        {
            rand_req(&tmp, t2_ex_min, t2_ex_max);
            tmp.crt_time = t2_time;
            t2_ent_cnt++;
            if (max2_cnt < t2_ent_cnt - t2_done_cnt)
                max2_cnt = t2_ent_cnt - t2_done_cnt;
            if (now_type)
            {
                rc = static_add(&q2, &tmp);
                if (rc)
                    break;
            }    
            else
            {
                wait_time += t2_time - start_exec_time;
                now_type = 2;
                start_exec_time = t1_time;
                exec_time = t2_time + tmp.exec_time;
            }
            time = t2_time;
            t2_time = time + randtime(t2_create_min, t2_create_max);
        }
    }

    if (!rc)
        *max_cnt = max1_cnt + max2_cnt;

    double av1_crt, av2_crt;
    double av1_ex, av2_ex;
    double av_res_time, av_ex_time, av_wait_time;
    double av1_ent_cnt, av2_ent_cnt, av1_done_cnt, av2_done_cnt;
    double exec_mistake, res_time_mistake, ent1_mistake, ent2_mistake;
    if (verbose && !rc)
    {
        av1_crt = (t1_create_max + t1_create_min) / 2, av2_crt = (t2_create_max + t2_create_min) / 2;
        av1_ex = (t1_ex_max + t1_ex_min) / 2, av2_ex = (t2_ex_max + t2_ex_min) / 2;
        
       
        if (av1_ex < av1_crt)
        {
            av_res_time = av1_crt * req_cnt;
            double diff = av1_crt - av1_ex;
            double cnt2 = av1_crt / av2_crt;
            double cycle2_time = cnt2 * av2_ex;
            if (cycle2_time > diff)
                cycle2_time = diff;
            
            av_wait_time = (diff - cycle2_time) * req_cnt;
            av_ex_time = av_res_time - av_wait_time;
            
            av1_ent_cnt = av_res_time / av1_crt;
            av2_ent_cnt = av_res_time / av2_crt;
            av1_done_cnt = req_cnt;
            av2_done_cnt = cycle2_time / av2_ex * req_cnt;
        }
        else
        {
            av_res_time = av1_ex * req_cnt;
            av_ex_time = av_res_time;
            av_wait_time = 0;

            av1_ent_cnt = av_res_time / av1_crt;
            av2_ent_cnt = av_res_time / av2_crt;
            av1_done_cnt = req_cnt;
            av2_done_cnt = 0;
        }

        exec_mistake = fabs((time - wait_time) / av_ex_time - 1);
        res_time_mistake = fabs(time / av_res_time - 1);
        ent1_mistake = fabs(t1_ent_cnt / av1_ent_cnt - 1);
        ent2_mistake = fabs(t2_ent_cnt / av2_ent_cnt - 1);
    }

    
        

    if (verbose && !rc)
    {
        printf("Количество выполненных запросов 1: %zu\n", t1_done_cnt);
        printf("Количество выполненных запросов 2: %zu\n", t2_done_cnt);
        printf("Количество вошедших запросов 1: %zu\n", t1_ent_cnt);
        printf("Количество вошедших запросов 2: %zu\n", t2_ent_cnt);
        printf("Среднее время выполнения заявок 1: %.2lf\n", t1_exec_sum / t1_done_cnt);
        printf("Среднее время выполнения заявок 2: %.2lf\n", t2_exec_sum / t2_done_cnt);
        printf("Общее время: %.2lf\n", time);
        printf("Время работы:%.2lf\n", time - wait_time);
        printf("Время простоя: %.2lf\n", wait_time);
        printf("\n");
        printf("Ожидаемое количество выполненных запросов 1: %.2lf\n", av1_done_cnt);
        printf("Ожидаемое количество выполненных запросов 2: %.2lf\n", av2_done_cnt);
        printf("Ожидаемое количество вошедших запросов 1: %.2lf\n", av1_ent_cnt);
        printf("Ожидаемое количество вошедших запросов 2: %.2lf\n", av2_ent_cnt);
        printf("Ожидаемое среднее время выполнения заявок 1: %.2lf\n", av1_ex);
        printf("Ожидаемое среднее время выполнения заявок 2: %.2lf\n", av2_ex);
        printf("Ожидаемое общее время: %.2lf\n", av_res_time);
        printf("Ожидаемое время простоя: %.2lf\n", av_wait_time);
        printf("Ожидаемое время работы: %.2lf\n", av_ex_time);
        printf("\n");
        printf("Погрешность общего времени: %.2lf %%\n", res_time_mistake * 100);
        printf("Погрешность времени работы: %.2lf %%\n", exec_mistake * 100);
        printf("Погрешность вошедших заявок 1: %.2lf %%\n" , ent1_mistake * 100);
        printf("Погрешность вошедших заявок 2: %.2lf %%\n", ent2_mistake * 100);
    }
    
    return rc;
}

size_t get_static_memory(size_t cnt)
{
    return sizeof(request_t) * cnt + sizeof(request_t *) * 3 + sizeof(int);
}