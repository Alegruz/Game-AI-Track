/************************************************************
 * Asks the user to enter an international dialing code and *
 * display the name of the corresponding country            *
 ************************************************************/
#include <stdio.h>

struct dialing_code {
    char *country;
    int code;
};

const struct dialing_code country_codes[] =
  {{"Argentina",            54}, {"Bangladesh",      880},
   {"Brazil",               55}, {"Burma (Myanmar)",  95},
   {"China",                86}, {"Colombia",         57},
   {"Congo, Dem. Rep. of", 243}, {"Egypt",            20},
   {"Ethiopia",            251}, {"France",           33},
   {"Germany",              49}, {"India",            91},
   {"Indonesia",            62}, {"Iran",             98},
   {"Italy",                39}, {"Japan",            81},
   {"Mexico",               52}, {"Nigeria",         234},
   {"Pakistan",             92}, {"Philippines",      63},
   {"Poland",               48}, {"Russia",            7},
   {"South Africa",         27}, {"South Korea",      82},
   {"Spain",                34}, {"Sudan",           249},
   {"Thailand",             66}, {"Turkey",           90},
   {"Ukraine",             380}, {"United Kingdom",   44},
   {"United States",         1}, {"Vietnam",          84}};

int main(void) {
    int international_dialing_code, country;

    for (;;) {
        printf("Enter an international dialing code: ");
        scanf(" %d", &international_dialing_code);
        if (international_dialing_code == 0)
            break;
        for (country = 0; country < sizeof (country_codes) / sizeof (country_codes[0]) && country_codes[country].code != international_dialing_code; ++country)
            ;
        if (country == 32)
            printf("Invalid dialing code. Try again.\n");
        else
            printf("The corresponding country is %s.\n", country_codes[country].country);
    }

    return 0;
}
