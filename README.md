# -IOCLA_PRINTF --

	
	FUNCTION DOCUMENTATION

static int write_stdout(const char *token, int length) -- wrapper function for
printing a set length string


int digit_counter(int n) -- digit counter function for signed integers	

int digit_counter_u(unsigned int n) -- unsigned variant

int hexa_counter(unsigned int n) -- digit counter for hexa representation

char *int_to_string (int n) -- function for converting an int into a string
	-- notable additions include a  the neg flag to determine whether or not 
	to add a - at the beggining of the string if the number is negative 
	and the use of the abs function for the result of the modulo operator
	in order to avoid the integer overflow when multiplying by -1

char *uint_to_string(unsigned int n) -- function for converting an unsigned 
										int into a string

char *int_to_hexstring (unsigned int n) -- function for converting an unsigned 
										int into a hexadecimal form string

int iocla_printf(const char *format, ...) 
		
		
		-- the variable format printing function
		
		
		-- uses a few temporary container variables such as 'd', 'u', 'c', 's' 
		and 'tempstr' for ease of use of called functions 
		
		
		--tempstr is used to avoid the repeated use of the to_string functions
		
		
		--the main if clause in the for determines whether or not the current 
		character calls for the validation of a second character following it 
		in order to use up one of the arguments in the va_arg list.
	