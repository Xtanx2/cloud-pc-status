#ifndef CLOUD_H
#define CLOUD_H

void upload_status(
    const char *hostname,
    double cpu,
    double ram,
    double disk,
    int health_score,
    const char *health_status
);

#endif