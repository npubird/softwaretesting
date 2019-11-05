// CgiDecode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"

using namespace std;

/*Get the hex value for a given character*/
int getHexValue(char c)
{
	int hValue=-1;
	if (c>='0' && c<='9')
	{
		hValue = c -'0';
	}
	else if (c>='A' && c<='F')
	{
		hValue = c-'A'+10;
	}
	else if (c>='a' && c<='f')
	{
		hValue = c-'a'+10;
	}
	return hValue;
}

/**    Translate a string from the CGI encoding to plain ascii text.
*     '+' becomes space, %xx becomes byte with hex value xx,
*    other alphanumeric characters map to themselves.
*    Returns 0 for success, positive for erroneous input
*         1 = bad hexadecimal digit
*/
int decode(char *encoded, char *decoded) 
{
	char *eptr = encoded;
	char *dptr = decoded;
	int ok=0;
	while (*eptr) 
	{
		char c;
		c = *eptr;
		if (c == '+') 
		{ /* Case 1: '+' maps to blank */
			*dptr = ' ';
		} 
		else if (c == '%') 
		{ /* Case 2: '%xx' is hex for character xx */
			int digit_high = getHexValue(*(++eptr));
			int digit_low = getHexValue(*(++eptr));
			if ( digit_high == -1 || digit_low==-1) {
				/* *dptr='?'; */
				ok=1; /* Bad return code */
			} else {
				*dptr = 16* digit_high + digit_low;
			}
		} else {/* Case 3: All other characters map to themselves */
			*dptr = *eptr;
		}
		++dptr;
		++eptr;
	}
	*dptr = '\0';               /* Null terminator for string */
	return ok;
}


int main()
{
	int ok;
	char *input="http://w...content-available-to-author-only...s.org/index.pl?node=Snippets%20Section";/*This is a test case*/
	char *output=(char*) malloc(strlen(input)+1);

	ok = decode(input, output);

	if (ok==0)
	{
		cout<<"Decode success!	output:"<<output<<endl;
	}
	else if (ok>0)
	{
		cout<<"erroneous input"<<endl;
		if (ok==1)
		{
			cout<<"bad hexadecimal digit"<<endl;
		}
	}

	return 0;
}

