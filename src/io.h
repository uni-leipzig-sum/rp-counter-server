#ifndef IO_H
#define IO_H

typedef struct {
  const char *name;
  int32_t id;
} pin_to_id_map_t;

typedef struct {
  const char *name;
  int32_t dir;
} d_pin_direction_t;

int Analog_PinReset(int argc, char **argv, char **res, size_t *resLen);
int Analog_GetPinValue(int argc, char **argv, char **res, size_t *resLen);
int Analog_SetPinValue(int argc, char **argv, char **res, size_t *resLen);

int Digital_PinReset(int argc, char **argv, char **res, size_t *resLen);
int Digital_GetPinState(int argc, char **argv, char **res, size_t *resLen);
int Digital_SetPinState(int argc, char **argv, char **res, size_t *resLen);
int Digital_GetPinDirection(int argc, char **argv, char **res, size_t *resLen);
int Digital_SetPinDirection(int argc, char **argv, char **res, size_t *resLen);

#endif /* IO_H */
