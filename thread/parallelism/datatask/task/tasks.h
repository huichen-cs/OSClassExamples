#ifndef PART_SUM_H
#define PART_SUM_H

/* threads do these works */
void *find_min(void *param); 
void *find_max(void *param);
void *compute_sum(void *param);
void *compute_average(void *param);

#endif
