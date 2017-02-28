#ifndef ROTULIN_H
#define ROTULIN_H 1

/**
 * @brief Initialize rotulin
 */
int rotulin_initialize(void);

/**
 * @brief Load all scripts for rotulin
 */
int rotulin_load_scripts(void);

/**
 * @brief Run rotulin service
 */
int rotulin_run(void);

/**
 * @brief Destroy rotulin
 */
int rotulin_destroy(void);

#endif // ROTULIN_H
