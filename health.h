#ifndef HEALTH_H
#define HEALTH_H

int get_health_score(double cpu, double ram, double disk);
const char *get_health_status(int score);

#endif