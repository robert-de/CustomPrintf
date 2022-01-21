#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <math.h>

static int write_stdout(const char *token, int length)
{
	int rc;
	int bytes_written = 0;

	do {
		rc = write(1, token + bytes_written, length - bytes_written);
		if (rc < 0)
			return rc;

		bytes_written += rc;
	} while (bytes_written < length);

	return bytes_written;
}

//%d	%u		%x		%c		%s	-- specificatori

int digit_counter(int n) {
	int count = 0;
	while( n ) {
		n/=10;
		count++;
	}
	return count;
}


int digit_counter_u(unsigned int n) {
	int count = 0;
	while( n > 0 ) {
		n/=10;
		count++;
	}
	return count;
}

int hexa_counter(unsigned int n) {
	int count = 0;
	while( n > 0 ) {
		n/=16;
		count++;
	}
	return count;
}

char *int_to_string (int n) {
	int neg = 0;
	if (n < 0) {
		neg = 1;
	}

	int count = digit_counter(n);
	int size = count;
	char *res = (char*) calloc((count+2)*sizeof(char),1);
	
	if (n == 0) {
		res[0] = '0';
		return res;
	} 

	while( n ) {
		res[--count] = abs(n % 10) + '0';
		n /= 10;
	}

	if ( neg ) {
		for (int i=strlen(res); i>0; i--)
			res[i] = res[i-1];

		res[0] = '-';
		res[size+1] = '\0';
	}
	
	return res;
}

char *uint_to_string(unsigned int n) {
	int count = digit_counter_u(n);
	char *res = (char*) calloc(count+1,1);

	if (n == 0) {
		res[0] = '0';
		return res;
	} 

	while( n > 0 ) {
		res[--count] = n % 10 + '0';
		n /= 10;
	}

	return res;
}

char *int_to_hexstring (unsigned int n) {
	char v[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
	int count = hexa_counter(n);
	char *string = (char*) calloc(count + 1,1);
	string[count] = '\0';

	while( n > 0 ) {
		string[--count] = v[n%16];
		n/=16;
	}
	
	return string;
}



int iocla_printf(const char *format, ...)
{
	va_list args;
	char *tempstr;
	int length = 0;
	int i;
	int d;
	unsigned int u;

	char *c = (char*) malloc(2);
	c[1] = '\0';

	char *s;
	
	va_start(args, format);
		
	for (i=0; i<strlen(format); i++) {
		if(format[i] == '%') {
			if (format[i+1] == 'd') {
				d = va_arg(args, int);
				tempstr = int_to_string(d);
				write_stdout(tempstr, strlen(tempstr));
				length += strlen(tempstr);
				i++;
			}
			else if (format[i+1] == 'u') {
				u = va_arg(args, unsigned int);
				tempstr = uint_to_string(u);
				write_stdout(tempstr, strlen(tempstr));
				length += strlen(tempstr);
				i++;
			}
			else if (format[i+1] == 'x') {
				u = va_arg(args, unsigned int);
				tempstr = int_to_hexstring(u);
				write_stdout(tempstr, strlen(tempstr));
				length += strlen(tempstr);
				i++;
			}
			else if (format[i+1] == 'c') {
				c[0] = (char) va_arg(args, int);
				write_stdout(c, strlen(c));
				length++;
				i++;
			}
			else if (format[i+1] == 's') {
				s = va_arg(args, char*);
				write_stdout(s, strlen(s));
				length += strlen(s);
				i++;
			}
			else if (format[i+1]=='%')
			{
				write_stdout("%",1);
				i++;
				length++;
			}
		} 
		else {
			c[0] = format[i];
			write_stdout(c,1);
			length++;
		}

	}
	
	return length;
}


int main() {

}