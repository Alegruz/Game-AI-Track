/* Specify the types guaranteed to be large enough to store the item */

#include <stdio.h>

int main(void)
{
    /* (a) Days in a month = 28 ~ 31 */
    short days_in_a_month = 31;
    
    /* (b) Days in a year = 365 ~ 366 */
    short days_in_a_year = 365;
    
    /* (c) Minutes in a day = 1440 */
    short minutes_in_a_day = 1440;
    
    /* (d) Seconds in a day = 86400 */
    int seconds_in_a_day = 86400;

    return 0;
}
