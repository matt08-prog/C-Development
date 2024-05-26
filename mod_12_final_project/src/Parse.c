#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

__attribute__((__packed__)) struct s_DatabaseHeader {
	u_short version;
	u_short num_employees;
	u_int file_length;
};

int parseFileHeader(int fd, int *num_employees) {
	struct s_DatabaseHeader my_database = {0};

	if (read(fd, &my_database, sizeof(struct s_DatabaseHeader)) != sizeof(struct s_DatabaseHeader)) {
		perror("read");
		close(fd);
		return -1;
	}
	*num_employees = my_database.num_employees;
	close(fd);
}
