#ifndef RANDTIMES_H__
#define RANDTIMES_H__

#include "request.h"

/**
 * @brief Функция возвращает случайное вещественное время между границами.
 * 
 * @param min - Нижняя граница.
 * @param max - Верхняя граница.
 * @return double - Случайное время.
 */
double randtime(double min, double max);

/**
 * @brief Функция для заполнения запроса случайным временем между границами.
 * 
 * @param req - Указатель на запрос.
 * @param min - Нижняя граница.
 * @param max - Верхняя граница.
 */
void rand_req(request_t *req, double min, double max);

#endif // RANDTIMES_H__
