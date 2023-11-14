#ifndef REQUEST_H__
#define REQUEST_H__

typedef struct request_t request_t;

/// Структура заявки
struct request_t
{
    double exec_time; /// Время, требуемое для выполнения заявки
    double crt_time; /// Время создания заявки
};


#endif // REQUEST_H__
