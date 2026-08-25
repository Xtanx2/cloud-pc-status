#ifndef SYSTEM_INFO_H
#define SYSTEM_INFO_H

void get_hostname(char *hostname, int size);
double get_cpu_load(void);
double get_ram_usage(void);
double get_disk_usage(void);

#endif