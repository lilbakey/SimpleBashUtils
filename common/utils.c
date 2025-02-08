#include "utils.h"

void error_message(char *message) {
  perror(message);
  exit(EXIT_FAILURE);
}
