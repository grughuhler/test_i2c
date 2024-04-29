/* Simple i2c test program.  See README.
 *
 * SPDX: BSD 2-Clause "Simplified" License: BSD-2-Clause
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <i2c/smbus.h>

int main(void)
{
  int file;
  char *fname = "/dev/i2c-1";
  int dev_addr = 0x31;
  unsigned int reg_index;
  unsigned int data;
  int val, errors = 0;

  /* First open the correct i2c bus */
  if ((file = open(fname, O_RDWR)) < 0) {
    perror("Cannot open i2c bus");
    exit(EXIT_FAILURE);
  }

  /* Set address of i2c target to be read/written */
  if (ioctl(file, I2C_SLAVE, dev_addr) < 0) {
    perror("Cannot access slave device");
    close(file);
    exit(EXIT_FAILURE);
  }
  
  /* Test all values from 0..255 can be written to and read from
   * registers 0..3 */
  for (reg_index = 0; reg_index < 4; reg_index++) {
    for (data = 0; data < 256; data++) {

      if (i2c_smbus_write_byte_data(file, reg_index, data)) {
	perror("Write to slave failed");
      }

      val = i2c_smbus_read_byte_data(file, reg_index);
      //      printf("Val = %d\n", val);
      if (val != data) {
	printf("ERROR no match\n");
	errors += 1;
      }
    }
  }
  
  close(file);
  printf("Test complete with %d errors\n", errors);

  return EXIT_SUCCESS;
}

  
