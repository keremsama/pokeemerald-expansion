/*
 * Add trainers using DYNAMIC_TRAINER_LEVEL(TRAINER_ID, RATIO).
 * A ratio of 100 matches the player's highest-level non-Egg Pokemon.
 * A ratio of 90 targets 90 percent of that level.
 * Dynamic trainers only scale upward; their defined levels remain the minimum.
 */
DYNAMIC_TRAINER_LEVEL(TRAINER_ROSE_2, 100)
DYNAMIC_TRAINER_LEVEL(TRAINER_CINDY_6, 94)
