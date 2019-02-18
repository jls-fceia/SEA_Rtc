#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/rtc.h>

	/*
	 *	      Sistemas Embebidos Avanzados
	 *	   Ejemplo de uso de un device driver
	 *	          S.O. Linux (Ubuntu)
	 *	Dispositivo: Reloj de tiempo real (/dev/rtc
	 */

int main( int argc, char *argv[]){
    char fecha_hora[256];
    unsigned long irq_frec;
    int fd;
    struct rtc_time tm;

	printf("\nAcceso al dispositivo RTC via ioctl()\n");
/*
 * Leer fecha y hora del RTC 
 */
	errno = 0;
  	if ((fd = open("/dev/rtc", O_RDONLY, S_IREAD)) < 0){
		printf("Error: no se puede abrir /dev/rtc: %s\n", strerror(errno));
		return -1;
	} else {
		if ((ioctl(fd, RTC_RD_TIME, &tm)) != 0){
			printf("Error: ioctl sobre /dev/rtc: %s\n", strerror(errno));
			close(fd);
			return -1;
		} else {
				printf("Hora: %02d:%02d:%02d\tfecha: %02d/%02d/%02d\n", tm.tm_hour,
				tm.tm_min, tm.tm_sec, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
			}
	}

/*
 * Leer el numero de IRQ por segundo generadas por el RTC usando ioctl()
 */
	
	if (ioctl(fd, RTC_IRQP_READ, &irq_frec) != 0){
		printf("Error: ioctl sobre /dev/rtc: %s\n", strerror(errno));
		close(fd);		
		return -1;
	} else
		printf("\nInterrupciones por segundo del RTC: %ld\n", irq_frec);

	close(fd);
	return 0;
}
