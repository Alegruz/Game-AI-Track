/* Shows the illegal statements */

#include <stdio.h>

int main(void)
{
    char c = 'a';
    int i = 0;
    
    /* a */
    i += c;
    
    /* b */
    c = 2 * c - 1;
    
    /* c */
    putchar(c);
    
    /* d
     * printf(c);   no matching function for call to 'printf'
     */

    return 0;
}
