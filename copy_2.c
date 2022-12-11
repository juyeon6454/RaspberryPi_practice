#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
		int n, in, out;
		char buffer[1024];

		if(argc < 0)
		{
				write(2, "Usage : copy file1 file2\n" , 25);
				return -1;
		}

		if((in=open(argv[1], O_RDONLY)) < 0) {
				perror(argv[1]);
				return -1;

		}

		if((out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) < 0){
				perror(argv[2]);
				return -1;
}

while((n=read (in, buffer, sizeof(buffer))) > 0)
		write(out, buffer, n);

		close(out);
		close(in);

		return 0;
		}

						
